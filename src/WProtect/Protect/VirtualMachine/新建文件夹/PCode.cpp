/*
 *
 *   Copyright (C) Sun Jun  9 22:03:40 2013 XiaoWei
 *
 *                       handsomexiaowei@gmail.com
 *
 *
 */

#include "PCode.hpp"
#include <iostream>
#include <string.h>
#include <WProtectConfig.h>
#include <algorithms>

PCode::PCode()
  : _key_(m_random()),key(_key_),r_pc_size(0)
#ifdef DEBUG
  ,v_log(NULL)
#endif
{
  pcode_info.size = 0xFFFF;
  pcode_info.buf = new unsigned char [pcode_info.size];
  pcode_info.offset = 0;
  for (int i = 0; i < REG_NUMBER; i++)
  {
    v_reg_context.vr[i].reg_id = T_INVALID;
    v_reg_context.vr[i].reg_offset = i*4;
  }
#ifdef DEBUG
  char save_log = 'N';
  fprintf(stdout,"是否保存VM流程到文件:Y/N\r\n");
  //scanf("%c",&save_log);
  if (save_log == 'Y' || save_log == 'y')
  {
    v_log = fopen("vm_log.txt","wb");
  }
  else
    v_log = stdout;
#endif

    int register_count = 0;
#ifdef PROTECT_X64
  register_store_in.register_array[register_count++] = T_R15;
  register_store_in.register_array[register_count++] = T_R14;
  register_store_in.register_array[register_count++] = T_R13;
  register_store_in.register_array[register_count++] = T_R12;
  register_store_in.register_array[register_count++] = T_R11;
  register_store_in.register_array[register_count++] = T_R10;
  register_store_in.register_array[register_count++] = T_R9;
  register_store_in.register_array[register_count++] = T_R8;

#endif
  register_store_in.register_array[register_count++] = T_NDI ;
  register_store_in.register_array[register_count++] = T_NSI ;
  register_store_in.register_array[register_count++] = T_NBP ;
  register_store_in.register_array[register_count++] = T_NSP ;
  register_store_in.register_array[register_count++] = T_NBX ;
  register_store_in.register_array[register_count++] = T_NDX ;
  register_store_in.register_array[register_count++] = T_NCX ;
  register_store_in.register_array[register_count++] = T_NAX ;
  register_store_in.register_array[register_count++] = T_EFLAG ;
  register_store_in.register_array[register_count++] = T_KEY;
  register_store_in.register_array[register_count++] = T_RET;
  
  upset<long>(register_store_in.register_array,register_count);

  register_store_in.register_count = register_count;
}

PCode::PCode(vm_handle table,bool sign)
  : _key_(m_random()),key(_key_),r_pc_size(0)
#ifdef DEBUG
  ,v_log(NULL)
#endif
{
  pcode_info.size = 0xFFFF;
  pcode_info.buf = new unsigned char [pcode_info.size];
  pcode_info.offset = 0;
  init_handle_table(table);
  init_sign(sign);
  for (int i = 0; i < REG_NUMBER; i++)
  {
    v_reg_context.vr[i].reg_id = T_INVALID;
    v_reg_context.vr[i].reg_offset = i*4;
  }
#ifdef DEBUG
  char save_log = 'N';
  fprintf(stdout,"是否保存VM流程:Y/n\r\n");
  scanf("%c",&save_log);
  if (save_log == 'Y' || save_log == 'y')
  {
    v_log = fopen("vm_log.txt","wb");
  }
  else
    v_log = stdout;
#endif

  int register_count = 0;
#ifdef PROTECT_X64
  register_store_in.register_array[register_count++] = T_R15;
  register_store_in.register_array[register_count++] = T_R14;
  register_store_in.register_array[register_count++] = T_R13;
  register_store_in.register_array[register_count++] = T_R12;
  register_store_in.register_array[register_count++] = T_R11;
  register_store_in.register_array[register_count++] = T_R10;
  register_store_in.register_array[register_count++] = T_R9;
  register_store_in.register_array[register_count++] = T_R8;

#endif
  register_store_in.register_array[register_count++] = T_NDI ;
  register_store_in.register_array[register_count++] = T_NSI ;
  register_store_in.register_array[register_count++] = T_NBP ;
  register_store_in.register_array[register_count++] = T_NSP ;
  register_store_in.register_array[register_count++] = T_NBX ;
  register_store_in.register_array[register_count++] = T_NDX ;
  register_store_in.register_array[register_count++] = T_NCX ;
  register_store_in.register_array[register_count++] = T_NAX ;
  register_store_in.register_array[register_count++] = T_EFLAG ;
    register_store_in.register_array[register_count++] = T_KEY;
  register_store_in.register_array[register_count++] = T_RET;
  upset<long>(register_store_in.register_array,register_count);

  register_store_in.register_count = register_count;
}

