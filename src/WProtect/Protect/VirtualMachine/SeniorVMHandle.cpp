#include "SeniorVMHandle.hpp"
#include <WProtectConfig.h>
#include <algorithms>

SeniorVMHandle::SeniorVMHandle() : super_protect(false)
{
}

SeniorVMHandle::SeniorVMHandle(PCode *p) : super_protect(false)
{
  pcode = p;
}

SeniorVMHandle::~SeniorVMHandle()
{
}

void SeniorVMHandle::link_pcode(PCode *p)
{
  pcode = p;
}

void SeniorVMHandle::set_protect_grade(bool b )
{
  super_protect = b;
}

long SeniorVMHandle::get_code_size( )
{
  return pcode->get_code_size(  );
}

#define HANDLE pcode->pcode_info.handle_table
//#define db(x) pcode->db(x)
//#define dw(x) pcode->dw(x)
//#define dd(x) pcode->dd(x)
//#define dq(x) pcode->dq(x)
#define push_esp push_stack_top_base 
#define GET_HANDLE(x) pcode->pcode_info.handle_table.x.handle

void* SeniorVMHandle::get_code_buf( )
{
  if ( pcode->pcode_info.sign == false)
     return &pcode->pcode_info.buf
    [pcode->pcode_info.size - pcode->pcode_info.offset];
  else
    return pcode->pcode_info.buf;
}

void SeniorVMHandle::save_vm_context()
{
  /*
  int register_count = 0;
#ifdef PROTECT_X64
  pcode->register_store_in.register_array[register_count++] = T_R15;
  pcode->register_store_in.register_array[register_count++] = T_R14;
  pcode->register_store_in.register_array[register_count++] = T_R13;
  pcode->register_store_in.register_array[register_count++] = T_R12;
  pcode->register_store_in.register_array[register_count++] = T_R11;
  pcode->register_store_in.register_array[register_count++] = T_R10;
  pcode->register_store_in.register_array[register_count++] = T_R9;
  pcode->register_store_in.register_array[register_count++] = T_R8;
#endif
  pcode->register_store_in.register_array[register_count++] = T_NDI ;
  pcode->register_store_in.register_array[register_count++] = T_NSI ;
  pcode->register_store_in.register_array[register_count++] = T_NBP ;
  pcode->register_store_in.register_array[register_count++] = T_NSP ;
  pcode->register_store_in.register_array[register_count++] = T_NBX ;
  pcode->register_store_in.register_array[register_count++] = T_NDX ;
  pcode->register_store_in.register_array[register_count++] = T_NCX ;
  pcode->register_store_in.register_array[register_count++] = T_NAX ;
  pcode->register_store_in.register_array[register_count++] = T_EFLAG ;
  pcode->register_store_in.register_array[register_count++] = T_KEY;
  pcode->register_store_in.register_array[register_count++] = T_RET;
  
  upset<long>(pcode->register_store_in.register_array,register_count);
  */
  //pcode->register_store_in.register_count = register_count;
  int register_count = pcode->register_store_in.register_count;
  for (int i = register_count; i > 0; --i)
  {
    /* if (pcode->register_store_in.register_array[ i ] ==  T_NAX ||
        pcode->register_store_in.register_array[ i ] ==  T_NBX ||
        pcode->register_store_in.register_array[ i ] ==  T_NCX ||
        pcode->register_store_in.register_array[ i ] ==  T_NDX ||
        pcode->register_store_in.register_array[ i ] ==  T_NSP ||
        pcode->register_store_in.register_array[ i ] ==  T_NBP ||
        pcode->register_store_in.register_array[ i ] ==  T_NSI ||
        pcode->register_store_in.register_array[ i ] ==  T_NDI ||
#ifdef PROTECT_X64
        pcode->register_store_in.register_array[ i ] ==  T_NAX | T_RN ||
        pcode->register_store_in.register_array[ i ] ==  T_NBX | T_RN ||
        pcode->register_store_in.register_array[ i ] ==  T_NCX | T_RN ||
        pcode->register_store_in.register_array[ i ] ==  T_NDX | T_RN ||
        pcode->register_store_in.register_array[ i ] ==  T_NSP | T_RN ||
        pcode->register_store_in.register_array[ i ] ==  T_NBP | T_RN ||
        pcode->register_store_in.register_array[ i ] ==  T_NSI | T_RN ||
        pcode->register_store_in.register_array[ i ] ==  T_NDI | T_RN ||
#endif
        pcode->register_store_in.register_array[ i ] ==  T_RET ||
        pcode->register_store_in.register_array[ i ] ==  T_KEY ||
        pcode->register_store_in.register_array[ i ] ==  T_EFLAG3 )    */
    pop(pcode->register_store_in.register_array[i-1]);
  }
}

void SeniorVMHandle::upset_register_array(RegisterStore & r )
{
  int register_count = 0;
  
    //  upset<long>(pcode->register_store_in.register_array,register_count);
  r.register_array[ register_count++ ] = T_NAX;
  r.register_array[ register_count++ ] = T_NBX;
  r.register_array[ register_count++ ] = T_NCX;
  r.register_array[ register_count++ ] = T_NDX;
  //r.register_array[ register_count++ ] = T_NSP;
  r.register_array[ register_count++ ] = T_NBP;
  r.register_array[ register_count++ ] = T_NSI;
  r.register_array[ register_count++ ] = T_NDI;
  r.register_array[ register_count++ ] = T_EFLAG;
  r.register_array[ register_count++ ] = T_KEY;
  r.register_array[ register_count++ ] = T_RET;
#ifdef PROTECT_X64
  r.register_array[ register_count++ ] = T_R8;
  r.register_array[ register_count++ ] = T_R9;
  r.register_array[ register_count++ ] = T_R10;
  r.register_array[ register_count++ ] = T_R11;
  r.register_array[ register_count++ ] = T_R12;
  r.register_array[ register_count++ ] = T_R13;
  r.register_array[ register_count++ ] = T_R14;
  r.register_array[ register_count++ ] = T_R15;
#endif
  r.register_count = register_count;
  upset<long>( r.register_array, register_count);
}

