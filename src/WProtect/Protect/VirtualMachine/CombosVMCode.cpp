/************************************************************
 *                                                         *
 *                                                        *
 *                2015年7月31日                          *
 *                             By:XiaoWei               *
 *                                                     *
 *                                                    *
 *****************************************************/

#include "CombosVMCode.hpp"
#include <WProtectConfig.h>
#include <algorithms>

#define get_handle(x) ptr_pcode->pcode_info.handle_table.x.handle
#define build_vm_mnemonic(x) build_byte_code(x) 

VCombosVMCode::VCombosVMCode()
    :super_protect(false),ptr_pcode(NULL),change_vmregister_flag(true)
{
    memset(&tmp_vmregister_status,false,sizeof(tmp_vmregister_status)); 
}

VCombosVMCode::VCombosVMCode(PCode * p)
    :super_protect(false),ptr_pcode(NULL),change_vmregister_flag(true)
{
    if (ptr_pcode)
        printf("ptr_pcode is Empty");
    ptr_pcode = p;
    memset(&tmp_vmregister_status,false,sizeof(tmp_vmregister_status));  
}

VCombosVMCode::~VCombosVMCode()
{
    
}

void VCombosVMCode::set_vmregister_store_in(RegisterStore & store_in)
{
    ptr_pcode->register_store_in = store_in;
}

void VCombosVMCode::set_vmregister_store_out(RegisterStore & store_out)
{
    ptr_pcode->register_store_out = store_out;
}

void *VCombosVMCode::get_code_buf()
{
  if ( ptr_pcode->pcode_info.sign == false)
     return &ptr_pcode->pcode_info.buf
    [ptr_pcode->pcode_info.size - ptr_pcode->pcode_info.offset];
  else
    return ptr_pcode->pcode_info.buf; 
}

long VCombosVMCode::get_code_size()
{
 return ptr_pcode->get_code_size(  );    
}

#define push_esp push_stack_top_base                         
                                                             



void VCombosVMCode::save_vm_context()
{
   int register_count = ptr_pcode->register_store_in.register_count;
   for (int i = register_count; i > 0; --i)
   {
    pop(ptr_pcode->register_store_in.register_array[i-1]);
   }
}

void VCombosVMCode::recover_vm_context()
{
  int register_count = ptr_pcode->register_store_out.register_count;

  for (int i = 0; i < register_count; ++i)
  {
    if (ptr_pcode->register_store_out.register_array[ i ] ==  T_NAX ||
        ptr_pcode->register_store_out.register_array[ i ] ==  T_NBX ||
        ptr_pcode->register_store_out.register_array[ i ] ==  T_NCX ||
        ptr_pcode->register_store_out.register_array[ i ] ==  T_NDX ||
        ptr_pcode->register_store_out.register_array[ i ] ==  T_NSP ||
        ptr_pcode->register_store_out.register_array[ i ] ==  T_NBP ||
        ptr_pcode->register_store_out.register_array[ i ] ==  T_NSI ||
        ptr_pcode->register_store_out.register_array[ i ] ==  T_NDI ||
#ifdef PROTECT_X64
        ptr_pcode->register_store_out.register_array[ i ] ==  T_NAX | T_RN ||
        ptr_pcode->register_store_out.register_array[ i ] ==  T_NBX | T_RN ||
        ptr_pcode->register_store_out.register_array[ i ] ==  T_NCX | T_RN ||
        ptr_pcode->register_store_out.register_array[ i ] ==  T_NDX | T_RN ||
        ptr_pcode->register_store_out.register_array[ i ] ==  T_NSP | T_RN ||
        ptr_pcode->register_store_out.register_array[ i ] ==  T_NBP | T_RN ||
        ptr_pcode->register_store_out.register_array[ i ] ==  T_NSI | T_RN ||
        ptr_pcode->register_store_out.register_array[ i ] ==  T_NDI | T_RN ||
#endif
        ptr_pcode->register_store_out.register_array[ i ] ==  T_RET ||
        ptr_pcode->register_store_out.register_array[ i ] ==  T_KEY ||
        ptr_pcode->register_store_out.register_array[ i ] ==  T_EFLAG)
        push( ptr_pcode->register_store_out.register_array[ i ] );
  }    
}

void VCombosVMCode::upset_register_array(RegisterStore & r )
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
  //r.register_array[ register_count++ ] = T_RET;
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

void VCombosVMCode::run_stack()
{
    build_vm_mnemonic(get_handle(run_stack));
}

void VCombosVMCode::push_vsp()  //vm_stack_point 虚拟机堆栈指针
{
    build_vm_mnemonic(get_handle(push_stack_top_base));
} 

void VCombosVMCode::pop_vsp()
{
    build_vm_mnemonic(get_handle(pop_stack_top_base));
}

void VCombosVMCode::pushf()
{
    push(T_FLAG);
}

