.intel_syntax noprefix
.global dot_product
.text
dot_product: // (size_t N, float* A, float* B)
//                 rdi,      rsi,      rdx
  mov rcx, 0
  vxorpd ymm0, ymm0, ymm0
  sub rdi, 4
  LoopStart:
    cmp rcx, rdi
      jg LoopEnd

    vmovups ymm1, [rsi + rcx * 4]
    vmovups ymm2, [rdx + rcx * 4]
    vdpps ymm3, ymm1, ymm2, 0xFF
    vaddps ymm0, ymm0, ymm3
    add rcx, 4 
    jmp LoopStart
  LoopEnd:
    add rdi, 4
  Lope:
  cmp rcx, rdi
    jge LoopEndEnd
  movss xmm1, [rsi + rcx * 4]
  movss xmm2, [rdx + rcx * 4]
  mulss xmm1, xmm2
  vinsertf128 ymm1, ymm1, xmm1, 0 
  vaddps ymm0, ymm0, ymm1
  add rcx, 1
  jmp Lope
  LoopEndEnd:
  ret
