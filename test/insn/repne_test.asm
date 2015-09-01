section .data
string db "WProtect",0xA
len equ $-string
section .text
[GLOBAL _start]
jmp _start
find:
repne scasb
ret
nop
nop
nop
_start:   
mov al,'t'
or ecx,0xffffffff
mov edi,string
call find
not ecx
ret
section .align
nop

