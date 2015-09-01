#include "AsmJit.h"

using namespace AsmJit;

#ifdef PROTECT_X64
GPReg jit_reg[  ] = {
  al,cl,dl,bl,ah,ch,dh,bh,
  ax,cx,dx,bx,bx,sp,si,di,
  eax,ecx,edx,ebx,esp,esi,edi,
  rax,rcx,rdx,rbx,rsp,rsi,rdi,
  r8,r9,r10,r11,r12,r13,r14,r15
};
char * ia86_reg[  ] = {
  "al","cl","dl","bl","ah","ch","dh","bh",
  "ax","cx","dx","bx","bx","sp","si","di",
  "eax","ecx","edx","ebx","esp","esi","edi",
  "rax","rcx","rdx","rbx3","rsp","rsi","rdi",
  "r8","r9","r10","r11","r12","r13","r14","r15"
};
#else
GPReg jit_reg[  ] = {
  al,cl,dl,bl,ah,ch,dh,bh,
  ax,cx,dx,bx,bx,sp,si,di,
  eax,ecx,edx,ebx,esp,esi,edi
};
char * ia86_reg[  ] = {
  "al","cl","dl","bl","ah","ch","dh","bh",
  "ax","cx","dx","bx","bx","sp","si","di",
  "eax","ecx","edx","ebx","esp","esi","edi"
};
#endif




GPReg text_to_reg( char *src );
