#include "opcode_table.h"
const unsigned int instruction_table_count = 575;
const char * instruction_table[575] =
{
  "ADC",           // X86/X64
  "ADD",           // X86/X64
  "ADDPD",         // SSE2
  "ADDPS",         // SSE
  "ADDSD",         // SSE2
  "ADDSS",         // SSE
  "ADDSUBPD",      // SSE3
  "ADDSUBPS",      // SSE3
  "AMD_PREFETCH",
  "AMD_PREFETCHW",
  "AND",           // X86/X64
  "ANDNPD",        // SSE2
  "ANDNPS",        // SSE
  "ANDPD",         // SSE2
  "ANDPS",         // SSE
  "BLENDPD",       // SSE4.1
  "BLENDPS",       // SSE4.1
  "BLENDVPD",      // SSE4.1
  "BLENDVPS",      // SSE4.1
  "BSF",           // X86/X64
  "BSR",           // X86/X64
  "BSWAP",         // X86/X64 (i486)
  "BT",            // X86/X64
  "BTC",           // X86/X64
  "BTR",           // X86/X64
  "BTS",           // X86/X64
  "CALL",          // X86/X64
  "CBW",           // X86/X64
  "CDQE",          // X64 only
  "CLC",           // X86/X64
  "CLD",           // X86/X64
  "CLFLUSH",       // SSE2
  "CMC",           // X86/X64
  "CMOVA",         //X86/X64 (cmovcc) (i586)
  "CMOVAE",        // X86/X64 (cmovcc) (i586)
  "CMOVB",         // X86/X64 (cmovcc) (i586)
  "CMOVBE",        // X86/X64 (cmovcc) (i586)
  "CMOVC",         // X86/X64 (cmovcc) (i586)
  "CMOVE",         // X86/X64 (cmovcc) (i586)
  "CMOVG",         // X86/X64 (cmovcc) (i586)
  "CMOVGE",        // X86/X64 (cmovcc) (i586)
  "CMOVL",         // X86/X64 (cmovcc) (i586)
  "CMOVLE",        // X86/X64 (cmovcc) (i586)
  "CMOVNA",        // X86/X64 (cmovcc) (i586)
  "CMOVNAE",       // X86/X64 (cmovcc) (i586)
  "CMOVNB",        // X86/X64 (cmovcc) (i586)
  "CMOVNBE",       // X86/X64 (cmovcc) (i586)
  "CMOVNC",        // X86/X64 (cmovcc) (i586)
  "CMOVNE",        // X86/X64 (cmovcc) (i586)
  "CMOVNG",        // X86/X64 (cmovcc) (i586)
  "CMOVNGE",       // X86/X64 (cmovcc) (i586)
  "CMOVNL",        // X86/X64 (cmovcc) (i586)
  "CMOVNLE",       // X86/X64 (cmovcc) (i586)
  "CMOVNO",        // X86/X64 (cmovcc) (i586)
  "CMOVNP",        // X86/X64 (cmovcc) (i586)
  "CMOVNS",        // X86/X64 (cmovcc) (i586)
  "CMOVNZ",        // X86/X64 (cmovcc) (i586)
  "CMOVO",         // X86/X64 (cmovcc) (i586)
  "CMOVP",         // X86/X64 (cmovcc) (i586)
  "CMOVPE",        // X86/X64 (cmovcc) (i586)
  "CMOVPO",        // X86/X64 (cmovcc) (i586)
  "CMOVS",         // X86/X64 (cmovcc) (i586)
  "CMOVZ",         // X86/X64 (cmovcc) (i586)

  "CMP",           // X86/X64
  "CMPPD",         // SSE2
  "CMPPS",         // SSE
  "CMPSD",         // SSE2
  "CMPSS",         // SSE
  "CMPXCHG",       // X86/X64 (i486)
  "CMPXCHG16B",    // X64 only
  "CMPXCHG8B",     // X86/X64 (i586)
  "COMISD",        // SSE2
  "COMISS",        // SSE
  "CPUID",         // X86/X64 (i486)
  "CRC32",         // SSE4.2
  "CVTDQ2PD",      // SSE2
  "CVTDQ2PS",      // SSE2
  "CVTPD2DQ",      // SSE2
  "CVTPD2PI",      // SSE2
  "CVTPD2PS",      // SSE2
  "CVTPI2PD",      // SSE2
  "CVTPI2PS",      // SSE
  "CVTPS2DQ",      // SSE2
  "CVTPS2PD",      // SSE2
  "CVTPS2PI",      // SSE
  "CVTSD2SI",      // SSE2
  "CVTSD2SS",      // SSE2
  "CVTSI2SD",      // SSE2
  "CVTSI2SS",      // SSE
  "CVTSS2SD",      // SSE2
  "CVTSS2SI",      // SSE
  "CVTTPD2DQ",     // SSE2
  "CVTTPD2PI",     // SSE2
  "CVTTPS2DQ",     // SSE2
  "CVTTPS2PI",     // SSE
  "CVTTSD2SI",     // SSE2
  "CVTTSS2SI",     // SSE
  "CWDE",          // X86/X64
  "DAA",           // X86 only
  "DAS",           // X86 only
  "DEC",           // X86/X64
  "DIV",           // X86/X64
  "DIVPD",         // SSE2
  "DIVPS",         // SSE
  "DIVSD",         // SSE2
  "DIVSS",         // SSE
  "DPPD",          // SSE4.1
  "DPPS",          // SSE4.1
  "EMMS",          // MMX
  "ENTER",         // X86/X64
  "EXTRACTPS",     // SSE4.1
  "F2XM1",         // X87
  "FABS",          // X87
  "FADD",          // X87
  "FADDP",         // X87
  "FBLD",          // X87
  "FBSTP",         // X87
  "FCHS",          // X87
  "FCLEX",         // X87
  "FCMOVB",        // X87
  "FCMOVBE",       // X87
  "FCMOVE",        // X87
  "FCMOVNB",       // X87
  "FCMOVNBE",      // X87
  "FCMOVNE",       // X87
  "FCMOVNU",       // X87
  "FCMOVU",        // X87
  "FCOM",          // X87
  "FCOMI",         // X87
  "FCOMIP",        // X87
  "FCOMP",         // X87
  "FCOMPP",        // X87
  "FCOS",          // X87
  "FDECSTP",       // X87
  "FDIV",          // X87
  "FDIVP",         // X87
  "FDIVR",         // X87
  "FDIVRP",        // X87
  "FEMMS",         // 3dNow!
  "FFREE",         // X87
  "FIADD",         // X87
  "FICOM",         // X87
  "FICOMP",        // X87
  "FIDIV",         // X87
  "FIDIVR",        // X87
  "FILD",          // X87
  "FIMUL",         // X87
  "FINCSTP",       // X87
  "FINIT",         // X87
  "FIST",          // X87
  "FISTP",         // X87
  "FISTTP",        // SSE3
  "FISUB",         // X87
  "FISUBR",        // X87
  "FLD",           // X87
  "FLD1",          // X87
  "FLDCW",         // X87
  "FLDENV",        // X87
  "FLDL2E",        // X87
  "FLDL2T",        // X87
  "FLDLG2",        // X87
  "FLDLN2",        // X87
  "FLDPI",         // X87
  "FLDZ",          // X87
  "FMUL",          // X87
  "FMULP",         // X87
  "FNCLEX",        // X87
  "FNINIT",        // X87
  "FNOP",          // X87
  "FNSAVE",        // X87
  "FNSTCW",        // X87
  "FNSTENV",       // X87
  "FNSTSW",        // X87
  "FPATAN",        // X87
  "FPREM",         // X87
  "FPREM1",        // X87
  "FPTAN",         // X87
  "FRNDINT",       // X87
  "FRSTOR",        // X87
  "FSAVE",         // X87
  "FSCALE",        // X87
  "FSIN",          // X87
  "FSINCOS",       // X87
  "FSQRT",         // X87
  "FST",           // X87
  "FSTCW",         // X87
  "FSTENV",        // X87
  "FSTP",          // X87
  "FSTSW",         // X87
  "FSUB",          // X87
  "FSUBP",         // X87
  "FSUBR",         // X87
  "FSUBRP",        // X87
  "FTST",          // X87
  "FUCOM",         // X87
  "FUCOMI",        // X87
  "FUCOMIP",       // X87
  "FUCOMP",        // X87
  "FUCOMPP",       // X87
  "FWAIT",         // X87
  "FXAM",          // X87
  "FXCH",          // X87
  "FXRSTOR",       // X87
  "FXSAVE",        // X87
  "FXTRACT",       // X87
  "FYL2X",         // X87
  "FYL2XP1",       // X87
  "HADDPD",        // SSE3
  "HADDPS",        // SSE3
  "HSUBPD",        // SSE3
  "HSUBPS",        // SSE3
  "IDIV",          // X86/X64
  "IMUL",          // X86/X64
  "INC",           // X86/X64
  "INT3",          // X86/X64
  "JA",             // Begin (jcc)
  "JAE",           // X86/X64 (jcc)
  "JB",            // X86/X64 (jcc)
  "JBE",           // X86/X64 (jcc)
  "JC",            // X86/X64 (jcc)
  "JE",            // X86/X64 (jcc)
  "JG",            // X86/X64 (jcc)
  "JGE",           // X86/X64 (jcc)
  "JL",            // X86/X64 (jcc)
  "JLE",           // X86/X64 (jcc)
  "JNA",           // X86/X64 (jcc)
  "JNAE",          // X86/X64 (jcc)
  "JNB",           // X86/X64 (jcc)
  "JNBE",          // X86/X64 (jcc)
  "JNC",           // X86/X64 (jcc)
  "JNE",           // X86/X64 (jcc)
  "JNG",           // X86/X64 (jcc)
  "JNGE",          // X86/X64 (jcc)
  "JNL",           // X86/X64 (jcc)
  "JNLE",          // X86/X64 (jcc)
  "JNO",           // X86/X64 (jcc)
  "JNP",           // X86/X64 (jcc)
  "JNS",           // X86/X64 (jcc)
  "JNZ",           // X86/X64 (jcc)
  "JO",            // X86/X64 (jcc)
  "JP",            // X86/X64 (jcc)
  "JPE",           // X86/X64 (jcc)
  "JPO",           // X86/X64 (jcc)
  "JS",            // X86/X64 (jcc)
  "JZ",            // X86/X64 (jcc)
  "JMP",           // X86/X64 (jmp)
  "LDDQU",         // SSE3
  "LDMXCSR",       // SSE
  "LAHF",          // X86/X64 (CPUID NEEDED)
  "LEA",           // X86/X64
  "LEAVE",         // X86/X64
  "LFENCE",        // SSE2
  "MASKMOVDQU",    // SSE2
  "MASKMOVQ",      // MMX-Ext
  "MAXPD",         // SSE2
  "MAXPS",         // SSE
  "MAXSD",         // SSE2
  "MAXSS",         // SSE
  "MFENCE",        // SSE2
  "MINPD",         // SSE2
  "MINPS",         // SSE
  "MINSD",         // SSE2
  "MINSS",         // SSE
  "MONITOR",       // SSE3
  "MOV",           // X86/X64
  "MOVAPD",        // SSE2
  "MOVAPS",        // SSE
  "MOVBE",         // SSE3 - Intel-Atom
  "MOVD",          // MMX/SSE2
  "MOVDDUP",       // SSE3
  "MOVDQ2Q",       // SSE2
  "MOVDQA",        // SSE2
  "MOVDQU",        // SSE2
  "MOVHLPS",       // SSE
  "MOVHPD",        // SSE2
  "MOVHPS",        // SSE
  "MOVLHPS",       // SSE
  "MOVLPD",        // SSE2
  "MOVLPS",        // SSE
  "MOVMSKPD",      // SSE2
  "MOVMSKPS",      // SSE2
  "MOVNTDQ",       // SSE2
  "MOVNTDQA",      // SSE4.1
  "MOVNTI",        // SSE2
  "MOVNTPD",       // SSE2
  "MOVNTPS",       // SSE
  "MOVNTQ",        // MMX-Ext
  "MOVQ",          // MMX/SSE/SSE2
  "MOVQ2DQ",       // SSE2
  "MOVSD",         // SSE2
  "MOVSHDUP",      // SSE3
  "MOVSLDUP",      // SSE3
  "MOVSS",         // SSE
  "MOVSX",         // X86/X64
  "MOVSXD",        // X86/X64
  "MOVUPD",        // SSE2
  "MOVUPS",        // SSE
  "MOVZX",         // X86/X64
  "MOV_PTR",       // X86/X64
  "MPSADBW",       // SSE4.1
  "MUL",           // X86/X64
  "MULPD",         // SSE2
  "MULPS",         // SSE
  "MULSD",         // SSE2
  "MULSS",         // SSE
  "MWAIT",         // SSE3
  "NEG",           // X86/X64
  "NOP",           // X86/X64
  "NOT",           // X86/X64
  "OR",            // X86/X64
  "ORPD",          // SSE2
  "ORPS",          // SSE
  "PABSB",         // SSSE3
  "PABSD",         // SSSE3
  "PABSW",         // SSSE3
  "PACKSSDW",      // MMX/SSE2
  "PACKSSWB",      // MMX/SSE2
  "PACKUSDW",      // SSE4.1
  "PACKUSWB",      // MMX/SSE2
  "PADDB",         // MMX/SSE2
  "PADDD",         // MMX/SSE2
  "PADDQ",         // SSE2
  "PADDSB",        // MMX/SSE2
  "PADDSW",        // MMX/SSE2
  "PADDUSB",       // MMX/SSE2
  "PADDUSW",       // MMX/SSE2
  "PADDW",         // MMX/SSE2
  "PALIGNR",       // SSSE3
  "PAND",          // MMX/SSE2
  "PANDN",         // MMX/SSE2
  "PAUSE",         // SSE2.
  "PAVGB",         // MMX-Ext
  "PAVGW",         // MMX-Ext
  "PBLENDVB",      // SSE4.1
  "PBLENDW",       // SSE4.1
  "PCMPEQB",       // MMX/SSE2
  "PCMPEQD",       // MMX/SSE2
  "PCMPEQQ",       // SSE4.1
  "PCMPEQW",       // MMX/SSE2    
  "PCMPESTRI",     // SSE4.2
  "PCMPESTRM",     // SSE4.2
  "PCMPGTB",       // MMX/SSE2
  "PCMPGTD",       // MMX/SSE2
  "PCMPGTQ",       // SSE4.2
  "PCMPGTW",       // MMX/SSE2
  "PCMPISTRI",     // SSE4.2
  "PCMPISTRM",     // SSE4.2
  "PEXTRB",        // SSE4.1
  "PEXTRD",        // SSE4.1        
  "PEXTRQ",        // SSE4.1
  "PEXTRW",        // MMX-Ext/SSE2
  "PF2ID",         // 3dNow!
  "PF2IW",         // Enhanced 3dNow!
  "PFACC",         // 3dNow!
  "PFADD",         // 3dNow!
  "PFCMPEQ",       // 3dNow!
  "PFCMPGE",       // 3dNow!
  "PFCMPGT",       // 3dNow!
  "PFMAX",         // 3dNow!
  "PFMIN",         // 3dNow!
  "PFMUL",         // 3dNow!
  "PFNACC",        // Enhanced 3dNow!
  "PFPNACC",       // Enhanced 3dNow!
  "PFRCP",         // 3dNow!
  "PFRCPIT1",      // 3dNow!
  "PFRCPIT2",      // 3dNow!
  "PFRSQIT1",      // 3dNow!
  "PFRSQRT",       // 3dNow!
  "PFSUB",         // 3dNow!
  "PFSUBR",        // 3dNow!
  "PHADDD",        // SSSE3
  "PHADDSW",       // SSSE3
  "PHADDW",        // SSSE3
  "PHMINPOSUW",    // SSE4.1
  "PHSUBD",        // SSSE3
  "PHSUBSW",       // SSSE3
  "PHSUBW",        // SSSE3
  "PI2FD",         // 3dNow!
  "PI2FW",         // Enhanced 3dNow!
  "PINSRB",        // SSE4.1
  "PINSRD",        // SSE4.1
  "PINSRQ",        // SSE4.1
  "PINSRW",        // MMX-Ext
  "PMADDUBSW",     // SSSE3
  "PMADDWD",       // MMX/SSE2
  "PMAXSB",        // SSE4.1
  "PMAXSD",        // SSE4.1
  "PMAXSW",        // MMX-Ext
  "PMAXUB",        // MMX-Ext
  "PMAXUD",        // SSE4.1
  "PMAXUW",        // SSE4.1
  "PMINSB",        // SSE4.1
  "PMINSD",        // SSE4.1
  "PMINSW",        // MMX-Ext
  "PMINUB",        // MMX-Ext
  "PMINUD",        // SSE4.1
  "PMINUW",        // SSE4.1
  "PMOVMSKB",      // MMX-Ext
  "PMOVSXBD",      // SSE4.1
  "PMOVSXBQ",      // SSE4.1
  "PMOVSXBW",      // SSE4.1
  "PMOVSXDQ",      // SSE4.1
  "PMOVSXWD",      // SSE4.1
  "PMOVSXWQ",      // SSE4.1
  "PMOVZXBD",      // SSE4.1
  "PMOVZXBQ",      // SSE4.1
  "PMOVZXBW",      // SSE4.1
  "PMOVZXDQ",      // SSE4.1
  "PMOVZXWD",      // SSE4.1
  "PMOVZXWQ",      // SSE4.1
  "PMULDQ",        // SSE4.1
  "PMULHRSW",      // SSSE3
  "PMULHUW",       // MMX-Ext
  "PMULHW",        // MMX/SSE2
  "PMULLD",        // SSE4.1
  "PMULLW",        // MMX/SSE2
  "PMULUDQ",       // SSE2
  "POP",           // X86/X64
  "POPAD",         // X86 only
  "POPCNT",        // SSE4.2
  "POPFD",         // X86 only
  "POPFQ",         // X64 only
  "POR",           // MMX/SSE2
  "PREFETCH",      // MMX-Ext
  "PSADBW",        // MMX-Ext
  "PSHUFB",        // SSSE3
  "PSHUFD",        // SSE2
  "PSHUFW",        // MMX-Ext
  "PSHUFHW",       // SSE2
  "PSHUFLW",       // SSE2
  "PSIGNB",        // SSSE3
  "PSIGND",        // SSSE3
  "PSIGNW",        // SSSE3
  "PSLLD",         // MMX/SSE2
  "PSLLDQ",        // SSE2
  "PSLLQ",         // MMX/SSE2
  "PSLLW",         // MMX/SSE2
  "PSRAD",         // MMX/SSE2
  "PSRAW",         // MMX/SSE2
  "PSRLD",         // MMX/SSE2
  "PSRLDQ",        // SSE2
  "PSRLQ",         // MMX/SSE2
  "PSRLW",         // MMX/SSE2
  "PSUBB",         // MMX/SSE2
  "PSUBD",         // MMX/SSE2
  "PSUBQ",         // SSE2
  "PSUBSB",        // MMX/SSE2
  "PSUBSW",        // MMX/SSE2
  "PSUBUSB",       // MMX/SSE2
  "PSUBUSW",       // MMX/SSE2
  "PSUBW",         // MMX/SSE2
  "PSWAPD",        // Enhanced 3dNow!
  "PTEST",         // SSE4.1
  "PUNPCKHBW",     // MMX/SSE2
  "PUNPCKHDQ",     // MMX/SSE2
  "PUNPCKHQDQ",    // SSE2
  "PUNPCKHWD",     // MMX/SSE2
  "PUNPCKLBW",     // MMX/SSE2
  "PUNPCKLDQ",     // MMX/SSE2
  "PUNPCKLQDQ",    // SSE2
  "PUNPCKLWD",     // MMX/SSE2
  "PUSH",          // X86/X64
  "PUSHAD",        // X86 only
  "PUSHFD",        // X86 only
  "PUSHFQ",        // X64 only
  "PXOR",          // MMX/SSE2
  "RCL",           // X86/X64
  "RCPPS",         // SSE
  "RCPSS",         // SSE
  "RCR",           // X86/X64
  "RDTSC",         // X86/X64
  "RDTSCP",        // X86/X64
  "REP_LODSB",     // X86/X64 (REP)
  "REP_LODSD",     // X86/X64 (REP)
  "REP_LODSQ",     // X64 only (REP)
  "REP_LODSW",     // X86/X64 (REP)
  "REP_MOVSB",     // X86/X64 (REP)
  "REP_MOVSD",     // X86/X64 (REP)
  "REP_MOVSQ",     // X64 only (REP)
  "REP_MOVSW",     // X86/X64 (REP)
  "REP_STOSB",     // X86/X64 (REP)
  "REP_STOSD",     // X86/X64 (REP)
  "REP_STOSQ",     // X64 only (REP)
  "REP_STOSW",     // X86/X64 (REP)
  "REPE_CMPSB",    // X86/X64 (REP)
  "REPE_CMPSD",    // X86/X64 (REP)
  "REPE_CMPSQ",    // X64 only (REP)
  "REPE_CMPSW",    // X86/X64 (REP)
  "REPE_SCASB",    // X86/X64 (REP)
  "REPE_SCASD",    // X86/X64 (REP)
  "REPE_SCASQ",    // X64 only (REP)
  "REPE_SCASW",    // X86/X64 (REP)
  "REPNE_CMPSB",   // X86/X64 (REP)
  "REPNE_CMPSD",   // X86/X64 (REP)
  "REPNE_CMPSQ",   // X64 only (REP)
  "REPNE_CMPSW",   // X86/X64 (REP)
  "REPNE_SCASB",   // X86/X64 (REP)
  "REPNE_SCASD",   // X86/X64 (REP)
  "REPNE_SCASQ",   // X64 only (REP)
  "REPNE_SCASW",   // X86/X64 (REP)
  "RET",           // X86/X64
  "ROL",           // X86/X64
  "ROR",           // X86/X64
  "ROUNDPD",       // SSE4.1
  "ROUNDPS",       // SSE4.1
  "ROUNDSD",       // SSE4.1
  "ROUNDSS",       // SSE4.1
  "RSQRTPS",       // SSE
  "RSQRTSS",       // SSE
  "SAHF",          // X86/X64 (CPUID NEEDED)
  "SAL",           // X86/X64
  "SAR",           // X86/X64
  "SBB",           // X86/X64
  "SETA",           // Begin (setcc)
                 // X86/X64 (setcc)
  "SETAE",         // X86/X64 (setcc)
  "SETB",          // X86/X64 (setcc)
  "SETBE",         // X86/X64 (setcc)
  "SETC",          // X86/X64 (setcc)
  "SETE",          // X86/X64 (setcc)
  "SETG",          // X86/X64 (setcc)
  "SETGE",         // X86/X64 (setcc)
  "SETL",          // X86/X64 (setcc)
  "SETLE",         // X86/X64 (setcc)
  "SETNA",         // X86/X64 (setcc)
  "SETNAE",        // X86/X64 (setcc)
  "SETNB",         // X86/X64 (setcc)
  "SETNBE",        // X86/X64 (setcc)
  "SETNC",         // X86/X64 (setcc)
  "SETNE",         // X86/X64 (setcc)
  "SETNG",         // X86/X64 (setcc)
  "SETNGE",        // X86/X64 (setcc)
  "SETNL",         // X86/X64 (setcc)
  "SETNLE",        // X86/X64 (setcc)
  "SETNO",         // X86/X64 (setcc)
  "SETNP",         // X86/X64 (setcc)
  "SETNS",         // X86/X64 (setcc)
  "SETNZ",         // X86/X64 (setcc)
  "SETO",          // X86/X64 (setcc)
  "SETP",          // X86/X64 (setcc)
  "SETPE",         // X86/X64 (setcc)
  "SETPO",         // X86/X64 (setcc)
  "SETS",          // X86/X64 (setcc)
  "SETZ",          // X86/X64 (setcc)
  "SFENCE",        // MMX-Ext/SSE
  "SHL",           // X86/X64
  "SHLD",          // X86/X64
  "SHR",           // X86/X64
  "SHRD",          // X86/X64
  "SHUFPD",        // SSE2
  "SHUFPS",        // SSE
  "SQRTPD",        // SSE2
  "SQRTPS",        // SSE
  "SQRTSD",        // SSE2
  "SQRTSS",        // SSE
  "STC",           // X86/X64
  "STD",           // X86/X64
  "STMXCSR",       // SSE
  "SUB",           // X86/X64
  "SUBPD",         // SSE2
  "SUBPS",         // SSE
  "SUBSD",         // SSE2
  "SUBSS",         // SSE
  "TEST",          // X86/X64
  "UCOMISD",       // SSE2
  "UCOMISS",       // SSE
  "UD2",           // X86/X64
  "UNPCKHPD",      // SSE2
  "UNPCKHPS",      // SSE
  "UNPCKLPD",      // SSE2
  "UNPCKLPS",      // SSE
  "XADD",          // X86/X64 (i486)
  "XCHG",          // X86/X64 (i386)
  "XOR",           // X86/X64
  "XORPD",         // SSE2
  "XORPS",         // SSE
};     