/*
PCode::PCode(VirtualMachine *pvm)
{
  pcode_info.size = 0xFFFF;
  pcode_info.buf = new unsigned char [pcode_info.size];
  pcode_info.offset = 0;
  init_handle_table(pvm->handle_pcode);
  init_sign(pvm->handle.fuc_select.addorsub);
  for (int i = 0; i < REG_NUMBER; i++)
  {
    v_reg_context.vr[i].reg_id = T_INVALID;
    v_reg_context.vr[i].reg_offset = i*4;
  }
  }*/

PCode::~PCode()
{
  if (pcode_info.buf)
  {
    delete [] pcode_info.buf;
    pcode_info.buf = NULL;
  }
#ifdef DEBUG
  if (v_log != stdout)
  {
    fclose(v_log);
  }
#endif
}

#ifdef PROTECT_X64
const unsigned long
#else
const unsigned int
#endif
PCode::get_original_key() 
{
  return _key_;
}

#ifdef PROTECT_X64
const unsigned long
#else
const unsigned int
#endif
PCode::get_current_key()
{
  return key;
}

typedef unsigned char (*b_MyFn)(unsigned char *);
typedef unsigned short (*w_MyFn)(unsigned short *);
typedef unsigned int (*d_MyFn)(unsigned int *);
typedef unsigned long (*q_MyFn)(unsigned long *);

#ifdef PROTECT_X64
typedef q_MyFn KeyFn;
#else
typedef d_MyFn KeyFn;
#endif

size_t PCode::get_code_size()
{
  return pcode_info.offset;
}

void PCode::call_encode_pcode_fn(vcode_encryption::MyFn fn,void *data,long * ikey)
{
  /*  if (*ikey)
  {
    fn(data,ikey);
  }
  else
  {
    fn(data,&key);
  }
  return;*/
  using namespace AsmJit;
  AsmJit::Assembler a;
FileLogger logger(stderr);  
  a.setLogger(&logger);  
  //fn(data,ikey);
  printf("sysint_t :%d\r\n",sizeof(sysint_t));

  if (*ikey)
  {
    //    a.push((unsigned long long)ikey);
    //a.push((unsigned long long)data);
    a.mov(nax,(long)ikey);
    a.push(nax);
    a.mov(nax,(long)data);
    a.push(nax);
#ifdef PROTECT_X64
    a.call((void*)fn);
    a.add(nsp,16);
    a.ret();
#else
    a.call((void*)fn);
    a.add(nsp,8);
    a.ret();
#endif
    typedef void (*f)();
    
    f mycall = function_cast<f>(a.make());
    mycall();
  }
  else
  {
    // a.push((unsigned long)&key);
    // a.push((unsigned long)data);
    a.mov(nax,(long)&key);
    a.push(nax);
    a.mov(nax,(long)data);
    a.push(nax);
#ifdef PROTECT_X64
    a.call((void*)fn);
    a.add(nsp,16);
    a.ret();
#else
    a.call((void*)fn);
    a.add(nsp,8);
    a.ret();
#endif
    typedef void (*f)();
    
    f mycall = function_cast<f>(a.make());
    mycall();           
  }
}


