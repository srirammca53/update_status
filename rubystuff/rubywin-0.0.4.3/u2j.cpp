#include "ruby.h"
#include <string.h>
#include "rwcommon.h"
#include "rwuconv.h"
#include "u8tou16.h"
#include "u2s.h"
#include "nkf.h"
#include "ustring.h"

int
u8tojis(const unsigned char * u, UString *j)
{
  UString out, s;
  u8tou16(u, &out);
  u2s_conv2(out.str, out.len, &s);
  VALUE jstr = rw_nkf_sjis2jis(s.str, s.len);
  UStr_alloc(j);
  UStr_addChars(j, (unsigned char *)STR2CSTR(jstr), RSTRING(jstr)->len);
  UStr_free(&out);
  UStr_free(&s);
  return j->len;
}
