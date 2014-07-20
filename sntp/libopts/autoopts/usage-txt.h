/*  -*- buffer-read-only: t -*- vi: set ro:
 *
 * DO NOT EDIT THIS FILE   (usage-txt.h)
 *
 * It has been AutoGen-ed  July  6, 2014 at 02:01:31 PM by AutoGen 5.18.4pre8
 * From the definitions    usage-txt.def
 * and the template file   usage-txt.tpl
 *
 *  This file is part of AutoOpts, a companion to AutoGen.
 *  AutoOpts is free software.
 *  AutoOpts is Copyright (C) 1992-2014 by Bruce Korb - all rights reserved
 *
 *  AutoOpts is available under any one of two licenses.  The license
 *  in use must be one of these two and the choice is under the control
 *  of the user of the license.
 *
 *   The GNU Lesser General Public License, version 3 or later
 *      See the files "COPYING.lgplv3" and "COPYING.gplv3"
 *
 *   The Modified Berkeley Software Distribution License
 *      See the file "COPYING.mbsd"
 *
 *  These files have the following sha256 sums:
 *
 *  8584710e9b04216a394078dc156b781d0b47e1729104d666658aecef8ee32e95  COPYING.gplv3
 *  4379e7444a0e2ce2b12dd6f5a52a27a4d02d39d247901d3285c88cf0d37f477b  COPYING.lgplv3
 *  13aa749a5b0a454917a944ed8fffc530b784f5ead522b1aacaf4ec8aa55a6239  COPYING.mbsd
 */
/** @file usage-txt.h
 *
 *  This file handles all the bookkeeping required for tracking all the little
 *  tiny strings used by the AutoOpts library.  There are 108
 *  of them.  This is not versioned because it is entirely internal to the
 *  library and accessed by client code only in a very well-controlled way:
 *  they may substitute translated strings using a procedure that steps through
 *  all the string pointers.
 */
#ifndef AUTOOPTS_USAGE_TXT_H_GUARD
#define AUTOOPTS_USAGE_TXT_H_GUARD 1

/*
 *  One structure to hold all the pointers to all the translatable strings.
 */
typedef struct {
  int           field_ct;
  char *        utpz_GnuBoolArg;
  char *        utpz_GnuKeyArg;
  char *        utpz_GnuNumArg;
  char *        utpz_GnuStrArg;
  char const *  apz_str[104];
} usage_text_t;

/*
 *  Declare the global structure with all the pointers to translatable
 *  strings and the text array containing untranslatable strings.
 */
extern usage_text_t option_xlateable_txt;
extern char const option_lib_text[4285];

#if defined(AUTOOPTS_INTERNAL)
/*
 *  Provide a mapping from a short name to either the text directly
 *  (for untranslatable strings), or to pointers to the text, rendering
 *  them translatable.
 */