void PCode::db(unsigned char b)
{
  if (!r_pc_size)
  {
      pVMHandleInfo instruction = (pVMHandleInfo)&pcode_info.handle_table;  //这里拦截VM指令
      int count = sizeof(vm_handle)/sizeof(VMHandleInfo);
      while (count != 0)
      { 
        if (instruction->handle == b) //获取到handle了
        {
#ifdef DEBUG
          if (b == pcode_info.handle_table.b_write_stack.handle)
          {
            printf("handle:%d,d_pop_reg:%d\r\n",b,pcode_info.handle_table.d_pop_reg.handle);
            __asm__ ("int $3");
          }
#endif
#ifdef DEBUG
          char *f = "VM_Handle: ";
          char *l = "";
          if (pcode_info.handle_table.b_read_stack.handle == b)
            fprintf(v_log,"%s%s%s",f,"b_read_stack",l);
          else if (pcode_info.handle_table.w_read_stack.handle == b)
            fprintf(v_log,"%s%s%s",f,"w_read_stack",l);
          else if (pcode_info.handle_table.d_read_stack.handle == b)
            fprintf(v_log,"%s%s%s",f,"d_read_stack",l);

          else if (pcode_info.handle_table.b_write_stack.handle == b)
            fprintf(v_log,"%s%s%s",f,"b_write_stack",l);
          else if (pcode_info.handle_table.w_write_stack.handle == b)
            fprintf(v_log,"%s%s%s",f,"w_write_stack",l);
          else if (pcode_info.handle_table.d_write_stack.handle == b)
            fprintf(v_log,"%s%s%s",f,"d_write_stack",l);

#ifdef PROTECT_X64
          else if (pcode_info.handle_table.q_nand.handle == b)
            fprintf(v_log,"%s%s%s",f,"q_nand",l);
          else if (pcode_info.handle_table.q_push_imm.handle == b)
            fprintf(v_log,"%s%s%s",f,"q_push_imm",l);
          else if (pcode_info.handle_table.q_shl.handle == b)
            fprintf(v_log,"%s%s%s",f,"q_shl",l);
          else if (pcode_info.handle_table.q_push_imm.handle == b)
            fprintf(v_log,"%s%s%s",f,"q_push_imm",l);
          else if (pcode_info.handle_table.q_pop_reg.handle == b)
            fprintf(v_log,"%s%s%s",f,"q_pop_reg",l);
          else if (pcode_info.handle_table.q_push_reg.handle == b)
            fprintf(v_log,"%s%s%s",f,"q_push_reg",l);
          else if (pcode_info.handle_table.q_read_stack.handle == b)
            fprintf(v_log,"%s%s%s",f,"q_read_stack",l);
          else if (pcode_info.handle_table.q_write_stack.handle == b)
            fprintf(v_log,"%s%s%s",f,"q_write_stack",l);
          else if (pcode_info.handle_table.q_shl.handle == b)
            fprintf(v_log,"%s%s%s",f,"q_shl",l);
          else if (pcode_info.handle_table.q_shr.handle == b)
            fprintf(v_log,"%s%s%s",f,"q_shr",l);
          else if (pcode_info.handle_table.q_ror.handle == b)
            fprintf(v_log,"%s%s%s",f,"q_ror",l);
          else if (pcode_info.handle_table.q_add.handle == b)
            fprintf(v_log,"%s%s%s",f,"q_add",l);
          else if (pcode_info.handle_table.q_rol.handle == b)
            fprintf(v_log,"%s%s%s",f,"q_rol",l);
          else if (pcode_info.handle_table.q_read_mem.handle == b)
            fprintf(v_log,"%s%s%s",f,"q_read_mem",l);
          else if (pcode_info.handle_table.q_write_mem.handle == b)
            fprintf(v_log,"%s%s%s",f,"q_write_mem",l);
          else if (pcode_info.handle_table.d_push_imm_sx.handle == b)
            fprintf(v_log,"%s%s%s",f,"d_push_imm_sx",l);
          else if (pcode_info.handle_table.d_push_imm_zx.handle == b)
            fprintf(v_log,"%s%s%s",f,"d_push_imm_zx",l);          
#endif
          else if (pcode_info.handle_table.b_push_reg.handle == b)
            fprintf(v_log,"%s%s%s",f,"b_push_reg",l);
          else if (pcode_info.handle_table.w_push_reg.handle == b)
            fprintf(v_log,"%s%s%s",f,"w_push_reg",l);
          else if (pcode_info.handle_table.d_push_reg.handle == b)
            fprintf(v_log,"%s%s%s",f,"d_push_reg",l);

          else if (pcode_info.handle_table.b_pop_reg.handle == b)
            fprintf(v_log,"%s%s%s",f,"b_pop_reg",l);
          else if (pcode_info.handle_table.w_pop_reg.handle == b)
            fprintf(v_log,"%s%s%s",f,"w_pop_reg",l);
          else if (pcode_info.handle_table.d_pop_reg.handle == b)
            fprintf(v_log,"%s%s%s",f,"d_pop_reg",l);

          else if (pcode_info.handle_table.b_push_imm.handle == b)
            fprintf(v_log,"%s%s%s",f,"b_push_imm",l);
          else if (pcode_info.handle_table.w_push_imm.handle == b)
            fprintf(v_log,"%s%s%s",f,"w_push_imm",l);
          else if (pcode_info.handle_table.d_push_imm.handle == b)
            fprintf(v_log,"%s%s%s",f,"d_push_imm",l);

          else if (pcode_info.handle_table.b_shl.handle == b)
            fprintf(v_log,"%s%s%s",f,"b_shl",l);
          else if (pcode_info.handle_table.w_shl.handle == b)
            fprintf(v_log,"%s%s%s",f,"w_shl",l);
          else if (pcode_info.handle_table.d_shl.handle == b)
            fprintf(v_log,"%s%s%s",f,"d_shl",l);

          else if (pcode_info.handle_table.b_shr.handle == b)
            fprintf(v_log,"%s%s%s",f,"b_shr",l);
          else if (pcode_info.handle_table.w_shr.handle == b)
            fprintf(v_log,"%s%s%s",f,"w_shr",l);
          else if (pcode_info.handle_table.d_shr.handle == b)
            fprintf(v_log,"%s%s%s",f,"d_shr",l);
          else if (pcode_info.handle_table.b_push_imm.handle == b)
            fprintf(v_log,"%s%s%s",f,"b_push_imm",l);
          else if (pcode_info.handle_table.w_push_imm.handle == b)
            fprintf(v_log,"%s%s%s",f,"w_push_imm",l);
          else if (pcode_info.handle_table.d_push_imm.handle == b)
            fprintf(v_log,"%s%s%s",f,"d_push_imm",l);

          else if (pcode_info.handle_table.b_shl.handle == b)
            fprintf(v_log,"%s%s%s",f,"b_shl",l);
          else if (pcode_info.handle_table.w_shl.handle == b)
            fprintf(v_log,"%s%s%s",f,"w_shl",l);
          else if (pcode_info.handle_table.d_shl.handle == b)
            fprintf(v_log,"%s%s%s",f,"d_shl",l);

          else if (pcode_info.handle_table.b_shr.handle == b)
            fprintf(v_log,"%s%s%s",f,"b_shr",l);
          else if (pcode_info.handle_table.w_shr.handle == b)
            fprintf(v_log,"%s%s%s",f,"w_shr",l);
          else if (pcode_info.handle_table.d_shr.handle == b)
            fprintf(v_log,"%s%s%s",f,"d_shr",l);

          else if (pcode_info.handle_table.shld.handle == b)
            fprintf(v_log,"%s%s%s",f,"shld",l);
          else if (pcode_info.handle_table.shrd.handle == b)
            fprintf(v_log,"%s%s%s",f,"shrd",l);
          else if (pcode_info.handle_table.b_nand.handle == b)
            fprintf(v_log,"%s%s%s",f,"b_nand",l);
          else if (pcode_info.handle_table.w_nand.handle == b)
            fprintf(v_log,"%s%s%s",f,"w_nand",l);
          else if (pcode_info.handle_table.d_nand.handle == b)
            fprintf(v_log,"%s%s%s",f,"d_nand",l);
          else if (pcode_info.handle_table.set_pc.handle == b)
            fprintf(v_log,"%s%s%s",f,"set_pc",l);
          else if (pcode_info.handle_table.ret.handle == b)
            fprintf(v_log,"%s%s%s",f,"ret",l);
          else if (pcode_info.handle_table.in.handle == b)
            fprintf(v_log,"%s%s%s",f,"in",l);
          else if (pcode_info.handle_table.rdtsc.handle == b)
            fprintf(v_log,"%s%s%s",f,"rdtsc",l);
          else if (pcode_info.handle_table.cpuid.handle == b)
            fprintf(v_log,"%s%s%s",f,"cpuid",l);
          else if (pcode_info.handle_table.check_stack.handle == b)
            fprintf(v_log,"%s%s%s",f,"check_stack",l);
          else if (pcode_info.handle_table.dispatch.handle == b)
            fprintf(v_log,"%s%s%s",f,"dispatch",l);
          else if (pcode_info.handle_table.push_stack_top_base.handle == b)
            fprintf(v_log,"%s%s%s",f,"push_stack_top_base",l);
          else if (pcode_info.handle_table.b_read_mem.handle == b)
            fprintf(v_log,"%s%s%s",f,"b_read_mem",l);
          else if (pcode_info.handle_table.w_read_mem.handle == b)
            fprintf(v_log,"%s%s%s",f,"w_read_mem",l);
          else if (pcode_info.handle_table.d_read_mem.handle == b)
            fprintf(v_log,"%s%s%s",f,"d_read_mem",l);
          else if (pcode_info.handle_table.b_write_mem.handle == b)
            fprintf(v_log,"%s%s%s",f,"b_write_mem",l);
          else if (pcode_info.handle_table.w_write_mem.handle == b)
            fprintf(v_log,"%s%s%s",f,"w_write_mem",l);
          else if (pcode_info.handle_table.d_write_mem.handle == b)
            fprintf(v_log,"%s%s%s",f,"d_write_mem",l);


          else if (pcode_info.handle_table.pop_stack_top_base.handle == b)
            fprintf(v_log,"%s%s%s",f,"pop_stack_top_base",l);
          else if (pcode_info.handle_table.b_push_imm_sx.handle == b)
            fprintf(v_log,"%s%s%s",f,"b_push_imm_sx",l);
          else if (pcode_info.handle_table.w_push_imm_sx.handle == b)
            fprintf(v_log,"%s%s%s",f,"w_push_imm_sx",l);
          else if (pcode_info.handle_table.b_push_imm_zx.handle == b)
            fprintf(v_log,"%s%s%s",f,"b_push_imm_zx",l);
          else if (pcode_info.handle_table.w_push_imm_zx.handle == b)
            fprintf(v_log,"%s%s%s",f,"w_push_imm_zx",l);
          else if (pcode_info.handle_table.b_add.handle == b)
            fprintf(v_log,"%s%s%s",f,"b_add",l);
          else if (pcode_info.handle_table.w_add.handle == b)
            fprintf(v_log,"%s%s%s",f,"w_add",l);
          else if (pcode_info.handle_table.d_add.handle == b)
            fprintf(v_log,"%s%s%s",f,"d_add",l);

          else if (pcode_info.handle_table.b_rol.handle == b)
            fprintf(v_log,"%s%s%s",f,"b_rol",l);
          else if (pcode_info.handle_table.w_rol.handle == b)
            fprintf(v_log,"%s%s%s",f,"w_rol",l);
          else if (pcode_info.handle_table.d_rol.handle == b)
            fprintf(v_log,"%s%s%s",f,"d_rol",l);

          else if (pcode_info.handle_table.b_ror.handle == b)
            fprintf(v_log,"%s%s%s",f,"b_ror",l);
          else if (pcode_info.handle_table.w_ror.handle == b)
            fprintf(v_log,"%s%s%s",f,"w_ror",l);
          else if (pcode_info.handle_table.d_ror.handle == b)
            fprintf(v_log,"%s%s%s",f,"d_ror",l);
#endif
         r_pc_size = instruction->type;
#ifdef DEBUG
         if (r_pc_size == 0)
         {
           fprintf(v_log,"()\r\n");
         }
#endif
         pVMHandleInfo dispatch_en_key = &pcode_info.handle_table.dispatch;
         for (vector<encryption>::iterator iter  //这是虚拟机派遣函数的加密KEY
                = dispatch_en_key->encode_key->begin();
              iter != dispatch_en_key->encode_key->end();
              ++iter)
         {
           //encryption en_key = *iter;
#ifdef DEBUG
           //fprintf(v_log,"dispatch old key:%x\r\n",key);
#endif
           //en_key.fn(&key);
           iter->fn(&key);
#ifdef DEBUG
           fprintf(v_log,"dispatch new key:%x\r\n",key);
#endif
         }
          for (list<vcode_encryption>::reverse_iterator iter =
                dispatch_en_key->encode_pcode->rbegin();
              iter != dispatch_en_key->encode_pcode->rend();
              ++iter)
         {
           call_encode_pcode_fn(iter->fn,&b,&iter->key);
           if (iter->key)
           {
             //            iter->fn(&b,&iter->key);
           }
           else
           {
             //     iter->fn(&b,&key);
           }
         }
         ////先动态加密KEY////
#ifdef DEBUG
         if (instruction->encode_key == NULL)
         {
           printf("error encode_key_list emliy\r\n");
         } else
#endif
         for (vector<encryption>::iterator iter2 = instruction->encode_key->begin();
              iter2 != instruction->encode_key->end(); ++iter2) //可能出现q_read_mem错误
         {
           //           fprintf(v_log,"begin\r\n");
             iter2->fn(&key);

           //           encryption en_key = *iter2;
           //           en_key.fn(&key);
           //  fprintf(v_log,"end\r\n");
         }
         current_instruction = instruction;
#ifdef DEBUG
         printf("key:%x\r\n",key);
#endif
         break;
        }
        instruction++; //这个不能放在前面否则会导致读取到q_read_mem
        count--;
      }
  }
  else
  {
     for (list<vcode_encryption>::reverse_iterator iter = current_instruction->encode_pcode->rbegin();
              iter != current_instruction->encode_pcode->rend(); ++iter) //可能出现q_read_mem错误
     {
       call_encode_pcode_fn(iter->fn,&b,&iter->key); //兼容64程序
       //if (iter2->key)
       //  iter2->fn(&b,&iter2->key);
       //else
       //  iter2->fn(&b,&key);
     }
     current_instruction = NULL;
#ifdef DEBUG
    fprintf(v_log,"(0%x)\r\n",b);
#endif
    r_pc_size = 0; //不是虚拟pcode而是读取数据
  }
  
  
  check_pcode_buf();
  if (pcode_info.sign == false)
  {
    pcode_info.buf[pcode_info.size - 1 - pcode_info.offset] = b;
  }
  else
  {
    pcode_info.buf[pcode_info.offset] = b;
  }
  pcode_info.offset++;
}

