/*
 *
 *   Copyrigth (C) Sun Jun  9 22:03:40 2013 XiaoWei
 *
 *                       handsomexiaowei@gmail.com
 *
 *
 */

#include "PCode.hpp"
#include <iostream>
#include <string.h>
#include <WProtectConfig.h>

PCode::PCode()
{
  pcode_info.size = 0xFFFF;
  pcode_info.buf = new unsigned char [pcode_info.size];
  pcode_info.offset = 0;
  for (int i = 0; i < REG_NUMBER; i++)
  {
    v_reg_context.vr[i].reg_id = T_INVALID;
    v_reg_context.vr[i].reg_offset = i*4;
  }
}

PCode::PCode(vm_handle table,bool sign)
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
}

void PCode::db(unsigned char b)
{
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

