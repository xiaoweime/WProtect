
#include "Assembl.h"
#include <string.h>
#include "opcode_table.h"
#include <ctype.h>
//#include <direct.h>
#include <math.h>
#include <float.h>
#include <WProtectConfig.h>

#ifndef WINDOWS
#include <MyString.h>
#endif


Assembl::Assembl()
{

}
Assembl::~Assembl()
{

}

using namespace AsmJit;

typedef struct t_addrdec {
	int            defseg;
	char           *descr;
} t_addrdec;

// Scanner modes.
#define SA_NAME        0x0001          // Don't try to decode labels
#define SA_IMPORT      0x0002          // Allow import pseudolabel

// Types of input tokens reported by scanner.
#define SCAN_EOL       0               // End of line
#define SCAN_REG8      1               // 8-bit register
#define SCAN_REG16     2               // 16-bit register
#define SCAN_REG32     3               // 32-bit register
#define SCAN_SEG       4               // Segment register
#define SCAN_FPU       5               // FPU register
#define SCAN_MMX       6               // MMX register
#define SCAN_CR        7               // Control register
#define SCAN_DR        8               // Debug register
#define SCAN_OPSIZE    9               // Operand size modifier
#define SCAN_JMPSIZE   10              // Jump size modifier
#define SCAN_LOCAL     11              // Address on stack in form LOCAL.decimal
#define SCAN_ARG       12              // Address on stack in form ARG.decimal
#define SCAN_PTR       20              // PTR in MASM addressing statements
#define SCAN_REP       21              // REP prefix
#define SCAN_REPE      22              // REPE prefix
#define SCAN_REPNE     23              // REPNE prefix
#define SCAN_LOCK      24              // LOCK prefix
#define SCAN_NAME      25              // Command or label
#define SCAN_ICONST    26              // Hexadecimal constant
#define SCAN_DCONST    27              // Decimal constant
#define SCAN_OFS       28              // Undefined constant
#define SCAN_FCONST    29              // Floating-point constant
#define SCAN_EIP       30              // Register EIP
#define SCAN_SIGNED    31              // Keyword "SIGNED" (in expressions)
#define SCAN_UNSIGNED  32              // Keyword "UNSIGNED" (in expressions)
#define SCAN_CHAR      33              // Keyword "CHAR" (in expressions)
#define SCAN_FLOAT     34              // Keyword "FLOAT" (in expressions)
#define SCAN_DOUBLE    35              // Keyword "DOUBLE" (in expressions)
#define SCAN_FLOAT10   36              // Keyword "FLOAT10" (in expressions)
#define SCAN_STRING    37              // Keyword "STRING" (in expressions)
#define SCAN_UNICODE   38              // Keyword "UNICODE" (in expressions)
#define SCAN_MSG       39              // Pseudovariable MSG (in expressions)

#define SCAN_LABEL     40              //是否是注释
#define SCAN_LABEL_BIND 41

#define SCAN_REG64     42               // 32-bit register

#define SCAN_SYMB      64              // Any other character
#define SCAN_IMPORT    65              // Import pseudolabel
#define SCAN_ERR       255             // Definitely bad item

#define SEG_UNDEF     -1
#define SEG_ES         0               // Indexes of segment/selector registers
#define SEG_CS         1
#define SEG_SS         2
#define SEG_DS         3
#define SEG_FS         4
#define SEG_GS         5

#ifdef PROTECT_X64
const char *w_regname[5][9] = {
	{ "AL", "CL", "DL", "BL", "AH", "CH", "DH", "BH", "REG8"  },
	{ "AX", "CX", "DX", "BX", "SP", "BP", "SI", "DI", "REG16" },
	{ "EAX","ECX","EDX","EBX","ESP","EBP","ESI","EDI","REG32" },
	{ "RAX","RCX","RDX","RBX","RSP","RBP","RSI","RDI","REG64" },
	{ "R8","R9","R10","R11","R12","R13","R14","R15","R64" }
};
#else
const char *w_regname[3][9] = {
	{ "AL", "CL", "DL", "BL", "AH", "CH", "DH", "BH", "REG8"  },
	{ "AX", "CX", "DX", "BX", "SP", "BP", "SI", "DI", "REG16" },
	{ "EAX","ECX","EDX","EBX","ESP","EBP","ESI","EDI","REG32" }
};
#endif


	const char *w_segname[8] = {
		"ES","CS","SS","DS","FS","GS","SEG?","SEG?" };

		const char *w_sizename[11] = {
			"(0-BYTE)", "BYTE", "WORD", "(3-BYTE)",
			"DWORD", "(5-BYTE)", "FWORD", "(7-BYTE)",
			"QWORD", "(9-BYTE)", "TBYTE" };

			const t_addrdec w_addr16[8] = {
				{ SEG_DS,"BX+SI" }, { SEG_DS,"BX+DI" },
				{ SEG_SS,"BP+SI" }, { SEG_SS,"BP+DI" },
				{ SEG_DS,"SI" },    { SEG_DS,"DI" },
				{ SEG_SS,"BP" },    { SEG_DS,"BX" } };

				const t_addrdec w_addr32[8] = {
					{ SEG_DS,"EAX" }, { SEG_DS,"ECX" },
					{ SEG_DS,"EDX" }, { SEG_DS,"EBX" },
					{ SEG_SS,"" },    { SEG_SS,"EBP" },
					{ SEG_DS,"ESI" }, { SEG_DS,"EDI" } };

					const char *w_fpuname[9] = {
						"ST0","ST1","ST2","ST3","ST4","ST5","ST6","ST7","FPU" };

						const char *w_mmxname[9] = {
							"MM0","MM1","MM2","MM3","MM4","MM5","MM6","MM7","MMX" };

							const char *w_crname[9] = {
								"CR0","CR1","CR2","CR3","CR4","CR5","CR6","CR7","CRX" };

								const char *w_drname[9] = {
									"DR0","DR1","DR2","DR3","DR4","DR5","DR6","DR7","DRX" };

