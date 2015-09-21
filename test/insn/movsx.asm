%include "WProtectSDK.inc"

section .text
jmp start
b_movsx:
WProtectBegin

movsx eax,bl
ret
WProtectEnd
start:
mov bl,0xff
call b_movsx
ret
  
