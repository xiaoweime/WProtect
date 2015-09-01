#include "SeniorVMHandle.hpp"
#include <WProtectConfig.h>
#include <algorithms>

SeniorVMHandle::SeniorVMHandle() : super_protect(false)
{
}

SeniorVMHandle::SeniorVMHandle(PCode *p) : super_protect(false)
{
  pcode = p;
}

SeniorVMHandle::~SeniorVMHandle()
{
}

void SeniorVMHandle::link_pcode(PCode *p)
{
  pcode = p;
}

void SeniorVMHandle::set_protect_grade(bool b )
{
  super_protect = b;
}

#define HANDLE pcode->pcode_info.handle_table
#define db(x) pcode->db(x)
#define dw(x) pcode->dw(x)
#define dd(x) pcode->dd(x)
#define dq(x) pcode->dq(x)
#define push_esp push_stack_top_base 

void SeniorVMHandle::push(long _register,bool _disable)
{
   pcode->v_push_register(_register,_disable);
}

void SeniorVMHandle::pop(long _register)
{
  pcode->v_pop_register(_register);
}

void SeniorVMHandle::b_not(long _register)
{
  if (_register == 0)
  {
    db(HANDLE.b_nand.handle);
    return;
  }  
  push(_register);
  db(HANDLE.push_stack_top_base.handle);
  db(HANDLE.b_read_mem.handle);

  db(HANDLE.b_nand.handle);
}

void SeniorVMHandle::w_not(long _register)
{
  if (_register == 0)
  {
    db(HANDLE.w_nand.handle);
    return;
  }
  push(_register);
  db(HANDLE.push_stack_top_base.handle);
  db(HANDLE.w_read_mem.handle);
  db(HANDLE.w_nand.handle);
}

void SeniorVMHandle::d_not(long _register)
{
  if (_register == 0)
  {
    db(HANDLE.d_nand.handle);
    return;
  }
  char n = rand()%101;
  if (n <= 10)
  {
    d_not(_register); //a = nand(_r,_r);
    pop(T_INVALID);
    d_not(_register); //b = nand(_r,_r);
    pop(T_INVALID);
    db(HANDLE.d_nand.handle); //nand(a,b)
    pop(T_INVALID);
    
    d_not(_register); //a = nand(_r,_r);
    pop(T_INVALID);
    d_not(_register); //b = nand(_r,_r);
    pop(T_INVALID);
    db(HANDLE.d_nand.handle); //nand(a,b)
    pop(T_INVALID);
    db(HANDLE.d_nand.handle);
    return;
  }
  push(_register,false);
  db(HANDLE.push_stack_top_base.handle);
  db(HANDLE.d_read_mem.handle);
  //#ifndef PROTECT_X64
  //db(HANDLE.push_stack_top_base.handle);
  //db(HANDLE.d_read_mem.handle);
  //pop(_register);
  //#endif
  db(HANDLE.d_nand.handle);
}

#ifdef PROTECT_X64
void SeniorVMHandle::q_not(long _register)
{
  if (_register == 0)
  {
    db(HANDLE.q_nand.handle);
    return;
  }
  push(_register,false);
  db(HANDLE.push_stack_top_base.handle);
  db(HANDLE.q_read_mem.handle);

  //db(HANDLE.push_stack_top_base.handle);
  //db(HANDLE.q_read_mem.handle);
  //pop(_register);

  db(HANDLE.q_nand.handle);
}
#endif
void SeniorVMHandle::b_not_and(long _register1,long _register2)
{
  if (_register1 == 0 || _register2 == 0)
  {
    db(HANDLE.b_nand.handle);
    return;
  }
  push(_register2);
  push(_register1);
  db(HANDLE.b_nand.handle);
}

void SeniorVMHandle::w_not_and(long _register1,long _register2)
{
  if (_register1 == 0 || _register2 == 0)
  {
    db(HANDLE.w_nand.handle);
    return;
  }
  push(_register2);
  push(_register1);
  db(HANDLE.w_nand.handle);
}

