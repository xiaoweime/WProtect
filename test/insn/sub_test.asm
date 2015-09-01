section .text
jmp start

d_sub:
sub eax,1
ret
nop
w_sub:

sub ax,1
ret

bl_sub:
sub al,1
ret
nop
nop

bh_sub:
sub ah,1
ret
nop
nop

start:
xor eax,eax
call d_sub
xor eax,eax
call w_sub
xor eax,eax
call bl_sub
xor eax,eax
call bh_sub  
ret
