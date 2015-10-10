/*
 *
 *   Copyright (C) Sat Jun  1 10:51:23 2013 XiaoWei
 *
 *                       handsomexiaowei@gmail.com
 *
 *
 */

#include <iostream>
#include <vector>
#include "SeniorVMHandle.hpp"
#include "BuildVMCode.hpp"
#include "VMAddressTable.hpp"
#include "VMCodeBuffer.hpp"
#include <WProtectConfig.h>
#include "CombosVMCode.hpp"

using namespace std;

#ifdef PROTECT_X64
#define _SIZE q
#else
#define _SIZE d
#endif

BuildVMCode::BuildVMCode()
{
}

BuildVMCode::~BuildVMCode()
{
}

long BuildVMCode::get_reg(const ud_type & t)
{
      switch ( t )
      {
      case UD_R_RAX:
        return T_RAX;
        break;
      case UD_R_RBX:
        return T_RBX;
        break;
      case UD_R_RCX:
        return T_RCX;
        break;
      case UD_R_RDX:
        return T_RDX;
        break;
      case UD_R_RSP:
        return T_RSP;
        break;
      case UD_R_RBP:
        return T_RBP;
        break;
      case UD_R_RDI:
        return T_RDI;
        break;
      case UD_R_RSI:
        return T_RSI;
        break;        
      case UD_R_EAX:
        return T_EAX;
        break;
      case UD_R_EBX:
        return T_EBX;
        break;
      case UD_R_ECX:
        return T_ECX;
        break;
      case UD_R_EDX:
        return T_EDX;
        break;
      case UD_R_ESP:
        return T_ESP;
        break;
      case UD_R_EBP:
        return T_EBP;
        break;
      case UD_R_EDI:
        return T_EDI;
        break;
      case UD_R_ESI:
        return T_ESI;
        break;
      case UD_R_AL:
        return T_AL;
        break;
      case UD_R_AH:
        return T_AH;
        break;
      case UD_R_BL:
        return T_BL;
        break;
      case UD_R_BH:
        return T_BH;
        break;
      case UD_R_CL:
        return T_CL;
        break;
      case UD_R_CH:
        return T_CH;
        break;
      case UD_R_DL:
        return T_DL;
        break;
      case UD_R_DH:
        return T_DH;
        break;
      case UD_R_AX:
        return T_AX;
        break;
      case UD_R_BX:
        return T_BX;
        break;
      case UD_R_CX:
        return T_CX;
        break;
      case UD_R_DX:
        return T_DX;
        break;
      case UD_R_SP:
        return T_SP;
        break;
      case UD_R_BP:
        return T_BP;
        break;
      case UD_R_SI:
        return T_SI;
        break;
      case UD_R_DI:
        return T_DI;
        break;
      dafault:
        return 0;
      }
      return 0;
}

void BuildVMCode::get_operand( SeniorVMHandle *svm,const ud_operand & op  ,bool _disable)
{
  long base = 0;
  long index = 0;
  long scale = 0;
  long lval = 0;
  if (op.type == UD_OP_MEM)
  {
    base = get_reg( op.base );
    index = get_reg( op.index );
    lval = op.offset == 8 ? op.lval.sbyte : op.lval.sdword;
    scale = op.scale;
    svm->r_get_mem( base,index,scale,index );
  } else if (op.type == UD_OP_REG)
  {
    svm->push(get_reg(op.base),_disable);
  } else if (op.type == UD_OP_IMM)
  {
    if ( op.size == 8 )
      svm->b_push_imm( op.lval.sbyte );
    else if (op.size == 16)
      svm->w_push_imm( op.lval.sword );
    else if ( op.size == 32 )
      svm->d_push_imm( op.lval.sdword );
#ifdef PROTECT_X64
    else if (op.size == 64)
      svm->q_push_imm(op.lval.sqword);
#endif
  }
}

void BuildVMCode::get_mem_data( SeniorVMHandle *svm,const ud_operand & op )
{
  switch ( op.size )
  {
  case 8:
    svm->b_read_mem(  );
    break;
  case 16:
    svm->w_read_mem(  );
    break;
  case 32:
    svm->d_read_mem(  );
    break;
#ifdef PROTECT_X64
  case 64:
    svm->q_read_mem(  )  ;
    break;
#endif
  }
}

