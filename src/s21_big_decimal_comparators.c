#include "s21_decimal.h"

int s21_big_is_equal(s21_big_decimal first_value,
                     s21_big_decimal second_value) {
  int result = TRUE;
  for (int i = 0;
       i < (int)(sizeof(s21_big_decimal) / sizeof(unsigned)) && result != FALSE;
       ++i) {
    if (first_value.bits[i] != second_value.bits[i]) result = FALSE;
  }
  return result;
}
