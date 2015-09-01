#ifndef CODEINFOSTRCUT_H
#define CODEINFOSTRCUT_H
#include <CodeInfoStruct.h>
#endif

#ifndef WPROTECTCONFIG_H
#define WPROTECTCONFIG_H
#include <WProtectConfig.h>
#endif

#include "OutOfOrder.h"
#include <udis86.h>
#include <string.h>

#include <disasm.h>
//#include <Assembl.h>

#include <time.h>
#include <stdlib.h>
#include <stdio.h>

OutOfOrder::OutOfOrder()
{
	m_InstructionBlockHead = NULL;
	m_block_max = 0;
	m_codebuf = NULL;
}

OutOfOrder::~OutOfOrder()
{
	clean_instruction_block_list();
	if (m_codebuf)
		delete [] m_codebuf;
}

pInstructionList OutOfOrder::add_instruction_list(pInstructionBlockList block,ud_t *pobj)
{
	if (block->list == NULL)
	{
		block->list = new InstructionList;
		block->list->id = 1;
		block->list->next = NULL;
		memcpy(&block->list->udobj,pobj,sizeof(block->list->udobj));
		return block->list;
	}
	pInstructionList nowlist = block->list;
	pInstructionList lastlist = NULL;
	int id = 1;
	while (nowlist)
	{
		id++;
		lastlist = nowlist;
		nowlist = nowlist->next;
	}
	lastlist->next = new InstructionList;
	lastlist->next->next = NULL;
	lastlist->next->id = id;
	memcpy(&lastlist->next->udobj,pobj,sizeof(lastlist->next->udobj));
	return lastlist->next;
}

pInstructionList OutOfOrder::add_instruction_list(pInstructionList instruction,ud_t *pobj)
{
	if (instruction == NULL)
	{
		pInstructionList newlist = new InstructionList;
		newlist->id = 1;
		newlist->next = NULL;
		memcpy (&newlist->udobj,pobj,sizeof(newlist->udobj));
		return newlist;
	}
	pInstructionList lastlist = NULL;
	pInstructionList nowlist = instruction;
	int id = 1;
	while (nowlist)
	{
		id++;
		lastlist = nowlist;
		nowlist = nowlist->next;
	}
	lastlist->next = new InstructionList;
	lastlist->next->id = id;
	lastlist->next->next = NULL;
	memcpy (&lastlist->next->udobj,pobj,sizeof(lastlist->next->udobj));
	return lastlist->next;
}

pInstructionBlockList OutOfOrder::add_instruction_block_list()
{
	if (m_InstructionBlockHead == NULL)
	{
		m_InstructionBlockHead = new InstructionBlockList;
		m_block_max = m_InstructionBlockHead->id = 1;
		m_InstructionBlockHead->next = NULL;
		m_InstructionBlockHead->list = NULL;
		return m_InstructionBlockHead;
	}
	pInstructionBlockList nowlist = m_InstructionBlockHead;
	pInstructionBlockList lastlist = NULL;
	int id = 1;
	while (nowlist)
	{
		id++;
		lastlist = nowlist;
		nowlist = nowlist->next;
	}
	lastlist->next = new InstructionBlockList;
	m_block_max = lastlist->next->id = id;
	lastlist->next->next = NULL;
	lastlist->next->list = NULL;
	return lastlist;
}

pInstructionBlockList OutOfOrder::add_instruction_block_list(pInstructionList instruction)
{
	if (m_InstructionBlockHead == NULL)
	{
		m_InstructionBlockHead = new InstructionBlockList;
		m_block_max = m_InstructionBlockHead->id = 1;
		m_InstructionBlockHead->next = NULL;
		m_InstructionBlockHead->list = instruction;
		m_InstructionBlockHead->oldaddr = instruction->udobj.insn_offset;
		return m_InstructionBlockHead;
	}
	pInstructionBlockList nowlist = m_InstructionBlockHead;
	pInstructionBlockList lastlist = NULL;
	int id = 1;
	while (nowlist)
	{
		id++;
		lastlist = nowlist;
		nowlist = nowlist->next;
	}
	lastlist->next = new InstructionBlockList;
	m_block_max = lastlist->next->id = id;
#ifdef DEBUG
	fprintf(stdout,"block id:%d\r\n",id);
#endif
	lastlist->next->next = NULL;
	lastlist->next->list = instruction;
	lastlist->next->oldaddr = instruction->udobj.insn_offset;
	return lastlist;
}

