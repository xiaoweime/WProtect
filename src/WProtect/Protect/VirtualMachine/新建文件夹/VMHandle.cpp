/*
 *
 *   Copyright (C) Mon May  6 05:21:23 2013 XiaoWei
 *
 *                       handsomexiaowei@gmail.com
 *
 */

#include <time.h>
#include "VMHandle.h"
#include <string.h>
#include <WProtectConfig.h>
#include <algorithms>
//#include "PCode.hpp"

using namespace AsmJit;

FileLogger logger(stderr);

VMHandle::VMHandle()
{
  	l_b_read_stack = a.newLabel(); //byte
	l_w_read_stack = a.newLabel(); //word
	l_d_read_stack = a.newLabel(); //dword
    l_q_read_stack = a.newLabel();

    l_initialization = a.newLabel();

    l_b_write_stack = a.newLabel();
    l_w_write_stack = a.newLabel();
    l_d_write_stack = a.newLabel();
    l_q_write_stack = a.newLabel();

    l_b_push_reg = a.newLabel();
    l_w_push_reg = a.newLabel();
    l_d_push_reg = a.newLabel();
    l_q_push_reg = a.newLabel();

    l_b_pop_reg = a.newLabel();
    l_w_pop_reg = a.newLabel();
    l_d_pop_reg = a.newLabel();
    l_q_pop_reg = a.newLabel();

    l_b_push_imm = a.newLabel();
    l_w_push_imm = a.newLabel();
    l_d_push_imm = a.newLabel();
    l_q_push_imm = a.newLabel();

    l_b_shl = a.newLabel();
    l_w_shl = a.newLabel();
    l_d_shl = a.newLabel();
    l_q_shl = a.newLabel();

    l_b_shr = a.newLabel();
    l_w_shr = a.newLabel();
    l_d_shr = a.newLabel();
    l_q_shr = a.newLabel();

    l_shld = a.newLabel();
    l_shrd = a.newLabel();

    l_b_nand = a.newLabel();
    l_w_nand = a.newLabel();
    l_d_nand = a.newLabel();
    l_q_nand = a.newLabel();

    l_set_pc = a.newLabel();
    l_ret = a.newLabel();

    l_in = a.newLabel();
    l_rdtsc = a.newLabel();
    l_cpuid = a.newLabel();
    l_check_stack = a.newLabel();
    l_dispatch = a.newLabel();
    l_push_stack_top_base = a.newLabel();

    l_b_read_mem = a.newLabel();
    l_d_read_mem = a.newLabel();
    l_w_read_mem = a.newLabel();
    l_q_read_mem = a.newLabel();
    l_b_write_mem = a.newLabel();
    l_w_write_mem = a.newLabel();
    l_d_write_mem = a.newLabel();
    l_q_write_mem = a.newLabel();

    l_b_push_imm_sx = a.newLabel();
    l_w_push_imm_sx = a.newLabel();
    l_d_push_imm_sx = a.newLabel();

    l_b_push_imm_zx = a.newLabel();
    l_w_push_imm_zx = a.newLabel();
    l_d_push_imm_zx = a.newLabel();
    
    l_b_add = a.newLabel();
    l_w_add = a.newLabel();
    l_d_add = a.newLabel();
    l_q_add = a.newLabel();
    l_pop_stack_top_base = a.newLabel();

    l_b_rol = a.newLabel();
    l_w_rol = a.newLabel();
    l_d_rol = a.newLabel();
    l_q_rol = a.newLabel();
    l_b_ror = a.newLabel();
    l_w_ror = a.newLabel();
    l_d_ror = a.newLabel();
    l_q_ror = a.newLabel();
    
    srand(time(NULL));
    key = rand(); //随机key
    a.setLogger(&logger);

}

VMHandle::~VMHandle()
{
}


#define FULL_BEGIN 1
#define FULL_END  2
#define FULL_BYTE_DECODE  3
#define FULL_WORD_DECODE 4
#define FULL_DWORD_DECODE 5
#define FULL_QWORD_DECODE 6




void c_add(encryption &_en,decryption &_de,const AsmJit::GPReg &_op_r)
{
  using namespace AsmJit;
  _de.defuc = new AsmJit::Assembler;
  _en.enfuc = new AsmJit::Compiler;
#ifdef DEBUG
  //  _en.enfuc->setLogger(&logger);
#endif  
  bool bD = _op_r.isGPD();
  bool bQ = _op_r.isGPQ();
  bool bW = _op_r.isGPW();
  bool bB = _op_r.isGPB();
   if (bB)
   {
      char r = m_random()%0x100;  
      _de.defuc->add(_op_r,r);
      _en.enfuc->newFunction(CALL_CONV_DEFAULT, FunctionBuilder1<unsigned char,unsigned char*>());
      GPVar result(_en.enfuc->newGP());
      _en.enfuc->add(byte_ptr(_en.enfuc->argGP(0)),r);
      _en.enfuc->movzx(result,byte_ptr(_en.enfuc->argGP(0)));
      _en.enfuc->ret(result);
    } else if (bW)
    {
      short r = m_random()%0x10000;  
      _de.defuc->add(_op_r,r);
      _en.enfuc->newFunction(CALL_CONV_DEFAULT, FunctionBuilder1<unsigned short,unsigned short*>());
      GPVar result(_en.enfuc->newGP());
      _en.enfuc->add(word_ptr(_en.enfuc->argGP(0)),r);
      _en.enfuc->movzx(result,word_ptr(_en.enfuc->argGP(0)));
      _en.enfuc->ret(result);
    } else if (bD)
    {
      int r = m_random()%0xFFFFFFFF;  
      _de.defuc->add(_op_r,imm(r));
      _en.enfuc->newFunction(CALL_CONV_DEFAULT, FunctionBuilder1<unsigned int,unsigned int*>());
        GPVar result(_en.enfuc->newGP());
      _en.enfuc->add(dword_ptr(_en.enfuc->argGP(0)),imm(r));
#ifdef PROTECT_X64
      _en.enfuc->mov(result,qword_ptr(_en.enfuc->argGP(0)));
      _en.enfuc->and_(result,0x00000000ffffffff);
#else
      _en.enfuc->mov(result,dword_ptr(_en.enfuc->argGP(0)));
#endif
      _en.enfuc->ret(result);
    } else if(bQ)
    {
       long r = m_random();  
      _de.defuc->add(_op_r,r);
#ifdef PROTECT_X64
      _en.enfuc->newFunction(CALL_CONV_DEFAULT, FunctionBuilder1<unsigned long,unsigned long*>());
#endif
      GPVar result(_en.enfuc->newGP());
      _en.enfuc->add(qword_ptr(_en.enfuc->argGP(0)),r);
      _en.enfuc->mov(result,qword_ptr(_en.enfuc->argGP(0)));
      _en.enfuc->ret(result);
    }
     _en.enfuc->endFunction();
  // _en->enfuc = function_cast<b_MyFn>(_en->c->make());
}

void c_sub(encryption &_en,decryption &_de,const AsmJit::GPReg &_op_r)
{
  using namespace AsmJit;
  _de.defuc = new AsmJit::Assembler;
  _en.enfuc = new AsmJit::Compiler;
#ifdef DEBUG
   _en.enfuc->setLogger(&logger);
#endif  
  bool bD = _op_r.isGPD();
  bool bQ = _op_r.isGPQ();
  bool bW = _op_r.isGPW();
  bool bB = _op_r.isGPB();

   if (bB)
   {
      char r = m_random()%0x100;  
      _de.defuc->sub(_op_r,r);
      _en.enfuc->newFunction(CALL_CONV_DEFAULT, FunctionBuilder1<unsigned char,unsigned char*>());
        GPVar result(_en.enfuc->newGP());
      _en.enfuc->sub(byte_ptr(_en.enfuc->argGP(0)),r);
      _en.enfuc->movzx(result,byte_ptr(_en.enfuc->argGP(0)));
      _en.enfuc->ret(result);
    } else if (bW)
    {
      short r = m_random()%0x10000;  
      _de.defuc->sub(_op_r,r);
      _en.enfuc->newFunction(CALL_CONV_DEFAULT, FunctionBuilder1<unsigned short,unsigned short*>());
      GPVar result(_en.enfuc->newGP());      
      _en.enfuc->sub(word_ptr(_en.enfuc->argGP(0)),r);
      _en.enfuc->movzx(result,word_ptr(_en.enfuc->argGP(0)));
      _en.enfuc->ret(result);      
    } else if (bD)
    {
      int r = m_random()%0xFFFFFFFF;  
      _de.defuc->sub(_op_r,r);
      _en.enfuc->newFunction(CALL_CONV_DEFAULT, FunctionBuilder1<unsigned int,unsigned int*>());
      GPVar result(_en.enfuc->newGP());            
      _en.enfuc->sub(dword_ptr(_en.enfuc->argGP(0)),r);
#ifdef PROTECT_X64
      _en.enfuc->mov(result,qword_ptr(_en.enfuc->argGP(0)));
      _en.enfuc->and_(result,0x00000000ffffffff);
#else
      _en.enfuc->mov(result,dword_ptr(_en.enfuc->argGP(0)));
#endif
      _en.enfuc->ret(result);      
    } else if(bQ)
    {
       long r = m_random();  
      _de.defuc->sub(_op_r,r);
#ifdef PROTECT_X64
      _en.enfuc->newFunction(CALL_CONV_DEFAULT, FunctionBuilder1<unsigned long,unsigned long*>());
#endif
      GPVar result(_en.enfuc->newGP());            
      _en.enfuc->sub(qword_ptr(_en.enfuc->argGP(0)),r);
      _en.enfuc->mov(result,qword_ptr(_en.enfuc->argGP(0)));
      _en.enfuc->ret(result);      
    }

     _en.enfuc->endFunction();
}

void c_rol(encryption &_en,decryption &_de,const AsmJit::GPReg & _op_r )
{
  using namespace AsmJit;
#ifdef PROTECT_X64
  char r = m_random()%0x64;
#else
  char r = m_random()%0x32;
#endif
  _de.defuc = new AsmJit::Assembler;
  _de.defuc->rol(_op_r,r);
  _en.enfuc = new AsmJit::Compiler;
#ifdef DEBUG
  //  _en.enfuc->setLogger(&logger);
#endif
  bool bD = _op_r.isGPD();
  bool bQ = _op_r.isGPQ();
  bool bW = _op_r.isGPW();
  bool bB = _op_r.isGPB();

  if (bB)
  {
    _en.enfuc->newFunction(CALL_CONV_DEFAULT, FunctionBuilder1<unsigned char,unsigned char*>());
    GPVar result(_en.enfuc->newGP());
    _en.enfuc->rol(byte_ptr(_en.enfuc->argGP(0)),r);
    _en.enfuc->movzx(result,byte_ptr(_en.enfuc->argGP(0)));
      _en.enfuc->ret(result);    
  }
  else if (bW)
  {
    _en.enfuc->newFunction(CALL_CONV_DEFAULT, FunctionBuilder1<unsigned short,unsigned short*>());
    GPVar result(_en.enfuc->newGP());    
     _en.enfuc->rol(word_ptr(_en.enfuc->argGP(0)),r);
    _en.enfuc->movzx(result,word_ptr(_en.enfuc->argGP(0)));
      _en.enfuc->ret(result);    
  }
  else if (bD)
  {
    _en.enfuc->newFunction(CALL_CONV_DEFAULT, FunctionBuilder1<unsigned int,unsigned int*>());
    GPVar result(_en.enfuc->newGP());    
    _en.enfuc->rol(dword_ptr(_en.enfuc->argGP(0)),r);
#ifdef PROTECT_X64
      _en.enfuc->mov(result,qword_ptr(_en.enfuc->argGP(0)));
      _en.enfuc->and_(result,0x00000000ffffffff);    
#else
    _en.enfuc->mov(result,dword_ptr(_en.enfuc->argGP(0)));
#endif
      _en.enfuc->ret(result);    
  }
#ifdef PROTECT_X64
  else
  {
    _en.enfuc->newFunction(CALL_CONV_DEFAULT, FunctionBuilder1<unsigned long,unsigned long*>());
    GPVar result(_en.enfuc->newGP());    
    _en.enfuc->rol(qword_ptr(_en.enfuc->argGP(0)),r);
    _en.enfuc->mov(result,qword_ptr(_en.enfuc->argGP(0)));
      _en.enfuc->ret(result);    
  }
#endif

  _en.enfuc->endFunction();  
}