#define zalloc_fail           (option_xlateable_txt.apz_str[  0])
#define zno_opt_arg           (option_xlateable_txt.apz_str[  1])
#define ztoo_new              (option_xlateable_txt.apz_str[  2])
#define zwrong_ver            (option_xlateable_txt.apz_str[  3])
#define zrealloc_fail         (option_xlateable_txt.apz_str[  4])
#define ztoo_old              (option_xlateable_txt.apz_str[  5])
#define zao_ver_fmt           (option_xlateable_txt.apz_str[  6])
#define zao_bug_msg           (option_xlateable_txt.apz_str[  7])
#define zno_reset             (option_xlateable_txt.apz_str[  8])
#define zmissing_help_msg     (option_xlateable_txt.apz_str[  9])
#define zbad_data_msg         (option_xlateable_txt.apz_str[ 10])
#define zbad_arg_type_msg     (option_xlateable_txt.apz_str[ 11])
#define zbad_default_msg      (option_xlateable_txt.apz_str[ 12])
#define zbad_alias_id         (option_xlateable_txt.apz_str[ 13])
#define zambiguous_key        (option_xlateable_txt.apz_str[ 14])
#define zambig_list_msg       (option_xlateable_txt.apz_str[ 15])
#define zambig_opt_fmt        (option_xlateable_txt.apz_str[ 16])
#define zargs_must            (option_xlateable_txt.apz_str[ 17])
#define zat_most              (option_xlateable_txt.apz_str[ 18])
#define zfserr_fmt            (option_xlateable_txt.apz_str[ 19])
#define zinter_proc_pipe      (option_xlateable_txt.apz_str[ 20])
#define zBadVerArg            (option_xlateable_txt.apz_str[ 21])
#define zconflict_fmt         (option_xlateable_txt.apz_str[ 22])
#define zDisabledErr          (option_xlateable_txt.apz_str[ 23])
#define zequiv                (option_xlateable_txt.apz_str[ 24])
#define zGnuBoolArg           (option_xlateable_txt.utpz_GnuBoolArg)
#define zGnuKeyArg            (option_xlateable_txt.utpz_GnuKeyArg)
#define zGnuNumArg            (option_xlateable_txt.utpz_GnuNumArg)
#define zGnuStrArg            (option_xlateable_txt.utpz_GnuStrArg)
#define zIllOptChr            (option_xlateable_txt.apz_str[ 25])
#define zIllOptStr            (option_xlateable_txt.apz_str[ 26])
#define zIllVendOptStr        (option_xlateable_txt.apz_str[ 27])
#define zIntRange             (option_xlateable_txt.apz_str[ 28])
#define zbad_od               (option_xlateable_txt.apz_str[ 29])
#define zInvalOptName         (option_xlateable_txt.apz_str[ 30])
#define zMisArg               (option_xlateable_txt.apz_str[ 31])
#define zmultiway_bug         (option_xlateable_txt.apz_str[ 32])
#define zneed_one             (option_xlateable_txt.apz_str[ 33])
#define zNoArg                (option_xlateable_txt.apz_str[ 34])
#define zNoArgs               (option_xlateable_txt.apz_str[ 35])
#define zNoCreat              (option_xlateable_txt.apz_str[ 36])
#define zNoKey                (option_xlateable_txt.apz_str[ 37])
#define zreset_arg            (option_xlateable_txt.apz_str[ 38])
#define zNoStat               (option_xlateable_txt.apz_str[ 39])
#define zNoState              (option_xlateable_txt.apz_str[ 40])
#define zNotCmdOpt            (option_xlateable_txt.apz_str[ 41])
#define zNotDate              (option_xlateable_txt.apz_str[ 42])
#define zNotDef               (option_xlateable_txt.apz_str[ 43])
#define zNotDuration          (option_xlateable_txt.apz_str[ 44])
#define zneed_more            (option_xlateable_txt.apz_str[ 45])
#define zNotNumber            (option_xlateable_txt.apz_str[ 46])
#define znum_too_large        (option_xlateable_txt.apz_str[ 47])
#define zoffer_usage_fmt      (option_xlateable_txt.apz_str[ 48])
#define zonly_one             (option_xlateable_txt.apz_str[ 49])
#define zstdout_name          (option_xlateable_txt.apz_str[ 50])
#define zstderr_name          (option_xlateable_txt.apz_str[ 51])
#define zwriting              (option_xlateable_txt.apz_str[ 52])
#define zRangeErr             (option_xlateable_txt.apz_str[ 53])
#define zneed_fmt             (option_xlateable_txt.apz_str[ 54])
#define zsave_warn            (option_xlateable_txt.apz_str[ 55])
#define zalt_opt              (option_xlateable_txt.apz_str[ 56])
#define zAuto                 (option_xlateable_txt.apz_str[ 57])
#define zDefaultOpt           (option_xlateable_txt.apz_str[ 58])
#define zDis                  (option_xlateable_txt.apz_str[ 59])
#define zDisabledOpt          (option_xlateable_txt.apz_str[ 60])
#define zDisabledWhy          (option_xlateable_txt.apz_str[ 61])
#define zEnab                 (option_xlateable_txt.apz_str[ 62])
#define ztoo_often_fmt        (option_xlateable_txt.apz_str[ 63])
#define zExamineFmt           (option_xlateable_txt.apz_str[ 64])
#define zFileCannotExist      (option_xlateable_txt.apz_str[ 65])
#define zFileMustExist        (option_xlateable_txt.apz_str[ 66])
#define zFlagOkay             (option_xlateable_txt.apz_str[ 67])
#define zGenshell             (option_xlateable_txt.apz_str[ 68])
#define zLowerBits            (option_xlateable_txt.apz_str[ 69])
#define zMembers              (option_xlateable_txt.apz_str[ 70])
#define zMust                 (option_xlateable_txt.apz_str[ 71])
#define zNoFlags              (option_xlateable_txt.apz_str[ 72])
#define zNoLim                (option_xlateable_txt.apz_str[ 73])
#define zNoPreset             (option_xlateable_txt.apz_str[ 74])
#define zNoRq_NoShrtTtl       (option_xlateable_txt.apz_str[ 75])
#define zNoRq_ShrtTtl         (option_xlateable_txt.apz_str[ 76])
#define zNrmOptFmt            (option_xlateable_txt.apz_str[ 77])
#define zNumberOpt            (option_xlateable_txt.apz_str[ 78])
#define zOptsOnly             (option_xlateable_txt.apz_str[ 79])
#define zPathFmt              (option_xlateable_txt.apz_str[ 80])
#define zPlsSendBugs          (option_xlateable_txt.apz_str[ 81])
#define zPreset               (option_xlateable_txt.apz_str[ 82])
#define zPresetIntro          (option_xlateable_txt.apz_str[ 83])
#define zProhib               (option_xlateable_txt.apz_str[ 84])
#define zProhibOne            (option_xlateable_txt.apz_str[ 85])
#define zRange                (option_xlateable_txt.apz_str[ 86])
#define zRangeAbove           (option_xlateable_txt.apz_str[ 87])
#define zRangeExact           (option_xlateable_txt.apz_str[ 88])
#define zRangeLie             (option_xlateable_txt.apz_str[ 89])
#define zRangeOnly            (option_xlateable_txt.apz_str[ 90])
#define zRangeOr              (option_xlateable_txt.apz_str[ 91])
#define zRangeScaled          (option_xlateable_txt.apz_str[ 92])
#define zRangeUpto            (option_xlateable_txt.apz_str[ 93])
#define zReorder              (option_xlateable_txt.apz_str[ 94])
#define zReqOne               (option_xlateable_txt.apz_str[ 95])
#define zReqThese             (option_xlateable_txt.apz_str[ 96])
#define zReq_NoShrtTtl        (option_xlateable_txt.apz_str[ 97])
#define zReq_ShrtTtl          (option_xlateable_txt.apz_str[ 98])
#define zSetMemberSettings    (option_xlateable_txt.apz_str[ 99])
#define zUpTo                 (option_xlateable_txt.apz_str[100])
#define zValidKeys            (option_xlateable_txt.apz_str[101])
#define zVendIntro            (option_xlateable_txt.apz_str[102])
#define zVendOptsAre          (option_xlateable_txt.apz_str[103])

  /*
   *  First, set up the strings.  Some of these are writable.  These are all in
   *  English.  This gets compiled into libopts and is distributed here so that
   *  xgettext (or equivalents) can extract these strings for translation.
   */
