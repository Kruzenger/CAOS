#include <stdint.h>
#include <stdio.h>

int FindSymbolPosition(int16_t symbol) {
  if (symbol >= '0' && symbol <= '9') {
    return (symbol - '0');
  } else if (symbol >= 'A' && symbol <= 'Z') {
    return (symbol - 'A' + 10);
  } else if (symbol >= 'a' && symbol <= 'z') {
    return (symbol - 'a' + 36);
  }
  return 0;
}

int16_t GetCharFromBit(int bit) {
  if (bit <= 9) {
    return ('0' + bit);
  } else if (bit >= 10 && bit <= 35) {
    return ('A' + bit - 10);
  } else if (bit >= 36 && bit <= 61) {
    return ('a' + bit - 36);
  }
  return 0;
}

void ShowResult(uint64_t result) {
  for (int i = 0; i < 62; i++) {
    if ((result & 1) == 1) {
      printf("%c", GetCharFromBit(i));
    }
    result >>= 1;
  }
}

int main() {
  uint64_t result = 0;
  uint64_t buffer = 0;
  uint64_t input = 0;
  int16_t input_char = 0;

  while ((input_char = getchar()) != EOF) {
    if (input_char == '&') {
      result &= input;
      input = 0;
    } else if (input_char == '|') {
      result |= input;
      input = 0;
    } else if (input_char == '^') {
      result ^= input;
      input = 0;
    } else if (input_char == '~') {
      result |= input;
      result = ~result;
      input = 0;
    } else {
      buffer = 1;
      input |= (buffer << (FindSymbolPosition(input_char)));
    }
  }

  ShowResult(result);

  return 0;
}