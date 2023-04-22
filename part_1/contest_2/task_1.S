.text      

.global sum

sum:
    mov x5, 4
    mul x1, x1, x5
    mov x5, 0
    LoopBegin:
      cmp x5, x1
        bge LoopEnd
      ldr x4, [x2, x5]
      add x0, x0, x4
      add x5, x5, 4
      b LoopBegin
    LoopEnd:
    ret