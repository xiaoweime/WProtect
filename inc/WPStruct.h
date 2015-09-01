#include <stdio.h>
#include <stdlib.h>
#include <udis86.h>

#ifndef _WP_STRUCT_
#define _WP_STRUCT_
typedef struct _CODE_INFORMATION_
{
	unsigned char * buf; //代码缓冲区
	unsigned long  size; //大小
	unsigned long base; // 基址
}CodeInformation,*pCodeInformation;

typedef struct _INSTRUCTION_LIST_
{
	int id;
	ud_t udobj;
	_INSTRUCTION_LIST_ *next;
}InstructionList,*pInstructionList;

typedef struct _INSTRUCTION_BLOCK_LIST_
{
	int id;
	pInstructionList list;	
	unsigned long oldaddr;
	unsigned long newaddr;
	_INSTRUCTION_BLOCK_LIST_ *next;
}InstructionBlockList,*pInstructionBlockList;
#endif