void BuildVMCode::set_mem_data( SeniorVMHandle *svm,const ud_operand & op )
{
  switch ( op.size )
  {
  case 8:
    svm->b_write_mem(  );
    break;
  case 16:
    svm->w_write_mem(  );
    break;
  case 32:
    svm->d_write_mem(  );
    break;
#ifdef PROTECT_X64
  case 64:
    svm->q_write_mem(  )  ;
    break;
#endif
  }
}

VOperand BuildVMCode::to_voperand(ud_operand &ud_op)
{
  VOperand o;
  switch (ud_op.type)
  {
  case UD_OP_MEM:
    o._mem.op = VOPERAND_MEM;
    switch(ud_op.size)
    {
    case 8:
      o._mem.size = 1;
      break;
    case 16:
      o._mem.size = 2;
      break;
    case 32:
      o._mem.size = 4;
      break;
    case 64:
      o._mem.size = 8;
      break;
    }
    o._mem.base = get_reg(ud_op.base);
    o._mem.index = get_reg(ud_op.index);
    o._mem.scale = ud_op.index;
    o._mem.lval = ud_op.offset == 8? (signed char)ud_op.lval.sbyte : ud_op.lval.sdword;
    break;
  case UD_OP_IMM:
    o._imm.op = VOPERAND_IMM;
    switch(ud_op.size)
    {
    case 8:
      o._imm.size = 1;
      break;
    case 16:
      o._imm.size = 2;
      break;
    case 32:
      o._imm.size = 4;
      break;
    case 64:
      o._imm.size = 8;
      break;
    }
    o._imm.value = ud_op.offset == 8? (signed char)ud_op.lval.sbyte : ud_op.lval.sdword;
    break;
  case UD_OP_JIMM:
    o._imm.op = VOPERAND_JIMM;
    switch(ud_op.size)
    {
    case 8:
      o._imm.size = 1;
      break;
    case 16:
      o._imm.size = 2;
      break;
    case 32:
      o._imm.size = 4;
      break;
    case 64:
      o._imm.size = 8;
      break;
    }
    o._imm.value = ud_op.offset == 8? (signed char)ud_op.lval.sbyte : ud_op.lval.sdword;    
    break;
  case UD_OP_REG:
    o._reg.op = VOPERAND_REG;
    o._reg.base = get_reg(ud_op.base);
    if (o._reg.base & T_8H || o._reg.base & T_8L)
    {
      o._reg.size = 1;
    } else if (o._reg.base & T_16X)
    {
      o._reg.size = 2;
    } else if (o._reg.base & T_E32X)
    {
      o._reg.size = 4;
    } else 
    {
      o._reg.size = 8;
    }
    break;
  }
  return o;
}


