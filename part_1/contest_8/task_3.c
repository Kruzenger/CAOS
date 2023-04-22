#include <stdint.h>
#include <stdio.h>
#include <windows.h>

void printa(int value) {
  char buffer[20];
  sprintf(buffer, "%d", value);
  for (int i = 0; *(buffer + i); ++i) {
    write(1, buffer + i, sizeof(char));
  }
  write(1, " ", sizeof(char));
}

int main(int argc, char* argv[]) {
  int exit_code = 0;
  HANDLE in = CreateFileA(argv[1], GENERIC_READ, FILE_SHARE_READ, NULL,
                          OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

  int value = 0;
  long unsigned int in_size = 0;
  ReadFile(in, &value, sizeof(int), &in_size, NULL);
  if (in_size > 0) {
    printa(value);
  }

  DWORD next = 0;
  ReadFile(in, &next, sizeof(DWORD), NULL, NULL);
  while (next != 0) {
    SetFilePointer(in, next, NULL, FILE_BEGIN);
    ReadFile(in, &value, sizeof(int), NULL, NULL);
    printa(value);
    ReadFile(in, &next, sizeof(DWORD), NULL, NULL);
  }

  CloseHandle(in);

  return exit_code;
}