void VCombosVMCode::popf()
{
    pop(T_FLAG);
}

void VCombosVMCode::push(long _register,bool _disable)
{
  ptr_pcode->v_push_register(_register,_disable);
}

void VCombosVMCode::push(long _register)
{
  ptr_pcode->v_push_register(_register,change_vmregister_flag); 
}

void VCombosVMCode::pop(long _register)
{
    ptr_pcode->v_pop_register(_register);
}

void VCombosVMCode::b_push_imm(char b)
{
    build_vm_mnemonic(get_handle(b_push_imm));
    build_byte_code(b);
}

void VCombosVMCode::w_push_imm(short w)
{
    build_vm_mnemonic(get_handle(w_push_imm));
    build_word_code(w);
}

void VCombosVMCode::d_push_imm(int d)
{
    build_vm_mnemonic(get_handle(d_push_imm));
    build_dword_code(d);
}

#ifdef PROTECT_X64
void VCombosVMCode::q_push_imm(long q)
{
    build_vm_mnemonic(get_handle(q_push_imm));
    build_qword_code(q);
}
#endif
    
void VCombosVMCode::b_push_imm_sx(char b)
{
    build_vm_mnemonic(get_handle(b_push_imm_sx));
    build_byte_code(b);
}

void VCombosVMCode::w_push_imm_sx(short w)
{
    build_vm_mnemonic(get_handle(w_push_imm_sx));
    build_word_code(w);
}

#ifdef PROTECT_X64
void VCombosVMCode::d_push_imm_sx(int d)
{
    build_vm_mnemonic(get_handle(d_push_imm_sx));
    build_dword_code(d);
}
#endif
 
void VCombosVMCode::b_push_imm_zx(char b)
{
    build_vm_mnemonic(get_handle(b_push_imm_zx));
    build_byte_code(b);
}

void VCombosVMCode::w_push_imm_zx(short w)
{
    build_vm_mnemonic(get_handle(w_push_imm_zx));
    build_word_code(w);
}

#ifdef PROTECT_X64
void VCombosVMCode::d_push_imm_zx(int d)
{
    build_vm_mnemonic(get_handle(d_push_imm_zx));
    build_dword_code(d);
}
#endif

void VCombosVMCode::b_nand()
{
    build_vm_mnemonic(get_handle(b_nand));
}

void VCombosVMCode::w_nand()
{
    build_vm_mnemonic(get_handle(w_nand));
}

void VCombosVMCode::d_nand()
{
    build_vm_mnemonic(get_handle(d_nand));
}

#ifdef PROTECT_X64
void VCombosVMCode::q_nand()
{
    build_vm_mnemonic(get_handle(q_nand));
}
#endif

void VCombosVMCode::b_not()
{
    build_vm_mnemonic(get_handle(push_stack_top_base));
    build_vm_mnemonic(get_handle(b_read_mem));
    build_vm_mnemonic(get_handle(b_nand));
}

void VCombosVMCode::w_not()
{
    build_vm_mnemonic(get_handle(push_stack_top_base));
    build_vm_mnemonic(get_handle(w_read_mem));
    build_vm_mnemonic(get_handle(w_nand));
}

void VCombosVMCode::d_not()
{
    build_vm_mnemonic(get_handle(push_stack_top_base));
    build_vm_mnemonic(get_handle(d_read_mem));
    build_vm_mnemonic(get_handle(d_nand));
}

#ifdef PROTECT_X64
void VCombosVMCode::q_not()
{
    build_vm_mnemonic(get_handle(push_stack_top_base));
    build_vm_mnemonic(get_handle(q_read_mem));
    build_vm_mnemonic(get_handle(q_nand));
} 
#endif 

void VCombosVMCode::b_neg()
{
    b_push_imm(0);
    b_sub();
    //pop(T_INVALID)
}

void VCombosVMCode::w_neg()
{
    w_push_imm(0);
    w_sub();
}

void VCombosVMCode::d_neg()
{
    d_push_imm(0);
    d_sub();
}

void VCombosVMCode::b_add()
{
   build_vm_mnemonic(get_handle(b_add));
}                                       
void VCombosVMCode::w_add()
{
   build_vm_mnemonic(get_handle(w_add));
}                                        
void VCombosVMCode::d_add()
{
   build_vm_mnemonic(get_handle(d_add));
}                                         
#ifdef PROTECT_X64
void VCombosVMCode::q_add()
{
   build_vm_mnemonic(get_handle(q_add));
}      
#endif

void VCombosVMCode::b_read_mem()
{
    build_vm_mnemonic(get_handle(b_read_mem));
}

void VCombosVMCode::w_read_mem()
{
    build_vm_mnemonic(get_handle(w_read_mem));
}

void VCombosVMCode::d_read_mem()
{
    build_vm_mnemonic(get_handle(d_read_mem));
}

