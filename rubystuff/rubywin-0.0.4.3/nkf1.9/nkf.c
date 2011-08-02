/** Network Kanji Filter. (PDS Version)
************************************************************************
** Copyright (C) 1987, Fujitsu LTD. (Itaru ICHIKAWA)
** $BO"Mm@h!'(B $B!J3t!KIY;NDL8&5f=j!!%=%U%H#38&!!;T@n!!;j(B 
** $B!J(BE-Mail Address: ichikawa@flab.fujitsu.co.jp$B!K(B
** Copyright (C) 1996,1998
** $BO"Mm@h!'(B $BN05eBg3X>pJs9)3X2J(B $B2OLn(B $B??<#(B  mine/X0208 support
** $B!J(BE-Mail Address: kono@ie.u-ryukyu.ac.jp$B!K(B
** $BO"Mm@h!'(B COW for DOS & Win16 & Win32 & OS/2
** $B!J(BE-Mail Address: GHG00637@niftyserve.or.p$B!K(B
**    $B$3$N%=!<%9$N$$$+$J$kJ#<L!$2~JQ!$=$@5$b5vBz$7$^$9!#$?$@$7!"(B
**    $B$=$N:]$K$O!"C/$,9W8%$7$?$r<($9$3$NItJ,$r;D$9$3$H!#(B
**    $B:FG[I[$d;(;o$NIUO?$J$I$NLd$$9g$o$;$bI,MW$"$j$^$;$s!#(B
**    $B%P%$%J%j$NG[I[$N:]$K$O(Bversion message$B$rJ]B8$9$k$3$H$r>r7o$H$7$^$9!#(B
**    $B$3$N%W%m%0%i%`$K$D$$$F$OFC$K2?$NJ]>Z$b$7$J$$!"0-$7$+$i$:!#(B
**    Everyone is permitted to do anything on this program 
**    including copying, modifying, improving,
**    as long as you don't try to pretend that you wrote it.
**    i.e., the above copyright notice has to appear in all copies.
**    Binary distribution requires original version messages.
**    You don't have to ask before copying, redistribution or publishing.
**    THE AUTHOR DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE.
***********************************************************************/

static char *CopyRight =
      "Copyright (C) 1987, FUJITSU LTD. (I.Ichikawa),2000 S. Kono, COW";
static char *Version =
      "1.9";
static char *Patchlevel =
      "2/0002/Shinji Kono";

/*
**
**
**
** USAGE:       nkf [flags] [file] 
**
** Flags:
** b    Output is bufferred             (DEFAULT)
** u    Output is unbufferred
**
** t    no operation
**
** j    Outout code is JIS 7 bit        (DEFAULT SELECT) 
** s    Output code is MS Kanji         (DEFAULT SELECT) 
** e    Output code is AT&T JIS         (DEFAULT SELECT) 
** l    Output code is JIS 7bit and ISO8859-1 Latin-1
**
** m    MIME conversion for ISO-2022-JP
** i_ Output sequence to designate JIS-kanji (DEFAULT_J)
** o_ Output sequence to designate single-byte roman characters (DEFAULT_R)
** M    MIME output conversion 
**
** r  {de/en}crypt ROT13/47
**
** v  display Version
**
** T  Text mode output        (for MS-DOS)
**
** x    Do not convert X0201 kana into X0208
** Z    Convert X0208 alphabet to ASCII
**
** f60  fold option
**
** m    MIME decode
** B    try to fix broken JIS, missing Escape
** B[1-9]  broken level
**
** O   Output to 'nkf.out' file 
** d   Delete \r in line feed 
** c   Add \r in line feed 
** -- other long option
**
**/
/******************************/
/* $B%G%U%)%k%H$N=PNO%3!<%IA*Br(B */
/* Select DEFAULT_CODE */
#define DEFAULT_CODE_JIS
/* #define DEFAULT_CODE_SJIS */
/* #define DEFAULT_CODE_EUC */
/******************************/

#if (defined(__TURBOC__) || defined(LSI_C)) && !defined(MSDOS)
#define MSDOS
#endif

#ifndef PERL_XS
#include <stdio.h>
#endif

#if defined(MSDOS) || defined(__OS2__) 
#include <stdlib.h>
#include <fcntl.h>
#include <io.h>
#endif

#ifdef MSDOS
#ifdef LSI_C
#define setbinmode(fp) fsetbin(fp)
#else /* Microsoft C, Turbo C */
#define setbinmode(fp) setmode(fileno(fp), O_BINARY)
#endif
#else /* UNIX,OS/2 */
#define setbinmode(fp)
#endif

#ifdef _IOFBF /* SysV and MSDOS */
#define       setvbuffer(fp, buf, size)       setvbuf(fp, buf, _IOFBF, size)
#else /* BSD */
#define       setvbuffer(fp, buf, size)       setbuffer(fp, buf, size)
#endif

/*Borland C++ 4.5 EasyWin*/
#if defined(__TURBOC__) && defined(_Windows) && !defined(__WIN32__) /*Easy Win */
#define         EASYWIN
#include <windows.h>
#endif

#define         FALSE   0
#define         TRUE    1

/* state of output_mode and input_mode  

   c2           0 means ASCII
                X0201
                ISO8859_1
                X0208
                EOF      all termination
   c1           32bit data

 */

#define         ASCII           0
#define         X0208           1
#define         X0201           2
#define         ISO8859_1       8
#define         NO_X0201        3

/* Input Assumption */

#define         JIS_INPUT       4
#define         SJIS_INPUT      5
#define         LATIN1_INPUT    6
#define         FIXED_MIME      7
#define         STRICT_MIME     8

/* MIME ENCODE */

#define        	ISO2022JP       9
#define  	JAPANESE_EUC   10
#define		SHIFT_JIS      11

/* ASCII CODE */

#define         BS      0x08
#define         NL      0x0a
#define         CR      0x0d
#define         ESC     0x1b
#define         SPACE   0x20
#define         AT      0x40
#define         SSP     0xa0
#define         DEL     0x7f
#define         SI      0x0f
#define         SO      0x0e
#define         SSO     0x8e

#define		is_alnum(c)  \
            (('a'<=c && c<='z')||('A'<= c && c<='Z')||('0'<=c && c<='9'))

#define         HOLD_SIZE       32
#define         IOBUF_SIZE      16384

#define         DEFAULT_J       'B'
#define         DEFAULT_R       'B'

#define         SJ0162  0x00e1          /* 01 - 62 ku offset */
#define         SJ6394  0x0161          /* 63 - 94 ku offset */


/* MIME preprocessor */


#ifdef EASYWIN /*Easy Win */
extern POINT _BufferSize;
#endif

/*      function prototype  */

/* #define PROTO(x)  () */
#define PROTO(x)  x 
static  int     noconvert PROTO((FILE *f));
static  int     kanji_convert PROTO((FILE *f));
static  int     h_conv PROTO((FILE *f,int c2,int c1));
static  int     push_hold_buf PROTO((int c2,int c1));
static  void    s_iconv PROTO((int c2,int c1));
static  void    e_iconv PROTO((int c2,int c1));
static  void    e_oconv PROTO((int c2,int c1));
static  void    s_oconv PROTO((int c2,int c1));
static  void    j_oconv PROTO((int c2,int c1));
static  void    fold_conv PROTO((int c2,int c1));
static  void    cr_conv PROTO((int c2,int c1));
static  void    z_conv PROTO((int c2,int c1));
static  void    rot_conv PROTO((int c2,int c1));
static  void    base64_conv PROTO((int c2,int c1));
static  void    no_connection PROTO((int c2,int c1));

static  void    std_putc PROTO((int c));
static  int     std_getc PROTO((FILE *f));
static  int     std_ungetc PROTO((int c,FILE *f));

static  int     broken_getc PROTO((FILE *f));
static  int     broken_ungetc PROTO((int c,FILE *f));

static  int     mime_begin PROTO((FILE *f));
static  int     mime_getc PROTO((FILE *f));
static  int     mime_ungetc PROTO((int c,FILE *f));

static  int     mime_begin_strict PROTO((FILE *f));
static  int     mime_getc_buf PROTO((FILE *f));
static  int     mime_ungetc_buf  PROTO((int c,FILE *f));
static  int     mime_integrity PROTO((FILE *f,unsigned char *p));

static  int     base64decode PROTO((int c));
static  void    mime_putc PROTO((int c));
static  void    open_mime PROTO((int c));
static  void    close_mime PROTO(());
static  void    usage PROTO(());
static  void    version PROTO(());
static  void    options PROTO((unsigned char *c));
#ifdef PERL_XS
static  void    reinit PROTO(());
#endif

/* buffers */

static unsigned char   stdibuf[IOBUF_SIZE];
static unsigned char   stdobuf[IOBUF_SIZE];
static unsigned char   hold_buf[HOLD_SIZE*2];
static int             hold_count;

/* MIME preprocessor fifo */

#define MIME_BUF_SIZE   (1024)    /* 2^n ring buffer */
#define MIME_BUF_MASK   (MIME_BUF_SIZE-1)   
#define Fifo(n)         mime_buf[(n)&MIME_BUF_MASK]
static unsigned char           mime_buf[MIME_BUF_SIZE];
static unsigned int            mime_top = 0;
static unsigned int            mime_last = 0;  /* decoded */
static unsigned int            mime_input = 0; /* undecoded */

