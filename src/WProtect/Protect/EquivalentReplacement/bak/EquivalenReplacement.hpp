/*
 *
 *   Copyright (C) Mon Jul  1 16:56:17 2013 XiaoWei
 *
 *                       handsomexiaowei@gmail.com
 *
 *
 */


#ifndef _EQUIVALENREPLACEMENT_H_
#define _EQUIVALENREPLACEMENT_H_

#include <Analysis.hpp>
#include <CodeAddressTable.hpp>
#include <PCode.hpp>
#include <SeniorVMHandle.cpp>
#include <queue>
#include <AsmJit.h>

typedef struct _CLabel
{
  long addr;
  AsmJit::Label label;
}CLabel;

CLabel clabel( long addr,AsmJit::Label label );

class EquivalenReplacement
{
public:
  EquivalenReplacement();
  virtual ~EquivalenReplacement();
  pCodeBufferInfo BuildCode(pCodeBufferInfo code,CodeAddressTable* address_table  );
  AsmJit::GPReg & get_register( pVOperand o1 );
  AsmJit::GPReg & get_register( const AsmJit::ud_type & o1 );
  long & get_register( const ud_type & o1 );
  AsmJit::GPReg & get_rand_register(  );
  long get_register_diff( long _register );
  void get_mem( const ud_operand & o  );
  void push( pVOperand o1 );
  void pushad(  );
  void pushfd(  );
  
  long register_store[ 30*4 ];
  long nsp_diff;
  AsmJit::Assembler a;
};

#endif /* _EQUIVALENREPLACEMENT_H_ */
