#ifndef CODEINFOSTRCUT_H
#define CODEINFOSTRCUT_H
#include <CodeInfoStruct.h>
#endif

#include <WPStruct.h>

#include <udis86.h>

/*
typedef struct _CODE_INFORMATION_
{
	unsigned char * buf; //代码缓冲区
	unsigned long  size; //大小
	unsigned long base; // 基址
}CodeInformation,*pCodeInformation;
*/


	
class OutOfOrder
{
 public:
	 OutOfOrder();
	 ~OutOfOrder();
public:
	 pCodeInformation code_out_of_order(pCodeInformation info,unsigned long imagebase); //第一个参数是输入的代码信息  第二个参数表示要把代码重定位到哪里
	 pInstructionBlockList m_InstructionBlockHead;
	 pInstructionBlockList add_instruction_block_list();   //创建空的程序块
	 pInstructionBlockList add_instruction_block_list(pInstructionList instruction);  //创建程序块并且用instruction指令初始化List
	 pInstructionList add_instruction_list(pInstructionBlockList block,ud_t *pobj);  //在block块添加指令

	 pInstructionList add_instruction_list(pInstructionList instruction,ud_t *pobj);  //在block块添加指令

	 void clean_instruction_list(pInstructionList head);
	 void clean_instruction_block_list();

	 pCodeInformation build_block(pInstructionBlockList block,pCodeInformation info); //第一个参数块  第二个参数  一个空的含有base的pCodeInformation
	 pCodeInformation code_recombine(pCodeInformation info);
	 unsigned int m_block_max;
	 template <class T>  T * recombine(T * t,int nSize);
	 pInstructionBlockList get_instruction_block_list(int id);
	 unsigned long **m_addr_table;//[][3] [][0]为oldaddr [][1]为newaddr [][2]size [][3]id
	// unsigned long m_addr_table_size;
	 pCodeInformation build_reloc_jcc(pInstructionBlockList block,pCodeInformation info);
	 unsigned long get_old_addr_to_new_addr(unsigned long oldaddr);  //传递老地址 获取新地址

	 unsigned char *m_codebuf;
};
