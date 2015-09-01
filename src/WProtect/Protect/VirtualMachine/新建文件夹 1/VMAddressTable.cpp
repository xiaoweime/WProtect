/*
 *
 *   Copyright (C) Sun Jun 23 09:34:14 2013 XiaoWei
 *
 *                       handsomexiaowei@gmail.com
 *
 *
 */
#include "VMAddressTable.hpp"
#include <algorithm>
#include <functional>
#include <algorithms>

VMAddressTable::VMAddressTable()
  :base(0),block_count(0)
{
}

VMAddressTable::~VMAddressTable()
{
}

long VMAddressTable::init(long pcode_base,long size)
{
  base = pcode_base;
  base_max = base + size;
  alignment = size;
  //address_vect.push(base);
  //address_vect.push(base_max);
}

pAssress_Table VMAddressTable::find_effective_space()
{
  int n = (base_max - base)/100; //获取块数
  if (block_count == n)
  {
    base_max = base_max + alignment;
  }
  long count=0;
  long *findaddr = new long[n - block_count];
  for (int i = 0; i < n; ++i)
  {
    bool  b = true;
      for (vector<long>::iterator iter = user_address.begin(); iter != user_address.end(); ++iter)
      {
        if (*iter == i)
        {
          b = false;
        }
      }
      if (b)
      {
        findaddr[count++] = base + (i*100);
      }
  }
  count = m_random()%count;
  long addr = findaddr[count];
  user_address.push(count);
  delete [] findaddr;
  return addr;
}

pAddress_Table VMAddressTable::newtable()
{
  
}

pAddress_Table VMAddressTable::addtable(PCode *p,long addr)
{
  Address_Table table;
  table.pcode = p;
  //  table.begin_addr =
  table.label.addr = addr;
  table.label.label_id = label_id++;
}

void VMAddressTable::update(Address_Table *p)
{
  p->size = p->pcode->get_code_size();
  if (p->sign)
  {
    p->end_addr = p->begin_addr + p->size;
  }
  else
  {
    p->end_addr = p->begin_addr - p->size;
  }
}