/* flags */
static int             unbuf_f = FALSE;
static int             estab_f = FALSE;
static int             nop_f = FALSE;
static int             binmode_f = TRUE;       /* binary mode */
static int             rot_f = FALSE;          /* rot14/43 mode */
static int             input_f = FALSE;        /* non fixed input code  */
static int             alpha_f = FALSE;        /* convert JIx0208 alphbet to ASCII */
static int             mime_f = STRICT_MIME;   /* convert MIME B base64 or Q */
static int             mimebuf_f = FALSE;      /* MIME buffered input */
static int             broken_f = FALSE;       /* convert ESC-less broken JIS */
static int             iso8859_f = FALSE;      /* ISO8859 through */
static int             mimeout_f = FALSE;       /* base64 mode */
#if defined(MSDOS) || defined(__OS2__) 
static int             x0201_f = TRUE;         /* Assume JISX0201 kana */
#else
static int             x0201_f = NO_X0201;     /* Assume NO JISX0201 */
#endif

static int              mimeout_mode = 0;
static int              base64_count = 0;

/* X0208 -> ASCII converter */

/* fold parameter */
static int f_line = 0;    /* chars in line */
static int f_prev = 0;
static int             fold_f  = FALSE;
static int             fold_len  = 0;

/* options */
static unsigned char   kanji_intro = DEFAULT_J,
                       ascii_intro = DEFAULT_R;

/* Folding */

#define FOLD_MARGIN  10
#define DEFAULT_FOLD 60

/* converters */

#ifdef DEFAULT_CODE_JIS
#   define  DEFAULT_CONV j_oconv
#endif
#ifdef DEFAULT_CODE_SJIS
#   define  DEFAULT_CONV s_oconv
#endif
#ifdef DEFAULT_CODE_EUC
#   define  DEFAULT_CONV e_oconv
#endif

/* process default */
static void (*output_conv)PROTO((int c2,int c1)) = DEFAULT_CONV;   

static void (*oconv)PROTO((int c2,int c1)) = no_connection; 
/* s_iconv or oconv */
static void (*iconv)PROTO((int c2,int c1)) = no_connection;   

static void (*o_zconv)PROTO((int c2,int c1)) = no_connection; 
static void (*o_fconv)PROTO((int c2,int c1)) = no_connection; 
static void (*o_crconv)PROTO((int c2,int c1)) = no_connection; 
static void (*o_rot_conv)PROTO((int c2,int c1)) = no_connection; 
static void (*o_base64conv)PROTO((int c2,int c1)) = no_connection;

/* static redirections */

static  void   (*o_putc)PROTO((int c)) = std_putc;

static  int    (*i_getc)PROTO((FILE *f)) = std_getc; /* general input */
static  int    (*i_ungetc)PROTO((int c,FILE *f)) =std_ungetc;

static  int    (*i_bgetc)PROTO((FILE *)) = std_getc; /* input of mgetc */
static  int    (*i_bungetc)PROTO((int c ,FILE *f)) = std_ungetc;

static  void   (*o_mputc)PROTO((int c)) = std_putc ; /* output of mputc */

static  int    (*i_mgetc)PROTO((FILE *)) = std_getc; /* input of mgetc */
static  int    (*i_mungetc)PROTO((int c ,FILE *f)) = std_ungetc;

/* for strict mime */
static  int    (*i_mgetc_buf)PROTO((FILE *)) = std_getc; /* input of mgetc_buf */
static  int    (*i_mungetc_buf)PROTO((int c,FILE *f)) = std_ungetc;

/* Global states */
static int output_mode = ASCII,    /* output kanji mode */
           input_mode =  ASCII,    /* input kanji mode */
           shift_mode =  FALSE;    /* TRUE shift out, or X0201  */
static int mime_decode_mode =   FALSE;    /* MIME mode B base64, Q hex */

/* X0201 / X0208 conversion tables */

/* X0201 kana conversion table */
/* 90-9F A0-DF */
static
unsigned char cv[]= {
    0x21,0x21,0x21,0x23,0x21,0x56,0x21,0x57,
    0x21,0x22,0x21,0x26,0x25,0x72,0x25,0x21,
    0x25,0x23,0x25,0x25,0x25,0x27,0x25,0x29,
    0x25,0x63,0x25,0x65,0x25,0x67,0x25,0x43,
    0x21,0x3c,0x25,0x22,0x25,0x24,0x25,0x26,
    0x25,0x28,0x25,0x2a,0x25,0x2b,0x25,0x2d,
    0x25,0x2f,0x25,0x31,0x25,0x33,0x25,0x35,
    0x25,0x37,0x25,0x39,0x25,0x3b,0x25,0x3d,
    0x25,0x3f,0x25,0x41,0x25,0x44,0x25,0x46,
    0x25,0x48,0x25,0x4a,0x25,0x4b,0x25,0x4c,
    0x25,0x4d,0x25,0x4e,0x25,0x4f,0x25,0x52,
    0x25,0x55,0x25,0x58,0x25,0x5b,0x25,0x5e,
    0x25,0x5f,0x25,0x60,0x25,0x61,0x25,0x62,
    0x25,0x64,0x25,0x66,0x25,0x68,0x25,0x69,
    0x25,0x6a,0x25,0x6b,0x25,0x6c,0x25,0x6d,
    0x25,0x6f,0x25,0x73,0x21,0x2b,0x21,0x2c,
    0x00,0x00};


/* X0201 kana conversion table for daguten */
/* 90-9F A0-DF */
static
unsigned char dv[]= { 
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x25,0x74,
    0x00,0x00,0x00,0x00,0x25,0x2c,0x25,0x2e,
    0x25,0x30,0x25,0x32,0x25,0x34,0x25,0x36,
    0x25,0x38,0x25,0x3a,0x25,0x3c,0x25,0x3e,
    0x25,0x40,0x25,0x42,0x25,0x45,0x25,0x47,
    0x25,0x49,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x25,0x50,0x25,0x53,
    0x25,0x56,0x25,0x59,0x25,0x5c,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00};

/* X0201 kana conversion table for han-daguten */
/* 90-9F A0-DF */
static
unsigned char ev[]= { 
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x25,0x51,0x25,0x54,
    0x25,0x57,0x25,0x5a,0x25,0x5d,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00};


/* X0208 kigou conversion table */
/* 0x8140 - 0x819e */
static
unsigned char fv[] = {

    0x00,0x00,0x00,0x00,0x2c,0x2e,0x00,0x3a,
    0x3b,0x3f,0x21,0x00,0x00,0x27,0x60,0x00,
    0x5e,0x00,0x5f,0x00,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x2d,0x00,0x2f,
    0x5c,0x00,0x00,0x7c,0x00,0x00,0x60,0x27,
    0x22,0x22,0x28,0x29,0x00,0x00,0x5b,0x5d,
    0x7b,0x7d,0x3c,0x3e,0x00,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x2b,0x2d,0x00,0x00,
    0x00,0x3d,0x00,0x3c,0x3e,0x00,0x00,0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    0x24,0x00,0x00,0x25,0x23,0x26,0x2a,0x40,
    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
} ;


#define    CRLF      1

static int             file_out = FALSE;
static int             crmode_f = 0;   /* CR, NL, CRLF */
#ifdef EASYWIN /*Easy Win */
static int             end_check;
#endif /*Easy Win */

#ifndef PERL_XS
int
main(argc, argv)
    int             argc;
    char          **argv;
{
    FILE  *fin;
    unsigned char  *cp;

#ifdef EASYWIN /*Easy Win */
    _BufferSize.y = 400;/*Set Scroll Buffer Size*/
#endif

    for (argc--,argv++; (argc > 0) && **argv == '-'; argc--, argv++) {
        cp = *argv;
        options(cp);
    }

    if (binmode_f == TRUE)
#ifdef __OS2__
    if (freopen("","wb",stdout) == NULL) 
        return (-1);
#else
    setbinmode(stdout);
#endif

    if (unbuf_f)
      setbuf(stdout, (char *) NULL);
    else
      setvbuffer(stdout, stdobuf, IOBUF_SIZE);

    if (argc == 0) {
      if (binmode_f == TRUE)
#ifdef __OS2__
      if (freopen("","rb",stdin) == NULL) return (-1);
#else
      setbinmode(stdin);
#endif
      setvbuffer(stdin, stdibuf, IOBUF_SIZE);
      if (nop_f)
          noconvert(stdin);
      else
          kanji_convert(stdin);
    } else {
      while (argc--) {
          if ((fin = fopen(*argv++, "r")) == NULL) {
              perror(*--argv);
              return(-1);
          } else {
/* reopen file for stdout */
              if (file_out == TRUE){ 
                  if (argc == 1 ) {
                      if (freopen(*argv++, "w", stdout) == NULL) {
                          perror(*--argv);
                          return (-1);
                      }
                      argc--;
                  } else {
                      if (freopen("nkf.out", "w", stdout) == NULL) {
                         perror(*--argv);
                         return (-1);
                      }
                  }
                  if (binmode_f == TRUE) {
#ifdef __OS2__
                      if (freopen("","wb",stdout) == NULL) 
                           return (-1);
#else
                      setbinmode(stdout);
#endif
                  }
              }
              if (binmode_f == TRUE)
#ifdef __OS2__
                 if (freopen("","rb",fin) == NULL) 
                    return (-1);
#else
                 setbinmode(fin);
#endif 
              setvbuffer(fin, stdibuf, IOBUF_SIZE);
              if (nop_f)
                  noconvert(fin);
              else
                  kanji_convert(fin);
              fclose(fin);
          }
      }
    }
#ifdef EASYWIN /*Easy Win */
    if (file_out == FALSE) 
        scanf("%d",&end_check);
    else 
        fclose(stdout);
#else /* for Other OS */
    if (file_out == TRUE) 
        fclose(stdout);
#endif 
    return (0);
}
#endif

