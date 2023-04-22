#define _OPEN_SYS_ITOA_EXT
#include <errno.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

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
  int in = open(argv[1], O_RDONLY);
  if (in == -1) {
    exit_code = 1;
    perror("Open input file");
    goto finally;
  }

  int value = 0;
  uint32_t next = 0;
  ssize_t in_read;

  lseek(in, 0, SEEK_SET);

  if (in_read = read(in, &value, sizeof(int)) > 0) {
    if (in_read == -1) {
      exit_code = 3;
      goto finally;
    }
    printa(value);
  }

  in_read = read(in, &next, sizeof(uint32_t));
  if (in_read == -1) {
    exit_code = 3;
    goto finally;
  }
  while (next != 0) {
    lseek(in, next, SEEK_SET);
    in_read = read(in, &value, sizeof(int));
    if (in_read == -1) {
      exit_code = 3;
      goto finally;
    }
    printa(value);
    in_read = read(in, &next, sizeof(uint32_t));
    if (in_read == -1) {
      exit_code = 3;
      goto finally;
    }
  }

finally:
  close(in);
  return exit_code;
}