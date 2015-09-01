/*
 *
 *   Copyright (C) Sat Jun  1 09:10:39 2013 XiaoWei
 *
 *                       handsomexiaowei@gmail.com
 *
 *
 */

#ifndef _BUILDVMCODE_H_
#define _BUILDVMCODE_H_

#include <Analysis.hpp>
#include "VirtualMachineManage.hpp"
#include "VMAddressTable.hpp"
#include "VMCodeBuffer.hpp"
class BuildVMCode
{
public:
  BuildVMCode();
  virtual ~BuildVMCode();
  long get_reg( const ud_type & t );
  void get_operand( SeniorVMHandle *svm,const ud_operand &op,bool _disable = false );
  void get_mem_data( SeniorVMHandle *svm,const ud_operand &op );
  void set_mem_data( SeniorVMHandle *svm,const ud_operand &op );  
  pCodeBufferInfo BuildPCode(VirtualMachineManage *vmmanage,pCodeBufferInfo pinfo,VMAddressTable * addrerss_table);
  long asm_to_vm(SeniorVMHandle *svm,ud_t *p_ud);
  long alloc_address(VirtualMachine *vm,VMAddressTable * address_table,Analysis * analysis,vector <VMCodeBufferManage*>*vcodebufs); //返回第一个pcode地址
  void dispose_key(Analysis *analysis);
  void update_key_data(Analysis *analysis);
  VOperand to_voperand(ud_operand & ud_op);
};

#endif /* _BUILDVM_H_ */