long BuildVMCode::asm_to_vm(SeniorVMHandle *svm,ud_t *p_ud) //返回大小
{  
  #define GET_HANDLE(x) svm->pcode->pcode_info.handle_table.x.handle     
  #define op1 p_ud->operand[ 0 ]
  #define op2 p_ud->operand[ 1 ]
  #define op3 p_ud->operand[ 2 ]  
  VOperand o1 = to_voperand(op1);
  VOperand o2 = to_voperand(op2);
  VOperand o3 = to_voperand(op3);
  switch (p_ud->mnemonic)
  {
  case UD_Imov:
    {
      if ( op1.type == UD_OP_MEM )
      {
        get_operand(svm,op1);
        svm->pop( T_MEM_REGISTER );
      }
      
      get_operand(svm, op2 );
      if ( op2.type == UD_OP_MEM )
      {        
        get_mem_data(svm,op2);
      } 
      if (op1.type == UD_OP_REG)
      {
        svm->pop( get_reg(op1.base) );
      } else if (op1.type == UD_OP_MEM)
      {
        svm->push( T_MEM_REGISTER );
        set_mem_data(svm,op1);
      }
    }
    break;
  case UD_Ipush:
    {
      get_operand( svm,op1,false );
      if (op1.type == UD_OP_MEM)
      {
        get_mem_data( svm,op1 );
      }
    }
    break;
  case UD_Ixor:
    {
  /*
      if (op1.type == UD_OP_MEM)
      {
        get_operand( svm , op1 ,false);
        svm->pop( T_MEM_REGISTER );
      }
      get_operand( svm,op2 ,false);
      if (op2.type == UD_OP_MEM)
      {
        get_mem_data( svm,op2 );
      }
      if (op1.type == UD_OP_REG)
      {
       svm->pop(T_DATA_REGISTER);
       //svm->v_xor( get_reg(op1.base),T_DATA_REGISTER);
       svm->pop(T_EFLAG);
       svm->pop( get_reg( op1.base ) );
      } else if (op1.type == UD_OP_MEM)
      {
        svm->push(T_MEM_REGISTER);
        get_mem_data(svm,op1);
        svm->pop(T_DATA_REGISTER);
        svm->pop(T_TMP_REGISTER1);
  
        }*/
        svm->v_xor(&o1,&o2);
        svm->pop(T_EFLAG);
        svm->pop_operand(&o1);
    }
    break;
  case UD_Ior:
   {
     svm->v_or(&o1,&o2);
     svm->pop(T_EFLAG);
     svm->pop_operand(&o1);
   } 
   break;
 case UD_Inot:
   {
     svm->v_not(&o1);
     svm->pop(T_EFLAG);
     svm->pop_operand(&o1);
   }
   break;
   
  case UD_Ijnz:
    {
  //svm->push( T_EFLAG ,false);
      svm->a_push_imm(p_ud->vm_jcc_addr1);
      svm->a_push_imm(p_ud->vm_jcc_addr2);      
      svm->push_vesp(  );
      //svm->d_push_imm( 0x40 );
      //svm->pop( T_TMP_REGISTER1 );
      svm->d_and( T_EFLAG,0x40,true );
      //svm->d_and( T_EFLAG, T_TMP_REGISTER1);      
      svm->pop( T_INVALID );
      svm->b_push_imm( 4 );
      svm->db( GET_HANDLE( d_shr ) );
      svm->pop( T_INVALID );
      svm->db( GET_HANDLE( d_add ) );
      svm->pop( T_INVALID );
      svm->d_read_mem();
      svm->pop(T_JCC_REGISTER);
      svm->pop(T_INVALID);
      svm->pop(T_INVALID);
      // svm->push(T_JCC_REGISTER);
      //svm->push(T_TMP_REGISTER1);
    }
    break;
  case UD_Ijz:
    {
      svm->a_push_imm(p_ud->vm_jcc_addr2);
      svm->a_push_imm(p_ud->vm_jcc_addr1);
      svm->push_vesp(  );
      // svm->d_push_imm( 0x40 );
      //svm->pop( T_TMP_REGISTER1 );
      svm->d_and( T_EFLAG,0x40,true );
      //svm->d_and( T_EFLAG, T_TMP_REGISTER1);
      svm->pop( T_INVALID );
      svm->b_push_imm( 4 );
      svm->db( GET_HANDLE( d_shr ) );
      svm->pop( T_INVALID );
      svm->db( GET_HANDLE( d_add ) );
      svm->pop( T_INVALID );
      svm->d_read_mem();
      // svm->set_pc();
      svm->pop(T_JCC_REGISTER);
      svm->pop(T_INVALID);
      svm->pop(T_INVALID);
      //svm->push(T_TMP_REGISTER1);
    }
    break;
  case UD_Iret:
    svm->exit( );
    break;
  case UD_Itest:
    svm->test(&o1,&o2);
    break;
     
  }
  printf("%s\r\n",p_ud->insn_buffer);
  return 0;         
}

