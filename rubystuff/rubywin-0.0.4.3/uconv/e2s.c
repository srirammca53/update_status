/*
 * EUC-JP <=> Shift_JIS Conversion Library
 * 1999 by yoshidam
 *
 */

unsigned short
sjis2euc(unsigned short sjis)
{
  register unsigned int ku = sjis >> 8;
  register unsigned int ten = sjis & 255;

  ku = (ku & 0x3f) << 1;
  if (ten > 158) {
    ten -= 158;
  }
  else {
    ku--;
    ten -= 64;
    if (ten <= 62) /* Aug 13, 1999 */
      ten++;
  }
  ten += 32;
  ku += 32;

  return ((ku << 8) | ten ) | 0x8080;
}

unsigned short
euc2sjis(unsigned short euc)
{
  register unsigned int high = (euc >> 8) - 160;
  register unsigned int low = (euc & 255) - 160;

  if (high & 1) {
    high++;
    low += 63;
    if (low >= 127)
      low++;
  }
  else {
    low += 158;
  }
  high = (high/2) | 0x80;
  if (high >= 0xa0)
    high |= 0x40;

  return (high << 8) | low;
}
