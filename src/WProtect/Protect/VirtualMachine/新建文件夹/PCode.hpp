/*
 *
 *   Copyrigth (C) Mon May 20 01:02:51 2013 XiaoWei
 *
 *                       handsomexiaowei@gmail.com
 *
 *
 */

#ifndef _PCODE_H_
#define _PCODE_H_

#include <iostream>
#include <list>
#include <vector>
using namespace std;

#include <WProtectConfig.h>
#include "VMHandle.h"
//#include "VirtualMachine.h"

typedef struct V_HANDLE_CONTEXT_
{
  long type; //大小和各种信息 READ_BYTE ...
  unsigned char handle;
  //list <encryption> encode_key; //加密PCode KEY 加上这句程序就崩溃了
  std::vector <encryption> *encode_key;
  std::list <vcode_encryption> *encode_pcode;
  //unsigned char (*b_de)(unsigned char);
  //unsigned short (*w_de)(unsigned short);
  //unsigned int (*d_de)(unsigned int);
  //unsigned long (*q_de)(unsigned long);
}VMHandleInfo,*pVMHandleInfo;
  
typedef struct _VM_HANDLE_
{
    VMHandleInfo  b_read_stack; 
  VMHandleInfo  w_read_stack; 
  VMHandleInfo  d_read_stack;  

  
  VMHandleInfo  b_write_stack;
  VMHandleInfo  w_write_stack;
  VMHandleInfo  d_write_stack;


  VMHandleInfo  b_push_reg;
  VMHandleInfo  w_push_reg;
  VMHandleInfo  d_push_reg;


  VMHandleInfo  b_pop_reg;
  VMHandleInfo  w_pop_reg;
  VMHandleInfo  d_pop_reg;


  VMHandleInfo  b_push_imm;
  VMHandleInfo  w_push_imm;
  VMHandleInfo  d_push_imm;


  VMHandleInfo  b_shl;
  VMHandleInfo  w_shl;
  VMHandleInfo  d_shl;


  VMHandleInfo  b_shr;
  VMHandleInfo  w_shr;
  VMHandleInfo  d_shr;


  VMHandleInfo  shld;
  VMHandleInfo  shrd;

  VMHandleInfo  b_nand;
  VMHandleInfo  w_nand;
  VMHandleInfo  d_nand;

  
  VMHandleInfo  set_pc;
  VMHandleInfo  ret;
  VMHandleInfo  in;
  VMHandleInfo  rdtsc;
  VMHandleInfo  cpuid;
  VMHandleInfo  check_stack;
  VMHandleInfo  dispatch;
  VMHandleInfo  push_stack_top_base;
  VMHandleInfo  b_read_mem;
  VMHandleInfo  w_read_mem;
  VMHandleInfo  d_read_mem;

  VMHandleInfo  b_write_mem;
  VMHandleInfo  w_write_mem;
  VMHandleInfo  d_write_mem;


  VMHandleInfo pop_stack_top_base;
  VMHandleInfo b_push_imm_sx;
  VMHandleInfo w_push_imm_sx;

  VMHandleInfo b_push_imm_zx;
  VMHandleInfo w_push_imm_zx;

  VMHandleInfo b_add;
  VMHandleInfo w_add;
  VMHandleInfo d_add;

  VMHandleInfo b_rol;
  VMHandleInfo w_rol;
  VMHandleInfo d_rol;

  VMHandleInfo b_ror;
  VMHandleInfo w_ror;
  VMHandleInfo d_ror;

#ifdef PROTECT_X64
  VMHandleInfo d_push_imm_sx;  
  VMHandleInfo d_push_imm_zx;  
  VMHandleInfo  q_read_stack;
  VMHandleInfo  q_write_stack;
  VMHandleInfo  q_push_reg;
  VMHandleInfo  q_pop_reg;
  VMHandleInfo  q_push_imm;
  VMHandleInfo  q_shl;
  VMHandleInfo  q_shr;
  VMHandleInfo  q_nand;
  VMHandleInfo  q_read_mem;
  VMHandleInfo  q_write_mem;
  VMHandleInfo q_rol;
  VMHandleInfo q_ror;
  VMHandleInfo q_add;
#endif
}vm_handle,*pvm_handle;
  
typedef struct _VM_BUF_INFO_
{
  unsigned char * buf;
  unsigned long size;
  unsigned long offset;
  bool sign;  //true表示正 flase表示负
  vm_handle handle_table;
}vm_buf_info,*pvm_buf_info;


typedef struct _V_REG_
{
  long reg_id;
  long reg_offset;
  long status;
}vm_reg,*pvm_reg;

#define REG_NUMBER 30