#ifdef PROTECT_X64
void VCombosVMCode::q_read_mem()
{
    build_vm_mnemonic(get_handle(q_read_mem));
}
#endif

 void VCombosVMCode::b_write_mem()
{
    build_vm_mnemonic(get_handle(b_write_mem));
}

void VCombosVMCode::w_write_mem()
{
    build_vm_mnemonic(get_handle(w_write_mem));
}

void VCombosVMCode::d_write_mem()
{
    build_vm_mnemonic(get_handle(d_write_mem));
}

#ifdef PROTECT_X64
void VCombosVMCode::q_write_mem()
{
    build_vm_mnemonic(get_handle(q_write_mem));
}
#endif 

void VCombosVMCode::build_byte_code(unsigned char b)
{
    ptr_pcode->db( b );
}

void VCombosVMCode::build_word_code(unsigned short w)
{
    ptr_pcode->dw( w );
}

void VCombosVMCode::build_dword_code(unsigned int d)
{
    ptr_pcode->dd( d );
}

#ifdef PROTECT_X64
void VCombosVMCode::build_qword_code(unsigned long q)
{
    ptr_pcode->dq( q );
}
#endif


void VCombosVMCode::set_pc(long _key)
{
#ifndef PROTECT_X64
    d_push_imm(_key);
#else
    q_push_imm(_key);
#endif
    build_vm_mnemonic(get_handle(set_key));
}


void VCombosVMCode::set_pc()
{
    build_vm_mnemonic(get_handle(set_pc));
}


void VCombosVMCode::b_shl()
{
    build_vm_mnemonic(get_handle(b_shl));
}

void VCombosVMCode::w_shl()
{
    build_vm_mnemonic(get_handle(w_shl));
}

void VCombosVMCode::d_shl()
{
    build_vm_mnemonic(get_handle(d_shl));
}

#ifdef PROTECT_X64
void VCombosVMCode::q_shl()
{
    build_vm_mnemonic(get_handle(q_shl));
}
#endif

 
void VCombosVMCode::b_shr()
{
    build_vm_mnemonic(get_handle(b_shr));
}

void VCombosVMCode::w_shr()
{
    build_vm_mnemonic(get_handle(w_shr));
}

void VCombosVMCode::d_shr()
{
    build_vm_mnemonic(get_handle(d_shr));
}

#ifdef PROTECT_X64
void VCombosVMCode::q_shr()
{
    build_vm_mnemonic(get_handle(q_shr));
}
#endif                      


void VCombosVMCode::b_sar()
{
    /*
    * sar 10101110,2
    * 最高位 = 1
    * 11111111  sub 0,最高位 -> diff
    * 11111000  shl diff << 右移位数 + 1
    * 11111001  add diff,最高位
    * 00000111  neg diff
    * 11100000  shl diff,目标操作数位数(7) - 右移位数 + 1
    * shr 目标操作数,右移位数
    * add 目标操作数,diff
    */
    int dest_reg = get_tmp_vmregister();
    int highest_bit = get_tmp_vmregister();
    int count_reg = get_tmp_vmregister();
    int tmp_cf_reg = get_tmp_vmregister();

    pop(count_reg|T_E32X|T_16X|T_8H);//save count
    //and o1,10000000b
    push_vsp();
    b_read_mem(); //copy dest
    pop(dest_reg|T_E32X|T_16X|T_8H); //save dest
    b_push_imm(1<<7);
    b_and();
    pop(T_INVALID);

    b_push_imm(7);
    b_shr();
    pop(T_INVALID);

    push_vsp();
    b_read_mem();
    pop(highest_bit|T_E32X|T_16X|T_8H);
    //neg diff
    b_neg();
    pop(T_INVALID);
    //add count,1
    push(count_reg|T_E32X|T_16X|T_8H);
    b_push_imm(1);
    b_add();
    pop(T_INVALID);
    //shl diff,count+1
    b_shl();
    pop(T_INVALID);
    //add diff,最高位
    push(highest_bit|T_E32X|T_16X|T_8H);
    b_add();
    pop(T_INVALID);
    //neg diff
    b_neg();
    pop(T_INVALID);
    //shl diff,7 - count_reg
    push(count_reg|T_E32X|T_16X|T_8H);
    b_push_imm(8-1);
    b_sub();
    pop(T_INVALID);

    b_shl();
    pop(T_INVALID);
    //shr dest_reg,count_reg
    push(dest_reg|T_E32X|T_16X|T_8H);
    push(count_reg|T_E32X|T_16X|T_8H);
    b_shr();

    //pop(T_INVALID);
    //get_cf();
    //d_push_imm(1);
    b_push_imm_zx(1);
    d_and();   //获取shr的cf标志位
    pop(T_INVALID);
    pop(tmp_cf_reg);

    //or dest_reg,diff
    b_or();

    push(tmp_cf_reg);
    d_or(); //合并shr的cf和or的其他标志位
    pop(T_INVALID);

    unlock_tmp_vmregister(count_reg);
    unlock_tmp_vmregister(dest_reg);
    unlock_tmp_vmregister(highest_bit);
    unlock_tmp_vmregister(tmp_cf_reg);
}

