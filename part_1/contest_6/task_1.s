.intel_syntax noprefix
.text
.global avx_sin

avx_sin:
  movsd xmm1, xmm0
  movsd xmm2, xmm0
  
  mov rax, 1
  cvtsi2sd xmm3, rax
  movsd xmm4, xmm3
  mov rax, -1
  cvtsi2sd xmm6, rax
  
  StartLoop:
    movsd xmm5, xmm0

    mulsd xmm2, xmm1
    mulsd xmm2, xmm1
    addsd xmm3, xmm4
    divsd xmm2, xmm3
    addsd xmm3, xmm4
    divsd xmm2, xmm3
    mulsd xmm2, xmm6

    addsd xmm0, xmm2
    comisd xmm0, xmm5
      je EndLoop
    
    jmp StartLoop 
  EndLoop:
  ret 