/*
pCodeBufferInfo BuildVMCode::BuildPCode(VirtualMachineManage *vmmanage,pCodeBufferInfo pinfo)
{
  Analysis analysis;
  analysis.disasm(pinfo);
  VirtualMachine *vm = vmmanage->rand_virtual_machine();
  
  PCode *pcode_array = new PCode[analysis.block_count];
  SeniorVMHandle *seniorvm_array = new SeniorVMHandle[analysis.block_count];

  for (int i = 0; i < analysis.block_count; ++i)
  {
    vmmanage->moc(vm,&pcode_array[i]);
    seniorvm_array[i].link_pcode(&pcode_array[i]);
  }
  for (int i = 0; i < analysis.block_count; ++i)
  {
    pAssemblerTree nowtree = analysis.get_tree(i);
    for (std::vector<ud_t>::iterator iter = nowtree->asmpiece.begin();
         iter != nowtree->asmpiece.end(); ++iter)
    {
      ud_t ud = *iter;
      asm_to_vm(&seniorvm_array[i],&ud);
    }
      printf("\r\n");    
  }
  delete [] seniorvm_array;
  delete [] pcode_array;
  return pinfo;
  }*/

void rm( VMCodeBufferManage * p )
{
    delete p;
}


void BuildVMCode::dispose_key(Analysis *analysis)
{
  pAssemblerTree nowtree = analysis->root;
  vector <pAssemblerTree> tree_vec;
  while (nowtree)
  {
    nowtree->set_key = false;
    nowtree->key = 0;
    tree_vec.push_back(nowtree);
    nowtree = nowtree->LeftChild;
  }
  nowtree = analysis->root;
  while (nowtree)
  {
    pAssemblerTree t_nowtree = analysis->root;
    if (nowtree->RightChild)
    {
      nowtree->set_key = true;
    }
    
    nowtree = nowtree -> LeftChild;
  }                                           
}

