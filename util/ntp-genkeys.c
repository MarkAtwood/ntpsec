/*
 * Program to generate MD5 and RSA keys for NTP clients and servers
 */

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <limits.h>		/* PATH_MAX */
#include <sys/stat.h>		/* for umask() and stat() */
#include <sys/time.h>

#ifdef HAVE_NETINFO
#include <netinfo/ni.h>
#endif

#include "ntpd.h"
#include "ntp_stdlib.h"
#include "ntp_string.h"
#include "ntp_filegen.h"
#include "ntp_unixtime.h"
#include "ntp_config.h"

#ifdef PUBKEY
# include "ntp_crypto.h"
#endif

#ifndef PATH_MAX
# ifdef _POSIX_PATH_MAX
#  define PATH_MAX _POSIX_PATH_MAX
# else
#  define PATH_MAX 255
# endif
#endif

/*
 * Cryptodefines
 */
#define MAXKEYLEN	1024	/* maximum encoded key length */
#define MODULUSLEN	512	/* length of RSA modulus */
#define PRIMELEN	512	/* length of D_H prime, generator */

/*
 * This program generates (up to) four files:
 *
 *	ntp.keys    containing the DES/MD5 private keys,
 *	ntpkey      containing the RSA private key,
 *	ntpkey_HOST containing the RSA public key
 *		     where HOST is the DNS name of the generating machine,
 *	ntpkey_dh   containing the parameters for the Diffie-Hellman
 *		    key-agreement algorithm.
 *
 * The files contain cryptographic values generated by the algorithms of
 * the rsaref20 package and are in printable ASCII format.  Since the
 * algorythms are seeded by the system clock, each run of this program
 * will produce a different outcome.  There are no options or frills of
 * any sort, although a number of options would seem to be appropriate.
 * Waving this program in the breeze will no doubt bring a cast of
 * thousands to wiggle the options this way and that for various useful
 * purposes.
 *
 * The names of all files begin with "ntp" and end with an extension
 * consisting of the seconds value of the current NTP timestamp, which
 * appears in the form ".*".  This provides a way to distinguish between
 * key generations, since the host name and timestamp can be fetched by
 * a client during operation.
 *
 * The ntp.keys.* file contains 16 MD5 keys.  Each key consists of 16
 * characters randomized over the ASCII 95-character printing subset.
 * The file is read by the daemon at the location specified by the keys
 * configuration file command and made visible only to root.  An
 * additional key consisting of a easily remembered password should be
 * added by hand for use with the ntpdc program.  The file must be
 * distributed by secure means to other servers and clients sharing the
 * same security compartment.
 *
 * The key identifiers for MD5 and DES keys must be less than 65536,
 * although this program uses only the identifiers from 1 to 16.  The key
 * identifier for each association is specified as the key argument in
 * the server or peer configuration file command.
 *
 * The ntpkey.* file contains the RSA private key.  It is read by the
 * daemon at the location specified by the private argument of the
 * crypto configuration file command and made visible only to root.
 * This file is useful only to the machine that generated it and never
 * shared with any other daemon or application program.
 *
 * The ntpkey_host.* file contains the RSA public key, where host is the
 * DNS name of the host that generated it.  The file is read by the
 * daemon at the location specified by the public argument to the server
 * or peer configuration file command.  This file can be widely
 * distributed and stored without using secure means, since the data are
 * public values.
 *
 * The ntp_dh.* file contains two Diffie-Hellman parameters, the prime
 * modulus and the generator.  The file is read by the daemon at the
 * location specified by the dhparams argument of the crypto
 * configuration file command.  This file can be widely distributed and
 * stored without using secure means, since the data are public values.
 *
 * The file formats all begin with two lines.  The first line contains
 * the file name and decimal timestamp, while the second contains the
 * readable datestamp.  Lines beginning with # are considered comments
 * and ignored by the daemon.  In the ntp.keys.* file, the next 16 lines
 * contain the MD5 keys in order.  In the ntpkey.* and ntpkey_host.*
 * files, the next line contains the modulus length in bits followed by
 * the key as a PEM encoded string.  In the ntpkey_dh.* file, the next
 * line contains the prime length in bytes followed by the prime as a
 * PEM encoded string, and the next and final line contains the
 * generator length in bytes followed by the generator as a PEM encoded
 * string.
 *
 * Note: See the file ./source/rsaref.h in the rsaref20 package for
 * explanation of return values, if necessary.
 */


