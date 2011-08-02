/*
 * Unicode Conversion Library (Shift_JIS to UCS2)
 * 1999 by yoshidam
 *
 */

#ifdef USE_SJIS

#include <string.h>
#include "uconv.h"
#ifdef USE_WIN32API
#  include <windows.h>
#  define SJIS_CODEPAGE 932
#else
#  include "s2u.h"
#endif
#include "ustring.h"

#ifdef USE_WIN32API
int s2u_conv2(const unsigned char* s, UString* u, unknown_sjis unknown_s_conv)
{
  int len = strlen((char*)s);
  int ulen;

  UStr_alloc(u);

  /* check converted string length */
  ulen = MultiByteToWideChar(SJIS_CODEPAGE, MB_PRECOMPOSED, s, len, NULL, 0);

  UStr_enlarge(u, ulen * 2);
  ulen = MultiByteToWideChar(SJIS_CODEPAGE, MB_PRECOMPOSED, s, len,
			     (LPWSTR)u->str, ulen);
  u->len = ulen * 2;
  return u->len;
}
#else
int s2u_conv2(const unsigned char* s, UString* u, unknown_sjis unknown_s_conv)
{
  int i;
  int len = strlen((char*)s);

  UStr_alloc(u);

  for (i = 0; i < len; i++) {
    if (s[i] < 128) {	/* ASCII */
      UStr_addChar2(u, s[i], 0);
    }
    else if (s[i] >= 0xa0 && s[i] <= 0xdf) { /* JIS X 0201 kana */
      UStr_addChar2(u, s[i] - 0x40, 0xff);
    }
    else if (s[i] <= 0xfc && s[i + 1] >= 0x40 && s[i + 1] <= 0xfc) {
                                             /* JIX X 0208 */
      int hi = s[i];
      int low = s[i + 1];
      int key;
      unsigned short sc = 0;

      if (hi >= 0xe0)
	key = (hi - 0xc1)*188;
      else
	key = (hi - 0x81)*188;
      if (low >= 0x80)
	key += low - 0x41;
      else
	key += low - 0x40;
      if (key < 11280)
	sc = s2u_tbl[key];
      if (sc == 0) {
	sc = '?';
	if (unknown_s_conv != NULL) {
	  unsigned char us[3];
	  us[0] = s[i]; us[1] = s[i+1]; us[2] = 0;
	  sc = unknown_s_conv(us);
	}
      }
      UStr_addChar2(u, sc & 0xff, sc >> 8);
      i++;
    }
    else { /* Illegal sequence */
      unsigned short sc = '?';
      if (unknown_s_conv != NULL) {
	unsigned char us[2];
	us[0] = s[i]; us[1] = 0;
	sc = unknown_s_conv(us);
      }
      UStr_addChar2(u, sc & 0xff, sc >> 8);
    }
  }

  return u->len;
}
#endif

#if 0
unsigned short
conv(const unsigned char* s)
{
  return '?';
}

int
main(void)
{
  UString u;
  s2u_conv2("Abc\x82\xa0\x82\xa2\x82\xa4", &u, conv);
  UStr_dump(&u);
  return 0;
}
#endif

#endif /* USE_SJIS */