void SeniorVMHandle::d_not_and(long _register1,long _register2)
{
  if (_register1 == 0 || _register2 == 0)
  {
    db(HANDLE.d_nand.handle);
    return;
  }
  push(_register2,false);
  //  db(HANDLE.push_esp.handle);
  //db(HANDLE.d_read_mem.handle);
  //pop(_register2);
  
  push(_register1,false);
  //db(HANDLE.push_esp.handle);
  //db(HANDLE.d_read_mem.handle);
  //pop(_register1);
  db(HANDLE.d_nand.handle);
}
#ifdef PROTECT_X64
void SeniorVMHandle::q_not_and(long _register1,long _register2)
{
  if (_register1 == 0 || _register2 == 0)
  {
    db(HANDLE.q_nand.handle);
    return;
  }
  push(_register2,false);
  //db(HANDLE.push_esp.handle);
  //db(HANDLE.q_read_mem.handle);
  //pop(_register2);
  
  push(_register1,false);
  //db(HANDLE.push_esp.handle);
  //db(HANDLE.q_read_mem.handle);
  //pop(_register1);
  db(HANDLE.q_nand.handle);
}
#endif

void SeniorVMHandle::b_and(long _register1,long _register2) //先是第二个 
{ //and _register1,_register2
  
  //pcode->v_push_register(_register2);
  //db(HANDLE.push_esp.handle);
  //db(HANDLE.b_read_mem.handle);
  //db(HANDLE.b_rand);
  b_not(_register2);
  pop(T_INVALID);
  //pcode->v_push_register(_register1);
  //db(HANDLE.push_esp.handle);
  //db(HANDLE.b_read_mem.handle);
  //db(HANDLE.b_rand);
  b_not(_register1);
  pop(T_INVALID);
  db(HANDLE.b_nand.handle);
  //pcode->v_pop_register(T_EFLAG);
  //pcode->v_pop_register(_register1);
}

void SeniorVMHandle::w_and(long _register1,long _register2)
{
  w_not(_register2);
  pop(T_INVALID);
  w_not(_register1);
  pop(T_INVALID);
  db(HANDLE.w_nand.handle);
}

void SeniorVMHandle::d_and(long _register1,long _register2)
{
  d_not(_register2);
  pop(T_INVALID);
  d_not(_register1);
  pop(T_INVALID);
  db(HANDLE.d_nand.handle);
}

#ifdef PROTECT_X64
void SeniorVMHandle::q_and(long _register1,long _register2)
{
  q_not(_register2);
  pop(T_INVALID);
  q_not(_register1);
  pop(T_INVALID);
  db(HANDLE.q_nand.handle);
}
#endif

void SeniorVMHandle::b_or(long _register1,long _register2)
{
  b_not_and(_register1,_register2);
  pop(T_INVALID);
  b_not_and(_register1,_register2);
  pop(T_INVALID);
  db(HANDLE.b_nand.handle);
}

void SeniorVMHandle::w_or(long _register1,long _register2)
{
  w_not_and(_register1,_register2);
  pop(T_INVALID);
  w_not_and(_register1,_register2);
  pop(T_INVALID);
  db(HANDLE.w_nand.handle);
}

void SeniorVMHandle::d_or(long _register1,long _register2)
{
  d_not_and(_register1,_register2);
  pop(T_INVALID);
  d_not_and(_register1,_register2);
  pop(T_INVALID);
  db(HANDLE.d_nand.handle);
}
#ifdef PROTECT_X64
void SeniorVMHandle::q_or(long _register1,long _register2)
{
  q_not_and(_register1,_register2);
  pop(T_INVALID);
  q_not_and(_register1,_register2);
  pop(T_INVALID);
  db(HANDLE.q_nand.handle);
}
#endif
void SeniorVMHandle::b_xor(long _register1,long _register2)
{
  b_not_and(_register1,_register2);
  pop(T_INVALID);
  b_and(_register1,_register2);
  pop(T_INVALID);
  db(HANDLE.b_nand.handle);
}

void SeniorVMHandle::w_xor(long _register1,long _register2)
{
  w_not_and(_register1,_register2);
  pop(T_INVALID);
  w_and(_register1,_register2);
  pop(T_INVALID);
  db(HANDLE.w_nand.handle);
}

void SeniorVMHandle::d_xor(long _register1,long _register2)
{
  d_not_and(_register1,_register2);
  pop(T_INVALID);
  d_and(_register1,_register2);
  pop(T_INVALID);
  db(HANDLE.d_nand.handle);
}
#ifdef PROTECT_X64
void SeniorVMHandle::q_xor(long _register1,long _register2)
{
  q_not_and(_register1,_register2);
  pop(T_INVALID);
  q_and(_register1,_register2);
  pop(T_INVALID);
  db(HANDLE.q_nand.handle);
}
#endif

