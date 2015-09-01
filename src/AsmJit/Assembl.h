#ifndef  ASSEMBL_H
#define  ASSEMBL_H

#include "AsmJit.h"
#include <iostream>
#include <list>

using namespace AsmJit;

typedef struct asmmodel {
    char code[256];
    char mask[256];
    int length;
} asmmodel;

#define TEXTLEN        256             // Maximal length of text string

typedef struct asmoperand {
	int            type;                 // Operand type, see beginning of file
	int            size;                 // Operand size or 0 if yet unknown
	int            index;                // Index or other register
	int            scale;                // Scale
	int            base;                 // Base register if present
	long           offset;               // Immediate value or offset
	int            anyoffset;            // Offset is present but undefined
	int            segment;              // Segment in address if present
	int            jmpmode;              // Specified jump size
	Label * label;
	int           mode;   //判断是否是什么类型  浮点还是什么  上面的类型是reg 这个是
} asmoperand;


typedef struct label_list {
	char labelname[256];
	Label label;
};

class Assembl
{
public:
    Assembl();
    ~Assembl();
public:
     int Assemble(char *cmd,ulong ip,asmmodel *model,char *error);
	 int Assemble(char *cmd);

	void Parseasmoperand(asmoperand *op);
    Assembler a;
	void Scanasm(int mode);
	const GPReg * get_reg(int reg,int size);
	const Operand get_operand(asmoperand *op);
	void reloc(unsigned long relocaddr);
	unsigned char * get_code();
	int get_code_size();
	char      *asmcmd;              // Pointer to 0-terminated source line
	int       scan;                 // Type of last scanned element
	int       prio;                 // Priority of operation (0: highest)
	char      sdata[TEXTLEN];       // Last scanned name (depends on type)
	long      idata;                // Last scanned value
	long      double fdata;         // Floating-point number
	const char      *asmerror;            // Explanation of last error, or NULL
	Label * now_label;                        // 指向label的指针
	std::list <label_list> l_label;
};
#endif
