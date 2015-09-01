/*
 *
 *   Copyrigth (C) Mon May 20 10:39:21 2013 XiaoWei
 *
 *                       handsomexiaowei@gmail.com
 *
 *
 */

#include "VirtualMachine.h"
//#include <time.h>
//#include <DataOperation.h>
#include "PCode.hpp"
#include <WProtectConfig.h>

VirtualMachine::VirtualMachine(long base)
{
  build_vm_handle(base);
}

VirtualMachine::VirtualMachine(long base,bool sign)
{
#ifdef DEBUG
  fprintf(stdout,"virtualmachine begin\r\n");
#endif
  handle.fuc_select.addorsub = sign;
  build_vm_handle(base);
#ifdef DEBUG
  fprintf(stdout,"virtualmachine end\r\n");
#endif
}

VirtualMachine::~VirtualMachine()
{
  list <ppcode_block_info>::iterator iter;
  for (iter = pcode_list.begin(); iter != pcode_list.end(); ++iter)
  {
    ppcode_block_info info = *iter;
    delete info;
  }
  
  for (list <handle_info>::iterator iter = handle_info_list.begin(); iter != handle_info_list.end(); ++iter)
  {

    handle_info dv = *iter;
  //printf("删除encode_key开始\r\n");
    //for (list <encryption>::iterator eiter = dv.encode_key.begin(); eiter != dv.encode_key.end();++eiter) //删除encode对象
#ifdef DEBUG

#endif    
    for (vector <encryption>::iterator eiter = dv.encode_key.begin(); eiter != dv.encode_key.end();++eiter) //删除encode对象
    {
      encryption en = *eiter;
      if (en.enfuc)
      {
        delete en.enfuc;
        en.enfuc = NULL;
      }
    }
#ifdef DEBUG
  //printf("删除encode_key成功\r\n");
#endif

    //for (list <decryption>::iterator diter = dv.decode_key.begin(); diter != dv.decode_key.end();++diter) //删除decode对象
    for (vector <decryption>::iterator diter = dv.decode_key.begin(); diter != dv.decode_key.end();++diter)
    {
      //decryption de = *diter;
      //
      if (diter->defuc)
      {
          delete diter->defuc;
          diter->defuc = NULL;
      }
    }
    for (list <vcode_encryption>::iterator eiter = dv.encode_pcode.begin(); eiter != dv.encode_pcode.end();++eiter) //删除encode对象
    {
      vcode_encryption en = *eiter;
      if (en.enfuc)
      delete en.enfuc;
      en.enfuc = NULL;
    }
    for (list <vcode_decryption>::iterator diter = dv.decode_pcode.begin(); diter != dv.decode_pcode.end();++diter)
    {
      vcode_decryption de = *diter;
      if (de.defuc)
        delete de.defuc;
      de.defuc = NULL;
    }
    //delete dv.encode_key;
    // delete dv.decode_key;
  }
}


template <class T>
T * upset(T * t,int nSize)  //把数据乱序后返回  其他类无法调用 需要增加一个接口
{
	T *temp=new T[nSize];
	int nowsize=nSize;
	while (nowsize)
	{
		int rd=rand()%nowsize;
		temp[nSize-nowsize]=t[rd];
		nowsize--;
		for (int i = 0; i < nowsize - rd; i++)
		{
			t[rd+i]=t[rd+1+i];
		}
	}
	memcpy(t,temp,nSize * sizeof(T));
	return t;
}

typedef handle_info (VMHandle::*v_handle)();