void SeniorVMHandle::recover_vm_context()
{
  /*
  int register_count = 0;

  pcode->register_store_out.register_array[ register_count++ ] = T_NAX;
  pcode->register_store_out.register_array[ register_count++ ] = T_NBX;
  pcode->register_store_out.register_array[ register_count++ ] = T_NCX;
  pcode->register_store_out.register_array[ register_count++ ] = T_NDX;
  pcode->register_store_out.register_array[ register_count++ ] = T_NSP;
  pcode->register_store_out.register_array[ register_count++ ] = T_NBP;
  pcode->register_store_out.register_array[ register_count++ ] = T_NSI;
  pcode->register_store_out.register_array[ register_count++ ] = T_NDI;
  pcode->register_store_out.register_array[ register_count++ ] = T_EFLAG;
  pcode->register_store_out.register_array[ register_count++ ] = T_RET;
  pcode->register_store_out.register_array[ register_count++ ] = T_KEY;

#ifdef PROTECT_X64
  pcode->register_store_out.register_array[ register_count++ ] = T_R8;
  pcode->register_store_out.register_array[ register_count++ ] = T_R9;
  pcode->register_store_out.register_array[ register_count++ ] = T_R10;
  pcode->register_store_out.register_array[ register_count++ ] = T_R11;
  pcode->register_store_out.register_array[ register_count++ ] = T_R12;
  pcode->register_store_out.register_array[ register_count++ ] = T_R13;
  pcode->register_store_out.register_array[ register_count++ ] = T_R14;
  pcode->register_store_out.register_array[ register_count++ ] = T_R15;
#endif

  pcode->register_store_out.register_count = register_count;
  
  //int register_count = pcode->register_store_out.register_count;
  upset<long>( pcode->register_store_out.register_array, register_count );*/
  int register_count = pcode->register_store_out.register_count;

  /*
  for (int i = register_count; i > 0; --i)
  {
    push(pcode->register_store_out.register_array[i-1]);
  }
  */
  for (int i = 0; i < register_count; ++i)
  {
    if (pcode->register_store_out.register_array[ i ] ==  T_NAX ||
        pcode->register_store_out.register_array[ i ] ==  T_NBX ||
        pcode->register_store_out.register_array[ i ] ==  T_NCX ||
        pcode->register_store_out.register_array[ i ] ==  T_NDX ||
        pcode->register_store_out.register_array[ i ] ==  T_NSP ||
        pcode->register_store_out.register_array[ i ] ==  T_NBP ||
        pcode->register_store_out.register_array[ i ] ==  T_NSI ||
        pcode->register_store_out.register_array[ i ] ==  T_NDI ||
#ifdef PROTECT_X64
        pcode->register_store_out.register_array[ i ] ==  T_NAX | T_RN ||
        pcode->register_store_out.register_array[ i ] ==  T_NBX | T_RN ||
        pcode->register_store_out.register_array[ i ] ==  T_NCX | T_RN ||
        pcode->register_store_out.register_array[ i ] ==  T_NDX | T_RN ||
        pcode->register_store_out.register_array[ i ] ==  T_NSP | T_RN ||
        pcode->register_store_out.register_array[ i ] ==  T_NBP | T_RN ||
        pcode->register_store_out.register_array[ i ] ==  T_NSI | T_RN ||
        pcode->register_store_out.register_array[ i ] ==  T_NDI | T_RN ||
#endif
        pcode->register_store_out.register_array[ i ] ==  T_RET ||
        pcode->register_store_out.register_array[ i ] ==  T_KEY ||
        pcode->register_store_out.register_array[ i ] ==  T_EFLAG)
    /* if (pcode->register_store_out.register_array[ i ] & T_TMP_R64_1 ||
        pcode->register_store_out.register_array[ i ] & T_TMP_R64_2 ||
        pcode->register_store_out.register_array[ i ] & T_TMP_R64_3 ||
        pcode->register_store_out.register_array[ i ] & T_TMP_R64_4 ||
        pcode->register_store_out.register_array[ i ] & T_TMP_R64_5 ||
        pcode->register_store_out.register_array[ i ] & T_TMP_R64_6 ||
        pcode->register_store_out.register_array[ i ] & T_TMP_R64_7 ||
        pcode->register_store_out.register_array[ i ] & T_TMP_R64_8 )
    {
    }
    else*/
    push( pcode->register_store_out.register_array[ i ] );
  }
  //push(T_JCC_REGISTER);
}


void SeniorVMHandle::push(long _register,bool _disable)
{
#ifdef DEBUG
  char *type = "push(" ;
  switch ( _register )
  {
  case T_NAX:
    printf("%s%s" ,type,"nax" );
    break;
  case T_NBX:
    printf("%s%s" ,type,"nbx" );
    break;
  case T_NCX:
    printf("%s%s" ,type,"ncx" );
    break;
  case T_NDX:
    printf("%s%s" ,type,"ndx" );
    break;
  case T_NSP:
    printf("%s%s" ,type,"nsp" );
    break;
  case T_NBP:
    printf("%s%s" ,type,"nbp" );
    break;
  case T_NSI:
    printf("%s%s" ,type,"nsi" );
    break;
  case T_NDI:
    printf("%s%s" ,type,"ndi" );
    break;
  case T_KEY:
    printf("%s%s" ,type,"key" );
    break;
  case T_RET:
    printf("%s%s" ,type,"ret" );
    break;
  case T_EFLAG:
    printf("%s%s" ,type,"eflag" );
    break;
  case T_TMP_REGISTER1:
    printf("%s%s" ,type,"tmp1" );    
    break;
  case T_TMP_REGISTER2:
    printf("%s%s" ,type,"tmp2" );
    break;
  case T_TMP_REGISTER3:
    printf("%s%s" ,type,"tmp3" );    
    break;
  case T_TMP_REGISTER4:
    printf("%s%s" ,type,"tmp4" );    
    break;
  case T_TMP_REGISTER5:
    printf("%s%s" ,type,"tmp5" );
    break;
  case T_TMP_REGISTER6:
    printf("%s%s" ,type,"tmp6" );    
    break;
  case T_TMP_REGISTER7:
    printf("%s%s" ,type,"tmp7" );    
    break;
  case T_TMP_REGISTER8:
    printf("%s%s" ,type,"tmp8" );    
    break;
  case T_INVALID:
    printf("%s%s",type,"invalid");
  default:
    printf("%sunregister",type);
    break;
  }
  printf( ")\r\n" );
#endif
   pcode->v_push_register(_register,_disable);
}

void SeniorVMHandle::pop(long _register)
{
#ifdef DEBUG
  char *type = "pop(" ;
  switch ( _register )
  {
  case T_NAX:
    printf("%s%s" ,type,"nax" );
    break;
  case T_NBX:
    printf("%s%s" ,type,"nbx" );
    break;
  case T_NCX:
    printf("%s%s" ,type,"ncx" );
    break;
  case T_NDX:
    printf("%s%s" ,type,"ndx" );
    break;
  case T_NSP:
    printf("%s%s" ,type,"nsp" );
    break;
  case T_NBP:
    printf("%s%s" ,type,"nbp" );
    break;
  case T_NSI:
    printf("%s%s" ,type,"nsi" );
    break;
  case T_NDI:
    printf("%s%s" ,type,"ndi" );
    break;
  case T_KEY:
    printf("%s%s" ,type,"key" );
    break;
  case T_RET:
    printf("%s%s" ,type,"ret" );
    break;
  case T_EFLAG:
    printf("%s%s" ,type,"eflag" );
    break;
  case T_TMP_REGISTER1:
    printf("%s%s" ,type,"tmp1" );    
    break;
  case T_TMP_REGISTER2:
    printf("%s%s" ,type,"tmp2" );
    break;
  case T_TMP_REGISTER3:
    printf("%s%s" ,type,"tmp3" );    
    break;
  case T_TMP_REGISTER4:
    printf("%s%s" ,type,"tmp4" );    
    break;
  case T_TMP_REGISTER5:
    printf("%s%s" ,type,"tmp5" );
    break;
  case T_TMP_REGISTER6:
    printf("%s%s" ,type,"tmp6" );    
    break;
  case T_TMP_REGISTER7:
    printf("%s%s" ,type,"tmp7" );    
    break;
  case T_TMP_REGISTER8:
    printf("%s%s" ,type,"tmp8" );    
    break;
  case T_INVALID:
    printf("%s%s" ,type,"invalid");
    break;
  default:
    printf("unregister code:%x\r\n",_register);
    break;    
  }
  printf( ")\r\n" );
#endif  
  pcode->v_pop_register(_register);
}

void SeniorVMHandle::b_not(long _register,bool is_data)
{
  if (is_data)
  {
    b_push_imm( _register );
    b_copy_stack();
    db( GET_HANDLE( b_nand ) );
  }
  if (_register == 0)
  {
    db(HANDLE.b_nand.handle);
    return;
  }  
  push(_register);
  db(HANDLE.push_stack_top_base.handle);
  db(HANDLE.b_read_mem.handle);
  db(HANDLE.b_nand.handle);
}

void SeniorVMHandle::w_not(long _register,bool is_data)
{
  if (is_data)
  {
    w_push_imm( _register );
    w_copy_stack();
    db( GET_HANDLE( w_nand ) );
    return;
  }
  if (_register == 0)
  {
    db(HANDLE.w_nand.handle);
    return;
  }
  push(_register);
  db(HANDLE.push_stack_top_base.handle);
  db(HANDLE.w_read_mem.handle);
  db(HANDLE.w_nand.handle);
}

