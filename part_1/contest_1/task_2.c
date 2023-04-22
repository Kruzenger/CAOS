#include <stdint.h>

typedef union {
  double value;
  uint64_t u_value;
} number;

typedef enum {
  PlusZero = 0x00,
  MinusZero = 0x01,
  PlusInf = 0xF0,
  MinusInf = 0xF1,
  PlusRegular = 0x10,
  MinusRegular = 0x11,
  PlusDenormal = 0x20,
  MinusDenormal = 0x21,
  SignalingNaN = 0x30,
  QuietNaN = 0x31
} float_class_t;

int16_t MAX_EXP = 2047;
int16_t MANTISS_BIT_SIZE = 52;
int16_t EXP_BIT_SIZE = 12;
int16_t NUM_BIT_SIZE = 64;

extern float_class_t classify(double *value_ptr) {
  number num;
  num.value = *value_ptr;
  uint64_t sign = (num.u_value >> (NUM_BIT_SIZE - 1));
  uint64_t mantiss = (num.u_value & (~0ULL >> EXP_BIT_SIZE));
  uint64_t exp = ((num.u_value & (~0ULL >> 1)) >> MANTISS_BIT_SIZE);

  // printf("%lu %lu %lu", sign, mantiss, exp);

  if ((mantiss >> (MANTISS_BIT_SIZE - 1)) == 0 && mantiss != 0 &&
      exp == MAX_EXP) {
    return SignalingNaN;
  }
  if ((mantiss >> (MANTISS_BIT_SIZE - 1)) == 1 && mantiss != 0 &&
      exp == MAX_EXP) {
    return QuietNaN;
  }

  if (sign == 0) {
    if (mantiss == 0 && exp == 0) {
      return PlusZero;
    }
    if (mantiss == 0 && exp == MAX_EXP) {
      return PlusInf;
    }
    if (exp == 0) {
      return PlusDenormal;
    }
    return PlusRegular;
  }
  if (sign == 1) {
    if (mantiss == 0 && exp == 0) {
      return MinusZero;
    }
    if (mantiss == 0 && exp == MAX_EXP) {
      return MinusInf;
    }
    if (exp == 0) {
      return MinusDenormal;
    }
    return MinusRegular;
  }

  return PlusRegular;
}

// int main() {
//   double a = 0;
//   printf("%d", classify(&a));
//   return 0;
// }