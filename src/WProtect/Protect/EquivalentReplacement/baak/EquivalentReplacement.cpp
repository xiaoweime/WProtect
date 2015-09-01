/*
 *
 *   Copyright (C) Mon Jul  1 17:03:59 2013 XiaoWei
 *
 *                       handsomexiaowei@gmail.com
 *
 *
 */


#include <EquivalentReplacement.hpp>
#include <AsmJit.h>
#include <WProtectConfig.h>

using namespace AsmJit;

EquivalentReplacement::EquivalentReplacement(  )
  :nsp_diff( 0 ),nsp_data_diff( 0 )
{
  /*
  for (int i = 0; i < 30*4; ++i)
  {
    register_store[ i ] = 0;
  }
  */
}

EquivalentReplacement::~EquivalentReplacement()
{
  
}

//#define T_TMP_REGISTER1 T_IMM
//#define T_TMP_REGISTER2 T_MEM

GPReg  EquivalentReplacement::get_register( pVOperand o1 ) 
{
  if (o1->is_reg(  ))
  {
    switch( o1->_reg.base )
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
  cout << "get_register error\r\n" << endl;
  throw;
}

GPReg EquivalentReplacement::get_register( const ud_type & o1 )
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
  }
  cout << "get_register error\r\n" <<endl;
  throw;
}


long EquivalentReplacement::get_v_register( const ud_type & o1 )
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
  cout << "get_v_register error\r\n" << endl;
  throw;
}

GPReg  EquivalentReplacement::get_rand_register(GPReg *r_n  ,int count)
{
  int n = rand(  )%count;
  GPReg r = r_n[n];
  bool start = false;
  for (int i = 0; i < count; ++i)
  {
    if (start)
    {
      r_n[ i-1 ] = r_n[ i ];
    }    
    if (i == n)
    {
      start = true;
    }

  }
  return r;
}

long EquivalentReplacement::get_register_diff( long _register )
{
  /*
  for (int i = 0; i < 30 * 4; ++i)
  {
    if (register_store[ i ] == _register)
    {
      return nsp_diff - (i+1)*4;
    }
    }*/
  int i = 0;
  for (std::vector<long>::iterator iter = register_store.begin(  ); iter != register_store.end(  ); ++iter)
  {
    if (*iter & _register)
    {
      if ( *iter & T_8H )
        return nsp_diff - i + 1;
      return nsp_diff - i;
    }
    i++;
  }
  cout << "get_register_diff error \r\n" << endl;
  throw;
}
  
GPReg EquivalentReplacement::get_mem( ud_operand  o ,GPReg * r,int & r_count )
{
  GPReg reg_base;
  GPReg reg_index;

  /*
  GPReg r_n[  ] = {
  nax,nbx,ncx,ndx,nbp,nsi,ndi
  };*/
  GPReg *r_n = r;
  //int reg_count = r_count;
  if (o.base != UD_NONE)
  {
    reg_base = get_rand_register( r_n , r_count-- );
    long r = get_v_register( o.base );
    long reg_diff = get_register_diff(r);
#ifndef PROTECT_X64
    a.mov(reg_base,dword_ptr(nsp,reg_diff));
#else
    a.mov( reg_base,qword_ptr( nsp,reg_diff ) );
#endif
  }
  if (o.index != UD_NONE )
  {
    reg_index = get_rand_register( r_n , r_count-- );
    long r = get_v_register( o.base );
    long reg_diff = get_register_diff( r );
#ifndef PROTECT_X64
    a.mov(reg_index,dword_ptr(nsp,reg_diff));
#else
    a.mov( reg_index,qword_ptr( nsp,reg_diff ) );
#endif   
    if (o.scale)
    {
      if (o.scale == 1)
      {
      
      } else if (o.scale == 2)
      {
        a.shl( reg_index,1 );
      } else if (o.scale == 4)
      {
        a.shl( reg_index,2 );
      } else if (o.scale == 8)
      {
        a.shl( reg_index,3 );
      }
    }
    if (o.base != UD_NONE)
    {
      a.add( reg_base,reg_index );
    } else {
      a.mov( reg_base,reg_index );
    }
  }
  if (o.lval.sdword && (o.base != UD_NONE  || o.index != UD_NONE ) ) 
  {
    a.add(reg_base,o.offset==8?o.lval.sbyte:o.lval.sdword);
  } else if (o.base == UD_NONE && o.lval.sdword )
  {
    a.mov( reg_base,o.offset==8?o.lval.sbyte:o.lval.sdword );  
  }
  if (o.base == UD_R_ESP)
  {
    a.add( reg_base,nsp_diff - nsp_data_diff );
  }
  if (o.index == UD_R_ESP)
  {
    a.add( reg_base,nsp_diff - nsp_data_diff );
  }
  return reg_base;
}