void c_ror(encryption &_en,decryption &_de,const AsmJit::GPReg & _op_r )
{
  using namespace AsmJit;
#ifdef PROTECT_X64
  char r = m_random()%0x64;
#else
  char r = m_random()%0x32;
#endif
  _de.defuc = new AsmJit::Assembler;
  _de.defuc->ror(_op_r,r);
  _en.enfuc = new AsmJit::Compiler;
#ifdef DEBUG
  //   _en.enfuc->setLogger(&logger);
#endif  
  bool bD = _op_r.isGPD();
  bool bQ = _op_r.isGPQ();
  bool bW = _op_r.isGPW();
  bool bB = _op_r.isGPB();

  if (bB)
  {
    _en.enfuc->newFunction(CALL_CONV_DEFAULT, FunctionBuilder1<unsigned char,unsigned char*>());
    GPVar result(_en.enfuc->newGP());
    _en.enfuc->ror(byte_ptr(_en.enfuc->argGP(0)),r);
    _en.enfuc->movzx(result,byte_ptr(_en.enfuc->argGP(0)));
      _en.enfuc->ret(result);    
  }
  else if (bW)
  {
    _en.enfuc->newFunction(CALL_CONV_DEFAULT, FunctionBuilder1<unsigned short,unsigned short*>());
    GPVar result(_en.enfuc->newGP());    
     _en.enfuc->ror(word_ptr(_en.enfuc->argGP(0)),r);
    _en.enfuc->movzx(result,word_ptr(_en.enfuc->argGP(0)));
      _en.enfuc->ret(result);    
  }
  else if (bD)
  {
    _en.enfuc->newFunction(CALL_CONV_DEFAULT, FunctionBuilder1<unsigned int,unsigned int*>());
    GPVar result(_en.enfuc->newGP());    
    _en.enfuc->ror(dword_ptr(_en.enfuc->argGP(0)),r);
#ifdef PROTECT_X64
      _en.enfuc->mov(result,qword_ptr(_en.enfuc->argGP(0)));
      _en.enfuc->and_(result,0x00000000ffffffff);    
#else
    _en.enfuc->mov(result,dword_ptr(_en.enfuc->argGP(0)));
#endif
      _en.enfuc->ret(result);    
  }
#ifdef PROTECT_X64
  else
  {
    _en.enfuc->newFunction(CALL_CONV_DEFAULT, FunctionBuilder1<unsigned long,unsigned long*>());
    GPVar result(_en.enfuc->newGP());    
    _en.enfuc->ror(qword_ptr(_en.enfuc->argGP(0)),r);
    _en.enfuc->mov(result,qword_ptr(_en.enfuc->argGP(0)));
      _en.enfuc->ret(result);    
  }
#endif
  _en.enfuc->endFunction();  
}


void c_inc(encryption &_en,decryption &_de,const AsmJit::GPReg & _op_r)
{
  using namespace AsmJit;
  _de.defuc = new AsmJit::Assembler;
  _de.defuc->inc(_op_r);
  _en.enfuc = new AsmJit::Compiler;
#ifdef DEBUG
  // _en.enfuc->setLogger(&logger);
#endif  
  bool bD = _op_r.isGPD();
  bool bQ = _op_r.isGPQ();
  bool bW = _op_r.isGPW();
  bool bB = _op_r.isGPB();
  if (bB)
  {
    _en.enfuc->newFunction(CALL_CONV_DEFAULT, FunctionBuilder1<unsigned char,unsigned char*>());
    GPVar result(_en.enfuc->newGP());    
    _en.enfuc->inc(byte_ptr(_en.enfuc->argGP(0)));
    _en.enfuc->movzx(result,byte_ptr(_en.enfuc->argGP(0)));
      _en.enfuc->ret(result);    
  }
  else if (bW)
  {
    _en.enfuc->newFunction(CALL_CONV_DEFAULT, FunctionBuilder1<unsigned short,unsigned short*>());
    GPVar result(_en.enfuc->newGP());  
     _en.enfuc->inc(word_ptr(_en.enfuc->argGP(0)));
    _en.enfuc->movzx(result,word_ptr(_en.enfuc->argGP(0)));
      _en.enfuc->ret(result);    
  }
  else if (bD)
  {
    _en.enfuc->newFunction(CALL_CONV_DEFAULT, FunctionBuilder1<unsigned int,unsigned int*>());
    GPVar result(_en.enfuc->newGP());  
    _en.enfuc->inc(dword_ptr(_en.enfuc->argGP(0)));
#ifdef PROTECT_X64
      _en.enfuc->mov(result,qword_ptr(_en.enfuc->argGP(0)));
      _en.enfuc->and_(result,0x00000000ffffffff);        
#else
    _en.enfuc->mov(result,dword_ptr(_en.enfuc->argGP(0)));
#endif
      _en.enfuc->ret(result);    
  }
#ifdef PROTECT_X64
  else
  {
    _en.enfuc->newFunction(CALL_CONV_DEFAULT, FunctionBuilder1<unsigned long,unsigned long*>());
    GPVar result(_en.enfuc->newGP());  
    _en.enfuc->inc(qword_ptr(_en.enfuc->argGP(0)));
    _en.enfuc->mov(result,qword_ptr(_en.enfuc->argGP(0)));
      _en.enfuc->ret(result);    
  }
#endif
  _en.enfuc->endFunction();
}

void c_dec(encryption &_en,decryption &_de,const AsmJit::GPReg & _op_r )
{
  using namespace AsmJit;
  _de.defuc = new AsmJit::Assembler;
  _de.defuc->dec(_op_r);
  _en.enfuc = new AsmJit::Compiler;
#ifdef DEBUG
  // _en.enfuc->setLogger(&logger);
#endif  
  bool bD = _op_r.isGPD();
  bool bQ = _op_r.isGPQ();
  bool bW = _op_r.isGPW();
  bool bB = _op_r.isGPB();
  if (bB)
  {
    _en.enfuc->newFunction(CALL_CONV_DEFAULT, FunctionBuilder1<unsigned char,unsigned char*>());
    GPVar result(_en.enfuc->newGP());  
    _en.enfuc->dec(byte_ptr(_en.enfuc->argGP(0)));
    _en.enfuc->movzx(result,byte_ptr(_en.enfuc->argGP(0)));
      _en.enfuc->ret(result);    
  }
  else if (bW)
  {
    _en.enfuc->newFunction(CALL_CONV_DEFAULT, FunctionBuilder1<unsigned short,unsigned short*>());
    GPVar result(_en.enfuc->newGP());
     _en.enfuc->dec(word_ptr(_en.enfuc->argGP(0)));
    _en.enfuc->movzx(result,word_ptr(_en.enfuc->argGP(0)));
      _en.enfuc->ret(result);    
  }
  else if (bD)
  {
    _en.enfuc->newFunction(CALL_CONV_DEFAULT, FunctionBuilder1<unsigned int,unsigned int*>());
      GPVar result(_en.enfuc->newGP());  
    _en.enfuc->dec(dword_ptr(_en.enfuc->argGP(0)));
#ifdef PROTECT_X64
      _en.enfuc->mov(result,qword_ptr(_en.enfuc->argGP(0)));
      _en.enfuc->and_(result,0x00000000ffffffff);         
#else
    _en.enfuc->mov(result,dword_ptr(_en.enfuc->argGP(0)));
#endif
      _en.enfuc->ret(result);    
  }
#ifdef PROTECT_X64
  else
  {
    _en.enfuc->newFunction(CALL_CONV_DEFAULT, FunctionBuilder1<unsigned long,unsigned long*>());
      GPVar result(_en.enfuc->newGP());  
    _en.enfuc->dec(qword_ptr(_en.enfuc->argGP(0)));
    _en.enfuc->mov(result,qword_ptr(_en.enfuc->argGP(0)));
      _en.enfuc->ret(result);    
  }
#endif
  _en.enfuc->endFunction();
}

void c_not(encryption &_en,decryption &_de,const AsmJit::GPReg & _op_r )
{
 using namespace AsmJit;
  _de.defuc = new AsmJit::Assembler;
  _de.defuc->not_(_op_r);
  _en.enfuc = new AsmJit::Compiler;

#ifdef DEBUG
  // _en.enfuc->setLogger(&logger);
#endif
  bool bD = _op_r.isGPD();
  bool bQ = _op_r.isGPQ();
  bool bW = _op_r.isGPW();
  bool bB = _op_r.isGPB();
  if (bB)
  {
    _en.enfuc->newFunction(CALL_CONV_DEFAULT, FunctionBuilder1<unsigned char,unsigned char*>());
    GPVar result(_en.enfuc->newGP());  
    _en.enfuc->not_(byte_ptr(_en.enfuc->argGP(0)));
    _en.enfuc->movzx(result,byte_ptr(_en.enfuc->argGP(0)));
      _en.enfuc->ret(result);    
  }
  else if (bW)
  {
    _en.enfuc->newFunction(CALL_CONV_DEFAULT, FunctionBuilder1<unsigned short,unsigned short*>());
    GPVar result(_en.enfuc->newGP());
     _en.enfuc->not_(word_ptr(_en.enfuc->argGP(0)));
    _en.enfuc->movzx(result,word_ptr(_en.enfuc->argGP(0)));
      _en.enfuc->ret(result);    
  }
  else if (bD)
  {
    _en.enfuc->newFunction(CALL_CONV_DEFAULT, FunctionBuilder1<unsigned int,unsigned int*>());
    GPVar result(_en.enfuc->newGP());    
    _en.enfuc->not_(dword_ptr(_en.enfuc->argGP(0)));
#ifdef PROTECT_X64
      _en.enfuc->mov(result,qword_ptr(_en.enfuc->argGP(0)));
      _en.enfuc->and_(result,0x00000000ffffffff);             
#else
    _en.enfuc->mov(result,dword_ptr(_en.enfuc->argGP(0)));
#endif
      _en.enfuc->ret(result);    
  }
#ifdef PROTECT_X64
  else
  {
    _en.enfuc->newFunction(CALL_CONV_DEFAULT, FunctionBuilder1<unsigned long,unsigned long*>());
    GPVar result(_en.enfuc->newGP());    
    _en.enfuc->not_(qword_ptr(_en.enfuc->argGP(0)));
    _en.enfuc->mov(result,qword_ptr(_en.enfuc->argGP(0)));
      _en.enfuc->ret(result);    
  }
#endif
  _en.enfuc->endFunction();
}

void c_xor(encryption &_en,decryption &_de,const AsmJit::GPReg  & _op_r)
{
  using namespace AsmJit;
  
 _de.defuc = new AsmJit::Assembler;
  _en.enfuc = new AsmJit::Compiler;

#ifdef DEBUG
  //  _en.enfuc->setLogger(&logger);
#endif
  
  bool bD = _op_r.isGPD();
  bool bQ = _op_r.isGPQ();
  bool bW = _op_r.isGPW();
  bool bB = _op_r.isGPB();
   if (bB)
   {
      char r = m_random()%0x100;  
      _de.defuc->xor_(_op_r,r);
      _en.enfuc->newFunction(CALL_CONV_DEFAULT, FunctionBuilder1<unsigned char,unsigned char*>());
      GPVar result(_en.enfuc->newGP());
      _en.enfuc->xor_(byte_ptr(_en.enfuc->argGP(0)),r);
      _en.enfuc->movzx(result,byte_ptr(_en.enfuc->argGP(0)));
      _en.enfuc->ret(result);      
    } else if (bW)
    {
      short r = m_random()%0x10000;  
      _de.defuc->xor_(_op_r,r);
      _en.enfuc->newFunction(CALL_CONV_DEFAULT, FunctionBuilder1<unsigned short,unsigned short*>());
      GPVar result(_en.enfuc->newGP());      
      _en.enfuc->xor_(word_ptr(_en.enfuc->argGP(0)),r);
      _en.enfuc->movzx(result,word_ptr(_en.enfuc->argGP(0)));
      _en.enfuc->ret(result);      
    } else if (bD)
    {
      int r = m_random()%0xFFFFFFFF;  
      _de.defuc->xor_(_op_r,r);
      _en.enfuc->newFunction(CALL_CONV_DEFAULT, FunctionBuilder1<unsigned int,unsigned int*>());
      GPVar result(_en.enfuc->newGP());
      _en.enfuc->xor_(dword_ptr(_en.enfuc->argGP(0)),r);
#ifdef PROTECT_X64
      _en.enfuc->mov(result,qword_ptr(_en.enfuc->argGP(0)));
      _en.enfuc->and_(result,0x00000000ffffffff);             
#else
    _en.enfuc->mov(result,dword_ptr(_en.enfuc->argGP(0)));
#endif
      _en.enfuc->ret(result);    
    } else if(bQ)
    {
       long r = m_random();  
      _de.defuc->xor_(_op_r,r);
#ifdef PROTECT_X64
      _en.enfuc->newFunction(CALL_CONV_DEFAULT, FunctionBuilder1<unsigned long,unsigned long*>());
#endif
      GPVar result(_en.enfuc->newGP());      
      _en.enfuc->xor_(qword_ptr(_en.enfuc->argGP(0)),r);
      _en.enfuc->mov(result,qword_ptr(_en.enfuc->argGP(0)));
      _en.enfuc->ret(result);      
    }
     _en.enfuc->endFunction();
}