void PCode::dw(unsigned short w)
{
  if (r_pc_size)
  {
#ifdef DEBUG
    fprintf(v_log,"(0%x)\r\n",w);
#endif
     for (list<vcode_encryption>::reverse_iterator iter = current_instruction->encode_pcode->rbegin();
              iter != current_instruction->encode_pcode->rend(); ++iter) //可能出现q_read_mem错误
     {
       call_encode_pcode_fn(iter->fn,&w,&iter->key);
       //if (iter2->key)
       //  iter2->fn(&w,&iter2->key);
       //else
       //  iter2->fn(&w,&key);
     }
     current_instruction = NULL;    
    r_pc_size = 0;
  }
  check_pcode_buf();
  if (pcode_info.sign == false)
  {
    unsigned short * buf = (unsigned short *)&pcode_info.buf[pcode_info.size - 2 - pcode_info.offset];
    *buf = w;
  }
  else
  {
    unsigned short * buf = (unsigned short *)&pcode_info.buf[pcode_info.offset];
    *buf = w;
  }
  pcode_info.offset += 2;
}

void PCode::dd(unsigned int d)
{
  if (r_pc_size)
  {
#ifdef DEBUG
    fprintf(v_log,"(0%x)\r\n",d);
#endif
     for (list<vcode_encryption>::reverse_iterator iter = current_instruction->encode_pcode->rbegin();
              iter != current_instruction->encode_pcode->rend(); ++iter) //可能出现q_read_mem错误
     {
       call_encode_pcode_fn(iter->fn,&d,&iter->key);
       //if (iter2->key)
       //  iter2->fn(&d,&iter2->key);
       //else
       //  iter2->fn(&d,&key);
     }
     current_instruction = NULL;    
    r_pc_size = 0;
  }
  check_pcode_buf();
  if (pcode_info.sign == false)
  {
     unsigned int * buf = (unsigned int *)&pcode_info.buf[pcode_info.size - 4 - pcode_info.offset];
     *buf = d;
  }
  else
  {
     unsigned int * buf = (unsigned int *)&pcode_info.buf[pcode_info.size - 4 - pcode_info.offset];
     *buf = d;
  }
  pcode_info.offset += 4;
}