void VirtualMachine::build_vm_handle(long base)
{
  handle_info info;
  unsigned long handle_count = 0;
  v_handle handle_array[]={
    &VMHandle::b_read_stack,
    &VMHandle::w_read_stack,
    &VMHandle::d_read_stack,
    
    &VMHandle::b_write_stack,
    &VMHandle::w_write_stack,
    &VMHandle::d_write_stack,
    
    &VMHandle::b_push_reg,
    &VMHandle::w_puah_reg,
    &VMHandle::d_push_reg,
   
    &VMHandle::b_pop_reg,
    &VMHandle::w_pop_reg,
    &VMHandle::d_pop_reg,
    
    &VMHandle::b_push_imm,
    &VMHandle::w_push_imm,
    &VMHandle::d_push_imm,
    
    &VMHandle::b_shl,
    &VMHandle::w_shl,
    &VMHandle::d_shl,
    
    &VMHandle::b_shr,
    &VMHandle::w_shr,
    &VMHandle::d_shr,
    
    &VMHandle::shld,
    &VMHandle::shrd,
    &VMHandle::b_nand,
    &VMHandle::w_nand,
    &VMHandle::d_nand,
    
    &VMHandle::set_pc,
    &VMHandle::ret,
    &VMHandle::in,
    &VMHandle::rdtsc,
    &VMHandle::cpuid,
    &VMHandle::check_stack,
    &VMHandle::push_stack_top_base,
    &VMHandle::b_read_mem,
    &VMHandle::w_read_mem,
    &VMHandle::d_read_mem,
   
    &VMHandle::b_write_mem,
    &VMHandle::w_write_mem,
    &VMHandle::d_write_mem,
    
    &VMHandle::pop_stack_top_base,
    &VMHandle::b_push_imm_sx,
    &VMHandle::w_push_imm_sx,
    
    &VMHandle::b_push_imm_zx,
    &VMHandle::w_push_imm_zx,
   
    &VMHandle::b_add,
    &VMHandle::w_add,
    &VMHandle::d_add,

    &VMHandle::b_rol,
    &VMHandle::w_rol,
    &VMHandle::d_rol,
    &VMHandle::b_ror,
    &VMHandle::w_ror,
    &VMHandle::d_ror,

    &VMHandle::set_key,
    &VMHandle::run_stack_code,
    &VMHandle::fstsw
#ifdef DEBUG
    ,&VMHandle::int3
#endif

#ifdef PROTECT_X64
    ,&VMHandle::q_read_stack,
    &VMHandle::q_write_stack,
    &VMHandle::q_push_reg,
    &VMHandle::q_pop_reg,
    &VMHandle::q_push_imm,
    &VMHandle::q_shl,
    &VMHandle::q_shr,
    &VMHandle::q_nand,
    &VMHandle::q_read_mem,
    &VMHandle::q_write_mem,
    &VMHandle::d_push_imm_sx,
    &VMHandle::d_push_imm_zx,
    &VMHandle::q_add,
    &VMHandle::q_rol,
    &VMHandle::q_ror
#endif
  };
  handle_count = sizeof(handle_array) / sizeof (v_handle);
  upset<v_handle>(handle_array,handle_count);
  for (int i = 0; i < handle_count; i++)
  {
     v_handle r_fuc = handle_array[i];
    // printf("begin\r\n");
    info = (handle.*r_fuc)();
#ifdef DEBUG
    printf("%s\r\n",info.handle_name);
#endif
     //printf("end\r\n");
    handle_info_list.push_back(info);
  }

  long size = handle.a.getCodeSize();
#ifdef PROTECT_X64
  for (int i = 0; i < 0xff; i++)
  {
    handle.a.dq(rand());
  }
#else
  for (int i = 0; i < 0xff; i++)
  {
    handle.a.dd(rand());
  }
#endif
  dispatch_base = handle.a.getCodeSize() + base;
  info = handle.dispatch(base + size);
  
  full_handle_table(base,size);
  
  handle_info_list.push_back(info);
  
  handle_pcode.dispatch.encode_key = &handle_info_list.back().encode_key;
  handle_pcode.dispatch.encode_pcode = &handle_info_list.back().encode_pcode;
  /*
  typedef unsigned int (*d_MyFn)(unsigned int *);
  for (list<encryption>::iterator iter = handle_pcode.dispatch.encode_key->begin();
       iter != handle_pcode.dispatch.encode_key->end(); ++iter)
  {
    encryption p =  *iter;
    unsigned int i = 2;
    d_MyFn f= AsmJit::function_cast<d_MyFn>(p.enfuc->make());
    f(&i);
    // p.encode_key->make();
    }*/
  handle.a.relocCode(handle.a.getCode(),base);
  vm_info.base = base;
  vm_info.buf = handle.a.getCode();
  vm_info.size = handle.a.getCodeSize();
}