static 
struct {
    unsigned char *name;
    unsigned char *alias;
} long_option[] = {
    {"base64","jMB"},
    {"euc","e"},
    {"euc-input","E"},
    {"fj","jm"},
    {"help","v"},
    {"jis","j"},
    {"jis-input","J"},
    {"mac","sLm"},
    {"mime","jM"},
    {"mime-input","m"},
    {"msdos","sLw"},
    {"sjis","s"},
    {"sjis-input","S"},
    {"unix","eLu"},
    {"version","V"},
    {"windows","sLw"},
};

static option_mode;

void
options(unsigned char *cp) 
{
    int i;
    unsigned char *p;

    if (option_mode==1)
	return;
    if (*cp++ != '-') 
	return;
    while (*cp) {
        switch (*cp++) {
        case '-':  /* literal options */
	    if (!*cp) {        /* ignore the rest of arguments */
		option_mode = 1;
		return;
	    }
            for (i=0;i<sizeof(long_option)/sizeof(long_option[0]);i++) {
		int j;
                p = long_option[i].name;
                for (j=0;*p && *p++ == cp[j];j++);
                if (! *p) break;
            }
	    if (*p) return;
            cp = long_option[i].alias;
            continue;
        case 'b':           /* buffered mode */
            unbuf_f = FALSE;
            continue;
        case 'u':           /* non bufferd mode */
            unbuf_f = TRUE;
            continue;
        case 't':           /* transparent mode */
            nop_f = TRUE;
            continue;
        case 'j':           /* JIS output */
        case 'n':
            output_conv = j_oconv;
            continue;
        case 'e':           /* AT&T EUC output */
            output_conv = e_oconv;
            continue;
        case 's':           /* SJIS output */
            output_conv = s_oconv;
            continue;
        case 'l':           /* ISO8859 Latin-1 support, no conversion */
            iso8859_f = TRUE;  /* Only compatible with ISO-2022-JP */
            input_f = LATIN1_INPUT;
            continue;
        case 'i':           /* Kanji IN ESC-$-@/B */
            if (*cp=='@'||*cp=='B') 
                kanji_intro = *cp++;
            continue;
        case 'o':           /* ASCII IN ESC-(-J/B */
            if (*cp=='J'||*cp=='B'||*cp=='H') 
                ascii_intro = *cp++;
            continue;
        case 'r':
            rot_f = TRUE;
            continue;
#if defined(MSDOS) || defined(__OS2__) 
        case 'T':
            binmode_f = FALSE;
            continue;
#endif
#ifndef PERL_XS
        case 'V':
            version();
            exit(1);
            break;
        case 'v':
            usage();
            exit(1);
            break;
#endif
        /* Input code assumption */
        case 'J':   /* JIS input */
        case 'E':   /* AT&T EUC input */
            input_f = JIS_INPUT;
            continue;
        case 'S':   /* MS Kanji input */
            input_f = SJIS_INPUT;
            if (x0201_f==NO_X0201) x0201_f=TRUE;
            continue;
        case 'Z':   /* Convert X0208 alphabet to asii */
            /*  bit:0   Convert X0208
                bit:1   Convert Kankaku to one space
                bit:2   Convert Kankaku to two spaces
            */
            if ('9'>= *cp && *cp>='0') 
                alpha_f |= 1<<(*cp++ -'0');
            else 
                alpha_f |= TRUE;
            continue;
        case 'x':   /* Convert X0201 kana to X0208 or X0201 Conversion */
            x0201_f = FALSE;    /* No X0201->X0208 conversion */
            /* accept  X0201
                    ESC-(-I     in JIS, EUC, MS Kanji
                    SI/SO       in JIS, EUC, MS Kanji
                    SSO         in EUC, JIS, not in MS Kanji
                    MS Kanji (0xa0-0xdf) 
               output  X0201
                    ESC-(-I     in JIS (0x20-0x5f)
                    SSO         in EUC (0xa0-0xdf)
                    0xa0-0xd    in MS Kanji (0xa0-0xdf) 
            */
            continue;
        case 'X':   /* Assume X0201 kana */
            /* Default value is NO_X0201 for EUC/MS-Kanji mix */
            x0201_f = TRUE;
            continue;
        case 'f':   /* folding -f60 or -f */
            fold_f = TRUE;
            fold_len = 0;
            while('0'<= *cp && *cp <='9') {
		fold_len *= 10;
		fold_len += *cp++ - '0';
	    }
            if (!(0<fold_len && fold_len<BUFSIZ)) 
                fold_len = DEFAULT_FOLD;
            continue;
        case 'm':   /* MIME support */
            if (*cp=='B'||*cp=='Q') {
                mime_decode_mode = *cp++;
                mimebuf_f = FIXED_MIME;
            } else if (*cp=='N') {
                mime_f = TRUE; cp++;
            } else if (*cp=='S') {
                mime_f = STRICT_MIME; cp++;
            } else if (*cp=='0') {
                mime_f = FALSE;
            }
            continue;
        case 'M':   /* MIME output */
            if (*cp=='B') {
                mimeout_mode = 'B';
                mimeout_f = FIXED_MIME; cp++;
            } else if (*cp=='Q') {
                mimeout_mode = 'Q';
                mimeout_f = FIXED_MIME; cp++;
            } else {
		mimeout_f = TRUE;
	    }
            continue;
        case 'B':   /* Broken JIS support */
            /*  bit:0   no ESC JIS
                bit:1   allow any x on ESC-(-x or ESC-$-x
                bit:2   reset to ascii on NL
            */
            if ('9'>= *cp && *cp>='0') 
                broken_f |= 1<<(*cp++ -'0');
            else 
                broken_f |= TRUE;
            continue;
#ifndef PERL_XS
        case 'O':/* for Output file */
            file_out = TRUE;
            continue;
#endif
        case 'c':/* add cr code */
            crmode_f = CRLF;
            continue;
        case 'd':/* delete cr code */
            crmode_f = NL;
            continue;
        case 'L':  /* line mode */
            if (*cp=='u') {         /* unix */
                crmode_f = NL;
            } else if (*cp=='m') { /* mac */
                crmode_f = CR;
            } else if (*cp=='w') { /* windows */
                crmode_f = CRLF;
            } else if (*cp=='0') { /* no conversion  */
                crmode_f = 0;
            }
            continue;
        default:
            /* bogus option but ignored */
            continue;
        }
    }
}

int 
std_getc(f)
FILE *f;
{
    return getc(f);
}

int 
std_ungetc(c,f)
int c;
FILE *f;
{
    return ungetc(c,f);
}

void 
std_putc(c)
int c;
{
    putchar(c);
}

int
noconvert(f)
    FILE  *f;
{
    int    c;

    while ((c = (*i_getc)(f)) != EOF)
      (*o_putc)(c);
    return 1;
}


void
module_connection()
{
    oconv = output_conv; 
    o_putc = std_putc;

    /* replace continucation module, from output side */

    /* output redicrection */
    if (mimeout_f) {
	o_mputc = o_putc;
	o_putc = mime_putc;
	if (mimeout_f == TRUE) {
	    o_base64conv = oconv; oconv = base64_conv;
	}
	/* base64_count = 0; */
    }

    if (crmode_f) {
	o_crconv = oconv; oconv = cr_conv;
    }
    if (rot_f) {
	o_rot_conv = oconv; oconv = rot_conv;
    }
    if (fold_f) {
	o_fconv = oconv; oconv = fold_conv;
	f_line = 0;
    }
    if (alpha_f || x0201_f) {
	o_zconv = oconv; oconv = z_conv;
    }

    i_getc = std_getc;
    /* input redicrection */
    if (mime_f && mimebuf_f==FIXED_MIME) {
	i_mgetc = i_getc; i_getc = mime_getc;
	i_mungetc = i_ungetc; i_ungetc = mime_ungetc;
    }
    if (broken_f & 1) {
	i_bgetc = i_getc; i_getc = broken_getc;
	i_bungetc = i_ungetc; i_ungetc = broken_ungetc;
    }
    if (input_f == JIS_INPUT || input_f == LATIN1_INPUT) {
        estab_f = TRUE; iconv = e_iconv;
    } else if (input_f == SJIS_INPUT) {
        estab_f = TRUE;  iconv = s_iconv;
    } else {
        estab_f = FALSE; iconv = e_iconv;
    }

}

/*
   Conversion main loop. Code detection only. 
 */