void VCombosVMCode::w_sar()
{
    /*
    * sar 10101110,2
    * 最高位 = 1
    * 11111111  sub 0,最高位 -> diff
    * 11111000  shl diff << 右移位数 + 1
    * 11111001  add diff,最高位
    * 00000111  neg diff
    * 11100000  shl diff,目标操作数位数(7) - 右移位数 + 1
    * shr 目标操作数,右移位数
    * add 目标操作数,diff
    */
    int dest_reg = get_tmp_vmregister();
    int highest_bit = get_tmp_vmregister();
    int count_reg = get_tmp_vmregister();
    int tmp_cf_reg = get_tmp_vmregister();
    pop(count_reg|T_E32X|T_16X|T_8H);//save count
    //and o1,10000000b
    push_vsp();
    w_read_mem(); //copy dest
    pop(dest_reg|T_E32X|T_16X); //save dest
    w_push_imm(1<<15);
    w_and();
    pop(T_INVALID);

    b_push_imm(15);
    w_shr();
    pop(T_INVALID);

    push_vsp();
    w_read_mem();
    pop(highest_bit|T_E32X|T_16X);
    //neg diff
    w_neg();
    pop(T_INVALID);
    //add count,1
    push(count_reg|T_E32X|T_16X|T_8H);
    b_push_imm(1);
    b_add();
    pop(T_INVALID);
    //shl diff,count+1
    w_shl();
    pop(T_INVALID);
    //add diff,最高位
    push(highest_bit|T_E32X|T_16X);
    w_add();
    pop(T_INVALID);
    //neg diff
    w_neg();
    pop(T_INVALID);
    //shl diff,7 - count_reg
    push(count_reg|T_E32X|T_16X|T_8H);
    b_push_imm(16-1);
    b_sub();
    pop(T_INVALID);

    w_shl();
    pop(T_INVALID);
    //shr dest_reg,count_reg
    push(dest_reg|T_E32X|T_16X);
    push(count_reg|T_E32X|T_16X|T_8H);
    w_shr();
    //pop(T_INVALID);
    //get_cf();
    //d_push_imm(1);
    b_push_imm_zx(1);
    d_and();   //获取shr的cf标志位
    pop(T_INVALID);
    pop(tmp_cf_reg);

    //or dest_reg,diff
    w_or();

    push(tmp_cf_reg);
    d_or(); //合并shr的cf和or的其他标志位
    pop(T_INVALID);
    unlock_tmp_vmregister(count_reg);
    unlock_tmp_vmregister(dest_reg);
    unlock_tmp_vmregister(highest_bit);
    unlock_tmp_vmregister(tmp_cf_reg);
}

void VCombosVMCode::d_sar()
{
    /*
    * sar 10101110,2
    * 最高位 = 1
    * 11111111  sub 0,最高位 -> diff
    * 11111000  shl diff << 右移位数 + 1
    * 11111001  add diff,最高位
    * 00000111  neg diff
    * 11100000  shl diff,目标操作数位数(7) - 右移位数 + 1
    * shr 目标操作数,右移位数
    * add 目标操作数,diff
    */
    int dest_reg = get_tmp_vmregister();
    int highest_bit = get_tmp_vmregister();
    int count_reg = get_tmp_vmregister();
    int tmp_cf_reg = get_tmp_vmregister();
    pop(count_reg|T_E32X|T_16X|T_8H);//save count
    //and o1,10000000b
    push_vsp();
    d_read_mem(); //copy dest
    pop(dest_reg|T_E32X); //save dest
    d_push_imm(1<<31);
    d_and();
    pop(T_INVALID);

    b_push_imm(31);
    d_shr();
    pop(T_INVALID);
    //int3();

    push_vsp();
    d_read_mem();
    pop(highest_bit|T_E32X);
    //neg diff
    d_neg();
    pop(T_INVALID);
    //int3();
    //add count,1
    push(count_reg|T_E32X|T_16X|T_8H);
    d_shl(); //new
    pop(T_INVALID);

    b_push_imm(1);
    d_shl();
    //b_add();
    pop(T_INVALID);
    //int3();
    //shl diff,count+1
    /*d_shl();
    pop(T_INVALID);
    int3();*/
    //add diff,最高位
    push(highest_bit|T_E32X);
    d_add();
    pop(T_INVALID);
    //neg diff
    d_neg();
    pop(T_INVALID);
    //int3();

    //shl diff,7 - count_reg
    push(count_reg|T_E32X|T_16X|T_8H);
    b_push_imm(32-1);
    b_sub();
    pop(T_INVALID);
    //int3();

    d_shl();
    pop(T_INVALID);
    //int3();
    //shr dest_reg,count_reg
    push(dest_reg|T_E32X);
    push(count_reg|T_E32X|T_16X|T_8H);
    d_shr();
    //pop(T_INVALID);
    //get_cf();
    //d_push_imm(1);
    b_push_imm_zx(1);
    d_and();   //获取shr的cf标志位
    pop(T_INVALID);
    pop(tmp_cf_reg);

    //or dest_reg,diff
    d_or();
    //int3();


    push(tmp_cf_reg);
    d_or(); //合并shr的cf和or的其他标志位
    pop(T_INVALID);
    unlock_tmp_vmregister(count_reg);
    unlock_tmp_vmregister(dest_reg);
    unlock_tmp_vmregister(highest_bit);
    unlock_tmp_vmregister(tmp_cf_reg);
}


