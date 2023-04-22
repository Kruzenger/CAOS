.text
.global solve

solve: 
  sxtw x0, w0
  sxtw x1, w1
  sxtw x2, w2
  sxtw x3, w3

  mov x4, x3    // x4 = D
  mov x3, x2    // x3 = C
  mov x2, x1    // x2 = B
  mov x1, x0    // x1 = A
  mov x0, 0     // x0 = 0
  mov x6, 254   // x6 = 254

  LoopBegin:          // метка начала цикла
    cmp x0, x6    // сравниваем  
      bge LoopEnd    // переходим в конец цикла, если x0 >= x6

    mov x5, x0        // x5 = x0
    mul x7, x5, x0    // x7 = x0^2  
    mul x5, x7, x0    // x5 = x0^3
    mul x5, x5, x1    // x5 = A*x0^3
    mul x7, x7, x2    // x7 = B*x0^2
    add x5, x5, x7    // x5 = A*x0^3 + B*xO^2
    mul x7, x0, x3    // x7 = C*x0
    add x5, x5, x7    // x5 = A*x0^3 + B*xO^2 + C*x0
    add x5, x5, x4    // x5 = A*x0^3 + B*xO^2 + C*x0 + D

    cmp x5, xzr
      beq LoopEnd

    add x0, x0, 1  // инкремент переменной цикла
    b LoopBegin  // переходим к началу цикла, где будет проверка
  LoopEnd:
  ret
  