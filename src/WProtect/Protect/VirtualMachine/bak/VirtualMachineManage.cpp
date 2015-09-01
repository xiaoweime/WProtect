/*
 *
 *   Copyrigth (C) Thu May 23 00:35:35 2013 XiaoWei
 *
 *                       handsomexiaowei@gmail.com
 *
 *
 */

#include "VirtualMachineManage.hpp"

VirtualMachineManage::VirtualMachineManage()
{
  virtual_machine_count = 0;
}

VirtualMachineManage::~VirtualMachineManage()
{
  list <VirtualMachine*>::iterator iter;
  for (iter = virtual_machine_list.begin(); iter != virtual_machine_list.end(); ++iter)
  {
    delete *iter;
  }
}

VirtualMachine *VirtualMachineManage::add_virtual_machine(long base,bool sign)
{
  VirtualMachine *pVm = new VirtualMachine(base,sign);
  virtual_machine_list.push_back(pVm);
  virtual_machine_count++;
  return pVm;
}

VirtualMachine *VirtualMachineManage::rand_virtual_machine()
{
  list <VirtualMachine*>::iterator iter;
  int r = rand()%virtual_machine_count;
  int i;
  for (i = 0, iter = virtual_machine_list.begin(); iter != virtual_machine_list.end();i++,++iter)
  {
    if (r == i)
    {
      return (*iter);
    }
  }
  return NULL;
}

void VirtualMachineManage::moc(VirtualMachine *pvm,PCode *code) //连接PCode到虚拟机
{
  code->init_handle_table(pvm->handle_pcode);
  code->init_sign(pvm->handle.fuc_select.addorsub);
}