void SeniorVMHandle::pushf()
{
  pcode->v_push_register(T_EFLAG);
}

void SeniorVMHandle::pushad()
{
  
  int mode = 0;
#ifndef PROTECT_X64
  mode = T_E32X;
#endif  
  pcode->v_push_register(T_RAX | mode);
  pcode->v_push_register(T_RCX | mode);
  pcode->v_push_register(T_RDX | mode);
  pcode->v_push_register(T_RBX | mode);
  pcode->v_push_register(T_RSP | mode);
  pcode->v_push_register(T_RBP | mode);
  pcode->v_push_register(T_RSI | mode);
  pcode->v_push_register(T_RDI | mode);
#ifdef PROTECT_X64
  pcode->v_push_register(T_R8);
  pcode->v_push_register(T_R9);
  pcode->v_push_register(T_R10);
  pcode->v_push_register(T_R11);
  pcode->v_push_register(T_R12);
  pcode->v_push_register(T_R13);
  pcode->v_push_register(T_R14);
  pcode->v_push_register(T_R15);
#endif
  
  //int register_count =  pcode->register_store_in.register_count;
}

void SeniorVMHandle::b_shl(long _register,char n)
{
  push(_register);
  b_push_imm(n);
  db(HANDLE.b_shl.handle);
}

void SeniorVMHandle::w_shl(long _register,char n)
{
  push(_register);
  b_push_imm(n);
  db(HANDLE.w_shl.handle);
}

void SeniorVMHandle::d_shl(long _register,char n)
{
  push(_register,false);
  b_push_imm(n);
  db(HANDLE.d_shl.handle);
}
#ifdef PROTECT_X64
void SeniorVMHandle::q_shl(long _register,char n)
{
  push(_register,false);
  b_push_imm(n);
  db(HANDLE.q_shl.handle);
}
#endif

void SeniorVMHandle::b_shr(long _register,char n)
{
  push(_register);
  b_push_imm(n);
  db(HANDLE.b_shr.handle);
}

void SeniorVMHandle::w_shr(long _register,char n)
{
  push(_register);
  b_push_imm(n);
  db(HANDLE.w_shr.handle);
}

void SeniorVMHandle::d_shr(long _register,char n)
{
  push(_register,false);
  b_push_imm(n);
  db(HANDLE.d_shr.handle);
}
#ifdef PROTECT_X64
void SeniorVMHandle::q_shr(long _register,char n)
{
  push(_register,false);
  b_push_imm(n);
  db(HANDLE.q_shr.handle);
}
#endif
void SeniorVMHandle::b_push_imm(char n)
{
  db(HANDLE.b_push_imm.handle);
  db(n);
}

void SeniorVMHandle::w_push_imm(short n)
{
  db(HANDLE.w_push_imm.handle);
  dw(n);
}

void SeniorVMHandle::d_push_imm(int n)
{
  db(HANDLE.d_push_imm.handle);
  dd(n);
}
#ifdef PROTECT_X64
void SeniorVMHandle::q_push_imm(long n)
{
  db(HANDLE.q_push_imm.handle);
  dq(n);
}
#endif

void SeniorVMHandle::save_vm_context()
{
  int register_count = pcode->register_store_in.register_count;
  for (int i = register_count; i > 0; --i)
  {
    pop(pcode->register_store_in.register_array[i-1]);
  }
}

void SeniorVMHandle::recover_vm_context()
{
  int register_count = pcode->register_store_out.register_count;
  for (int i = register_count; i > 0; --i)
  {
    push(pcode->register_store_out.register_array[i-1]);
  }
}


void SeniorVMHandle::popad()
{
#ifdef PROTECT_X64
  pcode->v_pop_register(T_R15);
  pcode->v_pop_register(T_R14);
  pcode->v_pop_register(T_R13);
  pcode->v_pop_register(T_R12);
  pcode->v_pop_register(T_R11);
  pcode->v_pop_register(T_R10);
  pcode->v_pop_register(T_R9);
  pcode->v_pop_register(T_R8);
#endif
  
  int mode = 0;
#ifndef PROTECT_X64
  mode = T_E32X;
#endif
  pcode->v_pop_register(T_RDI | mode);
  pcode->v_pop_register(T_RSI | mode);
  pcode->v_pop_register(T_RBP | mode);
  pcode->v_pop_register(T_RSP | mode);
  pcode->v_pop_register(T_RBX | mode);
  pcode->v_pop_register(T_RDX | mode);
  pcode->v_pop_register(T_RCX | mode);
  pcode->v_pop_register(T_RAX | mode);
}