#define NNN            0               // No operand
#define REG            1               // Integer register in Reg field
#define RCM            2               // Integer register in command byte
#define RG4            3               // Integer 4-byte register in Reg field
#define RAC            4               // Accumulator (AL/AX/EAX, implicit)
#define RAX            5               // AX (2-byte, implicit)
#define RDX            6               // DX (16-bit implicit port address)
#define RCL            7               // Implicit CL register (for shifts)
#define RS0            8               // Top of FPU stack (ST(0), implicit)
#define RST            9               // FPU register (ST(i)) in command byte
#define RMX            10              // MMX register MMx
#define R3D            11              // 3DNow! register MMx
#define MRG            12              // Memory/register in ModRM byte
#define MR1            13              // 1-byte memory/register in ModRM byte
#define MR2            14              // 2-byte memory/register in ModRM byte
#define MR4            15              // 4-byte memory/register in ModRM byte
#define RR4            16              // 4-byte memory/register (register only)
#define MR8            17              // 8-byte memory/MMX register in ModRM
#define RR8            18              // 8-byte MMX register only in ModRM
#define MRD            19              // 8-byte memory/3DNow! register in ModRM
#define RRD            20              // 8-byte memory/3DNow! (register only)
#define MRJ            21              // Memory/reg in ModRM as JUMP target
#define MMA            22              // Memory address in ModRM byte for LEA
#define MML            23              // Memory in ModRM byte (for LES)
#define MMS            24              // Memory in ModRM byte (as SEG:OFFS)
#define MM6            25              // Memory in ModRm (6-byte descriptor)
#define MMB            26              // Two adjacent memory locations (BOUND)
#define MD2            27              // Memory in ModRM (16-bit integer)
#define MB2            28              // Memory in ModRM (16-bit binary)
#define MD4            29              // Memory in ModRM byte (32-bit integer)
#define MD8            30              // Memory in ModRM byte (64-bit integer)
#define MDA            31              // Memory in ModRM byte (80-bit BCD)
#define MF4            32              // Memory in ModRM byte (32-bit float)
#define MF8            33              // Memory in ModRM byte (64-bit float)
#define MFA            34              // Memory in ModRM byte (80-bit float)
#define MFE            35              // Memory in ModRM byte (FPU environment)
#define MFS            36              // Memory in ModRM byte (FPU state)
#define MFX            37              // Memory in ModRM byte (ext. FPU state)
#define MSO            38              // Source in string op's ([ESI])
#define MDE            39              // Destination in string op's ([EDI])
#define MXL            40              // XLAT operand ([EBX+AL])
#define IMM            41              // Immediate data (8 or 16/32)
#define IMU            42              // Immediate unsigned data (8 or 16/32)
#define VXD            43              // VxD service
#define IMX            44              // Immediate sign-extendable byte
#define C01            45              // Implicit constant 1 (for shifts)
#define IMS            46              // Immediate byte (for shifts)
#define IM1            47              // Immediate byte
#define IM2            48              // Immediate word (ENTER/RET)
#define IMA            49              // Immediate absolute near data address
#define JOB            50              // Immediate byte offset (for jumps)
#define JOW            51              // Immediate full offset (for jumps)
#define JMF            52              // Immediate absolute far jump/call addr
#define SGM            53              // Segment register in ModRM byte
#define SCM            54              // Segment register in command byte
#define CRX            55              // Control register CRx
#define DRX            56              // Debug register DRx
#define LABEL          57              // 标签

#define REG_EAX        0               // Indexes of general-purpose registers
#define REG_ECX        1               // in t_reg.
#define REG_EDX        2
#define REG_EBX        3
#define REG_ESP        4
#define REG_EBP        5
#define REG_ESI        6
#define REG_EDI        7

