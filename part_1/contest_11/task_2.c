#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  char word[4096];
  int counter = 0;
  while (1) {
    pid_t pid = fork();
    if (pid == 0) {
      fflush(stdin);
      if (scanf("%s", word) != EOF) {
        exit(0);
      }
      exit(1);
    }
    int status = 0;
    wait(&status);
    if (WEXITSTATUS(status)) {
      break;
    }
    ++counter;
  }

  printf("%d\n", counter);
  return 0;
}