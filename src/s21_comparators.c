#include "s21_decimal.h"

int s21_is_less(s21_decimal first_number, s21_decimal second_number) {
  int result = compare(first_number, second_number);
  if (result == 1) {
    return TRUE;
  }
  return FALSE;
}

int s21_is_less_or_equal(s21_decimal first_number, s21_decimal second_number) {
  int result = compare(first_number, second_number);
  if (result == 1 || result == 0) {
    return TRUE;
  }
  return FALSE;
}

int s21_is_greater(s21_decimal first_number, s21_decimal second_number) {
  int result = compare(first_number, second_number);
  if (result == -1) {
    return TRUE;
  }
  return FALSE;
}

int s21_is_greater_or_equal(s21_decimal first_number,
                            s21_decimal second_number) {
  int result = compare(first_number, second_number);
  if (result == -1 || result == 0) {
    return TRUE;
  }
  return FALSE;
}

int s21_is_equal(s21_decimal first_number, s21_decimal second_number) {
  int result = compare(first_number, second_number);
  if (result == 0) {
    return TRUE;
  }
  return FALSE;
}

int s21_is_not_equal(s21_decimal first_number, s21_decimal second_number) {
  int result = compare(first_number, second_number);
  if (result != 0) {
    return TRUE;
  }
  return FALSE;
}

int compare(s21_decimal first_number, s21_decimal second_number) {
  s21_big_decimal big_first_number = {0};
  s21_big_decimal big_second_number = {0};

  s21_convert_to_big_decimal(&first_number, &big_first_number);
  s21_convert_to_big_decimal(&second_number, &big_second_number);

  int first_sign = s21_big_get_sign(&big_first_number);
  int second_sign = s21_big_get_sign(&big_second_number);

  s21_normalization(&big_first_number, &big_second_number);

  if (s21_big_is_zero(&big_first_number) &&
      s21_big_is_zero(&big_second_number)) {
    return 0;
  }
  if (first_sign == 1 && second_sign == 0) {
    return 1;
  } else if (first_sign == 0 && second_sign == 1) {
    return -1;
  }

  for (int i = BIG_DECIMAL_SIZE - 1; i >= 0; i--) {
    if (big_first_number.bits[i] > big_second_number.bits[i]) {
      //      return -1;
      if (first_sign && second_sign) {
        return 1;
      } else {
        return -1;
      }
    } else if (big_first_number.bits[i] < big_second_number.bits[i]) {
      //      return 1;
      if (first_sign && second_sign) {
        return -1;
      } else {
        return 1;
      }
    }
  }

  return 0;
}
