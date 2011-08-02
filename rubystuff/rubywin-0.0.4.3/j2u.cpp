#include "ruby.h"
#include <string.h>
#include "rwuconv.h"
#include "u16tou8.h"
#include "s2u.h"
#include "nkf.h"
#include "ustring.h"

int 
jistou8(const unsigned char * j, UString *u)
{
  UString in;
  VALUE sjis;
  sjis = rw_nkf_jis2sjis((unsigned char*)j, strlen((char*)j));
  unsigned char * s = (unsigned char *)STR2CSTR(sjis);

  s2u_conv2(s, &in);
  int len = u16tou8(in.str, in.len, u, 1);

  UStr_free(&in);
  return len;
}
