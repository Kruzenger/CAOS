#include <fcntl.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

static char prog_text[4096] = {
    "#include <stdio.h>\n"
    "int main(){\n"
    "int ans = (%s);\n"
    "printf(\"%%d\", ans);\n"
    "return 0;\n"
    "}\0"};

int main() {
  char buff[4096];
  char prog[4096];

  fgets(buff, sizeof(buff), stdin);
  char* sl = strchr(buff, '\n');
  if (sl) {
    *sl = '\0';
  }

  if (strnlen(buff, sizeof(buff)) == 0) {
    return 0;
  }

  snprintf(prog, sizeof(prog), prog_text, buff);

  int file = open("file.c", O_RDWR | O_CREAT, 0644);
  write(file, prog, strlen(prog));
  close(file);

  if (fork() == 0) {
    execlp("gcc", "gcc", "file.c", "-o", "file.out", NULL);
    exit(0);
  } else {
    int status = 0;
    wait(&status);
  }

  if (fork() == 0) {
    execlp("./file.out", "./file.out", NULL);
    exit(0);
  } else {
    int status = 0;
    wait(&status);
  }

  remove("file.c");
  remove("file.out");
}