void OutOfOrder::clean_instruction_list(pInstructionList head)
{
	pInstructionList nowlist = head;
	while (nowlist)
	{
		pInstructionList oldlist = NULL;
		oldlist = nowlist->next;
		delete nowlist;
		nowlist = oldlist;
	}
}

void OutOfOrder::clean_instruction_block_list()
{
	pInstructionBlockList nowlist = m_InstructionBlockHead;
	pInstructionBlockList nextlist = NULL;
	while (nowlist)
	{
		nextlist = nowlist->next;
		clean_instruction_list(nowlist->list);
		delete nowlist;
		nowlist = nextlist;
	}
	m_InstructionBlockHead = NULL;
}

pCodeInformation OutOfOrder::build_block(pInstructionBlockList block,pCodeInformation info)
{
	block->newaddr = info->base;
	if (block->list == NULL || block == NULL)
	{
		fprintf(stdout,"error: build_block");
	}
	else
		block->oldaddr = block->list->udobj.insn_offset;
	
	info->size = 0;
	pInstructionList head = block->list;
	t_disasm da;
	pInstructionList nowlist = head;
	int nCodelen = 0;
	//int nDiff = 0;
	//int ip = head->udobj.insn_offset;
	t_asmmodel model;
	char  error[256];
	while (nowlist)
	{
		int size = Disasm((char*)nowlist->udobj.inp_sess,20, nowlist->udobj.insn_offset, &da, DISASM_CODE);
		//info->size += Assemble(da.result,info->base+nCodelen,&model,0,0,error);
		info->size += Assemble(da.result,info->base+nCodelen,&model,0,nowlist->udobj.inp_ctr,error);
		if (strcmp(error,"")!=0)
		{
			char *n;
			if (n = strstr(da.result,"SHORT"))
			{
				memset(n,' ',5);
				info->size = nCodelen;
				//Assembl a;
				//a.Assemble()
				//info->size += Assemble(da.result,info->base+nCodelen,&model,0,nowlist->udobj.inp_ctr,error);
				if (strcmp(error,"")!=0)
				{
					fprintf(stderr,"error 无法识别的指令");
					return NULL;
				}
			}
			else if (strcmp(error,"Unknown identifier")==0)
			{
				info->size = nCodelen;
				info->size += Assemble(nowlist->udobj.insn_buffer,info->base+nCodelen,&model,0,nowlist->udobj.inp_ctr,error);
				if (strcmp(error,"")!=0)
				{
					fprintf(stderr,"error 无法识别的指令");
					return NULL;
				}
			} else
			fprintf(stderr,"error:%s buf:%s",da.result,nowlist->udobj.insn_buffer);
		}

		memcpy(
			&info->buf[nCodelen],
			model.code,
			info->size-nCodelen
			);
#ifdef DEBUG
		printf("size: %d          ",nowlist->udobj.inp_ctr);
#endif
		nCodelen = info->size;
#ifdef DEBUG
		fprintf(stdout,"addr:%08x  \r\n",nowlist->udobj.insn_offset);
#endif
		nowlist = nowlist->next;
	}
	
	return info;
}