void SeniorVMHandle::popf()
{
  pcode->v_pop_register(T_EFLAG);
}

void SeniorVMHandle::exit()
{
  pcode->v_push_register(T_RET);
  pushf();
  pushad();
  
  db(HANDLE.ret.handle);
}

void SeniorVMHandle::start()
{
  //popad();
  //popf();
  //pop(T_KEY);
  save_vm_context();
  //pop(T_RET);
}

#define T_TMP_EFLAG T_TMP_REGISTER5

void SeniorVMHandle::b_add_b(long _register1,long _register2)
{
  d_push_imm(0);
  pop(T_TMP_REGISTER3);
  
  b_and(_register1,_register2);
  pop(T_INVALID);
  b_xor(_register1,_register2);
  pop(T_INVALID);
  pop(T_TMP_R8_1H);
  b_push_imm(1<<7);
  pop(T_TMP_R8_1L);
  pop(T_TMP_R8_2H);
  b_and(T_TMP_R8_2H,T_TMP_R8_1L);
  pop(T_INVALID);
  pop(T_TMP_R8_3L);
  d_shr(T_TMP_REGISTER3,7);
  pop(T_INVALID);
  pop(T_TMP_REGISTER3);
  d_or(T_TMP_REGISTER3,T_TMP_EFLAG);
  pop(T_INVALID);
  pop(T_TMP_EFLAG);

  d_push_imm(0);
  pop(T_TMP_REGISTER3);
  
  b_push_imm(1<<3);
  pop(T_TMP_R8_3H);
  b_and(T_TMP_R8_3H,T_TMP_R8_2H);
  pop(T_INVALID);
  pop(T_TMP_R8_2L);
  
  b_shl(T_TMP_R8_2L,1);
  pop(T_INVALID);
  pop(T_TMP_R8_3L);
  d_or(T_TMP_REGISTER3,T_TMP_EFLAG);
  pop(T_INVALID);
  pop(T_TMP_EFLAG);
  b_shl(T_TMP_R8_2H,1);
  pop(T_INVALID);
  pop(T_TMP_R8_2H);
}

void SeniorVMHandle::b_add(long _register1,long _register2)
{
  push(_register1);
  push(_register2);
  db(HANDLE.b_add.handle);
}

void SeniorVMHandle::w_add(long _register1,long _register2)
{
  push(_register1);
  push(_register2);
  db(HANDLE.w_add.handle);
}

void SeniorVMHandle::d_add_d(long _register1,long _register2)
{
  d_and(_register1,_register2);  //8
  pcode->v_pop_register(T_INVALID); //4
  
  d_xor(_register1,_register2); 
  pcode->v_pop_register(T_INVALID); //4
  //pcode->v_pop_register(T_TMPconst T_TMP_R8_3H_R8_1L);
  pcode->v_pop_register(T_TMP_REGISTER1);


  ///这里保存CF 判断是否进位
  // pcode->v_push_register(T_TMP_REGISTER4);

  db(HANDLE.d_push_imm.handle); // var1 = 1<<31
  dd(1<<31);  //8
  pcode->v_pop_register(T_TMP_REGISTER4); //4
  pcode->v_pop_register(T_TMP_REGISTER3);//AND结果 0
  
  d_and(T_TMP_REGISTER4,T_TMP_REGISTER3); //8
  pcode->v_pop_register(T_INVALID); //4
 
  db(HANDLE.b_push_imm.handle);
  db(31);
  db(HANDLE.d_shr.handle);
  pcode->v_pop_register(T_INVALID);
  
  pcode->v_pop_register(T_TMP_REGISTER4);//AND结果  //0
  d_or(T_TMP_REGISTER4,T_TMP_EFLAG); 
  pcode->v_pop_register(T_INVALID);
    
  pcode->v_pop_register(T_TMP_EFLAG); //0
  ///end

  ///这里保存AF 判断bit3是否进位到bit4
  db(HANDLE.d_push_imm.handle);
  dd(1<<3);
  pcode->v_pop_register(T_TMP_REGISTER4);
  d_and(T_TMP_REGISTER4,T_TMP_REGISTER3); //8
  pcode->v_pop_register(T_INVALID);

  db(HANDLE.b_push_imm.handle); //左移一位
  db(1);
  db(HANDLE.d_shl.handle);
  
  pcode->v_pop_register(T_INVALID);
  
  pcode->v_pop_register(T_TMP_REGISTER4); //0

  
  d_or(T_TMP_REGISTER4,T_TMP_EFLAG); //8
  pcode->v_pop_register(T_INVALID);
  pcode->v_pop_register(T_TMP_EFLAG); //0*/
  
  //pcode->v_pop_register(T_INVALID); //第一个and的标志位
  pcode->v_push_register(T_TMP_REGISTER3);
  db(HANDLE.b_push_imm.handle);
  db(1);
  db(HANDLE.d_shl.handle);
  pcode->v_pop_register(T_INVALID);
  pcode->v_pop_register(T_TMP_REGISTER2);  
}

