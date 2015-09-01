section .text
jmp start
d_mov:
mov eax,1
ret
w_mov:
mov ax,2
ret
bl_mov:
mov al,1
ret
nop
nop
bh_mov:
mov ah,1
ret
nop
nop
start:
xor eax,eax
call d_mov
xor eax,eax
call w_mov
xor eax,eax
call bl_mov
xor eax,eax
call bh_mov
ret

