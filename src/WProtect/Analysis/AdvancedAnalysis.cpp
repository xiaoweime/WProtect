#include <AdvancedAnalysis.hpp>

void AdvancedAnalysis::push()
{
  
}

long AdvancedAnalysis::get_register_size(ud_operand & op)//ud_type & op)
{
  if (op.type == UD_OP_MEM)
  {
    return op.size / 8;
  }
  if (op.type == UD_OP_REG)
      switch ( op )
      {
      case UD_R_RAX:
        return 8;
        break;
      case UD_R_RBX:
        return 8;
        break;
      case UD_R_RCX:
        return 8;
        break;
      case UD_R_RDX:
        return 8;
        break;
      case UD_R_RSP:
        return 8;
        break;
      case UD_R_RBP:
        return 8;
        break;
      case UD_R_RDI:
        return 8;
        break;
      case UD_R_RSI:
        return 8;
        break;        
      case UD_R_EAX:
        return 4;
        break;
      case UD_R_EBX:
        return 4;
        break;
      case UD_R_ECX:
        return 4;
        break;
      case UD_R_EDX:
        return 4;
        break;
      case UD_R_ESP:
        return 4;
        break;
      case UD_R_EBP:
        return 4;
        break;
      case UD_R_EDI:
        return 4;
        break;
      case UD_R_ESI:
        return 4;
        break;
      case UD_R_AL:
        return 1;
        break;
      case UD_R_AH:
        return 1;
        break;
      case UD_R_BL:
        return 1;
        break;
      case UD_R_BH:
        return 1;
        break;
      case UD_R_CL:
        return 1;
        break;
      case UD_R_CH:
        return 1;
        break;
      case UD_R_DL:
        return 1;
        break;
      case UD_R_DH:
        return 1;
        break;
      case UD_R_AX:
        return 2;
        break;
      case UD_R_BX:
        return 2;
        break;
      case UD_R_CX:
        return 2;
        break;
      case UD_R_DX:
        return 2;
        break;
      case UD_R_SP:
        return 2;
        break;
      case UD_R_BP:
        return 2;
        break;
      case UD_R_SI:
        return 2;
        break;
      case UD_R_DI:
        return 2;
        break;
      dafault:
        return 0;
      }
    else
    {
#ifdef PROTECT_X64
      return 8;
#else
      return 4;
#endif
    }
    
      return 0;
}

 AdvancedAnalysis::get_analysis_operand(Analysis_Fuc & fuc)
{
   
}

void AdvancedAnalysis::set_analysis_operand(std::vector<Analysis_Operand> & o,ud_operand & op)
{  
  if (op.type == UD_OP_REG)
  {
    
  }
}

void AdvancedAnalysis::analysis_code()
{
  for (int i = 0; i < block_count ; ++i)
  {
    ud_t ud;
    pAssemblere nowtree = get_tree(i);
    Analysis_Fuc fuc;
    for (std::vector<ud_t>::iterator iter = nowtree->asmpiece.begin();
         iter != nowtree->asmpiece.end(); ++iter)
    {
      ud = *iter;
      switch(ud.mnemonic)
      {
      case UD_Ipush:
        fuc.local_variable_count += get_operand_size(ud.operand[0]);
        All_Analysis_Operand o;
        Analysis_Operand o1;
        fuc.virtual_stack(
        break;
      case UD_Iadd:
        All_Analysis_Operand o;
        Analysis_Operand o1,o2,o3;
        break;
      case UD_Ipop:
        break;
      case UD_Isub:
        break;
      case UD_Ipusha:
        break;
      case UD_Ipushfd:
        break;
      case UD_Ilea:
        break;
      }
      
    }
  }
}
