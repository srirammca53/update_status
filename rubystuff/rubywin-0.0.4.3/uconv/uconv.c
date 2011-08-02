/*
 * uconv version 0.4.9
 * Dec 10, 2001 yoshidam  supports the tainted status
 * Nov 23, 2001 yoshidam  appends shortest_flag
 * Nov 24, 1999 yoshidam  appends eliminate_zwnbsp_flag
 * Nov  5, 1999 yoshidam  supports SJIS
 * Feb 22, 1999 yoshidam
 * Jul 24, 1998 yoshidam
 * Jun 30, 1998 yoshidam
 *
 */

#include "ruby.h"
#include "rubyio.h"
#include <stdio.h>
#include "uconv.h"
#include "ustring.h"

/*#define UTF32*/

#define REPLACEMENT_CHAR (0xFFFD)

static VALUE mUconv;

static int eliminate_zwnbsp_flag = 1;
static int shortest_flag = 1;
static int replace_invalid = 0;
static VALUE eUconvError;

/* Convert UTF-8 to UTF-16-LE (byte order: 21) */
static int
_u8tou16(unsigned char* in, UString* out)
{
  unsigned int u = 0;
  size_t inlen;

  UStr_alloc(out);
  inlen = strlen(in);
  while (inlen > 0) {
    unsigned char c = in[0];
    if ((c & 0x80) == 0) { /* 0b0nnnnnnn (7bit) */
      if (c == 0)
	rb_warn("input may not be UTF-8 text!");
      UStr_addChar2(out, c, 0);
      in++;
      inlen--;
    }
    else if ((c & 0xe0) == 0xc0 && /* 0b110nnnnn (11bit) */
	     inlen >= 2 &&
	     (in[1] & 0xc0) == 0x80) {
      if (shortest_flag && (c == 0xc0 || c == 0xc1)) {
	if (replace_invalid) {
	  UStr_addWCharToU16LE(out, replace_invalid);
	  in += 2;
	  inlen -= 2;
	  continue;
	}
	else
	  rb_raise(eUconvError, "non-shortest UTF-8 sequence (%02x)", c);
      }
      u = ((c & 31) << 6) | (in[1] & 63);
      UStr_addChar2(out, u & 0xff, u >> 8);
      in += 2;
      inlen -= 2;
    }
    else if ((c & 0xf0) == 0xe0 && /* 0b1110nnnn (16bit) */
	     inlen >= 3 &&
	     (in[1] & 0xc0) == 0x80 &&
	     (in[2] & 0xc0) == 0x80) {
      if (shortest_flag && c == 0xe0 && in[1] < 0xa0) {
	if (replace_invalid) {
	  UStr_addWCharToU16LE(out, replace_invalid);
	  in += 3;
	  inlen -= 3;
	  continue;
	}
	else
	  rb_raise(eUconvError, "non-shortest UTF-8 sequence (%02x)", c);
      }
      u = ((c & 15) << 12) | ((in[1] & 63) << 6) | (in[2] & 63);
      /* surrogate chars */
      if (u >= 0xd800 && u <= 0xdfff) {
	if (replace_invalid) {
	  UStr_addWCharToU16LE(out, replace_invalid);
	  in += 3;
	  inlen -= 3;
	  continue;
	}
	else
	  rb_raise(eUconvError, "none-UTF-16 char detected (%04x)", u);
      }
      UStr_addChar2(out, u & 0xff, u >> 8);
      in += 3;
      inlen -= 3;
    }
    else if ((c & 0xf8) == 0xf0 && /* 0b11110nnn (21bit) */
	     inlen >= 4 &&
	     (in[1] & 0xc0) == 0x80 &&
	     (in[2] & 0xc0) == 0x80 &&
	     (in[3] & 0xc0) == 0x80) {
      if (shortest_flag && c == 0xf0 && in[1] < 0x90) {
	if (replace_invalid) {
	  UStr_addWCharToU16LE(out, replace_invalid);
	  in += 4;
	  inlen -= 4;
	  continue;
	}
	else
	  rb_raise(eUconvError, "non-shortest UTF-8 sequence (%02x)", c);
      }
      u = ((c & 7) << 18) | ((in[1] & 63) << 12) |
	((in[2] & 63) << 6) | (in[3] & 63);
      if (u < 0x10000)
	UStr_addChar2(out, u & 255, u >> 8);
      else if (u < 0x110000) {
	unsigned int high = ((u - 0x10000) >> 10) | 0xd800;
	unsigned int low = (u & 1023) | 0xdc00;
	UStr_addChar4(out, high & 255, high >> 8, low & 255, low >> 8);
      }
      else {
	if (replace_invalid) {
	  UStr_addWCharToU16LE(out, replace_invalid);
	  in += 4;
	  inlen -= 4;
	  continue;
	}
	else
	  rb_raise(eUconvError, "none-UTF-16 char detected (%04x)", u);
      }
      //      UStr_addWCharToU16LE(out, u);
      in += 4;
      inlen -= 4;
    }
    else {
      if (replace_invalid) {
	UStr_addWCharToU16LE(out, replace_invalid);
	in++;
	inlen--;
      }
      else
	rb_raise(eUconvError, "illegal UTF-8 sequence (%02x)", c);
    }
  }

  return out->len;
}

