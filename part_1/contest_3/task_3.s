.text
.global main
.extern getchar_unlocked
.extern putchar_unlocked
.extern realloc
.extern free
main:
  sub sp, sp, 48
  str x30, [sp, 8]
  str x21, [sp, 16]
  str x23, [sp, 16]
  mov x1, 8
  mov x0, 0
  bl realloc
  mov x23, x0
  mov x21, 0
  LoopBegin:
    bl getchar_unlocked
    cmp x0, -1
      beq LoopEnd
    str x0, [x23, x21, lsl 3]
 
    add x21, x21, 1
    mov x0, x21
    b CountIndex
    CountIndexEnd:
      mov x1, x0
      mov x0, x23 
      bl realloc
    
      mov x23, x0
      b LoopBegin
  LoopEnd:

  Loop1Begin:
    sub x21, x21, 1
    b PrintOut 
    PrintOutEnd:   
      cmp x21, 0
        beq Loop1End
    
      b Loop1Begin
  Loop1End:
  mov x0, x23
  bl free
  ldr  x23, [sp, 16]
  ldr  x21, [sp, 16]
  ldr x30, [sp, 8]
  add sp, sp, 48
  ret

PrintOut:
  ldr x0, [x23, x21, lsl 3]
  bl putchar_unlocked 
  b PrintOutEnd

CountIndex:
  add x0, x0, 1
  mov x1, 8
  mul x0, x0, x1
  b CountIndexEnd
