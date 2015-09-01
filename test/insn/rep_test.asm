section .data
string db "WProtect",0x0
len equ $-string
newstring db "XXXXXXXX is very good",0x0
section .text
[GLOBAL _start]
jmp _start
b_movs:
rep movsb
ret
nop
nop
d_movs:
rep movsd
ret
nop
nop
_start:   
mov ecx,len
mov esi,string
mov edi,newstring
call b_movs
nop
mov ecx,2
mov esi,string
mov edi,newstring
call d_movs
ret
section .align
nop

