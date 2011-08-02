#include <windows.h>
#include "ruby.h"

#include "nkf.h"
#undef getc
#undef ungetc
#define getc(f)   	(input_ctr<i_len?input[input_ctr++]:-1)
#define ungetc(c,f)	input_ctr--

#undef putchar
#define putchar(c)	rb_nkf_putchar(c)

#define INCSIZE		32
static int incsize;

static unsigned char *input, *output;
static int input_ctr, i_len;
static int output_ctr, o_len;

static VALUE dst;

static int
rb_nkf_putchar(unsigned int c)
{
  if (output_ctr >= o_len) {
    o_len += incsize;
    rb_str_cat(dst, 0, incsize);
    output = (unsigned char *)RSTRING(dst)->ptr;
    incsize *= 2;
  }
  output[output_ctr++] = c;

  return c;
}

#define PERL_XS 1
#include "nkf1.9/nkf.c"

VALUE rw_nkf_jis2sjis(unsigned char *src, int len) {
    return rw_nkf_kconv("-Js", src, len);
}

VALUE rw_nkf_sjis2jis(unsigned char *src, int len) {
    return rw_nkf_kconv("-Sj", src, len);
}

VALUE
rw_nkf_kconv(const char *opt, unsigned char * src, int len)
{
  volatile VALUE v;

  reinit();
  options(opt);

  incsize = INCSIZE;

  input_ctr = 0;
  i_len = len;
  input = src;
  dst = rb_str_new(0, i_len*3 + 10);
  v = dst;

  output_ctr = 0;
  output     = RSTRING(dst)->ptr;
  o_len      = RSTRING(dst)->len;
  *output    = '\0';

  if(iso8859_f && (oconv != j_oconv || !x0201_f )) {
    iso8859_f = FALSE;
  } 

  kanji_convert(NULL);
  RSTRING(dst)->ptr[output_ctr] = '\0';
  RSTRING(dst)->len = output_ctr;

  return dst;
}