unsigned long OutOfOrder::get_old_addr_to_new_addr(unsigned long oldaddr)
{
	for (int i=0;i<m_block_max;i++)
	{
		if (m_addr_table[i][0] == oldaddr)
		{
			return m_addr_table[i][1];
		}
	}
	return oldaddr;
}
int dddbg=0;
pCodeInformation OutOfOrder::build_reloc_jcc(pInstructionBlockList block,pCodeInformation info)
{
	bool is_jump = false;
	//block->newaddr = info->base;                 ///////////////////////////////////////////////////严重注意 可能这里就错了
	if (block->list == NULL || block == NULL)
	{
		fprintf(stdout,"error: build_block");
	}
//	else
//		block->oldaddr = block->list->udobj.insn_offset;

	info->size = 0;
	pInstructionList head = block->list;
	t_disasm da;
	pInstructionList nowlist = head;
	int nCodelen = 0;
	//int nDiff = 0;
	//int ip = head->udobj.insn_offset;
	t_asmmodel model;
	char  error[256];
	int diff = 0; //jcc后字节差 比如本来是short jnz  改成 jnz 多了三个字节
	while (nowlist)
	{
		char jcc[10];
		switch (nowlist->udobj.mnemonic)
		{
		case UD_Ija:
			strcpy(jcc,"ja ");
			break;
		case UD_Ijae:
			strcpy(jcc,"jae ");
			break;
		case UD_Ijb:
			strcpy(jcc,"jb ");
			break;
		case UD_Ijbe:
			strcpy(jcc,"jbe ");
			break;
		case UD_Ijcxz:
			strcpy(jcc,"jcxz ");
			break;
		case UD_Ijecxz:
			strcpy(jcc,"jecxz ");
			break;
		case UD_Ijz:
			strcpy(jcc,"jz ");
			break;
		case UD_Ijg:
			strcpy(jcc,"jg ");
			break;
		case UD_Ijge:
			strcpy(jcc,"jge ");
			break;
		case UD_Ijl:
			strcpy(jcc,"jl ");
			break;
		case UD_Ijle:
			strcpy(jcc,"jle ");
			break;
		case UD_Ijnz:
			strcpy(jcc,"jnz ");
			break;
		case UD_Ijno:
			strcpy(jcc,"jno ");
			break;
		case UD_Ijnp:
			strcpy(jcc,"jnp ");
			break;
		case UD_Ijns:
			strcpy(jcc,"jns ");
			break;
		case UD_Ijo:
			strcpy(jcc,"jo ");
			break;
		case UD_Ijp:
			strcpy(jcc,"jp ");
			break;
		case UD_Ijs:
			strcpy(jcc,"js ");
			break;
		case UD_Icall:
			strcpy(jcc,"call ");
			break;
		case UD_Ijmp:
			{
				is_jump = true;
				strcpy(jcc,"jmp ");
			}
			break;
		case UD_Iret:
			is_jump = true;
			break;
		default:
			strcpy(jcc,"");
			break;
		}
		int size ;
		int tempdiff;
		if (strcmp(jcc,"")!=0)
		{
			char jcc_addr[20];
			printf("%d \r\n",dddbg++);
			if (nowlist->udobj.operand[0].type == UD_OP_IMM || nowlist->udobj.operand[0].type == UD_OP_JIMM)
			{
				if (nowlist->udobj.operand[0].size==8) sprintf(jcc_addr,
					"%s0x%x",
					jcc,
					get_old_addr_to_new_addr(nowlist->udobj.operand[0].lval.sbyte+nowlist->udobj.pc));
				else if (nowlist->udobj.operand[0].size==16) sprintf(
					jcc_addr,
					"%s0x%x",
					jcc,
					get_old_addr_to_new_addr(nowlist->udobj.operand[0].lval.sword+nowlist->udobj.pc));
				else if (nowlist->udobj.operand[0].size==32) sprintf(
					jcc_addr,
					"%s0x%x",
					jcc,
					get_old_addr_to_new_addr(nowlist->udobj.operand[0].lval.sdword+nowlist->udobj.pc));
				//size = Disasm(jcc_addr,20, nowlist->udobj.insn_offset + diff, &da, DISASM_CODE);  应该是assemble的 弄错了
				memset(da.result,0,256);
				strcpy(da.result,jcc_addr);
				char *fkfk;
				if (fkfk = strchr(da.result,0xac))  //偶尔会出现几个无法识别的字符 
				{
					*fkfk = ' ';
				}
				if (fkfk = strchr(da.result,0xfe))
				{
					*fkfk = ' ';
				}
				if (fkfk = strchr(da.result,0xdc))
				{
					*fkfk = ' ';
				}
				for (int n = 0; n<strlen(da.result); n++)
				{
					if ( (da.result[n] >= 'A' && da.result[n] <= 'Z') || (da.result[n] >= 'a' && da.result[n] <= 'z') || 
						(da.result[n] >= '0' && da.result[n] <= '9'))
					{
					}
					else
					{
						da.result[n] = ' ';
					}
				}
				goto next;
			}

		}
		
		size = Disasm((char*)nowlist->udobj.inp_sess,20, nowlist->udobj.insn_offset + diff, &da, DISASM_CODE);
		//info->size += Assemble(da.result,info->base+nCodelen,&model,0,0,error);
next:
		info->size += tempdiff = Assemble(da.result,info->base+nCodelen,&model,0,nowlist->udobj.inp_ctr,error);

		if (strcmp(jcc,"")!=0)  //如果是jcc判断一下是否更改了大小   不是很重要
		{
			diff = tempdiff - nowlist->udobj.inp_ctr;
		}
		if (strcmp(error,"")!=0)
		{
			char *n;
			if (n = strstr(da.result,"SHORT"))
			{
				memset(n,' ',5);
				info->size = nCodelen;
				info->size += Assemble(da.result,info->base+nCodelen,&model,0,nowlist->udobj.inp_ctr,error);
				if (strcmp(error,"")!=0)
				{
					fprintf(stdout,"error 无法识别的指令");
					return NULL;
				}
			}
			else if (strcmp(error,"Unknown identifier")==0)
			{
				info->size = nCodelen;
				info->size += Assemble(nowlist->udobj.insn_buffer,info->base+nCodelen,&model,0,nowlist->udobj.inp_ctr,error);
				if (strcmp(error,"")!=0)
				{
					fprintf(stdout,"error 无法识别的指令");
					return NULL;
				}
			}  else
			fprintf(stdout,"error:%s buf:%s",error,da.result/*,nowlist->udobj.insn_buffer*/);
		}

		memcpy(
			&info->buf[nCodelen],
			model.code,
			info->size-nCodelen
			);
#ifdef DEBUG
		printf("size: %d          ",nowlist->udobj.inp_ctr);
#endif
		nCodelen = info->size;
#ifdef DEBUG
		fprintf(stdout,"addr:%08x  \r\n",nowlist->udobj.insn_offset);
#endif
		nowlist = nowlist->next;
	}

	char jmp_addr[20];   //跳到下一个目标
	if (block->next && is_jump == false)
	{
		sprintf(jmp_addr,"jmp 0x%08x",block->next->newaddr);
		//info->size += Assemble(jmp_addr,info->base+nCodelen,&model,0,0,error);
		info->size += Assemble(jmp_addr,block->newaddr+nCodelen,&model,0,0,error);
		memcpy(
			&info->buf[nCodelen],
			model.code,
			info->size-nCodelen
			);
	}


	return info;
}