/* Convert UTF-8 to UCS-4-LE (byte order: 4321) */
static int
_u8tou4(unsigned char* in, UString* out)
{
  unsigned int u = 0;
  size_t inlen;

  UStr_alloc(out);
  inlen = strlen(in);
  while (inlen > 0) {
    unsigned char c = in[0];
    if ((c & 0x80) == 0) { /* 0b0nnnnnnn (7bit) */
      if (c == 0)
	rb_warn("input may not be UTF-8 text!");
      UStr_addChar4(out, c, 0, 0, 0);
      in++;
      inlen--;
    }
    else if ((c & 0xe0) == 0xc0 && /* 0b110nnnnn (11bit) */
	     inlen >= 2 &&
	     (in[1] & 0xc0) == 0x80) {
      if (shortest_flag && (c == 0xc0 || c == 0xc1)) {
	if (replace_invalid) {
	  UStr_addWCharToU32LE(out, replace_invalid);
	  in += 2;
	  inlen -= 2;
	  continue;
	}
	else
	  rb_raise(eUconvError, "non-shortest UTF-8 sequence (%02x)", c);
      }
      u = ((c & 31) << 6) | (in[1] & 63);
      UStr_addChar4(out, u & 0xff, u >> 8, 0, 0);
      in += 2;
      inlen -= 2;
    }
    else if ((c & 0xf0) == 0xe0 && /* 0b1110nnnn (16bit) */
	     inlen >= 3 &&
	     (in[1] & 0xc0) == 0x80 &&
	     (in[2] & 0xc0) == 0x80) {
      if (shortest_flag && c == 0xe0 && in[1] < 0xa0) {
	if (replace_invalid) {
	  UStr_addWCharToU32LE(out, replace_invalid);
	  in += 3;
	  inlen -= 3;
	  continue;
	}
	else
	  rb_raise(eUconvError, "non-shortest UTF-8 sequence (%02x)", c);
      }
      u = ((c & 15) << 12) | ((in[1] & 63) << 6) | (in[2] & 63);
      /* surrogate chars */
      if (u >= 0xd800 && u <= 0xdfff) {
	if (replace_invalid) {
	  UStr_addWCharToU32LE(out, replace_invalid);
	  in += 3;
	  inlen -= 3;
	  continue;
	}
	else
	  rb_raise(eUconvError, "none-UTF-16 char detected (%04x)", u);
      }
      UStr_addChar4(out, u & 0xff, u >> 8, 0, 0);
      in += 3;
      inlen -= 3;
    }
    else if ((c & 0xf8) == 0xf0 && /* 0b11110nnn (21bit) */
	     inlen >= 4 &&
	     (in[1] & 0xc0) == 0x80 &&
	     (in[2] & 0xc0) == 0x80 &&
	     (in[3] & 0xc0) == 0x80) {
      if (shortest_flag && c == 0xf0 && in[1] < 0x90) {
	if (replace_invalid) {
	  UStr_addWCharToU32LE(out, replace_invalid);
	  in += 4;
	  inlen -= 4;
	  continue;
	}
	else
	  rb_raise(eUconvError, "non-shortest UTF-8 sequence (%02x)", c);
      }
      u = ((c & 7) << 18) | ((in[1] & 63) << 12) |
	((in[2] & 63) << 6) | (in[3] & 63);
#ifdef UTF32
      if (u < 0x110000) { /* UTF-32 ???? */
#endif /* UTF32 */
	UStr_addChar4(out, u & 0xff, (u >> 8) & 0xff,
		      (u >>16) & 0xff, u >> 24);
#ifdef UTF32
      }
      else {
	if (replace_invalid) {
	  UStr_addWCharToU32LE(out, replace_invalid);
	  in += 4;
	  inlen -= 4;
	  continue;
	}
	else
	  rb_raise(eUconvError, "none-UTF-16 char detected (%04x)", u);
      }
#endif /* UTF32 */
      in += 4;
      inlen -= 4;
    }
#ifndef UTF32
    else if ((c & 0xfc) == 0xf8 && /* 0b111110nn (26bit) */
	     inlen >= 5 &&
	     (in[1] & 0xc0) == 0x80 &&
	     (in[2] & 0xc0) == 0x80 &&
	     (in[3] & 0xc0) == 0x80 &&
	     (in[4] & 0xc0) == 0x80) {
      if (shortest_flag && c == 0xf8 && in[1] < 0x88) {
	if (replace_invalid) {
	  UStr_addWCharToU32LE(out, replace_invalid);
	  in += 5;
	  inlen -= 5;
	  continue;
	}
	else
	  rb_raise(eUconvError, "non-shortest UTF-8 sequence (%02x)", c);
      }
      u = ((c & 3) << 24) | ((in[1] & 63) << 18) |
	((in[2] & 63) << 12) | ((in[3] & 63) << 6) | (in[4] & 63);
      UStr_addChar4(out, u & 0xff, (u >> 8) & 0xff,
		    (u >>16) & 0xff, u >> 24);
      in += 5;
      inlen -= 5;
    }
    else if ((c & 0xfe) == 0xfc && /* 0b1111110n (31bit) */
	     inlen >= 6 &&
	     (in[1] & 0xc0) == 0x80 &&
	     (in[2] & 0xc0) == 0x80 &&
	     (in[3] & 0xc0) == 0x80 &&
	     (in[4] & 0xc0) == 0x80 &&
	     (in[5] & 0xc0) == 0x80) {
      if (shortest_flag && c == 0xfc && in[1] < 0x84) {
	if (replace_invalid) {
	  UStr_addWCharToU32LE(out, replace_invalid);
	  in += 6;
	  inlen -= 6;
	  continue;
	}
	else
	  rb_raise(eUconvError, "non-shortest UTF-8 sequence (%02x)", c);
      }
      u = ((c & 1) << 30) | ((in[1] & 63) << 24) |
	((in[2] & 63) << 18) | ((in[3] & 63) << 12) |
	((in[4] & 63) << 6) | (in[5] & 63);
      UStr_addChar4(out, u & 0xff, (u >> 8) & 0xff,
		    (u >>16) & 0xff, u >> 24);
      in += 6;
      inlen -= 6;
    }
#endif /* !UTF32 */
    else {
      if (replace_invalid) {
	UStr_addWCharToU32LE(out, replace_invalid);
	in++;
	inlen--;
      }
      else
	rb_raise(eUconvError, "illegal UTF-8 sequence (%02x)", c);
    }
  }

  return out->len;
}

