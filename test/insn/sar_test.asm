section .align0
nop
section .text
jmp start
bl_sar:
sar al,3
ret
nop
bh_sar:
sar ah,3
ret
nop
w_sar:
sar ax,3
ret
d_sar:
sar eax,3
ret
nop

start:
mov al,0xae
call bl_sar
mov ah,0xae
call bh_sar
mov ax,0xaed9
call w_sar
mov eax,0xaed92b00
call d_sar
ret

section .align
nop
