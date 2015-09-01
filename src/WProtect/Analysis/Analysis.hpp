/*
 *
 *   Copyright (C) Wed May 29 04:00:49 2013 XiaoWei
 *
 *                       handsomexiaowei@gmail.com
 *
 *
 */

#ifndef _ANALYSIS_H_
#define _ANALYSIS_H_

#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <udis86.h>
//#include "PESection.h"

typedef struct ANALYSIS_OPTIONS
{
	long addr;
    void *buf;
    long size;
}CodeBufferInfo,*pCodeBufferInfo;

/*
#define CF 1
#define PF 4
#define AF 16
#define ZF 64
#define SF 128
#define TF 256
#define IF 512
#define DF 1024
#define OF 2048
*/

#define PC_NONE -1
#define PC_MEM -4
#define PC_RET -2
#define PC_EXIT -3
#define PC_MIN -10000

#define PC_LABEL_MAX  10000
#define TYPE_LABEL 1
#define TYPE_ADDR  2   
#define TYPE_MEM   3
#define TYPE_RET   4
#define TYPE_CALL  5

enum OPCODE_ATTRIBUTE{
    OPCODE_ATTRIBUTE_CALL,
    OPCODE_ATTRIBUTE_EXTERNAL_CALL,
    OPCODE_ATTRIBUTE_JMP,
    OPCODE_ATTRIBUTE_EXTERNAL_JMP,
    OPCODE_ATTRIBUTE_RET,
    OPCODE_ATTRIBUTE_NORMAL,
    OPCODE_ATTRIBUTE_EXTERNAL_JCC,
    OPCODE_ATTRIBUTE_JCC,
    OPCODE_ATTRIBUTE_EXIT
};

typedef struct ASSEMBLER_PIECE_INFO   //反汇编信息 块 
{
  ud_t u;  //包含各种信息
}AssemblerInfo,*pAssemblerInfo;

typedef struct ASSEMBLER_TREE
{
  //long address; //块地址
  bool set_key;
  long key;
  long jcc_addr; //跳转到的地址
  long next_instruction; //下一条指令跳转地址 mov eax,1  jmp hello mov eax,2 hello: ret    mov eax,2就是这个
  long reloc_address;   //冲定位到
  long id; //代码块id 从0开始
  long base; //代码块开始地址  //块地址
  long size; //代码块大小

  // std::list<ud_t>asmpiect;
  long eflag;
  //pAssemblerInfo asmpiece;  //指向汇编块头
	ASSEMBLER_TREE *LeftChild; //左孩纸
	ASSEMBLER_TREE *RightChild; //右孩纸
	std::vector <ud_t> asmpiece;
}AssemblerTree,*pAssemblerTree;
 
typedef struct _AddressArray
{
  private:
   long * a_array;
   size_t a_size; 
  public:
   _AddressArray(int _size) {
     a_array = new long[_size];
     a_size = _size;
   }
   /*
   _AddressArray(_AddressArray && rlhs)
   {
     a_array = rlhs.a_array;
     a_length = rlhs.a_length;
     rlhs.a_array = NULL;
   }*/
   /*
   _AddressArray(_AddressArray & rlhs)
   {
     a_array = rlhs.a_array;
     a_size = rlhs.a_size;
     rlhs.a_array = NULL; 
   } */
   
   ~_AddressArray(){
     if(a_array != NULL)
       delete [] a_array;
   }
   long &operator[](size_t _index)
   {
     if (_index >= a_size || a_array == NULL) {
       printf("Address_Array数组访问越界");
     }
     return a_array[_index];
   }     /*
   long operator=(_AddressArray & rlhs)
   {
     a_array = rlhs.a_array;
     a_size = rlhs.a_size;
     rlhs.a_array = NULL;   
   }        */
   size_t get_size()
   {
     return a_size;
   }
   void set_size(size_t _size)
   {
     a_size = _size;
   }
}AddressArray;
      

typedef struct _CodePiece
{
  _CodePiece():is_jcc(false){}
  ~_CodePiece(){}
  void set_label(int id)
  {
    label = id;
  }
  void set_jmplabel(int jmpid)
  {
    jmp_to_label = jmpid;
  }
  void add_assemble(ud_t & ud)
  {
    piece.push_back(ud);
  }
  int get_jmplabel()
  {
    return jmp_to_label;
  }
  int get_label()
  {
    return label;
  }
  void set_is_jcc(bool _is_jcc)
  {
    is_jcc = _is_jcc;
  }
  bool get_is_jcc()
  {
    return is_jcc;
  }
  std::list<ud_t> & get_piece()
  {
    return piece;
  }
  /*int get_jmplabel_type()
  {
    if (jmp_to_label == PC_RET)
    {
      return TYPE_RET;
    }
    if (jmp_to_label >= 0 && jmp_to_label < PC_LABEL_MAX)
    {
       return TYPE_LABEL;
    }
    if (jmp_to_label < 0 && jmp_to_label > PC_MIN)
    {
      return TYPE_MEM;
    }
    return TYPE_ADDR;
  }*/
  void set_opcode_attribute(OPCODE_ATTRIBUTE attribute)
  {
      opcode_attribute = attribute;
  }
  OPCODE_ATTRIBUTE get_opcode_attribute()
  {
      return opcode_attribute;
  }

  private:
  int label;
  int jmp_to_label;
  OPCODE_ATTRIBUTE opcode_attribute;
  bool is_jcc;
  std::list<ud_t> piece;
}CodePiece;
               
class Analysis
{
public:
  Analysis();
  virtual ~Analysis();
public:
  size_t reloc_asm_address(long old_address,long new_address); //返回一个成功重定位个数 0为没找到
  size_t reloc_asm_address();
  AddressArray analysis_code_piece_address(pCodeBufferInfo pinfo); 
  void disasm(pCodeBufferInfo pinfo,std::vector<CodePiece> & code);
  void printf_piece(std::vector<CodePiece>& var_piece);
  pAssemblerTree add_tree(pAssemblerTree parent, pAssemblerTree child,bool l_r);
  pAssemblerTree disasm(pCodeBufferInfo pinfo);
  void set_label_address(pCodeBufferInfo pinfo,AddressArray & _addra,std::map<long,int> &_map);
  void link_tree();

  pAssemblerTree find_tree(long addr); //传递一个地址
  pAssemblerTree get_tree(long id);
  void analysis_address_table(pCodeBufferInfo pinfo,std::vector<long> & addr_entry_table,long addr_min,long addr_max);
  void clean_tree();
  pAssemblerTree root;
  long block_count;
  void set_eflag(  );
  long base;
  long size;
  const bool L;// = false;
  const bool R;// = true;
  bool check_address( long addr );
};
#endif /* _ANALYSIS_H_ */