/* Convert UTF-16-LE (byte order: 21) to UTF-8 */
static int
_u16tou8(unsigned char* in, int len, UString* out, int eliminate_zwnbsp)
{
  int i;

  UStr_alloc(out);

  if (len < 2) return 0;
  for (i = 0; i < len; i += 2) {
    unsigned int c = in[i] | (in[i+1] << 8);
    if (eliminate_zwnbsp && c == 0xfeff) { /* byte order mark */
      continue;
    }
    else if (c < 128) {         /* 0x0000-0x00FF */
      UStr_addChar(out, c);
    }
    else if (c < 2048) {        /* 0x0100-0x07FF */
      unsigned char b2 = c & 63;
      unsigned char b1 = c >> 6;
      UStr_addChar2(out, b1 | 192, b2 | 128);
    }
    else if (c >= 0xdc00 && c <= 0xdfff) { /* sole low surrogate */
      if (replace_invalid) {
	UStr_addWChar(out, replace_invalid);
	continue;
      }
      else
	rb_raise(eUconvError, "invalid surrogate detected");
    }
    else if (c >= 0xd800 && c <= 0xdbff) { /* high surrogate */
      unsigned int low;
      unsigned char b1, b2, b3, b4;
      if (i + 4 > len) { /* not enough length */
	if (replace_invalid) {
	  UStr_addWChar(out, replace_invalid);
	  continue;
	}
	else
	  rb_raise(eUconvError, "invalid surrogate detected");
      }
      low = in[i+2] | (in[i+3] << 8);
      if (low < 0xdc00 || low > 0xdfff) { /* not low surrogate */
	if (replace_invalid) {
	  UStr_addWChar(out, replace_invalid);
	  continue;
	}
	else
	  rb_raise(eUconvError, "invalid surrogate detected");
      }
      c = (((c & 1023)) << 10 | (low & 1023)) + 0x10000;
      b4 = c & 63;
      b3 = (c >> 6) & 63;
      b2 = (c >> 12) & 63;
      b1 = c >> 18;
      UStr_addChar4(out, b1 | 240, b2 | 128, b3 | 128, b4 | 128);
      i += 2;
    }
    else {                      /* 0x0800-0xFFFF */
      unsigned char b3 = c & 63;
      unsigned char b2 = (c >> 6) & 63;
      unsigned char b1 = c >> 12;
      UStr_addChar3(out, b1 | 224, b2 | 128, b3 | 128);
    }
  }

  return out->len;
}