void Assembl::Scanasm(int mode) {

	int i,j,base,maxdigit;
	long decimal,hex;
	long double floating,divisor;
	char s[TEXTLEN],*pcmd;
	sdata[0]='\0';
	idata=0;
	if (asmcmd==NULL) {
		asmerror="NULL input line"; scan=SCAN_ERR; return; };

		while (*asmcmd==' ' || *asmcmd=='\t')
			asmcmd++;                          // Skip leading spaces

		if (*asmcmd=='\0' || *asmcmd==';') {
			scan=SCAN_EOL; return; };          // Empty line


			char t_lable[256];
			strcpy(t_lable,asmcmd);
			char *is_lable = strchr(t_lable,':');  //判断是否标签
			char *check1 = strchr(asmcmd,'[');
			char *check2 = strchr(asmcmd,']');
			if (is_lable && !check1 && !check2)
			{
				strupr(t_lable);
				*is_lable = '\0';
				std::list <label_list> ::iterator labeliter;
				bool is_existing = false;
				for (labeliter = l_label.begin();labeliter!=l_label.end();++labeliter)
				{
					if (strcmp(labeliter->labelname,t_lable) == 0)
					{
						is_existing = true;
						a.bind(labeliter->label);
					}

				}
				if (is_existing == false)
				{
					label_list label;
					label.label = a.newLabel();
					strcpy(label.labelname,t_lable);
					l_label.push_back(label);
					a.bind(l_label.back().label);
				}
				scan = SCAN_LABEL_BIND;
				return;
			}

			if (isalpha(*asmcmd) || *asmcmd=='_' || *asmcmd=='@') {
				sdata[0]=*asmcmd++; i=1;           // Some keyword or identifier
				while ((isalnum(*asmcmd) || *asmcmd=='_' || *asmcmd=='@') &&
					i<sizeof(sdata))
					sdata[i++]=*asmcmd++;
				if (i>=sizeof(sdata)) {
					asmerror="Too long identifier"; scan=SCAN_ERR; return; };
					sdata[i]='\0';
					while (*asmcmd==' ' || *asmcmd=='\t')
						asmcmd++;                        // Skip trailing spaces
					strcpy(s,sdata); strupr(s);
					for (j=0; j<=8; j++) {             // j==8 means "any register"
						if (strcmp(s,w_regname[0][j])!=0) continue;
						idata=j; scan=SCAN_REG8;         // 8-bit register
						return; };
						for (j=0; j<=8; j++) {
							if (strcmp(s,w_regname[1][j])!=0) continue;
							idata=j; scan=SCAN_REG16;        // 16-bit register
							return; };
							for (j=0; j<=8; j++) {
								if (strcmp(s,w_regname[2][j])!=0) continue;
								idata=j; scan=SCAN_REG32;        // 32-bit register
								return; };
#ifdef PROTECT_X64
								for (j=0; j<=8; j++) {
									if (strcmp(s,w_regname[3][j])!=0) continue;
									idata=j; scan=SCAN_REG64;        // 64-bit register
									return; };
									for (j=0; j<=8; j++) {
										if (strcmp(s,w_regname[4][j])!=0) continue;
										idata=j+8; scan=SCAN_REG64;        // 64-bit register
										return; };
#endif
								for (j=0; j<6; j++) {
									if (strcmp(s,w_segname[j])!=0) continue;
									idata=j; scan=SCAN_SEG;          // Segment register
									while (*asmcmd==' ' || *asmcmd=='\t')
										asmcmd++;                      // Skip trailing spaces
									return; };
									if (strcmp(s,"ST")==0) {
										pcmd=asmcmd; Scanasm(SA_NAME);   // FPU register
										if (scan!=SCAN_SYMB || idata!='(') {
											asmcmd=pcmd;                   // Undo last scan
											idata=0; scan=SCAN_FPU; return; };
											Scanasm(SA_NAME); j=idata;
											if ((scan!=SCAN_ICONST && scan!=SCAN_DCONST) || idata<0 || idata>7) {
												asmerror="FPU registers have indexes 0 to 7";
												scan=SCAN_ERR; return; };
												Scanasm(SA_NAME);
												if (scan!=SCAN_SYMB || idata!=')') {
													asmerror="Closing parenthesis expected";
													scan=SCAN_ERR; return; };
													idata=j; scan=SCAN_FPU; return; };
													for (j=0; j<=8; j++) {
														if (strcmp(s,w_fpuname[j])!=0) continue;
														idata=j; scan=SCAN_FPU;          // FPU register (alternative coding)
														return; };
														for (j=0; j<=8; j++) {
															if (strcmp(s,w_mmxname[j])!=0) continue;
															idata=j; scan=SCAN_MMX;          // MMX register
															return; };
															for (j=0; j<=8; j++) {
																if (strcmp(s,w_crname[j])!=0) continue;
																idata=j; scan=SCAN_CR;           // Control register
																return; };
																for (j=0; j<=8; j++) {
																	if (strcmp(s,w_drname[j])!=0) continue;
																	idata=j; scan=SCAN_DR;           // Debug register
																	return; };
																	for (j=0; j<sizeof(w_sizename)/sizeof(w_sizename[0]); j++) {
																		if (strcmp(s,w_sizename[j])!=0) continue;
																		pcmd=asmcmd; Scanasm(SA_NAME);
																		if (scan!=SCAN_PTR)              // Fetch non-functional "PTR"
																			asmcmd=pcmd;
																		idata=j; scan=SCAN_OPSIZE;       // Operand (data) size in bytes
																		return; };
																		if (strcmp(s,"EIP")==0) {          // Register EIP
																			scan=SCAN_EIP; idata=0; return; };
																			if (strcmp(s,"SHORT")==0) {        // Relative jump has 1-byte offset
																				scan=SCAN_JMPSIZE; idata=1; return; };
																				if (strcmp(s,"LONG")==0) {         // Relative jump has 4-byte offset
																					scan=SCAN_JMPSIZE; idata=2; return; };
																					if (strcmp(s,"NEAR")==0) {         // Jump within same code segment
																						scan=SCAN_JMPSIZE; idata=4; return; };
																						if (strcmp(s,"FAR")==0) {          // Jump to different code segment
																							scan=SCAN_JMPSIZE; idata=8; return; };
																							if (strcmp(s,"LOCAL")==0 && *asmcmd=='.') {
																								asmcmd++;
																								while (*asmcmd==' ' || *asmcmd=='\t')
																									asmcmd++;                      // Skip trailing spaces
																								if (!isdigit(*asmcmd)) {
																									asmerror="Integer number expected";
																									scan=SCAN_ERR; return; };
																									while (isdigit(*asmcmd))         // LOCAL index is decimal number!
																										idata=idata*10+(*asmcmd++)-'0';
																									scan=SCAN_LOCAL; return; };
																									if (strcmp(s,"ARG")==0 && *asmcmd=='.') {
																										asmcmd++;
																										while (*asmcmd==' ' || *asmcmd=='\t')
																											asmcmd++;                      // Skip trailing spaces
																										if (!isdigit(*asmcmd)) {
																											asmerror="Integer number expected";
																											scan=SCAN_ERR; return; };
																											while (isdigit(*asmcmd))         // ARG index is decimal number!
																												idata=idata*10+(*asmcmd++)-'0';
																											scan=SCAN_ARG; return; };
																											if (strcmp(s,"REP")==0) {
																												scan=SCAN_REP; return; };        // REP prefix
																												if (strcmp(s,"REPE")==0 || strcmp(s,"REPZ")==0) {
																													scan=SCAN_REPE; return; };       // REPE prefix
																													if (strcmp(s,"REPNE")==0 || strcmp(s,"REPNZ")==0) {
																														scan=SCAN_REPNE; return; };      // REPNE prefix
																														if (strcmp(s,"LOCK")==0) {
																															scan=SCAN_LOCK; return; };       // LOCK prefix
																															if (strcmp(s,"PTR")==0) {
																																scan=SCAN_PTR; return; };        // PTR in MASM addressing statements
																																if (strcmp(s,"CONST")==0 || strcmp(s,"OFFSET")==0) {
																																	scan=SCAN_OFS; return; };        // Present but undefined offset/constant
																																	if (strcmp(s,"SIGNED")==0) {
																																		scan=SCAN_SIGNED; return; };     // Keyword "SIGNED" (in expressions)
																																		if (strcmp(s,"UNSIGNED")==0) {
																																			scan=SCAN_UNSIGNED; return; };   // Keyword "UNSIGNED" (in expressions)
																																			if (strcmp(s,"CHAR")==0) {
																																				scan=SCAN_CHAR; return; };       // Keyword "CHAR" (in expressions)
																																				if (strcmp(s,"FLOAT")==0) {
																																					scan=SCAN_FLOAT; return; };      // Keyword "FLOAT" (in expressions)
																																					if (strcmp(s,"DOUBLE")==0) {
																																						scan=SCAN_DOUBLE; return; };     // Keyword "DOUBLE" (in expressions)
																																						if (strcmp(s,"FLOAT10")==0) {
																																							scan=SCAN_FLOAT10; return; };    // Keyword "FLOAT10" (in expressions)
																																							if (strcmp(s,"STRING")==0) {
																																								scan=SCAN_STRING; return; };     // Keyword "STRING" (in expressions)
																																								if (strcmp(s,"UNICODE")==0) {
																																									scan=SCAN_UNICODE; return; };    // Keyword "UNICODE" (in expressions)
																																									if (strcmp(s,"MSG")==0) {
																																										scan=SCAN_MSG; return; };        // Pseudovariable MSG (in expressions)
																																										if (mode & SA_NAME) {            //标签
																																											idata=i; scan=SCAN_NAME;         // Don't try to decode symbolic label
																																											return; }
																																										std::list <label_list> ::iterator labeliter;
																																										bool is_existing = false;
																																										for (labeliter = l_label.begin();labeliter!=l_label.end();++labeliter)
																																										{
																																											if (strcmp(labeliter->labelname,s) == 0)
																																											{
																																												is_existing = true;
																																												now_label = &labeliter->label;
																																											//	a.bind(labeliter->label);
																																											}
																																										}
																																										if (is_existing == false)
																																										{
																																											label_list label;
																																											//label.label = a.newLabel();
																																											strcpy(label.labelname,s);
																																											l_label.push_back(label);
																																											l_label.back().label = a.newLabel();
																																											now_label = &l_label.back().label;
																																										}
																																										scan = SCAN_LABEL;
																																										return;
																																										/*asmerror="Unknown identifier";*/
																																										/*scan=SCAN_ERR; return; */}                //如过是不认识的东西就暂时把他当做标签
				else if (isdigit(*asmcmd)) {         // Constant
					base=0; maxdigit=0; decimal=hex=0L; floating=0.0;
					if (asmcmd[0]=='0' && toupper(asmcmd[1])=='X') {
						base=16; asmcmd+=2; };           // Force hexadecimal number
						while (1) {
							if (isdigit(*asmcmd)) {
								decimal=decimal*10+(*asmcmd)-'0';
								floating=floating*10.0+(*asmcmd)-'0';
								hex=hex*16+(*asmcmd)-'0';
								if (maxdigit==0) maxdigit=9;
								asmcmd++; }
							else if (isxdigit(*asmcmd)) {
								hex=hex*16+toupper(*asmcmd++)-'A'+10;
								maxdigit=15; }
							else break; };
							if (maxdigit==0) {
								asmerror="Hexadecimal digits after 0x... expected";
								scan=SCAN_ERR; return; };
								if (toupper(*asmcmd)=='H') {       // Force hexadecimal number
									if (base==16) {
										asmerror="Please don't mix 0xXXXX and XXXXh forms";
										scan=SCAN_ERR; return; };
										asmcmd++;
										idata=hex; scan=SCAN_ICONST;
										while (*asmcmd==' ' || *asmcmd=='\t') asmcmd++;
										return; };
										if (*asmcmd=='.') {                // Force decimal number
											if (base==16 || maxdigit>9) {
												asmerror="Not a decimal number"; scan=SCAN_ERR; return; };
												asmcmd++;
												if (isdigit(*asmcmd) || toupper(*asmcmd)=='E') {
													divisor=1.0;
													while (isdigit(*asmcmd)) {     // Floating-point number
														divisor/=10.0;
														floating+=divisor*(*asmcmd-'0');
														asmcmd++; };
														if (toupper(*asmcmd)=='E') {
															asmcmd++;
															if (*asmcmd=='-') { base=-1; asmcmd++; }
															else base=1;
															if (!isdigit(*asmcmd)) {
																asmerror="Invalid exponent"; scan=SCAN_ERR; return; };
																decimal=0;
																while (isdigit(*asmcmd)) {
																	if (decimal<65536L) decimal=decimal*10+(*asmcmd++)-'0'; };
																	floating*=pow(10.0,decimal*base); };
																	fdata=floating;
																	scan=SCAN_FCONST; return; }
												else {
													idata=decimal; scan=SCAN_DCONST;
													while (*asmcmd==' ' || *asmcmd=='\t') asmcmd++;
													return;
												};
										};
										idata=hex; scan=SCAN_ICONST;       // Default is hexadecimal
										while (*asmcmd==' ' || *asmcmd=='\t') asmcmd++;
										return; }
				else if (*asmcmd=='\'') {            // Character constant
					asmcmd++;
					if (*asmcmd=='\0' || (*asmcmd=='\\' && asmcmd[1]=='\0'))  {
						asmerror="Unterminated character constant"; scan=SCAN_ERR; return; };
						if (*asmcmd=='\'') {
							asmerror="Empty character constant"; scan=SCAN_ERR; return; };
							if (*asmcmd=='\\') asmcmd++;
							idata=*asmcmd++;
							if (*asmcmd!='\'')  {
								asmerror="Unterminated character constant"; scan=SCAN_ERR; return; };
								asmcmd++;
								while (*asmcmd==' ' || *asmcmd=='\t') asmcmd++;
								scan=SCAN_ICONST; return; }
				else {                               // Any other character or combination
					idata=sdata[0]=*asmcmd++; sdata[1]=sdata[2]='\0';
					if (idata=='|' && *asmcmd=='|') {
						idata='||'; prio=10;             // '||'
						sdata[1]=*asmcmd++; }
					else if (idata=='&' && *asmcmd=='&') {
						idata='&&'; prio=9;              // '&&'
						sdata[1]=*asmcmd++; }
					else if (idata=='=' && *asmcmd=='=') {
						idata='=='; prio=5;              // '=='
						sdata[1]=*asmcmd++; }
					else if (idata=='!' && *asmcmd=='=') {
						idata='!='; prio=5;              // '!='
						sdata[1]=*asmcmd++; }
					else if (idata=='<' && *asmcmd=='=') {
						idata='<='; prio=4;              // '<='
						sdata[1]=*asmcmd++; }
					else if (idata=='>' && *asmcmd=='=') {
						idata='>='; prio=4;              // '>='
						sdata[1]=*asmcmd++; }
					else if (idata=='<' && *asmcmd=='<') {
						idata='<<'; prio=3;              // '<<'
						sdata[1]=*asmcmd++; }
					else if (idata=='>' && *asmcmd=='>') {
						idata='>>'; prio=3;              // '>>'
						sdata[1]=*asmcmd++; }
					else if (idata=='|') prio=8;       // '|'
					else if (idata=='^') prio=7;       // '^'
					else if (idata=='&') prio=6;       // '&'
					else if (idata=='<') {
						if (*asmcmd=='&') {              // Import pseudolabel (for internal use)
							if ((mode & SA_IMPORT)==0) {
								asmerror="Syntax error"; scan=SCAN_ERR; return; };
								asmcmd++; i=0;
								while (*asmcmd!='\0' && *asmcmd!='>') {
									sdata[i++]=*asmcmd++;
									if (i>=sizeof(sdata)) {
										asmerror="Too long import name"; scan=SCAN_ERR; return;
									};
								};
								if (*asmcmd!='>') {
									asmerror="Unterminated import name"; scan=SCAN_ERR; return; };
									asmcmd++; sdata[i]='\0';
									scan=SCAN_IMPORT; return; }
						else prio=4; }                   // '<'
					else if (idata=='>') prio=4;       // '>'
					else if (idata=='+') prio=2;       // '+'
					else if (idata=='-') prio=2;       // '-'
					else if (idata=='*') prio=1;       // '*'
					else if (idata=='/') prio=1;       // '/'
					else if (idata=='%') prio=1;       // '%'
					else if (idata==']') {
						pcmd=asmcmd; Scanasm(SA_NAME);
						if (scan!=SCAN_SYMB || idata!='[') {
							idata=']'; asmcmd=pcmd; prio=0; }
						else {
							idata='+'; prio=2;             // Translate '][' to '+'
						};
					}
					else prio=0;                       // Any other character
					scan=SCAN_SYMB;
					return;
				};
};


 void Assembl::Parseasmoperand(asmoperand *op) {
	int i,j,bracket,sign,xlataddr;
	int reg,r[9+8];
	long offset;
	if (scan==SCAN_EOL || scan==SCAN_ERR)
		return;                            // No or bad operand

	//标签
	if (scan == SCAN_LABEL)
	{
		op->type = LABEL;
		op->label = now_label;
		return;
	}
	// Jump or call address may begin with address size modifier(s) SHORT, LONG,
	// NEAR and/or FAR. Not all combinations are allowed. After operand is
	// completely parsed, this function roughly checks whether modifier is
	// allowed. Exact check is done in Assemble().
	if (scan==SCAN_JMPSIZE) {
		j=0;
		while (scan==SCAN_JMPSIZE) {
			j|=idata;                        // Fetch all size modifiers
			Scanasm(0); };
			if (
				((j & 0x03)==0x03) ||            // Mixed SHORT and LONG
				((j & 0x0C)==0x0C) ||            // Mixed NEAR and FAR
				((j & 0x09)==0x09)               // Mixed FAR and SHORT
				) {
					asmerror="Invalid combination of jump address modifiers";
					scan=SCAN_ERR; return; };
					if ((j & 0x08)==0) j|=0x04;        // Force NEAR if not FAR
					op->jmpmode=j; };
					// Simple operands are either register or constant, their processing is
					// obvious and straightforward.
					if (scan==SCAN_REG8 || scan==SCAN_REG16 || scan==SCAN_REG32 || scan == SCAN_REG64) {
						op->type=REG; op->index=idata;     // Integer general-purpose register
						if (scan==SCAN_REG8) op->size=1;
						else if (scan==SCAN_REG16) op->size=2;
						else if (scan==SCAN_REG64) op->size=8; //64位寄存器
						else op->size=4; }
					else if (scan==SCAN_FPU) {           // FPU register
						op->type=RST; op->index=idata; }
					else if (scan==SCAN_MMX) {           // MMX or 3DNow! register
						op->type=RMX; op->index=idata; }
					else if (scan==SCAN_CR) {            // Control register
						op->type=CRX; op->index=idata; }
					else if (scan==SCAN_DR) {            // Debug register
						op->type=DRX; op->index=idata; }
					else if (scan==SCAN_SYMB && idata=='-') {
						Scanasm(0);                        // Negative constant
						if (scan!=SCAN_ICONST && scan!=SCAN_DCONST && scan!=SCAN_OFS) {
							asmerror="Integer number expected";
							scan=SCAN_ERR; return; };
							op->type=IMM; op->offset=-idata;
							if (scan==SCAN_OFS) op->anyoffset=1; }
					else if (scan==SCAN_SYMB && idata=='+') {
						Scanasm(0);                        // Positive constant
						if (scan!=SCAN_ICONST && scan!=SCAN_DCONST && scan!=SCAN_OFS) {
							asmerror="Integer number expected";
							scan=SCAN_ERR; return; };
							op->type=IMM; op->offset=idata;
							if (scan==SCAN_OFS) op->anyoffset=1; }
					else if (scan==SCAN_ICONST || scan==SCAN_DCONST || scan==SCAN_OFS) {
						j=idata;
						if (scan==SCAN_OFS) op->anyoffset=1;
						Scanasm(0);
						if (scan==SCAN_SYMB && idata==':') {
							Scanasm(0);                      // Absolute long address (seg:offset)
							if (scan!=SCAN_ICONST && scan!=SCAN_DCONST && scan!=SCAN_OFS) {
								asmerror="Integer address expected";
								scan=SCAN_ERR; return; };
								op->type=JMF; op->offset=idata; op->segment=j;
								if (scan==SCAN_OFS) op->anyoffset=1; }
						else {
							op->type=IMM; op->offset=j;      // Constant without sign
							return;                          // Next token already scanned
						}; }
					else if (scan==SCAN_FCONST) {
						asmerror="Floating-point numbers are not allowed in command";
						scan=SCAN_ERR; return; }
					// Segment register or address.
					else if (scan==SCAN_SEG || scan==SCAN_OPSIZE ||
						(scan==SCAN_SYMB && idata=='[')
						) {                                  // Segment register or address
							bracket=0;
							if (scan==SCAN_SEG) {
								j=idata; Scanasm(0);
								if (scan!=SCAN_SYMB || idata!=':') {
									op->type=SGM; op->index=j;     // Segment register as operand
									return; };                     // Next token already scanned
									op->segment=j; Scanasm(0); };
									// Scan 32-bit address. This parser does not support 16-bit addresses.
									// First of all, get size of operand (optional), segment register (optional)
									// and opening bracket (required).
									while (1) {
										if (scan==SCAN_SYMB && idata=='[') {
											if (bracket) {                 // Bracket
												asmerror="Only one opening bracket allowed";
												scan=SCAN_ERR; return; };
												bracket=1; }
										else if (scan==SCAN_OPSIZE) {
											if (op->size!=0) {             // Size of operand
												asmerror="Duplicated size modifier";
												scan=SCAN_ERR; return; };
												op->size=idata; }
										else if (scan==SCAN_SEG) {
											if (op->segment!=SEG_UNDEF) {  // Segment register
												asmerror="Duplicated segment register";
												scan=SCAN_ERR; return; };
												op->segment=idata; Scanasm(0);
												if (scan!=SCAN_SYMB || idata!=':') {
													asmerror="Semicolon expected";
													scan=SCAN_ERR; return;
												}; }
										else if (scan == SCAN_LABEL)
										{
											if (scan == SCAN_LABEL)
											{
												op->type = MRG;
												op->label = now_label;
												Scanasm(0);
												//return;
												break;
											}
										}
										else if (scan==SCAN_ERR)
											return;
										else break;                      // None of expected address elements
										Scanasm(0); };
										if (bracket==0) {
											asmerror="Address expression requires brackets";
											scan=SCAN_ERR; return; };
											// Assembling a 32-bit address may be a kind of nigthmare, due to a large
											// number of allowed forms. Parser collects immediate offset in op->offset
											// and count for each register in array r[]. Then it decides whether this
											// combination is valid and determines scale, index and base. Assemble()
											// will use these numbers to select address form (with or without SIB byte,
											// 8- or 32-bit offset, use segment prefix or not). As a useful side effect
											// of this technique, one may specify, for example, [EAX*5] which will
											// correctly assemble to [EAX*4+EAX].
											for (i=0; i<=8; i++) r[i]=0;
											sign='+';                          // Default sign for the first operand
											xlataddr=0;
											while (1) {                        // Get SIB and offset
												if (scan==SCAN_SYMB && (idata=='+' || idata=='-')) {
													sign=idata; Scanasm(0); };
													if (scan==SCAN_ERR) return;
													if (sign=='?') {
														asmerror="Syntax error"; scan=SCAN_ERR; return; };
														// Register AL appears as part of operand of (seldom used) command XLAT.
														if (scan==SCAN_REG8 && idata==REG_EAX) {
															if (sign=='-') {
																asmerror="Unable to subtract register"; scan=SCAN_ERR; return; };
																if (xlataddr!=0) {
																	asmerror="Too many registers"; scan=SCAN_ERR; return; };
																	xlataddr=1;
																	Scanasm(0); }
														else if (scan==SCAN_REG16) {
															asmerror="Sorry, 16-bit addressing is not supported";
															scan=SCAN_ERR; return; }
														else if (scan==SCAN_REG32) {
															if (sign=='-') {
																asmerror="Unable to subtract register"; scan=SCAN_ERR; return; };
																reg=idata; Scanasm(0);
																if (scan==SCAN_SYMB && idata=='*') {
																	Scanasm(0);                  // Try index*scale
																	if (scan==SCAN_ERR) return;
																	if (scan==SCAN_OFS) {
																		asmerror="Undefined scale is not allowed"; scan=SCAN_ERR; return; };
																		if (scan!=SCAN_ICONST && scan!=SCAN_DCONST) {
																			asmerror="Syntax error"; scan=SCAN_ERR; return; };
																			if (idata==6 || idata==7 || idata>9) {
																				asmerror="Invalid scale"; scan=SCAN_ERR; return; };
																				r[reg]+=idata;
																				Scanasm(0); }
																else r[reg]++; }               // Simple register
														else if (scan==SCAN_REG64) {                              ////////////////////////////////////////////////////////////////////////// 64
															if (sign=='-') {
																asmerror="Unable to subtract register"; scan=SCAN_ERR; return; };
																reg=idata; Scanasm(0);
																if (scan==SCAN_SYMB && idata=='*') {
																	Scanasm(0);                  // Try index*scale
																	if (scan==SCAN_ERR) return;
																	if (scan==SCAN_OFS) {
																		asmerror="Undefined scale is not allowed"; scan=SCAN_ERR; return; };
																		if (scan!=SCAN_ICONST && scan!=SCAN_DCONST) {
																			asmerror="Syntax error"; scan=SCAN_ERR; return; };
																			if (idata==6 || idata==7 || idata>9) {
																				asmerror="Invalid scale"; scan=SCAN_ERR; return; };
																				r[reg]+=idata;
																				Scanasm(0); }
																else r[reg]++; }               // Simple register
														else if (scan==SCAN_LOCAL) {
															r[REG_EBP]++;
															op->offset-=idata*4;
															Scanasm(0); }
														else if (scan==SCAN_ARG) {
															r[REG_EBP]++;
															op->offset+=(idata+1)*4;
															Scanasm(0); }
														else if (scan==SCAN_ICONST || scan==SCAN_DCONST) {
															offset=idata; Scanasm(0);
															if (scan==SCAN_SYMB && idata=='*') {
																Scanasm(0);                  // Try scale*index
																if (scan==SCAN_ERR) return;
																if (sign=='-') {
																	asmerror="Unable to subtract register"; scan=SCAN_ERR; return; };
																	if (scan==SCAN_REG16) {
																		asmerror="Sorry, 16-bit addressing is not supported";
																		scan=SCAN_ERR; return; };
																		if (scan!=SCAN_REG32) {
																			asmerror="Syntax error"; scan=SCAN_ERR; return; };
																			if (offset==6 || offset==7 || offset>9) {
																				asmerror="Invalid scale"; scan=SCAN_ERR; return; };
																				r[idata]+=offset;
																				Scanasm(0); }
															else {
																if (sign=='-') op->offset-=offset;
																else op->offset+=offset;
															}; }
														else if (scan==SCAN_OFS) {
															Scanasm(0);
															if (scan==SCAN_SYMB && idata=='*') {
																asmerror="Undefined scale is not allowed"; scan=SCAN_ERR; return; }
															else {
																op->anyoffset=1;
															}; }
														else break;                      // None of expected address elements
														if (scan==SCAN_SYMB && idata==']') break;
														sign='?';
											};
											if (scan==SCAN_ERR) return;
											if (scan!=SCAN_SYMB || idata!=']') {
												asmerror="Syntax error";
												scan=SCAN_ERR; return; };
												// Process XLAT address separately.
												if (xlataddr!=0) {                 // XLAT address in form [EBX+AX]
													for (i=0; i<=8; i++) {           // Check which registers used
														if (i==REG_EBX) continue;
														if (r[i]!=0) break; };
														if (i<=8 || r[REG_EBX]!=1 || op->offset!=0 || op->anyoffset!=0) {
															asmerror="Invalid address"; scan=SCAN_ERR; return; };
															op->type=MXL; }
												// Determine scale, index and base.
												else {
													j=0;                             // Number of used registers
													for (i=0; i<=8; i++) {
														if (r[i]==0)
															continue;                    // Unused register
														if (r[i]==3 || r[i]==5 || r[i]==9) {
															if (op->index>=0 || op->base>=0) {
																if (j==0) asmerror="Invalid scale";
																else asmerror="Too many registers";
																scan=SCAN_ERR; return; };
																op->index=op->base=i;
																op->scale=r[i]-1; }
														else if (r[i]==2 || r[i]==4 || r[i]==8) {
															if (op->index>=0) {
																if (j<=1) asmerror="Only one register may be scaled";
																else asmerror="Too many registers";
																scan=SCAN_ERR; return; };
																op->index=i; op->scale=r[i]; }
														else if (r[i]==1) {
															if (op->base<0)
																op->base=i;
															else if (op->index<0) {
																op->index=i; op->scale=1; }
															else {
																asmerror="Too many registers";
																scan=SCAN_ERR; return;
															}; }
														else {
															asmerror="Invalid scale"; scan=SCAN_ERR; return; };
															j++;
													};
													op->type=MRG;
												}; }
					else {
						asmerror="Unrecognized operand"; scan=SCAN_ERR; return; };
						// In general, address modifier is allowed only with address expression which
						// is a constant, a far address or a memory expression. More precise check
						// will be done later in Assemble().
						if (op->jmpmode!=0 && op->type!=IMM && op->type!=JMF && op->type!=MRG) {
							asmerror="Jump address modifier is not allowed";
							scan=SCAN_ERR; return; };
							Scanasm(0);                          // Fetch next token from input line
};

