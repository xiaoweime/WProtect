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
  :nsp_diff( 0 ),nsp_data_diff( 0 ),vm_context_space( 0 )
{
}

EquivalentReplacement::~EquivalentReplacement()
{
  
}

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
  cout << "err:1001\r\n" << endl;

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
  cout << "err:1003\r\n" << endl;
  throw;
}

GPReg  EquivalentReplacement::get_rand_register(GPReg *r_n  ,int & count)
{
  int n = rand(  )%count;
  GPReg r = r_n[n];
  bool start = false;
  for (int i = 0; i < count; ++i)
  {
    if (start)
    {
      r_n[ i-1 ] = r_n[ i ];
      continue;
    }    
    if (i == n)
    {
      start = true;
    }
  }
  count--;
  return r;
}

GPReg EquivalentReplacement::get_imm( pVOperand o , GPReg *r_n  ,int & count )
{
  if (o->_imm.op == VOPERAND_IMM)
  {
    GPReg r = get_rand_register(r_n,count);
    a.mov( r,o->_imm.value );
    return r;
  }
  cout << "err:1000 \r\n" << endl;
  throw;
}

#define ___BASE_REG___ 1
#define ___INDEX_REG___ 2

GPReg EquivalentReplacement::get_reg( pVOperand o , GPReg *r_n , int & count ,char is_mem )
{
  if (o->_reg.base == T_NSP && is_mem == 0)
  {
    GPReg r = get_rand_register(r_n,count);
    a.lea( r , ptr(nsp,nsp_diff - nsp_data_diff) );
    return r;
  }
  if (o->_base.op == VOPERAND_REG || is_mem)
  {
    for (std::vector<EReg>::iterator iter = register_vec.begin(  ); iter != register_vec.end(  ); ++iter)
    {
      if ( !is_mem )
      if (o->_reg.base == iter->register_id )
      {
        GPReg r = get_rand_register(r_n,count);
        int offset = 0;
        if (o->_reg.base & T_8H)
        {
          offset = 1;
        }
        switch ( o->_reg.size )
        {
        case 1:
          a.mov( r, byte_ptr(nsp,nsp_diff - iter->register_diff + offset) );
          break;
        case 2:
          a.mov( r, word_ptr(nsp,nsp_diff - iter->register_diff + offset) );          
          break;
        case 4:
          a.mov( r, dword_ptr(nsp,nsp_diff - iter->register_diff + offset) );          
          break;
        case 8:
          a.mov( r, qword_ptr(nsp,nsp_diff - iter->register_diff + offset) );          
          break;
        }
        return r;
      }         
      if ( is_mem )
      {
        GPReg r = get_rand_register(r_n,count);
        int offset = 0;
        size_t size = o->_mem.size;
        bool start = false;
        if ( is_mem == ___BASE_REG___ )
        {
          if (o->_mem.base == T_NSP)
          {
            a.lea( r , ptr(nsp , nsp_diff - nsp_data_diff) );
            return r;
          }
          if (iter->register_id & o->_mem.base)
          {
            start = true;
          }
          if (o->_mem.base & T_8H)
          {
            offset = 1;
          }
        } else if ( is_mem == ___INDEX_REG___ )
        {
          if (o->_mem.index == T_NSP)
          {
            a.lea( r ,ptr(nsp,nsp_diff - nsp_data_diff) );
            return r;
          }                      
          if (iter->register_id & o->_mem.index)
          {
            start = true;
          }
          if (o->_mem.index & T_8H)
          {
            offset = 1;
          }
        }
        if ( start )
        {
          switch ( size )
          {
          case 1:
            a.mov( r, byte_ptr(nsp,nsp_diff - iter->register_diff + offset) );
            break;
          case 2:
            a.mov( r, word_ptr(nsp,nsp_diff - iter->register_diff + offset) );          
            break;
          case 4:
            a.mov( r, dword_ptr(nsp,nsp_diff - iter->register_diff + offset) );          
            break;
          case 8:
            a.mov( r, qword_ptr(nsp,nsp_diff - iter->register_diff + offset) );          
            break;
          }
          return r;          
        }
      }
    }    
  }
  cout << "err:1002\r\n" << endl;
  throw;
}

