/*
 *
 *   Copyright (C) Mon Jul  1 17:03:59 2013 XiaoWei
 *
 *                       handsomexiaowei@gmail.com
 *
 *
 */


#include <EquivalenReplacement.hpp>
#include <AsmJit.h>
#include <WProtectConfig.h>

using namespace AsmJit;

EquivalenReplacement::EquivalenReplacement(  )
{
  
}

EquivalenReplacement::~EquivalenReplacement()
{
  
}

#define T_TMP_REGISTER1 T_IMM
#define T_TMP_REGISTER2 T_MEM

GPReg & EquivalenReplacement::get_register( pVOperand o1 )
{
  if (o1.is_reg(  ))
  {
    switch( o1._reg.base )
    {
    case T_NAX:
      return nax;
    case T_NBX:
      return nbx;
    case T_NCX:
      return ncx;
    case T_NDX:
      return ndx;
    case T_NSP:
      return nsp;
    case T_NBP:
      return nbp;
    case T_NSI:
      return nsi;
    case T_NDI:
      return ndi;
    case T_AX:
      return ax;
    case T_BX:
      return bx;
    case T_CX:
      return cx;
    case T_DX:
      return dx;
    case T_SI:
      return si;
    case T_DI:
      return di;
    case T_SP:
      return sp;
    case T_BP:
      return bp;
    case T_AL:
      return al;
    case T_BH:
      return bh;
    case T_CL:
      return cl;
    case T_CH:
      return ch;
    case T_DL:
      return dl;
    case T_AH:
      return ah;
    case T_BL:
      return dl;
    case T_DH:
      return dh;
    }
  }
  throw;
}

GPReg & EquivalenReplacement::get_register( const ud_type & o1 )
{
  switch ( o1 )
  {
  case UD_R_RAX:
    return nax;
  case UD_R_RBX:
    return nbx;
  case UD_R_RCX:
    return ncx;
  case UD_R_RDX:
    return ndx;
  case UD_R_RSP:
    return nsp;
  case UD_R_RBP:
    return nbp;
  case UD_R_RSI:
    return nsi;
  case UD_R_RDI:
    return ndi;
  case UD_R_EAX:
    return eax;
  case UD_R_EBX:
    return ebx;
  case UD_R_EDX:
    return edx;
  case UD_R_ECX:
    return ecx;
  case UD_R_ESP:
    return esp;
  case UD_R_EBP:
    return ebp;
  case UD_R_ESI:
    return esi;
  case UD_R_EDI:
    return edi;
  case UD_R_AX:
    return ax;
  case UD_R_BX:
    return bx;
  case UD_R_CX:
    return cx;
  case UD_R_DX:
    return dx;
  case UD_R_SP:
    return sp;
  case UD_R_BP:
    return bp;
  case UD_R_SI:
    return si;
  case UD_R_DI:
    return di;
  case UD_NONE:
    return 0;
  }
}


long & EquivalenReplacement::get_register( const ud_type & o1 )
{
  switch ( o1 )
  {
  case UD_R_RAX:
    return T_NAX;
  case UD_R_RBX:
    return T_NBX;
  case UD_R_RCX:
    return T_NCX;
  case UD_R_RDX:
    return T_NDX;
  case UD_R_RSP:
    return T_NSP;
  case UD_R_RBP:
    return T_NBP;
  case UD_R_RSI:
    return T_NSI;
  case UD_R_RDI:
    return T_NDI;
  case UD_R_EAX:
    return T_EAX;
  case UD_R_EBX:
    return T_EBX;
  case UD_R_EDX:
    return T_EDX;
  case UD_R_ECX:
    return T_ECX;
  case UD_R_ESP:
    return T_ESP;
  case UD_R_EBP:
    return T_EBP;
  case UD_R_ESI:
    return T_ESI;
  case UD_R_EDI:
    return T_EDI;
  case UD_R_AX:
    return T_AX;
  case UD_R_BX:
    return T_BX;
  case UD_R_CX:
    return T_CX;
  case UD_R_DX:
    return T_DX;
  case UD_R_SP:
    return T_SP;
  case UD_R_BP:
    return T_BP;
  case UD_R_SI:
    return T_SI;
  case UD_R_DI:
    return T_DI;
  }
  throw;
}

GPReg & EquivalenReplacement::get_rand_register(  )
{
  GPReg r_n = {
  nax,nbx,ncx,ndx,nbp,nsi,ndi
  };
  return r_n[rand(  )%7];
}

long EquivalenReplacement::get_register_diff( long _register )
{
  for (int i = 0; i < 30; ++i)
  {
    if (register_store[ i ] == _register)
    {
      return nsp_diff - (i+1)*4;
    }
  }
  throw;
}
  
void EquivalenReplacement::get_mem( const ud_operand & o  )
{
  GPReg r = get_rand_register(  );
  if (o.base != UD_NONE)
  {
    long _register_base = get_register( o->base );
  }
}

void EquivalenReplacement::push(pVOperand o1 )
{
  if (o1->is_reg(  ))
  {
     a.push( get_register( o1 ) );
     register_store[ nsp_diff ] = o1->_reg.base;

     nsp_diff += o1->_reg.size;

  }else if (o1->is_mem(  ))
  {
    long index = o1->_mem.index;
    long base = o1->_mem.base;
    long scale = o1->_mem.scale;
    long lval = o1->_mem.lval;
    register_store[ nsp_diff ] = T_TMP_MEM;
  }else if ( o1->is_imm(  ) )
  {
    long value = o1->_imm.value;
    a.push( value );
    register_store[ nsp_diff ] = T_TMP_IMM;
  }
}

void EquivalenReplacement::pushad()
{
  a.push( nax  );
  a.push( nbx );
  a.push( ncx );
  a.push( ndx );
  a.push( nsp );
  a.push( nbp );
  a.push( nsi );
  a.push( ndi );
}

void EquivalenReplacement::pushfd(const Assembler & a  )
{
  a.pushf(  );
  register_store[ nsp_diff ] = T_EFLAG;
#ifdef PROTECT_X64
  nsp_diff += 8;
#else
  nsp_diff += 4;
#endif
}

pCodeBufferInfo EquivalenReplacement::BuildCode(pCodeBufferInfo code ,CodeAddressTable * address_table )
{
  Analysis analysis;
  analysis.disasm( pinfo );
  for (int i = 0; i < analysis.block_count; ++i)
  {
    pAssemblerTree nowtree = get_tree( i );
    for (std::vector <ud_t> ::iterator iter = nowtree->asmpiece.begin(  )
         iter != nowtree->asmpiece.end(  ) ; ++iter)
    {
      switch( iter->mnemonic )
      {
      case UD_Icmp:
        break;
      case UD_Itest:
        break;
      }
    }
    address_table.assign_address(  )
  }
}