char *config_file;

#ifdef HAVE_NETINFO
struct netinfo_config_state *config_netinfo = NULL;
int check_netinfo = 1;
#endif /* HAVE_NETINFO */

#ifdef SYS_WINNT
char *alt_config_file;
LPTSTR temp;
char config_file_storage[PATH_MAX];
char alt_config_file_storage[PATH_MAX];
#endif /* SYS_WINNT */

int make_dh = 0;		/* Make D-H parameter file? */
int make_md5 = 0;		/* Make MD5 keyfile? */
int make_rsa = 0;		/* Make RSA pair? */
int force = 0;			/* Force the installation? */
int nosymlinks = 0;		/* Just create the (timestamped) files? */
int trash = 0;			/* Trash old files? */
int errflag = 0;

char *f1_keysdir = NTP_KEYSDIR;

char *f1_keys;			/* Visible MD5 key file name */
char *f2_keys;			/* timestamped */
char *f3_keys;			/* previous filename */

char *f1_publickey;
char *f2_publickey;
char *f3_publickey;

char *f1_privatekey;
char *f2_privatekey;
char *f3_privatekey;

char *f1_dhparms;
char *f2_dhparms;
char *f3_dhparms;


/* Stubs and hacks so we can link with ntp_config.o */
u_long	sys_automax;		/* maximum session key lifetime */
int	sys_bclient;		/* we set our time to broadcasts */
int	sys_manycastserver;	/* 1 => respond to manycast client pkts */
u_long	client_limit_period;
char *	req_file;		/* name of the file with configuration info */
keyid_t	ctl_auth_keyid;		/* keyid used for authenticating write requests */
struct interface *any_interface;	/* default interface */
keyid_t	info_auth_keyid;	/* keyid used to authenticate requests */
u_long	current_time;		/* current time (s) */
const char *Version = "";	/* version declaration */
keyid_t	req_keyid;		/* request keyid */
u_long	client_limit;
u_long	client_limit_period;
l_fp	sys_revoketime;
u_long	sys_revoke;		/* keys revoke timeout */
volatile int debug = 1;		/* debugging flag */

struct peer *
peer_config(
	struct sockaddr_in *srcadr,
	struct interface *dstadr,
	int hmode,
	int version,
	int minpoll,
	int maxpoll,
	u_int flags,
	int ttl,
	keyid_t key,
	u_char *keystr
	)
{
	if (debug > 1) printf("peer_config...\n");
	return 0;
}


void
set_sys_var(
	char *data,
	u_long size,
	int def
	)
{
	if (debug > 1) printf("set_sys_var...\n");
	return;
}


void
ntp_intres (void)
{
	if (debug > 1) printf("ntp_intres...\n");
	return;
}


int
ctlsettrap(
	struct sockaddr_in *raddr,
	struct interface *linter,
	int traptype,
	int version
	)
{
	if (debug > 1) printf("ctlsettrap...\n");
	return 0;
}


#ifdef PUBKEY
void
crypto_config(
	int item,		/* configuration item */
	char *cp		/* file name */
	)
{
	switch (item) {
	    case CRYPTO_CONF_DH:
		if (debug > 0) printf("crypto_config: DH/<%d> <%s>\n", item, cp);
		f1_dhparms = strdup(cp);
		break;
	    case CRYPTO_CONF_PRIV:
		if (debug > 0) printf("crypto_config: PRIVATEKEY/<%d> <%s>\n", item, cp);
		f1_privatekey = strdup(cp);
		break;
	    case CRYPTO_CONF_PUBL:
		if (debug > 0) printf("crypto_config: PUBLICKEY/<%d> <%s>\n", item, cp);
		f1_publickey = strdup(cp);
		break;
	    default:
		if (debug > 1) printf("crypto_config: <%d> <%s>\n", item, cp);
		break;
	}
	return;
}
#endif


