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


void PCode::out_log_file(char * file_name)
{
 #ifdef DEBUG
  //char save_log = 'y';
  //fprintf(stdout,"是否保存VM流程到文件:Y/N\r\n");
  //scanf("%c",&save_log);
  //if (save_log == 'Y' || save_log == 'y')
  //{
    v_log = fopen(file_name,"wb");
  //}
  //else
  //  v_log = stdout;  
#endif     
}

#ifdef DEBUG
void PCode::out_info(char * _sz)
{
    fprintf(v_log,"%s",_sz);
}
#endif

PCode::PCode()
  : _key_(m_random()),key(_key_),r_pc_size(0),is_begin_vmcode(false),current_instruction(NULL),vmcode_size(0)
#ifdef DEBUG
  ,v_log(stdout)
#endif
{
  pcode_info.size = DEFAULT_ALLOC_SIZE;
  pcode_info.buf = new unsigned char [pcode_info.size];
  pcode_info.offset = 0;
  for (int i = 0; i < REG_NUMBER; i++)
  {
    v_reg_context.vr[i].reg_id = T_INVALID;
    v_reg_context.vr[i].reg_offset = i*4;
  }
  /*
#ifdef DEBUG
  char save_log = 'y';
  fprintf(stdout,"是否保存VM流程到文件:Y/N\r\n");
  scanf("%c",&save_log);
  if (save_log == 'Y' || save_log == 'y')
  {
    v_log = fopen("vm_log.txt","wb");
  }
  else
    v_log = stdout;  
#endif
*/
 
}

PCode::PCode(vm_handle table,bool sign)
  : _key_(m_random()),key(_key_),r_pc_size(0),is_begin_vmcode(false)
#ifdef DEBUG
  ,v_log(stdout)
