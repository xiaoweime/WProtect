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


enum V_OPERAND_TYPE
{
  VOPERAND_NONE = 0x00;
  VOPERAND_REG  = 0x01;
  VOPERAND_IMM  = 0x02;
  VOPERAND_MEM  = 0x04;
};


typedef struct _V_Operand
{
  typedef struct _BASE_DATA
  {
    char op;
    char size;
    long id;
  }
  typedef struct _MEM_DATA
  {
    long id;
    char op;
    long base;
    long index;
    long scale;
    long lval;
    char size;  //指的是内存大小 比如dword_ptr为4
  }MemData;
  typedef struct _REG_DATA
  {
    long id;
    char op;
    long base;
    char size;
  }RegData;
  typedef struct _IMM_DATA
  {
    long id;
    char op;
    long value;
    char size;
  }ImmData;
  
  union
  {
    BaseData _base;
    MemData _mem;
    RegData _reg;
    ImmData _imm;
  };

  inline size_t get_size(  ) const {
    return _base.size;
  }
  inline long get_id(  ) const {
    return _base.id;
  }
}VOperand,*pVOperand;


typedef struct _VImm : public VOperand 
{
  _VImm( long _value , char _size) {
    _imm.op = VOPERAND_IMM;
    _imm.value = _value;
    _imm.size = _size;
  }
  _VImm( long _value ) {
    _imm.op = VOPERAND_IMM;    
    _imm.value = _value;
#ifdef PROTECT_X64
    _imm.size = 8;
#else
    _imm.size = 4;
#endif
  }
  ~_VImm(  ) {
    
  }
}VImm;

typedef struct _VReg : public VOperand
{
  _VReg( long _register,char _size )
  {
    _reg.op = VOPERAND_REG;
    _reg.base = _register;
    _reg.size = _size;
  }
  _VReg( long _register )
  {
    _reg.op = VOPERAND_REG;
    _reg.base = _register;
  }
  ~_VReg(  )
  {
    
  }
}VReg;

typedef struct _VMem : public VOperand
{
  _VMem( long base,long index,long scale,long lval,char _size){
    _mem.op = VOPERAND_MEM;
    _mem.base = base;
    _mem.index = index;
    _mem.scale = scale;
    _mem.lval = lval;
    _mem.size = _size;
  }
  ~_VMem(  ){
    
  }
};

  
VImm vimm( long value );

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
  void b_not_and(long _register1 = 0,long _register2 = 0,bool is_data = false);
  void w_not_and(long _register1 = 0,long _register2 = 0,bool is_data = false);
  void d_not_and(long _register1 = 0,long _register2 = 0,bool is_data = false);
  void q_not_and(long _register1 = 0,long _register2 = 0,bool is_data = false);
  
  void b_not(long _register,bool is_data = false);
  void w_not(long _register,bool is_data = false);
  void d_not(long _register,bool is_data = false);
  void q_not(long _register,bool is_data = false);
  void b_and(long _register1,long _register2,bool is_data = false);
  void w_and(long _register1,long _register2,bool is_data = false);
  void d_and(long _register1,long _register2,bool is_data = false);
  void q_and(long _register1,long _register2,bool is_data = false);
  void b_or(long _register1,long _register2,bool is_data = false);
  void w_or(long _register1,long _register2,bool is_data = false);
  void d_or(long _register1,long _register2,bool is_data = false);
  void q_or(long _register1,long _register2,bool is_data = false);
  void b_xor(long _register1,long _register2,bool is_data = false);
  void w_xor(long _register1,long _register2,bool is_data = false);
  void d_xor(long _register1,long _register2,bool is_data = false);
  void q_xor(long _register1,long _register2,bool is_data = false);

  void b_shl(long _register,char n,bool is_data = false);
  void w_shl(long _register,char n,bool is_data = false);
  void d_shl(long _register,char n,bool is_data = false);
  void q_shl(long _register,char n,bool is_data = false);
  void b_shr(long _register,char n,bool is_data = false);
  void w_shr(long _register,char n,bool is_data = false);
  void d_shr(long _register,char n,bool is_data = false);
  void q_shr(long _register,char n,bool is_data = false);

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

  void b_sub(long _register1,long _register2);
  void w_sub(long _register1,long _register2);
  void d_sub(long _register1,long _register2);
  void q_sub(long _register1,long _register2);
  
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
};

#endif /* _SENIORVMHANDLE_H_ */