void vcode_c_xor(vcode_encryption &_en,vcode_decryption &_de,const AsmJit::GPReg  & _rdata,const AsmJit::GPReg & _rkey)
{
  using namespace AsmJit;
  
 _de.defuc = new AsmJit::Assembler;
 _en.enfuc = new AsmJit::Assembler;

#ifdef DEBUG
     _en.enfuc->setLogger(&logger);
#endif
  
  bool bD = _rdata.isGPD();
  bool bQ = _rdata.isGPQ();
  bool bW = _rdata.isGPW();
  bool bB = _rdata.isGPB();
  bool b_register = false;

  long _key_ = 0;
  long _data_ = 1;
#ifdef PROTECT_X64
  _key_ = 16;
  _data_ = 8;
#else
  _key_ = 8;
  _data_ = 4;
#endif
  if (m_random()%50 >= 25)
  {
    b_register = true;
  }
  if (b_register)
  {
    _en.key = 0;
    _de.defuc->xor_(_rdata,_rkey);
  }
#ifdef PROTECT_X64
  _en.enfuc->mov(ndi,qword_ptr(nsp,_data_));
  _en.enfuc->mov(nsi,qword_ptr(nsp,_key_));
#else
  _en.enfuc->mov(ndi,dword_ptr(nsp,_data_));
  _en.enfuc->mov(nsi,dword_ptr(nsp,_key_));
#endif

  if (bB)
  {
    if (!b_register)
    {
      _en.key = m_random()%0xff + 1;
      _de.defuc->xor_(_rdata,_en.key);
    }
    _en.enfuc->mov(al,byte_ptr(nsi));
    _en.enfuc->xor_(byte_ptr(ndi),al);
    _en.enfuc->ret();
  }
  else if (bW)
  {
    if (!b_register)
    {
      _en.key = m_random()%0xffff + 1;
      _de.defuc->xor_(_rdata,_en.key);
    }
    _en.enfuc->mov(ax,word_ptr(nsi));
    _en.enfuc->xor_(word_ptr(ndi),ax);
    _en.enfuc->ret();    
  }
  else if (bD)
  {
    if (!b_register)
    {
      _en.key = m_random()%0xffffffff + 1;
      _de.defuc->xor_(_rdata,_en.key);
    }
    _en.enfuc->mov(eax,dword_ptr(nsi));
    _en.enfuc->xor_(dword_ptr(ndi),eax);
    _en.enfuc->ret();    
  }
#ifdef PROTECT_X64
  else if (bQ)
  {
    if (!b_register)
    {
      _en.key = m_random()%0xffffffffffffffff + 1;
      _de.defuc->xor_(_rdata,_en.key);
    }
    _en.enfuc->mov(rax,qword_ptr(nsi));
    _en.enfuc->xor_(qword_ptr(ndi),rax);
    _en.enfuc->ret();
  }
#endif
  _en.fn = function_cast<vcode_encryption::MyFn>(_en.enfuc->make());
}
  //  f(void data,void key)
  //push key
  //push data

void vcode_c_add(vcode_encryption &_en,vcode_decryption &_de,const AsmJit::GPReg  & _rdata,const AsmJit::GPReg & _rkey)
{
  using namespace AsmJit;
  
 _de.defuc = new AsmJit::Assembler;
 _en.enfuc = new AsmJit::Assembler;

#ifdef DEBUG
     _en.enfuc->setLogger(&logger);
#endif
  
  bool bD = _rdata.isGPD();
  bool bQ = _rdata.isGPQ();
  bool bW = _rdata.isGPW();
  bool bB = _rdata.isGPB();
  bool b_register = false;

  long _key_ = 0;
  long _data_ = 1;
#ifdef PROTECT_X64
  _key_ = 16;
  _data_ = 8;
#else
  _key_ = 8;
  _data_ = 4;
#endif
  if (m_random()%50 >= 25)
  {
    b_register = true;
  }
  if (b_register)
  {
    _en.key = 0;
    _de.defuc->add(_rdata,_rkey);
  }

#ifdef PROTECT_X64
  _en.enfuc->mov(ndi,qword_ptr(nsp,_data_));
  _en.enfuc->mov(nsi,qword_ptr(nsp,_key_));
#else
  _en.enfuc->mov(ndi,dword_ptr(nsp,_data_));
  _en.enfuc->mov(nsi,dword_ptr(nsp,_key_));
#endif

  if (bB)
  {
    if (!b_register)
    {
      _en.key = m_random()%0xff + 1;
      _de.defuc->add(_rdata,_en.key);
    }
    _en.enfuc->mov(al,byte_ptr(nsi));
    _en.enfuc->sub(byte_ptr(ndi),al);
    _en.enfuc->ret();
  }
  else if (bW)
  {
    if (!b_register)
    {
      _en.key = m_random()%0xffff + 1;
      _de.defuc->add(_rdata,_en.key);
    }
    _en.enfuc->mov(ax,word_ptr(nsi));
    _en.enfuc->sub(word_ptr(ndi),ax);
    _en.enfuc->ret();    
  }
  else if (bD)
  {
    if (!b_register)
    {
      _en.key = m_random()%0xffffffff + 1;
      _de.defuc->add(_rdata,_en.key);
    }
    _en.enfuc->mov(eax,dword_ptr(nsi));
    _en.enfuc->sub(dword_ptr(ndi),eax);
    _en.enfuc->ret();    
  }
#ifdef PROTECT_X64
  else if (bQ)
  {
    if (!b_register)
    {
      _en.key = m_random()%0xffffffffffffffff + 1;
      _de.defuc->add(_rdata,_en.key);
    }
    _en.enfuc->mov(rax,qword_ptr(nsi));
    _en.enfuc->sub(qword_ptr(ndi),rax);
    _en.enfuc->ret();
  }
#endif
  _en.fn = function_cast<vcode_encryption::MyFn>(_en.enfuc->make());
}

void vcode_c_sub(vcode_encryption &_en,vcode_decryption &_de,const AsmJit::GPReg  & _rdata,const AsmJit::GPReg & _rkey)
{
  using namespace AsmJit;
  
 _de.defuc = new AsmJit::Assembler;
 _en.enfuc = new AsmJit::Assembler;

#ifdef DEBUG
     _en.enfuc->setLogger(&logger);
#endif
  
  bool bD = _rdata.isGPD();
  bool bQ = _rdata.isGPQ();
  bool bW = _rdata.isGPW();
  bool bB = _rdata.isGPB();
  bool b_register = false;

  long _key_ = 0;
  long _data_ = 1;
#ifdef PROTECT_X64
  _key_ = 16;
  _data_ = 8;
#else
  _key_ = 8;
  _data_ = 4;
#endif
  if (m_random()%50 >= 25)
  {
    b_register = true;
  }
  if (b_register)
  {
    _en.key = 0;
    _de.defuc->sub(_rdata,_rkey);
  }

#ifdef PROTECT_X64
  _en.enfuc->mov(ndi,qword_ptr(nsp,_data_));
  _en.enfuc->mov(nsi,qword_ptr(nsp,_key_));
#else
  _en.enfuc->mov(ndi,dword_ptr(nsp,_data_));
  _en.enfuc->mov(nsi,dword_ptr(nsp,_key_));
#endif

  if (bB)
  {
    if (!b_register)
    {
      _en.key = m_random()%0xff + 1;
      _de.defuc->sub(_rdata,_en.key);
    }
    _en.enfuc->mov(al,byte_ptr(nsi));
    _en.enfuc->add(byte_ptr(ndi),al);
    _en.enfuc->ret();
  }
  else if (bW)
  {
    if (!b_register)
    {
      _en.key = m_random()%0xffff + 1;
      _de.defuc->sub(_rdata,_en.key);
    }
    _en.enfuc->mov(ax,word_ptr(nsi));
    _en.enfuc->add(word_ptr(ndi),ax);
    _en.enfuc->ret();    
  }
  else if (bD)
  {
    if (!b_register)
    {
      _en.key = m_random()%0xffffffff + 1;
      _de.defuc->sub(_rdata,_en.key);
    }
    _en.enfuc->mov(eax,dword_ptr(nsi));
    _en.enfuc->add(dword_ptr(ndi),eax);
    _en.enfuc->ret();    
  }
#ifdef PROTECT_X64
  else if (bQ)
  {
    if (!b_register)
    {
      _en.key = m_random()%0xffffffffffffffff + 1;
      _de.defuc->sub(_rdata,_en.key);
    }
    _en.enfuc->mov(rax,qword_ptr(nsi));
    _en.enfuc->add(qword_ptr(ndi),rax);
    _en.enfuc->ret();
  }
#endif
  _en.fn = function_cast<vcode_encryption::MyFn>(_en.enfuc->make());
}

const GPReg & get_register_l(const GPReg & r)
{
  using namespace AsmJit;
  GPReg reg_array[4][8]=
    {
      al,bl,cl,dl,ah,bh,ch,dh,
      ax,bx,cx,dx,sp,bp,si,di,
      eax,ebx,ecx,edx,esp,ebp,esi,edi,
      nax,nbx,ncx,ndx,nsp,nbp,nsi,ndi
    };
  for (int i = 0; i < 4; ++i)
  {
    for (int j = 0; j < 8; ++j)
    {
      if (memcmp(&reg_array[i][j],&r,sizeof(GPReg))==0)
      {
        return  reg_array[0][j];
      }
    }
  }
}

void vcode_c_ror(vcode_encryption &_en,vcode_decryption &_de,const AsmJit::GPReg  & _rdata,const AsmJit::GPReg & _rkey)
{
  using namespace AsmJit;
  
 _de.defuc = new AsmJit::Assembler;
 _en.enfuc = new AsmJit::Assembler;

#ifdef DEBUG
     _en.enfuc->setLogger(&logger);
#endif
  
  bool bD = _rdata.isGPD();
  bool bQ = _rdata.isGPQ();
  bool bW = _rdata.isGPW();
  bool bB = _rdata.isGPB();
  bool b_register = false;

  long _key_ = 0;
  long _data_ = 1;
  long max_r;
#ifdef PROTECT_X64
  _key_ = 16;
  _data_ = 8;
  max_r = 64;
#else
  _key_ = 8;
  _data_ = 4;
  max_r = 32;
#endif
  if (m_random()%50 >= 25)
  {
    b_register = true;
  }
  if (b_register)
  {
    _en.key = 0;
    _de.defuc->mov(AsmJit::cl,get_register_l(_rkey));
    _de.defuc->ror(_rdata,AsmJit::cl);
  }

#ifdef PROTECT_X64
  _en.enfuc->mov(ndi,qword_ptr(nsp,_data_));
  _en.enfuc->mov(nsi,qword_ptr(nsp,_key_));
#else
  _en.enfuc->mov(ndi,dword_ptr(nsp,_data_));
  _en.enfuc->mov(nsi,dword_ptr(nsp,_key_));
#endif

  if (bB)
  {
    if (!b_register)
    {
      _en.key = m_random()%max_r+1;
      _de.defuc->ror(_rdata,_en.key);
    }
    _en.enfuc->mov(cl,byte_ptr(nsi));
    _en.enfuc->rol(byte_ptr(ndi),cl);
    _en.enfuc->ret();
  }
  else if (bW)
  {
    if (!b_register)
    {
      _en.key = m_random()%max_r+1;
      _de.defuc->ror(_rdata,_en.key);
    }
    _en.enfuc->mov(cl,byte_ptr(nsi));
    _en.enfuc->rol(word_ptr(ndi),cl);
    _en.enfuc->ret();    
  }
  else if (bD)
  {
    if (!b_register)
    {
      _en.key = m_random()%max_r+1;
      _de.defuc->ror(_rdata,_en.key);
    }
    _en.enfuc->mov(cl,byte_ptr(nsi));
    _en.enfuc->rol(dword_ptr(ndi),cl);
    _en.enfuc->ret();    
  }
#ifdef PROTECT_X64
  else if (bQ)
  {
    if (!b_register)
    {
      _en.key = m_random()%max_r+1;
      _de.defuc->ror(_rdata,_en.key);
    }
    _en.enfuc->mov(cl,byte_ptr(nsi));
    _en.enfuc->rol(qword_ptr(ndi),cl);
    _en.enfuc->ret();
  }
#endif
  _en.fn = function_cast<vcode_encryption::MyFn>(_en.enfuc->make());
}


void vcode_c_rol(vcode_encryption &_en,vcode_decryption &_de,const AsmJit::GPReg  & _rdata,const AsmJit::GPReg & _rkey)
{
  using namespace AsmJit;
  
 _de.defuc = new AsmJit::Assembler;
 _en.enfuc = new AsmJit::Assembler;

#ifdef DEBUG
     _en.enfuc->setLogger(&logger);
#endif
  
  bool bD = _rdata.isGPD();
  bool bQ = _rdata.isGPQ();
  bool bW = _rdata.isGPW();
  bool bB = _rdata.isGPB();
  bool b_register = false;

  long _key_ = 0;
  long _data_ = 1;
  long max_r;
#ifdef PROTECT_X64
  _key_ = 16;
  _data_ = 8;
  max_r = 64;
#else
  _key_ = 8;
  _data_ = 4;
  max_r = 32;
#endif
  if (m_random()%50 >= 25)
  {
    b_register = true;
  }
  if (b_register)
  {
    _en.key = 0;
    _de.defuc->mov(AsmJit::cl,get_register_l(_rkey));
    _de.defuc->rol(_rdata,AsmJit::cl);
  }

#ifdef PROTECT_X64
  _en.enfuc->mov(ndi,qword_ptr(nsp,_data_));
  _en.enfuc->mov(nsi,qword_ptr(nsp,_key_));
#else
  _en.enfuc->mov(ndi,dword_ptr(nsp,_data_));
  _en.enfuc->mov(nsi,dword_ptr(nsp,_key_));
#endif

  if (bB)
  {
    if (!b_register)
    {
      _en.key = m_random()%max_r+1;
      _de.defuc->rol(_rdata,_en.key);
    }
    _en.enfuc->mov(cl,byte_ptr(nsi));
    _en.enfuc->ror(byte_ptr(ndi),cl);
    _en.enfuc->ret();
  }
  else if (bW)
  {
    if (!b_register)
    {
      _en.key = m_random()%max_r+1;
      _de.defuc->rol(_rdata,_en.key);
    }
    _en.enfuc->mov(cl,byte_ptr(nsi));
    _en.enfuc->ror(word_ptr(ndi),cl);
    _en.enfuc->ret();    
  }
  else if (bD)
  {
    if (!b_register)
    {
      _en.key = m_random()%max_r+1;
      _de.defuc->rol(_rdata,_en.key);
    }
    _en.enfuc->mov(cl,byte_ptr(nsi));
    _en.enfuc->ror(dword_ptr(ndi),cl);
    _en.enfuc->ret();    
  }
#ifdef PROTECT_X64
  else if (bQ)
  {
    if (!b_register)
    {
      _en.key = m_random()%max_r+1;
      _de.defuc->rol(_rdata,_en.key);
    }
    _en.enfuc->mov(cl,byte_ptr(nsi));
    _en.enfuc->ror(qword_ptr(ndi),cl);
    _en.enfuc->ret();
  }
#endif
  _en.fn = function_cast<vcode_encryption::MyFn>(_en.enfuc->make());
}

