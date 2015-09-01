section .data
string db "WProtect",0
newstring db "    NewString",0
section .text
jmp start
t:
;fcmovb st0, st1 	; da c1
;fcmovbe st0, st5 	; da d1
;fcmove st0, st4 	; da c9
;fcmovnb st0, st3 	; db c1
;fcmovnbe st0, st1 	; db d1
;fcmovne st0, st1 	; db c9
;fcmovnu st0, st1 	; db d9
;fcmovu st0, st1		; da d9
FSTSW AX
mov eax,string
FMUL qword[eax]
mov ebp,eax
FADD dword[ebp + 4]
ret
nop
nop
nop
nop
nop
nop
nop
nop
nop
nop
nop
start:  
call t
ret
section .align
nop
