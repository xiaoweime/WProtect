/*
 *
 *   Copyrigth (C) Wed Jun 12 14:45:50 2013 XiaoWei
 *
 *                       handsomexiaowei@gmail.com
 *
 *
 */


#ifndef _OUTOFORDER_H_
#define _OUTOFORDER_H_

typedef struct _ADDRESS_TABLE_
{
  long oldaddress;
  long newaddress;
}Address_table,*pAddress_table;

class OutOfOrder
{
public:
  OutOfOrder();
  virtual ~OutOfOrder();
};

#endif /* _OUTOFORDER_H_ */
