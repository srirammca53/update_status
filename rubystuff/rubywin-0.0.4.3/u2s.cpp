/*
 * Unicode Conversion Library (UCS2 to Shift_JIS)
 * 1999 by yoshidam
 *
 */

/*
 * Modified for RubyWin by Masaki Suketa
 */

#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include "rwuconv.h"
#include "u2s.h"
#include "u8tou16.h"
#include "ustring.h"

int u8tosjis(const unsigned char* u, UString *s) {
  UString out;
  u8tou16(u, &out);
  int len = u2s_conv2(out.str, out.len, s);
  UStr_free(&out);
  return len;
}

int
u2s_conv2(const unsigned char* u, int len, UString* s)
{
  int i;

  UStr_alloc(s);

  for (i = 0; i < len; i+=2) {
    unsigned char str[3];
    int slen = WideCharToMultiByte(SJIS_CODEPAGE, 0,
				   (LPCWSTR)(u + i), 1, 
                                   reinterpret_cast<CHAR*>(str), 3,
				   "\xff", NULL);

    if (slen == 1 && str[0] == (unsigned char)'\xff') { /* Unknown char */
      UStr_addChar(s, '?');
    }
    else if (slen == 1) {
      UStr_addChar(s, str[0]);
    }
    else if (slen == 2) {
      UStr_addChar2(s, str[0], str[1]);
    }
    else {
      UStr_addChar(s, '?');
    }
  }

  return s->len;
}

