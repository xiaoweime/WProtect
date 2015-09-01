%include "WProtectSDK.inc"

section .text
push 1
push 2
call fuc_test
add esp,8
ret

fuc_test:
WProtectBegin
mov eax,[esp+4]
mov edx,[esp+8]  
add eax,edx
ret
WProtectEnd
