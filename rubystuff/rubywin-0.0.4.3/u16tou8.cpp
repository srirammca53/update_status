#include "ustring.h"

int
u16tou8(unsigned char* in, int len, UString* out, int eliminate_zwnbsp)
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
    else if (c >= 0xd800 && c <= 0xdbff) { /* high surrogate */
      unsigned int low;
      unsigned char b1, b2, b3, b4;
      if (i + 4 > len) /* not enough length */
	return 0;
      low = in[i+2] | (in[i+3] << 8);
      if (low < 0xdc00 || low > 0xdfff) /* not low surrogate */
	return 0;
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