void vcode_c_not(vcode_encryption &_en,vcode_decryption &_de,const AsmJit::GPReg  & _rdata,const AsmJit::GPReg & _rkey)
{
  using namespace AsmJit;
  
 _de.defuc = new AsmJit::Assembler;
 _en.enfuc = new AsmJit::Assembler;

#ifdef DEBUG
     _en.enfuc->setLogger(&logger);
#endif
  
  bool bD = _rdata.isGPD();
  bool bQ = _rdata.isGPQ();
  bool bW = _rdata.isGPW();
  bool bB = _rdata.isGPB();

  long _key_ = 0;
  long _data_ = 1;
  long max_r;
#ifdef PROTECT_X64
  _key_ = 16;
  _data_ = 8;
  max_r = 64;
#else
  _key_ = 8;
  _data_ = 4;
  max_r = 32;
#endif

  _de.defuc->not_(_rdata);

#ifdef PROTECT_X64
  _en.enfuc->mov(ndi,qword_ptr(nsp,_data_));
#else
  _en.enfuc->mov(ndi,dword_ptr(nsp,_data_));
#endif

  if (bB)
  {
    _en.enfuc->not_(byte_ptr(ndi));
    _en.enfuc->ret();
  }
  else if (bW)
  {
    _en.enfuc->not_(word_ptr(ndi));
    _en.enfuc->ret();    
  }
  else if (bD)
  {
    _en.enfuc->not_(dword_ptr(ndi));
    _en.enfuc->ret();    
  }
#ifdef PROTECT_X64
  else if (bQ)
  {
    _en.enfuc->not_(qword_ptr(ndi));
    _en.enfuc->ret();
  }
#endif
  _en.fn = function_cast<vcode_encryption::MyFn>(_en.enfuc->make());
}

void vcode_c_dec(vcode_encryption &_en,vcode_decryption &_de,const AsmJit::GPReg  & _rdata,const AsmJit::GPReg & _rkey)
{
  using namespace AsmJit;
  
 _de.defuc = new AsmJit::Assembler;
 _en.enfuc = new AsmJit::Assembler;

#ifdef DEBUG
     _en.enfuc->setLogger(&logger);
#endif
  
  bool bD = _rdata.isGPD();
  bool bQ = _rdata.isGPQ();
  bool bW = _rdata.isGPW();
  bool bB = _rdata.isGPB();

  long _key_ = 0;
  long _data_ = 1;
  long max_r;
#ifdef PROTECT_X64
  _key_ = 16;
  _data_ = 8;
  max_r = 64;
#else
  _key_ = 8;
  _data_ = 4;
  max_r = 32;
#endif
  _de.defuc->dec(_rdata);

#ifdef PROTECT_X64
  _en.enfuc->mov(ndi,qword_ptr(nsp,_data_));
#else
  _en.enfuc->mov(ndi,dword_ptr(nsp,_data_));
#endif


  if (bB)
  {
    _en.enfuc->inc(byte_ptr(ndi));
    _en.enfuc->ret();
  }
  else if (bW)
  {
    _en.enfuc->inc(word_ptr(ndi));
    _en.enfuc->ret();    
  }
  else if (bD)
  {
    _en.enfuc->inc(dword_ptr(ndi));
    _en.enfuc->ret();    
  }
#ifdef PROTECT_X64
  else if (bQ)
  {
    _en.enfuc->inc(qword_ptr(ndi));
    _en.enfuc->ret();
  }
#endif
  _en.fn = function_cast<vcode_encryption::MyFn>(_en.enfuc->make());
}


 void vcode_c_inc(vcode_encryption &_en,vcode_decryption &_de,const AsmJit::GPReg  & _rdata,const AsmJit::GPReg & _rkey)
{
  using namespace AsmJit;
  
 _de.defuc = new AsmJit::Assembler;
 _en.enfuc = new AsmJit::Assembler;

#ifdef DEBUG
     _en.enfuc->setLogger(&logger);
#endif
  
  bool bD = _rdata.isGPD();
  bool bQ = _rdata.isGPQ();
  bool bW = _rdata.isGPW();
  bool bB = _rdata.isGPB();

  long _key_ = 0;
  long _data_ = 1;
  long max_r;
#ifdef PROTECT_X64
  _key_ = 16;
  _data_ = 8;
  max_r = 64;
#else
  _key_ = 8;
  _data_ = 4;
  max_r = 32;
#endif
  _de.defuc->inc(_rdata);

#ifdef PROTECT_X64
  _en.enfuc->mov(ndi,qword_ptr(nsp,_data_));
#else
  _en.enfuc->mov(ndi,dword_ptr(nsp,_data_));
#endif


  if (bB)
  {
    _en.enfuc->dec(byte_ptr(ndi));
    _en.enfuc->ret();
  }
  else if (bW)
  {
    _en.enfuc->dec(word_ptr(ndi));
    _en.enfuc->ret();    
  }
  else if (bD)
  {
    _en.enfuc->dec(dword_ptr(ndi));
    _en.enfuc->ret();    
  }
#ifdef PROTECT_X64
  else if (bQ)
  {
    _en.enfuc->dec(qword_ptr(ndi));
    _en.enfuc->ret();
  }
#endif
  _en.fn = function_cast<vcode_encryption::MyFn>(_en.enfuc->make());
}

void VMHandle::full_handle_info(handle_info & info,char flag)
{
  if (flag == FULL_BEGIN)
  {
    info.type = 0;
     unsigned char * code = a.getCode();
     info.size = a.getCodeSize();
     info.buf = &code[a.getCodeSize()];
     info.offset = a.getOffset();
     //return ;
     goto encode;
  }
  else if (flag == FULL_END)
  {
    info.size = a.getCodeSize()-info.size;
    return;
    // printf("HANDLE_END\r\n");
  }
  else if (flag == FULL_BYTE_DECODE)
  {
    info.type = READ_BYTE;

    typedef void (*algorithms_vcode) (vcode_encryption &,vcode_decryption &,const GPReg &,const GPReg &);
    algorithms_vcode alg_vcode_fuc_array[]=
      {
        vcode_c_add,
        vcode_c_sub,
        vcode_c_xor,
        vcode_c_ror,
        vcode_c_rol,
        vcode_c_not,
        vcode_c_inc,
        vcode_c_dec
       };
    int alg_count = sizeof(alg_vcode_fuc_array)/sizeof(alg_vcode_fuc_array[0]);
    int r = rand()%alg_count;
    vcode_encryption en;
    vcode_decryption de;
    en.key = 0;
    for (int i = 0; i < r; ++i)
    {
      algorithms_vcode fuc = alg_vcode_fuc_array[rand()%alg_count];
      fuc(en,de,AsmJit::al,AsmJit::bl);
      for (int i = 0; i < de.defuc->getCodeSize(); ++i)
      {
        unsigned char * code = de.defuc->getCode();
        a.db(code[i]);
      }      
      info.encode_pcode.push_back(en);
      info.decode_pcode.push_back(de);      
    }
    return;
  }
  else if (flag == FULL_WORD_DECODE)
  {
    info.type = READ_WORD;
    typedef void (*algorithms_vcode) (vcode_encryption &,vcode_decryption &,const GPReg &,const GPReg &);
    algorithms_vcode alg_vcode_fuc_array[]=
      {
         vcode_c_add,
         vcode_c_sub,
         vcode_c_xor,
         vcode_c_ror,
         vcode_c_rol,
         vcode_c_not,
         vcode_c_inc,
         vcode_c_dec
       };
    int alg_count = sizeof(alg_vcode_fuc_array)/sizeof(alg_vcode_fuc_array[0]);
    int r = rand()%alg_count;
    vcode_encryption en;
    vcode_decryption de;
    en.key = 0;
    for (int i = 0; i < r; ++i)
    {
      algorithms_vcode fuc = alg_vcode_fuc_array[rand()%alg_count];
      fuc(en,de,AsmJit::ax,AsmJit::bx);
      for (int i = 0; i < de.defuc->getCodeSize(); ++i)
      {
        unsigned char * code = de.defuc->getCode();
        a.db(code[i]);
      }      
      info.encode_pcode.push_back(en);
      info.decode_pcode.push_back(de);      
    }    
    return;
  }
  else if (flag == FULL_DWORD_DECODE)
  {
    info.type = READ_DWORD;
    typedef void (*algorithms_vcode) (vcode_encryption &,vcode_decryption &,const GPReg &,const GPReg &);
    algorithms_vcode alg_vcode_fuc_array[]=
      {
         vcode_c_add,
         vcode_c_sub,
         vcode_c_xor,
         vcode_c_ror,
         vcode_c_rol,
         vcode_c_not,
         vcode_c_inc,
         vcode_c_dec
       };
    int alg_count = sizeof(alg_vcode_fuc_array)/sizeof(alg_vcode_fuc_array[0]);
    int r = rand()%alg_count;
    vcode_encryption en;
    vcode_decryption de;
    en.key = 0;
    for (int i = 0; i < r; ++i)
    {
      algorithms_vcode fuc = alg_vcode_fuc_array[rand()%alg_count];
      fuc(en,de,AsmJit::eax,AsmJit::ebx);
      for (int i = 0; i < de.defuc->getCodeSize(); ++i)
      {
        unsigned char * code = de.defuc->getCode();
        a.db(code[i]);
      }      
      info.encode_pcode.push_back(en);
      info.decode_pcode.push_back(de);      
    }    
    return;
  }
  else if (flag == FULL_QWORD_DECODE)
  {
    info.type = READ_QWORD;
    typedef void (*algorithms_vcode) (vcode_encryption &,vcode_decryption &,const GPReg &,const GPReg &);
    algorithms_vcode alg_vcode_fuc_array[]=
      {
         vcode_c_add,
         vcode_c_sub,
         vcode_c_xor,
         vcode_c_ror,
         vcode_c_rol,
         vcode_c_not,
         vcode_c_inc,
         vcode_c_dec
       };
    int alg_count = sizeof(alg_vcode_fuc_array)/sizeof(alg_vcode_fuc_array[0]);
    int r = rand()%alg_count;
    vcode_encryption en;
    vcode_decryption de;
    en.key = 0;
    for (int i = 0; i < r; ++i)
    {
      algorithms_vcode fuc = alg_vcode_fuc_array[rand()%alg_count];
      fuc(en,de,nax,nbx);
      for (int i = 0; i < de.defuc->getCodeSize(); ++i)
      {
        unsigned char * code = de.defuc->getCode();
        a.db(code[i]);
      }      
      info.encode_pcode.push_back(en);
      info.decode_pcode.push_back(de);      
    }    
    return;
  }
 encode:
  typedef void (*algorithm) (encryption &,decryption &,const AsmJit::GPReg &);
    algorithm alg_fuc_array[] = 
        {
          c_add,
          c_dec,
          c_inc,
          c_sub,
          c_not,
          c_rol,
          c_ror,
          c_xor
        };
    int count = sizeof(alg_fuc_array)/sizeof(alg_fuc_array[0]);
    int r = rand()%count;

    
    for (int i = 0; i < r; ++i)
    {
      algorithm fuc = alg_fuc_array[rand()%count];
      encryption en;
      decryption de;
      
      GPReg random_register_array[] = 
        {
          bl,bx,ebx,nbx
        };
      size_t size = sizeof(random_register_array)/sizeof(random_register_array[0]);

      int r_reg = rand()%size;
      fuc(en,de,random_register_array[r_reg]);

      for (int i = 0; i < de.defuc->getCodeSize(); ++i)
      {
        unsigned char * code = de.defuc->getCode();
        a.db(code[i]);
      }
      //en.fn = function_cast<encryption::MyFn>(en.enfuc->make());
      info.encode_key.push_back(en);
      info.decode_key.push_back(de);
      info.encode_key.back().fn =
        function_cast<encryption::MyFn>(info.encode_key.back().enfuc->make());
      long key = 3;
      info.encode_key.back().fn(&key);
    }
}