void VirtualMachine::add_pcode(AsmJit::Assembler &a,PCode *code,long base,long ret_address,long v_key,long decryption_key) //true表示正
{
  using namespace AsmJit;
  /*
  a.push(ret_address);
  a.push(v_key);
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
*/
  int register_count = code->register_store_in.register_count;
  
  for (int i = 0; i < register_count; ++i)
  {
    switch (code->register_store_in.register_array[i])
    {
    case T_NAX:
      a.push(nax);
      break;
    case T_NBX:
      a.push(nbx);
      break;
    case T_NCX:
      a.push(ncx);
      break;
    case T_NDX:
      a.push(ndx);
      break;
    case T_NSP:
        a.push(nsp);
      break;
    case T_NBP:
      a.push(nbp);
      break;
    case T_NSI:
      a.push(nsi);
      break;
    case T_NDI:
      a.push(ndi);
      break;
    case T_EFLAG:
#ifndef PROTECT_X64
      a.pushfd();
#else
      a.pushfq();
#endif
      break;
    case T_KEY:
      a.push(v_key);
      break;
    case T_RET:
      a.push(ret_address);
      break;
#ifdef PROTECT_X64
    case T_R8:
      a.push(r8);
      break;
    case T_R9:
      a.push(r9);
      break;
    case T_R10:
      a.push(r10);
      break;
    case T_R11:
      a.push(r11);
      break;
    case T_R12:
      a.push(r12);
      break;
    case T_R13:
      a.push(r13);
      break;
    case T_R14:
      a.push(r14);
      break;
    case T_R15:
      a.push(r15);
      break;
#endif
    }
    
  }
      a.mov(nbx,decryption_key);
      a.mov(nbp,nsp);
#ifndef PROTECT_X64
      a.sub(nsp,REG_NUMBER * 4 + VMSTACK_MIN_COUNT * 4 );
#else
      a.sub(nsp,REG_NUMBER * 8 + VMSTACK_MIN_COUNT * 8);
#endif
      a.mov(ndi,nsp);
      if (code->pcode_info.sign)
        a.mov(nsi,base + 50);
      else
        a.mov(esi,base + 50 + code->pcode_info.offset);
      a.jmp(dispatch_base);
}

ppcode_block_info VirtualMachine::create_function_head(long reloc_base,
                                                       long pcode_base,
                                                       PCode *pcode,
                                                       long ret_address,
                                                       long v_key,
                                                       long decryption_key)
{
  using namespace AsmJit;
  ppcode_block_info info = new pcode_block_info;
  info->entry = pcode_base;
    int register_count = pcode->register_store_in.register_count;
  
  for (int i = 0; i < register_count; ++i)
  {
    switch (pcode->register_store_in.register_array[i])
    {
    case T_NAX:
      info->a.push(nax);
      break;
    case T_NBX:
      info->a.push(nbx);
      break;
    case T_NCX:
      info->a.push(ncx);
      break;
    case T_NDX:
      info->a.push(ndx);
      break;
    case T_NSP:
        info->a.push(nsp);
      break;
    case T_NBP:
      info->a.push(nbp);
      break;
    case T_NSI:
      info->a.push(nsi);
      break;
    case T_NDI:
      info->a.push(ndi);
      break;
    case T_EFLAG:
#ifndef PROTECT_X64
      info->a.pushfd();
#else
      info->a.pushfq();
#endif
      break;
    case T_KEY:
      info->a.push(v_key);
      break;
    /*case T_RET:
      info->a.push(ret_address);
      break;
      */
#ifdef PROTECT_X64
    case T_R8:
      info->a.push(r8);
      break;
    case T_R9:
      info->a.push(r9);
      break;
    case T_R10:
      info->a.push(r10);
      break;
    case T_R11:
      info->a.push(r11);
      break;
    case T_R12:
      info->a.push(r12);
      break;
    case T_R13:
      info->a.push(r13);
      break;
    case T_R14:
      info->a.push(r14);
      break;
    case T_R15:
      info->a.push(r15);
      break;
#endif
    }
    
  }
      info->a.mov(nbx,decryption_key);
      info->a.mov(nbp,nsp);
#ifndef PROTECT_X64
      info->a.sub(nsp,REG_NUMBER * 4 + VMSTACK_MIN_COUNT * 4);
#else
      info->a.sub(nsp,REG_NUMBER * 8 + VMSTACK_MIN_COUNT * 8);
#endif
      info->a.mov(ndi,nsp);

      info->a.mov(nsi,pcode_base );
      info->a.jmp(dispatch_base);
  info->a.relocCode(info->a.getCode(),reloc_base);
  info->buf = info->a.getCode();
  info->size = info->a.getCodeSize();
  pcode_list.push_back(info);
  return info;
}

