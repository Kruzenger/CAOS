#include <stdint.h>
#include <stdio.h>

int GetLength(int64_t a) {
  if ((a & 0xf0) == 0xf0) {
    return 4;
  }
  if ((a & 0xe0) == 0xe0) {
    return 3;
  }
  if ((a & 0xc0) == 0xc0) {
    return 2;
  }

  return 0;
}

int main() {
  int symbol;
  int additional_char;

  int ascii_count = 0;
  int utf_count = 0;

  while ((symbol = getchar()) != EOF) {
    if ((symbol & (1 << 7)) == 0) {
      ++ascii_count;
      continue;
    }

    int additional_chars = GetLength(symbol);
    if (additional_chars == 0) {
      printf("%d %d", ascii_count, utf_count);
      return 1;
    }

    for (int i = 0; i < additional_chars - 1; ++i) {
      additional_char = getchar();
      if (additional_char == '\0') {
        printf("%d %d", ascii_count, utf_count);
        return 1;
      }
      if ((additional_char & 0x80) != 0x80) {
        printf("%d %d", ascii_count, utf_count);
        return 1;
      }
    }
    ++utf_count;
  }

  printf("%d %d", ascii_count, utf_count);
  return 0;
}
