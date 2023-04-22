#define _GNU_SOURCE
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

struct Item {
  int value;
  uint32_t next_pointer;
};

int main(int argc, char* argv[]) {
  int file = open(argv[1], O_RDONLY);
  if (file == -1) {
    return 0;
  }

  struct stat status;
  fstat(file, &status);
  struct Item* input =
      mmap(NULL, status.st_size, PROT_READ, MAP_PRIVATE, file, 0);

  // realisation

  if (status.st_size > 0) {
    struct Item* current = input;

    while (current->next_pointer != 0) {
      printf("%d ", current->value);
      current = input + (current->next_pointer / sizeof(struct Item));
    }

    printf("%d ", current->value);
  }

  // postprocess

  munmap(input, status.st_size);
  close(file);
  return 0;
}