ppcode_block_info VirtualMachine::add_new_function(long base,PCode *code,long ret_address,long v_key,long decryption_key) //俩个key 一个是vm_context使用的 一个是ebx使用的解密Pcode key
{
  using namespace AsmJit;
  
  pcode_block_info *info = new pcode_block_info;
  info->entry = base;
  add_pcode(info->a,code,base,ret_address,v_key,decryption_key);
  if (code->pcode_info.sign)
  {
    info->pcode_base = base + 50;
    long init_handle_size = 50 - info->a.getCodeSize();
    for (int i = 0; i < init_handle_size; i++)
    {
      info->a.db(0xff & rand());
    }
    for (int i = 0; i < code->pcode_info.offset; i++)
    {
      info->a.db(code->pcode_info.buf[i]);
    }
    //return handle_offset;
  }
  else
  {
    info->pcode_base = base + 50 + code->pcode_info.offset;
    long init_handle_size = 50 - info->a.getCodeSize();
    for (int i = 0; i < init_handle_size; i++)
    {
      info->a.db(0xff & rand());
    }
    for (int i = code->pcode_info.size - code->pcode_info.offset; i < code->pcode_info.size; i++)
    {
      info->a.db(code->pcode_info.buf[i]);
    }
    //    return handle_offset;
  }
  info->a.relocCode(info->a.getCode(),base);
  info->buf = info->a.getCode();
  info->size = info->a.getCodeSize();
  pcode_list.push_back(info);
  /*
  long handle_offset = handle.a.getCodeSize();
  if (code->pcode_info.sign)
  {
    handle.initialization(base + 50);
    long init_handle_size = 50 - (handle.a.getCodeSize() - handle_offset);
    for (int i = 0; i < init_handle_size; i++)
    {
      handle.a.db(0xff & rand());
    }
    for (int i = 0; i < code->pcode_info.offset; i++)
    {
      handle.a.db(code->pcode_info.buf[i]);
    }
    //return handle_offset;
  }
  else
  {
    handle.initialization(base + 50 + code->pcode_info.offset); //50个byte是为这个handle预留的
    long init_handle_size = 50 - (handle.a.getCodeSize() - handle_offset);
    for (int i = 0; i < init_handle_size; i++)
    {
      handle.a.db(0xff & rand());
    }
    for (int i = code->pcode_info.size - code->pcode_info.offset; i < code->pcode_info.size; i++)
    {
      handle.a.db(code->pcode_info.buf[i]);
    }
    //    return handle_offset;
    }*/

  return info;
}


