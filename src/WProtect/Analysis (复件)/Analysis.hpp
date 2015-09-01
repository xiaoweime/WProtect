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
#include <udis86.h>

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

class Analysis
{
public:
  Analysis();
  virtual ~Analysis();
public:
  size_t reloc_asm_address(long old_address,long new_address); //返回一个成功重定位个数 0为没找到
  size_t reloc_asm_address();
  pAssemblerTree disasm(pCodeBufferInfo pinfo);
  pAssemblerTree add_tree(pAssemblerTree parent, pAssemblerTree child,bool l_r);
  void link_tree();
  pAssemblerTree find_tree(long addr); //传递一个地址
  pAssemblerTree get_tree(long id);
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
