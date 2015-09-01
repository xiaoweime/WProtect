/*
 *
 *   Copyright (C) Tue Jun 25 17:48:43 2013 XiaoWei
 *
 *                       handsomexiaowei@gmail.com
 *
 *
 */


#ifndef _VMADDRESSTABLE_H_
#define _VMADDRESSTABLE_H_

//#include "PCode.hpp"
#include <algorithms>
#include "SeniorVMHandle.hpp"
#include "CombosVMCode.hpp"
typedef struct _v_table_
{
  VCombosVMCode *v;
  //SeniorVMHandle *v;
  _v_table_(  )
    :vesp_diff( 0 ),key_status( false ),key( 0 ),v( NULL ){
    
  }
  ~_v_table_(  ) {
    
  }
  long base;
  long reloc_address;
  long id;
  long vesp_diff;

  long key;
  bool key_status;
}VTable,*pVTable;

class VMAddressTable : public AddressTable<VTable>
{
public:
  VMAddressTable(long _base,size_t _size,bool _sign)
    :AddressTable( _base,_size,_sign ),buffer(NULL),buffer_size(0)
#ifdef DEBUG
     ,vmcode_piece_count(0)
#endif
  {
    
  }
  virtual ~VMAddressTable(){
    if (buffer)
    {
      delete [] buffer;
    }
  }

  
  void update(VCombosVMCode * p ) {
    for (list<space>::iterator iter = addr_vec.begin(  ); iter != addr_vec.end(  ); ++iter)
    {
      if (iter->data.v == p)
      {
        if ( get_sign()  )
          iter->end = iter->begin + p->get_code_size(  ) ;
        else
          iter->begin = iter->end - p->get_code_size(  );
      }
    }
  }
  
  void init_buffer()
  {
      buffer = new char[size];
      buffer_size = size;   
  }

  long copy(unsigned char * buf,size_t size)
  {
    long address = assign_address(size);
    memcpy(&(buffer[address - base]),buf,size);
    return address;
  }

  void * copy(long address,unsigned char * buf,size_t size)
  {
    if (buffer == NULL)
      init_buffer();    
    void * buff = &(buffer[address-base]);
    memcpy(buff,buf,size);
    return buff;
  }
  
  void * copy(unsigned char * buf)
  {
    //sort( addr_vec.begin(  ) , addr_vec.end(  ));
    addr_vec_sort();
    for (list<space>::iterator iter = addr_vec.begin( ) ; iter !=
           addr_vec.end(  ); ++iter)
    {
      space d = *iter;
      if ( get_sign() )
      {
        memcpy(&buf[d.begin - base],
               d.data.v->get_code_buf(),
               d.data.v->get_code_size(  ));
      }
      else
      {
        /* memcpy(&buf[d.end - base],
               d.data.v->get_code_buf(),
               d.data.v->get_code_size());*/
        memcpy( &buf[ d.begin - base ],
                d.data.v->get_code_buf(  ),
                d.data.v->get_code_size(  ));
      }
      
    }
    return buf;
  }

#ifdef DEBUG
  size_t vmcode_piece_count;
#endif
  void * copy()
  {
    if (buffer == NULL)
      init_buffer();
    //sort( addr_vec.begin(  ) , addr_vec.end(  ));
    addr_vec_sort();

#ifdef DEBUG
    char buildvmcode_name[256];
    sprintf(buildvmcode_name,"virtual_machine_assembly/buildvmcode%d.log",vmcode_piece_count++);
FILE *file = fopen(buildvmcode_name,"wb");
#endif
 
    for (list<space>::iterator iter = addr_vec.begin( ) ; iter !=
           addr_vec.end(  ); ++iter)
    {/*{{{*/
      space & d = *iter;
      if (d.data.v)
        if (d.end - d.begin != d.data.v->get_code_size())
        {
          printf("字节不对,分配:%d,使用:%d\r\n",d.end-d.begin,d.data.v->get_code_size());
          throw;
        }          
      if ( get_sign() )
      {    
#ifdef DEBUG
        if (d.data.v)
        {
          fprintf(file,"代码地址:%x,虚拟代码地址:%x,标志位%d\r\n",d.data.base,d.begin,get_sign());
          for (int i = 0; i < d.data.v->get_code_size(); ++i)
          {
              fprintf(file," ");
              //            fwrite((char*)d.data.v->get_code_buf() + i,1,1,file);
              //
            unsigned char code = *(unsigned char*)((char*)d.data.v->get_code_buf() + i);
            code = code & 0xff;
              fprintf(file,"%02c",code);
              if ((i + 1) % 16 == 0)
              {
              fprintf(file,"\r\n");
              }
          }
          fprintf(file,"\r\n");
        }
        //printf("%s",file);
#endif               
        if (d.data.v)
        {
            memcpy(&buffer[d.begin - base],
               d.data.v->get_code_buf(),
               d.data.v->get_code_size(  ));
            d.data.v = NULL;
        }
      }
      else
      {
        /* memcpy(&buf[d.end - base],
               d.data.v->get_code_buf(),
               d.data.v->get_code_size());*/
#ifdef DEBUG
        if (d.data.v)
        {
          fprintf(file,"代码地址:%x,虚拟代码地址:%x,标志位置%d\r\n",d.data.base,d.end,get_sign());
          for (int i = 0; i < d.data.v->get_code_size(); ++i)
          {
            fprintf(file," ");
            //fwrite((char*)d.data.v->get_code_buf() + i,1,1,file);
           unsigned char code = *(unsigned char*)((char*)d.data.v->get_code_buf() + i);
            code = code & 0xff;
            fprintf(file,"%x",code);
            if ((i + 1) % 16 == 0)
            {
              fprintf(file,"\r\n");
            }
          }
          fprintf(file,"\r\n");
        }
        
#endif
        if (d.data.v)        
        {
          memcpy( &buffer[ d.begin - base ],
                d.data.v->get_code_buf(  ),
                d.data.v->get_code_size(  ));
          d.data.v = NULL;   
        }
      }
       
      
    }/*}}}*/
#ifdef DEBUG
    fclose(file);
#endif
    return buffer;    
  }
  
  VTable * get_data( long _base )
  {
    for (list<space>::iterator iter = addr_vec.begin( ) ; iter !=
           addr_vec.end(  ); ++iter)
    {
      // space d = *iter;
      if (iter->begin == _base)
        return &iter->data;
    }
    return NULL;
  }
  size_t get_size( ) const {
    return size;
  }
  long assign_address(size_t _size,const VTable & _data)
  {
    
    long addr = AddressTable::assign_address(_size, _data);
    //addr_vec.end()->data.base = addr;
    addr_vec.back().data.base = addr;
    //printf("分配开始\n");
    if (buffer)
    {
      if (buffer_size < size)
      {
        char * newbuf = new char[size];
        memcpy(newbuf,buffer,buffer_size);
        delete [] buffer;
        buffer = newbuf;
        buffer_size = size;
      }
    }    
    //printf("分配结束\n");
    return addr;
  }
  long assign_address(size_t _size)
  {
    long addr = AddressTable::assign_address(_size);
    //addr_vec.end()->data.v = NULL;
    //VTable table;
    
    //memset(&table,0,sizeof(table));
    //long addr = AddressTable::assign_address(_size,table);
    if (buffer)
    {
      if (buffer_size < size)
      {
        char * newbuf = new char[size];
        memcpy(newbuf,buffer,buffer_size);
        delete [] buffer;
        buffer = newbuf;
        buffer_size = size;
      }
    }
    return addr;
  }
  
  char *buffer;
  size_t buffer_size;
};

#endif /* _VMADDRESSTABLE_H_ */
