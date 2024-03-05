#include "s21_decimal.h"

unsigned s21_big_set_sign(s21_big_decimal* dec, int sign) {
  if (!sign) {
    dec->bits[(int)(sizeof(s21_big_decimal) / sizeof(unsigned) - 1)] &=
        ~(0b1 << 31);
  } else {
    dec->bits[(int)sizeof(s21_big_decimal) / sizeof(unsigned) - 1] |=
        (0b1 << 31);
  }
  return OK;
}

unsigned s21_big_get_sign(const s21_big_decimal* dec) {
  unsigned int ret =
      ((dec->bits[(int)sizeof(s21_big_decimal) / sizeof(unsigned) - 1]) &
       (0b1 << 31)) > 0;
  return (int)ret;
}

bool s21_big_is_zero(const s21_big_decimal* dec) {
  int ret = true;
  for (int i = 0; i < (int)(sizeof(*dec) / sizeof(unsigned) - 1); i++) {
    if (dec->bits[i] != 0) {
      ret = false;
    }
  }
  return ret;
}

bool s21_is_zero(const s21_decimal* dec) {
  int ret = true;
  for (int i = 0; i < DECIMAL_SIZE - 1; i++) {
    if (dec->bits[i] != 0) {
      ret = false;
    }
  }
  return ret;
}

unsigned s21_big_get_scale(const s21_big_decimal* dec) {
  return (dec->bits[7] >> 16) & 0b11111111;
}

unsigned s21_big_set_scale(s21_big_decimal* dec, int scale) {
  if (scale > 28 || scale < 0) {
    return CALCULATION_ERROR;
  }
  int sign = s21_big_get_sign(dec);
  dec->bits[7] = 0;
  dec->bits[7] |= scale << 16;
  s21_big_set_sign(dec, sign);
  return OK;
}

unsigned s21_big_set_bit(s21_big_decimal* dec, bool cell, int index) {
  if (index > (int)(sizeof(s21_big_decimal) - sizeof(unsigned)) * 32 ||
      index < 0) {
    return INDEX_ERROR;
  }

  int bucket = index / (int)(sizeof(unsigned) * 8);
  int pos = index % 32;

  if (cell) {
    dec->bits[bucket] |= 1U << pos;
  } else {
    dec->bits[bucket] &= ~(1U << pos);
  }
  return OK;
}

unsigned s21_big_get_bit(const s21_big_decimal* dec, int index) {
  if (index > (int)(sizeof(*dec) - sizeof(unsigned)) * 32 || index < 0) {
    return INDEX_ERROR;
  }

  int pos = index % 32;
  int backet = index / (int)(sizeof(unsigned) * 8);

  return (dec->bits[backet] >> pos) & 0b1;
}

unsigned s21_set_sign(s21_decimal* dec, int sign) {
  if (!sign) {
    dec->bits[(int)sizeof(s21_decimal) / sizeof(unsigned) - 1] &= ~(0b1 << 31);
  } else {
    dec->bits[(int)sizeof(s21_decimal) / sizeof(unsigned) - 1] |= (0b1 << 31);
  }
  return OK;
}

unsigned s21_get_sign(const s21_decimal* dec) {
  unsigned int ret =
      ((dec->bits[(int)sizeof(s21_decimal) / sizeof(unsigned) - 1]) &
       (0b1 << 31)) > 0;
  return (int)ret;
}

unsigned s21_get_scale(const s21_decimal* dec) {
  return (dec->bits[3] >> 16) & 0b11111111;
}
unsigned s21_set_scale(s21_decimal* dec, int scale) {
  if (scale > 28 || scale < 0) {
    return CALCULATION_ERROR;
  }
  int sign = s21_get_sign(dec);
  dec->bits[3] = 0;
  dec->bits[3] |= scale << 16;
  s21_set_sign(dec, sign);
  return OK;
}

unsigned s21_set_bit(s21_decimal* dec, bool cell, int index) {
  if (index > (int)(sizeof(s21_decimal) - sizeof(unsigned)) * 32 || index < 0) {
    return INDEX_ERROR;
  }

  int bucket = index / (int)(sizeof(unsigned) * 8);
  int pos = index % 32;

  if (cell) {
    dec->bits[bucket] |= 1U << pos;
  } else {
    dec->bits[bucket] &= ~(1U << pos);
  }
  return OK;
}

unsigned s21_get_bit(const s21_decimal* dec, int index) {
  if (index > (int)(sizeof(s21_decimal) - sizeof(unsigned)) * 32 || index < 0) {
    return INDEX_ERROR;
  }

  int bucket = index / (int)(sizeof(unsigned) * 8);
  int pos = index % 32;

  return (dec->bits[bucket] >> pos) & 1U;
}