int
kanji_convert(f)
    FILE  *f;
{
    int    c1,
                    c2;

    module_connection();
    c2 = 0;


    input_mode = ASCII;
    output_mode = ASCII;
    shift_mode = FALSE;

#define NEXT continue      /* no output, get next */
#define SEND ;             /* output c1 and c2, get next */
#define LAST break         /* end of loop, go closing  */

    while ((c1 = (*i_getc)(f)) != EOF) {
        if (c2) {
            /* second byte */
            if (c2 > DEL) {
                /* in case of 8th bit is on */
                if (!estab_f) {
                    /* in case of not established yet */
                    if (c1 > SSP) {
                        /* It is still ambiguious */
                        if (h_conv(f, c2, c1)==EOF) 
                            LAST;
                        else 
                            c2 = 0;
                        NEXT;
                    } else if (c1 < AT) {
                        /* ignore bogus code */
                        c2 = 0;
                        NEXT;
                    } else {
                        /* established */
                        /* it seems to be MS Kanji */
                        estab_f = TRUE;
                        iconv = s_iconv;
                        SEND;
                    }
                } else
                    /* in case of already established */
                    if (c1 < AT) {
                        /* ignore bogus code */
                        c2 = 0;
                        NEXT;
                    } else
                        SEND;
            } else
                /* second byte, 7 bit code */
                /* it might be kanji shitfted */
                if ((c1 == DEL) || (c1 <= SPACE)) {
                    /* ignore bogus first code */
                    c2 = 0;
                    NEXT;
                } else
                    SEND;
        } else {
            /* first byte */
            if (c1 > DEL) {
                /* 8 bit code */
                if (!estab_f && !iso8859_f) {
                    /* not established yet */
                    if (c1 < SSP) {
                        /* it seems to be MS Kanji */
                        estab_f = TRUE;
                        iconv = s_iconv;
                    } else if (c1 < 0xe0) {
                        /* it seems to be EUC */
                        estab_f = TRUE;
                        iconv = e_iconv;
                    } else {
                        /* still ambiguious */
                    }
                    c2 = c1;
                    NEXT;
                } else { /* estab_f==TRUE */
                    if (iso8859_f) {
                        c2 = ISO8859_1;
                        c1 &= 0x7f;
                        SEND;
                    } else if (SSP<=c1 && c1<0xe0 && iconv == s_iconv) {
                        /* SJIS X0201 Case... */
                        c2 = X0201;
                        c1 &= 0x7f;
                        SEND;
                    } else if (c1==SSO && iconv != s_iconv) {
                        /* EUC X0201 Case */
                        c1 = (*i_getc)(f);  /* skip SSO */
                        if (SSP<=c1 && c1<0xe0) {
                            c2 = X0201;
                            c1 &= 0x7f;
                            SEND;
                        } else  { /* bogus code, skip SSO and one byte */
                            NEXT;
                        }
                    } else if (c1 < SSP && iconv != s_iconv) {
                        /* strange code in EUC */
                        iconv = s_iconv;  /* try SJIS */
                        c2 = c1;
                        NEXT;
                    } else {
                       /* already established */
                       c2 = c1;
                       NEXT;
                    }
                }
            } else if ((c1 > SPACE) && (c1 != DEL)) {
                /* in case of Roman characters */
                if (shift_mode) { 
                    /* output 1 shifted byte */
                    if (iso8859_f) {
                        c2 = ISO8859_1;
                        SEND;
                    } else if (SPACE<=c1 && c1<(0xe0&0x7f) ){
                        c2 = X0201;
                        SEND;
                    } else {
                        /* look like bogus code */
                        NEXT;
                    }
                } else if (input_mode == X0208) {
                    /* in case of Kanji shifted */
                    c2 = c1;
                    NEXT;
                } else if (c1 == '=' && mime_f && !mime_decode_mode ) {
                    /* Check MIME code */
                    if ((c1 = (*i_getc)(f)) == EOF) {
                        (*oconv)(0, '=');
                        LAST;
                    } else if (c1 == '?') {
                        /* =? is mime conversion start sequence */
			if(mime_f == STRICT_MIME) {
			    /* check in real detail */
			    if (mime_begin_strict(f) == EOF) 
				LAST;
			    else
				NEXT;
			} else if (mime_begin(f) == EOF) 
                            LAST;
                        else
                            NEXT;
                    } else {
                        (*oconv)(0, '=');
                        (*i_ungetc)(c1,f);
                        NEXT;
                    }
                } else {
                    /* normal ASCII code */ 
                    SEND;
                }
            } else if (c1 == SI) {
                shift_mode = FALSE; 
                NEXT;
            } else if (c1 == SO) {
                shift_mode = TRUE; 
                NEXT;
            } else if (c1 == ESC ) {
                if ((c1 = (*i_getc)(f)) == EOF) {
                    /*  (*oconv)(0, ESC); don't send bogus code */
                    LAST;
                } else if (c1 == '$') {
                    if ((c1 = (*i_getc)(f)) == EOF) {
                        /*
                        (*oconv)(0, ESC); don't send bogus code 
                        (*oconv)(0, '$'); */
                        LAST;
                    } else if (c1 == '@'|| c1 == 'B') {
                        /* This is kanji introduction */
                        input_mode = X0208;
                        shift_mode = FALSE;
                        NEXT;
                    } else if (c1 == '(') {
                        if ((c1 = (*i_getc)(f)) == EOF) {
                            /* don't send bogus code 
                            (*oconv)(0, ESC);
                            (*oconv)(0, '$');
                            (*oconv)(0, '(');
                                */
                            LAST;
                        } else if (c1 == '@'|| c1 == 'B') {
                            /* This is kanji introduction */
                            input_mode = X0208;
                            shift_mode = FALSE;
                            NEXT;
                        } else {
                            /* could be some special code */
                            (*oconv)(0, ESC);
                            (*oconv)(0, '$');
                            (*oconv)(0, '(');
                            (*oconv)(0, c1);
                            NEXT;
                        }
                    } else if (broken_f&0x2) {
                        /* accept any ESC-(-x as broken code ... */
                        input_mode = X0208;
                        shift_mode = FALSE;
                        NEXT;
                    } else {
                        (*oconv)(0, ESC);
                        (*oconv)(0, '$');
                        (*oconv)(0, c1);
                        NEXT;
                    }
                } else if (c1 == '(') {
                    if ((c1 = (*i_getc)(f)) == EOF) {
                        /* don't send bogus code 
                        (*oconv)(0, ESC);
                        (*oconv)(0, '('); */
                        LAST;
                    } else {
                        if (c1 == 'I') {
                            /* This is X0201 kana introduction */
                            input_mode = X0201; shift_mode = X0201;
                            NEXT;
                        } else if (c1 == 'B' || c1 == 'J' || c1 == 'H') {
                            /* This is X0208 kanji introduction */
                            input_mode = ASCII; shift_mode = FALSE;
                            NEXT;
                        } else if (broken_f&0x2) {
                            input_mode = ASCII; shift_mode = FALSE;
                            NEXT;
                        } else {
                            (*oconv)(0, ESC);
                            (*oconv)(0, '(');
                            /* maintain various input_mode here */
                            SEND;
                        }
                    }
                } else {
                    /* lonely ESC  */
                    (*oconv)(0, ESC);
                    SEND;
                }
            } else if ((c1 == NL || c1 == CR) && broken_f&4) {
                input_mode = ASCII; estab_f = FALSE;
                SEND;
	    } else 
                SEND;
        }
        /* send: */
        if (input_mode == X0208) 
            (*oconv)(c2, c1);  /* this is JIS, not SJIS/EUC case */
        else if (input_mode) 
            (*oconv)(input_mode, c1);  /* other special case */
        else
            (*iconv)(c2, c1);  /* can be EUC/SJIS */
        c2 = 0;
        continue;
        /* goto next_word */
    }

    /* epilogue */
    (*iconv)(EOF, 0);
    return 1;
}

int
h_conv(f, c2, c1)
    FILE  *f;
    int    c1,
                    c2;
{
    int    wc,c3;


    /** it must NOT be in the kanji shifte sequence      */
    /** it must NOT be written in JIS7                   */
    /** and it must be after 2 byte 8bit code            */

    hold_count = 0;
    push_hold_buf(c2, c1);
    c2 = 0;

    while ((c1 = (*i_getc)(f)) != EOF) {
        if (c2) {
            /* second byte */
            if (!estab_f) {
                /* not established */
                if (c1 > SSP) {
                    /* it is still ambiguious yet */
                    SEND;
                } else if (c1 < AT) {
                    /* ignore bogus first byte */
                    c2 = 0;
                    SEND;
                } else {
                    /* now established */
                    /* it seems to be MS Kanji */
                    estab_f = TRUE;
                    iconv = s_iconv;
                    SEND;
                }
            } else
                SEND;
        } else {
            /* First byte */
            if (c1 > DEL) {
                /* 8th bit is on */
                if (c1 < SSP) {
                    /* it seems to be MS Kanji */
                    estab_f = TRUE;
                    iconv = s_iconv;
                } else if (c1 < 0xe0) {
                    /* it seems to be EUC */
                    estab_f = TRUE;
                    iconv = e_iconv;
                } else {
                    /* still ambiguious */
                }
                c2 = c1;
                NEXT;
            } else
            /* 7 bit code , then send without any process */
                SEND;
        }
        /* send: */
        if ((push_hold_buf(c2, c1) == EOF) || estab_f)
            break;
        c2 = 0;
        continue;
    }

    /** now,
     ** 1) EOF is detected, or
     ** 2) Code is established, or
     ** 3) Buffer is FULL (but last word is pushed)
     **
     ** in 1) and 3) cases, we continue to use
     ** Kanji codes by oconv and leave estab_f unchanged.
     **/

    c3=c1;
    for (wc = 0; wc < hold_count; wc += 2) {
        c2 = hold_buf[wc];
        c1 = hold_buf[wc+1];
        (*iconv)(c2, c1);
    }
    return c3;
}