void VCombosVMCode::ret()
{
 pushf();
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
 build_vm_mnemonic(get_handle(ret));
}


/////////////////////Combos/////////////////
void VCombosVMCode::b_and()
{
    int tmp_register = get_tmp_vmregister();
    pop(tmp_register | T_E32X | T_16X | T_8L);

    push_vsp();
    b_read_mem();
    b_nand();
    pop(T_INVALID);
    
    push(tmp_register | T_E32X | T_16X | T_8L);
    push_vsp();
    b_read_mem();
    b_nand();
    pop(T_INVALID);

    b_nand();
    unlock_tmp_vmregister(tmp_register);
}

void VCombosVMCode::w_and()
{
    int tmp_register = get_tmp_vmregister();
    pop(tmp_register | T_E32X | T_16X);

    push_vsp();
    w_read_mem();
    w_nand();
    pop(T_INVALID);
    
    push(tmp_register | T_E32X | T_16X);
    push_vsp();
    w_read_mem();
    w_nand();
    pop(T_INVALID);

    w_nand();
    unlock_tmp_vmregister(tmp_register);  
}

void VCombosVMCode::d_and()
{
    int tmp_register = get_tmp_vmregister();
    pop(tmp_register | T_E32X);

    push_vsp();
    d_read_mem();
    d_nand();
    pop(T_INVALID);
    
    push(tmp_register | T_E32X);
    push_vsp();
    d_read_mem();
    d_nand();
    pop(T_INVALID);

    d_nand();
    unlock_tmp_vmregister(tmp_register); 
}

#ifdef PROTECT_X64
void VCombosVMCode::q_and()
{
    int tmp_register = get_tmp_vmregister();
    pop(tmp_register);

    push_vsp();
    q_read_mem();
    q_nand();
    pop(T_INVALID);
    
    push(tmp_register);
    push_vsp();
    q_read_mem();
    q_nand();
    pop(T_INVALID);

    q_nand();
    unlock_tmp_vmregister(tmp_register); 
}
#endif

void VCombosVMCode::b_or()
{
 int tmp_vmregister  = get_tmp_vmregister();
 push_vsp();
 w_read_mem();
 b_nand();
 pop(T_INVALID);
 pop(tmp_vmregister | T_E32X | T_16X | T_8L);
 b_nand();
 pop(T_INVALID);
 push(tmp_vmregister | T_E32X | T_16X | T_8L);
 b_nand();
 unlock_tmp_vmregister(tmp_vmregister);
}

void VCombosVMCode::w_or()
{
 int tmp_vmregister1 = get_tmp_vmregister();
 int tmp_vmregister2 = get_tmp_vmregister();
 pop(tmp_vmregister1 | T_E32X | T_16X);
 pop(tmp_vmregister2 | T_E32X | T_16X);
 impact_vmregister(false);
 push(tmp_vmregister1 | T_E32X | T_16X);
 push(tmp_vmregister2 | T_E32X | T_16X);
 w_nand();
 pop(T_INVALID);
 impact_vmregister(true);  
 push(tmp_vmregister1 | T_E32X | T_16X);
 push(tmp_vmregister2 | T_E32X | T_16X);
 w_nand();
 pop(T_INVALID);                
 w_nand();

 unlock_tmp_vmregister(tmp_vmregister1);
 unlock_tmp_vmregister(tmp_vmregister2);
}
 
void VCombosVMCode::d_or()
{
 int tmp_vmregister1 = get_tmp_vmregister();
 int tmp_vmregister2 = get_tmp_vmregister();
 pop(tmp_vmregister1 | T_E32X);
 pop(tmp_vmregister2 | T_E32X);
 impact_vmregister(false);
 push(tmp_vmregister1 | T_E32X);
 push(tmp_vmregister2 | T_E32X);
 d_nand();
 pop(T_INVALID);
 impact_vmregister(true);    
 push(tmp_vmregister1 | T_E32X);
 push(tmp_vmregister2 | T_E32X);
 d_nand();
 pop(T_INVALID);                
 d_nand();

 unlock_tmp_vmregister(tmp_vmregister1);
 unlock_tmp_vmregister(tmp_vmregister2);
}
  
