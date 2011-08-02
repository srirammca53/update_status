/*
 * Unicode Conversion Library (Shift_JIS to UCS2)
 * 1999 by yoshidam
 *
 */

/*
 * Modified for RubyWin by Masaki Suketa
 */
#include <windows.h>

#include <string.h>
#include "rwuconv.h"
#include "u16tou8.h"
#include "s2u.h"
#include "ustring.h"

int sjistou8(
    const unsigned char* s, 
    UString* u
    ) {
    UString in;
    s2u_conv2(s, &in);
    int len =  u16tou8(in.str, in.len, u, 1);
    UStr_free(&in);
    return len;
}

int s2u_conv2(const unsigned char* s, UString* u)
{
  int len = strlen((char*)s);
  int ulen;

  UStr_alloc(u);

  /* check converted string length */
  ulen = MultiByteToWideChar(SJIS_CODEPAGE, MB_PRECOMPOSED, 
                             reinterpret_cast<const CHAR*>(s), len, NULL, 0);

  UStr_enlarge(u, ulen * 2);
  ulen = MultiByteToWideChar(SJIS_CODEPAGE, MB_PRECOMPOSED, 
                             reinterpret_cast<const CHAR*>(s), len,
			     (LPWSTR)u->str, ulen);
  u->len = ulen * 2;
  return u->len;
}

