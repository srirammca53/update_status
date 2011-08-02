/*******************************************************************************
 * vi:ts=4:sw=4
 *	original Ogasawara Hiroyuki (COR.)
 *  original Atsushi Nakamura
 ******************************************************************************/
/*
  Modified for RubyWin by Masaki Suketa
  */
#include "judge_jcode.h"

# include <windows.h>
int p_cpage = 932;
static unsigned char	kanji_map_sjis[]= {
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	0,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
	2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0
};

static int ISkanji(int code){
    if (code >= 0x100)
        return 0;
    return(kanji_map_sjis[code & 0xff] & 1);
}

static int judge_sjis_euc(const unsigned char	*ptr) {
    if (((0xa1 <= ptr[0] && ptr[0] <= 0xfe)
         && (0xa1 <= ptr[1] && ptr[1] <= 0xfe))
        || (ptr[0] == 0x8e && (0xa1 <= ptr[1] && ptr[1] <= 0xdf))
        || (ptr[0] == 0x8f && (0xa1 <= ptr[1] && ptr[1] <= 0xfe)))
        return(TRUE);/* EUC */
    else if ((((0x81 <= ptr[0] && ptr[0] <= 0x9f)
               || (0xe0 <= ptr[0] && ptr[0] <= 0xef))
              && ((0x40 <= ptr[1] && ptr[1] <= 0x7e)
                  || (0x80 <= ptr[1] && ptr[1] <= 0xfc)))
             || (0xa1 <= ptr[0] && ptr[0] <= 0xdf))
        return(TRUE);/* SJIS */
    return(FALSE);
}

static int wide2multi(
    unsigned char	*ptr,
    int			size,
    int			ubig,
    int			first
    ){
    unsigned char	*	p = ptr;
    unsigned char		buf[2];
    int			len;
    int			total = 0;
    int			i;

    if (first)	{
        p += 2;
        size -= 2;
    }
    for (i = 0; i < size; i += 2){
        if (ubig){
            buf[0]	= p[0];
            p[0]	= p[1];
            p[1]	= buf[0];
        }
        len = WideCharToMultiByte(p_cpage, WC_COMPOSITECHECK, (LPCWSTR)p, 1, (LPSTR)buf, 2, NULL, NULL);
        memmove((char *)&ptr[total], buf, len);
        p += 2;
        total += len;
    }
    return(total);
}

static int judge_ucs(const unsigned char *ptr){
    unsigned short	ucs;
    unsigned char	dst[2];

    if (ptr[0] < 0xe0)
        ucs = ((ptr[0] & 0x1f) << 6) | (ptr[1] & 0x3f);
    else
        ucs = ((ptr[0] & 0x0f) << 12) | ((ptr[1] & 0x3f) << 6) | (ptr[2] & 0x3f);
    dst[1] = ucs & 255;
    dst[0] = ucs >> 8;
    if (wide2multi(dst, 2, TRUE, FALSE) == 1 && dst[0] == '?')
        return(FALSE);
    return(TRUE);
}


