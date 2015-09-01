#include <WPStruct.h>
#include <CodeList.h>
#include <string.h>
#include <stdio.h>

pInstructionBlockList m_InstructionBlockHead = NULL;
unsigned long m_block_max = 0;
pInstructionList add_instruction_list(pInstructionBlockList block,ud_t *pobj)
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

pInstructionList add_instruction_list(pInstructionList instruction,ud_t *pobj)
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

pInstructionBlockList add_instruction_block_list()
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

pInstructionBlockList get_instruction_block_list_head()
{
	return m_InstructionBlockHead;
}

pInstructionBlockList add_instruction_block_list(pInstructionList instruction)
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

void clean_instruction_list(pInstructionList head)
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

void clean_instruction_block_list()
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
	m_block_max = 0;
}