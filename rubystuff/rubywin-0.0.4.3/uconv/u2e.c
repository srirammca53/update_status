/*
 * Unicode Conversion Library (UCS2 to EUC-JP)
 * 1997-1998 by yoshidam
 *
 */

#ifdef USE_EUC

#include <string.h>
#include <stdlib.h>
#include "uconv.h"
#include "u2e.h"
#include "ustring.h"

#if 0
/* Convert UCS2-little into EUC-JP */
int
u2e_conv(const unsigned char* u, unsigned char* e, int len)
{
  int i;
  int ei;

  e[0] = '\0';

  for (i = 0, ei = 0; i < len; i+=2) {
    unsigned short echar = u2e_tbl[u[i] | (u[i+1] << 8)];
    if (echar == 0) { /* Unknown char */
      e[ei++] = (unsigned char)'?';
    }
    else if (echar < 128) { /* ASCII */
      e[ei++] = (unsigned char)echar;
    }
    else if (echar > 0xa0 && echar <= 0xdf) { /* JIS X 0201 kana */
      e[ei++] = 0x8e;
      e[ei++] = echar & 0xff;
    }
    else if (echar >= 0x2121 && echar <= 0x6d63) { /* JIS X 0212 */
      e[ei++] = 0x8e;
      e[ei++] = (echar >> 8) | 0x80;
      e[ei++] = (echar & 0xff) | 0x80;
    }
    else if (echar != 0xffff) { /* JIS X 0208 */
      e[ei++] = echar >> 8;
      e[ei++] = echar & 0xff;
    }
  }
  e[ei] = '\0';

  return ei;
}
#endif

int
u2e_conv2(const unsigned char* u, int len, UString* e,
	  unknown_unicode unknown_u_conv)
{
  int i;

  UStr_alloc(e);

  for (i = 0; i < len; i+=2) {
    unsigned short echar = u2e_tbl[u[i] | (u[i+1] << 8)];
    if (echar == 0) { /* Unknown char */
      if (unknown_u_conv != NULL) {
	unsigned char* ue = unknown_u_conv(u[i] | (u[i+1] << 8));
	int len = strlen((char*)ue);
	UStr_addChars(e, ue, len);
	free(ue);
      }
      else {
	UStr_addChar(e, '?');
      }
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

#endif /* USE_EUC */
