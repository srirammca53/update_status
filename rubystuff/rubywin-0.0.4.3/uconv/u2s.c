/*
 * Unicode Conversion Library (UCS2 to Shift_JIS)
 * 1999 by yoshidam
 *
 */

#ifdef USE_SJIS

#include <string.h>
#include <stdlib.h>
#include "uconv.h"
#ifdef USE_WIN32API
#  include <windows.h>
#  define SJIS_CODEPAGE 932
#else
#  include "u2s.h"
#endif
#include "ustring.h"


#ifdef USE_WIN32API
int
u2s_conv2(const unsigned char* u, int len, UString* s,
	  unknown_unicode unknown_u_conv)
{
  int i;

  UStr_alloc(s);

  for (i = 0; i < len; i+=2) {
    unsigned char str[3];
    int slen = WideCharToMultiByte(SJIS_CODEPAGE, 0,
				   (LPCWSTR)(u + i), 1, str, 3,
				   "\xff", NULL);

    if (slen == 1 && str[0] == (unsigned char)'\xff') { /* Unknown char */
      if (unknown_u_conv != NULL) {
	unsigned char* us = unknown_u_conv(u[i] | (u[i+1] << 8));
	int len = strlen((char*)us);
	UStr_addChars(s, us, len);
	free(us);
      }
      else {
	UStr_addChar(s, '?');
      }
    }
    else if (slen == 1) {
      UStr_addChar(s, str[0]);
    }
    else if (slen == 2) {
      UStr_addChar2(s, str[0], str[1]);
    }
    else {
      if (unknown_u_conv != NULL) {
	unsigned char* us = unknown_u_conv(u[i] | (u[i+1] << 8));
	int len = strlen((char*)us);
	UStr_addChars(s, us, len);
	free(us);
      }
      else {
	UStr_addChar(s, '?');
      }
    }
  }

  return s->len;
}
#else
int
u2s_conv2(const unsigned char* u, int len, UString* s,
	  unknown_unicode unknown_u_conv)
{
  int i;

  UStr_alloc(s);

  for (i = 0; i < len; i+=2) {
    unsigned short schar = u2s_tbl[u[i] | (u[i+1] << 8)];
    if (schar == 0) { /* Unknown char */
      if (unknown_u_conv != NULL) {
	unsigned char* us = unknown_u_conv(u[i] | (u[i+1] << 8));
	int len = strlen((char*)us);
	UStr_addChars(s, us, len);
	free(us);
      }
      else {
	UStr_addChar(s, '?');
      }
    }
    else if (schar < 128) { /* ASCII */
      UStr_addChar(s, schar);
    }
    else if (schar > 0xa0 && schar <= 0xdf) { /* JIS X 0201 kana */
      UStr_addChar(s, schar);
    }
    else if (schar >= 0x8140 && schar != 0xffff) { /* JIS X 0208 */
      UStr_addChar2(s, schar >> 8, schar & 0xff);
    }
    else {
      if (unknown_u_conv != NULL) {
	unsigned char* us = unknown_u_conv(u[i] | (u[i+1] << 8));
	int len = strlen((char*)us);
	UStr_addChars(s, us, len);
	free(us);
      }
      else {
	UStr_addChar(s, '?');
      }
    }
  }

  return s->len;
}
#endif

#if 0
unsigned char*
conv(unsigned short u)
{
  unsigned char* ret = malloc(3);
  strcpy(ret, "??");
  return ret;
}

int
main(void)
{
  UString s;
  u2s_conv2("\x42\x30\x44\x30\0\0", 4, &s, conv);
  UStr_dump(&s);
  return 0;
}
#endif

#endif /* USE_SJIS */