template <class T>  T * OutOfOrder::recombine(T * t,int nSize)  //把数据乱序后返回  其他类无法调用 需要增加一个接口
{
	srand((int)time(0));
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

pInstructionBlockList OutOfOrder::get_instruction_block_list(int id)
{
	pInstructionBlockList nowlist = m_InstructionBlockHead;
	while (nowlist)
	{
		if (id == nowlist->id)
			return nowlist;
		nowlist = nowlist->next;
	}
	return NULL;
	
}

pCodeInformation OutOfOrder::code_recombine(pCodeInformation info)
{
	m_addr_table = new unsigned long*[m_block_max];
	for (int n=0;n<m_block_max;n++)
	{
		m_addr_table[n] = new unsigned long [4];
	}
	
	
	int *id_array = new int [m_block_max];
	for (int i=1;i<=m_block_max;i++)
	{
		id_array[i-1] = i;
	}
	fprintf(stdout,"max id:%d",m_block_max);
	id_array = recombine<int>(id_array,m_block_max);

	
	unsigned char buff[1024];
	pCodeInformation codeinfo = new CodeInformation;

	unsigned long base = info->base;
	codeinfo->base = base;
	codeinfo->buf = buff;
	codeinfo->size = 0;

	pInstructionBlockList nowlist = m_InstructionBlockHead;
	fprintf(stdout,"\r\n");

	int BUF_MAX_SIZE = 0xFFFF;
	unsigned char * asmbuf = new unsigned char[BUF_MAX_SIZE]; //先分配那么多
	for (int i = 0;i < BUF_MAX_SIZE;i++)
	{
		asmbuf[i] = rand()%0xFF;
	}
	unsigned long asmsize = 0;
	int j = 1;

	unsigned long *block_size_array = new unsigned long[m_block_max];  //下面二次覆盖时  无需从新移动位置
	for (j = 1;j <= m_block_max; j++)
	{
		pInstructionBlockList nowlist = get_instruction_block_list(id_array[j-1]);

		codeinfo = build_block(nowlist,codeinfo);
		m_addr_table[j-1][0] = nowlist->list->udobj.insn_offset; //填充addr.table原始地址
		m_addr_table[j-1][1] = codeinfo->base; //填充addr.table原始地址
		m_addr_table[j-1][2] = codeinfo->size;
		m_addr_table[j-1][3] = id_array[j-1];

		if (asmsize + codeinfo->size > 0xFFFF)  //内存不够了 从新分配
		{
			unsigned char * newasmbuf = new unsigned char[BUF_MAX_SIZE+0xFFFF];
			for (int i = 0; i < BUF_MAX_SIZE+0xFFFF; i++)
			{
				newasmbuf[i] = rand()%0xFF;  //用随机数填充
			}
			memcpy(newasmbuf,asmbuf,BUF_MAX_SIZE);
			BUF_MAX_SIZE += 0xFFFF;
			delete [] asmbuf;
			asmbuf = newasmbuf;
		}
		memcpy(&asmbuf[asmsize],codeinfo->buf,codeinfo->size);
		asmsize += codeinfo->size + 10; //预留5字节 可以放jmp         *******************************************************************
		codeinfo->base = base + asmsize;

		block_size_array[j-1] = codeinfo->size + 10;  //当前块有多少byte代码
	}
#ifdef DEBUG
	fprintf(stdout,"2 build reloc jcc");
#endif
	asmsize = 0;
	for (j = 1;j <= m_block_max; j++)  //二次覆盖
	{
		pInstructionBlockList nowlist = get_instruction_block_list(id_array[j-1]);
		if (nowlist->list->udobj.insn_offset == 0x40192d)
		{
	//		__asm int 3
		}
		codeinfo = build_reloc_jcc(nowlist,codeinfo);

		//m_addr_table[j-1][0] = nowlist->list->udobj.insn_offset; //填充addr.table原始地址
		//m_addr_table[j-1][1] = codeinfo->base; //填充addr.table原始地址
		//m_addr_table[j-1][3] = codeinfo->size;

		memcpy(&asmbuf[asmsize],codeinfo->buf,codeinfo->size);
		//asmsize += codeinfo->size; //预留5字节 可以放jmp
		//asmsize += (5 - codeinfo->size - block_size_array[j-1]);
		asmsize += block_size_array[j-1];

		codeinfo->base = base + asmsize;
	}

	//while (nowlist)
	//{
	//	codeinfo = build_block(nowlist,codeinfo);
	//	//printf("%08x",&codeinfo->buf);
	//	for (int i=0;i<codeinfo->size;i++)
	//	{
	//		fprintf(stdout,"%x ",codeinfo->buf[i]);
	//	}
	//	fprintf(stdout,"\r\n");
	//	nowlist = nowlist->next;
	//}

	
	delete  codeinfo;
	//delete [] asmbuf;
	m_codebuf = asmbuf;
	info->buf = m_codebuf;
	info->size = asmsize;
	return info;
}

pCodeInformation OutOfOrder::code_out_of_order(pCodeInformation info,unsigned long imagebase)
{
	ud_t ud_obj;
	ud_init(&ud_obj);
	ud_set_mode(&ud_obj, 32);
	ud_set_pc(&ud_obj,info->base);
	ud_set_input_buffer(&ud_obj, info->buf, info->size);
	ud_set_syntax(&ud_obj, UD_SYN_INTEL);

	while (ud_disassemble(&ud_obj) != 0 ) {
//		fprintf(stdout,"%s",ud_insn_asm(&ud_obj));
		if (ud_obj.mnemonic == UD_Inop)
		{
			continue;
		}
		else if (ud_obj.mnemonic == UD_Iint3)
		{
			continue;
		}
		pInstructionList list = NULL;
		add_instruction_block_list(add_instruction_list(list,&ud_obj));
		
	}
	//if (ud_obj.mnemonic != UD_Ijmp || ud_obj.mnemonic != UD_Iret )
	//{
	//	ud_t *newud= new ud_t;
	//	newud->inp_sess[0] = 0xE9;
	//	*(int *)&newud->inp_sess[1] = (int)(info->base + info->size - (info->base) - 5);
	//	newud->insn_offset = info->base + info->size;
	//	sprintf(newud->insn_buffer,"jmp 0%x",(int)(info->base));
	//	newud->inp_ctr = 5;
	//	newud->mnemonic = UD_Ijmp;
	//	pInstructionList list = NULL;
	//	add_instruction_block_list(add_instruction_list(list,newud));
	//}


	info->base = imagebase;
	info = code_recombine(info);

	return info;
}
























