#include <sys/syscall.h>

long syscall(long number, ...);

void _start()
{
  char symbol; 
  
  while(syscall(SYS_read, 0, &symbol, 1)){
    syscall(SYS_write, 1, &symbol, 1);
  }
  syscall(SYS_exit, 0);
}