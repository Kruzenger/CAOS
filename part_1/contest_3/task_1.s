.data
output_string:
  .asciz "%d\n"

input_string:
  .ascii "%d%d\0" 
  
z1: .word 0
z2: .word 0

.text
.global main
.extern scanf
.extern printf

main:
  sub sp, sp, 16
  str x30, [sp, 8]

  ldr w0, =input_string
  ldr w1, =z1
	ldr w2, =z2
  bl scanf

  ldr x1, =z1
	ldr x2, =z2
	ldr w1, [x1]
	ldr w2, [x2]

  add w1, w2, w1
	ldr w0, =output_string

	bl printf

  ldr x30, [sp, 8]
  add sp, sp, 16
	ret
