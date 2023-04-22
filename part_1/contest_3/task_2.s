.text
.global main
.extern getchar_unlocked
.extern putchar_unlocked
main:
  sub sp, sp, 16
  str x30, [sp, 8]
  LoopBegin:
    bl getchar_unlocked
    cmp x0, 0
      blt LoopEnd
    cmp x0, 48
      blt LoopBegin
    cmp x0, 57
      bgt LoopBegin
    bl putchar_unlocked
    b LoopBegin
  LoopEnd:
  ldr x30, [sp, 8]
  add sp, sp, 16
  ret
