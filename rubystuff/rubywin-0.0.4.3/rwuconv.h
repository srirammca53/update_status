/*
 * Unicode Conversion Library
 * 1997-1998 by yoshidam
 *
 */
/*
 * Modified for RubyWin by Masaki Suketa
 */
#ifndef _UCONV_H
#define _UCONV_H

#include "ustring.h"
#define SJIS_CODEPAGE 932
int s2u_conv2(const unsigned char* s, UString* u);
int u2s_conv2(const unsigned char* u, int len, UString* s);
int sjistou8(const unsigned char* s, UString* u);
int u8tosjis(const unsigned char* u, UString* s);

int e2u_conv2(const unsigned char* e, UString* u);
int u2e_conv2(const unsigned char* u, int len, UString* s);
int euctou8(const unsigned char* e, UString* u);
int u8toeuc(const unsigned char* u, UString* e);

int u8tojis(const unsigned char* u, UString* j);
int jistou8(const unsigned char* j, UString* u);

#endif
