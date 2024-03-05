#include "s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal* dst) {
  s21_reset_to_zero(dst);
  if (src < 0) {
    s21_set_sign(dst, 1);
    src = -src;
  }
  dst->bits[0] = src;
  return OK;
}
int s21_from_decimal_to_int(s21_decimal src, int* dst) {
  s21_truncate(src, &src);
  bool integer_overflow = false;
  for (int i = 1; i < DECIMAL_SIZE - 1 && !integer_overflow; i++) {
    if (src.bits[i] != 0) integer_overflow = true;
  }
  int sign = s21_get_sign(&src);
  if (integer_overflow || (sign == 1 && src.bits[0] > (unsigned)INT_MAX + 1) ||
      (sign == 0 && src.bits[0] > INT_MAX))
    integer_overflow = true;
  else {
    *dst = src.bits[0] * (sign == 1 ? -1 : 1);
  }
  return integer_overflow ? CONVERTATION_ERROR : OK;
}
