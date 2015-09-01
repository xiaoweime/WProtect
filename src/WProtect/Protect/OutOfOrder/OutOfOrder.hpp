/*
 *
 *   Copyright (C) Thu Jul  4 19:51:53 2013 XiaoWei
 *
 *                       handsomexiaowei@gmail.com
 *
 *
 */


#ifndef _OUTOFORDER_H_
#define _OUTOFORDER_H_

#include <Analysis.hpp>
#include <AsmJit.h>
#include <Assembl.h>

class OutOfOrder
{
public:  
  OutOfOrder();
  virtual ~OutOfOrder();
typedef struct _CLabel
{
  long addr;
  AsmJit::Label label;
}CLabel;  
  pCodeBufferInfo BuildCode( pCodeBufferInfo code );
  Assembl a;
  Label get_label( long addr );
  bool check_label( long addr );
  std::vector <CLabel> label_vec;  
};

#endif /* _OUTOFORDER_H_ */