GPReg EquivalentReplacement::get_operand( ud_operand o ,GPReg *r , int & r_count )
{
  switch ( o.type )
  {
  case UD_OP_IMM:
    {
      GPReg reg = get_rand_register( r , r_count-- );
      a.mov( reg,o.size == 8?o.lval.sbyte:o.lval.sdword  );
      return reg;
    }
    break;
  case UD_OP_MEM:
    {
      return get_mem(o,r,r_count);
    }
    break;
  case UD_OP_REG:
    {
      GPReg reg = get_rand_register( r , r_count-- );
      long r = get_v_register(o.base);
      r = get_register_diff( r );
      int isX64 = 0;
#ifdef PROTECT_X64
      isX64 = 4;
#endif
      if (reg.isGPD(  ))
        a.mov( reg,dword_ptr( nsp,r + isX64 ) );
      else if (reg.isGPW(  ))
      {
        a.mov( reg,word_ptr( nsp,r + isX64) );
      } else if (reg.isGPBLo(  ))
      {
        a.mov( reg,byte_ptr( nsp,r + isX64) );
      } else if (reg.isGPBHi(  ))
      {
        a.mov( reg,byte_ptr( nsp,r+1+isX64 ) );
      } else if (reg.isGPQ(  ))
      {
        a.mov( reg,qword_ptr( nsp,r+isX64 ) );
      }
      if (o.base == UD_R_ESP)
      {
        a.add( reg,nsp_diff - nsp_data_diff );
      }
      return reg;
    }
    break;
  case UD_OP_JIMM:
    GPReg reg;
    return reg;
    break;
  }
  cout << "get_operand error\r\n" << endl;
  throw;
}

GPReg EquivalentReplacement::get_mem( pVOperand o,GPReg *r,int & r_count )
{
  GPReg reg_base;
  GPReg reg_index;

  /*
  GPReg r_n[  ] = {
  nax,nbx,ncx,ndx,nbp,nsi,ndi
  };*/
  GPReg *r_n = r;
  //int reg_count = r_count;
  if (o->_mem.base != 0)
  {
    reg_base = get_rand_register( r_n , r_count-- );
    long reg_diff = get_register_diff(o->_mem.base);
    
#ifndef PROTECT_X64
    a.mov(reg_base,dword_ptr(nsp,reg_diff));
#else
    a.mov( reg_base,qword_ptr( nsp,reg_diff ) );
#endif    
  }
  if (o->_mem.index != 0 )
  {
    reg_index = get_rand_register( r_n , r_count-- );
    long reg_diff = get_register_diff( o->_mem.index );
#ifndef PROTECT_X64
    a.mov(reg_index,dword_ptr(nsp,reg_diff));
#else
    a.mov( reg_index,qword_ptr( nsp,reg_diff ) );
#endif   
    if (o->_mem.scale)
    {
      if (o->_mem.scale == 1)
      {
      
      } else if (o->_mem.scale == 2)
      {
        a.shl( reg_index,1 );
      } else if (o->_mem.scale == 4)
      {
        a.shl( reg_index,2 );
      } else if (o->_mem.scale == 8)
      {
        a.shl( reg_index,3 );
      }
    }
    if (o->_mem.base != 0)
    {
      a.add( reg_base,reg_index );
    } else {
      a.mov ( reg_base,reg_index );
    }
  }
  if (o->_mem.lval && (o->_mem.base != 0||o->_mem.index != 0) )
  {
    a.add(reg_base,o->_mem.lval);
  } else if (o->_mem.lval)
  {
    a.mov( reg_base,o->_mem.lval );
  }
  if (o->_mem.base == T_NSP)
  {
    a.add(reg_base,(nsp_diff-nsp_data_diff) );
  }
  if (o->_mem.index == T_NSP)
  {
    a.add(reg_base,(nsp_diff-nsp_data_diff) );
  }  
  return reg_base;
}

long EquivalentReplacement::create_space( long size )
{
  a.lea( nsp,ptr( nsp,-size ) );
  nsp_diff += size;
  for (int i = 0; i < size; ++i)
  {
    register_store.push_back( 0 );
  }
  return nsp_diff;
}

GPReg EquivalentReplacement::get_operand( pVOperand o,GPReg *r,int & r_count )
{
  switch( o->_base.op )
  {
  case VOPERAND_IMM:
    {
        GPReg reg = get_rand_register( r , r_count-- );
        a.mov(reg,o->_imm.value);
        return reg;
    }
    
    break;
  case VOPERAND_MEM:
    {
      return get_mem( o,r,r_count );
    }
    break;
  case VOPERAND_REG:
    {
      GPReg reg = get_rand_register( r , r_count-- );
      long r = get_register_diff( o->_reg.base );
      int isX64 = 0;
#ifdef PROTECT_X64
      isX64 = 4;
#endif
      if (reg.isGPD(  ))
        a.mov( reg,dword_ptr( nsp,r + isX64 ) );
      else if (reg.isGPW(  ))
      {
        a.mov( reg,word_ptr( nsp,r + isX64) );
      } else if (reg.isGPBLo(  ))
      {
        a.mov( reg,byte_ptr( nsp,r + isX64) );
      } else if (reg.isGPBHi(  ))
      {
        a.mov( reg,byte_ptr( nsp,r+1+isX64 ) );
      } else if (reg.isGPQ(  ))
      {
        a.mov( reg,qword_ptr( nsp,r+isX64 ) );
      }
      if (o->_reg.base == T_NSP)
      {
        a.add( reg,nsp_diff - nsp_data_diff );
      }
      return reg;        
    }
    break;
  }
  throw;
}