void SeniorVMHandle::d_not(long _register,bool is_data) //如果第二个参数为true 那第一个参数就是 要Not的立即数
{
  if (is_data)
  {
    d_push_imm(_register);
    d_copy_stack();
    db( GET_HANDLE(d_nand) );
    return;
  }
  if (_register == 0)
  {
    db(HANDLE.d_nand.handle);
    return;
  }
/*
  char n = rand()%101;
  if (n <= 10)
  {
    d_not(_register); //a = nand(_r,_r);
    pop(T_INVALID);
    d_not(_register); //b = nand(_r,_r);
    pop(T_INVALID);
    db(HANDLE.d_nand.handle); //nand(a,b)
    pop(T_INVALID);
    d_not(_register); //a = nand(_r,_r);
    pop(T_INVALID);
    d_not(_register); //b = nand(_r,_r);
    pop(T_INVALID);
    db(HANDLE.d_nand.handle); //nand(a,b)
    pop(T_INVALID);
    db(HANDLE.d_nand.handle);
    return;
    }*/
  push(_register,false);
  db(HANDLE.push_stack_top_base.handle);
  db(HANDLE.d_read_mem.handle);
  //#ifndef PROTECT_X64
  //db(HANDLE.push_stack_top_base.handle);
  //db(HANDLE.d_read_mem.handle);
  //pop(_register);
  //#endif
  db(HANDLE.d_nand.handle);
}

#ifdef PROTECT_X64
void SeniorVMHandle::q_not(long _register,bool is_data)
{
  if (is_data)
  {
    q_push_imm(_register);
    q_copy_stack(  );
    db( GET_HANDLE( q_nand ) );
    return;
  }
  if (_register == 0)
  {
    db(HANDLE.q_nand.handle);
    return;
  }
  push(_register,false);
  db(HANDLE.push_stack_top_base.handle);
  db(HANDLE.q_read_mem.handle);

  //db(HANDLE.push_stack_top_base.handle);
  //db(HANDLE.q_read_mem.handle);
  //pop(_register);

  db(HANDLE.q_nand.handle);
}
#endif

char SeniorVMHandle::v_not( pVOperand o1 )
{
  return v_not_and( o1,o1 );
}

void SeniorVMHandle::b_not_and(long _register1,long _register2,bool is_data)
{
  if (is_data)
  {
    b_push_imm( _register2 );
    push( _register1 );
    db( GET_HANDLE( b_nand ) );
    return;
  }
  if (_register1 == 0 || _register2 == 0)
  {
    db(HANDLE.b_nand.handle);
    return;
  }
  push(_register2);
  push(_register1);
  db(HANDLE.b_nand.handle);
}

void SeniorVMHandle::w_not_and(long _register1,long _register2,bool is_data)
{
  if (is_data)
  {
    w_push_imm( _register2 );
    push( _register1 );
    db( GET_HANDLE( w_nand ) );
    return;
  }  
  if (_register1 == 0 || _register2 == 0)
  {
    db(HANDLE.w_nand.handle);
    return;
  }
  push(_register2);
  push(_register1);
  db(HANDLE.w_nand.handle);
}

void SeniorVMHandle::d_not_and(long _register1,long _register2,bool is_data)
{
  if (is_data)
  {
    d_push_imm( _register2 );
    push( _register1 );
    db( GET_HANDLE( d_nand ) );
    return;
  }
  if (_register1 == 0 || _register2 == 0)
  {
    db(HANDLE.d_nand.handle);
    return;
  }
  push(_register2,false);
  //  db(HANDLE.push_esp.handle);
  //db(HANDLE.d_read_mem.handle);
  //pop(_register2);
  
  push(_register1,false);
  //db(HANDLE.push_esp.handle);
  //db(HANDLE.d_read_mem.handle);
  //pop(_register1);
  db(HANDLE.d_nand.handle);
}
#ifdef PROTECT_X64
void SeniorVMHandle::q_not_and(long _register1,long _register2,bool is_data)
{
  if (is_data)
  {
    q_push_imm( _register2 );
    push( _register1 );
    db( GET_HANDLE( q_nand ) );
    return;
  }  
  if (_register1 == 0 || _register2 == 0)
  {
    db(HANDLE.q_nand.handle);
    return;
  }
  push(_register2,false);
  //db(HANDLE.push_esp.handle);
  //db(HANDLE.q_read_mem.handle);
  //pop(_register2);
  
  push(_register1,false);
  //db(HANDLE.push_esp.handle);
  //db(HANDLE.q_read_mem.handle);
  //pop(_register1);
  db(HANDLE.q_nand.handle);
}
#endif

char SeniorVMHandle::push_operand( pVOperand o )
{
  if (o == NULL)
  {
    return 0;
  }
  if (o->is_mem(  ))
  {
    r_get_mem( o->_mem.base,o->_mem.index,o->_mem.scale,o->_mem.lval );
    switch (o->_mem.size )
    {
    case 1:
      db( GET_HANDLE( b_read_mem ) );
      return 1;
      break;
    case 2:
      db( GET_HANDLE( w_read_mem ) );
      return 2;
      break;
    case 4:
      db( GET_HANDLE( d_read_mem ) );
      return 4;
      break;
#ifdef PROTECT_X64
    case 8:
        db( GET_HANDLE( q_read_mem ) );
        return 8;
      break;
#endif
    }
  } else if (o->is_reg(  ))
  {
    push( o->_reg.base );
    if (o->_reg.base & T_E32X)
    {
      return 4;
    } else if (o->_reg.base & T_16X)
    {
      return 2;
    } else if ( o->_reg.base & T_8L || o->_reg.base & T_8H)
    {
      return 1;
    } else
      return 8;
      
  } else if (o->is_imm(  ))
  {
    switch( o->_imm.size )
    {
    case 1:
      b_push_imm(o->_imm.value);
      return 1;
      break;
    case 2:
      w_push_imm( o->_imm.value );
      return 2;
      break;
    case 4:
      d_push_imm( o->_imm.value );
      return 4;
      break;
#ifdef PROTECT_X64
    case 8:
      q_push_imm( o->_imm.value );
      return 8;
      break;
#endif
    }
  } else if (o->is_none(  ))
  {
    return 0;
  }
  else {
    cout << "Unknow OP\r\n" << endl;
    throw;
    return -1;
  }
  return 0;
}


char SeniorVMHandle::pop_operand( pVOperand o )
{
  if (o == NULL)
  {
    return 0;
  }
  if (o->is_mem(  ))
  {
    r_get_mem( o->_mem.base,o->_mem.index,o->_mem.scale,o->_mem.lval );
    switch (o->_mem.size )
    {
    case 1:
      db( GET_HANDLE( b_write_mem ) );
      return 1;
      break;
    case 2:
      db( GET_HANDLE( w_write_mem ) );
      return 2;
      break;
    case 4:
      db( GET_HANDLE( d_write_mem ) );
      return 4;
      break;
#ifdef PROTECT_X64
    case 8:
      db( GET_HANDLE( q_write_mem ) );
      return 8;
      break;
#endif
    }
  } else if (o->is_reg(  ))
  {
    pop( o->_reg.base );
    if (o->_reg.base & T_E32X)
    {
      return 4;
    } else if (o->_reg.base & T_16X)
    {
      return 2;
    } else if ( o->_reg.base & T_8L || o->_reg.base & T_8H)
    {
      return 1;
    } else
      return 8;
  } else if (o->is_none(  ))
  {
    return 0;
  }
  else {
    cout << "Unknow OP\r\n" << endl;
    throw;
    return -1;
  }
  return 0;
}

char SeniorVMHandle::v_not_and( pVOperand  o1,pVOperand o2 )
{
  char s1 = push_operand(o1);
  char s2 = push_operand(o2);
  switch ( s1?s1:s2 )
  {
  case 1:
    db( GET_HANDLE( b_nand ) );
    return 1;
    break;
  case 2:
    db( GET_HANDLE( w_nand ) );
    return 2;
    break;
  case 4:
    db( GET_HANDLE( d_nand ) );
    return 4;
    break;
#ifdef PROTECT_X64
  case 8:
    db( GET_HANDLE( q_nand ) );
    return 8;
    break;
#endif
  default:
    {
#ifdef PROTECT_X64
      db( GET_HANDLE( q_nand ) );
      return 8;
#else
      db( GET_HANDLE( d_nand ) );
      return 4;
#endif
    }
  }
  return 0;
}

