#include <sys/syscall.h>

long syscall(long number, ...);

static const char kFrase[] = "Hello, World!\n";

void _start()
{
  syscall(SYS_write, 1, kFrase, sizeof(kFrase) - 1);
  syscall(SYS_exit, 0);
}