void EquivalentReplacement::disable_register( pVOperand o1 )
{
  int i = 0;
  for (std::vector<long>::iterator iter = register_store.begin(  ); iter != register_store.end(  ); ++iter)
  {
    if (*iter & o1->_reg.base)
    {
      register_store[ i ] = 0;
    }
    i++;
  }
}

void EquivalentReplacement::push(pVOperand o1 )
{

  if (o1->is_reg(  ))
  {
     a.push( get_register( o1 ) );
     //     register_store[ nsp_diff ] = o1->_reg.base;
     register_store.push_back( o1->_reg.base );
     for (int i = 1; i < o1->_reg.size; ++i)
     {
       register_store.push_back( 0 );
     }
     nsp_diff += o1->_reg.size;
  }else if (o1->is_mem(  ))
  {
    long index = o1->_mem.index;
    long base = o1->_mem.base;
    long scale = o1->_mem.scale;
    long lval = o1->_mem.lval;
    //register_store[ nsp_diff ] = T_TMP_REGISTER1;
    
  }else if ( o1->is_imm(  ) )
  {
    long value = o1->_imm.value;
    a.push( value );
    //register_store[ nsp_diff ] = T_TMP_REGISTER2;
    register_store.push_back( T_TMP_REGISTER2 );
#ifdef PROTECT_X64
    //nsp_diff += 8;
    for (int i = 0; i < 7; ++i)
    {
      register_store.push_back( 0 );
    }
#else
    //nsp_diff += 4;
    for (int i = 0; i < 3; ++i)
    {
      register_store.push_back( 0 );
    }
#endif
  }    
}

void EquivalentReplacement::save_context(  )
{
  VReg vnax( T_NAX );
  VReg vnbx( T_NBX );
  VReg vncx( T_NCX );
  VReg vndx( T_NDX );
  VReg vnbp( T_NBP );
  VReg vnsi( T_NSI );
  VReg vndi( T_NDI );
  
  push( &vnax );
  push( &vnbx );
  push( &vncx );
  push( &vndx );
  push( &vndi );
  push( &vnsi );
  push( &vnbp );
}

void EquivalentReplacement::recover_context(  )
{
  //for (int i = 0; i < 30*4; i += 4)
  int i = 0;
  VReg vnax( T_NAX );
  VReg vnbx( T_NBX );
  VReg vncx( T_NCX );
  VReg vndx( T_NDX );
  VReg vnbp( T_NBP );
  VReg vnsi( T_NSI );
  VReg vndi( T_NDI );  
  for (std::vector<long>::iterator iter = register_store.begin(  );
       iter != register_store.end(  ); ++iter)
  {
    switch ( *iter )
    {
    case T_NAX:
      a.lea( nsp,ptr( nsp,i ) );
      pop( &vnax );
      disable_register( &vnax );
      break;
    case T_NBX:
      a.lea( nsp,ptr( nsp,i ) );
      pop( &vnbx );
      disable_register( &vnax );
      break;
    case T_NCX:
      a.lea( nsp,ptr( nsp,i ) );
      pop( &vncx );
      break;
    case T_NDX:
      a.lea( nsp,ptr( nsp,i ) );
      pop( &vndx );
      break;
    case T_NBP:
      a.lea( nsp,ptr( nsp,i ) );
      pop( &vnbp );
      break;
    case T_NSI:
      a.lea( nsp,ptr( nsp,i ) );
      pop( &vnsi );
      break;
    case T_NDI:
      a.lea( nsp,ptr( nsp,i ) );
      //pop( &ndi );
      break;
    }
    i++;
  }
}

void EquivalentReplacement::pushad()
{
  /*
  a.push( nax  );
  a.push( nbx );
  a.push( ncx );
  a.push( ndx );
  a.push( nsp );
  a.push( nbp );
  a.push( nsi );
  a.push( ndi );*/

  
  //push(static_cast<pVOperand>( &vreg( T_NAX )) );
}

void EquivalentReplacement::pop( pVOperand o1 )
{
  if (o1->is_reg(  ))
  {
     a.pop( get_register( o1 ) );
     register_store[ nsp_diff - o1->_reg.size ] = 0;
     for (int i = 0; i < o1->_reg.size; ++i)
     {
       register_store.erase( register_store.end(  ) );
     }
     nsp_diff -= o1->_reg.size;
  }else if (o1->is_mem(  ))
  {
    /*
    long index = o1->_mem.index;
    long base = o1->_mem.base;
    long scale = o1->_mem.scale;
    long lval = o1->_mem.lval;
    register_store[ nsp_diff ] = T_TMP_REGISTER1;
    switch ( o1->_mem.size )
    {
    case 1:
      {
        if (index != 0)
        {
          
        }
      }
      }*/
    GPReg t_reg[ 4 ][ 8 ] = {
        nax,nbx,ncx,ndx,nbp,nsi,ndi,ndi,
        eax,ebx,ecx,edx,ebp,esi,edi,edi,
        ax,bx,cx,dx,bp,si,di,di,
        cl,al,ah,bl,bh,ch,dl,dh
      };
    int count = 0;
    switch ( o1->_mem.size )
    {
    case 1:
      count = 8;
      a.pop(get_mem( o1,t_reg[ 3 ],count ));
      break;
    case 2:
      count = 7;
      a.pop(get_mem( o1,t_reg[ 2 ],count ));
      break;
    case 4:
      count = 7;
      a.pop(get_mem( o1,t_reg[ 1 ],count ));      
      break;
    case 8:
      count = 7;
      a.pop(get_mem( o1,t_reg[ 0 ],count ));      
      break;
    }
    nsp_diff -= o1->_mem.size;
    register_store[ nsp_diff ] = 0;

     for (int i = 0; i < o1->_mem.size; ++i)
     {
       register_store.erase( register_store.end(  ) );
     }    
  }else if ( o1->is_imm(  ) )
  {
    throw;
  }
}