GPReg EquivalentReplacement::get_mem( pVOperand o , GPReg *r_n , int & count )
{
  GPReg reg_base;
  GPReg reg_index;
  if (o->_mem.base != 0)
  {
    reg_base = get_rand_register( r_n,count );
    a.mov( reg_base , get_reg( o , r_n , count , ___BASE_REG___ ) );
  }
  if (o->_mem.index != 0)
  {
    reg_index = get_rand_register( r_n , count );
    a.mov( reg_index,get_reg( o , r_n , count , ___INDEX_REG___ ) );
    switch ( o->_mem.scale )
    {
    case 1:
      break;
    case 2:
      a.shl( reg_index,1 );
      break;
    case 4:
      a.shl( reg_index,2 );
      break;
    case 8:
      a.shl( reg_index,3 );
      break;
    }
    if (o->_mem.base != 0)
    {
      a.add( reg_base,reg_index );
    }
    else
    {
      a.mov( reg_base,reg_index );
    }
  }
  if (o->_mem.lval && (o->_mem.base != 0 || o->_mem.index != 0) )
  {
    a.add(reg_base,o->_mem.lval);
  } else if (o->_mem.lval)
  {
    a.mov( reg_base,o->_mem.lval );
  }
  /*
  if (o->_mem.base == T_NSP)
  {
    a.add( reg_base,nsp_diff - nsp_data_diff );
  }
  if (o->_mem.index == T_NSP)
  {
    a.add( reg_base,nsp_diff - nsp_data_diff );
    }*/
  return reg_base;
}

void EquivalentReplacement::v_push( long _register )
{
  VReg o( _register );
  if (_register == T_EFLAG)
  {
    a.pushf(  );
  }
  else
  {
    a.push(get_register(&o));
  }
  nsp_diff += o._reg.size;
}

void EquivalentReplacement::v_pop( long _register )
{
  VReg o( _register );
  if (_register == T_EFLAG)
  {
    a.popf(  );
  }
  else
  {
    a.pop(get_register(&o));
  }
  nsp_diff += o._reg.size;  
}

void EquivalentReplacement::create_vm_space( long _size )
{
  a.lea( nsp,ptr( nsp , -_size) );
  vm_context_space += _size;
  nsp_diff += _size;
}

void EquivalentReplacement::push( pVOperand o ,GPReg *r_n , int &count )
{
  GPReg r = get_operand( o , r_n ,count);
  a.push( r );
  switch ( o->_base.size )
  {
  case 1:
    a.pop( byte_ptr( nsp,nsp_diff - nsp_data_diff - 1) );
    break;
  case 2:
    a.pop( word_ptr( nsp,nsp_diff - nsp_data_diff - 2) );
    break;
  case 4:
    a.pop( dword_ptr( nsp,nsp_diff - nsp_data_diff - 4) );
    break;
  case 8:
    a.pop( qword_ptr( nsp,nsp_diff - nsp_data_diff - 8 ) );
    break;    
  }
}

void EquivalentReplacement::pop( pVOperand o ,GPReg *r_n, int &count)
{
  GPReg r = get_operand( o , r_n,count );
  a.push( r );
  disable_register(o->_reg.base);
  switch ( o->_base.size )
  {
  case 1:
    a.pop( byte_ptr( nsp,get_invalid_space( 1 ) ) );
    break;
  case 2:
    a.pop( word_ptr( nsp,get_invalid_space( 1 ) ) );
    break;
  case 4:
    a.pop( dword_ptr( nsp,get_invalid_space( 1 ) ) );
    break;
  case 8:
    a.pop( qword_ptr( nsp,get_invalid_space( 1 ) ) );
    break;    
  }
}

long EquivalentReplacement::get_invalid_space(size_t _size  )
{
  vector <long > space_vec;
  space_vec.push_back( vm_context_space );
  for (std::vector<EReg>::iterator iter = register_vec.begin(  ); iter != register_vec.end(  ); ++iter)
  {
    space_vec.push_back(iter->register_diff);
  }
  space_vec.push_back( nsp_diff );
  sort( space_vec.begin(  ),space_vec.end(  ) );
  for (int i = 1; i < space_vec.size(  )/2 + 1;i++)
  {
    if (space_vec[ i ] - space_vec[ i-1 ] >= _size)
    {
      return space_vec[ i ];
    }
  }
}

bool EquivalentReplacement::disable_register( long _register )
{
   for (std::vector<EReg>::iterator iter = register_vec.begin(  ); iter != register_vec.end(  ); ++iter)
   {
     if ( iter->register_id == _register )
     {
       register_vec.erase( iter );
       return true;
     }
   }
   return false;
}