void VMHandle::read_pc_byte(handle_info & info)
{
  if (fuc_select.addorsub)
  {
    a.mov(al,byte_ptr(esi));
    a.inc(esi);
  }
  else
  {
    a.mov(al,byte_ptr(esi,-1));
    a.dec(esi);
  }
  full_handle_info(info,FULL_BYTE_DECODE);
}

void VMHandle::read_pc_word(handle_info &info)
{
  if (fuc_select.addorsub)
  {
    a.mov(ax,word_ptr(esi));
    a.add(esi,2);
  }
  else
  {
    a.mov(ax,word_ptr(esi,-2));
    a.sub(esi,2);
  }
  full_handle_info(info,FULL_WORD_DECODE);
}

void VMHandle::read_pc_dword(handle_info &info)
{
  if (fuc_select.addorsub)
  {
    a.mov(eax,dword_ptr(esi));
    a.add(esi,4);
  }
  else
  {
    a.mov(eax,dword_ptr(esi,-4));
    a.sub(esi,4);
  }
  full_handle_info(info,FULL_DWORD_DECODE);
}

void VMHandle::read_pc_qword(handle_info &info)
{
  if (fuc_select.addorsub)
  {
    a.mov(nax,qword_ptr(nsi));
    a.add(nsi,4);
  }
  else
  {
    a.mov(nax,qword_ptr(nsi,-8));
    a.sub(nsi,8);
  }
  full_handle_info(info,FULL_QWORD_DECODE);
}

handle_info VMHandle::b_read_stack()
{
  handle_info info;
  a.bind(l_b_read_stack);
  info.label = &l_b_read_stack;
  full_handle_info(info,FULL_BEGIN);

#ifndef PROTECT_X64
  read_pc_dword(info);
#else
  read_pc_qword(info);
#endif
  a.mov(al,byte_ptr(nax,nbp));
  a.sub(nbp,1);
  a.mov(byte_ptr(nbp),al);

  a.jmp(l_check_stack);
  full_handle_info(info,FULL_END);
  return info;
}

handle_info VMHandle::w_read_stack()
{
  handle_info info;
  a.bind(l_w_read_stack);
  info.label = &l_w_read_stack;
  full_handle_info(info,FULL_BEGIN);

#ifndef PROTECT_X64
  read_pc_dword(info);
#else
  read_pc_qword(info);
#endif

  a.mov(ax,word_ptr(nbp,nax));
  a.sub(nbp,2);
  a.mov(word_ptr(nbp),ax);
  a.jmp(l_check_stack);

  full_handle_info(info,FULL_END);
  return info;
}

handle_info VMHandle::d_read_stack()
{
  handle_info info;
  a.bind(l_d_read_stack);
  info.label = &l_d_read_stack;
  full_handle_info(info,FULL_BEGIN);

#ifndef PROTECT_X64
  read_pc_dword(info);
#else
  read_pc_qword(info);
#endif

  a.mov(nax,dword_ptr(nbp,nax));
  a.sub(nbp,4);
  a.mov(dword_ptr(nbp),eax);
  a.jmp(l_check_stack);

  full_handle_info(info,FULL_END);
  return info;
}

handle_info VMHandle::q_read_stack()
{
  handle_info info;
  a.bind(l_q_read_stack);
  info.label = &l_q_read_stack;
  full_handle_info(info,FULL_BEGIN);

#ifndef PROTECT_X64
  read_pc_dword(info);
#else
  read_pc_qword(info);
#endif

  a.mov(nax,qword_ptr(nbp,nax));
  a.sub(nbp,8);
  a.mov(qword_ptr(nbp),nax);
  a.jmp(l_check_stack);

  full_handle_info(info,FULL_END);
  return info;
}


handle_info VMHandle::initialization(long pcode_base)
{
  handle_info info;
  a.bind(l_initialization);
  info.label = &l_initialization;
  full_handle_info(info,FULL_BEGIN);

  a.pushf();
#ifndef PROTECT_X64
  a.pushad();
#else
  a.push(nax);
  a.push(ndx);
  a.push(ncx);
  a.push(nbx);
  a.push(nsp);
  a.push(nbp);
  a.push(nsi);
  a.push(ndi);
  a.push(r8);
  a.push(r9);
  a.push(r10);
  a.push(r11);
  a.push(r12);
  a.push(r13);
  a.push(r14);
  a.push(r15);
#endif

  a.mov(nbp,nsp);
#ifndef PROTECT_X64
  a.sub(nsp,0xc0);
#else
  a.sub(nsp,0xc0 * 2);
#endif
  a.mov(ndi,nsp);
  a.mov(nsi,pcode_base);
  a.jmp(l_dispatch);

  full_handle_info(info,FULL_END);
  return info;
}

handle_info VMHandle::dispatch(long table_addr)
{
  handle_info info;
#ifdef DEBUG
  strcpy(info.handle_name,"dispatch");
#endif
  a.bind(l_dispatch);
  info.label = &l_dispatch;
  full_handle_info(info,FULL_BEGIN);

  if (fuc_select.addorsub)
  {
    a.movzx(nax,byte_ptr(nsi));
    a.inc(nsi);
  }
  else
  {
    a.movzx(nax,byte_ptr(nsi,-1));
    a.dec(nsi);
  }

  full_handle_info(info,FULL_BYTE_DECODE);

#ifdef PROTECT_X64
  a.push(qword_ptr_abs((void*)table_addr,nax,3));
#else
  a.push(dword_ptr_abs((void*)table_addr,nax,2));
#endif
  a.ret();
  full_handle_info(info,FULL_END);
  return info;
}

handle_info VMHandle::b_write_stack()
{
  handle_info info;
#ifdef DEBUG
  strcpy(info.handle_name,"b_write_stack");
#endif
  a.bind(l_b_read_stack);
  info.label = &l_b_read_stack;
  full_handle_info(info,FULL_BEGIN);
#ifndef PROTECT_X64
  read_pc_dword(info);
#else
  read_pc_qword(info);
#endif
  a.mov(dl,byte_ptr(nbp));
  a.mov(byte_ptr(nbp,nax),dl);
  //a.add(nbp,1);
  a.inc(nbp);

  a.jmp(l_check_stack);
  full_handle_info(info,FULL_END);
  return info;
}
handle_info VMHandle::w_write_stack()
{
  handle_info info;
#ifdef DEBUG
  strcpy(info.handle_name,"w_write_stack");
#endif  
  a.bind(l_w_read_stack);
  info.label = &l_w_read_stack;
  full_handle_info(info,FULL_BEGIN);
#ifndef PROTECT_X64
  read_pc_dword(info);
#else
  read_pc_qword(info);
#endif
  a.mov(dx,word_ptr(nbp));
  a.mov(word_ptr(nbp,nax),dx);
  a.add(nbp,2);

  a.jmp(l_check_stack);
  full_handle_info(info,FULL_END);
  return info;
}

handle_info VMHandle::d_write_stack()
{
  handle_info info;
#ifdef DEBUG
  strcpy(info.handle_name,"d_write_stack");
#endif  
  a.bind(l_d_read_stack);
  info.label = &l_d_read_stack;
  full_handle_info(info,FULL_BEGIN);
#ifndef PROTECT_X64
  read_pc_dword(info);
#else
  read_pc_qword(info);
#endif
  a.mov(edx,dword_ptr(nbp));
  a.mov(dword_ptr(nbp,nax),edx);
  a.add(nbp,4);

  a.jmp(l_check_stack);
  full_handle_info(info,FULL_END);
  return info;
}

handle_info VMHandle::q_write_stack()
{
  handle_info info;
#ifdef DEBUG
  strcpy(info.handle_name,"q_write_stack");
#endif  
  a.bind(l_q_read_stack);
  info.label = &l_q_read_stack;
  full_handle_info(info,FULL_BEGIN);
#ifndef PROTECT_X64
  read_pc_dword(info);
#else
  read_pc_qword(info);
#endif
  a.mov(ndx,qword_ptr(nbp));
  a.mov(qword_ptr(nbp,nax),ndx);
  a.add(nbp,8);

  a.jmp(l_check_stack);
  full_handle_info(info,FULL_END);
  return info;
}

handle_info VMHandle::b_push_reg()
{
  handle_info info;
#ifdef DEBUG
  strcpy(info.handle_name,"b_push_reg");
#endif  
  a.bind(l_b_push_reg);
  info.label = &l_b_push_reg;
  full_handle_info(info,FULL_BEGIN);

  read_pc_byte(info);

  a.movzx(nax,al);
  a.mov(al,byte_ptr(ndi,nax));
  a.dec(nbp);
  a.mov(byte_ptr(nbp),al);

  a.jmp(l_check_stack);
  full_handle_info(info,FULL_END);
  return info;
}

handle_info VMHandle::w_puah_reg()
{
  handle_info info;
#ifdef DEBUG
  strcpy(info.handle_name,"w_push_reg");
#endif
  a.bind(l_w_push_reg);
  info.label = &l_w_push_reg;
  full_handle_info(info,FULL_BEGIN);

  read_pc_byte(info);

  a.movzx(nax,al);
  a.mov(ax,word_ptr(ndi,nax));
  a.sub(nbp,2);
  a.mov(word_ptr(nbp),ax);

  a.jmp(l_check_stack);
  full_handle_info(info,FULL_END);
  return info;
}

handle_info VMHandle::d_push_reg()
{
    handle_info info;
#ifdef DEBUG
  strcpy(info.handle_name,"d_push_reg");
#endif    
  a.bind(l_d_push_reg);
  info.label = &l_d_push_reg;
  full_handle_info(info,FULL_BEGIN);

  read_pc_byte(info);

  a.movzx(nax,al);
  a.mov(eax,dword_ptr(ndi,nax));
  a.sub(nbp,4);
  a.mov(dword_ptr(nbp),eax);

  a.jmp(l_check_stack);
  full_handle_info(info,FULL_END);
  return info;
}

handle_info VMHandle::q_push_reg()
{
  handle_info info;
#ifdef DEBUG
  strcpy(info.handle_name,"q_push_reg");
#endif  
  a.bind(l_q_push_reg);
  info.label = &l_q_push_reg;
  full_handle_info(info,FULL_BEGIN);

  read_pc_byte(info);

  a.movzx(nax,al);
  a.mov(al,qword_ptr(ndi,nax));
  a.sub(nbp,8);
  a.mov(qword_ptr(nbp),nax);

  a.jmp(l_check_stack);
  full_handle_info(info,FULL_END);
  return info;
}

handle_info VMHandle::b_pop_reg()
{
  handle_info info;
#ifdef DEBUG
  strcpy(info.handle_name,"b_pop_reg");
#endif  
  a.bind(l_b_pop_reg);
  info.label = &l_b_pop_reg;
  full_handle_info(info,FULL_BEGIN);

  read_pc_byte(info);

  a.movzx(nax,al);
  a.mov(dl,byte_ptr(nbp));
  a.mov(byte_ptr(ndi,nax),dl);
  a.inc(nbp);

  a.jmp(l_check_stack);
  full_handle_info(info,FULL_END);
  return info;
}

handle_info VMHandle::w_pop_reg()
{
  handle_info info;
#ifdef DEBUG
  strcpy(info.handle_name,"w_pop_reg");
#endif  
  a.bind(l_w_pop_reg);
  info.label = &l_w_pop_reg;
  full_handle_info(info,FULL_BEGIN);

  read_pc_byte(info);

  a.movzx(nax,al);
  a.mov(dx,word_ptr(nbp));
  a.mov(word_ptr(ndi,nax),dx);
  a.add(nbp,2);

  a.jmp(l_check_stack);
  full_handle_info(info,FULL_END);
  return info;
}

handle_info VMHandle::d_pop_reg()
{
  handle_info info;
#ifdef DEBUG
  strcpy(info.handle_name,"d_pop_reg");
#endif  
  a.bind(l_d_pop_reg);
  info.label = &l_d_pop_reg;
  full_handle_info(info,FULL_BEGIN);

  read_pc_byte(info);

  a.movzx(nax,al);
  a.mov(edx,dword_ptr(nbp));
  a.mov(dword_ptr(ndi,nax),edx);
  a.add(nbp,4);

  a.jmp(l_check_stack);
  full_handle_info(info,FULL_END);
  return info;
}

handle_info VMHandle::q_pop_reg()
{
  handle_info info;
#ifdef DEBUG
  strcpy(info.handle_name,"q_pop_reg");
#endif  
  a.bind(l_q_pop_reg);
  info.label = &l_q_pop_reg;
  full_handle_info(info,FULL_BEGIN);

  read_pc_byte(info);

  a.movzx(nax,al);
  a.mov(ndx,qword_ptr(nbp));
  a.mov(qword_ptr(ndi,nax),ndx);
  a.add(nbp,8);

  a.jmp(l_check_stack);
  full_handle_info(info,FULL_END);
  return info;
}

handle_info VMHandle::b_push_imm()
{
  handle_info info;
#ifdef DEBUG
  strcpy(info.handle_name,"b_push_imm");
#endif  
  a.bind(l_b_push_imm);
  info.label = &l_b_push_imm;
  full_handle_info(info,FULL_BEGIN);

  read_pc_byte(info);

  a.dec(nbp);
  a.mov(byte_ptr(nbp),al);

  a.jmp(l_check_stack);
  full_handle_info(info,FULL_END);
  return info;
}