//OF 原本是0 结果变成1 或者相反    = 1 否这 = 0
//CF 超出能数值表示范围 至 = 1
//AF

void SeniorVMHandle::d_add(long _register1,long _register2)
{
  if (!super_protect)
  {
    push(_register1,false);
    push(_register2,false);
    db(HANDLE.d_add.handle);
    return;
  }

  //return;
  
  /*  db(HANDLE.d_push_imm.handle);
  dd(1<<31);
  pcode->v_pop_register(T_TMP_REGISTER3);
  d_and(_register1,T_TMP_REGISTER3);
  pcode->v_pop_register(T_INVALID);
  db(HANDLE.b_push_imm.handle);
  db(20);
  db(HANDLE.d_shr.handle);
  pcode->v_pop_register(T_INVALID);
  pcode->v_pop_register(T_TMP_EFLAG);*/
  d_xor(_register1,_register2);
  pcode->v_pop_register(T_INVALID);
  pcode->v_pop_register(T_TMP_REGISTER1);
  d_not(T_TMP_REGISTER1);
  pcode->v_pop_register(T_INVALID);
  db(HANDLE.d_push_imm.handle);
  dd(0x80000000);
  pcode->v_pop_register(T_TMP_REGISTER2);
  pcode->v_pop_register(T_TMP_REGISTER3);
  d_and(T_TMP_REGISTER3,T_TMP_REGISTER2);
  pcode->v_pop_register(T_INVALID);
  //  db(HANDLE.b_push_imm.handle);
  //  db(20);
  //  db(HANDLE.d_shr.handle);
  //  pcode->v_pop_register(T_INVALID);
  pcode->v_pop_register(T_TMP_EFLAG);
  
  d_add_d(_register1,_register2);
 for (int i = 0; i < 31; ++i) //6次 留一次填充标志位
 {
    d_add_d(T_TMP_REGISTER2,T_TMP_REGISTER1);
 }
//pcode->v_push_register(T_TMP_R32_2);
// pcode->v_push_register(T_TMP_EFLAG);
 //pcode->v_push_register(T_TMP_REGISTER1);

  ///OF 判断是否溢出


  d_xor(_register2,T_TMP_REGISTER1);
 pcode->v_pop_register(T_INVALID);
 pcode->v_pop_register(T_TMP_REGISTER3);
 db(HANDLE.d_push_imm.handle);
 dd(0x80000000);
 pcode->v_pop_register(T_TMP_REGISTER4);
 d_and(T_TMP_REGISTER4,T_TMP_REGISTER3);
 pcode->v_pop_register(T_INVALID);
 pcode->v_pop_register(T_TMP_REGISTER3);

 d_and(T_TMP_EFLAG,T_TMP_REGISTER3);
 pcode->v_pop_register(T_INVALID);
 
 db(HANDLE.b_push_imm.handle);
 db(20);
 db(HANDLE.d_shr.handle);
 
 pcode->v_pop_register(T_INVALID);
 pcode->v_pop_register(T_TMP_REGISTER4);
 //db(HANDLE.d_push_imm.handle);
 //dd(0x800);
 //pcode->v_pop_register(T_TMP_REGISTER3);
 // d_and(T_TMP_REGISTER3,T_TMP_REGISTER4);
 // pcode->v_pop_register(T_INVALID);
 //pcode->v_pop_register(T_TMP_REGISTER3);
 //d_and(T_TMP_EFLAG,T_TMP_REGISTER3); //这时候的OF还在最高位
 //pcode->v_pop_register(T_INVALID);
 //pcode->v_pop_register(T_TMP_REGISTER3);
 //db(HANDLE.d_push_imm.handle);
 //dd(0xFFFFF7FF);
 //pcode->v_pop_register(T_TMP_REGISTER3);
 //d_or(T_TMP_REGISTER3,T_TMP_REGISTER4);
 //pcode->v_pop_register(T_INVALID);
 //pcode->v_pop_register(T_TMP_REGISTER4);
 
 d_or(T_TMP_EFLAG,T_TMP_REGISTER4);
 pcode->v_pop_register(T_INVALID);
 pcode->v_pop_register(T_TMP_EFLAG);
 /*pcode->v_push_register(T_TMP_EFLAG); 
 db(HANDLE.push_esp.handle);
 db(HANDLE.d_read_mem.handle); 
 pcode->v_pop_register(T_TMP_EFLAG);
 db(HANDLE.b_push_imm.handle);
 db(20);
 db(HANDLE.d_shl.handle);
 pcode->v_pop_register(T_INVALID);
 pcode->v_pop_register(T_TMP_REGISTER3);
 
 d_xor(_register1,T_TMP_REGISTER3);
 pcode->v_pop_register(T_INVALID);
 //pcode->v_pop_register(T_TMP_REGISTER3);
  db(HANDLE.b_push_imm.handle);
 db(20);
 db(HANDLE.d_shr.handle);
 pcode->v_pop_register(T_INVALID);
 pcode->v_pop_register(T_TMP_REGISTER4);
 db(HANDLE.d_push_imm.handle);
 dd(0x800);
 pcode->v_pop_register(T_TMP_REGISTER3);
 d_and(T_TMP_REGISTER3,T_TMP_REGISTER4);
 pcode->v_pop_register(T_INVALID);
 pcode->v_pop_register(T_TMP_REGISTER3);
 d_and(T_TMP_EFLAG,T_TMP_REGISTER3);
 pcode->v_pop_register(T_INVALID);
 pcode->v_pop_register(T_TMP_REGISTER3);
 d_or(T_TMP_EFLAG,T_TMP_REGISTER3);
 pcode->v_pop_register(T_INVALID);
 pcode->v_pop_register(T_TMP_EFLAG);*/
 /////end OF
  d_and(T_TMP_REGISTER1,T_TMP_REGISTER1);
  pcode->v_pop_register(T_TMP_REGISTER2); //EFLAG
  d_or(T_TMP_EFLAG,T_TMP_REGISTER2);
  pcode->v_pop_register(T_INVALID);
  /* 
  pcode->v_push_register(T_TMP_EFLAG);
  db(HANDLE.push_esp.handle);
  db(HANDLE.d_read_mem.handle);
  pcode->v_pop_register(T_TMP_EFLAG);
  db(HANDLE.b_push_imm.handle);
  db(31);
  db(HANDLE.d_shr.handle);
  pcode->v_pop_register(T_INVALID);
  pcode->v_pop_register(T_TMP_REGISTER3);
  d_or(T_TMP_REGISTER3,T_TMP_REGISTER2);
  pcode->v_pop_register(T_INVALID);
  /*  pcode->v_pop_register(T_TMP_REGISTER2);
  
  pcode->v_push_register(T_TMP_EFLAG);
  db(HANDLE.push_esp.handle);
  db(HANDLE.d_read_mem.handle);
  pcode->v_pop_register(T_TMP_EFLAG);
  db(HANDLE.b_push_imm.handle);
  db(3);
  db(HANDLE.d_shr.handle);
  pcode->v_pop_register(T_INVALID);
  pcode->v_pop_register(T_TMP_REGISTER3);
  d_and(T_TMP_REGISTER3,T_TMP_REGISTER2);
  pcode->v_pop_register(T_INVALID);
  pcode->v_pop_register(T_TMP_REGISTER2);

  pcode->v_push_register(T_TMP_EFLAG);
  db(HANDLE.d_push_imm.handle);
  db(1<<11);
  pcode->v_pop_register(T_TMP_REGISTER3);
  d_xor(T_TMP_REGISTER3,T_TMP_REGISTER2);
  pcode->v_pop_register(T_INVALID);
  //pcode->v_push_register(T_TMP_REGISTER3);
  pcode->v_pop_register(T_TMP_REGISTER4);
  d_and(T_TMP_REGISTER3,T_TMP_REGISTER4);
  pcode->v_pop_register(T_INVALID);
  pcode->v_pop_register(T_TMP_REGISTER4);
  d_or(T_TMP_REGISTER4,T_TMP_REGISTER2);
  pcode->v_pop_register(T_INVALID);*/
  
//db(HANDLE.push_esp.handle);
//db(HANDLE.d_read_mem.handle);

//  pcode->v_pop_register(T_EAX);
}
#ifdef PROTECT_X64
void SeniorVMHandle::q_add(long _register1,long _register2)
{
  push(_register1);
  push(_register2);
  db(HANDLE.q_add.handle);
}
#endif
void SeniorVMHandle::b_push_imm_sx(char n)
{
  db(HANDLE.b_push_imm_sx.handle);
  db(n);
}