void PCode::dq(unsigned long long q)
{
  if (r_pc_size)
  {
#ifdef DEBUG
    fprintf(v_log,"(0%x)\r\n",q);
#endif
     for (list<vcode_encryption>::reverse_iterator iter = current_instruction->encode_pcode->rbegin();
              iter != current_instruction->encode_pcode->rend(); ++iter) //可能出现q_read_mem错误
     {
       call_encode_pcode_fn(iter->fn,&q,&iter->key);
       //if (iter2->key)
       //  iter2->fn(&q,&key);
       //else
       //  iter2->fn(&q,&key);
     }
     current_instruction = NULL;    
    r_pc_size = 0;
  }
  check_pcode_buf();
  if (pcode_info.sign == false)
  {
    unsigned long long * buf = (unsigned long long *)pcode_info.buf[pcode_info.size - 8 - pcode_info.offset];
    *buf = q;
  }
  else
  {
    unsigned long long * buf = (unsigned long long *)pcode_info.buf[pcode_info.offset];
    *buf = q;
  }
  pcode_info.offset += 8;
}

void PCode::init_handle_table(vm_handle table)
{
  memcpy(&pcode_info.handle_table,&table,sizeof(table));
}

void PCode::init_sign(bool b)
{
  pcode_info.sign = b;
}