handle_info VMHandle::w_push_imm()
{
  handle_info info;
#ifdef DEBUG
  strcpy(info.handle_name,"w_push_imm");
#endif  
  a.bind(l_w_push_imm);
  info.label = &l_w_push_imm;
  full_handle_info(info,FULL_BEGIN);

  read_pc_word(info);

  a.sub(nbp,2);
  a.mov(word_ptr(nbp),ax);

  a.jmp(l_check_stack);
  full_handle_info(info,FULL_END);
  return info;
}

handle_info VMHandle::d_push_imm()
{
    handle_info info;
#ifdef DEBUG
  strcpy(info.handle_name,"d_push_imm");
#endif    
  a.bind(l_d_push_imm);
  info.label = &l_d_push_imm;
  full_handle_info(info,FULL_BEGIN);

  read_pc_dword(info);

  a.sub(nbp,4);
  a.mov(dword_ptr(nbp),eax);

  a.jmp(l_check_stack);
  full_handle_info(info,FULL_END);
  return info;
}

handle_info VMHandle::q_push_imm()
{
    handle_info info;
#ifdef DEBUG
  strcpy(info.handle_name,"q_push_imm");
#endif    
  a.bind(l_q_push_imm);
  info.label = &l_q_push_imm;
  full_handle_info(info,FULL_BEGIN);

  read_pc_qword(info);

  a.sub(nbp,8);
  a.mov(qword_ptr(nbp),nax);

  a.jmp(l_check_stack);
  full_handle_info(info,FULL_END);
  return info;
}

handle_info VMHandle::b_shl() //ebp 俩个byte  变成 5个byte 栈顶是eflag
{
  handle_info info;
#ifdef DEBUG
  strcpy(info.handle_name,"b_shl");
#endif  
  a.bind(l_b_shl);
  info.label = &l_b_shl;
  full_handle_info(info,FULL_BEGIN);
  a.mov(cl,byte_ptr(nbp));
  a.inc(nbp);
  a.mov(al,byte_ptr(nbp));
  a.shl(al,cl);
  a.mov(byte_ptr(nbp),al);
  a.pushf();
#ifndef PROTECT_X64
  a.sub(nbp,4);
  a.pop(dword_ptr(nbp));
#else
  a.sub(nbp,8);
  a.pop(qword_ptr(nbp));
#endif
  a.jmp(l_check_stack);
  full_handle_info(info,FULL_END);
  return info;
}

handle_info VMHandle::w_shl() //栈顶3个byte变成6个Byte
{
  handle_info info;
#ifdef DEBUG
  strcpy(info.handle_name,"w_shl");
#endif  
  a.bind(l_w_shl);
  info.label = &l_w_shl;
  full_handle_info(info,FULL_BEGIN);
  a.mov(cl,byte_ptr(nbp));
  a.inc(nbp);
  a.mov(ax,word_ptr(nbp));
  a.shl(ax,cl);
  a.mov(word_ptr(nbp),ax);
  a.pushf();
#ifndef PROTECT_X64
  a.sub(nbp,4);
  a.pop(dword_ptr(nbp));
#else
  a.sub(nbp,8);
  a.pop(qword_ptr(nbp));
#endif
  a.jmp(l_check_stack);
  full_handle_info(info,FULL_END);
  return info;
}

handle_info VMHandle::d_shl() //5 byte  to  8 byte
{
  handle_info info;
#ifdef DEBUG
  strcpy(info.handle_name,"d_shl");
#endif
  
  a.bind(l_d_shl);
  info.label = &l_d_shl;
  full_handle_info(info,FULL_BEGIN);
  a.mov(cl,byte_ptr(nbp));
  a.inc(nbp);
  a.mov(eax,dword_ptr(nbp));
  a.shl(eax,cl);
  a.mov(dword_ptr(nbp),eax);
  a.pushf();
#ifndef PROTECT_X64
  a.sub(nbp,4);
  a.pop(dword_ptr(nbp));
#else
  a.sub(nbp,8);
  a.pop(qword_ptr(nbp));
#endif
  a.jmp(l_check_stack);
  full_handle_info(info,FULL_END);
  return info;
}

handle_info VMHandle::q_shl() //9 byte to 16 byte
{
    handle_info info;
#ifdef DEBUG
  strcpy(info.handle_name,"q_shl");
#endif    
  a.bind(l_q_shl);
  info.label = &l_q_shl;
  full_handle_info(info,FULL_BEGIN);
  a.mov(cl,byte_ptr(nbp));
  a.inc(nbp);
  a.mov(nax,qword_ptr(nbp));
  a.shl(nax,cl);
  a.mov(qword_ptr(nbp),nax);
  a.pushf();
#ifndef PROTECT_X64
  a.sub(nbp,4);
  a.pop(dword_ptr(nbp));
#else
  a.sub(nbp,8);
  a.pop(qword_ptr(nbp));
#endif
  a.jmp(l_check_stack);
  full_handle_info(info,FULL_END);
  return info;
}

handle_info VMHandle::b_shr()
{
  handle_info info;
#ifdef DEBUG
  strcpy(info.handle_name,"b_shr");
#endif  
  a.bind(l_b_shr);
  info.label = &l_b_shr;
  full_handle_info(info,FULL_BEGIN);
  a.mov(cl,byte_ptr(nbp));
  a.inc(nbp);
  a.mov(al,byte_ptr(nbp));
  a.shr(al,cl);
  a.mov(byte_ptr(nbp),al);
  a.pushf();
#ifndef PROTECT_X64
  a.sub(nbp,4);
  a.pop(dword_ptr(nbp));
#else
  a.sub(nbp,8);
  a.pop(qword_ptr(nbp));
#endif
  a.jmp(l_check_stack);
  full_handle_info(info,FULL_END);
  return info;
}

handle_info VMHandle::w_shr()
{
  handle_info info;
#ifdef DEBUG
  strcpy(info.handle_name,"w_shr");
#endif  
  a.bind(l_w_shr);
  info.label = &l_w_shr;
  full_handle_info(info,FULL_BEGIN);
  a.mov(cl,byte_ptr(nbp));
  a.inc(nbp);
  a.mov(ax,word_ptr(nbp));
  a.shr(ax,cl);
  a.mov(word_ptr(nbp),ax);
  a.pushf();
#ifndef PROTECT_X64
  a.sub(nbp,4);
  a.pop(dword_ptr(nbp));
#else
  a.sub(nbp,8);
  a.pop(qword_ptr(nbp));
#endif
  a.jmp(l_check_stack);
  full_handle_info(info,FULL_END);
  return info;
}

handle_info VMHandle::d_shr()
{
  handle_info info;
#ifdef DEBUG
  strcpy(info.handle_name,"d_shr");
#endif  
  a.bind(l_d_shr);
  info.label = &l_d_shr;
  full_handle_info(info,FULL_BEGIN);
  a.mov(cl,byte_ptr(nbp));
  a.inc(nbp);
  a.mov(eax,dword_ptr(nbp));
  a.shr(eax,cl);
  a.mov(dword_ptr(nbp),eax);
  a.pushf();
#ifndef PROTECT_X64
  a.sub(nbp,4);
  a.pop(dword_ptr(nbp));
#else
  a.sub(nbp,8);
  a.pop(qword_ptr(nbp));
#endif
  a.jmp(l_check_stack);
  full_handle_info(info,FULL_END);
  return info;
}

handle_info VMHandle::q_shr()
{
  handle_info info;
#ifdef DEBUG
  strcpy(info.handle_name,"q_shr");
#endif  
  a.bind(l_q_shr);
  info.label = &l_q_shr;
  full_handle_info(info,FULL_BEGIN);
  a.mov(cl,byte_ptr(nbp));
  a.inc(nbp);
  a.mov(nax,qword_ptr(nbp));
  a.shl(nax,cl);
  a.mov(qword_ptr(nbp),nax);
  a.pushf();
#ifndef PROTECT_X64
  a.sub(nbp,4);
  a.pop(dword_ptr(nbp));
#else
  a.sub(nbp,8);
  a.pop(qword_ptr(nbp));
#endif
  a.jmp(l_check_stack);
  full_handle_info(info,FULL_END);
  return info;
}

handle_info VMHandle::shld() //9byte to 8byte
{
  handle_info info;
#ifdef DEBUG
  strcpy(info.handle_name,"shld");
#endif
  a.bind(l_shld);
  info.label = &l_shld;
  full_handle_info(info,FULL_BEGIN);
  a.mov(eax,dword_ptr(nbp));
  a.mov(edx,dword_ptr(nbp,4));
  a.mov(cl,byte_ptr(nbp,8));
  a.inc(nbp);
  a.shld(eax,edx,cl);
  a.mov(dword_ptr(nbp,4),eax);
#ifdef PROTECT_X64
  a.pushf();
  a.sub(nbp,4);
  a.pop(qword_ptr(nbp));
#else
  a.pushf();
  a.pop(dword_ptr(nbp));
#endif
  a.jmp(l_check_stack);
  full_handle_info(info,FULL_END);
  return info;
}

handle_info VMHandle::shrd()
{
  handle_info info;
#ifdef DEBUG
  strcpy(info.handle_name,"shrd");
#endif  
  a.bind(l_shrd);
  info.label = &l_shrd;
  full_handle_info(info,FULL_BEGIN);
  a.mov(eax,dword_ptr(nbp));
  a.mov(edx,dword_ptr(nbp,4));
  a.mov(cl,byte_ptr(nbp,8));
  a.inc(nbp);
  a.shrd(eax,edx,cl);
  a.mov(dword_ptr(nbp,4),eax);
#ifdef PROTECT_X64
  a.pushf();
  a.sub(nbp,4);
  a.pop(qword_ptr(nbp));
#else
  a.pushf();
  a.pop(dword_ptr(nbp));
#endif
  a.jmp(l_check_stack);
  full_handle_info(info,FULL_END);
  return info;
}

handle_info VMHandle::b_nand() //2byte to 5byte
{
  handle_info info;
#ifdef DEBUG
  strcpy(info.handle_name,"b_nand");
#endif  
  a.bind(l_b_nand);
  info.label = &l_b_nand;
  full_handle_info(info,FULL_BEGIN);
  a.mov(al,byte_ptr(nbp));
  a.not_(al);
  a.inc(nbp);
  a.mov(dl,byte_ptr(nbp));
  a.not_(dl);
  a.and_(al,dl);
  a.mov(byte_ptr(nbp),al);
#ifdef PROTECT_X64
  a.pushf();
  a.sub(nbp,8);
  a.pop(qword_ptr(nbp));
#else
  a.pushf();
  a.sub(nbp,4);
  a.pop(dword_ptr(nbp));
#endif
  a.jmp(l_check_stack);
  full_handle_info(info,FULL_END);
  return info;
}

handle_info VMHandle::w_nand() //4byte to 6byte
{
  handle_info info;
#ifdef DEBUG
  strcpy(info.handle_name,"w_nand");
#endif
  a.bind(l_w_nand);
  info.label = &l_w_nand;
  full_handle_info(info,FULL_BEGIN);
  a.mov(ax,word_ptr(nbp));
  a.not_(ax);
  a.add(nbp,2);
  a.mov(dx,word_ptr(nbp));
  a.not_(dx);
  a.and_(ax,dx);
  a.mov(word_ptr(nbp),ax);
#ifdef PROTECT_X64
  a.pushf();
  a.sub(nbp,8);
  a.pop(qword_ptr(nbp));
#else
  a.pushf();
  a.sub(nbp,4);
  a.pop(dword_ptr(nbp));
#endif
  a.jmp(l_check_stack);
  full_handle_info(info,FULL_END);
  return info;
}

handle_info VMHandle::d_nand() //4 byte to 8 byte
{
  handle_info info;
#ifdef DEBUG
  strcpy(info.handle_name,"d_nand");
#endif  
  a.bind(l_d_nand);
  info.label = &l_d_nand;
  full_handle_info(info,FULL_BEGIN);
  a.mov(eax,dword_ptr(nbp));
  a.not_(eax);
  a.add(nbp,4);
  a.mov(edx,dword_ptr(nbp));
  a.not_(edx);
  a.and_(eax,edx);
  a.mov(dword_ptr(nbp),eax);
#ifdef PROTECT_X64
  a.pushf();
  a.sub(ebp,8);
  a.pop(qword_ptr(nbp));
#else
  a.pushf();
  a.sub(nbp,4);
  a.pop(dword_ptr(nbp));
#endif
  a.jmp(l_check_stack);
  full_handle_info(info,FULL_END);
  return info;
}

handle_info VMHandle::q_nand()
{
  handle_info info;
#ifdef DEBUG
  strcpy(info.handle_name,"q_nand");
#endif  
  a.bind(l_q_nand);
  info.label = &l_q_nand;
  full_handle_info(info,FULL_BEGIN);
  a.mov(nax,qword_ptr(nbp));
  a.not_(nax);
  a.sub(nbp,8);
  a.mov(ndx,qword_ptr(nbp));
  a.not_(ndx);
  a.and_(nax,ndx);
  a.mov(qword_ptr(nbp),nax);
#ifdef PROTECT_X64
  a.pushf();
  a.sub(nbp,8);
  a.pop(qword_ptr(nbp));
#else
  a.pushf();
  a.sub(nbp,4);
  a.pop(dword_ptr(nbp));
#endif
  a.jmp(l_check_stack);
  full_handle_info(info,FULL_END);
  return info;
}

