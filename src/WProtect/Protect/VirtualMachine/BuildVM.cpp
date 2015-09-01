/*
 *
 *   Copyrigth (C) Sat Jun  1 10:51:23 2013 XiaoWei
 *
 *                       handsomexiaowei@gmail.com
 *
 *
 */


#include "BuildVM.hpp"

BuildVM::BuildVM()
{
}

BuildVM::~BuildVM()
{
}

void BuildVM::asm_to_vm(SeniorVMHandle *svm,ud_t *p_ud)
{
  switch (p_ud->mnmonic)
  {
  case UD_Imov:
    break;
  case UD_Ipush:
    break;
  }
  
}

pCodeBufferInfo BuildVM::BuildPCode(VirtualMachineManage *vmmanage,pCodeBufferInfo pinfo)
{
  Analysis analysis;
  analysis.disasm(pinfo);
  VirtualMachine *vm = vmmanage->rand_virtual_machine();
  
  PCode *pcode_array = new PCode[analysis.block_count];
  SeniorVMHandle *seniorvm_array = new SeniorVMHandle[analysis.block_count];

  for (int i = 0; i < analysis.block_count; ++i)
  {
    vm.moc(vm,&pcode_array[i]);
    seniorvm_array[i].link_pcode(&pcode_array[i]);
  }
  
  for (int i = analysis.block_count; i > 0; --i)
  {
    pAssemblerTree nowtree = analysis.get_tree(analysis.block_count);
    for (std::vector<ud_t>::iterator iter = nowtree->asmpiece.begin();
         iter != nowtree->asmpiece.end(); ++iter)
    {
      ud_t ud = *iter;
      asm_to_vm(&seniorvm_array[i],&ud);
    }
  }
  delete [] seniorvm_array;
  delete [] pcode_array;
}
