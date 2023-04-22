#define _GNU_SOURCE
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
  int file = open(argv[1], O_RDWR | O_CREAT, 0600);
  // int main() {
  //   int file = open("output.txt", O_RDWR);
  if (file == -1) {
    return 0;
  }

  size_t N = 0;
  size_t W = 0;

  for (size_t i = 0; i < strlen(argv[2]); ++i) {
    N *= 10;
    N += argv[2][i] - '0';
  }

  for (size_t i = 0; i < strlen(argv[3]); ++i) {
    W *= 10;
    W += argv[3][i] - '0';
  }

  lseek(file, (N * N * W) + N - 1, SEEK_SET);
  write(file, "", 1);  // otherwise mmap does not work
  char* output =
      mmap(NULL, (N * N * W) + N, PROT_READ | PROT_WRITE, MAP_SHARED, file, 0);

  long value = 1;
  long max_row = N;
  long max_column = N;
  long row = 0;
  long column = 0;
  while (row < max_row && column < max_column) {
    for (long i = column; i < max_column - 1; ++i) {
      char buffer[W + 1];
      char text[W + 1];
      for (int i = 0; i < W; ++i) {
        text[i] = ' ';
      }
      sprintf(buffer, "%ld", value);
      sprintf(text + W - strlen(buffer), "%ld", value);
      memcpy(output + (row * (N * W + 1) + (i * W)), text, W);
      value++;
    }
    ++row;
    for (long i = row - 1; i < max_row; ++i) {
      char buffer[W + 1];
      char text[W + 1];
      for (int i = 0; i < W; ++i) {
        text[i] = ' ';
      }
      sprintf(buffer, "%ld", value);
      sprintf(text + W - strlen(buffer), "%ld", value);
      memcpy(output + (i * (N * W + 1) + ((max_column - 1) * W)), text, W);
      value++;
      if (max_column == N) {
        output[(i * (N * W + 1)) + (N * W)] = '\n';
      }
    }
    --max_column;
    for (long i = max_column - 1; i >= column; --i) {
      char buffer[W + 1];
      char text[W + 1];
      for (int i = 0; i < W; ++i) {
        text[i] = ' ';
      }
      sprintf(buffer, "%ld", value);
      sprintf(text + W - strlen(buffer), "%ld", value);
      memcpy(output + ((max_row - 1) * (N * W + 1) + (i * W)), text, W);
      value++;
    }
    --max_row;
    for (long i = max_row - 1; i >= row; --i) {
      char buffer[W + 1];
      char text[W + 1];
      for (int i = 0; i < W; ++i) {
        text[i] = ' ';
      }
      sprintf(buffer, "%ld", value);
      sprintf(text + W - strlen(buffer), "%ld", value);
      memcpy(output + (i * (N * W + 1) + (column * W)), text, W);
      value++;
    }
    ++column;
  }

  msync(output, (N * N * W) + N, MS_SYNC);
  munmap(output, (N * N * W) + N);
  close(file);
  return 0;
}