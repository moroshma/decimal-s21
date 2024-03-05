#include "s21_decimal.h"

void s21_sub_shift_right(s21_big_decimal* num, const int shift_value) {
  unsigned shift = 0;
  for (int i = sizeof(s21_big_decimal) / sizeof(unsigned) - 2; i >= 0; i--) {
    const unsigned temp = num->bits[i];
    num->bits[i] = num->bits[i] >> shift_value;
    num->bits[i] |= shift;
    shift = temp << (sizeof(unsigned) * 8 - shift_value);
  }
}
void s21_shift_right(s21_big_decimal* num, const int shift_value) {
  const int max_shift = sizeof(unsigned) * 8 - 1;
  for (int i = 0; i < shift_value / max_shift; ++i) {
    s21_sub_shift_right(num, max_shift);
  }
  s21_sub_shift_right(num, shift_value % max_shift);
}
