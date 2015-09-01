#include <stdio.h>
#include <string.h>

#ifndef WPROTECTCONFIG_H
#define WPROTECTCONFIG_H
#include <WProtectConfig.h>
#endif

#ifndef ASMJIT_H
#define ASMJIT_H
#include <AsmJit.h>
#endif

#ifndef LIBUDIS86_H
#define LIBUDIS86_H
#include <udis86.h>
#endif

#ifndef SINGLEOUTOFORDER_H
#define SINGLEOUTOFORDER_H
#include "SingleOutOfOrder.h0"
#endif

using namespace AsmJit;

CSingleCodeComplicated::CSingleCodeComplicated()
{
	
}

InstructionsInfo *CSingleCodeComplicated::mov()
{
	InstructionsInfo
}

InstructionsInfo *CSingleCodeComplicated::create_info()
{
	InstructionsInfo *info = new InstructionsInfo;
	memset(info,0,sizeof(InstructionsInfo));
	return info;
}

void CSingleCodeComplicated::copy_info(InstructionsInfo *info,Assembler a)
{
	info->code_buf = new unsigned char[a.getCodeSize()];
	memcpy(info->code_buf,a.getCode(),a.getCodeSize());
	info->code_size = a.getCodeSize();
}

InstructionsInfo *CSingleCodeComplicated::save_single_register(GPReg reg)
{
    InstructionsInfo * info = create_info();
	Assembler a;
    a.push(reg);
	copy_info(info,a);
	info->stack_change = 4;
}

InstructionsInfo *CSingleCodeComplicated::save_register()
{
	InstructionsInfo *info = create_info();
	GPReg * RegArray = new GPReg[8];
	RegArray[0] = nax;
	RegArray[1] = nbx;
	RegArray[2] = ncx;
	RegArray[3] = ndx;
	RegArray[4] = nsp;
	RegArray[5] = nbp;
	RegArray[6] = nsi;
	RegArray[7] = ndi;
	RegArray = disordering(RegArray,8);
	Assembler a;
	for (int i = 0; i < 8; i++)
	{
        info->stack_change += save_single_register(RegArray[i])->stack_change;
	}
	copy_info(info,a);
    return info;
}

template <class T>  T * CSingleCodeComplicated::disordering(T * t,int nSize)
{
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

InstructionsInfo *CSingleCodeComplicated::load_instruction(void *code_buf,unsigned long code_size)
{
	ud_t ud_obj;
	ud_init(&ud_obj);
	ud_set_mode(&ud_obj,32);
	ud_set_pc(&ud_obj,0);
	ud_set_input_buffer(&ud_obj,code_buf,code_size);
	ud_set_syntax(&ud_obj,UD_SYN_INTEL);
	while (ud_disassemble(&ud_obj) != 0)
	{
		switch (ud_obj.mnemonic)
		{
		case UD_NONE:
			break;
		case UD_Imov:
			{
					
			}
		}
	}
	
}
