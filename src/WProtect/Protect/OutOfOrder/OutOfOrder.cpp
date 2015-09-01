#include "OutOfOrder.hpp"

using namespace AsmJit;

OutOfOrder::OutOfOrder(  )
{
  
}

OutOfOrder::~OutOfOrder()
{
  
}


Label  OutOfOrder::get_label( long addr )
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
  label.label = a.a.newLabel(  );
  //  a.bind( label.label );
  label_vec.push_back( label );
  return label.label;
  throw;
}

bool OutOfOrder::check_label( long addr )
{
  for (std::vector<CLabel>::iterator iter =
         label_vec.begin(  ); iter != label_vec.end(  ); ++iter)
  {
    if (addr == iter->addr)
    {
      a.a.bind( iter->label );
      return true;
    }
  }
  return false;
}


pCodeBufferInfo OutOfOrder::BuildCode(pCodeBufferInfo code  )
{
  //FileLogger logger( stderr );
  //a.a.setLogger( &logger );
  Analysis analysis;
  analysis.disasm( code );
  for (int i = 0; i < analysis.block_count; ++i)
  {
    pAssemblerTree nowtree = analysis.get_tree( i );
    for (std::vector<ud_t>::iterator iter = nowtree->asmpiece.begin(  );
         iter != nowtree->asmpiece.end(  );++iter)
    {
      if ( !check_label( iter->insn_offset ) )
      {
        CLabel label;            
        label.addr = iter->insn_offset;
        label.label = a.a.newLabel(  );
        //a.a.bind( label.label );
        label_vec.push_back( label );
        a.a.bind(label_vec.back(  ).label);
      }      
      switch ( iter->mnemonic )
      {
      case UD_Ijmp:
        {
          long addr = iter->pc;
          addr += iter->operand[ 0 ].size == 8? iter->operand[ 0 ].lval.sbyte : iter->operand[ 0 ].lval.sdword;
          if (analysis.check_address( addr ))
          {
            a.a.jmp( get_label( addr ) );
          }
          else
          {
            a.a.jmp(( void* ) addr );
          }
        }
        break;        
      case UD_Icall:
        {
          long addr = iter->pc;
          addr += iter->operand[ 0 ].size == 8? iter->operand[ 0 ].lval.sbyte : iter->operand[ 0 ].lval.sdword;
          if (analysis.check_address( addr ))
          {
            a.a.call( get_label( addr ) );
          }
          else
          {
            a.a.call(( void* ) addr );
          }
        }
        break;
      case UD_Ijnz:
        {
          long addr = iter->pc;
          addr += iter->operand[ 0 ].size == 8? iter->operand[ 0 ].lval.sbyte : iter->operand[ 0 ].lval.sdword;
          if (analysis.check_address( addr ))
          {
            a.a.jnz( get_label( addr ) );
          }
          else
          {
            Label l;
            l = a.a.newLabel(  );
            a.a.jz( l );
            a.a.jmp( ( ( void* )addr ) );
            a.a.bind( l );
          }
        }
        break;
      case UD_Ijz:
        {
          long addr = iter->pc;
          addr += iter->operand[ 0 ].size == 8? iter->operand[ 0 ].lval.sbyte : iter->operand[ 0 ].lval.sdword;
          if (analysis.check_address( addr ))
          {
            a.a.jz( get_label( addr ) );
          }
          else
          {
            Label l;
            l = a.a.newLabel(  );
            a.a.jnz( l );
            a.a.jmp( ( ( void* )addr ) );
            a.a.bind( l );
          }

        }        
        break;
      case UD_Ijb: //如果进位位被置位则跳转  = 1
        {
          long addr = iter->pc;
          addr += iter->operand[ 0 ].size == 8? iter->operand[ 0 ].lval.sbyte : iter->operand[ 0 ].lval.sdword;
          if (analysis.check_address( addr ))
          {
            a.a.jnae( get_label( addr ) );
          }
          else
          {
            Label l;
            l = a.a.newLabel(  );
            a.a.jae( l );
            a.a.jmp( ( ( void* )addr ) );
            a.a.bind( l );
          }
        }                
        break;
      case UD_Ijae:
        {
          long addr = iter->pc;
          addr += iter->operand[ 0 ].size == 8? iter->operand[ 0 ].lval.sbyte : iter->operand[ 0 ].lval.sdword;
          if (analysis.check_address( addr ))
          {
            a.a.jae( get_label( addr ) );
          }
          else
          {
            Label l;
            l = a.a.newLabel(  );
            a.a.jnae( l );
            a.a.jmp( ( ( void* )addr ) );
            a.a.bind( l );
          }
        }                
        break;
      case UD_Ijs: 
        {
          long addr = iter->pc;
          addr += iter->operand[ 0 ].size == 8? iter->operand[ 0 ].lval.sbyte : iter->operand[ 0 ].lval.sdword;
          if (analysis.check_address( addr ))
          {
            a.a.js( get_label( addr ) );
          }
          else
          {
            Label l;
            l = a.a.newLabel(  );
            a.a.jns( l );
            a.a.jmp( ( ( void* )addr ) );
            a.a.bind( l );
          }
        }                
        break;
      case UD_Ijns:
        {
          long addr = iter->pc;
          addr += iter->operand[ 0 ].size == 8? iter->operand[ 0 ].lval.sbyte : iter->operand[ 0 ].lval.sdword;
          if (analysis.check_address( addr ))
          {
            a.a.js( get_label( addr ) );
          }
          else
          {
            Label l;
            l = a.a.newLabel(  );
            a.a.jc( l );
            a.a.jmp( ( ( void* )addr ) );
            a.a.bind( l );
          }
        }                
        break;
      case UD_Ijo: 
        {
          long addr = iter->pc;
          addr += iter->operand[ 0 ].size == 8? iter->operand[ 0 ].lval.sbyte : iter->operand[ 0 ].lval.sdword;
          if (analysis.check_address( addr ))
          {
            a.a.jo( get_label( addr ) );
          }
          else
          {
            Label l;
            l = a.a.newLabel(  );
            a.a.jno( l );
            a.a.jmp( ( ( void* )addr ) );
            a.a.bind( l );
          }
        }                
        break;
      case UD_Ijno:
        {
          long addr = iter->pc;
          addr += iter->operand[ 0 ].size == 8? iter->operand[ 0 ].lval.sbyte : iter->operand[ 0 ].lval.sdword;
          if (analysis.check_address( addr ))
          {
            a.a.jno( get_label( addr ) );
          }
          else
          {
            Label l;
            l = a.a.newLabel(  );
            a.a.jo( l );
            a.a.jmp( ( ( void* )addr ) );
            a.a.bind( l );
          }
        }                
        break;
      case UD_Ijp: 
        {
          long addr = iter->pc;
          addr += iter->operand[ 0 ].size == 8? iter->operand[ 0 ].lval.sbyte : iter->operand[ 0 ].lval.sdword;
          if (analysis.check_address( addr ))
          {
            a.a.jp( get_label( addr ) );
          }
          else
          {
            Label l;
            l = a.a.newLabel(  );
            a.a.jnp( l );
            a.a.jmp( ( ( void* )addr ) );
            a.a.bind( l );
          }
        }                
        break;
      case UD_Ijnp:
        {
          long addr = iter->pc;
          addr += iter->operand[ 0 ].size == 8? iter->operand[ 0 ].lval.sbyte : iter->operand[ 0 ].lval.sdword;
          if (analysis.check_address( addr ))
          {
            a.a.jnp( get_label( addr ) );
          }
          else
          {
            Label l;
            l = a.a.newLabel(  );
            a.a.jp( l );
            a.a.jmp( ( ( void* )addr ) );
            a.a.bind( l );
          }
        }                
        break;
      case UD_Ija: 
        {
          long addr = iter->pc;
          addr += iter->operand[ 0 ].size == 8? iter->operand[ 0 ].lval.sbyte : iter->operand[ 0 ].lval.sdword;
          if (analysis.check_address( addr ))
          {
            a.a.ja( get_label( addr ) );
          }
          else
          {
            Label l;
            l = a.a.newLabel(  );
            a.a.jna( l );
            a.a.jmp( ( ( void* )addr ) );
            a.a.bind( l );
          }
        }                
        break;
      case UD_Ijbe:
        {
          long addr = iter->pc;
          addr += iter->operand[ 0 ].size == 8? iter->operand[ 0 ].lval.sbyte : iter->operand[ 0 ].lval.sdword;
          if (analysis.check_address( addr ))
          {
            a.a.jbe( get_label( addr ) );
          }
          else
          {
            Label l;
            l = a.a.newLabel(  );
            a.a.jnbe( l );
            a.a.jmp( ( ( void* )addr ) );
            a.a.bind( l );
          }
        }                
        break;
      case UD_Ijl:
        {
          long addr = iter->pc;
          addr += iter->operand[ 0 ].size == 8? iter->operand[ 0 ].lval.sbyte : iter->operand[ 0 ].lval.sdword;
          if (analysis.check_address( addr ))
          {
            a.a.jl( get_label( addr ) );
          }
          else
          {
            Label l;
            l = a.a.newLabel(  );
            a.a.jnl( l );
            a.a.jmp( ( ( void* )addr ) );
            a.a.bind( l );
          }
        }                
        break;
      case UD_Ijge:
        {
          long addr = iter->pc;
          addr += iter->operand[ 0 ].size == 8? iter->operand[ 0 ].lval.sbyte : iter->operand[ 0 ].lval.sdword;
          if (analysis.check_address( addr ))
          {
            a.a.jge( get_label( addr ) );
          }
          else
          {
            Label l;
            l = a.a.newLabel(  );
            a.a.jnge( l );
            a.a.jmp( ( ( void* )addr ) );
            a.a.bind( l );
          }
        }                
        break;
      case UD_Ijle:
        {
          long addr = iter->pc;
          addr += iter->operand[ 0 ].size == 8? iter->operand[ 0 ].lval.sbyte : iter->operand[ 0 ].lval.sdword;
          if (analysis.check_address( addr ))
          {
            a.a.jle( get_label( addr ) );
          }
          else
          {
            Label l;
            l = a.a.newLabel(  );
            a.a.jnle( l );
            a.a.jmp( ( ( void* )addr ) );
            a.a.bind( l );
          }
        }                
        break;
      case UD_Ijg:
        {
          long addr = iter->pc;
          addr += iter->operand[ 0 ].size == 8? iter->operand[ 0 ].lval.sbyte : iter->operand[ 0 ].lval.sdword;
          if (analysis.check_address( addr ))
          {
            a.a.jg( get_label( addr ) );
          }
          else
          {
            Label l;
            l = a.a.newLabel(  );
            a.a.jng( l );
            a.a.jmp( ( ( void* )addr ) );
            a.a.bind( l );
          }
        }                
        break;
      }
              a.Assemble(iter->insn_buffer);
    }
  }
  return code;
}