const GPReg * Assembl::get_reg(int reg,int size)
{
	switch (size)
	{
	case 1:
		{
			switch (reg)
			{
			case REG_EAX:
				return &al;
				break;
			case REG_EBX:
				return &bl;
				break;
			case REG_ECX:
				return &cl;
				break;
			case REG_EDX:
				return &dl;
				break;
			case REG_ESP:
				return &ah;
				break;
			case REG_EBP:
				return &ch;
				break;
			case REG_ESI:
				return &dh;
				break;
			case REG_EDI:
				return &bh;
				break;
			}
		}
		break;
	case 2:
		switch (reg)
		{
		case REG_EAX:
			return &ax;
			break;
		case REG_EBX:
			return &bx;
			break;
		case REG_ECX:
			return &cx;
			break;
		case REG_EDX:
			return &dx;
			break;
		case REG_ESP:
			return &sp;
			break;
		case REG_EBP:
			return &bp;
			break;
		case REG_ESI:
			return &si;
			break;
		case REG_EDI:
			return &di;
			break;
		}
		break;
	case 4:
		{
			switch (reg)
			{
			case REG_EAX:
				return &eax;
				break;
			case REG_EBX:
				return &ebx;
				break;
			case REG_ECX:
				return &ecx;
				break;
			case REG_EDX:
				return &edx;
				break;
			case REG_ESP:
				return &esp;
				break;
			case REG_EBP:
				return &ebp;
				break;
			case REG_ESI:
				return &esi;
				break;
			case REG_EDI:
				return &edi;
				break;
			}
		}
		break;
#ifdef PROTECT_X64
	case 8:
		{
			switch (reg)
			{
			case REG_EAX:
				return &rax;
				break;
			case REG_EBX:
				return &rbx;
				break;
			case REG_ECX:
				return &rcx;
				break;
			case REG_EDX:
				return &rdx;
				break;
			case REG_ESP:
				return &rsp;
				break;
			case REG_EBP:
				return &rbp;
				break;
			case REG_ESI:
				return &rsi;
				break;
			case REG_EDI:
				return &rdi;
				break;
			case REG_EAX+8:
				return &r8;
				break;
			case REG_ECX+8:
				return &r9;
				break;
			case REG_EDX+8:
				return &r10;
				break;
			case REG_EBX+8:
				return &r11;
				break;
			case REG_ESP+8:
				return &r12;
				break;
			case REG_EBP+8:
				return &r13;
				break;
			case REG_ESI+8:
				return &r14;
				break;
			case REG_EDI+8:
				return &r15;
				break;
			}

		}
#endif
	}
	switch (reg)
	{
	case REG_EAX:
		return &eax;
		break;
	case REG_EBX:
		return &ebx;
		break;
	case REG_ECX:
		return &ecx;
		break;
	case REG_EDX:
		return &edx;
		break;
	case REG_ESP:
		return &esp;
		break;
	case REG_EBP:
		return &ebp;
		break;
	case REG_ESI:
		return &esi;
		break;
	case REG_EDI:
		return &edi;
		break;
	}
	return NULL;
}

