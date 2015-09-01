%include "WProtectSDK.inc"
section .align1
nop
section .text
global _main
WProtectBegin
push 1
push 2
call fuc_add 
add esp,8
WProtectEnd
ret    

fuc_add:
mov eax,[esp+4]
mov edx,[esp+8]
add eax,edx
ret

section .align
nop