#ifdef PROTECT_X64
void VCombosVMCode::q_or()
{
 int tmp_vmregister1 = get_tmp_vmregister();
 int tmp_vmregister2 = get_tmp_vmregister();
 pop(tmp_vmregister1 );
 pop(tmp_vmregister2 );
 impact_vmregister(false);
 push(tmp_vmregister1 );
 push(tmp_vmregister2 );
 q_nand();
 pop(T_INVALID);
 impact_vmregister(true);    
 push(tmp_vmregister1 );
 push(tmp_vmregister2 );
 q_nand();
 pop(T_INVALID);                
 q_nand();

 unlock_tmp_vmregister(tmp_vmregister1);
 unlock_tmp_vmregister(tmp_vmregister2);
} 
#endif


void VCombosVMCode::b_xor()
{
 int tmp_vmregister = get_tmp_vmregister();
 push_vsp();
 w_read_mem();
 b_nand();
 pop(T_INVALID);
 pop(tmp_vmregister | T_E32X | T_16X | T_8L);
 b_and();
 pop(T_INVALID);
 push(tmp_vmregister | T_E32X | T_16X | T_8L);
 b_nand();
 unlock_tmp_vmregister(tmp_vmregister);
}

void VCombosVMCode::w_xor()
{
 int tmp_vmregister1 = get_tmp_vmregister();
 int tmp_vmregister2 = get_tmp_vmregister();
 pop(tmp_vmregister1 | T_E32X | T_16X);
 pop(tmp_vmregister2 | T_E32X | T_16X);
 impact_vmregister(false);
 push(tmp_vmregister1 | T_E32X | T_16X);
 push(tmp_vmregister2 | T_E32X | T_16X);
 w_nand();
 pop(T_INVALID);
 impact_vmregister(true);
 push(tmp_vmregister1 | T_E32X | T_16X);
 push(tmp_vmregister2 | T_E32X | T_16X);
 w_and();
 pop(T_INVALID);
 w_nand();
 unlock_tmp_vmregister(tmp_vmregister1);
 unlock_tmp_vmregister(tmp_vmregister2);
}

void VCombosVMCode::d_xor()
{
 int tmp_vmregister1 = get_tmp_vmregister();
 int tmp_vmregister2 = get_tmp_vmregister();
 pop(tmp_vmregister1 | T_E32X);
 pop(tmp_vmregister2 | T_E32X);
 impact_vmregister(false);
 push(tmp_vmregister1 | T_E32X);
 push(tmp_vmregister2 | T_E32X);
 d_nand();
 pop(T_INVALID);
 impact_vmregister(true);
 push(tmp_vmregister1 | T_E32X);
 push(tmp_vmregister2 | T_E32X);
 d_and();
 pop(T_INVALID);
 d_nand();
 unlock_tmp_vmregister(tmp_vmregister1);
 unlock_tmp_vmregister(tmp_vmregister2);
}

#ifdef PROTECT_X64
void VCombosVMCode::q_xor()
{
 int tmp_vmregister1 = get_tmp_vmregister();
 int tmp_vmregister2 = get_tmp_vmregister();
 pop(tmp_vmregister1);
 pop(tmp_vmregister2);
 impact_vmregister(false);
 push(tmp_vmregister1);
 push(tmp_vmregister2);
 q_nand();
 pop(T_INVALID);
 impact_vmregister(true);
 push(tmp_vmregister1);
 push(tmp_vmregister2);
 q_and();
 pop(T_INVALID);
 q_nand();
 unlock_tmp_vmregister(tmp_vmregister1);
 unlock_tmp_vmregister(tmp_vmregister2);
}  
#endif

void VCombosVMCode::b_sub()
{
#ifdef DEBUG
   //fprintf(ptr_pcode->get_log(),"\nVCombosHandle:%s()\n","b_sub");
#endif

 int tmp_flag1 = get_tmp_vmregister();
 int tmp_flag2 = get_tmp_vmregister();
 b_not();
 pop(T_INVALID);
 //pop(tmp_vmregister1 | T_E32X);
 b_add();
 pop(tmp_flag1 | T_E32X); 
 push_vsp();
 b_read_mem();
 b_nand();
 pop(tmp_flag2 | T_E32X);
 push(tmp_flag1 | T_E32X);
 d_not();
 pop(T_INVALID);
 w_push_imm_sx(0xf7ea);
 d_nand();
 pop(T_INVALID);
 //pop(tmp_flag1);
 
 //pop(tmp_vmregister1 | T_E32X);
 push(tmp_flag2 | T_E32X);
 d_not();
 pop(T_INVALID);
 w_push_imm_sx(0x815);
 d_nand();
 pop(T_INVALID);
 d_add();
 pop(T_INVALID);
 unlock_tmp_vmregister(tmp_flag1);
 unlock_tmp_vmregister(tmp_flag2);        
}

