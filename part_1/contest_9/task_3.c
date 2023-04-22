#include <fcntl.h>
#include <libgen.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
  char file_name[PATH_MAX];
  char link_buff[PATH_MAX];
  char path[2 * PATH_MAX];
  char result[PATH_MAX];
  while (fgets(file_name, PATH_MAX, stdin) != NULL) {
    strtok(file_name, "\n");
    struct stat st;

    if (lstat(file_name, &st) != -1) {
      if (S_ISREG(st.st_mode)) {
        char link_name[PATH_MAX] = "link_to_";
        strcat(link_name, basename(file_name));
        symlink(file_name, link_name);
      } else if (S_ISLNK(st.st_mode)) {
        ssize_t link_size =
            readlink(file_name, link_buff, PATH_MAX * sizeof(char));
        *(link_buff + link_size) = '\0';
        sprintf(path, "%s/%s", dirname(file_name), link_buff);
        realpath(path, result);
        printf("%s\n", result);
      }
    }
  }
}