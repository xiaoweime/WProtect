/*
 *
 *   Copyrigth (C) Sat Jun  1 09:10:39 2013 XiaoWei
 *
 *                       handsomexiaowei@gmail.com
 *
 *
 */

#ifndef _BUILDVM_H_
#define _BUILDVM_H_

#include <Analysis.hpp>
#include "VirtualMachineManage.hpp"
#include "CombosVMCode.hpp"

class BuildVM
{
public:
  BuildVM();
  virtual ~BuildVM();
  pCodeBufferInfo BuildPCode(VirtualMachineManage *vmmanage,pCodeBufferInfo pinfo);
  void asm_to_vm();
};

#endif /* _BUILDVM_H_ */