void PCode::check_pcode_buf()
{
  if (pcode_info.offset + 8 > pcode_info.size)
  {
    if (pcode_info.sign == false)
    {
      unsigned char *newbuf = new unsigned char [pcode_info.size + 0xffff];
      memset(newbuf,0,pcode_info.size + 0xffff);
      memcpy(&newbuf[0xffff],pcode_info.buf,pcode_info.size);
      pcode_info.size += 0xffff;
      delete [] pcode_info.buf;
      pcode_info.buf = newbuf;
    }
    else
    {
      unsigned char *newbuf = new unsigned char [pcode_info.size + 0xffff];
      memset(newbuf,0,pcode_info.size + 0xffff);
      memcpy(newbuf,pcode_info.buf,pcode_info.size);
      pcode_info.size += 0xffff;
      delete [] pcode_info.buf;
      pcode_info.buf = newbuf;
    }
  }
}

//v_push(T_AX);
//v_pop(vr[30]);
//v_pop(T_AX)

void PCode::v_push_register(long _register,bool _disable)
{
  for (int i = 0; i < REG_NUMBER; i++)
  {
    long regid = 0xfffff & _register;
    long vregid = v_reg_context.vr[i].reg_id;
    if ( regid && ((vregid & 0xfffff) == regid) )
    {
      long reg_offset = v_reg_context.vr[i].reg_offset;
      long reg_status = v_reg_context.vr[i].status;
      //表示有寄存器类型
      if (_register & T_E32X )
      {
        //表示是32位寄存器
        if (_register & T_16X)
        {
          //表示是16位寄存器
          if (_register & T_8H)
          {
            //8位寄存器高位
            db(pcode_info.handle_table.b_push_reg.handle);
            db(reg_offset + 1);
          } else if (_register & T_8L)
          {
            //8位寄存器低位
            db(pcode_info.handle_table.b_push_reg.handle);
            db(reg_offset);
          } else 
          {
            //16位寄存器
            db(pcode_info.handle_table.w_push_reg.handle);
            db(reg_offset);
            
          }
        }
        else 
        {
          //32位寄存器
          db(pcode_info.handle_table.d_push_reg.handle);
          db(reg_offset);
#ifndef PROTECT_X64
          if (_disable)
          v_reg_context.vr[i].reg_id = T_INVALID;
          return;
#endif
        }
      }
      else
      {
#ifdef PROTECT_X64
        //64位寄存器
        if (_register & T_RN) 
        {
          //R8-R15
          db(pcode_info.handle_table.q_push_reg.handle);
          db(reg_offset);
        } else
        {
          //RAX-RDI
          db(pcode_info.handle_table.q_push_reg.handle);
          db(reg_offset);
        }
        if (_disable)
        v_reg_context.vr[i].reg_id = T_INVALID; //设置为无效
        return;
#endif        
      }
      v_reg_context.vr[i].status = _register & disable;
    }
//    else
//    {
      //没有类型的寄存器 没有 寄存器 或者 虚拟上下文环境找不到那个寄存器
//      break;
//    }
  }
}

