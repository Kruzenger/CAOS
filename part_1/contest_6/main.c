#include <stdio.h>

extern double avx_sin(double x);

extern float dot_product(size_t N, const float *A, const float *B);

int main() {
  double num = 0.3;
  size_t N = 8;
  float A[10] = {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0};
  float B[10] = {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0};
  printf("%.20f\n", dot_product(N, A, B));
  // printf("%.20f\n", avx_sin(num));
}