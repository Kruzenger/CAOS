#include <sys/syscall.h>
  .intel_syntax noprefix
  .global _start

  .data
symbol: .word 0
symbol_ptr: .quad symbol

  .text
_start:
  push rbx
  push rbp
  LoopBegin:
    mov eax, SYS_read
    mov edi, 0
    mov esi, symbol_ptr
    mov edx, 1
    syscall
    cmp rax, 0
      je LoopEnd
    mov eax, SYS_write
    mov edi, 1
    mov esi, symbol_ptr
    mov edx, 1
    syscall
    jmp LoopBegin
  LoopEnd:
  pop rbp
  pop rbx
  mov eax, SYS_exit
  syscall