pvm_reg PCode::find_invalid_register()
{
  int invalid_register_array[REG_NUMBER];
  int invalid_register_count = 0;
  for (int i = 0; i < REG_NUMBER; i++)
  {
    if (v_reg_context.vr[i].reg_id & T_INVALID)//== T_INVALID)
    {
      invalid_register_array[invalid_register_count++] = i;
    }
  }
  if (invalid_register_count)
  {
    int r = invalid_register_array[rand()%invalid_register_count];
    return &v_reg_context.vr[r];
  }
  else
  {
    return NULL;
  }
}

void PCode::v_pop_register(long _register)
{
  for (int i = 0; i < REG_NUMBER; i++)
  {
    long regid = 0xfffff & _register;
    long vregid = v_reg_context.vr[i].reg_id;
    if ( regid && ((vregid & 0xfffff) == regid) )
    {
      long reg_offset = v_reg_context.vr[i].reg_offset;
      //表示有寄存器类型
      if (_register & T_E32X)
      {
        //表示是32位寄存器
        if (_register & T_16X)
        {
          //表示是16位寄存器
          if (_register & T_8H)
          {
            //8位寄存器高位
            db(pcode_info.handle_table.b_pop_reg.handle);
            db(reg_offset + 1);
            v_reg_context.vr[i].status = _register & enable;
            return;
          } else if (_register & T_8L)
          {
            //8位寄存器低位
            db(pcode_info.handle_table.b_pop_reg.handle);
            db(reg_offset);
            v_reg_context.vr[i].status = _register & enable;
            return;
          } else 
          {
            //16位寄存器
            db(pcode_info.handle_table.w_pop_reg.handle);
                        db(reg_offset);
            v_reg_context.vr[i].status = _register & enable;
            return;
          }
        }
        else 
        {
          //32位寄存器
          db(pcode_info.handle_table.d_pop_reg.handle);
                    db(reg_offset);
          v_reg_context.vr[i].status = _register & enable;
          return;
        }
      }
      else
      {
#ifdef PROTECT_X64
        //64位寄存器
        if (_register & T_RN) 
        {
          //R8-R15
          db(pcode_info.handle_table.q_pop_reg.handle);
                    db(reg_offset);
          v_reg_context.vr[i].status = _register & enable;
          return;
        } else
        {
          //RAX-RDI
          db(pcode_info.handle_table.q_pop_reg.handle);
                    db(reg_offset);
          v_reg_context.vr[i].status = _register & enable;
          return;
        }
#endif
      }
    }
  }
  
  //没找到寄存器
  pvm_reg invalid_r = find_invalid_register();
  //#ifdef PROTECT_X64
  if (_register & T_8H)
  {
      db(pcode_info.handle_table.b_pop_reg.handle);
      db(invalid_r->reg_offset + 1);
      invalid_r->reg_id = _register;
      invalid_r->status = _register & disable;
      return;
  } else if (_register & T_8L)
  {
    db(pcode_info.handle_table.b_pop_reg.handle);
  } else if (_register & T_16X)
  {
    db(pcode_info.handle_table.w_pop_reg.handle);
  } else if (_register & T_E32X)
  {
    db(pcode_info.handle_table.d_pop_reg.handle);
  } else
  {
#ifdef PROTECT_X64
    db(pcode_info.handle_table.q_pop_reg.handle);
#else
    db(pcode_info.handle_table.d_pop_reg.handle);
#endif
  }
  db(invalid_r->reg_offset);
  invalid_r->reg_id = _register;
  invalid_r->status = _register & disable;
      //invalid_r->reg_id = _register;
  //db(pcode_info.handle_table.q_pop_reg);
  //db(invalid_r->reg_offset);
  //invalid_r->status = _register & disable;
      //#else
      //invalid_r->reg_id = _register;
      //db(pcode_info.handle_table.d_pop_reg);
      //db(invalid_r->reg_offset);
      //invalid_r->status = _register & disable;
      //#endif
}

