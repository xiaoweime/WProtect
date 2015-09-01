/*
 *
 *   Copyrigth (C) Mon May 20 10:36:14 2013 XiaoWei
 *
 *                       handsomexiaowei@gmail.com
 *
 *
 */

#ifndef _VIRTUALMACHINE_H_
#define _VIRTUALMACHINE_H_

#include <iostream>
#include <list>

#include "VMHandle.h"
#include "PCode.hpp"
#include <AsmJit.h>

using namespace std;

typedef struct PCODE_BLOCK_INFO
{
  long entry; //v_init的地址
  long pcode_base; //pcode地址
  unsigned char *buf;
  unsigned long size;
  AsmJit::Assembler a;
}pcode_block_info,*ppcode_block_info;

typedef struct VIRTUAL_MACHINE_CODE_INFO
{
  unsigned char *buf;
  unsigned long size;
  unsigned long base; //虚拟机基质
}VirtualMachineCode,*pVirtualMachineCode;

class VirtualMachine
{
 public:
  VirtualMachine(  );
  
  VirtualMachine(long base);
  VirtualMachine(long base,bool sign );
  ~VirtualMachine(  );
  VMHandle handle;
  vm_handle handle_pcode;
  vm_handle & get_vm_handle_table()
  {
   return handle_pcode;
  }
  VMHandle & get_vm_handle()
  {
   return handle;
  }
  void build_vm_handle(long base );
  void full_handle_table(long base,long table_offset);
  list <handle_info> handle_info_list;
  ppcode_block_info add_new_function( long base,PCode *code ,long ret_address,long v_key,long decryption_key);
  ppcode_block_info create_function_head(long reloc_base,long base,PCode *code ,long ret_address,long v_key,long decryption_key);  
  long dispatch_base;
  list <ppcode_block_info> pcode_list;
  void init(AsmJit::Assembler &a);
  void add_pcode(AsmJit::Assembler &a,PCode *code,long base,long ret_address,long v_key,long decryption_key);
  VirtualMachineCode vm_info;
};


#endif /* _VIRTUALMACHINE_H_ */