static char eng_zGnuBoolArg[]  = "=T/F";
static char eng_zGnuKeyArg[]   = "=KWd";
static char eng_zGnuNumArg[]   = "=num";
static char eng_zGnuStrArg[]   = "=str";
char const option_lib_text[4285] =
/*     0 */ "allocation of %d bytes failed\n\0"
/*    31 */ "AutoOpts function called without option descriptor\n\0"
/*    83 */ "\tThis exceeds the compiled library version:  \0"
/*   129 */ "Automated Options Processing Error!\n"
            "\t%s called AutoOpts function with structure version %d:%d:%d.\n\0"
/*   228 */ "realloc of %d bytes at 0x%p failed\n\0"
/*   264 */ "\tThis is less than the minimum library version:  \0"
/*   314 */ "Automated Options version %s\n"
            "\tCopyright (C) 1999-2014 by Bruce Korb - all rights reserved\n\0"
/*   405 */ "(AutoOpts bug):  %s.\n\0"
/*   427 */ "optionResetOpt() called, but reset-option not configured\0"
/*   484 */ "could not locate the 'help' option\0"
/*   519 */ "optionProcess() was called with invalid data\0"
/*   564 */ "invalid argument type specified\0"
/*   596 */ "defaulted to option with optional arg\0"
/*   634 */ "aliasing option is out of range.\0"
/*   667 */ "%s error:  the keyword '%s' is ambiguous for %s\n\0"
/*   716 */ "  The following options match:\n\0"
/*   748 */ "%s: ambiguous option name: %s (matches %d options)\n\0"
/*   800 */ "%s: Command line arguments required\n\0"
/*   837 */ "%d %s%s options allowed\n\0"
/*   862 */ "%s error %d (%s) calling %s for '%s'\n\0"
/*   900 */ "interprocess pipe\0"
/*   918 */ "error: version option argument '%c' invalid.  Use:\n"
            "\t'v' - version only\n"
            "\t'c' - version and copyright\n"
            "\t'n' - version and full copyright notice\n\0"
