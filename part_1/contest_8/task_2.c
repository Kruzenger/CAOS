#include <errno.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

const int kSize = 1 << 12;

int compare(const void *a, const void *b) {
  int arg1 = *(const int *)a;
  int arg2 = *(const int *)b;
  if (arg1 < arg2) return -1;
  if (arg1 > arg2) return 1;
  return 0;
}

void Merge(int file_num, int32_t values[kSize], int size) {
  if (file_num == -1) {
    int out = open("file" + 0, O_WRONLY | O_CREAT, 0640);
    for (int i = 0; i < size; ++i) {
      write(out, values + i, sizeof(int32_t));
    }
    close(out);
    return;
  }

  int in = open("file" + file_num, O_RDONLY);
  int out = open("file" + file_num + 1, O_WRONLY | O_CREAT, 0640);

  int32_t tmp = 0;
  int size_r = read(in, &tmp, sizeof(int32_t));
  for (int i = 0; i < size;) {
    if (size_r != 0) {
      if (values[i] < tmp) {
        write(out, values + i, sizeof(int32_t));
        ++i;
      } else {
        write(out, &tmp, sizeof(int32_t));
        size_r = read(in, &tmp, sizeof(int32_t));
      }
    } else {
      write(out, values + i, sizeof(int32_t));
      ++i;
    }
  }

  if (size_r > 0) {
    write(out, &tmp, sizeof(int32_t));
    while (read(in, &tmp, sizeof(int32_t)) > 0) {
      write(out, &tmp, sizeof(int32_t));
    }
  }
  close(in);
  close(out);
}

int main(int argc, char *argv[]) {
  int exit_code = 0;
  int in = open(argv[1], O_RDONLY);
  if (in == -1) {
    exit_code = 1;
    perror("Open input file");
    goto finally;
  }

  int file_count = 0;
  while (1) {
    int32_t values[kSize];
    int i = 0;
    for (; i < kSize; ++i) {
      if (!(read(in, &(values[i]), sizeof(int32_t)) > 0)) {
        if (i == 0) {
          goto end;
        }
        break;
      }
    }
    qsort(values, i, sizeof(int32_t), compare);
    Merge(file_count - 1, values, i);
    ++file_count;
  }
end:
  close(in);
  in = open("file" + (file_count - 1), O_RDONLY);
  int out = open(argv[1], O_WRONLY, 0640);

  int32_t value = 0;
  while (read(in, &value, sizeof(int32_t)) > 0) {
    write(out, &value, sizeof(int32_t));
    // printf("%d ", value);
  }

finally:
  close(in);
  close(out);
  return exit_code;
}