handle_info VMHandle::set_pc()
{
  handle_info info;
#ifdef DEBUG
  strcpy(info.handle_name,"set_pc");
#endif
  a.bind(l_set_pc);
  info.label = &l_set_pc;
  full_handle_info(info,FULL_BEGIN);
#ifdef PROTECT_X64
  a.mov(nax,qword_ptr(nbp));
  a.mov(nsi,nax);
  a.add(nbp,8);
#else
  a.mov(nax,dword_ptr(nbp));
  a.mov(nsi,nax);
  a.add(nbp,4);
#endif
  
  full_handle_info(info,FULL_END);
  
  return info;
}


handle_info VMHandle::ret()
{
    handle_info info;
#ifdef DEBUG
  strcpy(info.handle_name,"ret");
#endif    
    a.bind(l_ret);
    info.label = &l_ret;
    full_handle_info(info,FULL_BEGIN);
    a.mov(nsp,nbp);

  int register_count = 0;

  
#ifdef PROTECT_X64
  register_store_out.register_array[register_count++] = T_R15;
  register_store_out.register_array[register_count++] = T_R14;
  register_store_out.register_array[register_count++] = T_R13;
  register_store_out.register_array[register_count++] = T_R12;
  register_store_out.register_array[register_count++] = T_R11;
  register_store_out.register_array[register_count++] = T_R10;
  register_store_out.register_array[register_count++] = T_R9;
  register_store_out.register_array[register_count++] = T_R8;
#endif
  register_store_out.register_array[register_count++] = T_NDI ;
  register_store_out.register_array[register_count++] = T_NSI ;
  register_store_out.register_array[register_count++] = T_NBP ;
  register_store_out.register_array[register_count++] = T_NSP ;
  register_store_out.register_array[register_count++] = T_NBX ;
  register_store_out.register_array[register_count++] = T_NDX ;
  register_store_out.register_array[register_count++] = T_NCX ;
  register_store_out.register_array[register_count++] = T_NAX ;
  upset<long>(register_store_out.register_array,register_count);

  register_store_out.register_count = register_count;
  /*
  for (int i = 0; i < register_count; ++i)
  {
    switch (register_store_out.register_array[i])
    {
    case T_NAX:
      a.pop(nax);
      break;
    case T_NBX:
      a.pop(nbx);
      break;
    case T_NCX:
      a.pop(ncx);
      break;
    case T_NDX:
      a.pop(ndx);
      break;
    case T_NSP:
        a.pop(nsp);
      break;
    case T_NBP:
      a.pop(nbp);
      break;
    case T_NSI:
      a.pop(nsi);
      break;
    case T_NDI:
      a.pop(ndi);
      break;
    case T_EFLAG:
#ifndef PROTECT_X64
      a.popfd();
#else
      a.popfq();
#endif
      break;
#ifdef PROTECT_X64
    case T_R8:
      a.pop(r8);
      break;
    case T_R9:
      a.pop(r9);
      break;
    case T_R10:
      a.pop(r10);
      break;
    case T_R11:
      a.pop(r11);
      break;
    case T_R12:
      a.pop(r12);
      break;
    case T_R13:
      a.pop(r13);
      break;
    case T_R14:
      a.pop(r14);
      break;
    case T_R15:
      a.pop(r15);
      break;
#endif
    }    
    }*/
  
#ifndef PROTECT_X64
    a.popad();
#else
    a.pop(r15);
    a.pop(r14);
    a.pop(r13);
    a.pop(r12);
    a.pop(r11);
    a.pop(r10);
    a.pop(r9);
    a.pop(r8);
    a.pop(ndi);
    a.pop(nsi);
    a.pop(nsp);
    a.pop(nbp);
    a.pop(nbx);
    a.pop(ncx);
    a.pop(ndx);
    a.pop(nax);
#endif
    a.popf();
  
    a.ret();
    full_handle_info(info,FULL_END);
    return info;
}

handle_info VMHandle::push_stack_top_base()
{
  handle_info info;
#ifdef DEBUG
  strcpy(info.handle_name,"push_stack_top_base");
#endif  
  a.bind(l_push_stack_top_base);
  info.label = &l_push_stack_top_base;
  full_handle_info(info,FULL_BEGIN);
  
  a.mov(nax,nbp);
#ifdef PROTECT_X64
  a.sub(nbp,8);
  a.mov(qword_ptr(nbp),nax);
#else
  a.sub(nbp,4);
  a.mov(dword_ptr(nbp),nax);
#endif
  a.jmp(l_check_stack);
  full_handle_info(info,FULL_END);
  return info;
}

handle_info VMHandle::in()
{
  handle_info info;
#ifdef DEBUG
  strcpy(info.handle_name,"in");
#endif
  a.bind(l_in);
  info.label = &l_in;
  full_handle_info(info,FULL_BEGIN);

  a.jmp(l_check_stack);
  full_handle_info(info,FULL_END);
  return info;
}

handle_info VMHandle::rdtsc()
{
  handle_info info;
#ifdef DEBUG
  strcpy(info.handle_name,"rdtsc");
#endif  
  a.bind(l_rdtsc);
  info.label = &l_rdtsc;
  full_handle_info(info,FULL_BEGIN);
  a.rdtsc();

#ifdef PROTECT_X64
  a.sub(nbp,8*2);
  a.mov(qword_ptr(nbp),ndx);
  a.mov(qword_ptr(nbp,8),nax);
#else
  a.sub(nbp,4*2);
  a.mov(dword_ptr(nbp),ndx);
  a.mov(dword_ptr(nbp,4),nax);
#endif
  a.jmp(l_check_stack);
  full_handle_info(info,FULL_END);
  return info;
}

handle_info VMHandle::cpuid()
{
  handle_info info;
#ifdef DEBUG
  strcpy(info.handle_name,"cpuid");
#endif  
  a.bind(l_cpuid);
  info.label = &l_cpuid;
  full_handle_info(info,FULL_BEGIN);
  a.cpuid();

#ifdef PROTECT_X64
  a.sub(nbp,4*8);
  a.mov(qword_ptr(nbp,8*3),nax);
  a.mov(qword_ptr(nbp,8*2),nbx);
  a.mov(qword_ptr(nbp,8),ncx);
  a.mov(qword_ptr(nbp),ndx);
#else
  a.sub(nbp,4*4);
  a.mov(dword_ptr(nbp,4*3),nax);
  a.mov(dword_ptr(nbp,4*2),nbx);
  a.mov(dword_ptr(nbp,4),ncx);
  a.mov(dword_ptr(nbp),ndx);
#endif
  a.jmp(l_check_stack);
  full_handle_info(info,FULL_END);
  return info;
}

handle_info VMHandle::check_stack()
{
  handle_info info;
#ifdef DEBUG
  strcpy(info.handle_name,"check_stack");
#endif  
  a.bind(l_check_stack);
  info.label = &l_check_stack;
  //full_handle_info(info,FULL_BEGIN);  // 需要手动计算字节
  unsigned char * code = a.getCode();
  info.size = a.getCodeSize();
  info.buf = &code[a.getCodeSize()];
  info.offset = a.getOffset();
     
  a.lea(nax,ptr(ndi,0x50));
  a.cmp(nbp,nax);
  a.ja(l_dispatch);
  a.mov(ndx,nsp);
  a.lea(ncx,ptr(ndi,0x40));
  a.sub(ncx,ndx);
  
  a.jmp(l_dispatch);
  //full_handle_info(info,FULL_END);
  info.size = a.getCodeSize()-info.size;
  return info;
}

handle_info VMHandle::b_read_mem()
{
  handle_info info;
#ifdef DEBUG
  strcpy(info.handle_name,"b_read_mem");
#endif  
  a.bind(l_b_read_mem);
  info.label = &l_b_read_mem;
  full_handle_info(info,FULL_BEGIN);
#ifndef PROTECT_X64
  a.mov(nax,dword_ptr(nbp));
  a.add(nbp,3);
#else
  a.mov(nax,qword_ptr(nbp));
  a.add(nbp,7);
#endif
  a.mov(al,byte_ptr(nax));
  a.mov(byte_ptr(nbp),al);
  a.jmp(l_check_stack);
  full_handle_info(info,FULL_END);
  return info;
}

handle_info VMHandle::w_read_mem()
{
    handle_info info;
#ifdef DEBUG
  strcpy(info.handle_name,"w_read_mem");
#endif    
  a.bind(l_w_read_mem);
  info.label = &l_w_read_mem;
  full_handle_info(info,FULL_BEGIN);
#ifndef PROTECT_X64
  a.mov(nax,dword_ptr(nbp));
  a.add(nbp,2);
#else
  a.mov(nax,qword_ptr(nbp));
  a.add(nbp,6);
#endif
  a.mov(ax,word_ptr(nax));
  a.mov(word_ptr(nbp),ax);
  a.jmp(l_check_stack);
  full_handle_info(info,FULL_END);
  return info;
}

handle_info VMHandle::d_read_mem()
{
  handle_info info;
#ifdef DEBUG
  strcpy(info.handle_name,"d_read_mem");
#endif  
  a.bind(l_d_read_mem);
  info.label = &l_d_read_mem;
  full_handle_info(info,FULL_BEGIN);
#ifndef PROTECT_X64
  a.mov(nax,dword_ptr(nbp));
#else
  a.mov(nax,qword_ptr(nbp));
  a.add(nbp,4);
#endif
  a.mov(eax,dword_ptr(nax));
  a.mov(dword_ptr(nbp),eax);
  a.jmp(l_check_stack);
  full_handle_info(info,FULL_END);
  return info;
}

handle_info VMHandle::q_read_mem()
{
    handle_info info;
#ifdef DEBUG
  strcpy(info.handle_name,"q_read_mem");
#endif    
  a.bind(l_q_read_mem);
  info.label = &l_q_read_mem;
  full_handle_info(info,FULL_BEGIN);
  a.mov(nax,qword_ptr(nbp));
  a.mov(nax,qword_ptr(nax));
  a.mov(qword_ptr(nbp),nax);
  a.jmp(l_check_stack);
  full_handle_info(info,FULL_END);
  return info;
}

handle_info VMHandle::b_write_mem()
{
  handle_info info;
#ifdef DEBUG
  strcpy(info.handle_name,"b_write_mem");
#endif  
  a.bind(l_b_write_mem);
  info.label = &l_b_write_mem;
  full_handle_info(info,FULL_BEGIN);
#ifndef PROTECT_X64
  a.mov(nax,dword_ptr(nbp));
  a.mov(dl,byte_ptr(nax,4));
  a.add(nbp,5);
#else
  a.mov(nax,qword_ptr(nbp));
  a.mov(dl,byte_ptr(nbp,8));
  a.add(nbp,9);
#endif
  a.mov(byte_ptr(nax),dl);
  a.jmp(l_check_stack);
  full_handle_info(info,FULL_END);
  return info;
}

handle_info VMHandle::w_write_mem()
{
  handle_info info;
#ifdef DEBUG
  strcpy(info.handle_name,"w_write_mem");
#endif  
  a.bind(l_w_write_mem);
  info.label = &l_w_write_mem;
  full_handle_info(info,FULL_BEGIN);
#ifndef PROTECT_X64
  a.mov(nax,dword_ptr(nbp));
  a.mov(dx,word_ptr(nax,4));
  a.add(nbp,6);
#else
  a.mov(nax,qword_ptr(nbp));
  a.mov(dx,word_ptr(nbp,8));
  a.add(nbp,10);
#endif
  a.mov(byte_ptr(nax),dx);
  a.jmp(l_check_stack);
  full_handle_info(info,FULL_END);
  return info;
}

handle_info VMHandle::d_write_mem()
{
  handle_info info;
#ifdef DEBUG
  strcpy(info.handle_name,"d_write_mem");
#endif  
  a.bind(l_d_write_mem);
  info.label = &l_d_write_mem;
  full_handle_info(info,FULL_BEGIN);
#ifndef PROTECT_X64
  a.mov(nax,dword_ptr(nbp));
  a.mov(ndx,dword_ptr(nax,4));
  a.add(nbp,8);
#else
  a.mov(nax,qword_ptr(nbp));
  a.mov(ndx,dword_ptr(nbp,8));
  a.add(nbp,12);
#endif
  a.mov(dword_ptr(nax),ndx);
  a.jmp(l_check_stack);
  full_handle_info(info,FULL_END);
  return info;
}

handle_info VMHandle::q_write_mem()
{
  handle_info info;
#ifdef DEBUG
  strcpy(info.handle_name,"q_write_mem");
#endif  
  a.bind(l_q_write_mem);
  info.label = &l_q_write_mem;
  full_handle_info(info,FULL_BEGIN);

  a.mov(nax,qword_ptr(nbp));
  a.mov(ndx,qword_ptr(nbp,8));
  a.add(nbp,16);

  a.mov(qword_ptr(nax),ndx);
  a.jmp(l_check_stack);
  full_handle_info(info,FULL_END);
  return info;
}

