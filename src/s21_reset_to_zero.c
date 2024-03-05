#include "s21_decimal.h"

void s21_reset_to_zero(s21_decimal* number) {
  for (int i = 0; i < DECIMAL_SIZE; ++i) {
    number->bits[i] = 0;
  }
}

void s21_big_reset_to_zero(s21_big_decimal* number) {
  for (int i = 0; i < BIG_DECIMAL_SIZE; ++i) {
    number->bits[i] = 0;
  }
}