int
push_hold_buf(c2, c1)
    int             c2,
                    c1;
{
    if (hold_count >= HOLD_SIZE*2)
        return (EOF);
    hold_buf[hold_count++] = c2;
    hold_buf[hold_count++] = c1;
    return ((hold_count >= HOLD_SIZE*2) ? EOF : hold_count);
}


void
s_iconv(c2, c1)
    int    c2,
                    c1;
{
    if (c2 == X0201) {
	c1 &= 0x7f;
    } else if ((c2 == EOF) || (c2 == 0) || c2 < SPACE) {
        /* NOP */
    } else {
        c2 = c2 + c2 - ((c2 <= 0x9f) ? SJ0162 : SJ6394);
        if (c1 < 0x9f)
            c1 = c1 - ((c1 > DEL) ? SPACE : 0x1f);
        else {
            c1 = c1 - 0x7e;
            c2++;
        }
    }
    (*oconv)(c2, c1);
}

void
e_iconv(c2, c1)
    int    c2,
                    c1;
{
    if (c2 == X0201) {
	c1 &= 0x7f;
    } else if ((c2 == EOF) || (c2 == 0) || c2 < SPACE) {
        /* NOP */
    } else {
        c1 &= 0x7f;
        c2 &= 0x7f;
    }
    (*oconv)(c2, c1);
}

void
e_oconv(c2, c1)
    int    c2,
                    c1;
{
    if (c2 == EOF) {
        return;
    } else if (c2 == 0) { 
	output_mode = ASCII;
        (*o_putc)(c1);
    } else if (c2 == X0201) {
	output_mode = JAPANESE_EUC;
        (*o_putc)(SSO); (*o_putc)(c1|0x80);
    } else if (c2 == ISO8859_1) {
	output_mode = ISO8859_1;
        (*o_putc)(c1 | 0x080);
    } else {
        if ((c1<0x20 || 0x7e<c1) ||
           (c2<0x20 || 0x7e<c2)) {
            estab_f = FALSE;
            return; /* too late to rescue this char */
        }
	output_mode = JAPANESE_EUC;
        (*o_putc)(c2 | 0x080);
        (*o_putc)(c1 | 0x080);
    }
}



void
s_oconv(c2, c1)
    int    c2,
                    c1;
{
    if (c2 == EOF) {
        return;
    } else if (c2 == 0) {
	output_mode = ASCII;
        (*o_putc)(c1);
    } else if (c2 == X0201) {
	output_mode = SHIFT_JIS;
        (*o_putc)(c1|0x80);
    } else if (c2 == ISO8859_1) {
	output_mode = ISO8859_1;
        (*o_putc)(c1 | 0x080);
    } else {
        if ((c1<0x20 || 0x7e<c1) ||
           (c2<0x20 || 0x7e<c2)) {
            estab_f = FALSE;
            return; /* too late to rescue this char */
        }
	output_mode = SHIFT_JIS;
        (*o_putc)((((c2 - 1) >> 1) + ((c2 <= 0x5e) ? 0x71 : 0xb1)));
        (*o_putc)((c1 + ((c2 & 1) ? ((c1 < 0x60) ? 0x1f : 0x20) : 0x7e)));
    }
}

void
j_oconv(c2, c1)
    int    c2,
                    c1;
{
    if (c2 == EOF) {
        if (output_mode !=ASCII && output_mode!=ISO8859_1) {
            (*o_putc)(ESC);
            (*o_putc)('(');
            (*o_putc)(ascii_intro);
	    output_mode = ASCII;
        }
    } else if (c2==X0201) {
        if (output_mode!=X0201) {
            output_mode = X0201;
            (*o_putc)(ESC);
            (*o_putc)('(');
            (*o_putc)('I');
        }
        (*o_putc)(c1);
    } else if (c2==ISO8859_1) {
            /* iso8859 introduction, or 8th bit on */
            /* Can we convert in 7bit form using ESC-'-'-A ? 
               Is this popular? */
	output_mode = ISO8859_1;
        (*o_putc)(c1|0x80);
    } else if (c2 == 0) {
        if (output_mode !=ASCII && output_mode!=ISO8859_1) {
            (*o_putc)(ESC);
            (*o_putc)('(');
            (*o_putc)(ascii_intro);
            output_mode = ASCII;
        }
        (*o_putc)(c1);
    } else {
        if (output_mode != X0208) {
            output_mode = X0208;
            (*o_putc)(ESC);
            (*o_putc)('$');
            (*o_putc)(kanji_intro);
        }
        if (c1<0x20 || 0x7e<c1) 
            return;
        if (c2<0x20 || 0x7e<c2) 
            return;
        (*o_putc)(c2);
        (*o_putc)(c1);
    }
}

void
base64_conv(c2, c1)
    int    c2,
                    c1;
{
    if (base64_count>50 && !mimeout_mode && c2==0 && c1==SPACE) {
	(*o_putc)(NL);
    } else if (base64_count>66 && mimeout_mode) {
	(*o_base64conv)(EOF,0);
	(*o_putc)(NL);
    }
    (*o_base64conv)(c2,c1);
}


static int broken_buf[3];
static int broken_counter = 0;
static int broken_last = 0;
int
broken_getc(f)
FILE *f;
{
    int c,c1;

    if (broken_counter>0) {
	return broken_buf[--broken_counter];
    }
    c= (*i_bgetc)(f);
    if (c=='$' && broken_last != ESC 
            && (input_mode==ASCII || input_mode==X0201)) {
	c1= (*i_bgetc)(f);
	broken_last = 0;
	if (c1=='@'|| c1=='B') {
	    broken_buf[0]=c1; broken_buf[1]=c; 
	    broken_counter=2;
	    return ESC;
	} else {
	    (*i_bungetc)(c1,f);
	    return c;
	}
    } else if (c=='(' && broken_last != ESC 
            && (input_mode==X0208 || input_mode==X0201)) { /* ) */
	c1= (*i_bgetc)(f);
	broken_last = 0;
	if (c1=='J'|| c1=='B') {
	    broken_buf[0]=c1; broken_buf[1]=c;
	    broken_counter=2;
	    return ESC;
	} else {
	    (*i_bungetc)(c1,f);
	    return c;
	}
    } else {
	broken_last = c;
	return c;
    }
}

int
broken_ungetc(c,f)
int c;
FILE *f;
{
    if (broken_counter<2)
	broken_buf[broken_counter++]=c;
    return c;
}

static int prev_cr = 0;

void
cr_conv(c2,c1) 
int c2,c1;
{
    if (prev_cr) {
	prev_cr = 0;
	if (! (c2==0&&c1==NL) ) {
	    cr_conv(0,'\n');
	}
    }
    if (c2) {
        (*o_crconv)(c2,c1);
    } else if (c1=='\r') {
	prev_cr = c1;
    } else if (c1=='\n') {
        if (crmode_f==CRLF) {
            (*o_crconv)(0,'\r');
	} else if (crmode_f==CR) {
            (*o_crconv)(0,'\r');
	    return;
	} 
	(*o_crconv)(0,NL);
    } else {
        (*o_crconv)(c2,c1);
    }
}

/* 
  Return value of fold_conv()

       \n  add newline  and output char
       \r  add newline  and output nothing
       ' ' space
       0   skip  
       1   (or else) normal output 

  fold state in prev (previous character)

      >0x80 Japanese (X0208/X0201)
      <0x80 ASCII
      \n    new line 
      ' '   space

  This fold algorthm does not preserve heading space in a line.
  This is the main difference from fmt.
*/

int
char_size(c2,c1) {
    return c2?2:1;
}

