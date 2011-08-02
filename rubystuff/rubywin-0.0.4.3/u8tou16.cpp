#include "ustring.h"

int u8tou16(const unsigned char* in, UString* out)
{
  int i;
  unsigned int u = 0;
  int rest = 0;

  UStr_alloc(out);
  for (i = 0; in[i] != '\0'; i++) {
    unsigned char c = in[i];
    if ((c & 0xc0) == 0x80) {
      if (rest == 0)
	return 0;
      u = (u << 6) | (c & 63);
      rest--;
      if (rest == 0) {
	if (u < 0x10000) {
	  UStr_addChar2(out, u & 0xff, u >> 8);
	}
	else if (u < 0x110000) {
	  unsigned int high = ((u - 0x10000) >> 10) | 0xd800;
	  unsigned int low = (u & 1023) | 0xdc00;
	  UStr_addChar4(out, high & 255, high >> 8, low & 255, low >> 8);
	}
	else {
	  return 0;
	}
      }
    }
    else if ((c & 0x80) == 0) {      /* 0b0nnnnnnn (7bit) */
      if (c == 0)
	;
      UStr_addChar2(out, c, 0);
      rest = 0;
    }
    else if ((c & 0xe0) == 0xc0) {      /* 0b110nnnnn (11bit) */
      rest = 1;
      u = c & 31;
    }
    else if ((c & 0xf0) == 0xe0) {      /* 0b1110nnnn (16bit) */
      rest = 2;
      u = c & 15;
    }
    else if ((c & 0xf8) == 0xf0) {      /* 0b11110nnn (21bit) */
      rest = 3;
      u = c & 7;
    }
    else {
      return 0;
    }
  }

  return out->len;
}
