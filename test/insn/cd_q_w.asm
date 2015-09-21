%include "WProtectSDK.inc"

section .text
jmp start
d_cdq:
WProtectBegin
cdq
ret 
WProtectEnd

w_cwd:
WProtectBegin
cwd
ret
WProtectEnd


start:
mov eax,0x80000001
call d_cdq  
mov eax,0x00008001
call w_cwd
ret