#define ScaleState(Scale) (Scale>4?Scale/2-1:Scale/2)

const Operand Assembl::get_operand(asmoperand *op)
{
	if (op->mode == SCAN_FPU && op->type == SCAN_OPSIZE)
	{
		X87Reg x87reg = st(op->index);
		return x87reg;
	}

	switch (op->type)
	{
	case IMM:
		{
			const Imm imm = op->offset;
			return imm;
		}
		break;
	case REG:
		{
			GPReg reg = *get_reg(op->index,op->size);
			return reg;
		}
		break;
	case MRG:
		{
		  //  word_ptr(eax,0,SEGMENT_FS);
			Mem mem;
			const GPReg *base = NULL;
			const GPReg *index = NULL;
			if (op->base != -1)
			{
				base = get_reg(op->base,op->size);
			}
			if (op->index != -1)
			{
				index = get_reg(op->index,op->size);
			}
			if (op->label && index)
			{
				switch (op->size)
				{
				case 0:
					mem = ptr(*op->label,*index,ScaleState(op->scale),op->offset);
					break;
				case 1:
					mem = byte_ptr(*op->label,*index,ScaleState(op->scale),op->offset);
					break;
				case 2:
					mem = word_ptr(*op->label,*index,ScaleState(op->scale),op->offset);
					break;
				case 4:
					mem = dword_ptr(*op->label,*index,ScaleState(op->scale),op->offset);
					break;
				case 8:
					mem = qword_ptr(*op->label,*index,ScaleState(op->scale),op->offset);
					break;
				}
				return mem;
			}
			else if (op->label)
			{
				switch (op->size)
				{
				case 0:
					mem = ptr (*op->label,op->offset);
				case 1:
					mem = byte_ptr(*op->label,op->offset);
					break;
				case 2:
					mem = word_ptr(*op->label,op->offset);
					break;
				case 4:
					mem = dword_ptr(*op->label,op->offset);
					break;
				case 8:
					mem = qword_ptr(*op->label,op->offset);
					break;
				}
				return mem;
			}
			else if (base && index)
			{
				if (op->segment != -1) // 有段
				{
					switch (op->size)
					{
					case 0:
				//		mem = ptr(*base,*index,ScaleState(op->scale),op->offset,op->segment);
						break;
					case 1:
						mem = byte_ptr(*base,*index,ScaleState(op->scale),op->offset,op->segment);
						break;
					case 2:
						mem = word_ptr(*base,*index,ScaleState(op->scale),op->offset,op->segment);
						break;
					case 4:
						mem = dword_ptr(*base,*index,ScaleState(op->scale),op->offset,op->segment);
						break;
					case 8:
						mem = qword_ptr(*base,*index,ScaleState(op->scale),op->offset,op->segment);
						break;
					}
					return mem;
				}
				else
				{
					switch (op->size)
					{
					case 0:
						mem = ptr(*base,*index,ScaleState(op->scale),op->offset);
						break;
					case 1:
						mem = byte_ptr(*base,*index,ScaleState(op->scale),op->offset);
						break;
					case 2:
						mem = word_ptr(*base,*index,ScaleState(op->scale),op->offset);
						break;
					case 4:
						mem = dword_ptr(*base,*index,ScaleState(op->scale),op->offset);
						break;
					case 8:
						mem = qword_ptr(*base,*index,ScaleState(op->scale),op->offset);
						break;
					}
					return mem;
				}

			}
			else if (base)
			{
				if (op->segment != -1)
				{
					switch (op->size)
					{
					case 0:
				//		mem = ptr(*base,op->offset,op->segment);
						break;
					case 1:
						mem = byte_ptr(*base,op->offset,op->segment);
						break;
					case 2:
						mem = word_ptr(*base,op->offset,op->segment);
						break;
					case 4:
						mem = dword_ptr(*base,op->offset,op->segment);
						break;
					case 8:
						mem = qword_ptr(*base,op->offset,op->segment);
						break;
					}
				}
				else
				{
					switch (op->size)
					{
					case 0:
						mem = ptr(*base,op->offset);
						break;
					case 1:
						mem = byte_ptr(*base,op->offset);
						break;
					case 2:
						mem = word_ptr(*base,op->offset);
						break;
					case 4:
						mem = dword_ptr(*base,op->offset);
						break;
					case 8:
						mem = qword_ptr(*base,op->offset);
						break;
				     }
			//	mem = dword_ptr(*base,op->offset);
				}
				return mem;
			}
			else
			{
				if (op->segment != 0)
				{
					switch (op->size)
					{
					case 0:
						mem = ptr_abs((void *)op->offset,0,op->segment);
						break;
					case 1:
							mem = byte_ptr_abs((void *)op->offset,0,op->segment);
							break;
					case 2:
							mem = word_ptr_abs((void *)op->offset,0,op->segment);
						    break;
					case 4:
						mem = dword_ptr_abs((void *)op->offset,0,op->segment);
						break;
					case 8:
						mem = qword_ptr_abs((void *)op->offset,0,op->segment);
						break;
					}
				}
				else
				{
					switch (op->size)
					{
					case 1:
							mem = byte_ptr_abs((void *)op->offset);
							break;
					case 2:
							mem = word_ptr_abs((void *)op->offset);
							break;
					case 4:
						mem = dword_ptr_abs((void *)op->offset);
						break;
					case 8:
						mem = qword_ptr_abs((void *)op->offset);
						break;
					}
				}
				//mem = dword_ptr_abs((void*)op->offset,0,SEGMENT_CS);
				return mem;
			}
		}
		break;
	case LABEL:
		{
			Label label = *op->label;
			return label;
		}
		break;
	case SGM:
		{
			switch (op->index)
			{
			case SEG_CS:
				return cs;
			case SEG_DS:
				return ds;
			case SEG_ES:
				return es;
			case SEG_SS:
				return ss;
			case SEG_FS:
				return fs;
			case SEG_GS:
				return gs;
			default:
				return ds;
			}
		}
		break;
	}
    GPReg reg;
    return reg;
}