void SeniorVMHandle::b_and(long _register1,long _register2,bool is_data) //如果is_data为真 那register2为数据 
{
  if (is_data)
  {
    b_not( _register2 , true );
    pop( T_INVALID );
    b_not( _register1 );
    pop( T_INVALID );
    db( GET_HANDLE( b_nand ) );
    return;
  }
  b_not(_register2);
  pop(T_INVALID);
  b_not(_register1);
  pop(T_INVALID);
  db(HANDLE.b_nand.handle);
}

void SeniorVMHandle::w_and(long _register1,long _register2,bool is_data)
{
  if (is_data)
  {
    w_not( _register2 , true );
    pop( T_INVALID );
    w_not( _register1 );
    pop( T_INVALID );
    db( GET_HANDLE( w_nand ) );
    return;
  }  

  w_not(_register2);
  pop(T_INVALID);
  w_not(_register1);
  pop(T_INVALID);
  db(HANDLE.w_nand.handle);
}

void SeniorVMHandle::d_and(long _register1,long _register2,bool is_data)
{
  if (is_data)
  {
    d_not( _register2 , true );
    pop( T_INVALID );
    d_not( _register1 );
    pop( T_INVALID );
    db( GET_HANDLE( d_nand ) );
    return;
  }    
  d_not(_register2);
  pop(T_INVALID);
  d_not(_register1);
  pop(T_INVALID);
  db(HANDLE.d_nand.handle);
}

#ifdef PROTECT_X64
void SeniorVMHandle::q_and(long _register1,long _register2,bool is_data)
{
  if (is_data)
  {
    q_not( _register2 , true );
    pop( T_INVALID );
    q_not( _register1 );
    pop( T_INVALID );
    db( GET_HANDLE( q_nand ) );
    return;
  }    
  q_not(_register2);
  pop(T_INVALID);
  q_not(_register1);
  pop(T_INVALID);
  db(HANDLE.q_nand.handle);
}
#endif

char SeniorVMHandle::v_and( pVOperand o1,pVOperand o2 )
{
  char s1 = v_not_and(o1,o1);
  pop( T_INVALID );
  char s2 = v_not_and(o2,o2);
  pop( T_INVALID );
  switch ( s1?s1:s2 )
  {
  case 1:
    db( GET_HANDLE( b_nand ) );
    return 1;
    break;
  case 2:
    db( GET_HANDLE( w_nand ) );
    return 2;
    break;
  case 4:
    db( GET_HANDLE( d_nand ) );
    return 4;
    break;
#ifdef PROTECT_X64
  case 8:
    db( GET_HANDLE( q_nand ) );
    return 8;
    break;
#endif
  default:
    {
#ifdef PROTECT_X64
      db( GET_HANDLE( q_nand ) );
      return 8;
#else
      db( GET_HANDLE( d_nand ) );
      return 4;
#endif
    }
  }
  return 0;  
}

void SeniorVMHandle::b_or(long _register1,long _register2,bool is_data)
{
  b_not_and(_register1,_register2,is_data);
  pop(T_INVALID);
  b_not_and(_register1,_register2,is_data);
  pop(T_INVALID);
  db(HANDLE.b_nand.handle);
}

void SeniorVMHandle::w_or(long _register1,long _register2,bool is_data)
{
  w_not_and(_register1,_register2,is_data);
  pop(T_INVALID);
  w_not_and(_register1,_register2,is_data);
  pop(T_INVALID);
  db(HANDLE.w_nand.handle);
}

void SeniorVMHandle::d_or(long _register1,long _register2,bool is_data)
{
  d_not_and(_register1,_register2,is_data);
  pop(T_INVALID);
  d_not_and(_register1,_register2,is_data);
  pop(T_INVALID);
  db(HANDLE.d_nand.handle);
}
#ifdef PROTECT_X64
void SeniorVMHandle::q_or(long _register1,long _register2,bool is_data)
{
  q_not_and(_register1,_register2,is_data);
  pop(T_INVALID);
  q_not_and(_register1,_register2,is_data);
  pop(T_INVALID);
  db(HANDLE.q_nand.handle);
}
#endif

char SeniorVMHandle::v_or( pVOperand o1,pVOperand o2 )
{
  char s1 = v_not_and( o1,o2 );
  pop( T_INVALID );
  char s2 = v_not_and( o1,o2 );
  pop( T_INVALID );
  switch ( s1?s1:s2 )
  {
  case 1:
    db( GET_HANDLE( b_nand ) );
    return 1;
    break;
  case 2:
    db( GET_HANDLE( w_nand ) );
    return 2;
    break;
  case 4:
    db( GET_HANDLE( d_nand ) );
    return 4;
    break;
#ifdef PROTECT_X64
  case 8:
    db( GET_HANDLE( q_nand ) );
    return 8;
    break;
#endif
  default:
    {
#ifdef PROTECT_X64
      db( GET_HANDLE( q_nand ) );
      return 8;
#else
      db( GET_HANDLE( d_nand ) );
      return 4;
#endif
    }
  }
  return 0;  
}

void SeniorVMHandle::b_xor(long _register1,long _register2,bool is_data)
{
  b_not_and(_register1,_register2,is_data);
  pop(T_INVALID);
  b_and(_register1,_register2,is_data);
  pop(T_INVALID);
  db(HANDLE.b_nand.handle);
}

void SeniorVMHandle::w_xor(long _register1,long _register2,bool is_data)
{
  w_not_and(_register1,_register2,is_data);
  pop(T_INVALID);
  w_and(_register1,_register2,is_data);
  pop(T_INVALID);
  db(HANDLE.w_nand.handle);
}

void SeniorVMHandle::d_xor(long _register1,long _register2,bool is_data)
{
  d_not_and(_register1,_register2,is_data);
  pop(T_INVALID);
  d_and(_register1,_register2,is_data);
  pop(T_INVALID);
  db(HANDLE.d_nand.handle);
}
#ifdef PROTECT_X64
void SeniorVMHandle::q_xor(long _register1,long _register2,bool is_data)
{
  q_not_and(_register1,_register2,is_data);
  pop(T_INVALID);
  q_and(_register1,_register2,is_data);
  pop(T_INVALID);
  db(HANDLE.q_nand.handle);
}
#endif

char SeniorVMHandle::v_xor( pVOperand o1,pVOperand o2 )
{
  char s1 = v_not_and( o1,o2 );
  pop( T_INVALID );
  char s2 = v_and( o1,o2 );
  pop( T_INVALID );
  switch ( s1?s1:s2 )
  {
  case 1:
    db( GET_HANDLE( b_nand ) );
    return 1;
    break;
  case 2:
    db( GET_HANDLE( w_nand ) );
    return 2;
    break;
  case 4:
    db( GET_HANDLE( d_nand ) );
    return 4;
    break;
#ifdef PROTECT_X64
  case 8:
    db( GET_HANDLE( q_nand ) );
    return 8;
    break;
#endif
  default:
    {
#ifdef PROTECT_X64
      db( GET_HANDLE( q_nand ) );
      return 8;
#else
      db( GET_HANDLE( d_nand ) );
      return 4;
#endif
    }
  }
  return 0;    
}



void SeniorVMHandle::pushf()
{
  pcode->v_push_register(T_EFLAG);
}

void SeniorVMHandle::pushad()
{
  push(T_NAX);
  push(T_NCX);
  push(T_NDX);
  push(T_NBX);
  //  push(T_RSP | mode);
  push(T_NBP);
  push(T_NSI);
  push(T_NDI);
#ifdef PROTECT_X64
  push(T_R8);
  push(T_R9);
  push(T_R10);
  push(T_R11);
  push(T_R12);
  push(T_R13);
  push(T_R14);
  push(T_R15);  
#endif
}

