#include <stdio.h>
#include <string.h>
#include <unistd.h>

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
  snprintf(prog, sizeof(prog), "ans = %s; print(ans)", buff);
  execlp("python3", "python3", "-c", prog, NULL);
  perror("failed to exec");
  return 1;
}