void EquivalentReplacement::pop( ud_operand  ud_op )
{
  VOperand o = udop_to_vop( ud_op );
  pop( &o );
}

void EquivalentReplacement::push_value( pVOperand o ) //push到真实的堆栈
{
  push( o );
  switch ( o->_base.op )
  {
  case VOPERAND_IMM:
#ifdef PROTECT_X64
    a.pop( qword_ptr( nsp,nsp_diff - nsp_data_diff + 8 ) );
    nsp_data_diff += 8;
#else
    a.pop( dword_ptr( nsp,nsp_diff - nsp_data_diff + 4 ) );
    nsp_data_diff += 4;    
#endif
    break;
  case VOPERAND_MEM:
    {
      switch( o->_mem.size )
      {
      case 1:
        a.pop( byte_ptr(nsp , nsp_diff - nsp_data_diff + 1) );
        nsp_data_diff += 1;
        break;
      case 2:
        a.pop( word_ptr(nsp , nsp_diff - nsp_data_diff + 2) );
        nsp_data_diff += 2;
        break;
      case 4:
        a.pop( dword_ptr(nsp , nsp_diff - nsp_data_diff + 4) );
        nsp_data_diff += 4;
        break;
      case 8:
        a.pop( qword_ptr(nsp, nsp_diff - nsp_data_diff + 8) );
        nsp_data_diff += 8;
        break;
      }
    }
    break;
  case VOPERAND_REG:
    {
      switch( o->_reg.size )
      {
      case 1:
        a.pop( byte_ptr(nsp , nsp_diff - nsp_data_diff + 1) );
        nsp_data_diff += 1;
        break;
      case 2:
        a.pop( word_ptr(nsp , nsp_diff - nsp_data_diff + 2) );
        nsp_data_diff += 2;
        break;
      case 4:
        a.pop( dword_ptr(nsp , nsp_diff - nsp_data_diff + 4) );
        nsp_data_diff += 4;
        break;
      case 8:
        a.pop( qword_ptr(nsp , nsp_diff - nsp_data_diff + 8) );
        nsp_data_diff += 8;
        break;
      }
    }
    break;
  }
}

void EquivalentReplacement::pop_value( pVOperand o )
{
  switch ( o->_base.op )
  {
  case VOPERAND_IMM:
#ifdef PROTECT_X64
    a.push( qword_ptr( nsp,nsp_diff - nsp_data_diff + 8 ) );
    nsp_data_diff -= 8;
#else
    a.push( dword_ptr( nsp,nsp_diff - nsp_data_diff + 4 ) );
    nsp_data_diff -= 4;    
#endif
    break;
  case VOPERAND_MEM:
    {
      switch( o->_mem.size )
      {
      case 1:
        a.push( byte_ptr(nsp , nsp_diff - nsp_data_diff + 1) );
        nsp_data_diff -= 1;
        break;
      case 2:
        a.push( word_ptr(nsp , nsp_diff - nsp_data_diff + 2) );
        nsp_data_diff -= 2;
        break;
      case 4:
        a.push( dword_ptr(nsp , nsp_diff - nsp_data_diff + 4) );
        nsp_data_diff -= 4;
        break;
      case 8:
        a.push( qword_ptr(nsp, nsp_diff - nsp_data_diff + 8) );
        nsp_data_diff -= 8;
        break;
      }
    }
    break;
  case VOPERAND_REG:
    {
      switch( o->_reg.size )
      {
      case 1:
        a.push( byte_ptr(nsp , nsp_diff - nsp_data_diff + 1) );
        nsp_data_diff -= 1;
        break;
      case 2:
        a.push( word_ptr(nsp , nsp_diff - nsp_data_diff + 2) );
        nsp_data_diff -= 2;
        break;
      case 4:
        a.push( dword_ptr(nsp , nsp_diff - nsp_data_diff + 4) );
        nsp_data_diff -= 4;
        break;
      case 8:
        a.push( qword_ptr(nsp , nsp_diff - nsp_data_diff + 8) );
        nsp_data_diff -= 8;
        break;
      }
    }
    break;
  }
  pop ( o );
}

void EquivalentReplacement::pushf( )
{
  a.pushf(  );
  register_store[ nsp_diff ] = T_EFLAG;
#ifdef PROTECT_X64
  nsp_diff += 8;
#else
  nsp_diff += 4;
#endif
}

Label  EquivalentReplacement::get_label( long addr )
{
  for (std::vector<CLabel>::iterator iter =
         label_vec.begin(  ); iter != label_vec.end(  ); ++iter)
  {
    if (addr == iter->addr)
    {
      return iter->label;
    }
  }
  CLabel label;
  label.addr = addr;
  label.label = a.newLabel(  );
  //  a.bind( label.label );
  label_vec.push_back( label );
  return label.label;
  cout << "get_label error\r\n" << endl;
  throw;
}