/*  1060 */ "%s error:  the '%s' and '%s' options conflict\n\0"
/*  1107 */ "%s: The '%s' option has been disabled.\0"
/*  1146 */ "-equivalence\0"
/*  1159 */ "%s: illegal option -- %c\n\0"
/*  1185 */ "%s: illegal option -- %s\n\0"
/*  1211 */ "%s: unknown vendor extension option -- %s\n\0"
/*  1254 */ "  or an integer from %d through %d\n\0"
/*  1290 */ "%s error:  invalid option descriptor for %s\n\0"
/*  1335 */ "%s: invalid option name: %s\n\0"
/*  1364 */ "%s: The '%s' option requires an argument.\n\0"
/*  1407 */ "(AutoOpts bug):  Equivalenced option '%s' was equivalenced to both\n"
            "\t'%s' and '%s'.\0"
/*  1490 */ "%s error:  The %s option is required\n\0"
/*  1528 */ "%s: The '%s' option cannot have an argument.\n\0"
/*  1574 */ "%s: Command line arguments are not allowed.\n\0"
/*  1619 */ "error %d (%s) creating %s\n\0"
/*  1646 */ "%s error:  '%s' does not match any %s keywords.\n\0"
/*  1695 */ "%s error: The '%s' option requires an argument.\n\0"
/*  1744 */ "error %d (%s) stat-ing %s\n\0"
/*  1771 */ "%s error: no saved option state\n\0"
/*  1804 */ "'%s' is not a command line option.\n\0"
/*  1840 */ "%s error:  '%s' is not a recognizable date/time.\n\0"
/*  1890 */ "'%s' not defined\n\0"
/*  1908 */ "%s error:  '%s' is not a recognizable time duration.\n\0"
/*  1962 */ "%s error:  The %s option must appear %d times.\n\0"
/*  2010 */ "%s error:  '%s' is not a recognizable number.\n\0"
/*  2057 */ "%s error:  %s exceeds %s keyword count\n\0"
/*  2097 */ "Try '%s %s' for more information.\n\0"
/*  2132 */ "one %s%s option allowed\n\0"
/*  2157 */ "standard output\0"
/*  2173 */ "standard error\0"
/*  2188 */ "write\0"
/*  2194 */ "%s error:  %s option value %ld is out of range.\n\0"
/*  2243 */ "%s error:  %s option requires the %s option\n\0"
/*  2288 */ "%s warning:  cannot save options - %s not regular file\n\0"
/*  2344 */ "\t\t\t\t- an alternate for '%s'\n\0"
/*  2373 */ "Version, usage and configuration options:\0"
/*  2415 */ "\t\t\t\t- default option for unnamed options\n\0"
/*  2457 */ "\t\t\t\t- disabled as '--%s'\n\0"
/*  2483 */ " --- %-14s %s\n\0"
/*  2498 */ "This option has been disabled\0"
/*  2528 */ "\t\t\t\t- enabled by default\n\0"
/*  2554 */ "%s error:  only \0"
/*  2571 */ " - examining environment variables named %s_*\n\0"
/*  2618 */ "\t\t\t\t- file must not pre-exist\n\0"
/*  2649 */ "\t\t\t\t- file must pre-exist\n\0"
/*  2676 */ "Options are specified by doubled hyphens and their name or by a single\n"
            "hyphen and the flag character.\n\0"
/*  2779 */ "\n"
            "= = = = = = = =\n\n"
            "This incarnation of genshell will produce\n"
            "a shell script to parse the options for %s:\n\n\0"
/*  2885 */ "  or an integer mask with any of the lower %d bits set\n\0"
/*  2941 */ "\t\t\t\t- is a set membership option\n\0"
/*  2975 */ "\t\t\t\t- must appear between %d and %d times\n\0"
/*  3018 */ "Options are specified by single or double hyphens and their name.\n\0"
/*  3085 */ "\t\t\t\t- may appear multiple times\n\0"
/*  3118 */ "\t\t\t\t- may not be preset\n\0"
/*  3143 */ "   Arg Option-Name    Description\n\0"
/*  3178 */ "  Flg Arg Option-Name    Description\n\0"
/*  3216 */ " %3s %s\0"
/*  3224 */ "The '-#<number>' option may omit the hash char\n\0"
/*  3272 */ "All arguments are named options.\n\0"
/*  3306 */ " - reading file %s\0"
/*  3325 */ "\n"
            "Please send bug reports to:  <%s>\n\0"
/*  3361 */ "\t\t\t\t- may NOT appear - preset only\n\0"
/*  3397 */ "\n"
            "The following option preset mechanisms are supported:\n\0"
