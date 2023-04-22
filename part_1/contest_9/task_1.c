#include <fcntl.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
  char file_name[PATH_MAX];
  while (fgets(file_name, PATH_MAX, stdin) != NULL) {
    strtok(file_name, "\n");

    if (access(file_name, X_OK) == 0) {
      int fstr = open(file_name, O_RDONLY);
      char word[4];
      read(fstr, word, sizeof(char) * 4);
      if (!((word[0] == 127 && word[1] == 'E' && word[2] == 'L' &&
             word[3] == 'F') ||
            (word[0] == '#' && word[1] == '!'))) {
        printf("%s\n", file_name);
      } else if ((word[0] == '#' && word[1] == '!')) {
        lseek(fstr, 2, SEEK_SET);
        char buffer[PATH_MAX];
        read(fstr, buffer, PATH_MAX);
        strtok(buffer, "\n");
        if (access(buffer, X_OK) != 0) {
          printf("%s\n", file_name);
        }
      }
      close(fstr);
    }
  }
}