void SeniorVMHandle::b_shl(long _register,char n,bool is_data)
{
  if ( is_data )
    b_push_imm( _register );
  else
    push(_register);
  b_push_imm(n);
  db(HANDLE.b_shl.handle);
}

void SeniorVMHandle::w_shl(long _register,char n,bool is_data)
{
  if ( is_data )
    w_push_imm( _register );
  else
    push(_register);
  b_push_imm(n);
  db(HANDLE.w_shl.handle);
}

void SeniorVMHandle::d_shl(long _register,char n,bool is_data)
{
  if ( is_data )
    d_push_imm( _register );
  else
    push(_register,false);
  b_push_imm(n);
  db(HANDLE.d_shl.handle);
}
#ifdef PROTECT_X64
void SeniorVMHandle::q_shl(long _register,char n,bool is_data)
{
  if ( is_data )
    q_push_imm( _register );
  else
    push(_register,false);
  b_push_imm(n);
  db(HANDLE.q_shl.handle);
}
#endif

char SeniorVMHandle::v_shl( pVOperand o1,pVOperand o2 )
{
  char s1 = push_operand(o1);
  char s2 = push_operand(o2);
  if ( s2 > 1 )
  {
    cout << "shl Second param is greater than cl" << endl;
    throw;
  }
  
  switch ( s1 )
  {
  case 1:
    db( GET_HANDLE( b_shl ) );
    return 1;
    break;
  case 2:
    db( GET_HANDLE( w_shl ) );
    return 2;
    break;
  case 4:
    db( GET_HANDLE( d_shl ) );
    return 4;
    break;
#ifdef PROTECT_X64
  case 8:
    db( GET_HANDLE( q_shl ) );
    return 8;
    break;
#endif
  default:
    {
#ifdef PROTECT_X64
      db( GET_HANDLE( q_shl ) );
      return 8;
#else
      db( GET_HANDLE( d_shl ) );
      return 4;
#endif
    }
  }
  return 0;      
}

void SeniorVMHandle::b_shr(long _register,char n,bool is_data)
{
  if ( is_data )
    b_push_imm( _register );
  else
    push(_register);
  b_push_imm(n);
  db(HANDLE.b_shr.handle);
}

void SeniorVMHandle::w_shr(long _register,char n,bool is_data)
{
  if ( is_data )
    w_push_imm( _register );
  else
    push(_register);
  b_push_imm(n);
  db(HANDLE.w_shr.handle);
}

void SeniorVMHandle::d_shr(long _register,char n,bool is_data)
{
  if ( is_data )
    d_push_imm( _register );
  else
    push(_register,false);
  b_push_imm(n);
  db(HANDLE.d_shr.handle);
}
#ifdef PROTECT_X64
void SeniorVMHandle::q_shr(long _register,char n,bool is_data)
{
  if ( is_data )
    q_push_imm( _register );
  else
    push(_register,false);
  b_push_imm(n);
  db(HANDLE.q_shr.handle);
}
#endif


char SeniorVMHandle::v_shr( pVOperand o1,pVOperand o2 )
{
  char s1 = push_operand(o1);
  char s2 = push_operand(o2);
  if ( s2 > 1 )
  {
    cout << "shr p2 is greater than cl" << endl;
    throw;
  }
  
  switch ( s1 )
  {
  case 1:
    db( GET_HANDLE( b_shr ) );
    return 1;
    break;
  case 2:
    db( GET_HANDLE( w_shr ) );
    return 2;
    break;
  case 4:
    db( GET_HANDLE( d_shr ) );
    return 4;
    break;
#ifdef PROTECT_X64
  case 8:
    db( GET_HANDLE( q_shr ) );
    return 8;
    break;
#endif
  default:
    {
#ifdef PROTECT_X64
      db( GET_HANDLE( q_shr ) );
      return 8;
#else
      db( GET_HANDLE( d_shr ) );
      return 4;
#endif
    }
  }
  return 0;      
}


void SeniorVMHandle::b_push_imm(char n)
{
  db(HANDLE.b_push_imm.handle);
  db(n);
}

void SeniorVMHandle::w_push_imm(short n)
{
  db(HANDLE.w_push_imm.handle);
  dw(n);
}

void SeniorVMHandle::d_push_imm(int n)
{
  db(HANDLE.d_push_imm.handle);
  dd(n);
}

void SeniorVMHandle::a_push_imm(long a)
{
#ifdef PROTECT_X64
  db(HANDLE.q_push_imm.handle);
  dq(a);
#else
  db(HANDLE.d_push_imm.handle);
  dd(a);
#endif
}

#ifdef PROTECT_X64
void SeniorVMHandle::q_push_imm(long n)
{
  db(HANDLE.q_push_imm.handle);
  dq(n);
}
#endif

char SeniorVMHandle::v_push_imm( pVOperand o1)
{
  return push_operand(o1);
}

void SeniorVMHandle::popad()
{
#ifdef PROTECT_X64
  pcode->v_pop_register(T_R15);
  pcode->v_pop_register(T_R14);
  pcode->v_pop_register(T_R13);
  pcode->v_pop_register(T_R12);
  pcode->v_pop_register(T_R11);
  pcode->v_pop_register(T_R10);
  pcode->v_pop_register(T_R9);
  pcode->v_pop_register(T_R8);
#endif
  
  int mode = 0;
#ifndef PROTECT_X64
  mode = T_E32X;
#endif
  pcode->v_pop_register(T_RDI | mode);
  pcode->v_pop_register(T_RSI | mode);
  pcode->v_pop_register(T_RBP | mode);
  //pcode->v_pop_register(T_RSP | mode);
  pcode->v_pop_register(T_RBX | mode);
  pcode->v_pop_register(T_RDX | mode);
  pcode->v_pop_register(T_RCX | mode);
  pcode->v_pop_register(T_RAX | mode);
}

void SeniorVMHandle::popf()
{
  pcode->v_pop_register(T_EFLAG);
}

void SeniorVMHandle::exit()
{
  //pcode->v_push_register(T_RET);
  pushf();
  pushad();
  db(HANDLE.ret.handle);
}

void SeniorVMHandle::start()
{
  //popad();
  //popf();
  //pop(T_KEY);
  //pop(T_RET);
  save_vm_context();
}

#define T_TMP_EFLAG T_TMP_REGISTER5

void SeniorVMHandle::b_add_b(long _register1,long _register2)
{
  d_push_imm(0);
  pop(T_TMP_REGISTER3);
  
  b_and(_register1,_register2);
  pop(T_INVALID);
  b_xor(_register1,_register2);
  pop(T_INVALID);
  pop(T_TMP_R8_1H);
  b_push_imm(1<<7);
  pop(T_TMP_R8_1L);
  pop(T_TMP_R8_2H);
  b_and(T_TMP_R8_2H,T_TMP_R8_1L);
  pop(T_INVALID);
  pop(T_TMP_R8_3L);
  d_shr(T_TMP_REGISTER3,7);
  pop(T_INVALID);
  pop(T_TMP_REGISTER3);
  d_or(T_TMP_REGISTER3,T_TMP_EFLAG);
  pop(T_INVALID);
  pop(T_TMP_EFLAG);

  d_push_imm(0);
  pop(T_TMP_REGISTER3);
  
  b_push_imm(1<<3);
  pop(T_TMP_R8_3H);
  b_and(T_TMP_R8_3H,T_TMP_R8_2H);
  pop(T_INVALID);
  pop(T_TMP_R8_2L);
  
  b_shl(T_TMP_R8_2L,1);
  pop(T_INVALID);
  pop(T_TMP_R8_3L);
  d_or(T_TMP_REGISTER3,T_TMP_EFLAG);
  pop(T_INVALID);
  pop(T_TMP_EFLAG);
  b_shl(T_TMP_R8_2H,1);
  pop(T_INVALID);
  pop(T_TMP_R8_2H);
}