struct interface *
findinterface(
	struct sockaddr_in *addr
	)
{
 	if (debug > 1) printf("findinterface...\n");
	return 0;
}


void
refclock_control(
	struct sockaddr_in *srcadr,
	struct refclockstat *in,
	struct refclockstat *out
	)
{
	if (debug > 1) printf("refclock_control...\n");
	return;
}


void
loop_config(
	int item,
	double freq
	)
{
	if (debug > 1) printf("loop_config...\n");
	return;
}


void
filegen_config(
	FILEGEN *gen,
	char    *basename,
	u_int   type,
	u_int   flag
	)
{
	if (debug > 1) printf("filegen_config...\n");
	return;
}


void
stats_config(
	int item,
	char *invalue	/* only one type so far */
	)
{
	if (debug > 1) printf("stats_config...\n");
	return;
}


void
hack_restrict(
	int op,
	struct sockaddr_in *resaddr,
	struct sockaddr_in *resmask,
	int mflags,
	int flags
	)
{
	if (debug > 1) printf("hack_restrict...\n");
	return;
}


void
kill_asyncio (void)
{
	if (debug > 1) printf("kill_asyncio...\n");
	return;
}


void
proto_config(
	int item,
	u_long value,
	double dvalue
	)
{
	if (debug > 1) printf("proto_config...\n");
	return;
}

void
getauthkeys(
	char *keyfile
	)
{
	if (debug > 0) printf("getauthkeys: got <%s>\n", keyfile);
	f1_keys = strdup(keyfile);
	return;
}


FILEGEN *
filegen_get(
	char *name
	)
{
	if (debug > 1) printf("filegen_get...\n");
	return 0;
}


/* End of stubs and hacks */


static void
usage(
	void
	)
{
	printf("Usage: %s [ -c ntp.conf ] [ -k key_file ]\n", progname);
	printf("       [ -f ] [ -l ] [ -t ] [ -d ] [ -m ] [ -r ]\n");
	printf(" where:\n");
	printf("  -c /etc/ntp.conf   Location of ntp.conf file\n");
	printf("  -k key_file        Location of key file\n");
	printf("  -f     force installation of generated keys.\n");
	printf("  -l     Don't make the symlinks\n");
	printf("  -t     Trash the (old) files at the end of symlink\n");
	printf("  -d     Generate D-H parameter file\n");
	printf("  -m     Generate MD5 key file\n");
	printf("  -r     Generate RSA keys\n");

	exit(1);
}


void
getCmdOpts (
	int argc,
	char *argv[]
	)
{
	int i;

	while ((i = ntp_getopt(argc, argv, "c:dflmrt")) != EOF)
		switch (i) {
		    case 'c':
			config_file = ntp_optarg;
#ifdef HAVE_NETINFO
			check_netinfo = 0;
#endif
			break;
		    case 'd':
			++make_dh;
			break;
		    case 'f':
			++force;
			break;
		    case 'l':
			++nosymlinks;
			break;
		    case 'm':
			++make_md5;
			break;
		    case 'r':
			++make_rsa;
			break;
		    case 't':
			++trash;
			break;
		    case '?':
			++errflag;
			break;
		}

	if (errflag)
		usage();

	/* If no file type was specified, make them all. */
	if (!(make_dh | make_md5 | make_rsa)) {
		++make_dh;
		++make_md5;
		++make_rsa;
	}
}


void
snifflink(
	const char *file,
	char **linkdata
	)
{
#ifdef HAVE_READLINK
	char buf[PATH_MAX];
	int rc;

	if (!file)
		return;

	rc = readlink(file, buf, sizeof buf);
	if (-1 == rc) {
		switch (errno) {
		    case EINVAL:	/* Fall thru */
		    case ENOENT:
			return;
		}
		fprintf(stderr, "%s: readlink(%s) failed: (%d) %s\n",
			progname, file, errno, strerror(errno));
		exit(1);
	}
	buf[rc] = '\0';
	*linkdata = strdup(buf);
	/* XXX: make sure linkdata is not 0... */
#endif /* not HAVE_READLINK */
	return;
}


