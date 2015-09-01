/*
 *
 *   Copyrigth (C) Mon May 20 00:07:29 2013 XiaoWei
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

class SeniorVMHandle
{
 public:
  SeniorVMHandle();
  SeniorVMHandle(PCode *p);
  ~SeniorVMHandle(  );

  void link_pcode(PCode *p);
  void b_not_and(long _register1 = 0,long _register2 = 0);
  void w_not_and(long _register1 = 0,long _register2 = 0);
  void d_not_and(long _register1 = 0,long _register2 = 0);
  void q_not_and(long _register1 = 0,long _register2 = 0);
  
  void b_not(long _register);
  void w_not(long _register);
  void d_not(long _register);
  void q_not(long _register);
  void b_and(long _register1,long _register2);
  void w_and(long _register1,long _register2);
  void d_and(long _register1,long _register2);
  void q_and(long _register1,long _register2);
  void b_or(long _register1,long _register2);
  void w_or(long _register1,long _register2);
  void d_or(long _register1,long _register2);
  void q_or(long _register1,long _register2);
  void b_xor(long _register1,long _register2);
  void w_xor(long _register1,long _register2);
  void d_xor(long _register1,long _register2);
  void q_xor(long _register1,long _register2);

  void b_shl(long _register,char n);
  void w_shl(long _register,char n);
  void d_shl(long _register,char n);
  void q_shl(long _register,char n);
  void b_shr(long _register,char n);
  void w_shr(long _register,char n);
  void d_shr(long _register,char n);
  void q_shr(long _register,char n);

  void b_push_imm(char n);
  void w_push_imm(short n);
  void d_push_imm(int n);
  void q_push_imm(long n);

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

  void b_add_b(long _register1,long _register2);
  void b_add(long _register1,long _register2);
  void w_add(long _register1,long _register2);
  void d_add_d(long _register1,long _register2);
  void d_add(long _register1,long _register2);
  void q_add(long _register1,long _register2);

  void b_sub(long _register1,long _register2);
  void w_sub(long _register1,long _register2);
  void d_sub(long _register1,long _register2);
  void q_sub(long _register1,long _register2);
  
  void push(long _register,bool _disable = true);
  void pop(long _register);

  void r_get_mem(
                                  long _register_index,
                                  long _register_base,
                                  long _scale,
                                  long _lval);
  
  PCode *pcode;
};

#endif /* _SENIORVMHANDLE_H_ */