void SeniorVMHandle::w_push_imm_sx(short n)
{
  db(HANDLE.w_push_imm_sx.handle);
  dw(n);
}
#ifdef PROTECT_X64
void SeniorVMHandle::d_push_imm_sx(int n)
{
  db(HANDLE.d_push_imm_sx.handle);
  dd(n);
}
#endif
void SeniorVMHandle::b_push_imm_zx(char n)
{
  db(HANDLE.b_push_imm_zx.handle);
  db(n);
}

void SeniorVMHandle::w_push_imm_zx(short n)
{
  db(HANDLE.w_push_imm_zx.handle);
  dw(n);
}
#ifdef PROTECT_X64
void SeniorVMHandle::d_push_imm_zx(int n)
{
  db(HANDLE.d_push_imm_zx.handle);
  dd(n);
}
#endif
void SeniorVMHandle::b_copy_stack()
{
  db(HANDLE.push_esp.handle);
  db(HANDLE.b_read_mem.handle);
}

void SeniorVMHandle::w_copy_stack()
{
  db(HANDLE.push_esp.handle);
  db(HANDLE.w_read_mem.handle);
}

void SeniorVMHandle::d_copy_stack()
{
  db(HANDLE.push_esp.handle);
  db(HANDLE.d_read_mem.handle);
}
#ifdef PROTECT_X64
void SeniorVMHandle::q_copy_stack()
{
  db(HANDLE.push_esp.handle);
  db(HANDLE.q_read_mem.handle);
}
#endif
void SeniorVMHandle::b_sub(long _register1,long _register2)
{
  b_not(_register1);
  pop(T_INVALID);
  pop(T_TMP_R8_8L);
  b_add(T_TMP_R8_8L,_register2);
  //  pop(T_INVALID);
  pop(T_TMP_REGISTER6); //eflag 1
  b_copy_stack();
  b_not_and();
  pop(T_TMP_REGISTER7); //eflag 2 
  //pop(T_TMP_REGISTER8); //结果

  d_not(T_TMP_REGISTER6);
  pop(T_INVALID);
  w_push_imm_sx(0xf7ea);
  d_not_and();
  pop(T_INVALID);
  pop(T_TMP_REGISTER6);
  
  d_not(T_TMP_REGISTER7);
  pop(T_INVALID);
  w_push_imm_sx(0x815);
  d_not_and();
  pop(T_INVALID);
  pop(T_TMP_REGISTER7);
  d_add(T_TMP_REGISTER6,T_TMP_REGISTER7);
  pop(T_INVALID);
}

