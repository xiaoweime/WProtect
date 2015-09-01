/*
 *
 *   Copyright (C) Mon May 20 00:07:29 2013 XiaoWei
 *
 *                       handsomexiaowei@gmail.com
 *
 *
 */

#ifndef _SENIORVMHANDLE_H_
#define _SENIORVMHANDLE_H_

//操作组合

#include "VMHandle.h"
#include "PCode.hpp"

#include <VOperand.hpp>

class SeniorVMHandle
{
 public:
  SeniorVMHandle();
  SeniorVMHandle(PCode *p);
  ~SeniorVMHandle(  );


  bool super_protect;

  long get_code_size();
  void link_pcode(PCode *p);
  void set_protect_grade(bool b );
  char push_operand( pVOperand o );
  char pop_operand(pVOperand o);
  void b_not_and(long _register1 = 0,long _register2 = 0,bool is_data = false);
  void w_not_and(long _register1 = 0,long _register2 = 0,bool is_data = false);
  void d_not_and(long _register1 = 0,long _register2 = 0,bool is_data = false);
  void q_not_and(long _register1 = 0,long _register2 = 0,bool is_data = false);
  char v_not_and(pVOperand o1,pVOperand o2  );


  void b_not(long _register,bool is_data = false);
  void w_not(long _register,bool is_data = false);
  void d_not(long _register,bool is_data = false);
  void q_not(long _register,bool is_data = false);
  char v_not( pVOperand o1 );
  
  void b_and(long _register1,long _register2,bool is_data = false);
  void w_and(long _register1,long _register2,bool is_data = false);
  void d_and(long _register1,long _register2,bool is_data = false);
  void q_and(long _register1,long _register2,bool is_data = false);

  char v_and( pVOperand o1,pVOperand o2 );
  void b_or(long _register1,long _register2,bool is_data = false);
  void w_or(long _register1,long _register2,bool is_data = false);
  void d_or(long _register1,long _register2,bool is_data = false);
  void q_or(long _register1,long _register2,bool is_data = false);

  char v_or( pVOperand o1,pVOperand o2 );
  
  void b_xor(long _register1,long _register2,bool is_data = false);
  void w_xor(long _register1,long _register2,bool is_data = false);
  void d_xor(long _register1,long _register2,bool is_data = false);
  void q_xor(long _register1,long _register2,bool is_data = false);

  char v_xor( pVOperand o1,pVOperand o2 );
  
  void b_shl(long _register,char n,bool is_data = false);
  void w_shl(long _register,char n,bool is_data = false);
  void d_shl(long _register,char n,bool is_data = false);
  void q_shl(long _register,char n,bool is_data = false);
  
  char v_shl( pVOperand o1,pVOperand o2 );
  
  void b_shr(long _register,char n,bool is_data = false);
  void w_shr(long _register,char n,bool is_data = false);
  void d_shr(long _register,char n,bool is_data = false);
  void q_shr(long _register,char n,bool is_data = false);
  
  char v_shr( pVOperand o1,pVOperand o2 );
  
  void b_push_imm(char n);
  void w_push_imm(short n);
  void d_push_imm(int n);
  void a_push_imm(long n);
  void q_push_imm(long n);

  char v_push_imm( pVOperand o1 );
  
  void b_push_imm_sx(char n);
  void w_push_imm_sx(short n);
  void d_push_imm_sx(int n);

  void b_push_imm_zx(char n);
  void w_push_imm_zx(short n);
  void d_push_imm_zx(int n);

  void b_copy_stack();
  void w_copy_stack();
  void d_copy_stack();
  void q_copy_stack();
  
  void pushf();
  void pushad();
  void popad();
  void popf();
  void exit();
  void start();


  void save_vm_context();
  void recover_vm_context();
  void b_read_mem(  );
  void w_read_mem(  );
  void d_read_mem(  );
  void q_read_mem(  );
  void b_write_mem(  );
  void w_write_mem(  );
  void d_write_mem(  );
  void q_write_mem(  );  
  void b_add_b(long _register1,long _register2);
  void b_add(long _register1,long _register2,bool is_data = false);
  void w_add(long _register1,long _register2,bool is_data = false);
  void d_add_d(long _register1,long _register2);
  void d_add(long _register1,long _register2,bool is_data = false);
  void q_add(long _register1,long _register2,bool is_data = false);
  char v_add( pVOperand o1,pVOperand o2 );

  void b_sub(long _register1,long _register2);
  void w_sub(long _register1,long _register2);
  void d_sub(long _register1,long _register2);
  void q_sub(long _register1,long _register2);
  char v_sub(pVOperand o1,pVOperand o2 );
  

  void b_div(long _register1,long _register2);
  void w_div(long _register1,long _register2);
  void d_div(long _register1,long _register2);
  void q_div(long _register1,long _register2);

  void push(long _register,bool _disable = true);
  void pop(long _register);

  void b_cmp(long _register1,long _register2);
  void w_cmp(long _register1,long _register2);
  void d_cmp(long _register1,long _register2);
  void q_cmp(long _register1,long _register2);  
  
  void r_get_mem(
                                  long _register_index,
                                  long _register_base,
                                  long _scale,
                                  long _lval);

  void * get_code_buf(  );
  void push_vesp(  );
  void db( unsigned char b );
  void dw( unsigned short w );
  void dd( unsigned int d );
  void dq( unsigned long q );
  void set_pc(  );
  void set_key( long _key );
  void upset_register_array( RegisterStore & r );
  PCode *pcode;

  void mov(pVOperand o1,pVOperand o2);
  void test(pVOperand o1,pVOperand o2);
  void lea(pVOperand o1,pVOperand o2);
  void cmp(pVOperand o1,pVOperand o2);
  void sar(pVOperand o1,pVOperand o2);
  void cdq(pVOperand o1);
  void div(pVOperand o1);
  void sar(pVOperand o1);
  void imul(pVOperand o1,pVOperand o2,pVOperand o3);
  void jnz(long addr1,long addr2);
  void jz(long addr1,long addr2);
};

#endif /* _SENIORVMHANDLE_H_ */
