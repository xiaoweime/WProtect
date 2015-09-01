section .align0
nop
section .text
jmp start

stack_test:
sub esp,0x20
lea eax,[esp+30]
lea esp,[esp+0x20]
ret

start:
call stack_test
ret
section .align
nop