void
fold_conv(c2,c1) 
int c2,c1;
{ 
    int prev0;
    int fold_state=0;

    if (c1== '\r') {
    	fold_state=0;  /* ignroe cr */
    } else if (c1== BS) {
        if (f_line>0) f_line--;
        fold_state =  1;
    } else if (c2==EOF && f_line != 0) {    /* close open last line */
            fold_state = '\n';
    } else if (c1=='\n') {
        /* new line */
        if (f_prev == c1) {        /* duplicate newline */
            if (f_line) {
                f_line = 0;
                fold_state =  '\n';    /* output two newline */
            } else {
                f_line = 0;
                fold_state =  1;
            }
        } else  {
            if (f_prev&0x80) {     /* Japanese? */
                f_prev = c1;
                fold_state =  0;       /* ignore given single newline */
            } else if (f_prev==' ') {
                fold_state =  0;
            } else {
                f_prev = c1;
                if (++f_line<=fold_len) 
                    fold_state =  ' ';
                else {
                    f_line = 0;
                    fold_state =  '\r';        /* fold and output nothing */
                }
            }
        }
    } else if (c1=='\f') {
        f_prev = '\n';
        if (f_line==0)
            fold_state =  1;
        f_line = 0;
        fold_state =  '\n';            /* output newline and clear */
    } else if ( (c2==0  && c1==' ')||
               (c2==0  && c1=='\t')||
               (c2=='!'&& c1=='!')) {
        /* X0208 kankaku or ascii space */
            if (f_prev == ' ') {
                fold_state = 0;         /* remove duplicate spaces */
            } else {
                f_prev = ' ';    
                if (++f_line<=fold_len) 
                    fold_state = ' ';         /* output ASCII space only */
                else {
                    f_prev = ' '; f_line = 0;
                    fold_state = '\r';        /* fold and output nothing */
                }
            }
    } else {
        prev0 = f_prev; /* we still need this one... , but almost done */
        f_prev = c1;
        if (c2 || c2==X0201) 
            f_prev |= 0x80;  /* this is Japanese */
        f_line += char_size(c2,c1);
        if (f_line<=fold_len) {   /* normal case */
            fold_state = 1;
        } else {
            if (f_line>=fold_len+FOLD_MARGIN) { /* too many kinsou suspension */
                f_line = char_size(c2,c1);
                fold_state =  '\n';       /* We can't wait, do fold now */
            } else if (c2==X0201) {
            /* simple kinsoku rules  return 1 means no folding  */
                if (c1==(0xde&0x7f)) fold_state = 1; /* $B!+(B*/
                else if (c1==(0xdf&0x7f)) fold_state = 1; /* $B!,(B*/
                else if (c1==(0xa4&0x7f)) fold_state = 1; /* $B!#(B*/
                else if (c1==(0xa3&0x7f)) fold_state = 1; /* $B!$(B*/
                else if (c1==(0xa1&0x7f)) fold_state = 1; /* $B!W(B*/
                else if (c1==(0xb0&0x7f)) fold_state = 1; /* - */
                else if (SPACE<=c1 && c1<=(0xdf&0x7f)) {      /* X0201 */
		    f_line = 1;
		    fold_state = '\n';/* add one new f_line before this character */
		} else {
		    f_line = 1;
		    fold_state = '\n';/* add one new f_line before this character */
		}
            } else if (c2==0) {
                /* kinsoku point in ASCII */ 
		if (  c1==')'||    /* { [ ( */
                     c1==']'||
                     c1=='}'||
                     c1=='.'||
                     c1==','||
                     c1=='!'||
                     c1=='?'||
                     c1=='/'||
                     c1==':'||
                     c1==';' ) {
		    fold_state = 1;
		/* just after special */
		} else if (!is_alnum(prev0)) {
		    f_line = char_size(c2,c1);
		    fold_state = '\n';
		} else if ((prev0==' ') ||   /* ignored new f_line */
                      (prev0=='\n')||        /* ignored new f_line */
                      (prev0&0x80)) {        /* X0208 - ASCII */
		    f_line = char_size(c2,c1);
                    fold_state = '\n';/* add one new f_line before this character */
                } else {
                    fold_state = 1;  /* default no fold in ASCII */
                }
            } else {
                if (c2=='!') {
                    if (c1=='"')  fold_state = 1; /* $B!"(B */
                    else if (c1=='#')  fold_state = 1; /* $B!#(B */
                    else if (c1=='W')  fold_state = 1; /* $B!W(B */
                    else if (c1=='K')  fold_state = 1; /* $B!K(B */
                    else if (c1=='$')  fold_state = 1; /* $B!$(B */
                    else if (c1=='%')  fold_state = 1; /* $B!%(B */
                    else if (c1=='\'') fold_state = 1; /* $B!\(B */
                    else if (c1=='(')  fold_state = 1; /* $B!((B */
                    else if (c1==')')  fold_state = 1; /* $B!)(B */
                    else if (c1=='*')  fold_state = 1; /* $B!*(B */
                    else if (c1=='+')  fold_state = 1; /* $B!+(B */
                    else if (c1==',')  fold_state = 1; /* $B!,(B */
                         /* default no fold in kinsoku */
		    else { 
			fold_state = '\n';
			f_line = char_size(c2,c1);
			/* add one new f_line before this character */
		    }
                } else {
		    f_line = char_size(c2,c1);
                    fold_state = '\n'; 
                    /* add one new f_line before this character */
                }
            }
        }
    }
    /* terminator process */
    switch(fold_state) {
        case '\n': 
            (*o_fconv)(0,'\n');
            (*o_fconv)(c2,c1);
            break;
        case 0:    
            return;
        case '\r': 
            (*o_fconv)(0,'\n');
            break;
        case '\t': 
        case ' ': 
            (*o_fconv)(0,' ');
            break;
        default:
            (*o_fconv)(c2,c1);
    }
}

int z_prev2=0,z_prev1=0;

void
z_conv(c2,c1)
int c2,c1;
{

    /* if (c2) c1 &= 0x7f; assertion */

    if (x0201_f && z_prev2==X0201) {  /* X0201 */
        if (c1==(0xde&0x7f)) { /* $BByE@(B */
            z_prev2=0;
            (*o_zconv)(dv[(z_prev1-SPACE)*2],dv[(z_prev1-SPACE)*2+1]);
            return;
        } else if (c1==(0xdf&0x7f)&&ev[(z_prev1-SPACE)*2]) {  /* $BH>ByE@(B */
            z_prev2=0;
            (*o_zconv)(ev[(z_prev1-SPACE)*2],ev[(z_prev1-SPACE)*2+1]);
            return;
        } else {
            z_prev2=0;
            (*o_zconv)(cv[(z_prev1-SPACE)*2],cv[(z_prev1-SPACE)*2+1]);
        }
    }

    if (c2==EOF) {
        (*o_zconv)(c2,c1);
        return;
    }

    if (x0201_f && c2==X0201) {
        if (dv[(c1-SPACE)*2]||ev[(c1-SPACE)*2]) {
            /* wait for $BByE@(B or $BH>ByE@(B */
            z_prev1 = c1; z_prev2 = c2;
            return;
        } else {
            (*o_zconv)(cv[(c1-SPACE)*2],cv[(c1-SPACE)*2+1]);
            return;
        }
    }

    /* JISX0208 Alphabet */
    if (alpha_f && c2 == 0x23 ) {
        c2 = 0;
    } else if (alpha_f && c2 == 0x21 ) { 
    /* JISX0208 Kigou */
       if (0x21==c1) {
           if (alpha_f&0x2) {
               c1 = ' ';
           } else if (alpha_f&0x4) {
                (*o_zconv)(0,' ');
                (*o_zconv)(0,' ');
                return;
           } 
       } else if (0x20<c1 && c1<0x7f && fv[c1-0x20]) {
           c1 = fv[c1-0x20];
           c2 =  0;
       } 
    }
    (*o_zconv)(c2,c1);
}


#define rot13(c)  ( \
      ( c < 'A' ) ? c: \
      (c <= 'M')  ? (c + 13): \
      (c <= 'Z')  ? (c - 13): \
      (c < 'a')   ? (c): \
      (c <= 'm')  ? (c + 13): \
      (c <= 'z')  ? (c - 13): \
      (c) \
)

#define  rot47(c) ( \
      ( c < '!' ) ? c: \
      ( c <= 'O' ) ? (c + 47) : \
      ( c <= '~' ) ?  (c - 47) : \
      c \
)

void
rot_conv(c2,c1)
int c2,c1;
{
    if (rot_f) {
        if (c1==0 || c2==X0201 || c2==ISO8859_1) {
            c1 = rot13(c1);
        } else if (c2) {
            c1 = rot47(c1);
            c2 = rot47(c2);
        }
    }
    (*o_rot_conv)(c2,c1);
}

/* This converts  =?ISO-2022-JP?B?HOGE HOGE?= */

unsigned char *mime_pattern[] = {
   (unsigned char *)"\075?EUC-JP?B?",
   (unsigned char *)"\075?SHIFT_JIS?B?",
   (unsigned char *)"\075?ISO-8859-1?Q?",
   (unsigned char *)"\075?ISO-2022-JP?B?",
   (unsigned char *)"\075?ISO-2022-JP?Q?",
   NULL
};

int      mime_encode[] = {
    JAPANESE_EUC, SHIFT_JIS,ISO8859_1, X0208, X0201, 
    0
};

int      mime_encode_method[] = {
    'B', 'B','Q', 'B', 'Q', 
    0
};


#define MAXRECOVER 20

/* I don't trust portablity of toupper */
#define nkf_toupper(c)  (('a'<=c && c<='z')?(c-('a'-'A')):c)

void
switch_mime_getc()
{
    if (i_getc!=mime_getc) {
	i_mgetc = i_getc; i_getc = mime_getc;
	i_mungetc = i_ungetc; i_ungetc = mime_ungetc;
	if(mime_f==STRICT_MIME) {
	    i_mgetc_buf = i_mgetc; i_mgetc = mime_getc_buf;
	    i_mungetc_buf = i_mungetc; i_mungetc = mime_ungetc_buf;
	}
    }
}

void
unswitch_mime_getc()
{
    if(mime_f==STRICT_MIME) {
	i_mgetc = i_mgetc_buf;
	i_mungetc = i_mungetc_buf;
    }
    i_getc = i_mgetc;
    i_ungetc = i_mungetc;
}

int
mime_begin_strict(f)
FILE *f;
{
    int c1;
    int i,j,k;
    unsigned char *p,*q;
    int r[MAXRECOVER];    /* recovery buffer, max mime pattern lenght */

    mime_decode_mode = FALSE;
    /* =? has been checked */
    j = 0;
    p = mime_pattern[j];
    r[0]='='; r[1]='?';

    for(i=2;p[i]>' ';i++) {                   /* start at =? */
        if ( ((r[i] = c1 = (*i_getc)(f))==EOF) || nkf_toupper(c1) != p[i] ) {
            /* pattern fails, try next one */
            q = p;
            while ((p = mime_pattern[++j])) {
                for(k=2;k<i;k++)              /* assume length(p) > i */
                    if (p[k]!=q[k]) break;
                if (k==i && nkf_toupper(c1)==p[k]) break;
            }
            if (p) continue;  /* found next one, continue */
            /* all fails, output from recovery buffer */
            (*i_ungetc)(c1,f);
            for(j=0;j<i;j++) {
                (*oconv)(0,r[j]);
            }
            return c1;
        }
    }
    mime_decode_mode = p[i-2];
    if (mime_decode_mode=='B') {
        mimebuf_f = unbuf_f;
        if (!unbuf_f) {
            /* do MIME integrity check */
            return mime_integrity(f,mime_pattern[j]);
        } 
    }
    switch_mime_getc();
    mimebuf_f = TRUE;
    return c1;
}