unsigned char * Assembl::get_code()
{
	return a.getCode();
}

int Assembl::get_code_size()
{
	return a.getCodeSize();
}
int Assembl::Assemble(char *cmd,ulong ip,asmmodel *model,char *error)
{
	Assembler a;
	FileLogger logger(stderr);
	a.setLogger(&logger);

	asmerror = NULL;
	//	int oldsize = a.getCodeSize();

	///////////////////注释//////
	char *note = strchr(cmd,';');
	if (note)
		*note = '\0';
	//////////////////判断是否是标签///


	asmcmd = cmd;

	Scanasm(SA_NAME);

	if (scan == SCAN_LABEL_BIND)
	{
		return a.getCodeSize();
	}
	char name[20];
	strcpy(name,sdata);  //sdata就是指令前缀 比如mov
	strupr(sdata);
	//for (int i = 0;i<575;i++)
	//{
	//	printf("%d:%s\r\n",i,instruction_table[i]);
	//	if (strcmp(instruction_table[i],name) == 0)
	//	{
	//		a._emitInstruction(i);
	//	}
	//}
	char *asmend = asmcmd;
	Scanasm(0);
	if (scan == SCAN_LABEL_BIND)
	{
		return a.getCodeSize();
	}
	asmoperand aop[3],*op;
	for (int i=0; i<3; i++) {
		aop[i].type=NNN;                   // No operand
		aop[i].size=0;                     // Undefined size
		aop[i].index=-1;                   // No index
		aop[i].scale=0;                    // No scale
		aop[i].base=-1;                    // No base
		aop[i].offset=0;                   // No offset
		aop[i].anyoffset=0;                // No offset
		aop[i].segment=SEG_UNDEF;          // No segment
		aop[i].jmpmode=0;
		aop[i].label = NULL;
		aop[i].mode = 0;
	};               // No jump size modifier
	//	printf("%d",REG_EBX);
	aop[0].mode = scan;
	Parseasmoperand(aop + 0);
	if (scan == SCAN_LABEL_BIND)
	{
		return a.getCodeSize();
	}

	if (scan==SCAN_SYMB && idata==',') {
		Scanasm(0);
		aop[1].mode = scan;
		if (scan == SCAN_LABEL_BIND)
		{
			return a.getCodeSize();
		}
		Parseasmoperand(aop+1);

		if (scan==SCAN_SYMB && idata==',') {
			Scanasm(0);
			aop[2].mode = scan;
			if (scan == SCAN_LABEL_BIND)
			{
				return a.getCodeSize();
			}
			Parseasmoperand(aop+2);
		};
	};

	if (asmerror)
	{
		strcpy(error,asmerror);
		return -1;
	}

	Mem *mem;
	Imm *imm;
	GPReg *reg;
	const Operand *o1 = NULL;
	const Operand *o2 = NULL;
	const Operand *o3 = NULL;
	//o1 = &get_operand(aop + 0);
	//o2 = &get_operand(aop + 1);
	//o3 = &get_operand(aop + 2);
    Operand oo1 = get_operand(aop + 0);
    o1 = &oo1;
	Operand oo2 = get_operand(aop + 1);
	o2 = &oo2;
	Operand oo3 = get_operand(aop + 2);
    o3 = &oo3;

    const char * n = name;
	for (int i = 0;i<575;i++)
	{
		//		printf("%d:%s\r\n",i,instruction_table[i]);
        if (strcmp(instruction_table[i],name) == 0)
		{
			if (aop[0].type == 0)
				a._emitInstruction(i);
			else if (aop[1].type == 0)
				a._emitInstruction(i,o1);
			else if (aop[2].type == 0)
				a._emitInstruction(i,o1,o2);
			else
				a._emitInstruction(i,o1,o2,o2);
			memcpy(model->code,a.getCode(),a.getCodeSize());
			return a.getCodeSize();
		}
	}
	sprintf(error,"错误的汇编指令,没有找到:%s\r\n",name);
	return -1;
}

