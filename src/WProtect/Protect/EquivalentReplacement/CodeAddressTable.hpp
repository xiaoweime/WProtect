/*
 *
 *   Copyright (C) Mon Jul  1 16:59:49 2013 XiaoWei
 *
 *                       handsomexiaowei@gmail.com
 *
 *
 */

#ifndef _CODEADDRESSTABLE_H_
#define _CODEADDRESSTABLE_H_

#include <AddressTable.hpp>

typedef struct _code_table_
{
  
}CodeTable;

class CodeAddressTable : public AddressTable <CodeTable>
{
public:
  CodeAddressTable(long _base,size_t _size,bool _sign)
    :AddressTable( _base,_size,_sign ){
    
  }
  virtual ~CodeAddressTable(){
    
  }
};

#endif /* _CODEADDRESSTABLE_H_ */
