/*
 *
 *   Copyrigth (C) Wed Jun 12 14:52:54 2013 XiaoWei
 *
 *                       handsomexiaowei@gmail.com
 *
 *
 */


#ifndef _VMRELOCATION_H_
#define _VMRELOCATION_H_

#include <iostream>
#include <list>
using namespace std;

typedef struct _VM_LABEL_ 
{
  long address;
  list <long*> reloc_addr_list;
}*VLabel;

class VmReloc
{
public:
  VmReloc();
  virtual ~VmReloc();
  VLabel new_label();
  void bind(VLabel label);
  void reloc(long base);
};

#endif /* _VMRELOCATION_H_ */