void VCombosVMCode::w_sub()
{
#ifdef DEBUG
   //fprintf(ptr_pcode->get_log(),"\nVCombosHandle:%s()\n","w_sub");
#endif

 int tmp_flag1 = get_tmp_vmregister();
 int tmp_flag2 = get_tmp_vmregister();
 w_not();
 pop(T_INVALID);
 //pop(tmp_vmregister1 | T_E32X);
 w_add();
 pop(tmp_flag1 | T_E32X); 
 push_vsp();
 w_read_mem();
 w_nand();
 pop(tmp_flag2 | T_E32X);
 push(tmp_flag1 | T_E32X);
 d_not();
 pop(T_INVALID);
 w_push_imm_sx(0xf7ea);
 d_nand();
 pop(T_INVALID);
 //pop(tmp_flag1);
 
 //pop(tmp_vmregister1 | T_E32X);
 push(tmp_flag2|T_E32X);
 d_not();
 pop(T_INVALID);
 w_push_imm_sx(0x815);
 d_nand();
 pop(T_INVALID);
 d_add();
 pop(T_INVALID);
 unlock_tmp_vmregister(tmp_flag1);
 unlock_tmp_vmregister(tmp_flag2);     
}

void VCombosVMCode::d_sub() //[stacktop] - [stacktop-4]
{
 #ifdef DEBUG
   //fprintf(ptr_pcode->get_log(),"\nVCombosHandle:%s()\n","d_sub");
#endif

 int tmp_flag1 = get_tmp_vmregister();
 int tmp_flag2 = get_tmp_vmregister();
 d_not();
 pop(T_INVALID);
 //pop(tmp_vmregister1 | T_E32X);
 d_add();
 pop(tmp_flag1 | T_E32X); 
 push_vsp();
 d_read_mem();
 d_nand();
 pop(tmp_flag2 | T_E32X);
 push(tmp_flag1 | T_E32X);
 d_not();
 pop(T_INVALID);
 w_push_imm_sx(0xf7ea);
 d_nand();
 pop(T_INVALID);
 //pop(tmp_flag1);
 
 //pop(tmp_vmregister1 | T_E32X);
 push(tmp_flag2 | T_E32X);
 d_not();
 pop(T_INVALID);
 w_push_imm_sx(0x815);
 d_nand();
 pop(T_INVALID);
 d_add();
 pop(T_INVALID);
 unlock_tmp_vmregister(tmp_flag1);
 unlock_tmp_vmregister(tmp_flag2);
}

void VCombosVMCode::q_sub()
{
    
}

void VCombosVMCode::b_cmp()
{
#ifdef DEBUG
  // fprintf(ptr_pcode->get_log(),"\nVCombosHandle:%s()\n","b_cmp");
#endif

   int tmp_vmregister = get_tmp_vmregister();
   b_sub();
   pop(tmp_vmregister);
   pop(T_INVALID | T_E32X | T_16X | T_8L);
   push(tmp_vmregister);
   unlock_tmp_vmregister(tmp_vmregister);
}

void VCombosVMCode::w_cmp()
{
#ifdef DEBUG
  // fprintf(ptr_pcode->get_log(),"\nVCombosHandle:%s()\n","w_cmp");
#endif
   int tmp_vmregister = get_tmp_vmregister();
   w_sub();
   pop(tmp_vmregister);
   pop(T_INVALID | T_E32X | T_16X );
   push(tmp_vmregister);
   unlock_tmp_vmregister(tmp_vmregister); 
}

void VCombosVMCode::d_cmp()
{
#ifdef DEBUG
  // fprintf(ptr_pcode->get_log(),"\nVCombosHandle:%s()\n","d_cmp");
#endif
   int tmp_vmregister = get_tmp_vmregister();
   d_sub();
   pop(tmp_vmregister);
   pop(T_INVALID | T_E32X);
   push(tmp_vmregister);
   unlock_tmp_vmregister(tmp_vmregister);       
}

void VCombosVMCode::b_test()
{
    int tmp_vmregister = get_tmp_vmregister();
    b_and();
    pop(tmp_vmregister);
    pop(T_INVALID|T_E32X|T_16X|T_8H);
    push(tmp_vmregister);
    unlock_tmp_vmregister(tmp_vmregister);
}

void VCombosVMCode::w_test()
{
    int tmp_vmregister = get_tmp_vmregister();
    w_and();
    pop(tmp_vmregister);
    pop(T_INVALID|T_E32X|T_16X);
    push(tmp_vmregister);
    unlock_tmp_vmregister(tmp_vmregister);
}

