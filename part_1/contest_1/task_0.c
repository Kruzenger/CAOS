#include <stdint.h>
typedef uint64_t ITYPE;

extern void sum(ITYPE first, ITYPE second, ITYPE* res, int* CF) {
  ITYPE carry = 0;
  while (second != 0) {
    carry = (first & second);
    first = first ^ second;
    second = (carry << 1);
  }
  *res = first;
  if (carry > 0) {
    *CF = 1;
  } else {
    *CF = 0;
  }
}