void EquivalentReplacement::save_vm_context(  )
{
  long register_array[  ] = {
    T_NAX,T_NBX,T_NCX,T_NDX,T_NBP,T_NSI,T_NDI
  };
  EReg r;
  int count = sizeof( register_array ) / sizeof( register_array[ 0 ] );
  for (int i = 0; i < count; ++i)
  {
    //nsp_diff += 4;    
    r.register_id = register_array[ i ];
    v_push( r.register_id );
    r.register_diff = nsp_diff;
    register_vec.push_back( r );
  }
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
#ifdef PROTECT_X64
      vop._imm.size = 8;
#else
      vop._imm.size = 4;
#endif
      return vop; 
    }
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
#ifndef PROTECT_X64
      vop._base.size = 4;
#else
      vop._base.size = 8;
#endif
      return vop;
    }
  defualt:
    cout << "err:1004\r\n" << endl;
    VOperand vop;
    return vop;
    break;
  }
}

GPReg EquivalentReplacement::get_operand( pVOperand o ,GPReg * r_n, int & count )
{
  switch ( o->_base.op )
  {
  case VOPERAND_IMM:
    return get_imm( o , r_n , count);
    break;
  case VOPERAND_MEM:
    return get_mem( o , r_n , count);
    break;
  case VOPERAND_REG:
    return get_reg( o , r_n , count );
    break;
  case VOPERAND_JIMM:
    break;
  }
  cout << "err:1004\r\n" << endl;
  throw;
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

pCodeBufferInfo EquivalentReplacement::BuildCode(pCodeBufferInfo code ,CodeAddressTable * address_table )
{
  FileLogger logger(stderr);
  a.setLogger(&logger);
  Analysis analysis;
  analysis.disasm( code );
  save_vm_context();
  for (int i = 0; i < analysis.block_count; ++i)
  {
    pAssemblerTree nowtree = analysis.get_tree( i );
    for (std::vector <ud_t> ::iterator iter = nowtree->asmpiece.begin(  );
         iter != nowtree->asmpiece.end(  ) ; ++iter)
    {
      GPReg reg_array[ 4 ][ 8 ] = {
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
      GPReg * r1 = NULL;
      GPReg * r2 = NULL;
      GPReg * r3 = NULL;
      int c1 = 0;
      int c2 = 0;
      int c3 = 0;
      VOperand vo1;
      VOperand vo2;
      VOperand vo3;
      GPReg o1;
      GPReg o2;
      GPReg o3;
      if ( iter->operand[ 0 ].type != UD_NONE &&         iter->operand[ 0 ].type != UD_OP_JIMM )
      {
        vo1 = udop_to_vop(iter->operand[ 0 ]);
        switch ( vo1._base.size )
        {
        case 1:
          r1 = reg_array[ 3 ];
          c1 = 8;
          break;
        case 2:
          r1 = reg_array[ 2 ];
          c1 = 7;
          break;
        case 4:
          r1 = reg_array[ 1 ];
          c1 = 7;
          break;
        case 8:
          r1 = reg_array[ 0 ];
          c1 = 7;
          break;
        }
        o1 = get_operand(&vo1 , r1 , c1);
      }
      if ( iter->operand[ 1 ].type != UD_NONE )
      {
        vo2 = udop_to_vop(iter->operand[ 1 ]);
        if (vo2._base.op == VOPERAND_IMM)
        {
          vo2._base.size = vo1._base.size;
        }
        switch ( vo2._base.size )
        {
        case 1:
          r2 = reg_array[ 3 ];
          c2 = 8;
          break;
        case 2:
          r2 = reg_array[ 2 ];
          c2 = 7;
          break;
        case 4:
          r2 = reg_array[ 1 ];
          c2 = 7;
          break;
        case 8:
          r2 = reg_array[ 0 ];
          c2 = 7;
          break;
        }
        o2 = get_operand(&vo2 , r2 , c2);        
      }
      if ( iter->operand[ 2 ].type != UD_NONE )
      {
        vo3 = udop_to_vop(iter->operand[ 2 ]);
        r3 = reg_array[ 3 ];
        c3 = 1;
        o3 = get_operand(&vo3 , r3 , c3);        
      }
      switch( iter->mnemonic )
      {
      case UD_Ipush:
        push( &vo1,r1,c1 );
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
        a.mov( o1,o2);
        //a.push( o2 );
        //        a.pop(  )
        break;
      case UD_Iret:
        break;
      case UD_Iadd:
        a.add( o1,o2 );
        break;
      case UD_Isub:
        a.sub( o1,o2 );
        break;
      case UD_Icall:
        {
          long addr = iter->pc;
          addr += iter->operand[ 0 ].size == 8? iter->operand[ 0 ].lval.sbyte : iter->operand[ 0 ].lval.sdword;
          if (analysis.check_address( addr ))
          {
            a.call( get_label( addr ) );
          }
          else
          {
            a.call(( void* ) addr );
          }
        }
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
  }
  return code;
}
