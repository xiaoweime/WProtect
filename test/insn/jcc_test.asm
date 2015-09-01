%include "WProtectSDK.inc"

section .reloc
nop
section .data
nop
nop
nop
string db "WProtect",0

section .text
jmp start

jnz_test:
WProtectBegin
jnz jnz_label 
mov eax,0
ret
jnz_label:
mov eax,1
ret
WProtectEnd

jz_test:
WProtectBegin
jz jz_label 
mov eax,0
ret
jz_label:
mov eax,1
ret
WProtectEnd

ja_test:
WProtectBegin
ja ja_label 
mov eax,0
ret
ja_label:
mov eax,1
ret
WProtectEnd

jae_test:
WProtectBegin
jae jae_label 
mov eax,0
ret
jae_label:
mov eax,1
ret
WProtectEnd

jb_test:
WProtectBegin
jb jb_label 
mov eax,0
ret
jb_label:
mov eax,1
ret
WProtectEnd

jbe_test:
WProtectBegin
jbe jbe_label 
mov eax,0
ret
jbe_label:
mov eax,1
ret
WProtectEnd

jcxz_test:
WProtectBegin
jcxz jcxz_label 
mov eax,0
ret
jcxz_label:
mov eax,1
ret
WProtectEnd


jecxz_test:
WProtectBegin
jecxz jecxz_label 
mov eax,0
ret
jecxz_label:
mov eax,1
ret
WProtectEnd


jg_test:
WProtectBegin
jg jg_label 
mov eax,0
ret
jg_label:
mov eax,1
ret
WProtectEnd

jge_test:
WProtectBegin
jge jge_label 
mov eax,0
ret
jge_label:
mov eax,1
ret
WProtectEnd

jno_test:
WProtectBegin
jno jno_label 
mov eax,0
ret
jno_label:
mov eax,1
ret
WProtectEnd


jnp_test:
WProtectBegin
jnp jnp_label 
mov eax,0
ret
jnp_label:
mov eax,1
ret
WProtectEnd

jns_test:
WProtectBegin
jns jns_label 
mov eax,0
ret
jns_label:
mov eax,1
ret
WProtectEnd

jo_test:
WProtectBegin
jo jo_label 
mov eax,0
ret
jo_label:
mov eax,1
ret
WProtectEnd

jp_test:
WProtectBegin
jp jp_label 
mov eax,0
ret
jp_label:
mov eax,1
ret
WProtectEnd

js_test:
WProtectBegin
js js_label 
mov eax,0
ret
js_label:
mov eax,1
ret
WProtectEnd


jle_test:
WProtectBegin
jle jle_label 
mov eax,0
ret
jle_label:
mov eax,1
ret
WProtectEnd

jl_test:
WProtectBegin
jl jl_label 
mov eax,0
ret
jl_label:
mov eax,1
ret
WProtectEnd


start:
push 246
popfd
call jnz_test
call jz_test
call ja_test
call jae_test
call jb_test
call jbe_test
call jcxz_test
call jecxz_test
call jg_test
call jge_test
call jl_test
call jle_test
call jno_test
call jnp_test
call jns_test
call jo_test
call jp_test
call js_test
ret

section .align 
nop
nop
nop
