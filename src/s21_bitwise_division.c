#include "s21_decimal.h"
int get_first_non_zero_bit(const s21_big_decimal decimal) {
  int index = -1;
  for (int i = (sizeof(s21_big_decimal) - sizeof(unsigned)) * 8 - 1;
       i >= 0 && index == -1; i--) {
    if (s21_big_get_bit(&decimal, i) == 1) {
      index = i;
    }
  }
  return index;
}

int s21_bitwise_division(s21_big_decimal divisible, s21_big_decimal divider,
                         s21_big_decimal* result, s21_big_decimal* remainder) {
  if (s21_big_is_zero(&divider)) return CALCULATION_ERROR;
  s21_big_reset_to_zero(remainder);
  s21_big_reset_to_zero(result);
  if (s21_big_is_zero(&divisible)) {
    return OK;
  }

  int divider_length = get_first_non_zero_bit(divider) + 1;
  int divisible_length = get_first_non_zero_bit(divisible) + 1;
  int end_index = divisible_length - divider_length;
  s21_shift_left(&divider, end_index);
  for (int i = 0; i < end_index + 1; i++) {
    // printf("\n");
    // print_binary_decimal(&divisible);
    // printf("\n");
    // print_binary_decimal(&divider);
    // printf("\n");
    // print_binary_decimal(result);
    // printf("\n");
    s21_big_decimal temp;
    const int subtraction_result =
        s21_bitwise_subtraction(divisible, divider, &temp);
    s21_shift_left(result, 1);
    if (subtraction_result == OK) {
      s21_big_set_bit(result, true, 0);
      divisible = temp;
    } else {
      s21_big_set_bit(result, false, 0);
    }
    s21_shift_right(&divider, 1);
  }
  *remainder = divisible;
  return OK;
}