void VCombosVMCode::d_test()
{
    int tmp_vmregister = get_tmp_vmregister();
    d_and();
    pop(tmp_vmregister);
    pop(T_INVALID|T_E32X);
    push(tmp_vmregister);
    unlock_tmp_vmregister(tmp_vmregister);
}


void VCombosVMCode::get_cf()
{
#ifdef DEBUG
  // fprintf(ptr_pcode->get_log(),"\nVCombosHandle:%s()\n","get_cf");
#endif
 //d_push_imm(1 << 0);
 b_push_imm_zx(1);
 d_and();
 pop(T_INVALID);  
 b_push_imm(2);   //不是0就是4
 d_shl();
 pop(T_INVALID);
}

void VCombosVMCode::get_pf()
{
#ifdef DEBUG
  // fprintf(ptr_pcode->get_log(),"\nVCombosHandle:%s()\n","get_pf");
#endif
 b_push_imm_zx(1 << 2);
 d_and();
 pop(T_INVALID);  
 //b_push_imm(2);   //不是0就是4
 //d_shl();
 //pop(T_INVALID); 
}

void VCombosVMCode::get_af()
{
    #ifdef DEBUG
  // fprintf(ptr_pcode->get_log(),"\nVCombosHandle:%s()\n","get_af");
#endif

 b_push_imm_zx(1 << 4);
 d_and();
 pop(T_INVALID);  
 b_push_imm(2);   //不是0就是4
 d_shr();
 pop(T_INVALID);  
}

void VCombosVMCode::get_zf()
{
    #ifdef DEBUG
   //fprintf(ptr_pcode->get_log(),"\nVCombosHandle:%s()\n","get_zf");
#endif

 b_push_imm_zx(1 << 6);
 d_and();
 pop(T_INVALID);  
 b_push_imm(4);   //不是0就是4
 d_shr();
 pop(T_INVALID);  
}

void VCombosVMCode::get_sf()
{
    #ifdef DEBUG
   //fprintf(ptr_pcode->get_log(),"\nVCombosHandle:%s()\n","get_sf");
#endif

 b_push_imm_zx(1 << 7);
 d_and();
 pop(T_INVALID);  
 b_push_imm(5);   //不是0就是4
 d_shr();
 pop(T_INVALID);  
}

void VCombosVMCode::get_of()
{
    #ifdef DEBUG
   //fprintf(ptr_pcode->get_log(),"\nVCombosHandle:%s()\n","get_of");
#endif

 d_push_imm(1 << 11);
 d_and();
 pop(T_INVALID);  
 b_push_imm(9);   //不是0就是4
 d_shr();
 pop(T_INVALID);  
}

void VCombosVMCode::get_df()
{
#ifdef DEBUG
   //fprintf(ptr_pcode->get_log(),"\nVCombosHandle:%s()\n","get_df");
#endif

 d_push_imm(1 << 10);
 d_and();
 pop(T_INVALID);  
 b_push_imm(10);   //不是0就是1
 d_shr();
 pop(T_INVALID); 
}

#ifdef DEBUG
void VCombosVMCode::int3()
{
    build_vm_mnemonic(get_handle(int3));
}
#endif

void VCombosVMCode::fstsw()
{
    build_vm_mnemonic(get_handle(fstsw));
}

//输入：无  返回一个串指令根据df进行加减的数值和地址对其  ret 1 or -1
void VCombosVMCode::get_string_ins_diff()
{
        /*
        *
        * df = 1
        * neg df      ;0xffffffff
        * add edi,df
        * not df      ;0
        * sub edi,df
        *
        * df = 0
        * neg df      ;0
        * add edi,df
        * not df      ;0xffffffff
        * sub edi,df
        *
        */
       int tmp_vmregister_diff = get_tmp_vmregister();
       int tmp_vmregister_df = get_tmp_vmregister();

       impact_vmregister(false);
       //d_push_imm(0x0);

       //neg df    sub 0,df
       push(T_FLAG); //t_edi
       get_df();
       d_push_imm(0);
       d_sub();
       pop(T_INVALID);
       push_vsp();
       d_read_mem();
       pop(tmp_vmregister_df | T_E32X);

       //add edi,df
       d_push_imm(0);
       d_add();
       pop(T_INVALID);
       pop(tmp_vmregister_diff | T_E32X);

       //not df
       push(tmp_vmregister_df | T_E32X);
       d_not();
       pop(T_INVALID);

       //sub edi,df
       push(tmp_vmregister_diff | T_E32X);
       d_sub();
       pop(T_INVALID);

       unlock_tmp_vmregister(tmp_vmregister_diff);
       unlock_tmp_vmregister(tmp_vmregister_df);

       impact_vmregister(true);

}
