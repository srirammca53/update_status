/*
 * Unicode Conversion Library (UCS2 to EUC-JP)
 * 1997-1998 by yoshidam
 *
 */
/*
 * Modified for RubyWin by Masaki Suketa
 */

#include <string.h>
#include <stdlib.h>
#include "rwuconv.h"
#include "u8tou16.h"
#include "u2e.h"
#include "ustring.h"

int u8toeuc(const unsigned char* u, UString *s) {
  UString out;
  u8tou16(u, &out);
  int len = u2e_conv2(out.str, out.len, s);
  UStr_free(&out);
  return len;
}

int
u2e_conv2(const unsigned char* u, int len, UString* e)
{
  int i;

  UStr_alloc(e);

  for (i = 0; i < len; i+=2) {
    unsigned short echar = u2e_tbl[u[i] | (u[i+1] << 8)];
    if (echar == 0) { /* Unknown char */
	UStr_addChar(e, '?');
    }
    else if (echar < 128) { /* ASCII */
      UStr_addChar(e, echar);
    }
    else if (echar > 0xa0 && echar <= 0xdf) { /* JIS X 0201 kana */
      UStr_addChar2(e, 0x8e, echar & 0xff);
    }
    else if (echar >= 0x2121 && echar <= 0x6d63) { /* JIS X 0212 */
      UStr_addChar3(e, 0x8f, (echar >> 8) | 0x80, (echar & 0xff) | 0x80);
    }
    else if (echar != 0xffff) { /* JIS X 0208 */
      UStr_addChar2(e, echar >> 8, echar & 0xff);
    }
  }

  return e->len;
}

