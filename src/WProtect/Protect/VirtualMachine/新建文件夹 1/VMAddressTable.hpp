/*
 *
 *   Copyright (C) Wed Jun 12 14:52:54 2013 XiaoWei
 *
 *                       handsomexiaowei@gmail.com
 *
 *
 */


#ifndef _VMADDRESSTABLE_H_
#define _VMADDRESSTABLE_H_

#include "PCode.hpp"
#include <iostream>

#include <vector>

using namespace AsmJit;

class space
{
public:
  space(long _begin,long _end)
    : begin(_begin),end(_end),size(begin>end?begin-end:end-begin){}
  
  virtual ~space();
  long begin;
  long end;
  long size;
  bool operator < (const space & c1,const space & c2)
  {
    return c1.begin < c2.begin;
  }
  
};

typedef struct _VM_LABEL_
{
  long label_id;
  long addr;
}VLabel,*pVLabel;

typedef struct _Address_Table_
{
  long begin_addr;
  long end_addr;
  size_t size;
  bool sign;
  long old_addr;
  VLabel label;
  PCode *pcode;
  pRegisterStore reg_store;
}Address_Table,*pAddress_Table;

class VMAddressTable
{
public:
  VMAddressTable();
  virtual ~VMAddressTable();
  long init(long pcode_base,long size);
  void update(Address_Table *p);
  pAddress_Table addtable(PCode *p,long addr = 0);
  vector <Address_Table> table_list;
  vector <long> used_address;
private:
  long base;
  long label_id;
  long base_max;
  long block_count;
  long alignment;
};

#endif /* _VMADDRESSTABLE_H_ */
