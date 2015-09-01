section .text
jmp start

d_add:
add eax,1
ret
nop
w_add:

add ax,1
ret

bl_add:
add al,1
ret
nop
nop

bh_add:
add ah,1
ret
nop
nop

start:
xor eax,eax
call d_add
xor eax,eax
call w_add
xor eax,eax
call bl_add
xor eax,eax
call bh_add  
ret