void SeniorVMHandle::b_add(long _register1,long _register2,bool is_data)
{
  push(_register1);
  if ( is_data )
    b_push_imm( _register2 );
  else
    push(_register2);
  db(HANDLE.b_add.handle);
}

char SeniorVMHandle::v_add( pVOperand o1,pVOperand o2 )
{
  char s1 = push_operand(o1);
  char s2 = push_operand(o2);
  
  switch ( s1 )
  {
  case 1:
    db( GET_HANDLE( b_add ) );
    return 1;
    break;
  case 2:
    db( GET_HANDLE( w_add ) );
    return 2;
    break;
  case 4:
    db( GET_HANDLE( d_add ) );
    return 4;
    break;
#ifdef PROTECT_X64
  case 8:
    db( GET_HANDLE( q_add ) );
    return 8;
    break;
#endif
  default:
    {
#ifdef PROTECT_X64
      db( GET_HANDLE( q_add ) );
      return 8;
#else
      db( GET_HANDLE( d_add ) );
      return 4;
#endif
    }
  }  
}
  

void SeniorVMHandle::w_add(long _register1,long _register2,bool is_data)
{
  push(_register1);
  if ( is_data )
    w_push_imm( _register2 );
  else
    push(_register2);
  db(HANDLE.w_add.handle);
}

void SeniorVMHandle::d_add_d(long _register1,long _register2)
{
  d_and(_register1,_register2);  //8
  pcode->v_pop_register(T_INVALID); //4
  
  d_xor(_register1,_register2); 
  pcode->v_pop_register(T_INVALID); //4
  //pcode->v_pop_register(T_TMPconst T_TMP_R8_3H_R8_1L);
  pcode->v_pop_register(T_TMP_REGISTER1);


  ///这里保存CF 判断是否进位
  // pcode->v_push_register(T_TMP_REGISTER4);

  db(HANDLE.d_push_imm.handle); // var1 = 1<<31
  dd(1<<31);  //8
  pcode->v_pop_register(T_TMP_REGISTER4); //4
  pcode->v_pop_register(T_TMP_REGISTER3);//AND结果 0
  
  d_and(T_TMP_REGISTER4,T_TMP_REGISTER3); //8
  pcode->v_pop_register(T_INVALID); //4
 
  db(HANDLE.b_push_imm.handle);
  db(31);
  db(HANDLE.d_shr.handle);
  pcode->v_pop_register(T_INVALID);
  
  pcode->v_pop_register(T_TMP_REGISTER4);//AND结果  //0
  d_or(T_TMP_REGISTER4,T_TMP_EFLAG); 
  pcode->v_pop_register(T_INVALID);
    
  pcode->v_pop_register(T_TMP_EFLAG); //0
  ///end

  ///这里保存AF 判断bit3是否进位到bit4
  db(HANDLE.d_push_imm.handle);
  dd(1<<3);
  pcode->v_pop_register(T_TMP_REGISTER4);
  d_and(T_TMP_REGISTER4,T_TMP_REGISTER3); //8
  pcode->v_pop_register(T_INVALID);

  db(HANDLE.b_push_imm.handle); //左移一位
  db(1);
  db(HANDLE.d_shl.handle);
  
  pcode->v_pop_register(T_INVALID);
  
  pcode->v_pop_register(T_TMP_REGISTER4); //0

  
  d_or(T_TMP_REGISTER4,T_TMP_EFLAG); //8
  pcode->v_pop_register(T_INVALID);
  pcode->v_pop_register(T_TMP_EFLAG); //0*/
  
  //pcode->v_pop_register(T_INVALID); //第一个and的标志位
  pcode->v_push_register(T_TMP_REGISTER3);
  db(HANDLE.b_push_imm.handle);
  db(1);
  db(HANDLE.d_shl.handle);
  pcode->v_pop_register(T_INVALID);
  pcode->v_pop_register(T_TMP_REGISTER2);  
}

//OF 原本是0 结果变成1 或者相反    = 1 否这 = 0
//CF 超出能数值表示范围 至 = 1
//AF

