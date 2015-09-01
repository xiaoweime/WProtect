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

CLabel clabel( long addr,AsmJit::Label label );

typedef struct _NSP_DATA
{
  long diff;
}NspData;

class EquivalentReplacement
{
public:
  EquivalentReplacement();
  virtual ~EquivalentReplacement();
  pCodeBufferInfo BuildCode(pCodeBufferInfo code,CodeAddressTable* address_table  );
  AsmJit::GPReg  get_register( pVOperand o1 ) ;
  AsmJit::GPReg  get_register( const ud_type & o1 );
  long  get_v_register( const ud_type & o1 );
  AsmJit::GPReg  get_rand_register( AsmJit::GPReg *r_n,int count );
  long get_register_diff( long _register );
  AsmJit::GPReg get_mem(  ud_operand  o  ,AsmJit::GPReg *r,int & r_count);
  AsmJit::GPReg get_mem( pVOperand o,AsmJit::GPReg *r,int & r_count );
  AsmJit::GPReg get_operand( ud_operand o,AsmJit::GPReg *r,int & r_count );
  AsmJit::GPReg get_operand( pVOperand o,AsmJit::GPReg *r,int& r_count );
  void push( pVOperand o1 );
  void pushad(  );
  void pushf(  );
  void pop( pVOperand o1 );
  void pop( ud_operand o1 );
  void save_context(  );
  void recover_context(  );
  long create_space( long size );
  void push_value( pVOperand o );
  void pop_value( pVOperand o );
  //long register_store[ 30*4 ];
  //std::vector <NspData> register_store;
  std::vector<long>register_store;
  long nsp_diff;
  long nsp_data_diff; //真实的esp数据 比如进入vm后Push 就加上这个值
  //std::vector <NspData> data; //存放真实数据
  std::vector <CLabel> label_vec;
  
  std::vector <long>data;
  AsmJit::Assembler a;
  VOperand udop_to_vop( const ud_operand & o );
  AsmJit::Label  get_label( long addr );
  bool check_label( long addr ); //如果存在了就返回false
  void disable_register( pVOperand o1 );
};

#endif /* _EQUIVALENREPLACEMENT_H_ */
