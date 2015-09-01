section .data
string db 't',0xA
len equ $-string
section .text
[GLOBAL _start]
jmp _start
find:
scasb
ret
nop
nop
nop
_start:   
mov al,'t'
mov edi,string
call find
not ecx
ret
section .align
nop

