%include "WProtectSDK.inc"

section .text
jmp start
b_rol:
WProtectBegin
rol al,2
ret
WProtectEnd
start:
mov al,1
call b_rol
ret
  
