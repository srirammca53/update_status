#ifndef JUDGE_JCODE_H
#define JUDGE_JCODE_H
#define	JP_EUC		'E'	/* EUC */
#define	JP_JIS		'J'	/* JIS */
#define	JP_SJIS		'S'	/* Shift-JIS */
#define JP_WIDE		'U'	/* UNICODE */
#define JP_UTF8		'T'	/* UTF-8 */

int judge_jcode(
    unsigned char * origcode,
    int * ubig,
    const unsigned char * ptr,
    long size);
#endif

