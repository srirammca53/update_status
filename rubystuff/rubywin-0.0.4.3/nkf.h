#ifndef NKF_H
#define NKF_H
#include "ruby.h"

#ifdef __cplusplus
extern "C" {
#endif
VALUE rw_nkf_jis2sjis(unsigned char *src, int len);
VALUE rw_nkf_sjis2jis(unsigned char *src, int len);
VALUE rw_nkf_kconv(const char *opt, unsigned char * src, int len);
#ifdef __cplusplus
}
#endif

#endif