/*  3453 */ "prohibits these options:\n\0"
/*  3479 */ "prohibits the option '%s'\n\0"
/*  3506 */ "%s%ld to %ld\0"
/*  3519 */ "%sgreater than or equal to %ld\0"
/*  3550 */ "%s%ld exactly\0"
/*  3564 */ "%sit must lie in one of the ranges:\n\0"
/*  3601 */ "%sit must be in the range:\n\0"
/*  3629 */ ", or\n\0"
/*  3635 */ "%sis scalable with a suffix: k/K/m/M/g/G/t/T\n\0"
/*  3681 */ "%sless than or equal to %ld\0"
/*  3709 */ "Operands and options may be intermixed.  They will be reordered.\n\0"
/*  3775 */ "requires the option '%s'\n\0"
/*  3801 */ "requires these options:\n\0"
/*  3826 */ "   Arg Option-Name   Req?  Description\n\0"
/*  3866 */ "  Flg Arg Option-Name   Req?  Description\n\0"
/*  3909 */ "or you may use a numeric representation.  Preceding these with a '!'\n"
            "will clear the bits, specifying 'none' will clear all bits, and 'all'\n"
            "will set them all.  Multiple entries may be passed as an option\n"
            "argument list.\n\0"
/*  4128 */ "\t\t\t\t- may appear up to %d times\n\0"
/*  4161 */ "The valid \"%s\" option keywords are:\n\0"
/*  4198 */ "The next option supports vendor supported extra options:\0"
/*  4255 */ "These additional options are:";

/*
 *  Now, define (and initialize) the structure that contains
 *  the pointers to all these strings.
 *  Aren't you glad you don't maintain this by hand?
 */
usage_text_t option_xlateable_txt = {
  108,
  eng_zGnuBoolArg, eng_zGnuKeyArg,  eng_zGnuNumArg,  eng_zGnuStrArg,
    {
    option_lib_text +    0, option_lib_text +   31, option_lib_text +   83,
    option_lib_text +  129, option_lib_text +  228, option_lib_text +  264,
    option_lib_text +  314, option_lib_text +  405, option_lib_text +  427,
    option_lib_text +  484, option_lib_text +  519, option_lib_text +  564,
    option_lib_text +  596, option_lib_text +  634, option_lib_text +  667,
    option_lib_text +  716, option_lib_text +  748, option_lib_text +  800,
    option_lib_text +  837, option_lib_text +  862, option_lib_text +  900,
    option_lib_text +  918, option_lib_text + 1060, option_lib_text + 1107,
    option_lib_text + 1146, option_lib_text + 1159, option_lib_text + 1185,
    option_lib_text + 1211, option_lib_text + 1254, option_lib_text + 1290,
    option_lib_text + 1335, option_lib_text + 1364, option_lib_text + 1407,
    option_lib_text + 1490, option_lib_text + 1528, option_lib_text + 1574,
    option_lib_text + 1619, option_lib_text + 1646, option_lib_text + 1695,
    option_lib_text + 1744, option_lib_text + 1771, option_lib_text + 1804,
    option_lib_text + 1840, option_lib_text + 1890, option_lib_text + 1908,
    option_lib_text + 1962, option_lib_text + 2010, option_lib_text + 2057,
    option_lib_text + 2097, option_lib_text + 2132, option_lib_text + 2157,
    option_lib_text + 2173, option_lib_text + 2188, option_lib_text + 2194,
    option_lib_text + 2243, option_lib_text + 2288, option_lib_text + 2344,
    option_lib_text + 2373, option_lib_text + 2415, option_lib_text + 2457,
    option_lib_text + 2483, option_lib_text + 2498, option_lib_text + 2528,
    option_lib_text + 2554, option_lib_text + 2571, option_lib_text + 2618,
    option_lib_text + 2649, option_lib_text + 2676, option_lib_text + 2779,
    option_lib_text + 2885, option_lib_text + 2941, option_lib_text + 2975,
    option_lib_text + 3018, option_lib_text + 3085, option_lib_text + 3118,
    option_lib_text + 3143, option_lib_text + 3178, option_lib_text + 3216,
    option_lib_text + 3224, option_lib_text + 3272, option_lib_text + 3306,
    option_lib_text + 3325, option_lib_text + 3361, option_lib_text + 3397,
    option_lib_text + 3453, option_lib_text + 3479, option_lib_text + 3506,
    option_lib_text + 3519, option_lib_text + 3550, option_lib_text + 3564,
    option_lib_text + 3601, option_lib_text + 3629, option_lib_text + 3635,
    option_lib_text + 3681, option_lib_text + 3709, option_lib_text + 3775,
    option_lib_text + 3801, option_lib_text + 3826, option_lib_text + 3866,
    option_lib_text + 3909, option_lib_text + 4128, option_lib_text + 4161,
    option_lib_text + 4198, option_lib_text + 4255
  } };
#endif /* AUTOOPTS_INTERNAL */

