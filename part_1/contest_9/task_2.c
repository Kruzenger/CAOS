#include <fcntl.h>
#include <libgen.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

void extract(size_t start, size_t end, char* path) {
  size_t i = 0;
  for (; *(path + end + i); ++i) {
    *(path + start + i) = *(path + end + i);
  }
  for (; *(path + start + i); ++i) {
    *(path + start + i) = '\0';
  }
}

extern void normalize_path(char* path) {
  for (size_t i = 0; *(path + i + 1); ++i) {
    if (*(path + i) == '.') {
      if (*(path + i + 1) == '.') {
        size_t j = i - 2;
        for (; i > 0 && *(path + j) != '/'; --j) {
        }
        extract(j + 1, i + 3, path);
        i = j;
      } else if (*(path + i + 1) == '/') {
        extract(i, i + 2, path);
        i -= 2;
      }
    } else if (*(path + i) == '/' && *(path + i + 1) == '/') {
      extract(i, i + 1, path);
      --i;
    }
  }
}