handle_info VMHandle::b_push_imm_sx()
{
  handle_info info;
#ifdef DEBUG
  strcpy(info.handle_name,"b_push_imm_sx");
#endif  
  a.bind(l_b_push_imm_sx);
  info.label = &l_b_push_imm_sx;
  full_handle_info(info,FULL_BEGIN);
  read_pc_byte(info);
  a.movsx(nax,ax);
#ifdef PROTECT_X64
  a.sub(nbp,8);
  a.mov(qword_ptr(nbp),nax);
#else
  a.sub(nbp,4);
  a.mov(dword_ptr(nbp),nax);
#endif
  a.jmp(l_check_stack);
  full_handle_info(info,FULL_END);
  return info;
}

handle_info VMHandle::w_push_imm_sx()
{
  handle_info info;
#ifdef DEBUG
  strcpy(info.handle_name,"w_push_imm_sx");
#endif  
  a.bind(l_w_push_imm_sx);
  info.label = &l_w_push_imm_sx;
  full_handle_info(info,FULL_BEGIN);
  read_pc_word(info);
  a.movsx(nax,ax);
#ifdef PROTECT_X64
  a.sub(nbp,8);
  a.mov(qword_ptr(nbp),nax);
#else
  a.sub(nbp,4);
  a.mov(dword_ptr(nbp),nax);
#endif
  a.jmp(l_check_stack);
  full_handle_info(info,FULL_END);
  return info;
}

handle_info VMHandle::d_push_imm_sx()
{
  handle_info info;
#ifdef DEBUG
  strcpy(info.handle_name,"d_push_imm_sx");
#endif  
  a.bind(l_d_push_imm_sx);
  info.label = &l_d_push_imm_sx;
  full_handle_info(info,FULL_BEGIN);
  read_pc_dword(info);
  //a.movsx(nax,eax);
#ifdef PROTECT_X64
  a.and_(nax,0xFFFFFFFF00000000);
  a.sub(nbp,8);
  a.mov(qword_ptr(nbp),nax);
#else
  a.sub(nbp,4);
  a.mov(dword_ptr(nbp),nax);
#endif
  a.jmp(l_check_stack);
  full_handle_info(info,FULL_END);
  return info;
}

handle_info VMHandle::b_push_imm_zx()
{
  handle_info info;
#ifdef DEBUG
  strcpy(info.handle_name,"b_push_imm_zx");
#endif  
  a.bind(l_b_push_imm_zx);
  info.label = &l_b_push_imm_zx;
  full_handle_info(info,FULL_BEGIN);
  read_pc_byte(info);
  a.movzx(nax,ax);
#ifdef PROTECT_X64
  a.sub(nbp,8);
  a.mov(qword_ptr(nbp),nax);
#else
  a.sub(nbp,4);
  a.mov(dword_ptr(nbp),nax);
#endif
  a.jmp(l_check_stack);
  full_handle_info(info,FULL_END);
  return info;
}

handle_info VMHandle::w_push_imm_zx()
{
  handle_info info;
#ifdef DEBUG
  strcpy(info.handle_name,"w_push_imm_zx");
#endif  
  a.bind(l_w_push_imm_zx);
  info.label = &l_w_push_imm_zx;
  full_handle_info(info,FULL_BEGIN);
  read_pc_word(info);
  a.movzx(nax,ax);
#ifdef PROTECT_X64
  a.sub(nbp,8);
  a.mov(qword_ptr(nbp),nax);
#else
  a.sub(nbp,4);
  a.mov(dword_ptr(nbp),nax);
#endif
  a.jmp(l_check_stack);
  full_handle_info(info,FULL_END);
  return info;
}

handle_info VMHandle::d_push_imm_zx()
{
  handle_info info;
#ifdef DEBUG
  strcpy(info.handle_name,"d_push_inmm_zx");
#endif  
  a.bind(l_d_push_imm_zx);
  info.label = &l_d_push_imm_zx;
  full_handle_info(info,FULL_BEGIN);
  read_pc_dword(info);
#ifdef PROTECT_X64
  a.and_(nax,0x00000000FFFFFFFF);  
  a.sub(nbp,8);
  a.mov(qword_ptr(nbp),nax);
#else
  a.sub(nbp,4);
  a.mov(dword_ptr(nbp),nax);
#endif
  a.jmp(l_check_stack);
  full_handle_info(info,FULL_END);
  return info;
}


handle_info VMHandle::b_add()
{
  handle_info info;
#ifdef DEBUG
  strcpy(info.handle_name,"b_add");
#endif  
  a.bind(l_b_add);
  info.label = &l_b_add;
  full_handle_info(info,FULL_BEGIN);
  a.mov(al,byte_ptr(nbp));
  a.add(byte_ptr(nbp,1),al);
  a.pushf();
#ifdef PROTECT_X64
  a.sub(nbp,7);
  a.pop(qword_ptr(nbp));
#else
  a.sub(nbp,3);
  a.pop(dword_ptr(nbp));
#endif
  a.jmp(l_check_stack);
  full_handle_info(info,FULL_END);
  return info;
}

handle_info VMHandle::w_add()
{
  handle_info info;
#ifdef DEBUG
  strcpy(info.handle_name,"w_add");
#endif  
  a.bind(l_w_add);
  info.label = &l_w_add;
  full_handle_info(info,FULL_BEGIN);
  a.mov(ax,word_ptr(nbp));
  a.add(word_ptr(nbp,2),ax);
  a.pushf();
#ifdef PROTECT_X64
  a.sub(nbp,6);
  a.pop(qword_ptr(nbp));
#else
  a.sub(nbp,2);
  a.pop(dword_ptr(nbp));
#endif
  a.jmp(l_check_stack);
  full_handle_info(info,FULL_END);
  return info;
}

handle_info VMHandle::d_add()
{
  handle_info info;
#ifdef DEBUG
  strcpy(info.handle_name,"d_add");
#endif  
  a.bind(l_d_add);
  info.label = &l_d_add;
  full_handle_info(info,FULL_BEGIN);
  a.mov(nax,dword_ptr(nbp));
  a.add(dword_ptr(nbp,4),nax);
  a.pushf();
#ifdef PROTECT_X64
  a.sub(nbp,4);
  a.pop(qword_ptr(nbp));
#else
  a.pop(dword_ptr(nbp));
#endif
  a.jmp(l_check_stack);
  full_handle_info(info,FULL_END);
  return info;
}

handle_info VMHandle::q_add()
{
  handle_info info;
#ifdef DEBUG
  strcpy(info.handle_name,"q_add");
#endif  
  a.bind(l_q_add);
  info.label = &l_q_add;
  full_handle_info(info,FULL_BEGIN);
  a.mov(nax,qword_ptr(nbp));
  a.add(qword_ptr(nbp,8),nax);
  a.pushf();

  a.pop(qword_ptr(nbp));

  a.jmp(l_check_stack);
  full_handle_info(info,FULL_END);
  return info;
}

handle_info VMHandle::pop_stack_top_base()
{
  handle_info info;
#ifdef DEBUG
  strcpy(info.handle_name,"pop_stack_top_base");
#endif  
  a.bind(l_pop_stack_top_base);
  info.label = &l_pop_stack_top_base;
  full_handle_info(info,FULL_BEGIN);
#ifdef PROTECT_X64
  a.mov(nbp,qword_ptr(nbp));
#else
  a.mov(nbp,dword_ptr(nbp));
#endif

  a.jmp(l_check_stack);
  full_handle_info(info,FULL_END);
  return info;
}

handle_info VMHandle::b_rol()
{
  handle_info info;
#ifdef DEBUG
  strcpy(info.handle_name,"b_rol");
#endif  
  a.bind(l_b_rol);
  info.label = &l_b_rol;
  full_handle_info(info,FULL_BEGIN);
  a.mov(cl,byte_ptr(nbp));
  a.inc(nbp);

  a.mov(al,byte_ptr(nbp));
  
  a.rol(al,cl);
  a.pushf();
#ifdef PROTECT_X64
  a.sub(nbp,8);
  a.pop(qword_ptr(nbp));
#else
  a.sub(nbp,4);
  a.pop(dword_ptr(nbp));
#endif
  a.jmp(l_check_stack);
  full_handle_info(info,FULL_END);
  return info;
}

handle_info VMHandle::w_rol()
{
  handle_info info;
#ifdef DEBUG
  strcpy(info.handle_name,"w_rol");
#endif  
  a.bind(l_w_rol);
  info.label = &l_w_rol;
  full_handle_info(info,FULL_BEGIN);
  a.mov(cl,byte_ptr(nbp));
  a.inc(nbp);
  a.mov(ax,word_ptr(nbp));
  a.rol(ax,cl);
  a.pushf();
#ifdef PROTECT_X64
  a.sub(nbp,8);
  a.pop(qword_ptr(nbp));
#else
  a.sub(nbp,4);
  a.pop(dword_ptr(nbp));
#endif
  a.jmp(l_check_stack);
  full_handle_info(info,FULL_END);
  return info;
}

handle_info VMHandle::d_rol()
{
  handle_info info;
#ifdef DEBUG
  strcpy(info.handle_name,"d_rol");
#endif  
  a.bind(l_d_rol);
  info.label = &l_d_rol;
  full_handle_info(info,FULL_BEGIN);
  a.mov(cl,byte_ptr(nbp));
  a.inc(nbp);
  a.mov(eax,dword_ptr(nbp));
  a.rol(eax,cl);
  a.pushf();
#ifdef PROTECT_X64
  a.sub(nbp,8);
  a.pop(qword_ptr(nbp));
#else
  a.sub(nbp,4);
  a.pop(dword_ptr(nbp));
#endif
  a.jmp(l_check_stack);
  full_handle_info(info,FULL_END);
  return info;
}

handle_info VMHandle::q_rol()
{
  handle_info info;
#ifdef DEBUG
  strcpy(info.handle_name,"q_rol");
#endif  
  a.bind(l_q_rol);
  info.label = &l_q_rol;
  full_handle_info(info,FULL_BEGIN);
  a.mov(cl,byte_ptr(nbp));
  a.inc(nbp);
  a.mov(nax,qword_ptr(nbp));
  a.rol(nax,cl);
  a.pushf();
#ifdef PROTECT_X64
  a.sub(nbp,8);
  a.pop(qword_ptr(nbp));
#else
  a.sub(nbp,4);
  a.pop(dword_ptr(nbp));
#endif
  a.jmp(l_check_stack);
  full_handle_info(info,FULL_END);
  return info;
}


 
handle_info VMHandle::b_ror()
{
  handle_info info;
#ifdef DEBUG
  strcpy(info.handle_name,"b_ror");
#endif  
  a.bind(l_b_ror);
  info.label = &l_b_ror;
  full_handle_info(info,FULL_BEGIN);
  a.mov(cl,byte_ptr(nbp));
  a.inc(nbp);

  a.mov(al,byte_ptr(nbp));
  
  a.ror(al,cl);
  a.pushf();
#ifdef PROTECT_X64
  a.sub(nbp,8);
  a.pop(qword_ptr(nbp));
#else
  a.sub(nbp,4);
  a.pop(dword_ptr(nbp));
#endif
  a.jmp(l_check_stack);
  full_handle_info(info,FULL_END);
  return info;
}

handle_info VMHandle::w_ror()
{
  handle_info info;
#ifdef DEBUG
  strcpy(info.handle_name,"w_ror");
#endif  
  a.bind(l_w_ror);
  info.label = &l_w_ror;
  full_handle_info(info,FULL_BEGIN);
  a.mov(cl,byte_ptr(nbp));
  a.inc(nbp);
  a.mov(ax,word_ptr(nbp));
  a.ror(ax,cl);
  a.pushf();
#ifdef PROTECT_X64
  a.sub(nbp,8);
  a.pop(qword_ptr(nbp));
#else
  a.sub(nbp,4);
  a.pop(dword_ptr(nbp));
#endif
  a.jmp(l_check_stack);
  full_handle_info(info,FULL_END);
  return info;
}

handle_info VMHandle::d_ror()
{
  handle_info info;
#ifdef DEBUG
  strcpy(info.handle_name,"d_ror");
#endif  
  a.bind(l_d_ror);
  info.label = &l_d_ror;
  full_handle_info(info,FULL_BEGIN);
  a.mov(cl,byte_ptr(nbp));
  a.inc(nbp);
  a.mov(eax,dword_ptr(nbp));
  a.ror(eax,cl);
  a.pushf();
#ifdef PROTECT_X64
  a.sub(nbp,8);
  a.pop(qword_ptr(nbp));
#else
  a.sub(nbp,4);
  a.pop(dword_ptr(nbp));
#endif
  a.jmp(l_check_stack);
  full_handle_info(info,FULL_END);
  return info;
}

handle_info VMHandle::q_ror()
{
  handle_info info;
#ifdef DEBUG
  strcpy(info.handle_name,"q_ror");
#endif  
  a.bind(l_q_ror);
  info.label = &l_q_ror;
  full_handle_info(info,FULL_BEGIN);
  a.mov(cl,byte_ptr(nbp));
  a.inc(nbp);
  a.mov(nax,qword_ptr(nbp));
  a.ror(nax,cl);
  a.pushf();
#ifdef PROTECT_X64
  a.sub(nbp,8);
  a.pop(qword_ptr(nbp));
#else
  a.sub(nbp,4);
  a.pop(dword_ptr(nbp));
#endif
  a.jmp(l_check_stack);
  full_handle_info(info,FULL_END);
  return info;
}