#ifdef XGETTEXT_SCAN_DO_NOT_COMPILE
do not compile this section.
/* TRANSLATORS: The following dummy functions were crated solely so that
 * xgettext can extract the correct strings.  These strings are actually
 * referenced where the preceding "#line" directive states, though you will
 * not see the literal string there.  The literal string is defined above in
 * the @code{option_lib_text} table and referenced via a #define name that
 * redirects into the @code{option_xlateable_txt} structure above.  When
 * translating is activated, the pointers in @code{option_xlateable_txt} are
 * updated to point to translated strings.
 */
static void dummy_func(void) {
  /* LIBOPTS-MESSAGES: */
#line 67 "../autoopts.c"
  puts(_("allocation of %d bytes failed\n"));
#line 93 "../autoopts.c"
  puts(_("allocation of %d bytes failed\n"));
#line 53 "../init.c"
  puts(_("AutoOpts function called without option descriptor\n"));
#line 90 "../init.c"
  puts(_("\tThis exceeds the compiled library version:  "));
#line 88 "../init.c"
  puts(_("Automated Options Processing Error!\n"
       "\t%s called AutoOpts function with structure version %d:%d:%d.\n"));
#line 80 "../autoopts.c"
  puts(_("realloc of %d bytes at 0x%p failed\n"));
#line 92 "../init.c"
  puts(_("\tThis is less than the minimum library version:  "));
#line 121 "../version.c"
  puts(_("Automated Options version %s\n"
       "\tCopyright (C) 1999-2014 by Bruce Korb - all rights reserved\n"));
#line 82 "../makeshell.c"
  puts(_("(AutoOpts bug):  %s.\n"));
#line 90 "../reset.c"
  puts(_("optionResetOpt() called, but reset-option not configured"));
#line 292 "../usage.c"
  puts(_("could not locate the 'help' option"));
#line 336 "../autoopts.c"
  puts(_("optionProcess() was called with invalid data"));
#line 748 "../usage.c"
  puts(_("invalid argument type specified"));
#line 598 "../find.c"
  puts(_("defaulted to option with optional arg"));
#line 76 "../alias.c"
  puts(_("aliasing option is out of range."));
#line 234 "../enum.c"
  puts(_("%s error:  the keyword '%s' is ambiguous for %s\n"));
#line 108 "../find.c"
  puts(_("  The following options match:\n"));
#line 293 "../find.c"
  puts(_("%s: ambiguous option name: %s (matches %d options)\n"));
#line 161 "../check.c"
  puts(_("%s: Command line arguments required\n"));
#line 43 "../alias.c"
  puts(_("%d %s%s options allowed\n"));
#line 89 "../makeshell.c"
  puts(_("%s error %d (%s) calling %s for '%s'\n"));
#line 301 "../makeshell.c"
  puts(_("interprocess pipe"));
#line 168 "../version.c"
  puts(_("error: version option argument '%c' invalid.  Use:\n"
       "\t'v' - version only\n"
       "\t'c' - version and copyright\n"
       "\t'n' - version and full copyright notice\n"));
#line 58 "../check.c"
  puts(_("%s error:  the '%s' and '%s' options conflict\n"));
#line 217 "../find.c"
  puts(_("%s: The '%s' option has been disabled."));
#line 430 "../find.c"
  puts(_("%s: The '%s' option has been disabled."));
#line 38 "../alias.c"
  puts(_("-equivalence"));
#line 469 "../find.c"
  puts(_("%s: illegal option -- %c\n"));
#line 110 "../reset.c"
  puts(_("%s: illegal option -- %c\n"));
#line 271 "../find.c"
  puts(_("%s: illegal option -- %s\n"));
#line 755 "../find.c"
  puts(_("%s: illegal option -- %s\n"));
#line 118 "../reset.c"
  puts(_("%s: illegal option -- %s\n"));
#line 335 "../find.c"
  puts(_("%s: unknown vendor extension option -- %s\n"));
#line 159 "../enum.c"
  puts(_("  or an integer from %d through %d\n"));
#line 169 "../enum.c"
  puts(_("  or an integer from %d through %d\n"));
#line 747 "../usage.c"
  puts(_("%s error:  invalid option descriptor for %s\n"));
#line 1081 "../usage.c"
  puts(_("%s error:  invalid option descriptor for %s\n"));
#line 385 "../find.c"
  puts(_("%s: invalid option name: %s\n"));
#line 527 "../find.c"
  puts(_("%s: The '%s' option requires an argument.\n"));
#line 156 "../autoopts.c"
  puts(_("(AutoOpts bug):  Equivalenced option '%s' was equivalenced to both\n"
       "\t'%s' and '%s'."));
#line 94 "../check.c"
  puts(_("%s error:  The %s option is required\n"));
#line 632 "../find.c"
  puts(_("%s: The '%s' option cannot have an argument.\n"));
#line 151 "../check.c"
  puts(_("%s: Command line arguments are not allowed.\n"));
#line 535 "../save.c"
  puts(_("error %d (%s) creating %s\n"));
#line 234 "../enum.c"
  puts(_("%s error:  '%s' does not match any %s keywords.\n"));
#line 93 "../reset.c"
  puts(_("%s error: The '%s' option requires an argument.\n"));
#line 184 "../save.c"
  puts(_("error %d (%s) stat-ing %s\n"));
#line 238 "../save.c"
  puts(_("error %d (%s) stat-ing %s\n"));
#line 143 "../restore.c"
  puts(_("%s error: no saved option state\n"));
#line 231 "../autoopts.c"
  puts(_("'%s' is not a command line option.\n"));
#line 111 "../time.c"
  puts(_("%s error:  '%s' is not a recognizable date/time.\n"));
#line 132 "../save.c"
  puts(_("'%s' not defined\n"));
#line 50 "../time.c"
  puts(_("%s error:  '%s' is not a recognizable time duration.\n"));
#line 92 "../check.c"
  puts(_("%s error:  The %s option must appear %d times.\n"));
#line 164 "../numeric.c"
  puts(_("%s error:  '%s' is not a recognizable number.\n"));
#line 200 "../enum.c"
  puts(_("%s error:  %s exceeds %s keyword count\n"));
#line 330 "../usage.c"
  puts(_("Try '%s %s' for more information.\n"));
#line 45 "../alias.c"
  puts(_("one %s%s option allowed\n"));
#line 203 "../makeshell.c"
  puts(_("standard output"));
#line 938 "../makeshell.c"
  puts(_("standard output"));
#line 274 "../usage.c"
  puts(_("standard output"));
#line 415 "../usage.c"
  puts(_("standard output"));
#line 625 "../usage.c"
  puts(_("standard output"));
#line 175 "../version.c"
  puts(_("standard output"));
#line 274 "../usage.c"
  puts(_("standard error"));
#line 415 "../usage.c"
  puts(_("standard error"));
#line 625 "../usage.c"
  puts(_("standard error"));
#line 175 "../version.c"
  puts(_("standard error"));
#line 203 "../makeshell.c"
  puts(_("write"));
#line 938 "../makeshell.c"
  puts(_("write"));
#line 273 "../usage.c"
  puts(_("write"));
#line 414 "../usage.c"
  puts(_("write"));
#line 624 "../usage.c"
  puts(_("write"));
#line 174 "../version.c"
  puts(_("write"));
#line 60 "../numeric.c"
  puts(_("%s error:  %s option value %ld is out of range.\n"));
#line 44 "../check.c"
  puts(_("%s error:  %s option requires the %s option\n"));
#line 131 "../save.c"
  puts(_("%s warning:  cannot save options - %s not regular file\n"));
#line 183 "../save.c"
  puts(_("%s warning:  cannot save options - %s not regular file\n"));
#line 237 "../save.c"
  puts(_("%s warning:  cannot save options - %s not regular file\n"));
#line 256 "../save.c"
  puts(_("%s warning:  cannot save options - %s not regular file\n"));
#line 534 "../save.c"
  puts(_("%s warning:  cannot save options - %s not regular file\n"));
  /* END-LIBOPTS-MESSAGES */

  /* USAGE-TEXT: */
#line 873 "../usage.c"
  puts(_("\t\t\t\t- an alternate for '%s'\n"));
#line 1148 "../usage.c"
  puts(_("Version, usage and configuration options:"));
#line 924 "../usage.c"
  puts(_("\t\t\t\t- default option for unnamed options\n"));
#line 837 "../usage.c"
  puts(_("\t\t\t\t- disabled as '--%s'\n"));
#line 1117 "../usage.c"
  puts(_(" --- %-14s %s\n"));
#line 1115 "../usage.c"
  puts(_("This option has been disabled"));
#line 864 "../usage.c"
  puts(_("\t\t\t\t- enabled by default\n"));
#line 40 "../alias.c"
  puts(_("%s error:  only "));
#line 1194 "../usage.c"
  puts(_(" - examining environment variables named %s_*\n"));
#line 168 "../file.c"
  puts(_("\t\t\t\t- file must not pre-exist\n"));
#line 172 "../file.c"
  puts(_("\t\t\t\t- file must pre-exist\n"));
#line 380 "../usage.c"
  puts(_("Options are specified by doubled hyphens and their name or by a single\n"
       "hyphen and the flag character.\n"));
#line 916 "../makeshell.c"
  puts(_("\n"
       "= = = = = = = =\n\n"
       "This incarnation of genshell will produce\n"
       "a shell script to parse the options for %s:\n\n"));
#line 166 "../enum.c"
  puts(_("  or an integer mask with any of the lower %d bits set\n"));
#line 897 "../usage.c"
  puts(_("\t\t\t\t- is a set membership option\n"));
#line 918 "../usage.c"
  puts(_("\t\t\t\t- must appear between %d and %d times\n"));
#line 382 "../usage.c"
  puts(_("Options are specified by single or double hyphens and their name.\n"));
#line 904 "../usage.c"
  puts(_("\t\t\t\t- may appear multiple times\n"));
#line 891 "../usage.c"
  puts(_("\t\t\t\t- may not be preset\n"));
#line 1309 "../usage.c"
  puts(_("   Arg Option-Name    Description\n"));
#line 1245 "../usage.c"
  puts(_("  Flg Arg Option-Name    Description\n"));
#line 1303 "../usage.c"
  puts(_("  Flg Arg Option-Name    Description\n"));
#line 1304 "../usage.c"
  puts(_(" %3s %s"));
#line 1310 "../usage.c"
  puts(_(" %3s %s"));
#line 387 "../usage.c"
  puts(_("The '-#<number>' option may omit the hash char\n"));
#line 383 "../usage.c"
  puts(_("All arguments are named options.\n"));
#line 971 "../usage.c"
  puts(_(" - reading file %s"));
#line 409 "../usage.c"
  puts(_("\n"
       "Please send bug reports to:  <%s>\n"));
#line 100 "../version.c"
  puts(_("\n"
       "Please send bug reports to:  <%s>\n"));
#line 129 "../version.c"
  puts(_("\n"
       "Please send bug reports to:  <%s>\n"));
#line 903 "../usage.c"
  puts(_("\t\t\t\t- may NOT appear - preset only\n"));
#line 944 "../usage.c"
  puts(_("\n"
       "The following option preset mechanisms are supported:\n"));
#line 1192 "../usage.c"
  puts(_("\n"
       "The following option preset mechanisms are supported:\n"));
#line 682 "../usage.c"
  puts(_("prohibits these options:\n"));
#line 677 "../usage.c"
  puts(_("prohibits the option '%s'\n"));
#line 81 "../numeric.c"
  puts(_("%s%ld to %ld"));
#line 79 "../numeric.c"
  puts(_("%sgreater than or equal to %ld"));
#line 75 "../numeric.c"
  puts(_("%s%ld exactly"));
#line 68 "../numeric.c"
  puts(_("%sit must lie in one of the ranges:\n"));
#line 68 "../numeric.c"
  puts(_("%sit must be in the range:\n"));
#line 88 "../numeric.c"
  puts(_(", or\n"));
#line 66 "../numeric.c"
  puts(_("%sis scalable with a suffix: k/K/m/M/g/G/t/T\n"));
#line 77 "../numeric.c"
  puts(_("%sless than or equal to %ld"));
#line 390 "../usage.c"
  puts(_("Operands and options may be intermixed.  They will be reordered.\n"));
#line 652 "../usage.c"
  puts(_("requires the option '%s'\n"));
#line 655 "../usage.c"
  puts(_("requires these options:\n"));
#line 1321 "../usage.c"
  puts(_("   Arg Option-Name   Req?  Description\n"));
#line 1315 "../usage.c"
  puts(_("  Flg Arg Option-Name   Req?  Description\n"));
#line 167 "../enum.c"
  puts(_("or you may use a numeric representation.  Preceding these with a '!'\n"
       "will clear the bits, specifying 'none' will clear all bits, and 'all'\n"
       "will set them all.  Multiple entries may be passed as an option\n"
       "argument list.\n"));
#line 910 "../usage.c"
  puts(_("\t\t\t\t- may appear up to %d times\n"));
#line 77 "../enum.c"
  puts(_("The valid \"%s\" option keywords are:\n"));
#line 1152 "../usage.c"
  puts(_("The next option supports vendor supported extra options:"));
#line 773 "../usage.c"
  puts(_("These additional options are:"));
  /* END-USAGE-TEXT */
}
#endif /* XGETTEXT_SCAN_DO_NOT_COMPILE */
#endif /* AUTOOPTS_USAGE_TXT_H_GUARD */
