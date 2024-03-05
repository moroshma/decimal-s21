#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H
#define BIG_DECIMAL_SIZE (int)(sizeof(s21_big_decimal) / sizeof(unsigned))
#define DECIMAL_SIZE (int)(sizeof(s21_decimal) / sizeof(unsigned))
#include <limits.h>
#include <stdbool.h>

typedef struct {
  unsigned bits[4];
} s21_decimal;

typedef struct {
  unsigned bits[8];
} s21_big_decimal;

enum {
  TRUE = 1,
  FALSE = 0,
  OK = 0,
  CONVERTATION_ERROR = 1,
  CALCULATION_ERROR = 1,
  NUMBER_IS_TOO_LARGE = 1,
  NUMBER_IS_TOO_LOW = 2,
  DIVIZION_BY_ZERO = 3,
  INDEX_ERROR = 2
};

// Arithmetic Operators
/// \brief Складывает два числа типа decimal
/// \param value_1 - первое слагаемое
/// \param value_2 - второе слагаемое
/// \param result - результат суммирования
/// \return OK - операция выполнена успешна;
/// \return NUMBER_IS_TOO_LARGE - число слишком велико или равно бесконечности;
/// \return NUMBER_IS_TOO_LOW - число слишком мало или равно отрицательной
/// бесконечности;
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal* result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal* result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal* result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal* result);

// Comparison Operators
int s21_is_less(s21_decimal, s21_decimal);
int s21_is_less_or_equal(s21_decimal, s21_decimal);
int s21_is_greater(s21_decimal, s21_decimal);
int s21_is_greater_or_equal(s21_decimal, s21_decimal);
int s21_is_equal(s21_decimal, s21_decimal);
int s21_is_not_equal(s21_decimal, s21_decimal);
int s21_big_is_equal(s21_big_decimal first_value, s21_big_decimal second_value);
int compare(s21_decimal first_number, s21_decimal second_number);

// Convertors and parsers
int s21_from_int_to_decimal(int src, s21_decimal* dst);
int s21_from_float_to_decimal(float src, s21_decimal* dst);
int s21_from_decimal_to_int(s21_decimal src, int* dst);
int s21_from_decimal_to_float(s21_decimal src, float* dst);
int s21_convert_to_big_decimal(const s21_decimal* source,
                               s21_big_decimal* destination);
int s21_convert_from_big_decimal(const s21_big_decimal* source,
                                 s21_decimal* destination);

// Another functions
int s21_floor(s21_decimal value, s21_decimal* result);
int s21_round(s21_decimal value, s21_decimal* result);
int s21_truncate(s21_decimal value, s21_decimal* result);
int s21_negate(s21_decimal value, s21_decimal* result);

// Helper functions
int correction(s21_big_decimal* decimal);
int check_overflow(s21_big_decimal decimal);
void s21_move_to_expected_align(s21_big_decimal* dec, int expected_scale);
void s21_normalization(s21_big_decimal* dec1, s21_big_decimal* dec2);
void s21_shift_right(s21_big_decimal* num, const int shift_value);
void s21_shift_left(s21_big_decimal* num, const int shift_value);
int s21_mul_big_decimal(s21_big_decimal val1, s21_big_decimal val2,
                        s21_big_decimal* res);
bool s21_is_zero(const s21_decimal* dec);
bool s21_big_is_zero(const s21_big_decimal* dec);

unsigned s21_big_set_sign(s21_big_decimal* dec, int sign);
unsigned s21_big_get_sign(const s21_big_decimal* dec);

unsigned s21_big_get_scale(const s21_big_decimal* dec);
unsigned s21_big_set_scale(s21_big_decimal* dec, int scale);

unsigned s21_big_set_bit(s21_big_decimal* dec, bool cell, int index);
unsigned s21_big_get_bit(const s21_big_decimal* dec, int index);

unsigned s21_set_sign(s21_decimal* dec, int sign);
unsigned s21_get_sign(const s21_decimal* dec);

unsigned s21_get_scale(const s21_decimal* dec);
unsigned s21_set_scale(s21_decimal* dec, int scale);

unsigned s21_set_bit(s21_decimal* dec, bool cell, int index);
unsigned s21_get_bit(const s21_decimal* dec, int index);

int s21_copy(s21_decimal value, s21_decimal* result);

// IO
void print_binary_decimal(const s21_big_decimal* decimal);
void print_decimal(const s21_decimal* decimal);
void print_big_decimal(const s21_big_decimal* decimal);
// Bitwise operations
/// \brief Побитово складывает мантисы двух чисел типа s21_big_decimal
/// \param first_number первое число
/// \param second_number второе число
/// \param result результат побитового сложения мантисс(знаковый bits равен 0)
/// \return 0 - если переполнения не было
/// \return 1 - если произошло переполнение в знаковый разряд
int s21_bitwise_add(s21_big_decimal first_number, s21_big_decimal second_number,
                    s21_big_decimal* result);

/// \brief Побитово вычитает из числа minuend число subtrahend
/// \warning Для успешного вычитания число minuend должно быть больше числа
/// subtrahend \param minuend уменьшаемое число \param subtrahend вычитаемое
/// число \param difference побитовая разность двух чисел \return OK - если
/// операция прошла успешно \return CALCULATION_ERROR - если число minuend
/// оказалось меньше чем subtrahend
int s21_bitwise_subtraction(s21_big_decimal minuend, s21_big_decimal subtrahend,
                            s21_big_decimal* difference);

/// \brief Сбрасывает все bits числа типа s21_decimal в 0
/// \param number указатель на число, которое требуется обнулить
void s21_reset_to_zero(s21_decimal* number);
/// \brief Сбрасывает все bits числа типа s21_big_decimal в 0
/// \param number указатель на число, которое требуется обнулить
void s21_big_reset_to_zero(s21_big_decimal* number);

/// \brief Побитово делит число divisible на число divider
/// \param divisible уменьшаемое число
/// \param divider вычитаемое число
/// \param remainder остаток от деления
/// \param result результат от деления
/// \return OK - если операция прошла успешно
/// \return CALCULATION_ERROR - при делении на ноль
int s21_bitwise_division(s21_big_decimal divisible, s21_big_decimal divider,
                         s21_big_decimal* result, s21_big_decimal* remainder);

s21_big_decimal s21_bitwise_negation(s21_big_decimal decimal);
#endif  // S21_DECIMAL_H