bool EquivalentReplacement::check_label( long addr )
{
  for (std::vector<CLabel>::iterator iter =
         label_vec.begin(  ); iter != label_vec.end(  ); ++iter)
  {
    if (addr == iter->addr)
    {
      a.bind( iter->label );
      return true;
    }
  }
  return false;
}

VOperand EquivalentReplacement::udop_to_vop(const ud_operand & o)
{
  switch ( o.type )
  {
  case UD_OP_IMM:
    {
          VOperand vop;
    vop._base.op = VOPERAND_IMM;
    vop._imm.value = ( o.size == 8 ? o.lval.sbyte : o.lval.sdword   );
    return vop; 
    }
    //VImm vop( o.size == 8 ? o.lval.sbyte : o.lval.sdword );
    break;
  case UD_OP_REG:
    {
    VOperand vop;
    vop._base.op = VOPERAND_REG;
    vop._reg.base = get_v_register( o.base );
    if (vop.isGPD(  ))
    {
      vop._reg.size = 4;
    } else if (vop.isGPW(  ))
    {
      vop._reg.size = 2;
    } else if (vop.isGPB(  ))
    {
      vop._reg.size = 1;
    } else if (vop.isGPQ(  ))
    {
      vop._reg.size = 8;
    } 
    
    return vop;      
    }
    break;
  case UD_OP_MEM:
    {
      VOperand vop;
      vop._base.op = VOPERAND_MEM;
      if (o.base != UD_NONE)
      {
        vop._mem.base = get_v_register( o.base );
      }
      if (o.index != UD_NONE)
      {
        vop._mem.index = get_v_register( o.index );
      }
      vop._mem.scale = o.scale;
      vop._mem.lval = o.size == 8 ? o.lval.sbyte : o.lval.sdword;
      if (o.size == 8)
      {
        vop._mem.size = 1;
      } else if (o.size == 16)
      {
        vop._mem.size = 2;
      } else if (o.size == 32)
      {
        vop._mem.size = 4;
      }
      else 
        vop._mem.size = 8;
      return vop;
    }
    break;
  case UD_OP_JIMM:
    {
          VOperand vop;
    vop._base.op = VOPERAND_IMM;
    vop._imm.value = ( o.size == 8 ? o.lval.sbyte : o.lval.sdword   );
    return vop;
    }
  defualt:
    cout << "未知的操作数\r\n" << endl;
    VOperand vop;
    return vop;
    break;
  }
}