int
filep(
	const char *fn
	)
{
	struct stat sb;

	if (-1 == stat(fn, &sb)) {
		if (ENOENT == errno)
			return 0;
		fprintf(stderr, "stat(%s) failed: %s\n",
			fn, strerror(errno));
		exit(1);
	}
	return 1;
}


FILE *
newfile(
	const char *f1,		/* Visible file */
	const char *f2,		/* New timestamped file name */
	const char *f3		/* Previous symlink target */
	)
{
	FILE *fp;
	char fb[PATH_MAX];
	char *cp;

	if (debug > 1) printf("newfile(%s,%s,%s)\n", f1, f2, f3?f3:"NULL");
	/*
	   If:
	   - no symlink support, or
	   - there is no old symlink (!f3)
	   - - file = dirname(f1) / f2
	   Otherwise:
	   - If ('/' == *f3)
	   - - file = dirname(f3) / f2
	   - else
	   - - file = dirname(f1) / dirname(f3) / f2
	   fopen(file)
	   print any error message/bail
	   return FILE
	*/
	if (
#ifdef HAVE_READLINK
	    !f3
#else
	    1
#endif
	   ) {
		/* file = dirname(f1) / f2 */
		snprintf(fb, sizeof fb, "%s", f1);
		cp = strrchr(fb, '/');
		if (cp) {
			*cp = 0;
		}
		snprintf(fb, sizeof fb, "%s/%s", fb, f2);
		if (debug > 1) printf("case 1: file is <%s>\n", fb);
	} else {
	/*
	   - If ('/' == *f3)
	   - - file = dirname(f3) / f2
	   - else
	   - - file = dirname(f1) / dirname(f3) / f2
	*/
		if ('/' != *f3) {
			snprintf(fb, sizeof fb, "%s", f1);
			cp = strrchr(fb, '/');
			if (cp) {
				++cp;
				*cp = 0;
			}
			if (debug > 1) printf("case 2: file is <%s>\n", fb);
		} else {
			*fb = 0;
		}
		snprintf(fb, sizeof fb, "%s%s", fb, f3);
		cp = strrchr(fb, '/');
		if (cp) {
			*cp = 0;
		}
		snprintf(fb, sizeof fb, "%s/%s", fb, f2);
		if (debug > 1) printf("case 3: file is <%s>\n", fb);
	}

	/*
	   fopen(file)
	   print any error message/bail
	   return FILE
	*/
	fp = fopen(fb, "w");
	if (fp == NULL) {
		perror(fb);
		exit(1);
	}
	return fp;
}

void
cleanlinks(
	const char *f1,		/* Visible file */
	const char *f2,		/* New timestamped file name */
	const char *f3		/* Previous symlink target */
	)
{
#ifdef HAVE_READLINK
	char *cp;
	char fb[PATH_MAX];

	/*
	  Just return if nosymlinks.
	  unlink f1
	  file = dirname(f3) / f2
	  symlink file, f1
	  If trash:
	  - if f3 begins with a /, unlink it
	  - else, unlink dirname(f1) / f3
	*/
#endif /* HAVE_READLINK */
	if (unlink(f1)) {
		if (errno != ENOENT) {
			fprintf(stderr, "unlink(%s) failed: %s\n", f1,
				strerror(errno));
			return;
		}
	}
	/* file = dirname(f3) / f2 */
	if (f3) {
		snprintf(fb, sizeof fb, "%s", f3);
		cp = strrchr(fb, '/');
		if (cp) {
			++cp;
			*cp = 0;
		}
	} else {
		*fb = 0;
	}
	snprintf(fb, sizeof fb, "%s%s", fb, f2);
	if (debug > 1) printf("cleanlinks 1: file is <%s>\n", fb);

	if (symlink(fb, f1)) {
		fprintf(stderr, "symlink(%s,%s) failed: %s\n", fb, f1,
			strerror(errno));
		return;
	}

	/*
	  If trash:
	  - if f3 begins with a /, unlink it
	  - else, unlink dirname(f1) / f3
	*/
	if (trash && f3) {
		if ('/' == *f3) {
			if (unlink(f3)) {
				if (errno != ENOENT) {
					fprintf(stderr, "unlink(%s) failed: %s\n", f3,
						strerror(errno));
					return;
				}
			}
		} else {
			snprintf(fb, sizeof fb, "%s", f1);
			cp = strrchr(fb, '/');
			if (cp) {
				*cp = 0;
			}
			snprintf(fb, sizeof fb, "%s/%s", fb, f3);
			if (debug > 1)
				printf("cleanlinks 2: file is <%s>\n", fb);
			if (unlink(fb)) {
				if (errno != ENOENT) {
					fprintf(stderr, "unlink(%s) failed: %s\n", fb,
						strerror(errno));
					return;
				}
			}
		}
	}

	return;
}