void SeniorVMHandle::w_sub(long _register1,long _register2)
{
  w_not(_register1);  //sub eax,ebx = add((not eax),ebx) 
  pop(T_INVALID);
  pop(T_TMP_R16_8);
  b_add(T_TMP_R16_8,_register2);
  //  pop(T_INVALID);
  pop(T_TMP_REGISTER6); //eflag 1
  w_copy_stack();
  w_not_and();
  pop(T_TMP_REGISTER7); //eflag 2 
  //pop(T_TMP_REGISTER8); //结果

  d_not(T_TMP_REGISTER6);
  pop(T_INVALID);
  w_push_imm_sx(0xf7ea);
  d_not_and();
  pop(T_INVALID);
  pop(T_TMP_REGISTER6);
  
  d_not(T_TMP_REGISTER7);
  pop(T_INVALID);
  w_push_imm_sx(0x815);
  d_not_and();
  pop(T_INVALID);
  pop(T_TMP_REGISTER7);
  d_add(T_TMP_REGISTER6,T_TMP_REGISTER7);
  pop(T_INVALID);
}

void SeniorVMHandle::d_sub(long _register1,long _register2)
{
  d_not(_register1);
  pop(T_INVALID);
  pop(T_TMP_REGISTER8);
  d_add(T_TMP_REGISTER8,_register2);
  //  pop(T_INVALID);
  pop(T_TMP_REGISTER6); //eflag 1
  d_copy_stack();
  d_not_and();
  pop(T_TMP_REGISTER7); //eflag 2 
  //pop(T_TMP_REGISTER8); //结果

  d_not(T_TMP_REGISTER6);
  pop(T_INVALID);
  w_push_imm_sx(0xf7ea);
  d_not_and();
  pop(T_INVALID);
  pop(T_TMP_REGISTER6);
  
  d_not(T_TMP_REGISTER7);
  pop(T_INVALID);
  w_push_imm_sx(0x815);
  d_not_and();
  pop(T_INVALID);
  pop(T_TMP_REGISTER7);
  d_add(T_TMP_REGISTER6,T_TMP_REGISTER7);
  pop(T_INVALID);
}
#ifdef PROTECT_X64
void SeniorVMHandle::q_sub(long _register1,long _register2)
{
  q_not(_register1);
  pop(T_INVALID);
  pop(T_TMP_REGISTER8);
  q_add(T_TMP_REGISTER8,_register2);
  //  pop(T_INVALID);
  pop(T_TMP_REGISTER6); //eflag 1
  q_copy_stack();
  q_not_and();
  pop(T_TMP_REGISTER7); //eflag 2 
  //pop(T_TMP_REGISTER8); //结果

  q_not(T_TMP_REGISTER6);
  pop(T_INVALID);
  w_push_imm_sx(0xf7ea);
  q_not_and();
  pop(T_INVALID);
  pop(T_TMP_REGISTER6);
  
  q_not(T_TMP_REGISTER7);
  pop(T_INVALID);
  w_push_imm_sx(0x815);
  q_not_and();
  pop(T_INVALID);
  pop(T_TMP_REGISTER7);
  q_add(T_TMP_REGISTER6,T_TMP_REGISTER7);
  pop(T_INVALID);
}
#endif