typedef struct _VM_REG_CONTEXT_
{
  vm_reg vr[REG_NUMBER];
  pvm_reg nax;
  pvm_reg nbx;
  pvm_reg ncx;
  pvm_reg ndx;
  pvm_reg nsp;
  pvm_reg nbp;
  pvm_reg ndi;
  pvm_reg nsi;
  pvm_reg eflag;
  pvm_reg r8;
  pvm_reg r9;
  pvm_reg r10;
  pvm_reg r11;
  pvm_reg r12;
  pvm_reg r13;
  pvm_reg r14;
  pvm_reg r15;
}vm_reg_context,*pvm_reg_context;



#define T_RAX 1
#define T_RBX 2
#define T_RCX 4
#define T_RDX 8
#define T_RSP 16
#define T_RBP 32
#define T_RSI 64
#define T_RDI 128

#define T_EFLAG_ 256

#define T_TMP_R64_1 512
#define T_TMP_R64_2 1024
#define T_TMP_R64_3 2048
#define T_TMP_R64_4 4096

#define T_KEY64  8192
#define T_RET64  16384

#define T_TMP_R64_5 32768 //保留
#define T_TMP_R64_6 65536
#define T_TMP_R64_7 131072
#define T_TMP_R64_8 262144
#define T_XXX5 524288


#define T_INVALID 1048576

#define T_16X  2097152 //AX
#define T_8H 4194304 //AH
#define T_8L 8388608
#define T_E32X  16777216 //只有64位程序时才有
#define T_RN 33554432       //R8 - R15

#define  disable 67108864
#define  enable 134217728

#define T_KEY32 (T_KEY64 | T_E32X)
#define T_RET32 (T_RET64 | T_E32X)

#define T_TMP_R32_1 (T_TMP_R64_1 | T_E32X)
#define T_TMP_R32_2 (T_TMP_R64_2 | T_E32X)
#define T_TMP_R32_3 (T_TMP_R64_3 | T_E32X)
#define T_TMP_R32_4 (T_TMP_R64_4 | T_E32X)
#define T_TMP_R32_5 (T_TMP_R64_5 | T_E32X)
#define T_TMP_R32_6 (T_TMP_R64_6 | T_E32X)
#define T_TMP_R32_7 (T_TMP_R64_7 | T_E32X)
#define T_TMP_R32_8 (T_TMP_R64_8 | T_E32X)
#define T_INVALID_R32 (T_INVALID | T_E32X)

#define T_TMP_R16_1 (T_TMP_R32_1 | T_16X)
#define T_TMP_R16_2 (T_TMP_R32_2 | T_16X)
#define T_TMP_R16_3 (T_TMP_R32_3 | T_16X)
#define T_TMP_R16_4 (T_TMP_R32_4 | T_16X)
#define T_TMP_R16_5 (T_TMP_R32_5 | T_16X)
#define T_TMP_R16_6 (T_TMP_R32_6 | T_16X)
#define T_TMP_R16_7 (T_TMP_R32_7 | T_16X)
#define T_TMP_R16_8 (T_TMP_R32_8 | T_16X)
#define T_INVALID_R16 (T_INVALID_R32 | T_16X)

#define T_TMP_R8_1H (T_TMP_R16_1 | T_8H)
#define T_TMP_R8_2H (T_TMP_R16_2 | T_8H)
#define T_TMP_R8_3H (T_TMP_R16_3 | T_8H)
#define T_TMP_R8_4H (T_TMP_R16_4 | T_8H)
#define T_TMP_R8_5H (T_TMP_R16_5 | T_8H)
#define T_TMP_R8_6H (T_TMP_R16_6 | T_8H)
#define T_TMP_R8_7H (T_TMP_R16_7 | T_8H)
#define T_TMP_R8_8H (T_TMP_R16_8 | T_8H)
#define T_INVALID_R8 (T_INVALID_R16 | T_8H)

#define T_TMP_R8_1L (T_TMP_R16_1 | T_8L)
#define T_TMP_R8_2L (T_TMP_R16_2 | T_8L)
#define T_TMP_R8_3L (T_TMP_R16_3 | T_8L)
#define T_TMP_R8_4L (T_TMP_R16_4 | T_8L)
#define T_TMP_R8_5L (T_TMP_R16_5 | T_8L)
#define T_TMP_R8_6L (T_TMP_R16_6 | T_8L)
#define T_TMP_R8_7L (T_TMP_R16_7 | T_8L)
#define T_TMP_R8_8L (T_TMP_R16_8 | T_8L)

#define T_INVALID32 (T_INVALID | T_E32X)
#define T_INVALID16 (T_INVALID | T_16X)
#define T_INVALID8L  (T_INVALID | T_8L)
#define T_INVALID8H  (T_INVALID | T_8H)

#define T_R8 (T_RAX | T_RN)
#define T_R9 (T_RBX | T_RN)
#define T_R10 (T_RAX | T_RN)
#define T_R11 (T_RBX | T_RN)
#define T_R12 (T_RAX | T_RN)
#define T_R13 (T_RBX | T_RN)
#define T_R14 (T_RAX | T_RN)
#define T_R15 (T_RBX | T_RN)

