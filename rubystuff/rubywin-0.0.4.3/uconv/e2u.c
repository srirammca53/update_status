/*
 * Unicode Conversion Library (EUC-JP to UCS2)
 * 1997-1999 by yoshidam
 *
 */

#ifdef USE_EUC

#include <string.h>
#include "uconv.h"
#include "e2u.h"
#include "hojo2u.h"
#include "ustring.h"

#if 0
/* Convert EUC-JP into UCS2-little */
int
e2u_conv(const unsigned char* e, unsigned char* u)
{
  int i;
  int ui = 0;
  int len = strlen(e);

  for (i = 0; i < len; i++) {
    if (e[i] < 128) {	/* ASCII */
      u[ui++] = e[i];
      u[ui++] = 0;
    }
    else if (e[i] == 0x8e) { /* JIS X 0201 kana */
      u[ui++] = e[i + 1] - 0x40;
      u[ui++] = 0xff;
      i++;
    }
    else if (e[i] == 0x8f) { /* JIS X 0212 */
      int hi = e[i + 1] &  0x7f;
      int low = e[i + 2] &  0x7f;
      int key = (hi - 32) * 96 + (low - 32);
      unsigned short ec = hojo2u_tbl[key];
      u[ui++] = ec & 0xff;
      u[ui++] = ec >> 8;
      i++;
    }
    else if (e[i] < 0xa0) {  /* C1 */
    }
    else {		     /* JIX X 0208 */
      int hi = e[i] &  0x7f;
      int low = e[i + 1] &  0x7f;
      int key = (hi - 32) * 96 + (low - 32);
      unsigned short ec = e2u_tbl[key];
      u[ui++] = ec & 0xff;
      u[ui++] = ec >> 8;
      i++;
    }
  }

  return ui;
}
#endif

int e2u_conv2(const unsigned char* e, UString* u, unknown_euc unknown_e_conv)
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
	if (unknown_e_conv != NULL) {
	  unsigned char ue[4];
	  ue[0] = e[i]; ue[1] = e[i+1]; ue[2] = e[i+2]; ue[3] = 0;
	  ec = unknown_e_conv(ue);
	}
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
	if (unknown_e_conv != NULL) {
	  unsigned char ue[3];
	  ue[0] = e[i]; ue[1] = e[i+1]; ue[2] = 0;
	  ec = unknown_e_conv(ue);
	}
      }
      UStr_addChar2(u, ec & 0xff, ec >> 8);
      i++;
    }
  }

  return u->len;
}

#if 0
unsigned short
conv(unsigned char* e)
{
  return '?';
}

int
main(void)
{
  UString u;
  e2u_conv2("Abc¤¢¤¤¤¦", &u, conv);
  UStr_dump(&u);
  return 0;
}
#endif

#endif /* USE_EUC */
