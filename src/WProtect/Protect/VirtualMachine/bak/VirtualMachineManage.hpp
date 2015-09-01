/*
 *
 *   Copyrigth (C) Thu May 23 00:32:50 2013 XiaoWei
 *
 *                       handsomexiaowei@gmail.com
 *
 *
 */

#ifndef _VIRTUALMACHINEMANAGE_H_
#define _VIRTUALMACHINEMANAGE_H_

#include <iostream>
#include <list>
#include "VirtualMachine.h"
#include "PCode.hpp"

using namespace std;

class VirtualMachineManage
{
public:
  VirtualMachineManage();
  virtual ~VirtualMachineManage();
public:
  list <VirtualMachine *> virtual_machine_list;
  VirtualMachine * add_virtual_machine(long base,bool sign = false);
  int virtual_machine_count;
  VirtualMachine * rand_virtual_machine();
  void moc(VirtualMachine *pvm,PCode *code);
};

#endif /* _VIRTUALMACHINEMANAGE_H_ */