void Assembl::reloc(unsigned long relocaddr)
{
	a.relocCode((void*)a.getCode(),relocaddr);
}

int Assembl::Assemble(char *cmd)
{
	FileLogger logger(stderr);
	a.setLogger(&logger);

	asmerror = NULL;
//	int oldsize = a.getCodeSize();

	///////////////////注释//////
	char *note = strchr(cmd,';');
	if (note)
		*note = '\0';
    //////////////////判断是否是标签///


	asmcmd = cmd;

    Scanasm(SA_NAME);

	if (scan == SCAN_LABEL_BIND)
	{
		return a.getCodeSize();
	}
	char name[20];
	strcpy(name,strupr(sdata));  //sdata就是指令前缀 比如mov

	//for (int i = 0;i<575;i++)
	//{
	//	printf("%d:%s\r\n",i,instruction_table[i]);
	//	if (strcmp(instruction_table[i],name) == 0)
	//	{
	//		a._emitInstruction(i);
	//	}
	//}
	char *asmend = asmcmd;
	Scanasm(0);
	if (scan == SCAN_LABEL_BIND)
	{
		return a.getCodeSize();
	}
	asmoperand aop[3],*op;
	for (int i=0; i<3; i++) {
		aop[i].type=NNN;                   // No operand
		aop[i].size=0;                     // Undefined size
		aop[i].index=-1;                   // No index
		aop[i].scale=0;                    // No scale
		aop[i].base=-1;                    // No base
		aop[i].offset=0;                   // No offset
		aop[i].anyoffset=0;                // No offset
		aop[i].segment=SEG_UNDEF;          // No segment
		aop[i].jmpmode=0;
		aop[i].label = NULL;
		aop[i].mode = 0;
	};               // No jump size modifier
//	printf("%d",REG_EBX);
	aop[0].mode = scan;
	Parseasmoperand(aop + 0);
	if (scan == SCAN_LABEL_BIND)
	{
		return a.getCodeSize();
	}

	if (scan==SCAN_SYMB && idata==',') {
		Scanasm(0);
		aop[1].mode = scan;
		if (scan == SCAN_LABEL_BIND)
		{
			return a.getCodeSize();
		}
		Parseasmoperand(aop+1);

		if (scan==SCAN_SYMB && idata==',') {
			Scanasm(0);
			aop[2].mode = scan;
			if (scan == SCAN_LABEL_BIND)
			{
				return a.getCodeSize();
			}
			Parseasmoperand(aop+2);
		};
	};

	if (asmerror)
	{
		printf(asmerror);
		return -1;
	}

	Mem *mem;
	Imm *imm;
	GPReg *reg;
	const Operand *o1 = NULL;
	const Operand *o2 = NULL;
	const Operand *o3 = NULL;
	//o1 = &get_operand(aop + 0);
	//o2 = &get_operand(aop + 1);
	//o3 = &get_operand(aop + 2);
    Operand oo1 = get_operand(aop + 0);
    o1 = &oo1;
	Operand oo2 = get_operand(aop + 1);
	o2 = &oo2;
	Operand oo3 = get_operand(aop + 2);
    o3 = &oo3;
	for (int i = 0;i<575;i++)
	{
//		printf("%d:%s\r\n",i,instruction_table[i]);
		if (strcmp(instruction_table[i],name) == 0)
		{
			if (aop[0].type == 0)
				a._emitInstruction(i);
			else if (aop[1].type == 0)
				a._emitInstruction(i,o1);
		    else if (aop[2].type == 0)
			    a._emitInstruction(i,o1,o2);
		    else
			    a._emitInstruction(i,o1,o2,o2);
			return a.getCodeSize();
		}
	}
	printf("错误的汇编指令,没有找到:%s\r\n",name);
	return -1;
}