int
main(
	int argc,
	char *argv[]
	)
{
#ifdef PUBKEY
	R_RSA_PRIVATE_KEY rsaref_private; /* RSA private key */
	R_RSA_PUBLIC_KEY rsaref_public;	/* RSA public key */
	R_RSA_PROTO_KEY protokey;	/* RSA prototype key */
	R_DH_PARAMS dh_params;		/* Diffie-Hellman parameters */
	R_RANDOM_STRUCT randomstr;	/* random structure */
	int rval;			/* return value */
	u_char encoded_key[MAXKEYLEN];	/* encoded PEM string buffer */
	u_int modulus;			/* modulus length */
	u_int len;
#endif /* PUBKEY */
	struct timeval tv;		/* initialization vector */
	u_long ntptime;			/* NTP timestamp */
	u_char hostname[256];		/* DNS host name */
	u_char md5key[17];		/* generated MD5 key */ 
	FILE *str;			/* file handle */
	u_int temp;
	int i, j;
	mode_t std_mask;	/* Standard mask */
	mode_t sec_mask = 077;	/* Secure mask */
	char pathbuf[PATH_MAX];

	gethostname(hostname, sizeof(hostname));
	gettimeofday(&tv, 0);
	ntptime = tv.tv_sec + JAN_1970;

	/* Initialize config_file */
	getconfig(argc, argv);	/* ntpd/ntp_config.c */

	if (!f1_keysdir) {
		/* Shouldn't happen... */
		f1_keysdir = "PATH_KEYSDIR";
	}
	if (*f1_keysdir != '/') {
		fprintf(stderr,
			"%s: keysdir path <%s> doesn't begin with a /\n",
			progname, f1_keysdir);
		exit(1);
	}

	if (!f2_keys) {
		snprintf(pathbuf, sizeof pathbuf, "ntp.keys.%lu",
			 ntptime);
		f2_keys = strdup(pathbuf);
	}
	if (!f1_keys) {
		snprintf(pathbuf, sizeof pathbuf, "%s/ntp.keys",
			 f1_keysdir);
		f1_keys = strdup(pathbuf);
	}
	if (*f1_keys != '/') {
		fprintf(stderr,
			"%s: keys path <%s> doesn't begin with a /\n",
			progname, f1_keys);
		exit(1);
	}
	snifflink(f1_keys, &f3_keys);

	if (!f2_publickey) {
		snprintf(pathbuf, sizeof pathbuf, "ntpkey_%s.%lu",
			 hostname, ntptime);
		f2_publickey = strdup(pathbuf);
	}
	if (!f1_publickey) {
		snprintf(pathbuf, sizeof pathbuf, "%s/ntpkey_%s",
			 f1_keysdir, hostname);
		f1_publickey = strdup(pathbuf);
	}
	if (*f1_publickey != '/') {
		fprintf(stderr,
			"%s: publickey path <%s> doesn't begin with a /\n",
			progname, f1_publickey);
		exit(1);
	}
	snifflink(f1_publickey, &f3_publickey);

	if (!f2_privatekey) {
		snprintf(pathbuf, sizeof pathbuf, "ntpkey.%lu",
			 ntptime);
		f2_privatekey = strdup(pathbuf);
	}
	if (!f1_privatekey) {
		snprintf(pathbuf, sizeof pathbuf, "%s/ntpkey",
			 f1_keysdir);
		f1_privatekey = strdup(pathbuf);
	}
	if (*f1_privatekey != '/') {
		fprintf(stderr,
			"%s: privatekey path <%s> doesn't begin with a /\n",
			progname, f1_privatekey);
		exit(1);
	}
	snifflink(f1_privatekey, &f3_privatekey);

	if (!f2_dhparms) {
		snprintf(pathbuf, sizeof pathbuf, "ntpkey_dh.%lu",
			 ntptime);
		f2_dhparms = strdup(pathbuf);
	}
	if (!f1_dhparms) {
		snprintf(pathbuf, sizeof pathbuf, "%s/ntpkey_dh",
			 f1_keysdir);
		f1_dhparms = strdup(pathbuf);
	}
	if (*f1_dhparms != '/') {
		fprintf(stderr,
			"%s: dhparms path <%s> doesn't begin with a /\n",
			progname, f1_dhparms);
		exit(1);
	}
	snifflink(f1_dhparms, &f3_dhparms);

	if (debug) {
		printf("After config:\n");
		printf("keysdir    = <%s>\n", f1_keysdir? f1_keysdir: "");
		printf("keys       = <%s> -> <%s>\n"
		       , f1_keys? f1_keys: ""
		       , f2_keys? f2_keys: ""
		      );
		printf("       old = <%s>\n", f3_keys? f3_keys: "");
		printf("publickey  = <%s> -> <%s>\n"
		       , f1_publickey? f1_publickey: ""
		       , f2_publickey? f2_publickey: ""
		      );
		printf("       old = <%s>\n", f3_publickey? f3_publickey: "");
		printf("privatekey = <%s> -> <%s>\n"
		       , f1_privatekey? f1_privatekey: ""
		       , f2_privatekey? f2_privatekey: ""
		      );
		printf("       old = <%s>\n", f3_privatekey? f3_privatekey: "");
		printf("dhparms    = <%s> -> <%s>\n"
		       , f1_dhparms? f1_dhparms: ""
		       , f2_dhparms? f2_dhparms: ""
		      );
		printf("       old = <%s>\n", f3_dhparms? f3_dhparms: "");
	}

	/*
	  for each file we're going to install:
	  - make the new timestamped file
	  - if (!nosymlinks)
	  - - remove any old link
	  - - make the link
	  - - if (trash)
	  - - - remove the old file
	*/

	std_mask = umask(sec_mask); /* Get the standard mask */

	if (make_md5 && (force || !filep(f1_keys))) {
		/*
		 * Generate 16 random MD5 keys.
		 */
		printf("Generating MD5 key file...\n");
		str = newfile(f1_keys, f2_keys, f3_keys);
		srandom((u_int)tv.tv_usec);
		fprintf(str, "# MD5 key file %s\n# %s", f2_keys,
			ctime(&tv.tv_sec));
		for (i = 1; i <= 16; i++) {
			for (j = 0; j < 16; j++) {
				while (1) {
					temp = random() & 0xff;
					if (temp > 0x20 && temp < 0x7f)
						break;
				}
				md5key[j] = (u_char)temp;
			}
			md5key[16] = 0;
			fprintf(str, "%2d M %16s	# MD5 key\n", i,
				md5key);
		}
		fclose(str);
		cleanlinks(f1_keys, f2_keys, f3_keys);
	}

#ifdef PUBKEY
	if (make_rsa && (force || !filep(f1_publickey)
			 || !filep(f1_privatekey))) {
		/*
		 * Roll the RSA public/private key pair.
		 */
		printf("Generating RSA public/private key pair (%d bits)...\n",
		       MODULUSLEN);
		protokey.bits = MODULUSLEN;
		protokey.useFermat4 = 1;
		R_RandomInit(&randomstr);
		R_GetRandomBytesNeeded(&len, &randomstr);
		for (i = 0; i < len; i++) {
			temp = random();
			R_RandomUpdate(&randomstr, (u_char *)&temp, 1);
		}
		rval = R_GeneratePEMKeys(&rsaref_public, &rsaref_private,
					 &protokey, &randomstr);
		if (rval) {
			printf("R_GeneratePEMKeys error %x\n", rval);
			return (-1);
		}

		/*
		 * Generate the file "ntpkey.*" containing the RSA
		 * private key in printable ASCII format.
		 */
		str = newfile(f1_privatekey, f2_privatekey, f3_privatekey);
		len = sizeof(rsaref_private) - sizeof(rsaref_private.bits);
		modulus = (u_int32)rsaref_private.bits;
		fprintf(str, "# RSA private key file %s\n# %s", f2_privatekey,
			ctime(&tv.tv_sec));
		R_EncodePEMBlock(encoded_key, &temp,
				 (u_char *)rsaref_private.modulus, len);
		encoded_key[temp] = '\0';
		fprintf(str, "%d %s\n", modulus, encoded_key);
		fclose(str);
		cleanlinks(f1_privatekey, f2_privatekey, f3_privatekey);

		/*
		 * Generate the file "ntpkey_host.*" containing the RSA
		 * public key in printable ASCII format.
		 */
		str = newfile(f1_publickey, f2_publickey, f3_publickey);
		len = sizeof(rsaref_public) - sizeof(rsaref_public.bits);
		modulus = (u_int32)rsaref_public.bits;
		fprintf(str, "# RSA public key file %s\n# %s", f2_publickey,
			ctime(&tv.tv_sec));
		R_EncodePEMBlock(encoded_key, &temp,
				 (u_char *)rsaref_public.modulus, len);
		encoded_key[temp] = '\0';
		fprintf(str, "%d %s\n", modulus, encoded_key);
		fclose(str);
		cleanlinks(f1_publickey, f2_publickey, f3_publickey);
	}
#endif /* PUBKEY */

#ifdef PUBKEY
	if (make_dh && (force || !filep(f1_dhparms))) {
		/*
		 * Roll the prime and generator for the Diffie-Hellman key
		 * agreement algorithm.
		 */
		printf("Generating Diffie-Hellman parameters (%d bits)...\n",
		       PRIMELEN);
		str = newfile(f1_dhparms, f2_dhparms, f3_dhparms);

		R_RandomInit(&randomstr);
		R_GetRandomBytesNeeded(&len, &randomstr);
		for (i = 0; i < len; i++) {
			temp = random();
			R_RandomUpdate(&randomstr, (u_char *)&temp, 1);
		}

		/*
		 * Generate the file "ntpkey_dh.*" containing the
		 * Diffie-Hellman prime and generator in printable ASCII
		 * format.
		 */
		len = DH_PRIME_LEN(PRIMELEN);
		dh_params.prime = (u_char *)malloc(len);
		dh_params.generator = (u_char *)malloc(len);
		rval = R_GenerateDHParams(&dh_params, PRIMELEN, PRIMELEN / 2,
					  &randomstr);
		if (rval) {
			printf("R_GenerateDHParams error %x\n", rval);
			return (-1);
		}

		fprintf(str, "# Diffie-Hellman parameter file %s\n# %s",
			f2_dhparms, ctime(&tv.tv_sec));
		R_EncodePEMBlock(encoded_key, &temp,
				 (u_char *)dh_params.prime,
				 dh_params.primeLen);
		encoded_key[temp] = '\0';
		fprintf(str, "%d %s\n", dh_params.primeLen, encoded_key);
		R_EncodePEMBlock(encoded_key, &temp,
				 (u_char *)dh_params.generator,
				 dh_params.generatorLen);
		encoded_key[temp] = '\0';
		fprintf(str, "%d %s\n", dh_params.generatorLen, encoded_key);
		fclose(str);
		cleanlinks(f1_dhparms, f2_dhparms, f3_dhparms);
	}
#endif /* PUBKEY */

	return (0);
}
