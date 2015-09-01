/*
 *
 *   Copyright (C) Mon Jul  1 16:56:17 2013 XiaoWei
 *
 *                       handsomexiaowei@gmail.com
 *
 *
 */


#ifndef _EQUIVALENTREPLACEMENT_H_
#define _EQUIVALENTREPLACEMENT_H_

#include <Analysis.hpp>
#include <CodeAddressTable.hpp>
#include <VOperand.hpp>
#include <AsmJit.h>

typedef struct _CLabel
{
  long addr;
  AsmJit::Label label;
}CLabel;

typedef struct _EREG_
{
  long register_id;
  long register_diff;
  long key;
}EReg;


using namespace AsmJit;

class EquivalentReplacement
{
public:
  EquivalentReplacement();
  virtual ~EquivalentReplacement();
  pCodeBufferInfo BuildCode(pCodeBufferInfo code,CodeAddressTable* address_table  );
  AsmJit::Assembler a;
  //std::vector <long> v_register;
  long nsp_diff;
  long nsp_data_diff;
  long vm_context_space; //
  std::vector <EReg> register_vec;
  std::vector <CLabel> label_vec;
  
  GPReg get_register( pVOperand o1 );
  GPReg get_rand_register( GPReg * r_n , int & count );
  GPReg get_imm( pVOperand o,GPReg *r_n,int &count );
  GPReg get_reg( pVOperand o,GPReg *r_n,int &count , char is_mem = 0 );
  GPReg get_mem( pVOperand o,GPReg *r_n ,int & count );
  GPReg get_operand ( pVOperand o,GPReg *r_n,int &count );
  void v_push( long _register );
  void v_pop( long _register );
  void push( pVOperand o ,GPReg *r_n,int &count );
  void pop( pVOperand o,GPReg *r_n,int &count );
  void create_vm_space( long _size );
  void save_vm_context(  );
  VOperand udop_to_vop( const ud_operand & o );
  long get_v_register( const ud_type & o1 );
  Label get_label( long addr );
  bool check_label( long addr );
  bool disable_register( long _register );
  long get_invalid_space( size_t _size );
};

#endif /* _EQUIVALENREPLACEMENT_H_ */