#define T_EAX (T_RAX | T_E32X)
#define T_EBX (T_RBX | T_E32X)
#define T_ECX (T_RCX | T_E32X)
#define T_EDX (T_RDX | T_E32X)
#define T_ESP (T_RSP | T_E32X)
#define T_EBP (T_RBP | T_E32X)
#define T_ESI (T_RSI | T_E32X)
#define T_EDI (T_RDI | T_E32X)

#define T_AX (T_EAX | T_16X)
#define T_BX (T_EBX | T_16X)
#define T_CX (T_ECX | T_16X)
#define T_DX (T_EDX | T_16X)
#define T_SP (T_ESP | T_16X)
#define T_BP (T_EBP | T_16X)
#define T_SI (T_ESI | T_16X)
#define T_DI (T_EDI | T_16X)

#define T_AH (T_AX | T_8H)
#define T_AL (T_AX | T_8L)
#define T_CH (T_CX | T_8H)
#define T_CL (T_CX | T_8L)
#define T_DH (T_DX | T_8H)
#define T_DL (T_DX | T_8L)
#define T_BH (T_BX | T_8H)
#define T_BL (T_BX | T_8L)

#define T_EFLAG8H (T_EFLAG_ | T_8H)
#define T_EFLAG8L (T_EFLAG_ | T_8L)
#define T_EFLAG16 (T_EFLAG_ | T_16X)
#define T_EFLAG32 (T_EFLAG_ | T_E32X)

#ifdef PROTECT_X64
#define T_EFLAG T_EFLAG_
#define T_KEY T_KEY64
#define T_RET T_RET64
#define T_TMP_REGISTER1 T_TMP_R64_1
#define T_TMP_REGISTER2 T_TMP_R64_2
#define T_TMP_REGISTER3 T_TMP_R64_3
#define T_TMP_REGISTER4 T_TMP_R64_4
#define T_TMP_REGISTER5 T_TMP_R64_5
#define T_TMP_REGISTER6 T_TMP_R64_6
#define T_TMP_REGISTER7 T_TMP_R64_7
#define T_TMP_REGISTER8 T_TMP_R64_8
#define T_NAX T_RAX
#define T_NBX T_RBX
#define T_NCX T_RCX
#define T_NDX T_RDX
#define T_NSP T_RSP
#define T_NBP T_RBP
#define T_NSI T_RSI
#define T_NDI T_RDI
#else
#define T_EFLAG (T_EFLAG32)
#define T_KEY (T_KEY32)
#define T_RET (T_RET32)
#define T_TMP_REGISTER1 T_TMP_R32_1
#define T_TMP_REGISTER2 T_TMP_R32_2
#define T_TMP_REGISTER3 T_TMP_R32_3
#define T_TMP_REGISTER4 T_TMP_R32_4
#define T_TMP_REGISTER5 T_TMP_R32_5
#define T_TMP_REGISTER6 T_TMP_R32_6
#define T_TMP_REGISTER7 T_TMP_R32_7
#define T_TMP_REGISTER8 T_TMP_R32_8
#define T_NAX T_EAX
#define T_NBX T_EBX
#define T_NCX T_ECX
#define T_NDX T_EDX
#define T_NSP T_ESP
#define T_NBP T_EBP
#define T_NSI T_ESI
#define T_NDI T_EDI
#endif

typedef struct _REGISTER_STORE_
{
  long register_array[REG_NUMBER];
  size_t register_count;
}RegisterStore,*pRegisterStore;

class PCode
{
public:
  PCode();
  PCode(vm_handle table,bool sign);
  //PCode(VirtualMachine *pvm);
  virtual ~PCode();
public:
  RegisterStore register_store_in;   //进来的时候寄存器储存顺序
  RegisterStore register_store_out;  //出去的时候寄存器储存顺序
  vm_buf_info pcode_info;
  vm_reg_context v_reg_context;
  void check_pcode_buf();
  void db(unsigned char b);
  void dw(unsigned short w);
  void dd(unsigned int d);
  void dq(unsigned long long q);
  void init_handle_table(vm_handle table);
  void init_sign(bool b);
  char get_rand_reg();
  void v_push_register(long _register,bool _disable = true);
  void v_pop_register(long _register);
  pvm_reg find_invalid_register();
  void call_encode_pcode_fn(vcode_encryption::MyFn fn,void *data,long * ikey);
  size_t get_code_size();
#ifdef PROTECT_X64
  const unsigned long _key_;// = rand(); //PCode的KEY 而不是VM KEY 保存原始KEY
  unsigned long key;// = _key_;  //这个KEY是变化的
  const unsigned long get_original_key();
  const unsigned long get_current_key();
#else
  const unsigned int _key_;
  unsigned int key;
  const unsigned int get_original_key();
  const unsigned int get_current_key();
#endif
  char r_pc_size; //虚拟指令要读取pc多少个字节
  pVMHandleInfo current_instruction;
#ifdef DEBUG
  FILE *v_log;
#endif
private:
};

#endif /* _PCODE_H_ */
