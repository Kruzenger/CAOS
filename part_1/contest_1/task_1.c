#include <stdint.h>
typedef uint64_t ITYPE;

extern void sum(ITYPE first, ITYPE second, ITYPE* res, int* CF) {
  ITYPE carry = 0;
  ITYPE size = sizeof(ITYPE);
  for (ITYPE i = 0; i < 8 * size; ++i) {
    carry = first & second;
    first = first ^ second;
    second = (carry << 1);
  }

  *res = first;
  if (carry == 0) {
    *CF = 0;
  } else {
    *CF = 1;
  }
}

extern void mul(ITYPE first, ITYPE second, ITYPE* res, int* CF) {
  ITYPE carry = 0;
  ITYPE result = 0;
  int CF1 = 0;
  ITYPE num = 1;
  for (int i = 0; second != 0; ++i) {
    carry = (second & 1);
    second = (second >> 1);
    if (carry == 1) {
      sum(result, first << i, &result, &CF1);
    }
    if (CF1 == 1 || first > (((num << (63 - i)) - 1) << 1)) {
      *CF = 1;
    }
  }
  *res = result;
}