void SeniorVMHandle::d_add(long _register1,long _register2,bool is_data)
{
  if (!super_protect)
  {
    push(_register1,false);
    if ( is_data )
      d_push_imm( _register2 );
    else
      push(_register2,false);
    db(HANDLE.d_add.handle);
    return;
  }

  //return;
  
  /*  db(HANDLE.d_push_imm.handle);
  dd(1<<31);
  pcode->v_pop_register(T_TMP_REGISTER3);
  d_and(_register1,T_TMP_REGISTER3);
  pcode->v_pop_register(T_INVALID);
  db(HANDLE.b_push_imm.handle);
  db(20);
  db(HANDLE.d_shr.handle);
  pcode->v_pop_register(T_INVALID);
  pcode->v_pop_register(T_TMP_EFLAG);*/
  d_xor(_register1,_register2);
  pcode->v_pop_register(T_INVALID);
  pcode->v_pop_register(T_TMP_REGISTER1);
  d_not(T_TMP_REGISTER1);
  pcode->v_pop_register(T_INVALID);
  db(HANDLE.d_push_imm.handle);
  dd(0x80000000);
  pcode->v_pop_register(T_TMP_REGISTER2);
  pcode->v_pop_register(T_TMP_REGISTER3);
  d_and(T_TMP_REGISTER3,T_TMP_REGISTER2);
  pcode->v_pop_register(T_INVALID);
  //  db(HANDLE.b_push_imm.handle);
  //  db(20);
  //  db(HANDLE.d_shr.handle);
  //  pcode->v_pop_register(T_INVALID);
  pcode->v_pop_register(T_TMP_EFLAG);
  
  d_add_d(_register1,_register2);
 for (int i = 0; i < 31; ++i) //6次 留一次填充标志位
 {
    d_add_d(T_TMP_REGISTER2,T_TMP_REGISTER1);
 }
//pcode->v_push_register(T_TMP_R32_2);
// pcode->v_push_register(T_TMP_EFLAG);
 //pcode->v_push_register(T_TMP_REGISTER1);

  ///OF 判断是否溢出


  d_xor(_register2,T_TMP_REGISTER1);
 pcode->v_pop_register(T_INVALID);
 pcode->v_pop_register(T_TMP_REGISTER3);
 db(HANDLE.d_push_imm.handle);
 dd(0x80000000);
 pcode->v_pop_register(T_TMP_REGISTER4);
 d_and(T_TMP_REGISTER4,T_TMP_REGISTER3);
 pcode->v_pop_register(T_INVALID);
 pcode->v_pop_register(T_TMP_REGISTER3);

 d_and(T_TMP_EFLAG,T_TMP_REGISTER3);
 pcode->v_pop_register(T_INVALID);
 
 db(HANDLE.b_push_imm.handle);
 db(20);
 db(HANDLE.d_shr.handle);
 
 pcode->v_pop_register(T_INVALID);
 pcode->v_pop_register(T_TMP_REGISTER4);
 //db(HANDLE.d_push_imm.handle);
 //dd(0x800);
 //pcode->v_pop_register(T_TMP_REGISTER3);
 // d_and(T_TMP_REGISTER3,T_TMP_REGISTER4);
 // pcode->v_pop_register(T_INVALID);
 //pcode->v_pop_register(T_TMP_REGISTER3);
 //d_and(T_TMP_EFLAG,T_TMP_REGISTER3); //这时候的OF还在最高位
 //pcode->v_pop_register(T_INVALID);
 //pcode->v_pop_register(T_TMP_REGISTER3);
 //db(HANDLE.d_push_imm.handle);
 //dd(0xFFFFF7FF);
 //pcode->v_pop_register(T_TMP_REGISTER3);
 //d_or(T_TMP_REGISTER3,T_TMP_REGISTER4);
 //pcode->v_pop_register(T_INVALID);
 //pcode->v_pop_register(T_TMP_REGISTER4);
 
 d_or(T_TMP_EFLAG,T_TMP_REGISTER4);
 pcode->v_pop_register(T_INVALID);
 pcode->v_pop_register(T_TMP_EFLAG);
 /*pcode->v_push_register(T_TMP_EFLAG); 
 db(HANDLE.push_esp.handle);
 db(HANDLE.d_read_mem.handle); 
 pcode->v_pop_register(T_TMP_EFLAG);
 db(HANDLE.b_push_imm.handle);
 db(20);
 db(HANDLE.d_shl.handle);
 pcode->v_pop_register(T_INVALID);
 pcode->v_pop_register(T_TMP_REGISTER3);
 
 d_xor(_register1,T_TMP_REGISTER3);
 pcode->v_pop_register(T_INVALID);
 //pcode->v_pop_register(T_TMP_REGISTER3);
  db(HANDLE.b_push_imm.handle);
 db(20);
 db(HANDLE.d_shr.handle);
 pcode->v_pop_register(T_INVALID);
 pcode->v_pop_register(T_TMP_REGISTER4);
 db(HANDLE.d_push_imm.handle);
 dd(0x800);
 pcode->v_pop_register(T_TMP_REGISTER3);
 d_and(T_TMP_REGISTER3,T_TMP_REGISTER4);
 pcode->v_pop_register(T_INVALID);
 pcode->v_pop_register(T_TMP_REGISTER3);
 d_and(T_TMP_EFLAG,T_TMP_REGISTER3);
 pcode->v_pop_register(T_INVALID);
 pcode->v_pop_register(T_TMP_REGISTER3);
 d_or(T_TMP_EFLAG,T_TMP_REGISTER3);
 pcode->v_pop_register(T_INVALID);
 pcode->v_pop_register(T_TMP_EFLAG);*/
 /////end OF
  d_and(T_TMP_REGISTER1,T_TMP_REGISTER1);
  pcode->v_pop_register(T_TMP_REGISTER2); //EFLAG
  d_or(T_TMP_EFLAG,T_TMP_REGISTER2);
  pcode->v_pop_register(T_INVALID);
  /* 
  pcode->v_push_register(T_TMP_EFLAG);
  db(HANDLE.push_esp.handle);
  db(HANDLE.d_read_mem.handle);
  pcode->v_pop_register(T_TMP_EFLAG);
  db(HANDLE.b_push_imm.handle);
  db(31);
  db(HANDLE.d_shr.handle);
  pcode->v_pop_register(T_INVALID);
  pcode->v_pop_register(T_TMP_REGISTER3);
  d_or(T_TMP_REGISTER3,T_TMP_REGISTER2);
  pcode->v_pop_register(T_INVALID);
  /*  pcode->v_pop_register(T_TMP_REGISTER2);
  
  pcode->v_push_register(T_TMP_EFLAG);
  db(HANDLE.push_esp.handle);
  db(HANDLE.d_read_mem.handle);
  pcode->v_pop_register(T_TMP_EFLAG);
  db(HANDLE.b_push_imm.handle);
  db(3);
  db(HANDLE.d_shr.handle);
  pcode->v_pop_register(T_INVALID);
  pcode->v_pop_register(T_TMP_REGISTER3);
  d_and(T_TMP_REGISTER3,T_TMP_REGISTER2);
  pcode->v_pop_register(T_INVALID);
  pcode->v_pop_register(T_TMP_REGISTER2);

  pcode->v_push_register(T_TMP_EFLAG);
  db(HANDLE.d_push_imm.handle);
  db(1<<11);
  pcode->v_pop_register(T_TMP_REGISTER3);
  d_xor(T_TMP_REGISTER3,T_TMP_REGISTER2);
  pcode->v_pop_register(T_INVALID);
  //pcode->v_push_register(T_TMP_REGISTER3);
  pcode->v_pop_register(T_TMP_REGISTER4);
  d_and(T_TMP_REGISTER3,T_TMP_REGISTER4);
  pcode->v_pop_register(T_INVALID);
  pcode->v_pop_register(T_TMP_REGISTER4);
  d_or(T_TMP_REGISTER4,T_TMP_REGISTER2);
  pcode->v_pop_register(T_INVALID);*/
  
//db(HANDLE.push_esp.handle);
//db(HANDLE.d_read_mem.handle);

//  pcode->v_pop_register(T_EAX);
}
#ifdef PROTECT_X64
void SeniorVMHandle::q_add(long _register1,long _register2,bool is_data)
{
  push(_register1);
  if ( is_data )
    q_push_imm( _register2 );
  else
    push(_register2);
  db(HANDLE.q_add.handle);
}
#endif



void SeniorVMHandle::b_push_imm_sx(char n)
{
  db(HANDLE.b_push_imm_sx.handle);
  db(n);
}

void SeniorVMHandle::w_push_imm_sx(short n)
{
  db(HANDLE.w_push_imm_sx.handle);
  dw(n);
}
#ifdef PROTECT_X64
void SeniorVMHandle::d_push_imm_sx(int n)
{
  db(HANDLE.d_push_imm_sx.handle);
  dd(n);
}
#endif
void SeniorVMHandle::b_push_imm_zx(char n)
{
  db(HANDLE.b_push_imm_zx.handle);
  db(n);
}

void SeniorVMHandle::w_push_imm_zx(short n)
{
  db(HANDLE.w_push_imm_zx.handle);
  dw(n);
}
#ifdef PROTECT_X64
void SeniorVMHandle::d_push_imm_zx(int n)
{
  db(HANDLE.d_push_imm_zx.handle);
  dd(n);
}
#endif
void SeniorVMHandle::b_copy_stack()
{
  db(HANDLE.push_esp.handle);
  db(HANDLE.b_read_mem.handle);
}

void SeniorVMHandle::w_copy_stack()
{
  db(HANDLE.push_esp.handle);
  db(HANDLE.w_read_mem.handle);
}

void SeniorVMHandle::d_copy_stack()
{
  db(HANDLE.push_esp.handle);
  db(HANDLE.d_read_mem.handle);
}
#ifdef PROTECT_X64
void SeniorVMHandle::q_copy_stack()
{
  db(HANDLE.push_esp.handle);
  db(HANDLE.q_read_mem.handle);
}
#endif

void SeniorVMHandle::b_read_mem(  )
{
  db( GET_HANDLE( b_read_mem ) );
}

void SeniorVMHandle::w_read_mem(  )
{
  db( GET_HANDLE( w_read_mem ) );
}

void SeniorVMHandle::d_read_mem(  )
{
  db( GET_HANDLE( d_read_mem ) );
}

#ifdef PROTECT_X64
void SeniorVMHandle::q_read_mem(  )
{
  db( GET_HANDLE( q_read_mem ) );
}
#endif

void SeniorVMHandle::b_write_mem(  )
{
  db( GET_HANDLE( b_write_mem ) );
}

void SeniorVMHandle::w_write_mem(  )
{
  db( GET_HANDLE( w_write_mem ) );
}

void SeniorVMHandle::d_write_mem(  )
{
  db( GET_HANDLE( d_write_mem ) );
}

#ifdef PROTECT_X64
void SeniorVMHandle::q_write_mem(  )
{
  db( GET_HANDLE( q_write_mem ) );
}
#endif

/* 
char SeniorVMHandle::v_sub( pVOperand o1,pVOperand o2 )
{
  //char s1 = push_operand(o1);
  char s2 = push_operand(o2);
  
  switch ( s1 )
  {
  case 1:
    db( GET_HANDLE( b_sub ) );
    return 1;
    break;
  case 2:
    db( GET_HANDLE( w_sub ) );
    return 2;
    break;
  case 4:
    db( GET_HANDLE( d_sub ) );
    return 4;
    break;
#ifdef PROTECT_X64
  case 8:
    db( GET_HANDLE( q_sub ) );
    return 8;
    break;
#endif
  default:
    {
#ifdef PROTECT_X64
      db( GET_HANDLE( q_sub) );
      return 8;
#else
      db( GET_HANDLE( d_sub ) );
      return 4;
#endif
    }
  }  
}  */
  
                       


