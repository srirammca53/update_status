#ifndef MSCDISWARN_H
#define MSCDISWARN_H

#if defined(_MSC_VER) && (_MSC_VER==1200)
/* the limit of identifier of symbol 255 */
#pragma warning(disable:4786)
#endif

#endif