#endif
{
  pcode_info.size = DEFAULT_ALLOC_SIZE;
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
  /*
  char save_log = 'N';
  fprintf(stdout,"是否保存VM流程:Y/n\r\n");
  scanf("%c",&save_log);
  if (save_log == 'Y' || save_log == 'y')
  {
    v_log = fopen("vm_log.txt","wb");
  }
  else
    v_log = stdout;
    */
#endif
  
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

void PCode::set_key( const 
#ifdef PROTECT_X64
                    unsigned long _key
#else
                    unsigned int _key
#endif
                    )
{
  if ( _key_ != key )
  {
    cout << "程序已经开始运行,无法改变Key\r\n" << endl;
    throw ;
    return;
  }
  _key_ = _key;
  key = _key;
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
  //FileLogger logger(stderr);  
  //a.setLogger(&logger);  
  //fn(data,ikey);

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

void PCode::count_vmcode_begin()
{
  size_t vmcode_size = 0;
  is_begin_vmcode = true;
}

size_t PCode::count_vmcode_end()
{
  is_begin_vmcode = false;
  return vmcode_size;
}

void PCode::recovery_back()
{
  for (vector <vmcode_back>::iterator iter = vmcode_vec.begin(); iter != vmcode_vec.end(); ++iter)
  {
    switch (iter->size)
    {
    case -1: //重定位数据
      da(iter->a);
      break;
    case 1:
      db(iter->b);
      break;
    case 2:
      dw(iter->w);
      break;
    case 4:
      dd(iter->d);
      break;
    case 8:
      dq(iter->q);
      break;
    }
  }
  vmcode_vec.clear();
}


void PCode::db(unsigned char b)
{
  if (is_begin_vmcode)
  {
    vmcode_back bak;
    bak.size = 1;
    bak.b = b;
    vmcode_vec.push_back(bak);
    vmcode_size++;
    return;
  }
  if (!r_pc_size)
  {
      pVMHandleInfo instruction = (pVMHandleInfo)&pcode_info.handle_table;  //这里拦截VM指令
      int count = sizeof(vm_handle)/sizeof(VMHandleInfo);
      while (count != 0)
      {
        if (instruction->handle == b) //获取到handle了
        {/*{{{*/
#ifdef DEBUG
          /*          if (b == pcode_info.handle_table.b_write_stack.handle)
          {
            printf("handle:%d,d_pop_reg:%d\r\n",b,pcode_info.handle_table.d_pop_reg.handle);
            __asm__ ("int $3");
            }*/
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
          {
            fprintf(v_log,"%s%s%s",f,"b_push_reg",l);
          }
          else if (pcode_info.handle_table.w_push_reg.handle == b)
          {
            fprintf(v_log,"%s%s%s",f,"w_push_reg",l);
          }
          else if (pcode_info.handle_table.d_push_reg.handle == b)
          {
            fprintf(v_log,"%s%s%s",f,"d_push_reg",l);
          }
          else if (pcode_info.handle_table.b_pop_reg.handle == b)
          {
            fprintf(v_log,"%s%s%s",f,"b_pop_reg",l);
          }
          else if (pcode_info.handle_table.w_pop_reg.handle == b)
          {
            fprintf(v_log,"%s%s%s",f,"w_pop_reg",l);
          }
          else if (pcode_info.handle_table.d_pop_reg.handle == b)
          {
            fprintf(v_log,"%s%s%s",f,"d_pop_reg",l);
          }
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
            fprintf(v_log,"%s%s%s",f,"push_vsp",l);
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
          else if (pcode_info.handle_table.set_key.handle == b )
            fprintf( v_log,"%s%s%s",f,"set_key",l );
          else if (pcode_info.handle_table.run_stack.handle == b)
            fprintf( v_log,"%s%s%s",f,"run_stack",l);
          else if (pcode_info.handle_table.int3.handle == b)
            fprintf( v_log,"%s%s%s",f,"int3",l);
          else if (pcode_info.handle_table.fstsw.handle == b)
            fprintf( v_log,"%s%s%s",f,"fstsw",l);
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
           //         fprintf(v_log,"dispatch new key:%x\r\n",key);
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
         //  printf("key:%x\r\n",key);
#endif
         break;
        }/*}}}*/
        instruction++; //这个不能放在前面否则会导致读取到q_read_mem
        count--;
      }
  }
  else
  {
#ifdef DEBUG
    if (strcmp(reg_name,"") == 0)
    {
        fprintf(v_log,"(0%x)\r\n",b);
    }
    else
    {
        if (b != 0)
        {
            if (b % sizeof(long) == 0)
            {
                fprintf(v_log,"(%s) index:(%x)\r\n",reg_name,b);
            }
            else
            {
                fprintf(v_log,"(%s) index:(%x) offset:(%d)\r\n",reg_name,b / sizeof(long),b % sizeof(long));

            }
        }
        else
      fprintf(v_log,"(%s) index:(%x)\r\n",reg_name,b);
      if (b >= REG_NUMBER * 4)
      {
          printf("虚拟寄存器引索超过边界\n");
          debugbreakpoint();
      }
      //printf("寄存器数量：%d \n",REG_NUMBER);
      strcpy(reg_name,"");
    }
     
#endif    
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
  if (is_begin_vmcode)
  {
    vmcode_back bak;
    bak.size = 2;
    bak.w = w;
    vmcode_vec.push_back(bak);    
    vmcode_size+=2;
    return;
  }  
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
  if (is_begin_vmcode)
  {
    vmcode_back bak;
    bak.size = 4;
    bak.d = d;
    vmcode_vec.push_back(bak);    
    vmcode_size += 4;
    return;
  }  
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
  if (is_begin_vmcode)
  {
    vmcode_back bak;
    bak.size = 8;
    bak.q = q;
    vmcode_vec.push_back(bak);    
    vmcode_size += 8;
    return;
  }  
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

//data address 说明是一个地址
void PCode::da(long a)
{
  if (is_begin_vmcode)
  {
    vmcode_back bak;
    bak.size = -1; //-1代表重定位数据
    bak.a = a;
    vmcode_vec.push_back(bak);    
    vmcode_size += sizeof(long);
    return;
  }  
  if (r_pc_size)
  {
#ifdef DEBUG
    fprintf(v_log,"(0%x)\r\n",a);
#endif
     for (list<vcode_encryption>::reverse_iterator iter = current_instruction->encode_pcode->rbegin();
              iter != current_instruction->encode_pcode->rend(); ++iter) //可能出现q_read_mem错误
     {
       call_encode_pcode_fn(iter->fn,&a,&iter->key);
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
    unsigned long long * buf = (unsigned long long *)pcode_info.buf[pcode_info.size - sizeof(long) - pcode_info.offset];
    *buf = a;
  }
  else
  {
    unsigned long long * buf = (unsigned long long *)pcode_info.buf[pcode_info.offset];
    *buf = a;
  }
  pcode_info.offset += sizeof(long);  
}

void PCode::init_handle_table(vm_handle table)
{
  memcpy(&pcode_info.handle_table,&table,sizeof(table));
}

void PCode::init_sign(bool b)
{
  pcode_info.sign = b;
}
                                 /*
void PCode::attch_virtual_machine(VirtualMachine *vm)
{
  init_handle_table(vm->handle_pcode);
  init_sign(vm->handle.fuc_select.addorsub);
}                                  */

void PCode::check_pcode_buf()
{
  if (pcode_info.offset + 8 > pcode_info.size)
  {
    if (pcode_info.sign == false)
    {
      unsigned char *newbuf = new unsigned char [pcode_info.size + DEFAULT_ALLOC_SIZE];
      memset(newbuf,0,pcode_info.size + DEFAULT_ALLOC_SIZE);
      memcpy(&newbuf[DEFAULT_ALLOC_SIZE],pcode_info.buf,pcode_info.size);
      pcode_info.size += DEFAULT_ALLOC_SIZE;
      delete [] pcode_info.buf;
      pcode_info.buf = newbuf;
    }
    else
    {
      unsigned char *newbuf = new unsigned char [pcode_info.size + DEFAULT_ALLOC_SIZE];
      memset(newbuf,0,pcode_info.size + DEFAULT_ALLOC_SIZE);
      memcpy(newbuf,pcode_info.buf,pcode_info.size);
      pcode_info.size += DEFAULT_ALLOC_SIZE;
      delete [] pcode_info.buf;
      pcode_info.buf = newbuf;
    }
  }
}

//v_push(T_AX);
//v_pop(vr[30]);
//v_pop(T_AX)
#ifdef DEBUG  
void PCode::set_register_name(long _register)
{

      switch (_register & T_ALL_REGISTER)
      {
       case T_RAX:
        strcpy(reg_name,"rax");
        break;
       case T_RBX:
        strcpy(reg_name,"rbx");
        break;
       case T_RCX:
        strcpy(reg_name,"rcx");
        break;
       case T_RDX:
        strcpy(reg_name,"rdx");
        break;
       case T_RSP:
        strcpy(reg_name,"rsp");
        break;
       case T_RBP:
        strcpy(reg_name,"rbp");
        break;
       case T_RSI:
        strcpy(reg_name,"rsi");
        break;
       case T_RDI:
        strcpy(reg_name,"rdi");
        break;
       case T_KEY64:
        strcpy(reg_name,"key");
        break;
       case T_EFLAG_:
        strcpy(reg_name,"flag");
        break;
       case T_TMP_R64_1:
        strcpy(reg_name,"tr1");
        break;
       case T_TMP_R64_2:
         strcpy(reg_name,"tr2"); 
        break;
       case T_TMP_R64_3:
         strcpy(reg_name,"tr3"); 
        break;
       case T_TMP_R64_4:
         strcpy(reg_name,"tr4"); 
        break;
       case T_TMP_R64_5:
         strcpy(reg_name,"tr5"); 
        break;
       case T_TMP_R64_6:
         strcpy(reg_name,"tr6"); 
        break;
       case T_TMP_R64_7:
         strcpy(reg_name,"tr7"); 
        break;
       case T_TMP_R64_8:
         strcpy(reg_name,"tr8"); 
        break; 
       case T_JMPINSADDR64:
         strcpy(reg_name,"jcc");
        break;
       case T_NEXTINSADDR64:
        strcpy(reg_name,"pc");
        break;
       default:
        strcpy(reg_name,"invalid" );
        break;
      }
                             
      
      
      if (_register & T_E32X)
      {   
       if (_register & T_16X)   
       {
         if (_register & T_8H)
         {
          strcat(reg_name,"|8h");
         } 
         else if (_register & T_8L)
         {
          strcat(reg_name,"|8l");
         } else      
          strcat(reg_name,"|16l"); 
       }
       else
       {
        strcat(reg_name,"|32l");
       }
      } 
}
#endif  

void PCode::v_push_register(long _register,bool _disable)
{
    
#ifdef DEBUG
  set_register_name(_register);
#endif
  if (_register & T_INVALID)
  {
  //没找到寄存器
    pvm_reg invalid_r = find_invalid_register();
  //#ifdef PROTECT_X64
    if (_register & T_8H)
    {
        db(pcode_info.handle_table.b_push_reg.handle);
        db(invalid_r->reg_offset + 1);
        return;
    } else if (_register & T_8L)
    {
      db(pcode_info.handle_table.b_push_reg.handle);
    } else if (_register & T_16X)
    {
      db(pcode_info.handle_table.w_push_reg.handle);
    } else if (_register & T_E32X)
    {
      db(pcode_info.handle_table.d_push_reg.handle);
    } else
    {
#ifdef PROTECT_X64
      db(pcode_info.handle_table.q_push_reg.handle);
#else
      db(pcode_info.handle_table.d_push_reg.handle);
#endif
    }
    db(invalid_r->reg_offset);
    return;
  }
  
  int size = get_code_size();
  for (int i = 0; i < REG_NUMBER; i++)
  {
    long regid = T_ALL_REGISTER & _register;
    long vregid = v_reg_context.vr[i].reg_id;
    if ( regid && ((vregid & T_ALL_REGISTER) == regid) )
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
            return ;
          } 
          else if (_register & T_8L)
          {
            //8位寄存器低位
            db(pcode_info.handle_table.b_push_reg.handle);
            db(reg_offset);
            return;
          } 
          else 
          {
            //16位寄存器
            db(pcode_info.handle_table.w_push_reg.handle);
            db(reg_offset);
            return;
            
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
#ifndef PROTECT_X64
#ifdef DEBUG
        printf("保护32位程序却要push 64位寄存器\n");
        debugbreakpoint();
#endif
#endif     
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
  if (size == get_code_size(  ))
  {
#ifdef DEBUG
      set_register_name(_register);

    cout << "Register not found"  << reg_name << endl;
    //throw;
    //__asm__("int3");
#endif
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
#ifdef DEBUG
 set_register_name(_register);
#endif  

  for (int i = 0; i < REG_NUMBER; i++)
  {
    long regid = T_ALL_REGISTER & _register;
    long vregid = v_reg_context.vr[i].reg_id;
    if ( regid && ((vregid & T_ALL_REGISTER) == regid) )
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
#ifndef PROTECT_X64
#ifdef DEBUG
        printf("保护32位程序却要pop 64位寄存器\n");
        debugbreakpoint();
#endif 
#endif
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