int
mime_getc_buf(f) 
FILE *f;
{
    /* we don't keep eof of Fifo, becase it contains ?= as
       a terminator. It was checked in mime_integrity. */
    return ((mimebuf_f)?
        (*i_mgetc_buf)(f):Fifo(mime_input++));
}

int
mime_ungetc_buf(c,f) 
FILE *f;
int c;
{
    if (mimebuf_f)
	(*i_mungetc_buf)(c,f);
    else 
	Fifo(--mime_input)=c;
    return c;
}

int
mime_begin(f)
FILE *f;
{
    int c1;
    int i,k;

    /* In NONSTRICT mode, only =? is checked. In case of failure, we  */
    /* re-read and convert again from mime_buffer.  */

    /* =? has been checked */
    k = mime_last;
    Fifo(mime_last++)='='; Fifo(mime_last++)='?';
    for(i=2;i<MAXRECOVER;i++) {                   /* start at =? */
        /* We accept any character type even if it is breaked by new lines */
        c1 = (*i_getc)(f); Fifo(mime_last++)= c1 ;
        if (c1=='\n'||c1==' '||c1=='\r'||
                c1=='-'||c1=='_'||is_alnum(c1) ) continue;
        if (c1=='=') {
            /* Failed. But this could be another MIME preemble */
            (*i_ungetc)(c1,f);
            mime_last--;
            break;
        }
        if (c1!='?') break;
        else {
            /* c1=='?' */
            c1 = (*i_getc)(f); Fifo(mime_last++) = c1;
            if (!(++i<MAXRECOVER) || c1==EOF) break;
            if (c1=='b'||c1=='B') {
                mime_decode_mode = 'B';
            } else if (c1=='q'||c1=='Q') {
                mime_decode_mode = 'Q';
            } else {
                break;
            }
            c1 = (*i_getc)(f); Fifo(mime_last++) = c1;
            if (!(++i<MAXRECOVER) || c1==EOF) break;
            if (c1!='?') {
                mime_decode_mode = FALSE;
            }
            break;
        }
    }
    switch_mime_getc();
    if (!mime_decode_mode) {
        /* false MIME premble, restart from mime_buffer */
        mime_decode_mode = 1;  /* no decode, but read from the mime_buffer */
        /* Since we are in MIME mode until buffer becomes empty,    */
        /* we never go into mime_begin again for a while.           */
        return c1;
    }
    /* discard mime preemble, and goto MIME mode */
    mime_last = k;
    /* do no MIME integrity check */
    return c1;   /* used only for checking EOF */
}


int 
mime_getc(f)
FILE *f;
{
    int c1, c2, c3, c4, cc;
    int t1, t2, t3, t4, mode, exit_mode;

    if (mime_top != mime_last) {  /* Something is in FIFO */
        return  Fifo(mime_top++);
    }
    if (mime_decode_mode==1 ||mime_decode_mode==FALSE) {
	mime_decode_mode=FALSE;
	unswitch_mime_getc();
	return (*i_getc)(f);
    }

    if (mimebuf_f == FIXED_MIME)
        exit_mode = mime_decode_mode;
    else
        exit_mode = FALSE;
    if (mime_decode_mode == 'Q') {
        if ((c1 = (*i_mgetc)(f)) == EOF) return (EOF);
        if (c1=='_') return ' ';
        if (c1!='=' && c1!='?') 
            return c1;
        mime_decode_mode = exit_mode; /* prepare for quit */
        if (c1<=' ') return c1;
        if ((c2 = (*i_mgetc)(f)) == EOF) return (EOF);
        if (c2<=' ') return c2;
        if (c1=='?'&&c2=='=') {
            /* end Q encoding */
            input_mode = exit_mode;
            while((c1=(*i_getc)(f))!=EOF && c1==SPACE 
                        /* && (c1==NL||c1==TAB||c1=='\r') */ ) ;
            return c1;
        }
        if (c1=='?') {
            mime_decode_mode = 'Q'; /* still in MIME */
            (*i_mungetc)(c2,f);
            return c1;
        }
        if ((c3 = (*i_mgetc)(f)) == EOF) return (EOF);
        if (c2<=' ') return c2;
        mime_decode_mode = 'Q'; /* still in MIME */
#define hex(c)   (('0'<=c&&c<='9')?(c-'0'):\
     ('A'<=c&&c<='F')?(c-'A'+10):('a'<=c&&c<='f')?(c-'a'+10):0)
        return ((hex(c2)<<4) + hex(c3));
    }

    if (mime_decode_mode != 'B') {
        mime_decode_mode = FALSE;
        return (*i_mgetc)(f);
    }


    /* Base64 encoding */
    /* 
        MIME allows line break in the middle of 
        Base64, but we are very pessimistic in decoding
        in unbuf mode because MIME encoded code may broken by 
        less or editor's control sequence (such as ESC-[-K in unbuffered
        mode. ignore incomplete MIME.
    */
    mode = mime_decode_mode;
    mime_decode_mode = exit_mode;  /* prepare for quit */

    while ((c1 = (*i_mgetc)(f))<=' ') {
        if (c1==EOF)
            return (EOF);
    }
    if ((c2 = (*i_mgetc)(f))<=' ') {
        if (c2==EOF)
            return (EOF);
        if (mimebuf_f!=FIXED_MIME) input_mode = ASCII;  
        return c2;
    }
    if ((c1 == '?') && (c2 == '=')) {
        input_mode = ASCII;
        while((c1=(*i_getc)(f))!=EOF && c1==SPACE 
                    /* && (c1==NL||c1==TAB||c1=='\r') */ ) ;
        return c1;
    }
    if ((c3 = (*i_mgetc)(f))<=' ') {
        if (c3==EOF)
            return (EOF);
        if (mimebuf_f!=FIXED_MIME) input_mode = ASCII;  
        return c3;
    }
    if ((c4 = (*i_mgetc)(f))<=' ') {
        if (c4==EOF)
            return (EOF);
        if (mimebuf_f!=FIXED_MIME) input_mode = ASCII;  
        return c4;
    }

    mime_decode_mode = mode; /* still in MIME sigh... */

    /* BASE 64 decoding */

    t1 = 0x3f & base64decode(c1);
    t2 = 0x3f & base64decode(c2);
    t3 = 0x3f & base64decode(c3);
    t4 = 0x3f & base64decode(c4);
    cc = ((t1 << 2) & 0x0fc) | ((t2 >> 4) & 0x03);
    if (c2 != '=') {
        Fifo(mime_last++) = cc;
        cc = ((t2 << 4) & 0x0f0) | ((t3 >> 2) & 0x0f);
        if (c3 != '=') {
            Fifo(mime_last++) = cc;
            cc = ((t3 << 6) & 0x0c0) | (t4 & 0x3f);
            if (c4 != '=') 
                Fifo(mime_last++) = cc;
        }
    } else {
        return c1;
    }
    return  Fifo(mime_top++);
}

int
mime_ungetc(c,f) 
int   c;
FILE  *f;
{
    Fifo(--mime_top) = c;
    return c;
}

int
mime_integrity(f,p)
FILE *f;
unsigned char *p;
{
    int c,d;
    unsigned int q;
    /* In buffered mode, read until =? or NL or buffer full
     */
    mime_input = mime_top;
    mime_last = mime_top;
    while(*p) Fifo(mime_input++) = *p++;
    d = 0;
    q = mime_input;
    while((c=(*i_getc)(f))!=EOF) {
        if (((mime_input-mime_top)&MIME_BUF_MASK)==0) {
	    break;   /* buffer full */
	}
        if (c=='=' && d=='?') {
            /* checked. skip header, start decode */
            Fifo(mime_input++) = c;
            /* mime_last_input = mime_input; */
            mime_input = q; 
	    switch_mime_getc();
            return 1;
        }
        if (!( (c=='+'||c=='/'|| c=='=' || c=='?' || is_alnum(c))))
            break;
        /* Should we check length mod 4? */
        Fifo(mime_input++) = c;
        d=c;
    }
    /* In case of Incomplete MIME, no MIME decode  */
    Fifo(mime_input++) = c;
    mime_last = mime_input;     /* point undecoded buffer */
    mime_decode_mode = 1;              /* no decode on Fifo last in mime_getc */
    switch_mime_getc();         /* anyway we need buffered getc */
    return 1;
}

int
base64decode(c)
    int            c;
{
    int             i;
    if (c > '@') {
        if (c < '[') {
            i = c - 'A';                        /* A..Z 0-25 */
        } else {
            i = c - 'G'     /* - 'a' + 26 */ ;  /* a..z 26-51 */
	}
    } else if (c > '/') {
        i = c - '0' + '4'   /* - '0' + 52 */ ;  /* 0..9 52-61 */
    } else if (c == '+') {
        i = '>'             /* 62 */ ;          /* +  62 */
    } else {
        i = '?'             /* 63 */ ;          /* / 63 */
    }
    return (i);
}