void VirtualMachine::full_handle_table(long base,long table_offset)
{
  unsigned char * asmbuf = handle.a.getCode();
  unsigned long * buf = (unsigned long *)(asmbuf + table_offset);
  unsigned long count = 1;


#ifdef DEBUG
  FILE *file = fopen("VMHandleAddress.txt","wb");
  fprintf(file, "var note\r\n");
#endif
  for (list <handle_info>::iterator iter = handle_info_list.begin(); iter != handle_info_list.end(); ++iter)
  {
    pVMHandleInfo instruction = NULL;
    handle_info info = *iter;
    buf[count] = info.offset + base;
#ifdef DEBUG
    fprintf(file,"mov eip,401000\r\n");    
    fprintf(file,"mov note,%x\r\n",buf[count]);
    fprintf(file,"cmt note,\"%s\"\r\n ",info.handle_name);
    fprintf(file,"lbl note,\"%s\"\r\n ",info.handle_name);    
#endif
    if ( info.label == &handle.l_b_read_stack )
    {
        instruction = &handle_pcode.b_read_stack;
    } else  if ( info.label == &handle.l_w_read_stack )
    {
        instruction = &handle_pcode.w_read_stack;
    } else  if ( info.label == &handle.l_d_read_stack )
    {
        instruction = &handle_pcode.d_read_stack;
    } else  if ( info.label == &handle.l_b_write_stack )
    {
        instruction = &handle_pcode.b_write_stack;
    } else  if ( info.label == &handle.l_w_write_stack )
    {
        instruction = &handle_pcode.w_write_stack;
    } else  if ( info.label == &handle.l_d_write_stack )
    {
        instruction = &handle_pcode.d_write_stack;
    }  else  if ( info.label == &handle.l_b_push_reg )
    {
        instruction = &handle_pcode.b_push_reg;
    } else  if ( info.label == &handle.l_w_push_reg )
    {
        instruction = &handle_pcode.w_push_reg;
    } else  if ( info.label == &handle.l_d_push_reg )
    {
        instruction = &handle_pcode.d_push_reg;
    }  else  if ( info.label == &handle.l_b_pop_reg )
    {
        instruction = &handle_pcode.b_pop_reg;
    } else  if ( info.label == &handle.l_w_pop_reg )
    {
        instruction = &handle_pcode.w_pop_reg;
    } else  if ( info.label == &handle.l_d_pop_reg )
    {
        instruction = &handle_pcode.d_pop_reg;
    }  else  if ( info.label == &handle.l_b_push_imm )
    {
        instruction = &handle_pcode.b_push_imm;
    } else  if ( info.label == &handle.l_w_push_imm )
    {
        instruction = &handle_pcode.w_push_imm;
    } else  if ( info.label == &handle.l_d_push_imm )
    {
        instruction = &handle_pcode.d_push_imm;
    }  else  if ( info.label == &handle.l_b_shl )
    {
        instruction = &handle_pcode.b_shl;
    } else  if ( info.label == &handle.l_w_shl )
    {
        instruction = &handle_pcode.w_shl;
    } else  if ( info.label == &handle.l_d_shl )
    {
        instruction = &handle_pcode.d_shl;
    }  else  if ( info.label == &handle.l_b_shr )
    {
        instruction = &handle_pcode.b_shr;
    } else  if ( info.label == &handle.l_w_shr )
    {
        instruction = &handle_pcode.w_shr;
    } else  if ( info.label == &handle.l_d_shr )
    {
        instruction = &handle_pcode.d_shr;
    }  else  if ( info.label == &handle.l_shld )
    {
        instruction = &handle_pcode.shld;
    } else  if ( info.label == &handle.l_shrd )
    {
        instruction = &handle_pcode.shrd;
    } else  if ( info.label == &handle.l_b_nand )
    {
        instruction = &handle_pcode.b_nand;
    } else  if ( info.label == &handle.l_w_nand )
    {
        instruction = &handle_pcode.w_nand;
    } else  if ( info.label == &handle.l_d_nand )
    {
        instruction = &handle_pcode.d_nand;
    }  else  if ( info.label == &handle.l_set_pc )
    {
        instruction = &handle_pcode.set_pc;
    } else  if ( info.label == &handle.l_ret )
    {
        instruction = &handle_pcode.ret;
    } else  if ( info.label == &handle.l_in )
    {
        instruction = &handle_pcode.in;
    } else  if ( info.label == &handle.l_rdtsc )
    {
        instruction = &handle_pcode.rdtsc;
    } else  if ( info.label == &handle.l_cpuid )
    {
        instruction = &handle_pcode.cpuid;
    } else  if ( info.label == &handle.l_check_stack )
    {
        instruction = &handle_pcode.check_stack;
    } else  if ( info.label == &handle.l_dispatch )
    {
        instruction = &handle_pcode.dispatch;
    } else  if ( info.label == &handle.l_push_stack_top_base )
    {
        instruction = &handle_pcode.push_stack_top_base;
    } else if ( info.label == &handle.l_b_read_mem)
    {
        instruction = &handle_pcode.b_read_mem;
    } else if ( info.label == &handle.l_w_read_mem)
    {
        instruction = &handle_pcode.w_read_mem;
    } else if ( info.label == &handle.l_d_read_mem)
    {
        instruction = &handle_pcode.d_read_mem;
    }  else if ( info.label == &handle.l_b_write_mem)
    {
        instruction = &handle_pcode.b_write_mem;
    } else if ( info.label == &handle.l_w_write_mem)
    {
        instruction = &handle_pcode.w_write_mem;
    } else if ( info.label == &handle.l_d_write_mem)
    {
        instruction = &handle_pcode.d_write_mem;
    }  else if ( info.label == &handle.l_b_push_imm_sx )
    {
        instruction = &handle_pcode.b_push_imm_sx;
    } else if ( info.label == &handle.l_w_push_imm_sx )
    {
        instruction = &handle_pcode.w_push_imm_sx;
    }  else if ( info.label == &handle.l_b_push_imm_zx )
    {
        instruction = &handle_pcode.b_push_imm_zx;
    } else if ( info.label == &handle.l_w_push_imm_zx )
    {
        instruction = &handle_pcode.w_push_imm_zx;
    }  else if ( info.label == &handle.l_pop_stack_top_base)
    {
        instruction = &handle_pcode.pop_stack_top_base;
    } else if ( info.label == &handle.l_b_add)
    {
        instruction = &handle_pcode.b_add;
    } else if ( info.label == &handle.l_w_add)
    {
        instruction = &handle_pcode.w_add;
    } else if ( info.label == &handle.l_d_add)
    {
        instruction = &handle_pcode.d_add;
    }  else if ( info.label == &handle.l_b_rol)
    {
        instruction = &handle_pcode.b_rol;
    } else if ( info.label == &handle.l_w_rol)
    {
        instruction = &handle_pcode.w_rol;
    } else if ( info.label == &handle.l_d_rol)
    {
        instruction = &handle_pcode.d_rol;
    }  else if ( info.label == &handle.l_b_ror)
    {
        instruction = &handle_pcode.b_ror;
    } else if ( info.label == &handle.l_w_ror)
    {
        instruction = &handle_pcode.w_ror;
    } else if ( info.label == &handle.l_d_ror)
    {
        instruction = &handle_pcode.d_ror;
    } else if ( info.label == &handle.l_set_key )
    {
       instruction = &handle_pcode.set_key;
    } else if ( info.label == &handle.l_run_stack_code)
    {
        instruction = &handle_pcode.run_stack;
    } else if ( info.label == &handle.l_fstsw)
    {
        instruction = &handle_pcode.fstsw;
    }
#ifdef DEBUG
    else if ( info.label == &handle.l_int3)
    {
        instruction = &handle_pcode.int3;
    }
#endif

#ifdef PROTECT_X64
    else if ( info.label == &handle.l_q_ror)
    {
        instruction = &handle_pcode.q_ror;
    }else  if ( info.label == &handle.l_q_read_stack )
    {
        instruction = &handle_pcode.q_read_stack;
    }  else  if ( info.label == &handle.l_q_write_stack )
    {
        instruction = &handle_pcode.q_write_stack;
    }else  if ( info.label == &handle.l_q_push_reg )
    {
        instruction = &handle_pcode.q_push_reg;
    }else  if ( info.label == &handle.l_q_pop_reg )
    {
        instruction = &handle_pcode.q_pop_reg;
    }else  if ( info.label == &handle.l_q_push_imm )
    {
        instruction = &handle_pcode.q_push_imm;
    }else  if ( info.label == &handle.l_q_shl )
    {
        instruction = &handle_pcode.q_shl;
    }else  if ( info.label == &handle.l_q_shr )
    {
        instruction = &handle_pcode.q_shr;
    }else  if ( info.label == &handle.l_q_nand )
    {
        instruction = &handle_pcode.q_nand;
    }else if ( info.label == &handle.l_q_read_mem)
    {
        instruction = &handle_pcode.q_read_mem;
    }else if ( info.label == &handle.l_q_write_mem)
    {
        instruction = &handle_pcode.q_write_mem;
    }else if ( info.label == &handle.l_d_push_imm_sx )
    {
        instruction = &handle_pcode.d_push_imm_sx;
    }else if ( info.label == &handle.l_d_push_imm_zx )
    {
        instruction = &handle_pcode.d_push_imm_zx;
    }else if ( info.label == &handle.l_q_add)
    {
        instruction = &handle_pcode.q_add;
    }else if ( info.label == &handle.l_q_rol)
    {
        instruction = &handle_pcode.q_rol;
    }
#endif
    else
    {
#ifdef DEBUG
      fprintf(stderr,"%s:%d:%s\r\n",__FILE__,__LINE__,info.handle_name);
#endif
      // continue;
    }
    if (instruction == NULL)
    {
#ifdef DEBUG
      fprintf(stderr,"%s:%d:%s\r\n",__FILE__,__LINE__,info.handle_name);
#endif    
    }
    instruction->handle = count++;
    instruction->encode_key = &iter->encode_key;
    instruction->type = info.type;
    instruction->encode_pcode = &iter->encode_pcode;
  }
}
