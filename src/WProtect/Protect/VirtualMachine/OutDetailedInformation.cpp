#include "OutDetailedInformation.hpp"


OutDI::OutDI()
  :_begin_text(""),_end_text("")
{
    
}

OutDI::~OutDI()
{
    
}
void OutDI::print_vmregister_information(long _register)
{
  switch ( _register )
  {
  case T_EAX:
    printf("%s%s" ,_begin_text,"eax" );
    break;
  case T_EBX:
    printf("%s%s" ,_begin_text,"ebx" );
    break;
  case T_ECX:
    printf("%s%s" ,_begin_text,"ecx" );
    break;
  case T_EDX:
    printf("%s%s" ,_begin_text,"edx" );
    break;
  case T_ESP:
    printf("%s%s" ,_begin_text,"esp" );
    break;
  case T_EBP:
    printf("%s%s" ,_begin_text,"ebp" );
    break;
  case T_ESI:
    printf("%s%s" ,_begin_text,"esi" );
    break;
  case T_EDI:
    printf("%s%s" ,_begin_text,"edi" );
    break;
   case T_AX:
    printf("%s%s" ,_begin_text,"ax" );
    break;
  case T_BX:
    printf("%s%s" ,_begin_text,"bx" );
    break;
  case T_CX:
    printf("%s%s" ,_begin_text,"cx" );
    break;
  case T_DX:
    printf("%s%s" ,_begin_text,"dx" );
    break;
  case T_SP:
    printf("%s%s" ,_begin_text,"sp" );
    break;
  case T_BP:
    printf("%s%s" ,_begin_text,"bp" );
    break;
  case T_SI:
    printf("%s%s" ,_begin_text,"si" );
    break;
  case T_DI:
    printf("%s%s" ,_begin_text,"di" );
    break;       
  case T_AL:
    printf("%s%s" ,_begin_text,"al" );
    break;
  case T_AH:
    printf("%s%s" ,_begin_text,"ah" );
    break;
  case T_BL:
    printf("%s%s" ,_begin_text,"bl" );
    break;
  case T_BH:
    printf("%s%s" ,_begin_text,"bh" );
    break;
  case T_CL:
    printf("%s%s" ,_begin_text,"cl" );
    break;
  case T_CH:
    printf("%s%s" ,_begin_text,"ch" );
    break;
  case T_DL:
    printf("%s%s" ,_begin_text,"dl" );
    break;
  case T_DH:
    printf("%s%s" ,_begin_text,"dh" );
    break;                       
  case T_KEY:
    printf("%s%s" ,_begin_text,"key" );
    break;
  case T_RET:
    printf("%s%s" ,_begin_text,"ret" );
    break;
  case T_EFLAG:
    printf("%s%s" ,_begin_text,"eflag" );
    break;
  case T_TMP_REGISTER1:
    printf("%s%s" ,_begin_text,"tmp1" );    
    break;
  case T_TMP_REGISTER2:
    printf("%s%s" ,_begin_text,"tmp2" );
    break;
  case T_TMP_REGISTER3:
    printf("%s%s" ,_begin_text,"tmp3" );    
    break;
  case T_TMP_REGISTER4:
    printf("%s%s" ,_begin_text,"tmp4" );    
    break;
  case T_TMP_REGISTER5:
    printf("%s%s" ,_begin_text,"tmp5" );
    break;
  case T_TMP_REGISTER6:
    printf("%s%s" ,_begin_text,"tmp6" );    
    break;
  case T_TMP_REGISTER7:
    printf("%s%s" ,_begin_text,"tmp7" );    
    break;
  case T_TMP_REGISTER8:
    printf("%s%s" ,_begin_text,"tmp8" );    
    break;
  case T_INVALID:
    printf("%s%s" ,_begin_text,"invalid");
    break;
  default:
    printf("unregister code:%x\r\n",_register);
    break;    
  }
  printf("%s",_end_text);
}


void OutDI::print_vmregister_information(RegisterStore &store)
{
  for(int i = 0;i<store.register_count;i++)
  {
       print_vmregister_information(store.register_array[i]);
  }
}

void OutDI::set_begin_text(char * _text)
{
  _begin_text = _text;
}

void OutDI::set_end_text(char * _text)
{
  _end_text = _text;
}
