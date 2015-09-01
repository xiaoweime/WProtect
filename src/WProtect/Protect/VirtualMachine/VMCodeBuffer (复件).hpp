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
#include "SeniorVMHandle.hpp"
#include "VirtualMachine.h"
#include "VirtualMachineManage.hpp"
#include <WProtectConfig.h>

using namespace std;

class VMCodeBufferManage
{
public:
  explicit VMCodeBufferManage(VirtualMachineManage *vmmanage)
  {
    if ( !vmmanage )
      throw;
    VirtualMachine *vm = vmmanage->rand_virtual_machine();
    code.init_handle_table(vm->handle_pcode);
    code.init_sign(vm->handle.fuc_select.addorsub);
    senior.link_pcode( &code );
  }
  explicit VMCodeBufferManage( VirtualMachine *vm )
  {
    if ( !vm )
      throw;
     code.init_handle_table(vm->handle_pcode);
     code.init_sign( vm->handle.fuc_select.addorsub );
     senior.link_pcode( &code ); 
  }
  VMCodeBufferManage(VirtualMachineManage *vmmanage,
#ifdef PROTECT_X64
                      unsigned long key
#else
                      unsigned int key
#endif
                      )
  {
    if ( !vmmanage )
      throw;
    VirtualMachine *vm = vmmanage->rand_virtual_machine();
    code.init_handle_table(vm->handle_pcode);
    code.init_sign(vm->handle.fuc_select.addorsub);
    senior.link_pcode( &code );
  }
  
  VMCodeBufferManage( VirtualMachine *vm ,
#ifdef PROTECT_X64
                      unsigned long key
#else
                      unsigned int key
#endif
                      )
  {
    if ( !vm )
      throw;
     code.init_handle_table(vm->handle_pcode);
     code.init_sign( vm->handle.fuc_select.addorsub );
     senior.link_pcode( &code );
     code.set_key(key);
  }  
  virtual ~VMCodeBufferManage() {
    
  }
public:
  SeniorVMHandle senior;
  SeniorVMHandle & get_generator(  )  {
    return senior;
  }
  PCode code;  
private:
};

#endif /* _VMCODEBUFFER_H_ */
