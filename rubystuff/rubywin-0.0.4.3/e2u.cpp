/*
 * Unicode Conversion Library (EUC-JP to UCS2)
 * 1997-1999 by yoshidam
 *
 */

/*
 * Modified for RubyWin by Masaki Suketa
 */

#include <string.h>
#include "rwuconv.h"
#include "u16tou8.h"
#include "e2u.h"
#include "hojo2u.h"
#include "ustring.h"

int
euctou8(const unsigned char * e, UString *u)
{
  UString in;

  e2u_conv2(e, &in);
  int len = u16tou8(in.str, in.len, u, 1);

  UStr_free(&in);
  return len;

}

int e2u_conv2(const unsigned char* e, UString* u)
{
  int i;
  int len = strlen((char*)e);

  UStr_alloc(u);

  for (i = 0; i < len; i++) {
    if (e[i] < 128) {	/* ASCII */
      UStr_addChar2(u, e[i], 0);
    }
    else if (e[i] == 0x8e) { /* JIS X 0201 kana */
      unsigned char ec = 0;
      if (e[i + 1] >= 0xa1 && e[i + 1] <= 0xdf)
	ec = e[i + 1] - 0x40;
      UStr_addChar2(u, ec, 0xff);
      i++;
    }
    else if (e[i] == 0x8f) { /* JIS X 0212 */
      int hi = e[i + 1] &  0x7f;
      int low = e[i + 2] &  0x7f;
      int key = (hi - 32) * 96 + (low - 32);
      unsigned short ec = 0;
      if (hi >= 32 && hi <= 127 && low >= 32 && low <= 127)
	ec = hojo2u_tbl[key];
      if (ec == 0) {
	ec = '?';
      }
      UStr_addChar2(u, ec & 0xff, ec >> 8);
      i += 2;
    }
    else if (e[i] < 0xa0) {  /* C1 */
    }
    else {		     /* JIX X 0208 */
      int hi = e[i] &  0x7f;
      int low = e[i + 1] &  0x7f;
      int key = (hi - 32) * 96 + (low - 32);
      unsigned short ec = 0;
      if (hi >= 32 && hi <= 127 && low >= 32 && low <= 127)
	ec = e2u_tbl[key];
      if (ec == 0) {
	ec = '?';
      }
      UStr_addChar2(u, ec & 0xff, ec >> 8);
      i++;
    }
  }

  return u->len;
}

