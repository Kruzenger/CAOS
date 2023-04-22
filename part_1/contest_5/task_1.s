.intel_syntax noprefix
.text
.global sum

sum:
  push rbx
  mov rax, rcx
  mov rcx, rdi
  cmp rcx, 0
    je end
  .loop:
    mov rbx, rcx
    dec rbx
    mov edi, [rsi + 4 * rbx]
    add edi, [rdx + 4 * rbx]
    mov [rax + 4 * rbx], edi
    loop .loop
  end:
    pop rbx
    ret
