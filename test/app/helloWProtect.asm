%include "WProtectSDK.inc"
section .data
   string db "HelloWorld",0xa,0x0
   len equ $-string
section .text

[GLOBAL  _start]
_start:
WProtectBegin
    mov eax,4
    mov ebx,1
    mov ecx,string
    mov edx,len
    int 0x80
    mov eax,1
    mov ebx,0
    int 0x80
WProtectEnd