pCodeBufferInfo EquivalentReplacement::BuildCode(pCodeBufferInfo code ,CodeAddressTable * address_table )
{
  FileLogger logger(stderr);
  a.setLogger(&logger);
  Analysis analysis;
  analysis.disasm( code );
  create_space( 0x4 );
  //pushad(  );
  save_context(  );
  for (int i = 0; i < analysis.block_count; ++i)
  {
    pAssemblerTree nowtree = analysis.get_tree( i );
    for (std::vector <ud_t> ::iterator iter = nowtree->asmpiece.begin(  );
         iter != nowtree->asmpiece.end(  ) ; ++iter)
    {
#define o1 get_operand( iter->operand[ 0 ],reg1,count1 ) 
#define o2 get_operand( iter->operand[ 1 ],reg2,count2 ) 
#define o3 get_operand( iter->operand[ 2 ],reg3,count3 )

      GPReg t_reg[ 4 ][ 8 ] = {
        nax,nbx,ncx,ndx,nbp,nsi,ndi,ndi,
        eax,ebx,ecx,edx,ebp,esi,edi,edi,
        ax,bx,cx,dx,bp,si,di,di,
        cl,al,ah,bl,bh,ch,dl,dh
      };

      if ( !check_label( iter->insn_offset ) )
      {
        CLabel label;
        label.addr = iter->insn_offset;
        label.label = a.newLabel(  );
        a.bind( label.label );
        label_vec.push_back( label );
      }
      
      GPReg *reg1 = NULL;
      int count1 = 0;
      GPReg *reg2 = NULL;
      int count2 = 0;
      GPReg *reg3 = t_reg[ 3 ];
      int count3 = 1;
      switch (iter->operand[ 0 ].type)
      {
      case UD_OP_IMM:
        {
          switch ( iter->operand[ 0 ].size  )
          {
          case 8:
            reg1 = t_reg[ 3 ];
            count1 = 8;
            break;
          case 16:
            reg1 = t_reg[ 2 ];
            count1 = 7;
            break;
          case 32:
            reg1 = t_reg[ 1 ];
            count1 = 7;
            break;
          case 64:
            reg1 = t_reg[ 0 ];
            count1 = 7;
            break;
          }
        }
        break;
      case UD_OP_MEM:
        {
          switch ( iter->operand[ 0 ].size  )
          {
          case 8:
            reg1 = t_reg[ 3 ];
            count1 = 8;
            break;
          case 16:
            reg1 = t_reg[ 2 ];
            count1 = 7;
            break;
          case 32:
            reg1 = t_reg[ 1 ];
            count1 = 7;
            break;
          case 64:
            reg1 = t_reg[ 0 ];
            count1 = 7;
            break;
          }
          reg1 = t_reg[ 1 ];
          count1 = 7;          
        }
        break;
      case UD_OP_REG:
        {
          if (iter->operand[ 0 ].base == UD_R_AL ||
              iter->operand[ 0 ].base == UD_R_AH ||
              iter->operand[ 0 ].base == UD_R_DL ||
              iter->operand[ 0 ].base == UD_R_DH ||
              iter->operand[ 0 ].base == UD_R_CL ||
              iter->operand[ 0 ].base == UD_R_CH ||
              iter->operand[ 0 ].base == UD_R_DL ||
              iter->operand[ 0 ].base == UD_R_DH )
            {
              reg1 = t_reg[ 3 ];
              count1 = 8;
            } else  if ( iter->operand[ 0 ].base == UD_R_AX ||
              iter->operand[ 0 ].base == UD_R_BX ||
              iter->operand[ 0 ].base == UD_R_CX ||
              iter->operand[ 0 ].base == UD_R_DX ||
              iter->operand[ 0 ].base == UD_R_SP ||
              iter->operand[ 0 ].base == UD_R_BP ||
              iter->operand[ 0 ].base == UD_R_SI ||
              iter->operand[ 0 ].base == UD_R_DI )
            {
              reg1 = t_reg[ 2 ];
              count1 = 7;
            } else  if ( iter->operand[ 0 ].base == UD_R_EAX ||
              iter->operand[ 0 ].base == UD_R_EBX ||
              iter->operand[ 0 ].base == UD_R_ECX ||
              iter->operand[ 0 ].base == UD_R_EDX ||
              iter->operand[ 0 ].base == UD_R_ESP ||
              iter->operand[ 0 ].base == UD_R_EBP ||
              iter->operand[ 0 ].base == UD_R_ESI ||
              iter->operand[ 0 ].base == UD_R_EDI )
            {
              reg1 = t_reg[ 1 ];
              count1 = 7;
            } else  if ( iter->operand[ 0 ].base == UD_R_RAX ||
              iter->operand[ 0 ].base == UD_R_RBX ||
              iter->operand[ 0 ].base == UD_R_RCX ||
              iter->operand[ 0 ].base == UD_R_RDX ||
              iter->operand[ 0 ].base == UD_R_RSP ||
              iter->operand[ 0 ].base == UD_R_RBP ||
              iter->operand[ 0 ].base == UD_R_RSI ||
              iter->operand[ 0 ].base == UD_R_RDI )
            {
              reg1 = t_reg[ 0 ];
              count1 = 7;
            }
        }
        break;
      }


      switch (iter->operand[ 1 ].type)
      {
      case UD_OP_IMM:
        {
          switch ( iter->operand[ 1 ].size  )
          {
          case 8:
            reg2 = t_reg[ 3 ];
            count2 = 8;
            break;
          case 16:
            reg2 = t_reg[ 2 ];
            count2 = 7;
            break;
          case 32:
            reg2 = t_reg[ 1 ];
            count2 = 7;
            break;
          case 64:
            reg2 = t_reg[ 0 ];
            count2 = 7;
            break;
          }
        }
        break;
      case UD_OP_MEM:
        {
          switch ( iter->operand[ 0 ].size  )
          {
          case 8:
            reg2 = t_reg[ 3 ];
            count2 = 8;
            break;
          case 16:
            reg2 = t_reg[ 2 ];
            count2 = 7;
            break;
          case 32:
            reg2 = t_reg[ 1 ];
            count2 = 7;
            break;
          case 64:
            reg2 = t_reg[ 0 ];
            count2 = 7;
            break;
          }
          reg2 = t_reg[ 1 ];
          count2 = 7;          
        }
        break;
      case UD_OP_REG:
        {
          if (iter->operand[ 0 ].base == UD_R_AL ||
              iter->operand[ 0 ].base == UD_R_AH ||
              iter->operand[ 0 ].base == UD_R_DL ||
              iter->operand[ 0 ].base == UD_R_DH ||
              iter->operand[ 0 ].base == UD_R_CL ||
              iter->operand[ 0 ].base == UD_R_CH ||
              iter->operand[ 0 ].base == UD_R_DL ||
              iter->operand[ 0 ].base == UD_R_DH )
            {
              reg2 = t_reg[ 3 ];
              count2 = 8;
            } else  if ( iter->operand[ 0 ].base == UD_R_AX ||
              iter->operand[ 0 ].base == UD_R_BX ||
              iter->operand[ 0 ].base == UD_R_CX ||
              iter->operand[ 0 ].base == UD_R_DX ||
              iter->operand[ 0 ].base == UD_R_SP ||
              iter->operand[ 0 ].base == UD_R_BP ||
              iter->operand[ 0 ].base == UD_R_SI ||
              iter->operand[ 0 ].base == UD_R_DI )
            {
              reg2 = t_reg[ 2 ];
              count2 = 7;
            } else  if ( iter->operand[ 0 ].base == UD_R_EAX ||
              iter->operand[ 0 ].base == UD_R_EBX ||
              iter->operand[ 0 ].base == UD_R_ECX ||
              iter->operand[ 0 ].base == UD_R_EDX ||
              iter->operand[ 0 ].base == UD_R_ESP ||
              iter->operand[ 0 ].base == UD_R_EBP ||
              iter->operand[ 0 ].base == UD_R_ESI ||
              iter->operand[ 0 ].base == UD_R_EDI )
            {
              reg2 = t_reg[ 1 ];
              count2 = 7;
            } else  if ( iter->operand[ 0 ].base == UD_R_RAX ||
              iter->operand[ 0 ].base == UD_R_RBX ||
              iter->operand[ 0 ].base == UD_R_RCX ||
              iter->operand[ 0 ].base == UD_R_RDX ||
              iter->operand[ 0 ].base == UD_R_RSP ||
              iter->operand[ 0 ].base == UD_R_RBP ||
              iter->operand[ 0 ].base == UD_R_RSI ||
              iter->operand[ 0 ].base == UD_R_RDI )
            {
              reg2 = t_reg[ 0 ];
              count2 = 7;
            }
        }
        break;
      }
      VOperand vo1;
      if ( iter->operand[ 0 ].type != UD_NONE )
      vo1 = udop_to_vop(iter->operand[ 0 ]);
      
      VOperand vo2; 
      if ( iter->operand[ 1 ].type != UD_NONE )
      vo2 = udop_to_vop(iter->operand[ 1 ]);
      
      VOperand vo3;
      if ( iter->operand[ 2 ].type != UD_NONE )
      vo3 = udop_to_vop(iter->operand[ 2 ]);

      
      GPReg udo1 ;
      GPReg udo2 ;
      GPReg udo3 ;
      if (iter->operand[ 0 ].type != UD_NONE)
      {
        udo1 = o1;
      }
      if (iter->operand[ 1 ].type != UD_NONE)
      {
        udo2 = o2;
      }
      if (iter->operand[ 2 ].type != UD_NONE)
      {
        udo3 = o3;
      }
      switch( iter->mnemonic )
      {
      case UD_Ipush:
        push_value(&vo1);
        break;
      case UD_Icmp:
        a.cmp(o1,o2);
        break;
      case UD_Itest:
        a.test(o1,o2 );
        break;
      case UD_Ixor:
        a.xor_( o1,o2 );
        break;
      case UD_Ior:
        a.or_( o1,o2 );
        break;
      case UD_Iand:
        a.and_( o1,o2 );
        break;
      case UD_Imov:
        a.mov( udo1,udo2);
        //a.push( o2 );
        //        a.pop(  )
        break;
      case UD_Iret:
        break;
      case UD_Ijnz:
        {
          long addr = iter->pc;
          addr += iter->operand[ 0 ].size == 8? iter->operand[ 0 ].lval.sbyte : iter->operand[ 0 ].lval.sdword;
          if (analysis.check_address( addr ))
          {
            a.jnz( get_label( addr ) );
          }
          else
          {
            Label l;
            l = a.newLabel(  );
            a.jz( l );
            a.jmp( ( ( void* )addr ) );
            a.bind( l );
          }            
        }
        break;
      case UD_Ijz:
        {
          long addr = iter->pc;
          addr += iter->operand[ 0 ].size == 8? iter->operand[ 0 ].lval.sbyte : iter->operand[ 0 ].lval.sdword;
          if (analysis.check_address( addr ))
          {
            a.jz( get_label( addr ) );
          }
          else
          {
            Label l;
            l = a.newLabel(  );
            a.jnz( l );
            a.jmp( ( ( void* )addr ) );
            a.bind( l );
          }
        }        
        break;
      case UD_Ijb: //如果进位位被置位则跳转  = 1
        {
          long addr = iter->pc;
          addr += iter->operand[ 0 ].size == 8? iter->operand[ 0 ].lval.sbyte : iter->operand[ 0 ].lval.sdword;
          if (analysis.check_address( addr ))
          {
            a.jnae( get_label( addr ) );
          }
          else
          {
            Label l;
            l = a.newLabel(  );
            a.jae( l );
            a.jmp( ( ( void* )addr ) );
            a.bind( l );
          }
        }                
        break;
      case UD_Ijae:
        {
          long addr = iter->pc;
          addr += iter->operand[ 0 ].size == 8? iter->operand[ 0 ].lval.sbyte : iter->operand[ 0 ].lval.sdword;
          if (analysis.check_address( addr ))
          {
            a.jae( get_label( addr ) );
          }
          else
          {
            Label l;
            l = a.newLabel(  );
            a.jnae( l );
            a.jmp( ( ( void* )addr ) );
            a.bind( l );
          }
        }                
        break;
      case UD_Ijs: 
        {
          long addr = iter->pc;
          addr += iter->operand[ 0 ].size == 8? iter->operand[ 0 ].lval.sbyte : iter->operand[ 0 ].lval.sdword;
          if (analysis.check_address( addr ))
          {
            a.js( get_label( addr ) );
          }
          else
          {
            Label l;
            l = a.newLabel(  );
            a.jns( l );
            a.jmp( ( ( void* )addr ) );
            a.bind( l );
          }
        }                
        break;
      case UD_Ijns:
        {
          long addr = iter->pc;
          addr += iter->operand[ 0 ].size == 8? iter->operand[ 0 ].lval.sbyte : iter->operand[ 0 ].lval.sdword;
          if (analysis.check_address( addr ))
          {
            a.js( get_label( addr ) );
          }
          else
          {
            Label l;
            l = a.newLabel(  );
            a.jc( l );
            a.jmp( ( ( void* )addr ) );
            a.bind( l );
          }
        }                
        break;
      case UD_Ijo: 
        {
          long addr = iter->pc;
          addr += iter->operand[ 0 ].size == 8? iter->operand[ 0 ].lval.sbyte : iter->operand[ 0 ].lval.sdword;
          if (analysis.check_address( addr ))
          {
            a.jo( get_label( addr ) );
          }
          else
          {
            Label l;
            l = a.newLabel(  );
            a.jno( l );
            a.jmp( ( ( void* )addr ) );
            a.bind( l );
          }
        }                
        break;
      case UD_Ijno:
        {
          long addr = iter->pc;
          addr += iter->operand[ 0 ].size == 8? iter->operand[ 0 ].lval.sbyte : iter->operand[ 0 ].lval.sdword;
          if (analysis.check_address( addr ))
          {
            a.jno( get_label( addr ) );
          }
          else
          {
            Label l;
            l = a.newLabel(  );
            a.jo( l );
            a.jmp( ( ( void* )addr ) );
            a.bind( l );
          }
        }                
        break;
      case UD_Ijp: 
        {
          long addr = iter->pc;
          addr += iter->operand[ 0 ].size == 8? iter->operand[ 0 ].lval.sbyte : iter->operand[ 0 ].lval.sdword;
          if (analysis.check_address( addr ))
          {
            a.jp( get_label( addr ) );
          }
          else
          {
            Label l;
            l = a.newLabel(  );
            a.jnp( l );
            a.jmp( ( ( void* )addr ) );
            a.bind( l );
          }
        }                
        break;
      case UD_Ijnp:
        {
          long addr = iter->pc;
          addr += iter->operand[ 0 ].size == 8? iter->operand[ 0 ].lval.sbyte : iter->operand[ 0 ].lval.sdword;
          if (analysis.check_address( addr ))
          {
            a.jnp( get_label( addr ) );
          }
          else
          {
            Label l;
            l = a.newLabel(  );
            a.jp( l );
            a.jmp( ( ( void* )addr ) );
            a.bind( l );
          }
        }                
        break;
      case UD_Ija: 
        {
          long addr = iter->pc;
          addr += iter->operand[ 0 ].size == 8? iter->operand[ 0 ].lval.sbyte : iter->operand[ 0 ].lval.sdword;
          if (analysis.check_address( addr ))
          {
            a.ja( get_label( addr ) );
          }
          else
          {
            Label l;
            l = a.newLabel(  );
            a.jna( l );
            a.jmp( ( ( void* )addr ) );
            a.bind( l );
          }
        }                
        break;
      case UD_Ijbe:
        {
          long addr = iter->pc;
          addr += iter->operand[ 0 ].size == 8? iter->operand[ 0 ].lval.sbyte : iter->operand[ 0 ].lval.sdword;
          if (analysis.check_address( addr ))
          {
            a.jbe( get_label( addr ) );
          }
          else
          {
            Label l;
            l = a.newLabel(  );
            a.jnbe( l );
            a.jmp( ( ( void* )addr ) );
            a.bind( l );
          }
        }                
        break;
      case UD_Ijl:
        {
          long addr = iter->pc;
          addr += iter->operand[ 0 ].size == 8? iter->operand[ 0 ].lval.sbyte : iter->operand[ 0 ].lval.sdword;
          if (analysis.check_address( addr ))
          {
            a.jl( get_label( addr ) );
          }
          else
          {
            Label l;
            l = a.newLabel(  );
            a.jnl( l );
            a.jmp( ( ( void* )addr ) );
            a.bind( l );
          }
        }                
        break;
      case UD_Ijge:
        {
          long addr = iter->pc;
          addr += iter->operand[ 0 ].size == 8? iter->operand[ 0 ].lval.sbyte : iter->operand[ 0 ].lval.sdword;
          if (analysis.check_address( addr ))
          {
            a.jge( get_label( addr ) );
          }
          else
          {
            Label l;
            l = a.newLabel(  );
            a.jnge( l );
            a.jmp( ( ( void* )addr ) );
            a.bind( l );
          }
        }                
        break;
      case UD_Ijle:
        {
          long addr = iter->pc;
          addr += iter->operand[ 0 ].size == 8? iter->operand[ 0 ].lval.sbyte : iter->operand[ 0 ].lval.sdword;
          if (analysis.check_address( addr ))
          {
            a.jle( get_label( addr ) );
          }
          else
          {
            Label l;
            l = a.newLabel(  );
            a.jnle( l );
            a.jmp( ( ( void* )addr ) );
            a.bind( l );
          }
        }                
        break;
      case UD_Ijg:
        {
          long addr = iter->pc;
          addr += iter->operand[ 0 ].size == 8? iter->operand[ 0 ].lval.sbyte : iter->operand[ 0 ].lval.sdword;
          if (analysis.check_address( addr ))
          {
            a.jg( get_label( addr ) );
          }
          else
          {
            Label l;
            l = a.newLabel(  );
            a.jng( l );
            a.jmp( ( ( void* )addr ) );
            a.bind( l );
          }
        }                
        break;
        
      }      
    }
    //    address_table->assign_address(  )
  }
  return code;
}