static char basis_64[] =
   "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

static int b64c;

void
open_mime(mode)
int mode;
{
    char *p;
    int i;
    p  = mime_pattern[0];
    for(i=0;mime_encode[i];i++) {
	if (mode == mime_encode[i]) {
	    p = mime_pattern[i];
		break;
	}
    }
    mimeout_mode = mime_encode_method[i];
	    
    /* (*o_mputc)(' '); */
    while(*p) {
        (*o_mputc)(*p++);
        base64_count ++;
    }
}

void
close_mime()
{
    (*o_mputc)('?');
    (*o_mputc)('=');
    (*o_mputc)(' ');
    base64_count += 3;
    mimeout_mode = 0;
}

#define itoh4(c)   (c>=10?c+'A'-10:c+'0')

void
mime_putc(c)
    int            c;
{
    if (mimeout_f==FIXED_MIME) {
	if (base64_count>71) {
            (*o_mputc)('\n');
            base64_count=0;
        }
    } else if (c==NL) {
	base64_count=0;
    } 
    if (c!=EOF) {
        if ( c<=DEL &&(output_mode==ASCII ||output_mode == ISO8859_1 )
		&& mimeout_f!=FIXED_MIME) {
	    if (mimeout_mode=='Q') {
		if (c<=SPACE) {
		    close_mime();
		}
		(*o_mputc)(c);
		return;
	    }
            if (mimeout_mode!='B' || c!=SPACE) {
		if (mimeout_mode) {
		    mime_putc(EOF);
		    mimeout_mode=0;
		}
		(*o_mputc)(c);
		base64_count ++;
		return;
	    }
        } else if (!mimeout_mode && mimeout_f!=FIXED_MIME) {
         /* if (base64_count>55) { 
		(*o_mputc)('\n');
		base64_count = 0;
	    } */
	    open_mime(output_mode);
        }
    } else { /* c==EOF */
        switch(mimeout_mode) {
        case 'Q':
        case 'B':
            break;
        case 2:
            (*o_mputc)(basis_64[((b64c & 0x3)<< 4)]);
            (*o_mputc)('=');
            (*o_mputc)('=');
            base64_count += 3;
            break;
        case 1:
            (*o_mputc)(basis_64[((b64c & 0xF) << 2)]);
            (*o_mputc)('=');
            base64_count += 2;
            break;
        }
        if (mimeout_mode) {
            if (mimeout_f!=FIXED_MIME) {
                close_mime(); 
            } else if (mimeout_mode != 'Q')
                mimeout_mode = 'B';
        }
        return;
    }
    switch(mimeout_mode) {
    case 'Q':
	if(c>=DEL) {
	    (*o_mputc)('=');
	    (*o_mputc)(itoh4(((c>>4)&0xf)));
	    (*o_mputc)(itoh4((c&0xf)));
	} else {
	    (*o_mputc)(c);
	}
        break;
    case 'B':
        b64c=c;
        (*o_mputc)(basis_64[c>>2]);
        mimeout_mode=2;
        base64_count ++;
        break;
    case 2:
        (*o_mputc)(basis_64[((b64c & 0x3)<< 4) | ((c & 0xF0) >> 4)]);
        b64c=c;
        mimeout_mode=1;
        base64_count ++;
        break;
    case 1:
        (*o_mputc)(basis_64[((b64c & 0xF) << 2) | ((c & 0xC0) >>6)]);
        (*o_mputc)(basis_64[c & 0x3F]);
        mimeout_mode='B';
        base64_count += 2;
        break;
    }
}


#ifdef PERL_XS
void 
reinit()
{
    unbuf_f = FALSE;
    estab_f = FALSE;
    nop_f = FALSE;
    binmode_f = TRUE;       
    rot_f = FALSE;         
    input_f = FALSE;      
    alpha_f = FALSE;     
    mime_f = TRUE;      
    mimebuf_f = FALSE; 
    broken_f = FALSE;  
    iso8859_f = FALSE; 
    x0201_f = NO_X0201; 
    fold_f  = FALSE;
    kanji_intro = DEFAULT_J;
    ascii_intro = DEFAULT_R;

    output_conv = DEFAULT_CONV; 
    oconv = DEFAULT_CONV; 

    o_putc = std_putc;
    o_mputc = std_putc;
    o_crconv = oconv; 
    o_rot_conv = oconv; 
    o_fconv = oconv; 
    o_zconv = oconv;

    i_getc = std_getc;
    i_ungetc = std_ungetc;
    i_mgetc = std_getc; 
    i_mungetc = std_ungetc; 

    output_mode = ASCII;
    input_mode =  ASCII;
    shift_mode =  FALSE;
    mime_decode_mode =   FALSE;
    file_out = FALSE;
    mimeout_mode = 0;
    mimeout_f = FALSE;
    base64_count = 0;
    option_mode = 0;
}
#endif

void 
no_connection(c1,c2) 
int c1,c2;
{
    fprintf(stderr,"Module connection faileur.\n");
    exit(1);
}

#ifndef PERL_XS
void 
usage()   
{
    fprintf(stderr,"USAGE:  nkf(nkf32,wnkf,nkf2) -[flags] [in file] .. [out file for -O flag]\n");
    fprintf(stderr,"Flags:\n");
    fprintf(stderr,"b,u      Output is bufferred (DEFAULT),Output is unbufferred\n");
#ifdef DEFAULT_CODE_SJIS
    fprintf(stderr,"j,s,e    Outout code is JIS 7 bit, Shift JIS (DEFAULT), AT&T JIS (EUC)\n");
#endif
#ifdef DEFAULT_CODE_JIS
    fprintf(stderr,"j,s,e    Outout code is JIS 7 bit (DEFAULT), Shift JIS, AT&T JIS (EUC)\n");
#endif
#ifdef DEFAULT_CODE_EUC
    fprintf(stderr,"j,s,e    Outout code is JIS 7 bit, Shift JIS, AT&T JIS (EUC) (DEFAULT)\n");
#endif
    fprintf(stderr,"J,S,E    Input assumption is JIS 7 bit , Shift JIS, AT&T JIS (EUC)\n");
    fprintf(stderr,"t        no conversion\n");
    fprintf(stderr,"i_/o_    Output sequence to designate JIS-kanji/ASCII (DEFAULT B)\n");
    fprintf(stderr,"r        {de/en}crypt ROT13/47\n");
    fprintf(stderr,"v        Show this usage. V: show version\n");
    fprintf(stderr,"m[BQS0]  MIME decode [B:base64,Q:quoted,N:non-strict,0:no decode]\n");
    fprintf(stderr,"M[BQ]    MIME encode [B:base64 Q:quoted]\n");
    fprintf(stderr,"l        ISO8859-1 (Latin-1) support\n");
    fprintf(stderr,"f        Folding: -f60 or -f\n");
    fprintf(stderr,"Z[0-2]   Convert X0208 alphabet to ASCII  1: Kankaku to space,2: 2 spaces\n");
    fprintf(stderr,"X,x      Assume X0201 kana in MS-Kanji, -x preserves X0201\n");
    fprintf(stderr,"B[0-2]   Broken input  0: missing ESC,1: any X on ESC-[($]-X,2: ASCII on NL\n");
#ifdef MSDOS
    fprintf(stderr,"T        Text mode output\n");
#endif
    fprintf(stderr,"O        Output to File (DEFAULT 'nkf.out')\n");
    fprintf(stderr,"d,c      Delete \\r in line feed, Add \\r in line feed\n");
    fprintf(stderr,"-L[uwm]  line mode u:LF w:CRLF m:CR (DEFAULT noconversion)\n");
    fprintf(stderr,"long name options\n");
    fprintf(stderr," --fj,--unix,--mac,--windows         convert for the system\n");
    fprintf(stderr," --jis,--euc,--sjis,--mime,--base64  convert for the code\n");
    fprintf(stderr," --help,--version\n");
    version();
}

void
version()
{
    fprintf(stderr,"Network Kanji Filter Version %s (%s) "
#if defined(MSDOS) && !defined(_Windows)
                  "for DOS"
#endif
#if !defined(__WIN32__) && defined(_Windows)
                  "for Win16"
#endif
#if defined(__WIN32__) && defined(_Windows)
                  "for Win32"
#endif
#ifdef __OS2__
                  "for OS/2"
#endif
                  ,Version,Patchlevel);
    fprintf(stderr,"\n%s\n",CopyRight);
}
#endif

/**
 ** $B%Q%C%A@):n<T(B
 **  void@merope.pleiades.or.jp (Kusakabe Youichi)
 **  NIDE Naoyuki <nide@ics.nara-wu.ac.jp>
 **  ohta@src.ricoh.co.jp (Junn Ohta)
 **  inouet@strl.nhk.or.jp (Tomoyuki Inoue)
 **  kiri@pulser.win.or.jp (Tetsuaki Kiriyama)
 **  Kimihiko Sato <sato@sail.t.u-tokyo.ac.jp>
 **  a_kuroe@kuroe.aoba.yokohama.jp (Akihiko Kuroe)
 **  kono@ie.u-ryukyu.ac.jp (Shinji Kono)
 **  GHG00637@nifty-serve.or.jp (COW)
 **
 ** $B:G=*99?7F|(B
 **  1998.11.12
 **/

/* end */
