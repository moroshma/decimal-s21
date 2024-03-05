#include "s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  s21_copy(value, result);

  if (s21_get_sign(result) == 0) {
    s21_set_sign(result, 1);
  } else {
    s21_set_sign(result, 0);
  }
  return OK;
}