void SeniorVMHandle::b_sub(long _register1,long _register2)
{
  b_not(_register1);
  pop(T_INVALID);
  pop(T_TMP_R8_8L);
  b_add(T_TMP_R8_8L,_register2);
  //  pop(T_INVALID);
  pop(T_TMP_REGISTER6); //eflag 1
  b_copy_stack();
  b_not_and();
  pop(T_TMP_REGISTER7); //eflag 2 
  //pop(T_TMP_REGISTER8); //结果

  d_not(T_TMP_REGISTER6);
  pop(T_INVALID);
  w_push_imm_sx(0xf7ea);
  d_not_and();
  pop(T_INVALID);
  pop(T_TMP_REGISTER6);
  
  d_not(T_TMP_REGISTER7);
  pop(T_INVALID);
  w_push_imm_sx(0x815);
  d_not_and();
  pop(T_INVALID);
  pop(T_TMP_REGISTER7);
  d_add(T_TMP_REGISTER6,T_TMP_REGISTER7);
  pop(T_INVALID);
}

void SeniorVMHandle::w_sub(long _register1,long _register2)
{
  w_not(_register1);  //sub eax,ebx = add((not eax),ebx) 
  pop(T_INVALID);
  pop(T_TMP_R16_8);
  b_add(T_TMP_R16_8,_register2);
  //  pop(T_INVALID);
  pop(T_TMP_REGISTER6); //eflag 1
  w_copy_stack();
  w_not_and();
  pop(T_TMP_REGISTER7); //eflag 2 
  //pop(T_TMP_REGISTER8); //结果

  d_not(T_TMP_REGISTER6);
  pop(T_INVALID);
  w_push_imm_sx(0xf7ea);
  d_not_and();
  pop(T_INVALID);
  pop(T_TMP_REGISTER6);
  
  d_not(T_TMP_REGISTER7);
  pop(T_INVALID);
  w_push_imm_sx(0x815);
  d_not_and();
  pop(T_INVALID);
  pop(T_TMP_REGISTER7);
  d_add(T_TMP_REGISTER6,T_TMP_REGISTER7);
  pop(T_INVALID);
}

void SeniorVMHandle::d_sub(long _register1,long _register2)
{
  d_not(_register1);
  pop(T_INVALID);
  pop(T_TMP_REGISTER8);
  d_add(T_TMP_REGISTER8,_register2);
  //  pop(T_INVALID);
  pop(T_TMP_REGISTER6); //eflag 1
  d_copy_stack();
  d_not_and();
  pop(T_TMP_REGISTER7); //eflag 2 
  //pop(T_TMP_REGISTER8); //结果

  d_not(T_TMP_REGISTER6);
  pop(T_INVALID);
  w_push_imm_sx(0xf7ea);
  d_not_and();
  pop(T_INVALID);
  pop(T_TMP_REGISTER6);
  
  d_not(T_TMP_REGISTER7);
  pop(T_INVALID);
  w_push_imm_sx(0x815);
  d_not_and();
  pop(T_INVALID);
  pop(T_TMP_REGISTER7);
  d_add(T_TMP_REGISTER6,T_TMP_REGISTER7);
  pop(T_INVALID);
}
#ifdef PROTECT_X64
void SeniorVMHandle::q_sub(long _register1,long _register2)
{
  q_not(_register1);
  pop(T_INVALID);
  pop(T_TMP_REGISTER8);
  q_add(T_TMP_REGISTER8,_register2);
  //  pop(T_INVALID);
  pop(T_TMP_REGISTER6); //eflag 1
  q_copy_stack();
  q_not_and();
  pop(T_TMP_REGISTER7); //eflag 2 
  //pop(T_TMP_REGISTER8); //结果

  q_not(T_TMP_REGISTER6);
  pop(T_INVALID);
  w_push_imm_sx(0xf7ea);
  q_not_and();
  pop(T_INVALID);
  pop(T_TMP_REGISTER6);
  
  q_not(T_TMP_REGISTER7);
  pop(T_INVALID);
  w_push_imm_sx(0x815);
  q_not_and();
  pop(T_INVALID);
  pop(T_TMP_REGISTER7);
  q_add(T_TMP_REGISTER6,T_TMP_REGISTER7);
  pop(T_INVALID);
}
#endif

void SeniorVMHandle::b_cmp(long _register1,long _register2)
{
  b_sub(_register1,_register2);
  pop(T_EFLAG);
  pop(T_INVALID8H);
}

void SeniorVMHandle::w_cmp(long _register1,long _register2)
{
  w_sub(_register1,_register2);
  pop(T_EFLAG);
  pop(T_INVALID16);
}

void SeniorVMHandle::d_cmp(long _register1,long _register2)
{
  d_sub(_register1,_register2);
  pop(T_EFLAG);
  pop(T_INVALID32);
}

#ifdef PROTECT_X64
void SeniorVMHandle::q_cmp(long _register1,long _register2)
{
  q_sub(_register1,_register2);
  pop(T_EFLAG);
  pop(T_INVALID);
}
#endif

//带r的表示real真实的
//比如这条指令计算真正的内存地址

void SeniorVMHandle::r_get_mem(
                                  long _register_base,
                                  long _register_index,
                                  long _scale,
                                  long _lval)
{
  if (_register_base == T_NSP)
  {
    db( GET_HANDLE( push_esp ) );
    pop( T_ESP );
  }
  d_push_imm( _lval );
  pop( T_TMP_REGISTER4 );
  if ( _register_index ) {
    char sn = 0;
    for (int i = 0; i < 32; i++)
    {
      if (_scale == 1<<i)
      {
        sn = i;
        break;
      }
    }
    d_shl( _register_index,sn );
    pop( T_INVALID );
    pop( T_TMP_REGISTER5 );
    d_add(T_TMP_REGISTER4,T_TMP_REGISTER5  );
    pop( T_INVALID );
    pop( T_TMP_REGISTER4 );
  }
  if (_register_base)
  {
    d_add( _register_base,T_TMP_REGISTER4 );
    pop( T_INVALID );
  }
}


void SeniorVMHandle::push_vesp(  )
{
  db( GET_HANDLE( push_esp ) );
}


void SeniorVMHandle::db( unsigned char b)
{
  pcode->db( b );
}

void SeniorVMHandle::dw( unsigned short w )
{
  pcode->dw( w );
}

void SeniorVMHandle::dd( unsigned int d )
{
  pcode->dd( d );
}

#ifdef PROTECT_X64
void SeniorVMHandle::dq( unsigned long q )
{
  pcode->dq( q );
}
#endif

void SeniorVMHandle::set_pc(  )
{
  db( GET_HANDLE( set_pc ) );
}

void SeniorVMHandle::set_key( long _key )
{
  //recover_vm_context();
#ifndef PROTECT_X64
  d_push_imm( _key  );
#else
  q_push_imm( _key  );
#endif
  db( GET_HANDLE( set_key ) );
}

void SeniorVMHandle::mov(pVOperand o1,pVOperand o2)
{
  
}

void SeniorVMHandle::test(pVOperand o1,pVOperand o2)
{
  v_and(o1,o2);
  pop(T_EFLAG);
  pop(T_INVALID);
}


void SeniorVMHandle::lea(pVOperand o1,pVOperand o2)
{
}

void SeniorVMHandle::cmp(pVOperand o1,pVOperand o2)
{
}

void SeniorVMHandle::sar(pVOperand o1,pVOperand o2)
{
}

void SeniorVMHandle::cdq(pVOperand o1)
{
}

void SeniorVMHandle::div(pVOperand o1)
{
}


void SeniorVMHandle::sar(pVOperand o1)
{
}

void SeniorVMHandle::imul(pVOperand o1,pVOperand o2,pVOperand o3)
{
}

void SeniorVMHandle::jnz(long addr1,long addr2)
{
}

void SeniorVMHandle::jz(long addr1,long addr2)
{
}
