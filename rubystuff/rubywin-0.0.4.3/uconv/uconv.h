/*
 * Unicode Conversion Library
 * 1997-1998 by yoshidam
 *
 */

#ifndef _UCONV_H
#define _UCONV_H

#include "ustring.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned char* (unknown_unicode)(unsigned short);
typedef unsigned short (unknown_euc)(const unsigned char*);
typedef unsigned short (unknown_sjis)(const unsigned char*);


int u2e_conv(const unsigned char* u, unsigned char* e, int len);
int u2e_conv2(const unsigned char* u, int len, UString* e,
	      unknown_unicode unknown_u_conv);
int u2s_conv2(const unsigned char* u, int len, UString* s,
	      unknown_unicode unknown_u_conv);

int e2u_conv(const unsigned char* e, unsigned char* u);
int e2u_conv2(const unsigned char* e, UString* u,
	      unknown_euc unknown_e_conv);
int s2u_conv2(const unsigned char* s, UString* u,
	      unknown_sjis unknown_s_conv);

unsigned short sjis2euc(unsigned short sjis);
unsigned short euc2sjis(unsigned short euc);


#ifdef __cplusplus
}
#endif

#endif
