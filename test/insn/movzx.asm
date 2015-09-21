%include "WProtectSDK.inc"

section .text
jmp start
b_movzx:
WProtectBegin
mov bl,1
movzx eax,bl
ret
WProtectEnd
start:
call b_movzx
ret
  
