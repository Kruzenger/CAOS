#include <stdio.h>

extern void sum(size_t N, const int *A, const int *B, int *R);

int main() {
  int a[10] = {9, 1, 2, 3, 4, 7, 8, 9, 5, 4};
  int b[10] = {5, 4, 3, 2, 1, 4, 3, 5, 6, 7};
  int R[10];
  sum(10, a, b, R);
  for (int i = 0; i < 10; i++) {
    printf("%d ", R[i]);
  }
  return 0;
}