int judge_jcode(
    unsigned char*	origcode,
    int		*	ubig,
    const unsigned char*	ptr,
    long		size
    ){
    char code;
    int	i;
    int	bfr  = FALSE;	/* Kana Moji */
    int	bfk  = 0;		/* EUC Kana */
    int	sjis = 0;
    int	euc  = 0;
    int	utf8 = 0;
    int	bfu  = 0;

    code = '\0';
    if ((ptr[0] == 0xff && ptr[1] == 0xfe)
        || (ptr[0] == 0xfe && ptr[1] == 0xff)) {
        if (ptr[0] == 0xfe && ptr[1] == 0xff)
            *ubig = TRUE;
        else
            *ubig = FALSE;
        code = 'U';		/* UNICODE */
        goto breakBreak;
    }
    if (ptr[0] == 0xef && ptr[1] == 0xbb && ptr[2] == 0xbf){
        code = 'T';		/* MS UTF8 */
        goto breakBreak;
    }
    if (*origcode == 'U')
        *origcode = 'S';

    /* valid UTF-8 or not */
    i = 0;
    while (i < size) {
        if (ptr[i] < 0x80)
            i++;
        else if (ptr[i] < 0xc0) {
            /* malformed */
            utf8 = 0;
            break;
        }
        else if (ptr[i] < 0xe0) {
            if (size - i > 1) {
                if (ptr[i + 1] >= 0x80 && ptr[i + 1] < 0xc0) {
                    if (judge_sjis_euc(&ptr[i]))
                        ;
                    else if (judge_ucs(&ptr[i]))
                        utf8++;
                }
                else {
                    /* malformed */
                    utf8 = 0;
                    break;
                }
            }
            i += 2;
        }
        else if (ptr[i] < 0xf0) {
            if (size - i > 2) {
                if (ptr[i + 1] >= 0x80 && ptr[i + 1] < 0xc0
                    && ptr[i + 2] >= 0x80 && ptr[i + 2] < 0xc0)	{
                    if (judge_sjis_euc(&ptr[i]))
                        ;
                    else if (judge_ucs(&ptr[i]))
                        utf8++;
                }
                else {
                    /* malformed */
                    utf8 = 0;
                    break;
                }
            }
            i += 3;
        }
        else if (ptr[i] < 0xf8) {
            /* valid but not supported */
            if (size - i > 3) {
                if (!(ptr[i + 1] >= 0x80 && ptr[i + 1] < 0xc0
                      && ptr[i + 2] >= 0x80 && ptr[i + 2] < 0xc0
                      && ptr[i + 3] >= 0x80 && ptr[i + 3] < 0xc0)) {
                    /* malformed */
                    utf8 = 0;
                    break;
                }
            }
            i += 4;
        }
        else if (ptr[i] < 0xfc)	{
            /* valid but not supported */
            if (size - i > 4) {
                if (!(ptr[i + 1] >= 0x80 && ptr[i + 1] < 0xc0
                      && ptr[i + 2] >= 0x80 && ptr[i + 2] < 0xc0
                      && ptr[i + 3] >= 0x80 && ptr[i + 3] < 0xc0
                      && ptr[i + 4] >= 0x80 && ptr[i + 4] < 0xc0)){
                    /* malformed */
                    utf8 = 0;
                    break;
                }
            }
            i += 5;
        }
        else if (ptr[i] < 0xfe)	{
            /* valid but not supported */
            if (size - i > 5) {
                if (!(ptr[i + 1] >= 0x80 && ptr[i + 1] < 0xc0
                      && ptr[i + 2] >= 0x80 && ptr[i + 2] < 0xc0
                      && ptr[i + 3] >= 0x80 && ptr[i + 3] < 0xc0
                      && ptr[i + 4] >= 0x80 && ptr[i + 4] < 0xc0
                      && ptr[i + 5] >= 0x80 && ptr[i + 5] < 0xc0)){
                    /* malformed */
                    utf8 = 0;
                    break;
                }
            }
            i += 6;
        }
        else{
            /* malformed */
            utf8 = 0;
            break;
        }
    }
    if (utf8 > 1){
        code = 'T';
        goto breakBreak;
    }
    i = 0;
    while (i < size) {
        if (ptr[i] == '\033' && (size - i >= 3)){
            if ((ptr[i+1] == '$' && ptr[i+2] == 'B')
                || (ptr[i+1] == '(' && ptr[i+2] == 'B')){
                code = 'J';
                goto breakBreak;
            }
            else if ((ptr[i+1] == '$' && ptr[i+2] == '@')
                     || (ptr[i+1] == '(' && ptr[i+2] == 'J')) {
                code = 'J';
                goto breakBreak;
            }
            else if (ptr[i+1] == '(' && ptr[i+2] == 'I'){
                code = 'J';
                i += 3;
            }
            else if (ptr[i+1] == ')' && ptr[i+2] == 'I'){
                code = 'J';
                i += 3;
            }
            else
                i++;
            bfr = FALSE;
            bfk = 0;
        }
        else{
            if (ptr[i] < 0x20){
                if (bfr == TRUE){
                    code = 'S';
                    goto breakBreak;
                }
                bfr = FALSE;
                bfk = 0;
                /* ?? check kudokuten ?? && ?? hiragana ?? */
                if ((i >= 2) && (ptr[i-2] == 0x81)
                    && (0x41 <= ptr[i-1] && ptr[i-1] <= 0x49)) {
                    code = 'S';
                    sjis += 100;	/* kudokuten */
                }
                else if ((i >= 2) && (ptr[i-2] == 0xa1)
                         && (0xa2 <= ptr[i-1] && ptr[i-1] <= 0xaa)){
                    code = 'E';
                    euc  += 100;	/* kudokuten */
                }
                else if ((i >= 2) && (ptr[i-2] == 0x82) && (0xa0 <= ptr[i-1]))
                    sjis += 40;		/* hiragana */
                else if ((i >= 2) && (ptr[i-2] == 0xa4) && (0xa0 <= ptr[i-1]))
                    euc  += 40;		/* hiragana */
                else if ((0xa1 <= ptr[i-2] && ptr[i-2] <= 0xfe)
                         && (0xa1 <= ptr[i-1] && ptr[i-1] <= 0xfe))
                    ;	/* EUC */
                else if (0x8e == ptr[i-2]
                         && (0xa1 <= ptr[i-1] && ptr[i-1] <= 0xdf))
                    ;	/* EUC */
                else if (((0x81 <= ptr[i-2] && ptr[i-2] <= 0x9f)
                          || (0xe0 <= ptr[i-2] && ptr[i-2] <= 0xef))
                         && ((0x40 <= ptr[i-1] && ptr[i-1] <= 0x7e)
                             || (0x80 <= ptr[i-1] && ptr[i-1] <= 0xfc)))
                    ;	/* SJIS */
                else if ((i >= 3) && (ptr[i-3] & 0xf0) == 0xe0
                         && (ptr[i-2] & 0xc0) == 0x80
                         && (ptr[i-1] & 0xc0) == 0x80)	{
                    code = 'T';
                    utf8  += 30;
                }
                else if ((i >= 2) && (ptr[i-2] & 0xe0) == 0xc0
                         && (ptr[i-1] & 0xc0) == 0x80)	{
                    code = 'T';
                    utf8  += 10;
                }
            }
            else{
                /* ?? check hiragana or katana ?? */
                if ((size - i > 1) && (ptr[i] == 0x82) && (0xa0 <= ptr[i+1]))
                    sjis++;	/* hiragana */
                else if ((size - i > 1) && (ptr[i] == 0x83)
                         && (0x40 <= ptr[i+1] && ptr[i+1] <= 0x9f))
                    sjis++;	/* katakana */
                else if ((size - i > 1) && (ptr[i] == 0xa4) && (0xa0 <= ptr[i+1]))
                    euc++;	/* hiragana */
                else if ((size - i > 1) && (ptr[i] == 0xa5) && (0xa0 <= ptr[i+1]))
                    euc++;	/* katakana */
                if (bfu)
                    bfu--;
                else
                    if (bfr == TRUE){
                        if ((i >= 1) && (0x40 <= ptr[i] && ptr[i] <= 0xa0) && ISkanji(ptr[i-1])){
                            code = 'S';
                            goto breakBreak;
                        }
                        else if ((i >= 1) && (0x81 <= ptr[i-1] && ptr[i-1] <= 0x9f) && ((0x40 <= ptr[i] && ptr[i] < 0x7e) || (0x7e < ptr[i] && ptr[i] <= 0xfc))){
                            code = 'S';
                            goto breakBreak;
                        }
                        else if ((i >= 1) && (0xfd <= ptr[i] && ptr[i] <= 0xfe) && (0xa1 <= ptr[i-1] && ptr[i-1] <= 0xfe)){
                            code = 'E';
                            goto breakBreak;
                        }
                        else if ((i >= 1) && (0xfd <= ptr[i-1] && ptr[i-1] <= 0xfe) && (0xa1 <= ptr[i] && ptr[i] <= 0xfe)){
                            code = 'E';
                            goto breakBreak;
                        }
                        else if ((i >= 1) && (ptr[i] < 0xa0 || 0xdf < ptr[i]) && (0x8e == ptr[i-1])){
                            code = 'S';
                            goto breakBreak;
                        }
                        else if (ptr[i] <= 0x7f){
                            code = 'S';
                            goto breakBreak;
                        }
                        else{
                            if (0xa1 <= ptr[i] && ptr[i] <= 0xa6)
                                euc++;	/* sjis hankaku kana kigo */
                            else if (0xa1 <= ptr[i] && ptr[i] <= 0xdf)
                                ;	/* sjis hankaku kana */
                            else if (0xa1 <= ptr[i] && ptr[i] <= 0xfe)
                                euc++;
                            else if (0x8e == ptr[i])
                                euc++;
                            else if (0x20 <= ptr[i] && ptr[i] <= 0x7f)
                                sjis++;
                            bfr = FALSE;
                            bfk = 0;
                        }
                    }
                    else if ((size - i > 3) && (ptr[i] & 0xf0) == 0xe0
                             && (ptr[i+1] & 0xc0) == 0x80
                             && (ptr[i+2] & 0xc0) == 0x80
                             && ((ptr[i+3] & 0x80) == 0x00
                                 || (ptr[i+3] & 0xf0) == 0xe0
                                 || (ptr[i+3] & 0xe0) == 0xc0)
                             && !((0xa1 <= ptr[i] && ptr[i] <= 0xfe)
                                  && (0xa1 <= ptr[i+1] && ptr[i+1] <= 0xfe)
                                  && (0xa1 <= ptr[i+2] && ptr[i+2] <= 0xfe))){
                        utf8++;
                        bfu = 2;
                        bfk = 0;
                    }
                    else if ((size - i > 2) && (ptr[i] & 0xe0) == 0xc0
                             && (ptr[i+1] & 0xc0) == 0x80
                             && ((ptr[i+2] & 0x80) == 0x00
                                 || (ptr[i+2] & 0xf0) == 0xe0
                                 || (ptr[i+2] & 0xe0) == 0xc0)
                             && !((0xa1 <= ptr[i] && ptr[i] <= 0xfe)
                                  && (0xa1 <= ptr[i+1] && ptr[i+1] <= 0xfe))){
                        utf8++;
                        bfu = 1;
                        bfk = 0;
                    }
                    else if (0x8e == ptr[i]) {
                        if (size - i <= 1)
                            ;
                        else if (0xa1 <= ptr[i+1] && ptr[i+1] <= 0xdf) {
                            /* EUC KANA or SJIS KANJI */
                            if (bfk == 1)
                                euc += 100;
                            bfk++;
                            i++;
                        }
                        else{
                            /* SJIS only */
                            code = 'S';
                            goto breakBreak;
                        }
                    }
                    else if (0x8f == ptr[i]) {
                        if (size - i <= 2)
                            ;
                        else if ((0xa1 <= ptr[i+1] && ptr[i+1] <= 0xfe)
                                 && (0xa1 <= ptr[i+2] && ptr[i+2] <= 0xfe)){
                            euc += 10;
                            i += 2;
                        }
                        else{
                            /* SJIS only */
                            code = 'S';
                            goto breakBreak;
                        }
                    }
                    else if (0x81 <= ptr[i] && ptr[i] <= 0x9f){
                        /* SJIS only */
                        code = 'S';
                        if ((size - i >= 1)
                            && ((0x40 <= ptr[i+1] && ptr[i+1] <= 0x7e)
                                || (0x80 <= ptr[i+1] && ptr[i+1] <= 0xfc)))
                            goto breakBreak;
                    }
                    else if (0xfd <= ptr[i] && ptr[i] <= 0xfe) {
                        /* EUC only */
                        code = 'E';
                        if ((size - i >= 1)
                            && (0xa1 <= ptr[i+1] && ptr[i+1] <= 0xfe))
                            goto breakBreak;
                    }
                    else if (ptr[i] <= 0x7f)
                        ;
                    else{
                        bfr = TRUE;
                        bfk = 0;
                    }
            }
            i++;
        }
    }
    if (code == '\0') {
        code = *origcode;
        if (utf8 > sjis && utf8 > euc)
            code = 'T';
        else
            if (sjis > euc)
                code = 'S';
            else if (sjis < euc)
                code = 'E';
    }
breakBreak:
    return(code);
}