/* Convert UCS-4-LE (byte order: 4321) to UTF-8 */
static int
_u4tou8(unsigned char* in, int len, UString* out, int eliminate_zwnbsp)
{
  int i;

  UStr_alloc(out);

  if (len < 4) return 0;
  for (i = 0; i < len; i += 4) {
    unsigned int c = in[i] | (in[i+1] << 8) |
                             (in[i+2] << 16) | (in[i+3] << 24);
    if (eliminate_zwnbsp && c == 0xfeff) { /* byte order mark */
      continue;
    }
    else if (c < 128) {         /* 0x0000-0x00FF */
      UStr_addChar(out, c);
    }
    else if (c < 2048) {        /* 0x0100-0x07FF */
      unsigned char b2 = c & 63;
      unsigned char b1 = c >> 6;
      UStr_addChar2(out, b1 | 192, b2 | 128);
    }
    else if (c >= 0xd800 && c <=0xdfff) { /* surrogate chars */
      if (replace_invalid) {
	UStr_addWChar(out, replace_invalid);
	continue;
      }
      else
	rb_raise(eUconvError, "illegal char detected (%04x)", c);
    }
    else if (c < 0x10000) {     /* 0x0800-0xFFFF */
      unsigned char b3 = c & 63;
      unsigned char b2 = (c >> 6) & 63;
      unsigned char b1 = c >> 12;
      UStr_addChar3(out, b1 | 224, b2 | 128, b3 | 128);
    }
#ifdef UTF32
    else if (c < 0x110000) {     /* 0x00010000-0x0010FFFF */
#else
    else if (c < 0x200000) {     /* 0x00010000-0x001FFFFF */
#endif
      unsigned char b4 = c & 63;
      unsigned char b3 = (c >> 6) & 63;
      unsigned char b2 = (c >> 12) & 63;
      unsigned char b1 = c >> 18;
      UStr_addChar4(out, b1 | 240, b2 | 128, b3 | 128, b4 | 128);
    }
#ifndef UTF32
    else if (c < 0x4000000) {     /* 0x00200000-0x03FFFFFF */
      unsigned char b5 = c & 63;
      unsigned char b4 = (c >> 6) & 63;
      unsigned char b3 = (c >> 12) & 63;
      unsigned char b2 = (c >> 18) & 63;
      unsigned char b1 = c >> 24;
      UStr_addChar5(out, b1 | 248, b2 | 128, b3 | 128, b4 | 128, b5 | 128);
    }
    else if (c < 0x80000000) {     /* 0x04000000-0x7FFFFFFF */
      unsigned char b6 = c & 63;
      unsigned char b5 = (c >> 6) & 63;
      unsigned char b4 = (c >> 12) & 63;
      unsigned char b3 = (c >> 18) & 63;
      unsigned char b2 = (c >> 24) & 63;
      unsigned char b1 = (c >> 30) & 63;
      UStr_addChar6(out, b1 | 252, b2 | 128, b3 | 128,
		b4 | 128, b5 | 128, b6 | 128);
    }
#endif /* !UTF32 */
    else {
      if (replace_invalid)
	UStr_addWChar(out, replace_invalid);
      else
	rb_raise(eUconvError, "non-UCS char detected");
    }
  }

  return out->len;
}

/* Convert UCS-4-LE (byte order: 4321) to UTF-16-LE (byte order: 21) */
/* 10000-10FFFF -> D800-DBFF:DC00-DFFF */
static int
_u4tou16(unsigned char* in, int len, UString* out)
{
  int i;

  UStr_alloc(out);

  if (len < 4) return 0;
  for (i = 0; i < len; i += 4) {
    unsigned int c = in[i] | (in[i+1] << 8) |
                             (in[i+2] << 16) | (in[i+3] << 24);
    if (c >= 0xd800 && c <= 0xdfff) { /* surrogate chars */
      if (replace_invalid) {
	UStr_addWCharToU16LE(out, replace_invalid);
	continue;
      }
      else
	rb_raise(eUconvError, "none-UTF-16 char detected (%04x)", c);
    }
    else if (c < 0x10000) {     /* 0x0000-0xFFFF */
      UStr_addChar2(out, in[i], in[i+1]);
    }
    else if (c < 0x110000) {    /* 0x00010000-0x0010FFFF */
      unsigned int high = ((c - 0x10000) >> 10) | 0xd800;
      unsigned int low = (c & 1023) | 0xdc00;
      UStr_addChar4(out, high & 255, high >> 8, low & 255, low >> 8);
    }
    else {
      if (replace_invalid) {
	UStr_addWCharToU16LE(out, replace_invalid);
	continue;
      }
      else
	rb_raise(eUconvError, "non-UTF-16 char detected");
    }
  }

  return out->len;
}

/* Convert UTF-16-LE (byte order: 21) to UCS-4-LE (byte order: 4321) */
/* D800-DBFF:DC00-DFFF -> 10000-10FFFF */
static int
_u16tou4(unsigned char* in, int len, UString* out)
{
  int i;

  UStr_alloc(out);

  if (len < 2) return 0;
  for (i = 0; i < len; i += 2) {
    unsigned int c = in[i] | (in[i+1] << 8);
    if (c >= 0xdc00 && c <= 0xdfff) { /* sole low surrogate */
      if (replace_invalid) {
	UStr_addWCharToU32LE(out, replace_invalid);
	continue;
      }
      else
	rb_raise(eUconvError, "invalid surrogate detected");
    }
    else if (c >= 0xd800 && c <= 0xdbff) { /* high surrogate */
      unsigned int low;
      if (i + 4 > len) { /* not enough length */
	if (replace_invalid) {
	  UStr_addWCharToU32LE(out, replace_invalid);
	  continue;
	}
	else
	  rb_raise(eUconvError, "invalid surrogate detected");
      }
      low = in[i+2] | (in[i+3] << 8);
      if (low < 0xdc00 || low > 0xdfff) { /* not low surrogate */
	if (replace_invalid) {
	  UStr_addWCharToU32LE(out, replace_invalid);
	  continue;
	}
	else
	  rb_raise(eUconvError, "invalid surrogate detected");
      }
      c = (((c & 1023)) << 10 | (low & 1023)) + 0x10000;
      UStr_addChar4(out, c & 255, (c >> 8) & 255, c >> 16, 0);
      i += 2;
    }
    else {
      UStr_addChar4(out, in[i], in[i+1], 0, 0);
    }
  }

  return out->len;
}

#ifdef USE_EUC
static unsigned short
unknown_euc_handler(const unsigned char* seq)
{
  ID mid = rb_intern("unknown_euc_handler");
  VALUE ret;

  if (!rb_method_boundp(CLASS_OF(mUconv), mid, 0))
    return '?';

  ret = rb_funcall((VALUE)mUconv, mid, 1, rb_str_new2((char*)seq));
  Check_Type(ret, T_FIXNUM);
  return FIX2INT(ret);
}
#endif /* USE_EUC */

#ifdef USE_SJIS
static unsigned short
unknown_sjis_handler(const unsigned char* seq)
{
  ID mid = rb_intern("unknown_sjis_handler");
  VALUE ret;

  if (!rb_method_boundp(CLASS_OF(mUconv), mid, 0))
    return '?';

  ret = rb_funcall((VALUE)mUconv, mid, 1, rb_str_new2((char*)seq));
  Check_Type(ret, T_FIXNUM);
  return FIX2INT(ret);
}
#endif /* USE_SJIS */

static unsigned char*
unknown_unicode_handler(unsigned short code)
{
  ID mid = rb_intern("unknown_unicode_handler");
  VALUE ret;
  unsigned char* estr;

  if (!rb_method_boundp(CLASS_OF(mUconv), mid, 0)) {
    estr = (unsigned char*)malloc(2);
    estr[0] = '?';
    estr[1] = '\0';
    return estr;
  }
  ret = rb_funcall((VALUE)mUconv, mid, 1, INT2FIX(code));
  Check_Type(ret, T_STRING);
  estr = (unsigned char*)malloc(RSTRING(ret)->len + 1);
  memcpy(estr, RSTRING(ret)->ptr, RSTRING(ret)->len + 1);

  return estr;
}

#ifdef USE_EUC
static VALUE
uconv_u2toeuc(VALUE obj, VALUE wstr)
{
  int len;
  unsigned char* u;
  VALUE ret;
  UString e;

  Check_Type(wstr, T_STRING);

  u = (unsigned char*)(RSTRING(wstr)->ptr);
  len = RSTRING(wstr)->len;

  u2e_conv2(u, len, &e, unknown_unicode_handler);
  ret = rb_str_new((char*)e.str, e.len);
  UStr_free(&e);
  OBJ_INFECT(ret, wstr);

  return ret;
}

static VALUE
uconv_euctou2(VALUE obj, VALUE estr)
{
  int len;
  unsigned char* e;
  UString u;
  VALUE ret;

  Check_Type(estr, T_STRING);

  e = (unsigned char*)(RSTRING(estr)->ptr);
  len = e2u_conv2(e, &u, unknown_euc_handler);

  ret = rb_str_new((char*)u.str, u.len);
  UStr_free(&u);
  OBJ_INFECT(ret, estr);

  return ret;
}
#endif /* USE_EUC */

#ifdef USE_SJIS
static VALUE
uconv_u2tosjis(VALUE obj, VALUE wstr)
{
  int len;
  unsigned char* u;
  VALUE ret;
  UString s;

  Check_Type(wstr, T_STRING);

  u = (unsigned char*)(RSTRING(wstr)->ptr);
  len = RSTRING(wstr)->len;

  u2s_conv2(u, len, &s, unknown_unicode_handler);
  ret = rb_str_new((char*)s.str, s.len);
  UStr_free(&s);
  OBJ_INFECT(ret, wstr);

  return ret;
}

static VALUE
uconv_sjistou2(VALUE obj, VALUE sstr)
{
  int len;
  unsigned char* s;
  UString u;
  VALUE ret;

  Check_Type(sstr, T_STRING);

  s = (unsigned char*)(RSTRING(sstr)->ptr);
  len = s2u_conv2(s, &u, unknown_sjis_handler);

  ret = rb_str_new((char*)u.str, u.len);
  UStr_free(&u);
  OBJ_INFECT(ret, sstr);

  return ret;
}
#endif /* USE_SJIS */

static VALUE
uconv_u2swap(VALUE obj, VALUE wstr)
{
  int len;
  int i;
  unsigned char* u;
  unsigned char* out;
  VALUE ret;

  Check_Type(wstr, T_STRING);

  u = (unsigned char*)(RSTRING(wstr)->ptr);
  len = RSTRING(wstr)->len;
  if (len < 2) return Qnil;
  ret = rb_str_new(NULL, len);
  out = (unsigned char*)(RSTRING(ret)->ptr);

  for (i = 0; i < len; i+=2) {
    out[i] = u[i+1];
    out[i+1] = u[i];
  }
  OBJ_INFECT(ret, wstr);

  return ret;
}

static VALUE
uconv_u2swap_b(VALUE obj, VALUE wstr)
{
  int len;
  int i;
  unsigned char* u;

  Check_Type(wstr, T_STRING);

  rb_str_modify(wstr);
  u = (unsigned char*)(RSTRING(wstr)->ptr);
  len = RSTRING(wstr)->len;
  if (len < 2) return Qnil;

  for (i = 0; i < len; i+=2) {
    register unsigned char tmp = u[i+1];
    u[i+1] = u[i];
    u[i] = tmp;
  }
  return wstr;
}

static VALUE
uconv_u4swap(VALUE obj, VALUE wstr)
{
  int len;
  int i;
  unsigned char* u;
  unsigned char* out;
  VALUE ret;

  Check_Type(wstr, T_STRING);

  u = (unsigned char*)(RSTRING(wstr)->ptr);
  len = RSTRING(wstr)->len;
  if (len < 4) return Qnil;
  ret = rb_str_new(NULL, len);
  out = (unsigned char*)(RSTRING(ret)->ptr);

  for (i = 0; i < len; i+=4) {
    out[i]   = u[i+3];
    out[i+1] = u[i+2];
    out[i+2] = u[i+1];
    out[i+3] = u[i];
  }
  OBJ_INFECT(ret, wstr);

  return ret;
}

static VALUE
uconv_u4swap_b(VALUE obj, VALUE wstr)
{
  int len;
  int i;
  unsigned char* u;

  Check_Type(wstr, T_STRING);

  rb_str_modify(wstr);
  u = (unsigned char*)(RSTRING(wstr)->ptr);
  len = RSTRING(wstr)->len;
  if (len < 4) return Qnil;

  for (i = 0; i < len; i+=4) {
    register unsigned char tmp1 = u[i];
    register unsigned char tmp2 = u[i+1];
    u[i] = u[i+3];
    u[i+1] = u[i+2];
    u[i+2] = tmp2;
    u[i+3] = tmp1;
  }
  return wstr;
}


static VALUE
uconv_u8tou16(VALUE obj, VALUE ustr)
{
  unsigned char* in;
  UString out;
  VALUE ret;

  Check_Type(ustr, T_STRING);
  in = (unsigned char*)(RSTRING(ustr)->ptr);
  _u8tou16(in, &out);
  ret = rb_str_new((char*)out.str, out.len);
  UStr_free(&out);
  OBJ_INFECT(ret, ustr);

  return ret;
}

static VALUE
uconv_u16tou8(VALUE obj, VALUE wstr)
{
  int len;
  unsigned char* in;
  UString out;
  VALUE ret;

  Check_Type(wstr, T_STRING);
  in = (unsigned char*)(RSTRING(wstr)->ptr);
  len = RSTRING(wstr)->len;
  _u16tou8(in, len, &out, eliminate_zwnbsp_flag);
  ret = rb_str_new((char*)out.str, out.len);
  UStr_free(&out);
  OBJ_INFECT(ret, wstr);

  return ret;
}


static VALUE
uconv_u8tou4(VALUE obj, VALUE ustr)
{
  unsigned char* in;
  UString out;
  VALUE ret;

  Check_Type(ustr, T_STRING);
  in = (unsigned char*)(RSTRING(ustr)->ptr);
  _u8tou4(in, &out);
  ret = rb_str_new((char*)out.str, out.len);
  UStr_free(&out);
  OBJ_INFECT(ret, ustr);

  return ret;
}

static VALUE
uconv_u4tou8(VALUE obj, VALUE wstr)
{
  int len;
  unsigned char* in;
  UString out;
  VALUE ret;

  Check_Type(wstr, T_STRING);
  in = (unsigned char*)(RSTRING(wstr)->ptr);
  len = RSTRING(wstr)->len;
  _u4tou8(in, len, &out, eliminate_zwnbsp_flag);
  ret = rb_str_new((char*)out.str, out.len);
  UStr_free(&out);
  OBJ_INFECT(ret, wstr);

  return ret;
}


static VALUE
uconv_u16tou4(VALUE obj, VALUE wstr)
{
  int len;
  unsigned char* in;
  UString out;
  VALUE ret;

  Check_Type(wstr, T_STRING);
  in = (unsigned char*)(RSTRING(wstr)->ptr);
  len = RSTRING(wstr)->len;
  _u16tou4(in, len, &out);
  ret = rb_str_new((char*)out.str, out.len);
  UStr_free(&out);
  OBJ_INFECT(ret, wstr);

  return ret;
}

static VALUE
uconv_u4tou16(VALUE obj, VALUE wstr)
{
  int len;
  unsigned char* in;
  UString out;
  VALUE ret;

  Check_Type(wstr, T_STRING);
  in = (unsigned char*)(RSTRING(wstr)->ptr);
  len = RSTRING(wstr)->len;
  _u4tou16(in, len, &out);
  ret = rb_str_new((char*)out.str, out.len);
  UStr_free(&out);
  OBJ_INFECT(ret, wstr);

  return ret;
}

#ifdef USE_EUC
static VALUE
uconv_u8toeuc(VALUE obj, VALUE ustr)
{
  unsigned char* in;
  UString out;
  UString e;
  VALUE ret;

  Check_Type(ustr, T_STRING);
  in = (unsigned char*)(RSTRING(ustr)->ptr);
  _u8tou16(in, &out);
  u2e_conv2(out.str, out.len, &e, unknown_unicode_handler);
  ret = rb_str_new((char*)e.str, e.len);
  UStr_free(&e);
  UStr_free(&out);
  OBJ_INFECT(ret, ustr);

  return ret;
}

static VALUE
uconv_euctou8(VALUE obj, VALUE estr)
{
  int len;
  unsigned char* e;
  UString in;
  UString out;
  VALUE ret;

  Check_Type(estr, T_STRING);
  e = (unsigned char*)(RSTRING(estr)->ptr);
  len = RSTRING(estr)->len;
  e2u_conv2(e, &in, unknown_euc_handler);
  _u16tou8(in.str, in.len, &out, 1);
  ret = rb_str_new((char*)out.str, out.len);
  UStr_free(&out);
  UStr_free(&in);
  OBJ_INFECT(ret, estr);

  return ret;
}
#endif /* USE_EUC */

#ifdef USE_SJIS
static VALUE
uconv_u8tosjis(VALUE obj, VALUE ustr)
{
  unsigned char* in;
  UString out;
  UString s;
  VALUE ret;

  Check_Type(ustr, T_STRING);
  in = (unsigned char*)(RSTRING(ustr)->ptr);
  _u8tou16(in, &out);
  u2s_conv2(out.str, out.len, &s, unknown_unicode_handler);
  ret = rb_str_new((char*)s.str, s.len);
  UStr_free(&s);
  UStr_free(&out);
  OBJ_INFECT(ret, ustr);

  return ret;
}

static VALUE
uconv_sjistou8(VALUE obj, VALUE sstr)
{
  int len;
  unsigned char* s;
  UString in;
  UString out;
  VALUE ret;

  Check_Type(sstr, T_STRING);
  s = (unsigned char*)(RSTRING(sstr)->ptr);
  len = RSTRING(sstr)->len;
  s2u_conv2(s, &in, unknown_sjis_handler);
  _u16tou8(in.str, in.len, &out, 1);
  ret = rb_str_new((char*)out.str, out.len);
  UStr_free(&out);
  UStr_free(&in);
  OBJ_INFECT(ret, sstr);

  return ret;
}
#endif /* USE_SJIS */

static VALUE
get_eliminate_zwnbsp_flag(VALUE obj)
{
  if (eliminate_zwnbsp_flag == 0) return Qfalse;
  return Qtrue;
}

static VALUE
set_eliminate_zwnbsp_flag(VALUE obj, VALUE flag)
{
  if (flag == Qtrue) {
    eliminate_zwnbsp_flag = 1;
  }
  else if (flag == Qfalse) {
    eliminate_zwnbsp_flag = 0;
  }
  else {
    rb_raise(rb_eTypeError, "wrong argument type");
  }
  return flag;
}

static VALUE
get_shortest_flag(VALUE obj)
{
  if (shortest_flag == 0) return Qfalse;
  return Qtrue;
}

static VALUE
set_shortest_flag(VALUE obj, VALUE flag)
{
  if (flag == Qtrue) {
    shortest_flag = 1;
  }
  else if (flag == Qfalse) {
    shortest_flag = 0;
  }
  else {
    rb_raise(rb_eTypeError, "wrong argument type");
  }
  return flag;
}

static VALUE
get_replace_invalid(VALUE obj)
{
  if (replace_invalid == 0) return Qnil;
  return INT2NUM(replace_invalid);
}

static VALUE
set_replace_invalid(VALUE obj, VALUE uchar)
{
  if (uchar == Qnil) {
    replace_invalid = 0;
  }
  else {
    replace_invalid = NUM2INT(uchar);
  }
  return uchar;
}

void
Init_uconv()
{
  if (rb_const_defined(rb_cObject, rb_intern("Uconv")) == Qtrue)
    mUconv = rb_const_get(rb_cObject, rb_intern("Uconv"));
  else
    mUconv = rb_define_module("Uconv");
  eUconvError = rb_define_class_under(mUconv,
				      "Error", rb_eStandardError);

#ifdef USE_EUC
  rb_define_module_function(mUconv, "u16toeuc", uconv_u2toeuc, 1);
  rb_define_module_function(mUconv, "euctou16", uconv_euctou2, 1);
  rb_define_module_function(mUconv, "u2toeuc", uconv_u2toeuc, 1);
  rb_define_module_function(mUconv, "euctou2", uconv_euctou2, 1);

  rb_define_module_function(mUconv, "u8toeuc", uconv_u8toeuc, 1);
  rb_define_module_function(mUconv, "euctou8", uconv_euctou8, 1);
#endif

#ifdef USE_SJIS
  rb_define_module_function(mUconv, "u16tosjis", uconv_u2tosjis, 1);
  rb_define_module_function(mUconv, "sjistou16", uconv_sjistou2, 1);
  rb_define_module_function(mUconv, "u2tosjis", uconv_u2tosjis, 1);
  rb_define_module_function(mUconv, "sjistou2", uconv_sjistou2, 1);

  rb_define_module_function(mUconv, "u8tosjis", uconv_u8tosjis, 1);
  rb_define_module_function(mUconv, "sjistou8", uconv_sjistou8, 1);
#endif

  rb_define_module_function(mUconv, "u16swap", uconv_u2swap, 1);
  rb_define_module_function(mUconv, "u16swap!", uconv_u2swap_b, 1);
  rb_define_module_function(mUconv, "u2swap", uconv_u2swap, 1);
  rb_define_module_function(mUconv, "u2swap!", uconv_u2swap_b, 1);
  rb_define_module_function(mUconv, "u4swap", uconv_u4swap, 1);
  rb_define_module_function(mUconv, "u4swap!", uconv_u4swap_b, 1);

  rb_define_module_function(mUconv, "u8tou16", uconv_u8tou16, 1);
  rb_define_module_function(mUconv, "u8tou2",  uconv_u8tou16, 1);
  rb_define_module_function(mUconv, "u16tou8", uconv_u16tou8, 1);
  rb_define_module_function(mUconv, "u2tou8",  uconv_u16tou8, 1);
  rb_define_module_function(mUconv, "u8tou4", uconv_u8tou4, 1);
  rb_define_module_function(mUconv, "u4tou8", uconv_u4tou8, 1);
  rb_define_module_function(mUconv, "u16tou4", uconv_u16tou4, 1);
  rb_define_module_function(mUconv, "u4tou16", uconv_u4tou16, 1);

  rb_define_module_function(mUconv, "eliminate_zwnbsp",
			    get_eliminate_zwnbsp_flag, 0);
  rb_define_module_function(mUconv, "eliminate_zwnbsp=",
			    set_eliminate_zwnbsp_flag, 1);
  rb_define_module_function(mUconv, "shortest",
			    get_shortest_flag, 0);
  rb_define_module_function(mUconv, "shortest=",
			    set_shortest_flag, 1);
  rb_define_module_function(mUconv, "replace_invalid",
			    get_replace_invalid, 0);
  rb_define_module_function(mUconv, "replace_invalid=",
			    set_replace_invalid, 1);

  rb_define_const(mUconv, "REPLACEMENT_CHAR",
		  INT2FIX(REPLACEMENT_CHAR));
}