void SeniorVMHandle::b_cmp(long _register1,long _register2)
{
  b_sub(_register1,_register2);
  pop(T_EFLAG);
  pop(T_INVALID8H);
}

void SeniorVMHandle::w_cmp(long _register1,long _register2)
{
  w_sub(_register1,_register2);
  pop(T_EFLAG);
  pop(T_INVALID16);
}

void SeniorVMHandle::d_cmp(long _register1,long _register2)
{
  d_sub(_register1,_register2);
  pop(T_EFLAG);
  pop(T_INVALID32);
}

#ifdef PROTECT_X64
void SeniorVMHandle::q_cmp(long _register1,long _register2)
{
  q_sub(_register1,_register2);
  pop(T_EFLAG);
  pop(T_INVALID);
}
#endif

//带r的表示real真实的
//比如这条指令计算真正的内存地址

void SeniorVMHandle::r_get_mem(
                                  long _register_index,
                                  long _register_base,
                                  long _scale,
                                  long _lval)
{
  //_lval += 0x20;
  char sn = 0;
  for (int i = 0; i < 32; i++)
  {
    if (_scale == 1<<i)
    {
      sn = i;
      break;
    }
  }
  if (_register_index || _register_base || _scale || _lval)
  {
    //d_add(_register_index,_register_base);
    d_shl(_register_base,sn);
    pop(T_INVALID);
    pop(T_TMP_REGISTER5);
    d_add(_register_index,T_TMP_REGISTER5);
    pop(T_INVALID);
    pop(T_TMP_REGISTER5);
    d_push_imm(_lval);
    pop(T_TMP_REGISTER4);
    d_add(T_TMP_REGISTER5,T_TMP_REGISTER4);
    pop(T_INVALID);
  } else if (_register_index || _register_base || _lval)
  {
    
  } else if (_register_index || _scale || _lval)
  {
    
  } else if (_register_index || _register_base)
  {
    d_add(_register_index,_register_base);
    pop(T_INVALID);
  } else if (_register_base || _lval)
  {
    d_push_imm(_lval);
    pop(T_TMP_REGISTER4);
    d_add(_register_base,T_TMP_REGISTER4);
    pop(T_INVALID);
  } else if (_register_index || _lval)
  {
    d_push_imm(_lval);
    pop(T_TMP_REGISTER4);
    d_add(_register_index,T_TMP_REGISTER4);
    pop(T_INVALID);
  } else if (_register_index)
  {
    push(_register_index);
  } else if (_register_base)
  {
    
  }
}