void BuildVMCode::update_key_data(Analysis *analysis)
{
  pAssemblerTree nowtree = analysis->root;
  vector <pAssemblerTree> tree_vec;
  while (nowtree)
  {
    if (nowtree->set_key && nowtree->RightChild)
    {
      nowtree->key = nowtree->RightChild->key;
    }
    else if (nowtree->set_key)
    {
      nowtree->key = nowtree->LeftChild->key;
    }
    nowtree = nowtree->LeftChild;
  }
}
 

 long BuildVMCode::alloc_address(VirtualMachine *vm,VMAddressTable * address_table,Analysis *analysis, vector <VMCodeBufferManage*> *vcodebufs)
{
  //analysis->disasm(pinfo);
  dispose_key(analysis);
  
  long pcode_addr = 0;
  long t_key = 0;
  bool is_jcc = false;
  RegisterStore store;
  for (int i = 0; i < analysis->block_count; ++i)
  {
    vcodebufs->push_back(new VMCodeBufferManage(vm));
  }
  for (int i = 0; i < analysis->block_count; ++i)
  {

    SeniorVMHandle *senior;
    ud_t ud;
    VTable table;    
    pAssemblerTree nowtree = analysis->get_tree(i);
    
    senior = & ((*vcodebufs)[i]->get_generator());
    senior->pcode->count_vmcode_begin();
    
    table.key = (*vcodebufs)[i]->code.get_original_key();
    table.v = senior;
    if (i == 0)
    {
      senior->upset_register_array(senior->pcode->register_store_in);
      nowtree->key = (*vcodebufs)[i]->code.get_original_key(); //保存key
      store = (senior->pcode->register_store_in);      
    }
    
    table.id = nowtree->id;
    table.base = nowtree->base;

    if (i != 0)
    {
  //(*vcodebufs)[i]->code.set_key(t_key);
      senior->pcode->register_store_in = store;
      nowtree->key = t_key;
    }
    else
    {
       t_key = nowtree->key;
       store = (senior->pcode->register_store_in);
      //      t_key = nowtree->key = (*vcodebufs)[i]->code.get_original_key(); //保存key
      //store = (senior->pcode->register_store_in);
    }

    senior->save_vm_context();
    senior->pcode->register_store_in = store;
    bool b_j = false;
    for (std::vector<ud_t>::iterator iter = nowtree->asmpiece.begin();
         iter != nowtree->asmpiece.end(); ++iter)
    {
      ud = *iter;
      switch ( ud.mnemonic)
      {
      case UD_Ijnz:
        b_j = true;
        asm_to_vm( &((*vcodebufs)[ i ]->get_generator(  )),&ud );        
        break;
      case UD_Ijz:
        b_j = true;
        asm_to_vm( &((*vcodebufs)[ i ]->get_generator(  )),&ud );
        
        break;
      default:
        asm_to_vm( &((*vcodebufs)[ i ]->get_generator(  )),&ud );  
      }
    }
    if (i+1 < analysis->block_count    )
    {
      senior->pcode->register_store_out = store;
      senior->recover_vm_context();
      senior->pcode->register_store_out = store;
      senior->push(T_INVALID);
      //senior->dw(123);
      //if (!b_j)
      //senior->push(T_INVALID);
      //      senior->push
      senior->set_key(1);
    }
    /*    if (nowtree->set_key)
    {
      (*vcodebufs)[i]->code.set_key(nowtree->key);
      } */   
    long size = senior->pcode->count_vmcode_end();
    long addr = address_table->assign_address(size,table);
#ifdef DEBUG
    printf("Alloc PCODE Address%08x Size:%d\r\n",addr,size);
#endif    
    nowtree->reloc_address = addr;

    if (pcode_addr == 0)
    {
      pcode_addr = addr;
    }
    
  }
  update_key_data(analysis);
  analysis->reloc_asm_address();
  return pcode_addr;
}
 
 
  /*
pCodeBufferInfo BuildVMCode::BuildPCode(
                                        VirtualMachineManage *vmmanage,
                                        pCodeBufferInfo pinfo,
                                        VMAddressTable * address_table
                                          )
{
  Analysis analysis;
  std::vector<CodePiece> code_piece_list;
  analysis.disasm(pinfo,code_piece_list);
  VirtualMachine *vm = vmmanage->rand_virtual_machine();
  vector <VMCodeBufferManage*>vcodebufs;
  long first_pcode_addr = alloc_address(vm,address_table,&analysis,&vcodebufs);
  
   SeniorVMHandle *sfirst = &vcodebufs[ 0 ]->get_generator(  );
   //sfirst->upset_register_array(sfirst->pcode->register_store_in);
   //sfirst->start();
  
  long key = vcodebufs[ 0 ]->code.get_original_key(  );

  VTable t_v;

  memset(&t_v,0,sizeof(t_v));
  bool t_sign = address_table->get_sign();
  address_table->set_sign(true);
  //printf("1111%d\n",address_table->get_size());
  //__asm__ ("int3");
  long head_address = address_table->assign_address(0x70);
  address_table->set_sign(t_sign);

#ifdef DEBUG
  printf("vm入口地址:%x\r\n",head_address);
#endif
  ppcode_block_info info =  vm->create_function_head(head_address,first_pcode_addr,sfirst->pcode,pinfo->addr + pinfo->size,123456,key); //pcode位置有问题

  address_table->copy(head_address,info->buf,info->size);
  

  for (int i = 0; i < analysis.block_count; ++i)
  {
    ud_t ud;
    pAssemblerTree nowtree = analysis.get_tree(i);
    SeniorVMHandle *senior = &(vcodebufs)[i]->get_generator();
    vcodebufs[ i ]->code.set_key( nowtree->key ); //设置key
    senior->save_vm_context();
      bool b_j = false;    
    for (std::vector<ud_t>::iterator iter = nowtree->asmpiece.begin();
         iter != nowtree->asmpiece.end(); ++iter)
    {
      ud = *iter;
      if (nowtree->LeftChild)
      ud.vm_jcc_addr1 = nowtree->LeftChild->reloc_address;
      switch ( ud.mnemonic)
      {
      case UD_Ijnz:
        b_j = true;
        ud.vm_jcc_addr2 = nowtree->RightChild->reloc_address;//nowtree->jcc_addr;
        asm_to_vm( &vcodebufs[ i ]->get_generator(  ),&ud );        
        break;
      case UD_Ijz:
        b_j = true;
        ud.vm_jcc_addr2 = nowtree->jcc_addr;
        asm_to_vm( &vcodebufs[ i ]->get_generator(  ),&ud );        
        break;
      default:
        asm_to_vm( &vcodebufs[ i ]->get_generator(  ),&ud );
      }
    }
    printf("当前key:%x\r\n",nowtree->key);
    if (i+1 < analysis.block_count    )
    {
      senior->recover_vm_context();
      if (!b_j) 
        senior->push(nowtree->LeftChild->reloc_address);
      else
        senior->push(T_JCC_REGISTER);
      //senior->set_key(vcodebufs[i]->code.get_original_key());
      senior->set_key(nowtree->key); //handle设置key
    }
        
    //senior->recover_vm_context();      
  }
  address_table->copy();
  
  for (vector <VMCodeBufferManage*>::iterator iter = vcodebufs.begin(); iter != vcodebufs.end(); ++iter)
  {
    delete *iter;
  }
  pinfo->addr = head_address;
  return pinfo;
}*/
pCodeBufferInfo BuildVMCode::BuildPCode(
                                        VirtualMachineManage *vmmanage,
                                        pCodeBufferInfo pinfo,
                                        VMAddressTable * address_table
                                          )
{
  Analysis analysis;
  analysis.disasm(pinfo);
  VirtualMachine *vm = vmmanage->rand_virtual_machine();
  vector <VMCodeBufferManage*>vcodebufs;
  long first_pcode_addr = alloc_address(vm,address_table,&analysis,&vcodebufs);
  
   SeniorVMHandle *sfirst = &vcodebufs[ 0 ]->get_generator(  );
   //sfirst->upset_register_array(sfirst->pcode->register_store_in);
   //sfirst->start();
  
  long key = vcodebufs[ 0 ]->code.get_original_key(  );

  VTable t_v;

  memset(&t_v,0,sizeof(t_v));
  bool t_sign = address_table->get_sign();
  address_table->set_sign(true);
  //printf("1111%d\n",address_table->get_size());
  //__asm__ ("int3");
  long head_address = address_table->assign_address(0x70);
  address_table->set_sign(t_sign);

#ifdef DEBUG
  printf("vmEntryAddress:%x\r\n",head_address);
#endif
  ppcode_block_info info =  vm->create_function_head(head_address,first_pcode_addr,sfirst->pcode,pinfo->addr + pinfo->size,123456,key); //pcode位置有问题

  address_table->copy(head_address,info->buf,info->size);
  
  /*FILE *file;
  file = fopen( "head","wb" );
  fwrite( info->buf,1,info->size,file );
  fclose( file );  */
  for (int i = 0; i < analysis.block_count; ++i)
  {
    ud_t ud;
    pAssemblerTree nowtree = analysis.get_tree(i);
    SeniorVMHandle *senior = &(vcodebufs)[i]->get_generator();
    vcodebufs[ i ]->code.set_key( nowtree->key ); //设置key
    senior->save_vm_context();
      bool b_j = false;    
    for (std::vector<ud_t>::iterator iter = nowtree->asmpiece.begin();
         iter != nowtree->asmpiece.end(); ++iter)
    {
      ud = *iter;
      if (nowtree->LeftChild)
      ud.vm_jcc_addr1 = nowtree->LeftChild->reloc_address;
      switch ( ud.mnemonic)
      {
      case UD_Ijnz:
        b_j = true;
        ud.vm_jcc_addr2 = nowtree->RightChild->reloc_address;//nowtree->jcc_addr;
        asm_to_vm( &vcodebufs[ i ]->get_generator(  ),&ud );        
        break;
      case UD_Ijz:
        b_j = true;
        ud.vm_jcc_addr2 = nowtree->jcc_addr;
        asm_to_vm( &vcodebufs[ i ]->get_generator(  ),&ud );        
        break;
      default:
        asm_to_vm( &vcodebufs[ i ]->get_generator(  ),&ud );
      }
    }
    printf("Currentkey:%x\r\n",nowtree->key);
    if (i+1 < analysis.block_count    )
    {
      senior->recover_vm_context();
      if (!b_j) 
        senior->push(nowtree->LeftChild->reloc_address);
      else
        senior->push(T_JCC_REGISTER);
      //senior->set_key(vcodebufs[i]->code.get_original_key());
      senior->set_key(nowtree->key); //handle设置key
    }
        
    //senior->recover_vm_context();      
  }
  address_table->copy();
  
  for (vector <VMCodeBufferManage*>::iterator iter = vcodebufs.begin(); iter != vcodebufs.end(); ++iter)
  {
    delete *iter;
  }
  pinfo->addr = head_address;
  return pinfo;
}
