/*
 *
 *   Copyright (C) Wed Jun 26 18:49:56 2013 XiaoWei
 *
 *                       handsomexiaowei@gmail.com
 *
 *
 */

#ifndef _VMCODEBUFFER_H_
#define _VMCODEBUFFER_H_

#include <iostream>
#include "PCode.hpp"
//#include "SeniorVMHandle.hpp"
#include "CombosVMCode.hpp"
#include "VirtualMachine.h"
#include "VirtualMachineManage.hpp"
#include <WProtectConfig.h>

using namespace std;

class VMCodeBufferManage
{
public:
  explicit VMCodeBufferManage(VirtualMachineManage *vmmanage)
    :var_combos(&var_pcode)
  {
    if ( !vmmanage )
      throw;
    VirtualMachine *vm = vmmanage->rand_virtual_machine();
     var_pcode.init_handle_table(vm->get_vm_handle_table());
     var_pcode.init_sign( vm->get_vm_handle().fuc_select.addorsub );
     //var_combos.link_pcode( &var_pcode );    
  }
  explicit VMCodeBufferManage( VirtualMachine *vm )
    :var_combos(&var_pcode)
  {
    if ( !vm )
      throw;
     var_pcode.init_handle_table(vm->get_vm_handle_table());
     var_pcode.init_sign( vm->get_vm_handle().fuc_select.addorsub );
     //var_combos.link_pcode( &var_pcode ); 
  }
  VMCodeBufferManage(VirtualMachineManage *vmmanage,
#ifdef PROTECT_X64
                      unsigned long key
#else
                      unsigned int key
#endif
                      )
    :var_combos(&var_pcode)
  {
    if ( !vmmanage )
      throw;
    VirtualMachine *vm = vmmanage->rand_virtual_machine();
     var_pcode.init_handle_table(vm->get_vm_handle_table());
     var_pcode.init_sign( vm->get_vm_handle().fuc_select.addorsub );
     //var_combos.link_pcode( &var_pcode ); 
  }
  
  VMCodeBufferManage( VirtualMachine *vm ,
#ifdef PROTECT_X64
                      unsigned long key
#else
                      unsigned int key
#endif
                      )
    :var_combos(&var_pcode)
  {
    if ( !vm )
      throw;
     var_pcode.init_handle_table(vm->get_vm_handle_table());
     var_pcode.init_sign( vm->get_vm_handle().fuc_select.addorsub );
     //var_combos.link_pcode( &var_pcode );
     var_pcode.set_key(key);
  }  
  virtual ~VMCodeBufferManage() {
    
  }
public:
  VCombosVMCode var_combos;
  VCombosVMCode & get_generator(  )  {
    return var_combos;
  }
  PCode & get_pcode()
  {
    return var_pcode;
  }
  PCode var_pcode;  
  int var_label;
  void set_vmcode_label(int _label)
  {
     var_label = _label;
  }

private:
};

#endif /* _VMCODEBUFFER_H_ */
