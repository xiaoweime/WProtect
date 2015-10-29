

#ifndef ADVANCEDANALYSIS_HPP_2IOLFAJY
#define ADVANCEDANALYSIS_HPP_2IOLFAJY

#include "Analysis.hpp"
#include <udis86.h>

// 00 00 00
// o1 o2 o3
//

#define RAX (1 << 0)
#define RCX (1 << 1)
#define RDX (1 << 2)
#define RBX (1 << 3)
#define RSP (1 << 4)
#define RBP (1 << 5)
#define RSI (1 << 6)
#define RDI (1 << 7)
#define DEFAULT_32BIT (1 << 8)
#define DEFAULT_16BIT (1 << 9)
#define DEFAULT_8BIT_HIGT (1 << 10)
#define DEFAULT_8BIT_LOW  (1 << 11)
#define DEFAULT_R8_R15 (1 << 12)

#define EAX (RAX | DEFAULT_32BIT)
#define ECX (RCX | DEFAULT_32BIT)
#define EDX (RDX | DEFAULT_32BIT)
#define EBX (RBX | DEFAULT_32BIT)
#define ESP (RSP | DEFAULT_32BIT)
#define EBP (RBP | DEFAULT_32BIT)
#define ESI (RSI | DEFAULT_32BIT)
#define EDI (RDI | DEFAULT_32BIT)

#define R8D (EAX | DEFAULT_R8_R15 )
#define R9D (ECX | DEFAULT_R8_R15 )
#define R10D (EDX | DEFAULT_R8_R15 )
#define R11D (EBX | DEFAULT_R8_R15 )
#define R12D (ESP | DEFAULT_R8_R15 )
#define R13D (EBP | DEFAULT_R8_R15 )
#define R14D (ESI | DEFAULT_R8_R15 )
#define R15D (EDI | DEFAULT_R8_R15 )

#define AX (EAX | DEFAULT_16BIT)
#define CX (ECX | DEFAULT_16BIT)
#define DX (EDX | DEFAULT_16BIT)
#define BX (EBX | DEFAULT_16BIT)
#define SP (ESP | DEFAULT_16BIT)
#define BP (EBP | DEFAULT_16BIT)
#define SI (ESI | DEFAULT_16BIT)
#define DI (EDI | DEFAULT_16BIT)
#define R8W (R8D | DEFAULT_16BIT)
#define R9W (R9D | DEFAULT_16BIT)
#define R10W (R10D | DEFAULT_16BIT)
#define R11W (R11D | DEFAULT_16BIT) 
#define R12W (R12D | DEFAULT_16BIT)
#define R13W (R13D | DEFAULT_16BIT) 
#define R14W (R14D | DEFAULT_16BIT)
#define R15W (R15D | DEFAULT_16BIT) 
 
#define AL (AX | DEFAULT_8BIT_LOW) 
#define AH (AX | DEFAULT_8BIT_HIGT)
#define CL (CX | DEFAULT_8BIT_LOW) 
#define CH (CX | DEFAULT_8BIT_HIGT) 
#define DL (DX | DEFAULT_8BIT_LOW) 
#define DH (DX | DEFAULT_8BIT_HIGT) 
#define BL (BX | DEFAULT_8BIT_LOW) 
#define BH (BX | DEFAULT_8BIT_HIGT) 
#define R8B (R8W | DEFAULT_8BIT_LOW)
#define R9B (R9W | DEFAULT_8BIT_LOW) 
#define R10B (R10W | DEFAULT_8BIT_LOW) 
#define R11B (R11W | DEFAULT_8BIT_LOW) 
#define R12B (R12W | DEFAULT_8BIT_LOW)
#define R13B (R13W | DEFAULT_8BIT_LOW) 
#define R14B (R14W | DEFAULT_8BIT_LOW) 
#define R15B (R15W | DEFAULT_8BIT_LOW) 
#define SPL (R12W | DEFAULT_8BIT_HIGT)
#define BPL (R13W | DEFAULT_8BIT_HIGT)
#define SIL (R14W | DEFAULT_8BIT_HIGT)
#define DIL (R15W | DEFAULT_8BIT_HIGT)


#define O1R (1 << 0) 
#define O1W (1 << 1) 
#define O2R (1 << 2)
#define O2W (1 << 3) 
#define O3R (1 << 4)
#define O3W (1 << 5)
#define DEFO1R (1 << 6)
#define DEFO1W (1 << 7)
#define DEFO2R (1 << 8)
#define DEFO2W (1 << 9)
#define DEFO3R (1 << 10)
#define DEFO3W (1 << 11)
#define DEFO4R (1 << 12)
#define DEFO4W (1 << 13)
#define DEFALLR (1 << 14)
#define DEFALLW (1 << 15)
#define OPBYTE 1
#define OPWORD 2
#define OPDWORD 4
#define OPQWORD 8
#define DEFOPCOUNT(arg) ((arg & 0xf) << 14)
#define DEFOPSIZE(arg)  ((arg & 0x3) << 18)

#define O1C (O1R | O1W)
#define O2C (O2R | O2W)
#define O3C (O3R | O3W)
#define DEFO1C (DEFO1R | DEFO1W)
#define DEFO2C (DEFO2R | DEFO2W)
#define DEFO3C (DEFO3R | DEFO3W)
#define DEFO4C (DEFO4R | DEFO4W)
#define DEFALLC (DEFALLR | DEFALLW)

#define OERROR ~0
#define NONE 0

#define CF (1 << 0)
#define PF (1 << 2)
#define AF (1 << 4)
#define ZF (1 << 6)
#define SF (1 << 7)
#define TF (1 << 8)
#define IF (1 << 9)
#define DF (1 << 10)
#define OF (1 << 11)
#define IOPL (1 << 13)
#define NT (1 << 14)
#define RF (1 << 16)
#define VM (1 << 17)
#define AC (1 << 18)
#define VIF (1 << 19)
#define VIP (1 << 20)
#define ID (1 << 21)


struct X86AnalysisOption
{                                                                      
 ud_mnemonic_code mnemonic;
 long iflag;         //使用到的寄存器
 long oflag;         //指令会修改的寄存器
 long op;            //o1/rw,o2/rw,03/rw 
 char default_o1;
 char default_o2;
 char default_o3;
 char default_o4;
 X86AnalysisOption(
    ud_mnemonic_code _mnemonic,
    long _iflag,
    long _oflag,
    long _op,
    unsigned char _default_o1 = 0,
    unsigned char _default_o2 = 0,
    unsigned char _default_o3 = 0,
    unsigned char _default_o4 = 0
    )
  :mnemonic(_mnemonic),oflag(_oflag),iflag(_iflag),op(_op),
  default_o1(_default_o1),default_o2(_default_o2),
  default_o3(_default_o3),default_o4(_default_o4)
 {
   
 }
 ~X86AnalysisOption()
 {

 }
 ud_mnemonic_code get_mnemonic()
 {
  return mnemonic;
 }
 char get_oflag()
 {
  return oflag;
 }
 char get_iflag()
 {
  return iflag;
 }
 
 //read write chang(read+write)  000 000 000
};

/*
X86AnalysisOption X86AnalysisTable[] = {
    //{UD_Iinvalid,0x00000000,0x000000000,OERROR},
    //{UD_I3dnow,0x00000000,0x000000000,OERROR},
    //{UD_Inone,0x00000000,0x000000000,NONE},
    //{UD_Idb,0x00000000,0x000000000,OERROR},
    //{UD_Ipause,0x00000000,0x000000000,OERROR},
    {UD_Iaaa,0x00000000,AF | CF                          ,DEFO1C | DEFO2C,AL,AH},
    {UD_Iaad,0x00000000,SF | ZF | PF                     ,DEFO1C | DEFO2C,AL,AH},
    {UD_Iaam,0x00000000,SF | ZF | PF                     ,DEFO1C | DEFO2C,AL,AH},
    {UD_Iaas,0x00000000,AF | CF                          ,DEFO1C | DEFO2R,AL,AH},
    {UD_Iadc,0x00000000,OF | SF | ZF | AF | CF | PF      ,O1C | O2R},
    {UD_Iadd,0x00000000,OF | SF | ZF | AF | CF | PF      ,O1C | O2R},
    //{UD_Iaddpd,0x00000000,0x000000000,OERROR},
    //{UD_Iaddps,0x00000000,0x000000000,OERROR},
    //{UD_Iaddsd,0x00000000,0x000000000,OERROR},
    //{UD_Iaddss,0x00000000,0x000000000,OERROR},
    {UD_Iand,0x00000000,OF | CF | SF | ZF | PF           ,O1C | O2R},
    //{UD_Iandpd,0x00000000,0x000000000,OERROR},
    //{UD_Iandps,0x00000000,0x000000000,OERROR},
    //{UD_Iandnpd,0x00000000,0x000000000,OERROR},
    //{UD_Iandnps,0x00000000,0x000000000,OERROR},
    //--{UD_Iarpl,0x00000000,0x000000000,OERROR},
    //x64{UD_Imovsxd,0x00000000,0x000000000,OERROR},
    {UD_Ibound,0x00000000,0x000000000                    ,O1R | O2R},
    {UD_Ibsf,0x00000000,ZF                               ,O1W | O2R},
    {UD_Ibsr,0x00000000,ZF                               ,O1W | O2R},
    {UD_Ibswap,0x00000000,0x000000000                    ,O1C},
    {UD_Ibt,0x00000000,CF                                ,O1R | O2R},
    {UD_Ibtc,0x00000000,CF                               ,O1C | O2R},
    {UD_Ibtr,0x00000000,CF                               ,O1C | O2R},
    {UD_Ibts,0x00000000,CF                               ,O1C | O2R},
    {UD_Icall,0x00000000,0x000000000                     ,O1R},
    {UD_Icbw,0x00000000,0x000000000                      ,DEFO1W | DEFO2R,AX,AL},
    {UD_Icwde,0x00000000,0x000000000                     ,DEFO1W | DEFO2R,EAX,AX},
    {UD_Icdqe,0x00000000,0x000000000                     ,DEFO1W | DEFO2R,RAX,EAX},
    {UD_Iclc,0x00000000,CF                               ,NONE},
    {UD_Icld,0x00000000,DF                               ,NONE},
    //sys{UD_Iclflush,0x00000000,0x000000000,OERROR},
    //sys{UD_Iclgi,0x00000000,0x000000000,OERROR},
    //sys{UD_Icli,0x00000000,0x000000000,OERROR},
    //sys{UD_Iclts,0x00000000,0x000000000,OERROR},
    {UD_Icmc,CF        ,CF                               ,NONE},
    {UD_Icmovo,OF      ,0x000000000                      ,O1W | O2R},
    {UD_Icmovno,OF     ,0x000000000                      ,O1W | O2R},
    {UD_Icmovb,CF      ,0x000000000                      ,O1W | O2R},
    {UD_Icmovae,CF     ,0x000000000                      ,O1W | O2R},
    {UD_Icmovz,ZF      ,0x000000000                      ,O1W | O2R},
    {UD_Icmovnz,ZF     ,0x000000000                      ,O1W | O2R},
    {UD_Icmovbe,CF | ZF,0x000000000                      ,O1W | O2R},
    {UD_Icmova,CF | ZF ,0x000000000                      ,O1W | O2R},
    {UD_Icmovs,SF      ,0x000000000                      ,O1W | O2R},
    {UD_Icmovns,SF     ,0x000000000                      ,O1W | O2R},
    {UD_Icmovp,PF      ,0x000000000                      ,O1W | O2R},
    {UD_Icmovnp,PF     ,0x000000000                      ,O1W | O2R},
    {UD_Icmovl,SF | OF ,0x000000000                      ,O1W | O2R},
    {UD_Icmovge,SF | OF,0x000000000                      ,O1W | O2R},
    {UD_Icmovle,ZF | SF | OF,0x000000000                 ,O1W | O2R},
    {UD_Icmovg,ZF | SF | OF ,0x000000000                 ,O1W | O2R},
    {UD_Icmp,0x00000000,CF | OF | SF | ZF | AF | PF      ,O1R | O2R},
    //FPU{UD_Icmppd,0x00000000,0x000000000,OERROR},
    //FPU{UD_Icmpps,0x00000000,0x000000000,OERROR},
    //NO{UD_Icmpsb,0x00000000,0x000000000,OERROR},
    //NO{UD_Icmpsw,0x00000000,0x000000000,OERROR},
    //NO{UD_Icmpsd,0x00000000,0x000000000,OERROR},
    //NO{UD_Icmpsq,0x00000000,0x000000000,OERROR},
    //NO{UD_Icmpss,0x00000000,0x000000000,OERROR},
    {UD_Icmpxchg,0x00000000, ZF | CF | PF | AF | SF | OF ,O1C | O2R | DEFO1C,EAX},
    {UD_Icmpxchg8b,0x00000000,ZF                         ,O1C | DEFO1C | DEFO2C ,EAX,EDX },
    {UD_Icmpxchg16b,0x00000000,ZF                        ,O1C | DEFO1C | DEFO2C ,RAX,RDX },
    //FPU{UD_Icomisd,0x00000000,0x000000000,OERROR},
    //FPU{UD_Icomiss,0x00000000,0x000000000,OERROR},
    {UD_Icpuid,0x00000000,0x000000000                    ,DEFO1C|DEFO2W|DEFO3W|DEFO4W,EAX,EBX,ECX,EDX},
    //FPU{UD_Icvtdq2pd,0x00000000,0x000000000,OERROR},
    //FPU{UD_Icvtdq2ps,0x00000000,0x000000000,OERROR},
    //FPU{UD_Icvtpd2dq,0x00000000,0x000000000,OERROR},
    //FPU{UD_Icvtpd2pi,0x00000000,0x000000000,OERROR},
    //FPU{UD_Icvtpd2ps,0x00000000,0x000000000,OERROR},
    //FPU{UD_Icvtpi2ps,0x00000000,0x000000000,OERROR},
    //FPU{UD_Icvtpi2pd,0x00000000,0x000000000,OERROR},
    //FPU{UD_Icvtps2dq,0x00000000,0x000000000,OERROR},
    //FPU{UD_Icvtps2pi,0x00000000,0x000000000,OERROR},
    //FPU{UD_Icvtps2pd,0x00000000,0x000000000,OERROR},
    //FPU{UD_Icvtsd2si,0x00000000,0x000000000,OERROR},
    //FPU{UD_Icvtsd2ss,0x00000000,0x000000000,OERROR},
    //FPU{UD_Icvtsi2ss,0x00000000,0x000000000,OERROR},
    //FPU{UD_Icvtss2si,0x00000000,0x000000000,OERROR},
    //FPU{UD_Icvtss2sd,0x00000000,0x000000000,OERROR},
    //FPU{UD_Icvttpd2pi,0x00000000,0x000000000,OERROR},
    //FPU{UD_Icvttpd2dq,0x00000000,0x000000000,OERROR},
    //FPU{UD_Icvttps2dq,0x00000000,0x000000000,OERROR},
    //FPU{UD_Icvttps2pi,0x00000000,0x000000000,OERROR},
    //FPU{UD_Icvttsd2si,0x00000000,0x000000000,OERROR},
    //FPU{UD_Icvtsi2sd,0x00000000,0x000000000,OERROR},
    //FPU{UD_Icvttss2si,0x00000000,0x000000000,OERROR},
    {UD_Icwd,0x00000000,0x000000000                      ,DEFO1C | DEFO2W,AX,DX},
    {UD_Icdq,0x00000000,0x000000000                      ,DEFO1C | DEFO2W,EAX,EDX},
    {UD_Icqo,0x00000000,0x000000000                      ,DEFO1C | DEFO2W,RAX,RDX},
    {UD_Idaa,0x00000000,CF | AF | SF | ZF | PF           ,DEFO1C,AL},
    {UD_Idas,0x00000000,CF | AF | SF | ZF | PF           ,DEFO1C,AL},
    {UD_Idec,0x00000000,OF | SF | ZF | AF | CF           ,O1C},
    {UD_Idiv,0x00000000,0x000000000                      ,DEFOPSIZE(OPBYTE) | O1R | DEFO1C,AX}, //DIV R/M8
    {UD_Idiv,0x00000000,0x000000000                      ,DEFOPSIZE(OPWORD) | O1R | DEFO1C | DEFO2C,AX,DX },//DIV R/M16 
    {UD_Idiv,0x00000000,0x000000000                      ,DEFOPSIZE(OPDWORD) | O1R | DEFO1C | DEFO2C,EAX,EDX },//DIV R/M32
    {UD_Idiv,0x00000000,0x000000000                      ,DEFOPSIZE(OPQWORD) | O1R | DEFO1C | DEFO2C,RAX,RDX },//DIV R/M64
    //FPU{UD_Idivpd,0x00000000,0x000000000,OERROR},
    //FPU{UD_Idivps,0x00000000,0x000000000,OERROR},
    //FPU{UD_Idivsd,0x00000000,0x000000000,OERROR},
    //FPU{UD_Idivss,0x00000000,0x000000000,OERROR},
    //MMX{UD_Iemms,0x00000000,0x000000000,OERROR},
    //SYS{UD_Ienter,0x00000000,0x000000000,OERROR},
    //FPU{UD_If2xm1,0x00000000,0x000000000,OERROR},
    //FPU{UD_Ifabs,0x00000000,0x000000000,OERROR},
    //FPU{UD_Ifadd,0x00000000,0x000000000,OERROR},
    //FPU{UD_Ifaddp,0x00000000,0x000000000,OERROR},
    //FPU{UD_Ifbld,0x00000000,0x000000000,OERROR},
    //FPU{UD_Ifbstp,0x00000000,0x000000000,OERROR},
    //FPU{UD_Ifchs,0x00000000,0x000000000,OERROR},
    //FPU{UD_Ifclex,0x00000000,0x000000000,OERROR},
    //FPU{UD_Ifcmovb,0x00000000,0x000000000,OERROR},
    //FPU{UD_Ifcmove,0x00000000,0x000000000,OERROR},
    //FPU{UD_Ifcmovbe,0x00000000,0x000000000,OERROR},
    //FPU{UD_Ifcmovu,0x00000000,0x000000000,OERROR},
    //FPU{UD_Ifcmovnb,0x00000000,0x000000000,OERROR},
    //FPU{UD_Ifcmovne,0x00000000,0x000000000,OERROR},
    //FPU{UD_Ifcmovnbe,0x00000000,0x000000000,OERROR},
    //FPU{UD_Ifcmovnu,0x00000000,0x000000000,OERROR},
    //FPU{UD_Ifucomi,0x00000000,0x000000000,OERROR},
    //FPU{UD_Ifcom,0x00000000,0x000000000,OERROR},
    //FPU{UD_Ifcom2,0x00000000,0x000000000,OERROR},
    //FPU{UD_Ifcomp3,0x00000000,0x000000000,OERROR},
    //FPU{UD_Ifcomi,0x00000000,0x000000000,OERROR},
    //FPU{UD_Ifucomip,0x00000000,0x000000000,OERROR},
    //FPU{UD_Ifcomip,0x00000000,0x000000000,OERROR},
    //FPU{UD_Ifcomp,0x00000000,0x000000000,OERROR},
    //FPU{UD_Ifcomp5,0x00000000,0x000000000,OERROR},
    //FPU{UD_Ifcompp,0x00000000,0x000000000,OERROR},
    //FPU{UD_Ifcos,0x00000000,0x000000000,OERROR},
    //FPU{UD_Ifdecstp,0x00000000,0x000000000,OERROR},
    //FPU{UD_Ifdiv,0x00000000,0x000000000,OERROR},
    //FPU{UD_Ifdivp,0x00000000,0x000000000,OERROR},
    //FPU{UD_Ifdivr,0x00000000,0x000000000,OERROR},
    //FPU{UD_Ifdivrp,0x00000000,0x000000000,OERROR},
    //FPU{UD_Ifemms,0x00000000,0x000000000,OERROR},
    //FPU{UD_Iffree,0x00000000,0x000000000,OERROR},
    //FPU{UD_Iffreep,0x00000000,0x000000000,OERROR},
    //FPU{UD_Ificom,0x00000000,0x000000000,OERROR},
    //FPU{UD_Ificomp,0x00000000,0x000000000,OERROR},
    //{UD_Ifild,0x00000000,0x000000000,OERROR},
    //{UD_Ifincstp,0x00000000,0x000000000,OERROR},
    //{UD_Ifninit,0x00000000,0x000000000,OERROR},
    //{UD_Ifiadd,0x00000000,0x000000000,OERROR},
    //{UD_Ifidivr,0x00000000,0x000000000,OERROR},
    //{UD_Ifidiv,0x00000000,0x000000000,OERROR},
    //{UD_Ifisub,0x00000000,0x000000000,OERROR},
    //{UD_Ifisubr,0x00000000,0x000000000,OERROR},
    //{UD_Ifist,0x00000000,0x000000000,OERROR},
    //{UD_Ifistp,0x00000000,0x000000000,OERROR},
    //{UD_Ifisttp,0x00000000,0x000000000,OERROR},
    //{UD_Ifld,0x00000000,0x000000000,OERROR},
    //{UD_Ifld1,0x00000000,0x000000000,OERROR},
    //{UD_Ifldl2t,0x00000000,0x000000000,OERROR},
    //{UD_Ifldl2e,0x00000000,0x000000000,OERROR},
    //{UD_Ifldpi,0x00000000,0x000000000,OERROR},
    //{UD_Ifldlg2,0x00000000,0x000000000,OERROR},
    //{UD_Ifldln2,0x00000000,0x000000000,OERROR},
    //{UD_Ifldz,0x00000000,0x000000000,OERROR},
    //{UD_Ifldcw,0x00000000,0x000000000,OERROR},
    //{UD_Ifldenv,0x00000000,0x000000000,OERROR},
    //{UD_Ifmul,0x00000000,0x000000000,OERROR},
    //{UD_Ifmulp,0x00000000,0x000000000,OERROR},
    //{UD_Ifimul,0x00000000,0x000000000,OERROR},
    //{UD_Ifnop,0x00000000,0x000000000,OERROR},
    //{UD_Ifpatan,0x00000000,0x000000000,OERROR},
    //{UD_Ifprem,0x00000000,0x000000000,OERROR},
    //{UD_Ifprem1,0x00000000,0x000000000,OERROR},
    //{UD_Ifptan,0x00000000,0x000000000,OERROR},
    //{UD_Ifrndint,0x00000000,0x000000000,OERROR},
    //{UD_Ifrstor,0x00000000,0x000000000,OERROR},
    //{UD_Ifnsave,0x00000000,0x000000000,OERROR},
    //{UD_Ifscale,0x00000000,0x000000000,OERROR},
    //{UD_Ifsin,0x00000000,0x000000000,OERROR},
    //{UD_Ifsincos,0x00000000,0x000000000,OERROR},
    //{UD_Ifsqrt,0x00000000,0x000000000,OERROR},
    //{UD_Ifstp,0x00000000,0x000000000,OERROR},
    //{UD_Ifstp1,0x00000000,0x000000000,OERROR},
    //{UD_Ifstp8,0x00000000,0x000000000,OERROR},
    //{UD_Ifstp9,0x00000000,0x000000000,OERROR},
    //{UD_Ifst,0x00000000,0x000000000,OERROR},
    //{UD_Ifnstcw,0x00000000,0x000000000,OERROR},
    //{UD_Ifnstenv,0x00000000,0x000000000,OERROR},
    //{UD_Ifnstsw,0x00000000,0x000000000,OERROR},
    //{UD_Ifsub,0x00000000,0x000000000,OERROR},
    //{UD_Ifsubp,0x00000000,0x000000000,OERROR},
    //{UD_Ifsubr,0x00000000,0x000000000,OERROR},
    //{UD_Ifsubrp,0x00000000,0x000000000,OERROR},
    //{UD_Iftst,0x00000000,0x000000000,OERROR},
    //{UD_Ifucom,0x00000000,0x000000000,OERROR},
    //{UD_Ifucomp,0x00000000,0x000000000,OERROR},
    //{UD_Ifucompp,0x00000000,0x000000000,OERROR},
    //{UD_Ifxam,0x00000000,0x000000000,OERROR},
    //{UD_Ifxch,0x00000000,0x000000000,OERROR},
    //{UD_Ifxch4,0x00000000,0x000000000,OERROR},
    //{UD_Ifxch7,0x00000000,0x000000000,OERROR},
    //{UD_Ifxrstor,0x00000000,0x000000000,OERROR},
    //{UD_Ifxsave,0x00000000,0x000000000,OERROR},
    //{UD_Ifxtract,0x00000000,0x000000000,OERROR},
    //{UD_Ifyl2x,0x00000000,0x000000000,OERROR},
    //{UD_Ifyl2xp1,0x00000000,0x000000000,OERROR},
    //SYS{UD_Ihlt,0x00000000,0x000000000,OERROR},
    {UD_Iidiv,0x00000000,0x000000000                      ,DEFOPSIZE(OPBYTE) | O1R | DEFO1C,AX}, //DIV R/M8
    {UD_Iidiv,0x00000000,0x000000000                      ,DEFOPSIZE(OPWORD) | O1R | DEFO1C | DEFO2C,AX,DX },//DIV R/M16 
    {UD_Iidiv,0x00000000,0x000000000                      ,DEFOPSIZE(OPDWORD) | O1R | DEFO1C | DEFO2C,EAX,EDX },//DIV R/M32
    {UD_Iidiv,0x00000000,0x000000000                      ,DEFOPSIZE(OPQWORD) | O1R | DEFO1C | DEFO2C,RAX,RDX },//DIV R/M64
    {UD_Iin,0x00000000,0x000000000                        ,O1W | O2R,AL},

    {UD_Iimul,0x00000000,0x000000000                      ,DEFOPSIZE(OPBYTE) | DEFOPCOUNT(1) | DEFO1C | O1R,AX},     
    {UD_Iimul,0x00000000,0x000000000                      ,DEFOPSIZE(OPWORD) | DEFOPCOUNT(1) | DEFO1C | DEFO2W | O1R,AX,DX},     
    {UD_Iimul,0x00000000,0x000000000                      ,DEFOPSIZE(OPDWORD) | DEFOPCOUNT(1) | DEFO1C | DEFO2W | O1R,EAX,EDX},           
    {UD_Iimul,0x00000000,0x000000000                      ,DEFOPSIZE(OPQWORD) | DEFOPCOUNT(1) | DEFO1C | DEFO2W | O1R,RAX,RDX},      

    {UD_Iimul,0x00000000,0x000000000                      ,DEFOPCOUNT(2) | O1C | O2R},

    {UD_Iimul,0x00000000,0x000000000                      ,DEFOPCOUNT(3) | O1W | O2R | O3R}, 

    {UD_Iinc,0x00000000,OF | SF | ZF | AF | CF            ,O1C},
    {UD_Iinsb,0x00000000,0x000000000                      ,DEFOPCOUNT(2) | O1W | O2R},
    {UD_Iinsb,0x00000000,0x000000000                      ,DEFOPCOUNT(0) | DEFO1W | DEFO2R,EDI,DX}, 
    
    {UD_Iinsw,0x00000000,0x000000000                      ,DEFOPCOUNT(2) | O1W | O2R},
    {UD_Iinsw,0x00000000,0x000000000                      ,DEFOPCOUNT(0) | DEFO1W | DEFO2R,EDI,DX}, 

    {UD_Iinsd,0x00000000,0x000000000                      ,DEFOPCOUNT(2) | O1W | O2R},
    {UD_Iinsd,0x00000000,0x000000000                      ,DEFOPCOUNT(0) | DEFO1W | DEFO2R,EDI,DX}, 

    //{UD_Iint1,0x00000000,0x000000000,OERROR},
    //{UD_Iint3,0x00000000,0x000000000,OERROR},
    //{UD_Iint,0x00000000,0x000000000,OERROR},
    //{UD_Iinto,0x00000000,0x000000000,OERROR},
    //{UD_Iinvd,0x00000000,0x000000000,OERROR},
    //{UD_Iinvept,0x00000000,0x000000000,OERROR},
    //{UD_Iinvlpg,0x00000000,0x000000000,OERROR},
    //{UD_Iinvlpga,0x00000000,0x000000000,OERROR},
    //{UD_Iinvvpid,0x00000000,0x000000000,OERROR},
    //{UD_Iiretw,0x00000000,0x000000000,OERROR},
    //{UD_Iiretd,0x00000000,0x000000000,OERROR},
    //{UD_Iiretq,0x00000000,0x000000000,OERROR},
    {UD_Ijo,OF                     ,0x000000000           ,O1R},
    {UD_Ijno,OF                    ,0x000000000           ,O1R},
    {UD_Ijb,CF                     ,0x000000000           ,O1R},
    {UD_Ijae,CF                    ,0x000000000           ,O1R},
    {UD_Ijz,ZF                     ,0x000000000           ,O1R},
    {UD_Ijnz,ZF                    ,0x000000000           ,O1R},
    {UD_Ijbe,CF | ZF               ,0x000000000           ,O1R},
    {UD_Ija,CF | ZF                ,0x000000000           ,O1R},
    {UD_Ijs,SF                     ,0x000000000           ,O1R},
    {UD_Ijns,SF                    ,0x000000000           ,O1R},
    {UD_Ijp,PF                     ,0x000000000           ,O1R},
    {UD_Ijnp,PF                    ,0x000000000           ,O1R},
    {UD_Ijl,SF | OF                ,0x000000000           ,O1R},
    {UD_Ijge,SF | OF               ,0x000000000           ,O1R},
    {UD_Ijle,SF | ZF | OF          ,0x000000000           ,O1R},
    {UD_Ijg,ZF | SF | OF           ,0x000000000           ,O1R},
    {UD_Ijcxz,0x00000000           ,0x000000000           ,DEFO1R,CX},
    {UD_Ijecxz,0x00000000          ,0x000000000           ,DEFO2R,ECX},
    {UD_Ijrcxz,0x00000000          ,0x000000000           ,DEFO2R,RCX},
    {UD_Ijmp,0x00000000            ,0x000000000           ,O1R},
    {UD_Ilahf,SF | ZF | AF | PF | CF,0x000000000          ,DEFO1W,AH},
    {UD_Ilar,ZF                  ,0x000000000             ,O1W | O2R},
    //{UD_Ilddqu,0x00000000,0x000000000,OERROR},
    //{UD_Ildmxcsr,0x00000000,0x000000000,OERROR},
    {UD_Ilds,0x00000000,0x000000000                       ,O1W | O2R},
    {UD_Ilea,0x00000000,0x000000000                       ,O1W | O2R},
    {UD_Iles,0x00000000,0x000000000                       ,O1W | O2R},
    {UD_Ilfs,0x00000000,0x000000000                       ,O1W | O2R},
    {UD_Ilgs,0x00000000,0x000000000                       ,O1W | O2R},
    {UD_Ilidt,0x00000000,0x000000000                      ,O1R},
    {UD_Ilss,0x00000000,0x000000000                       ,O1W | O2R},
    {UD_Ileave,0x00000000,0x000000000                     ,DEFO1R | DEFO2W,RSP,EBP},
    //{UD_Ilfence,0x00000000,0x000000000                    ,OERROR},
    {UD_Ilgdt,0x00000000,0x000000000                      ,O1R},
    {UD_Illdt,0x00000000,0x000000000                      ,O1R},
    {UD_Ilmsw,0x00000000,0x000000000                      ,O1R},
    //{UD_Ilock,0x00000000,0x000000000,OERROR},
    {UD_Ilodsb,DF,0x000000000                             ,DEFO1W | DEFO2R,AL,RSI},
    {UD_Ilodsw,DF,0x000000000                             ,DEFO1W | DEFO2R,AX,RSI},
    {UD_Ilodsd,DF,0x000000000                             ,DEFO1W | DEFO2R,EAX,RSI},
    {UD_Ilodsq,DF,0x000000000                             ,DEFO1W | DEFO2R,RAX,RSI},
    {UD_Iloopne,ZF,0x000000000                            ,DEFO1R | O1R,RCX},
    {UD_Iloope,ZF,0x000000000                             ,DEFO1R | O1R,RCX},
    {UD_Iloop,0x00000000,0x000000000                      ,DEFO1R | O1R,RCX},
    {UD_Ilsl,0x00000000,0x000000000                       ,O1W | O2R},
    {UD_Iltr,0x00000000,0x000000000                       ,O1R},
    //{UD_Imaskmovq,0x00000000,0x000000000,OERROR},
    //{UD_Imaxpd,0x00000000,0x000000000,OERROR},
    //{UD_Imaxps,0x00000000,0x000000000,OERROR},
    //{UD_Imaxsd,0x00000000,0x000000000,OERROR},
    //{UD_Imaxss,0x00000000,0x000000000,OERROR},
    //{UD_Imfence,0x00000000,0x000000000,OERROR},
    //{UD_Iminpd,0x00000000,0x000000000,OERROR},
    //{UD_Iminps,0x00000000,0x000000000,OERROR},
    //{UD_Iminsd,0x00000000,0x000000000,OERROR},
    //{UD_Iminss,0x00000000,0x000000000,OERROR},
    {UD_Imonitor,0x00000000,0x000000000                   ,DEFO1R|DEFO2R|DEFO3R,RAX,RCX,RDX},
    //{UD_Imontmul,0x00000000,0x000000000,OERROR},
    {UD_Imov,0x00000000,0x000000000                       ,O2R | O1W},
    //{UD_Imovapd,0x00000000,0x000000000,OERROR},
    //{UD_Imovaps,0x00000000,0x000000000,OERROR},
    {UD_Imovd,0x00000000,0x000000000                      ,O1W},
    //{UD_Imovhpd,0x00000000,0x000000000,OERROR},
    //{UD_Imovhps,0x00000000,0x000000000,OERROR},
    //{UD_Imovlhps,0x00000000,0x000000000,OERROR},
    //{UD_Imovlpd,0x00000000,0x000000000,OERROR},
    //{UD_Imovlps,0x00000000,0x000000000,OERROR},
    //{UD_Imovhlps,0x00000000,0x000000000,OERROR},
    //{UD_Imovmskpd,0x00000000,0x000000000,OERROR},
    //{UD_Imovmskps,0x00000000,0x000000000,OERROR},
    //{UD_Imovntdq,0x00000000,0x000000000,OERROR},
    //{UD_Imovnti,0x00000000,0x000000000,OERROR},
    //{UD_Imovntpd,0x00000000,0x000000000,OERROR},
    //{UD_Imovntps,0x00000000,0x000000000,OERROR},
    //{UD_Imovntq,0x00000000,0x000000000,OERROR},
    //{UD_Imovq,0x00000000,0x000000000,OERROR},
    {UD_Imovsb,DF,0x000000000                            ,DEFO1R | DEFO2R,RSI,RDI},
    {UD_Imovsw,DF,0x000000000                            ,DEFO1R | DEFO2R,RSI,RDI},
    {UD_Imovsd,DF,0x000000000                            ,DEFO1R | DEFO2R,RSI,RDI},
    {UD_Imovsq,DF,0x000000000                            ,DEFO1R | DEFO2R,RSI,RDI},
    //{UD_Imovss,0x00000000,0x000000000,OERROR},
    {UD_Imovsx,0x00000000,0x000000000                    ,O2R | O1W},
    //UD_Imovupd,0x00000000,0x000000000,OERROR},
    //{UD_Imovups,0x00000000,0x000000000,OERROR},
    {UD_Imovzx,0x00000000,0x000000000                    ,O1W | O2R},
    {UD_Imul,0x00000000,OF | CF                          ,DEFOPSIZE(OPBYTE) | DEFO1C,AX},
    {UD_Imul,0x00000000,OF | CF                          ,DEFOPSIZE(OPWORD) | DEFO1C | DEFO2W,AX,DX}, 
    {UD_Imul,0x00000000,OF | CF                          ,DEFOPSIZE(OPDWORD) | DEFO1C | DEFO2W,EAX,EDX},
    {UD_Imul,0x00000000,OF | CF                          ,DEFOPSIZE(OPQWORD) | DEFO1C | DEFO2W,RAX,RDX},  
    //{UD_Imulpd,0x00000000,0x000000000,OERROR},
    //{UD_Imulps,0x00000000,0x000000000,OERROR},
    //{UD_Imulsd,0x00000000,0x000000000,OERROR},
    //{UD_Imulss,0x00000000,0x000000000,OERROR},
    {UD_Imwait,0x00000000,0x000000000                    ,DEFO1W | DEFO2W,RAX,RCX},
    {UD_Ineg,0x00000000,CF | OF | SF | ZF | AF | CF      ,O1C},
    {UD_Inop,0x00000000,0x000000000,NONE},
    {UD_Inot,0x00000000,0x000000000                      ,O1C},
    {UD_Ior,0x00000000,OF | CF | SF | ZF | PF            ,O1C | O2R},
    //{UD_Iorpd,0x00000000,0x000000000,OERROR},
    //{UD_Iorps,0x00000000,0x000000000,OERROR},
    {UD_Iout,0x00000000,0x000000000                      ,O1R | O2R},
    {UD_Ioutsb,0x00000000,0x000000000                    ,O1R | O2R},
    {UD_Ioutsw,0x00000000,0x000000000                    ,O1R | O2R},
    {UD_Ioutsd,0x00000000,0x000000000                    ,O1R | O2R},
    //{UD_Ipacksswb,0x00000000,0x000000000,OERROR},
    //{UD_Ipackssdw,0x00000000,0x000000000,OERROR},
    //{UD_Ipackuswb,0x00000000,0x000000000,OERROR},
    //{UD_Ipaddb,0x00000000,0x000000000,OERROR},
    //{UD_Ipaddw,0x00000000,0x000000000,OERROR},
    //{UD_Ipaddd,0x00000000,0x000000000,OERROR},
    //{UD_Ipaddsb,0x00000000,0x000000000,OERROR},
    //{UD_Ipaddsw,0x00000000,0x000000000,OERROR},
    //{UD_Ipaddusb,0x00000000,0x000000000,OERROR},
    //{UD_Ipaddusw,0x00000000,0x000000000,OERROR},
    //{UD_Ipand,0x00000000,0x000000000,OERROR},
    //{UD_Ipandn,0x00000000,0x000000000,OERROR},
    //{UD_Ipavgb,0x00000000,0x000000000,OERROR},
    //{UD_Ipavgw,0x00000000,0x000000000,OERROR},
    //{UD_Ipcmpeqb,0x00000000,0x000000000,OERROR},
    //{UD_Ipcmpeqw,0x00000000,0x000000000,OERROR},
    //{UD_Ipcmpeqd,0x00000000,0x000000000,OERROR},
    //{UD_Ipcmpgtb,0x00000000,0x000000000,OERROR},
    //{UD_Ipcmpgtw,0x00000000,0x000000000,OERROR},
    //{UD_Ipcmpgtd,0x00000000,0x000000000,OERROR},
    //{UD_Ipextrb,0x00000000,0x000000000,OERROR},
   // {UD_Ipextrd,0x00000000,0x000000000,OERROR},
    {UD_Ipextrq,0x00000000,0x000000000                  ,O1W},
    {UD_Ipextrw,0x00000000,0x000000000                  ,O1W},
    {UD_Ipinsrb,0x00000000,0x000000000                  ,O2R},
    {UD_Ipinsrw,0x00000000,0x000000000                  ,O2R},
    {UD_Ipinsrd,0x00000000,0x000000000                  ,O2R},
    {UD_Ipinsrq,0x00000000,0x000000000                  ,O2R},
    //{UD_Ipmaddwd,0x00000000,0x000000000,OERROR},
    //{UD_Ipmaxsw,0x00000000,0x000000000,OERROR},
    //{UD_Ipmaxub,0x00000000,0x000000000,OERROR},
    //{UD_Ipminsw,0x00000000,0x000000000,OERROR},
    //{UD_Ipminub,0x00000000,0x000000000,OERROR},
    //{UD_Ipmovmskb,0x00000000,0x000000000,OERROR},
    //{UD_Ipmulhuw,0x00000000,0x000000000,OERROR},
    //{UD_Ipmulhw,0x00000000,0x000000000,OERROR},
    //{UD_Ipmullw,0x00000000,0x000000000,OERROR},
    {UD_Ipop,0x00000000,0x000000000                     ,O1W},
    {UD_Ipopa,0x00000000,0x000000000                    ,DEFALLW},
    {UD_Ipopad,0x00000000,0x000000000                   ,DEFALLW},
    {UD_Ipopfw,0x00000000,0xFFFFFFFFF                   ,NONE},
    {UD_Ipopfd,0x00000000,0xFFFFFFFFF                   ,NONE},
    {UD_Ipopfq,0x00000000,0xFFFFFFFFF                   ,NONE},
    //{UD_Ipor,0x00000000,0x000000000,OERROR},
    //{UD_Iprefetch,0x00000000,0x000000000,OERROR},
    //{UD_Iprefetchnta,0x00000000,0x000000000,OERROR},
    //{UD_Iprefetcht0,0x00000000,0x000000000,OERROR},
    //{UD_Iprefetcht1,0x00000000,0x000000000,OERROR},
    //{UD_Iprefetcht2,0x00000000,0x000000000,OERROR},
    //{UD_Ipsadbw,0x00000000,0x000000000,OERROR},
    //{UD_Ipshufw,0x00000000,0x000000000,OERROR},
    //{UD_Ipsllw,0x00000000,0x000000000,OERROR},
    //{UD_Ipslld,0x00000000,0x000000000,OERROR},
    //{UD_Ipsllq,0x00000000,0x000000000,OERROR},
    //{UD_Ipsraw,0x00000000,0x000000000,OERROR},
    //{UD_Ipsrad,0x00000000,0x000000000,OERROR},
    //{UD_Ipsrlw,0x00000000,0x000000000,OERROR},
    //{UD_Ipsrld,0x00000000,0x000000000,OERROR},
    //{UD_Ipsrlq,0x00000000,0x000000000,OERROR},
    //{UD_Ipsubb,0x00000000,0x000000000,OERROR},
    //{UD_Ipsubw,0x00000000,0x000000000,OERROR},
    //{UD_Ipsubd,0x00000000,0x000000000,OERROR},
    //{UD_Ipsubsb,0x00000000,0x000000000,OERROR},
    //{UD_Ipsubsw,0x00000000,0x000000000,OERROR},
    //{UD_Ipsubusb,0x00000000,0x000000000,OERROR},
    //{UD_Ipsubusw,0x00000000,0x000000000,OERROR},
    //{UD_Ipunpckhbw,0x00000000,0x000000000,OERROR},
    //{UD_Ipunpckhwd,0x00000000,0x000000000,OERROR},
    //{UD_Ipunpckhdq,0x00000000,0x000000000,OERROR},
    //{UD_Ipunpcklbw,0x00000000,0x000000000,OERROR},
    //{UD_Ipunpcklwd,0x00000000,0x000000000,OERROR},
    //{UD_Ipunpckldq,0x00000000,0x000000000,OERROR},
    //{UD_Ipi2fw,0x00000000,0x000000000,OERROR},
    //{UD_Ipi2fd,0x00000000,0x000000000,OERROR},
    //{UD_Ipf2iw,0x00000000,0x000000000,OERROR},
    //{UD_Ipf2id,0x00000000,0x000000000,OERROR},
    //{UD_Ipfnacc,0x00000000,0x000000000,OERROR},
    //{UD_Ipfpnacc,0x00000000,0x000000000,OERROR},
    //{UD_Ipfcmpge,0x00000000,0x000000000,OERROR},
    //{UD_Ipfmin,0x00000000,0x000000000,OERROR},
    //{UD_Ipfrcp,0x00000000,0x000000000,OERROR},
    //{UD_Ipfrsqrt,0x00000000,0x000000000,OERROR},
    //{UD_Ipfsub,0x00000000,0x000000000,OERROR},
    //{UD_Ipfadd,0x00000000,0x000000000,OERROR},
    //{UD_Ipfcmpgt,0x00000000,0x000000000,OERROR},
    //{UD_Ipfmax,0x00000000,0x000000000,OERROR},
    //{UD_Ipfrcpit1,0x00000000,0x000000000,OERROR},
    //{UD_Ipfrsqit1,0x00000000,0x000000000,OERROR},
    //{UD_Ipfsubr,0x00000000,0x000000000,OERROR},
    //{UD_Ipfacc,0x00000000,0x000000000,OERROR},
    //{UD_Ipfcmpeq,0x00000000,0x000000000,OERROR},
    //{UD_Ipfmul,0x00000000,0x000000000,OERROR},
    //{UD_Ipfrcpit2,0x00000000,0x000000000,OERROR},
    //{UD_Ipmulhrw,0x00000000,0x000000000,OERROR},
    //{UD_Ipswapd,0x00000000,0x000000000,OERROR},
    //{UD_Ipavgusb,0x00000000,0x000000000,OERROR},
    {UD_Ipush,0x00000000,0x000000000                 ,O1R},
    {UD_Ipusha,0x00000000,0x000000000                ,DEFALLR},
    {UD_Ipushad,0x00000000,0x000000000               ,DEFALLR},
    {UD_Ipushfw,0xFFFFFFFF,0x000000000               ,NONE},
    {UD_Ipushfd,0xFFFFFFFF,0x000000000               ,NONE},
    {UD_Ipushfq,0xFFFFFFFF,0x000000000               ,NONE},
    //{UD_Ipxor,0x00000000,0x000000000,OERROR},
    {UD_Ircl,0x00000000,CF | OF                      ,O1C | O2R},
    {UD_Ircr,0x00000000,CF | OF                      ,O1C | O2R},
    {UD_Irol,0x00000000,CF | OF                      ,O1C | O2R},
    {UD_Iror,0x00000000,CF | OF                      ,O1C | O2R},
    //{UD_Ircpps,0x00000000,0x000000000,OERROR},
    //{UD_Ircpss,0x00000000,0x000000000,OERROR},
    {UD_Irdmsr,0x00000000,0x000000000                ,DEFO1R|DEFO2W|DEFO3W,RCX,RDX,RAX},
    {UD_Irdpmc,0x00000000,0x000000000                ,DEFO1R|DEFO2W|DEFO3W,RCX,RDX,RAX},
    {UD_Irdtsc,0x00000000,0x000000000                ,DEFO1W|DEFO2W,RDX,RAX},
    //{UD_Irdtscp,0x00000000,0x000000000,OERROR},
    //{UD_Irepne,0x00000000,0x000000000,OERROR},
    //{UD_Irep,0x00000000,0x000000000,OERROR},
    {UD_Iret,0x00000000,0x000000000                  ,O1R},
    //{UD_Iretf,0x00000000,0x000000000,OERROR},
    //{UD_Irsm,0x00000000,0x000000000,OERROR},
    //{UD_Irsqrtps,0x00000000,0x000000000,OERROR},
    //{UD_Irsqrtss,0x00000000,0x000000000,OERROR},
    {UD_Isahf,0x00000000,SF | ZF | AF | PF | CF      ,DEFO1R,AH},
    //{UD_Isalc,0x00000000,0x000000000,OERROR},
    {UD_Isar,0x00000000,OF | SF | ZF | PF            ,O1C|O2R},
    {UD_Ishl,0x00000000,OF | SF | ZF | PF            ,O1C|O2R},
    {UD_Ishr,0x00000000,OF | SF | ZF | PF            ,O1C|O2R},
    {UD_Isbb,0x00000000,OF | SF | ZF | AF | PF | CF  ,O1C|O2R},
    {UD_Iscasb,DF,0x000000000                        ,DEFO1R|DEFO2R,AL,RDI},
    {UD_Iscasw,DF,0x000000000                        ,DEFO1R|DEFO2R,AX,RDI}, 
    {UD_Iscasd,DF,0x000000000                        ,DEFO1R|DEFO2R,EAX,RDI},  
    {UD_Iscasq,DF,0x000000000                        ,DEFO1R|DEFO2R,RAX,RDI},   
    {UD_Iseto,OF,0x000000000                         ,O1W},
    {UD_Isetno,OF,0x000000000                        ,O1W},
    {UD_Isetb,CF,0x000000000                         ,O1W},
    {UD_Isetae,CF,0x000000000                        ,O1W},
    {UD_Isetz,ZF,0x000000000                         ,O1W},
    {UD_Isetnz,ZF,0x000000000                        ,O1W},
    {UD_Isetbe,CF | ZF,0x000000000                   ,O1W},
    {UD_Iseta,CF | ZF,0x000000000                    ,O1W},
    {UD_Isets,SF,0x000000000                         ,O1W},
    {UD_Isetns,SF,0x000000000                        ,O1W},
    {UD_Isetp,PF,0x000000000                         ,O1W},
    {UD_Isetnp,PF,0x000000000                        ,O1W},
    {UD_Isetl,SF | OF,0x000000000                    ,O1W},
    {UD_Isetge,SF | OF,0x000000000                   ,O1W},
    {UD_Isetle,ZF | SF | OF,0x000000000              ,O1W},
    {UD_Isetg,ZF | SF | OF,0x000000000               ,O1W},
    //{UD_Isfence,0x00000000,0x000000000,OERROR},
    //{UD_Isgdt,0x00000000,0x000000000,OERROR},
    {UD_Ishld,0x00000000,CF | SF | PF | OF           ,O1C,O2C,O3R},
    {UD_Ishrd,0x00000000,CF | SF | PF | OF           ,O1C,O2C,O3R},
    //{UD_Ishufpd,0x00000000,0x000000000,OERROR},
    //{UD_Ishufps,0x00000000,0x000000000,OERROR},
    //{UD_Isidt,0x00000000,0x000000000,OERROR},
    //{UD_Isldt,0x00000000,0x000000000,OERROR},
    {UD_Ismsw,0x00000000,0x000000000                 ,O1W},
    //{UD_Isqrtps,0x00000000,0x000000000,OERROR},
    //{UD_Isqrtpd,0x00000000,0x000000000,OERROR},
    //{UD_Isqrtsd,0x00000000,0x000000000,OERROR},
    //{UD_Isqrtss,0x00000000,0x000000000,OERROR},
    {UD_Istc,0x00000000,CF                           ,NONE},
    {UD_Istd,0x00000000,DF                           ,NONE},
    //{UD_Istgi,0x00000000,0x000000000,OERROR},
    {UD_Isti,0x00000000,IF                           ,NONE},
    //{UD_Iskinit,0x00000000,0x000000000,OERROR},
    //{UD_Istmxcsr,0x00000000,0x000000000,OERROR},
    {UD_Istosb,DF,0x000000000                        ,DEFO1R|DEFO2R,AL,RDI},
    {UD_Istosw,DF,0x000000000                        ,DEFO1R|DEFO2R,AX,RDI}, 
    {UD_Istosd,DF,0x000000000                        ,DEFO1R|DEFO2R,EAX,RDI},
    {UD_Istosq,DF,0x000000000                        ,DEFO1R|DEFO2R,RAX,RDI},  
    {UD_Istr,0x00000000,0x000000000                  ,O1W},
    {UD_Isub,0x00000000,OF | SF | ZF | AF | PF | CF  ,O1C|O2R},
    //{UD_Isubpd,0x00000000,0x000000000,OERROR},
    //{UD_Isubps,0x00000000,0x000000000,OERROR},
    //{UD_Isubsd,0x00000000,0x000000000,OERROR},
    //{UD_Isubss,0x00000000,0x000000000,OERROR},
    //{UD_Iswapgs,0x00000000,0x000000000,OERROR},
    //{UD_Isyscall,0x00000000,0x000000000,OERROR},
    //{UD_Isysenter,0x00000000,0x000000000,OERROR},
    //{UD_Isysexit,0x00000000,0x000000000,OERROR},
    //{UD_Isysret,0x00000000,0x000000000,OERROR},
    {UD_Itest,0x00000000,OF | CF | SF | ZF | PF      ,O1R|O2R},
    //{UD_Iucomisd,0x00000000,0x000000000,OERROR},
    //{UD_Iucomiss,0x00000000,0x000000000,OERROR},
    //{UD_IUD2,0x00000000,0x000000000,OERROR},
    //{UD_Iunpckhpd,0x00000000,0x000000000,OERROR},
    //{UD_Iunpckhps,0x00000000,0x000000000,OERROR},
    //{UD_Iunpcklps,0x00000000,0x000000000,OERROR},
    //{UD_Iunpcklpd,0x00000000,0x000000000,OERROR},
    //{UD_Iverr,0x00000000,0x000000000,OERROR},
    //{UD_Iverw,0x00000000,0x000000000,OERROR},
    //{UD_Ivmcall,0x00000000,0x000000000,OERROR},
    //{UD_Ivmclear,0x00000000,0x000000000,OERROR},
    //{UD_Ivmxon,0x00000000,0x000000000,OERROR},
    //{UD_Ivmptrld,0x00000000,0x000000000,OERROR},
    //{UD_Ivmptrst,0x00000000,0x000000000,OERROR},
    //{UD_Ivmlaunch,0x00000000,0x000000000,OERROR},
    //{UD_Ivmresume,0x00000000,0x000000000,OERROR},
    //{UD_Ivmxoff,0x00000000,0x000000000,OERROR},
    //{UD_Ivmread,0x00000000,0x000000000,OERROR},
    //{UD_Ivmwrite,0x00000000,0x000000000,OERROR},
    //{UD_Ivmrun,0x00000000,0x000000000,OERROR},
    //{UD_Ivmmcall,0x00000000,0x000000000,OERROR},
    //{UD_Ivmload,0x00000000,0x000000000,OERROR},
    //{UD_Ivmsave,0x00000000,0x000000000,OERROR},
    //{UD_Iwait,0x00000000,0x000000000,OERROR},
    //{UD_Iwbinvd,0x00000000,0x000000000,OERROR},
    {UD_Iwrmsr,0x00000000,0x000000000                   ,DEFO1R|DEFO2R|DEFO3R,RDX,RAX,RCX},
    {UD_Ixadd,0x00000000,CF | PF | AF | SF | ZF | OF    ,O1C|O2C},
    {UD_Ixchg,0x00000000,0x000000000                    ,O1C|O2C},
    //{UD_Ixgetbv,0x00000000,0x000000000,OERROR},
    //{UD_Ixlatb,0x00000000,0x000000000,OERROR},
    {UD_Ixor,0x00000000,OF | CF | SF | ZF | PF          ,O1C|O2R}
    //{UD_Ixorpd,0x00000000,0x000000000,OERROR},
    //{UD_Ixorps,0x00000000,0x000000000,OERROR},
    //{UD_Ixcryptecb,0x00000000,0x000000000,OERROR},
    //{UD_Ixcryptcbc,0x00000000,0x000000000,OERROR},
    //{UD_Ixcryptctr,0x00000000,0x000000000,OERROR},
    //{UD_Ixcryptcfb,0x00000000,0x000000000,OERROR},
    //{UD_Ixcryptofb,0x00000000,0x000000000,OERROR},
    //{UD_Ixrstor,0x00000000,0x000000000,OERROR},
    //{UD_Ixsave,0x00000000,0x000000000,OERROR},
    //{UD_Ixsetbv,0x00000000,0x000000000,OERROR},
    //{UD_Ixsha1,0x00000000,0x000000000,OERROR},
    //{UD_Ixsha256,0x00000000,0x000000000,OERROR},
    //{UD_Ixstore,0x00000000,0x000000000,OERROR},
    //{UD_Iaesdec,0x00000000,0x000000000,OERROR},
    //{UD_Iaesdeclast,0x00000000,0x000000000,OERROR},
    //{UD_Iaesenc,0x00000000,0x000000000,OERROR},
    //{UD_Iaesenclast,0x00000000,0x000000000,OERROR},
    //{UD_Iaesimc,0x00000000,0x000000000,OERROR},
    //{UD_Iaeskeygenassist,0x00000000,0x000000000,OERROR},
    //{UD_Ipclmulqdq,0x00000000,0x000000000,OERROR},
    //{UD_Igetsec,0x00000000,0x000000000,OERROR},
    //{UD_Imovdqa,0x00000000,0x000000000,OERROR},
    //{UD_Imaskmovdqu,0x00000000,0x000000000,OERROR},
    //{UD_Imovdq2q,0x00000000,0x000000000,OERROR},
    //{UD_Imovdqu,0x00000000,0x000000000,OERROR},
    //{UD_Imovq2dq,0x00000000,0x000000000,OERROR},
    //{UD_Ipaddq,0x00000000,0x000000000,OERROR},
    //{UD_Ipsubq,0x00000000,0x000000000,OERROR},
    //{UD_Ipmul{UDq,0x00000000,0x000000000,OERROR},
    //{UD_Ipshufhw,0x00000000,0x000000000,OERROR},
    //{UD_Ipshuflw,0x00000000,0x000000000,OERROR},
    //{UD_Ipshufd,0x00000000,0x000000000,OERROR},
    //{UD_Ipslldq,0x00000000,0x000000000,OERROR},
    //{UD_Ipsrldq,0x00000000,0x000000000,OERROR},
    //{UD_Ipunpckhqdq,0x00000000,0x000000000,OERROR},
    //{UD_Ipunpcklqdq,0x00000000,0x000000000,OERROR},
    //{UD_Iaddsubpd,0x00000000,0x000000000,OERROR},
    //{UD_Iaddsubps,0x00000000,0x000000000,OERROR},
    //{UD_Ihaddpd,0x00000000,0x000000000,OERROR},
    //{UD_Ihaddps,0x00000000,0x000000000,OERROR},
    //{UD_Ihsubpd,0x00000000,0x000000000,OERROR},
    //{UD_Ihsubps,0x00000000,0x000000000,OERROR},
    //{UD_Imovddup,0x00000000,0x000000000,OERROR},
    //{UD_Imovshdup,0x00000000,0x000000000,OERROR},
    //{UD_Imovsldup,0x00000000,0x000000000,OERROR},
    //{UD_Ipabsb,0x00000000,0x000000000,OERROR},
    //{UD_Ipabsw,0x00000000,0x000000000,OERROR},
    //{UD_Ipabsd,0x00000000,0x000000000,OERROR},
    //{UD_Ipshufb,0x00000000,0x000000000,OERROR},
    //{UD_Iphaddw,0x00000000,0x000000000,OERROR},
    //{UD_Iphaddd,0x00000000,0x000000000,OERROR},
    //{UD_Iphaddsw,0x00000000,0x000000000,OERROR},
    //{UD_Ipmaddubsw,0x00000000,0x000000000,OERROR},
    //{UD_Iphsubw,0x00000000,0x000000000,OERROR},
    //{UD_Iphsubd,0x00000000,0x000000000,OERROR},
    //{UD_Iphsubsw,0x00000000,0x000000000,OERROR},
    //{UD_Ipsignb,0x00000000,0x000000000,OERROR},
    //{UD_Ipsignd,0x00000000,0x000000000,OERROR},
    //{UD_Ipsignw,0x00000000,0x000000000,OERROR},
    //{UD_Ipmulhrsw,0x00000000,0x000000000,OERROR},
    //{UD_Ipalignr,0x00000000,0x000000000,OERROR},
    //{UD_Ipblendvb,0x00000000,0x000000000,OERROR},
    //{UD_Ipmuldq,0x00000000,0x000000000,OERROR},
    //{UD_Ipminsb,0x00000000,0x000000000,OERROR},
    //{UD_Ipminsd,0x00000000,0x000000000,OERROR},
    //{UD_Ipminuw,0x00000000,0x000000000,OERROR},
    //{UD_Ipmin{UD,0x00000000,0x000000000,OERROR},
    //{UD_Ipmaxsb,0x00000000,0x000000000,OERROR},
    //{UD_Ipmaxsd,0x00000000,0x000000000,OERROR},
    //{UD_Ipmax{UD,0x00000000,0x000000000,OERROR},
    //{UD_Ipmaxuw,0x00000000,0x000000000,OERROR},
    //{UD_Ipmulld,0x00000000,0x000000000,OERROR},
    //{UD_Iphminposuw,0x00000000,0x000000000,OERROR},
    //{UD_Iroundps,0x00000000,0x000000000,OERROR},
    //{UD_Iroundpd,0x00000000,0x000000000,OERROR},
    //{UD_Iroundss,0x00000000,0x000000000,OERROR},
    //{UD_Iroundsd,0x00000000,0x000000000,OERROR},
    //{UD_Iblendpd,0x00000000,0x000000000,OERROR},
    //{UD_Ipblendw,0x00000000,0x000000000,OERROR},
    //{UD_Iblendps,0x00000000,0x000000000,OERROR},
    //{UD_Iblendvpd,0x00000000,0x000000000,OERROR},
    //{UD_Iblendvps,0x00000000,0x000000000,OERROR},
    //{UD_Idpps,0x00000000,0x000000000,OERROR},
    //{UD_Idppd,0x00000000,0x000000000,OERROR},
    //{UD_Impsadbw,0x00000000,0x000000000,OERROR},
    //{UD_Iextractps,0x00000000,0x000000000,OERROR},
    //{UD_Iinsertps,0x00000000,0x000000000,OERROR},
    //{UD_Imovntdqa,0x00000000,0x000000000,OERROR},
    //{UD_Ipackusdw,0x00000000,0x000000000,OERROR},
    //{UD_Ipmovsxbw,0x00000000,0x000000000,OERROR},
    //{UD_Ipmovsxbd,0x00000000,0x000000000,OERROR},
    //{UD_Ipmovsxbq,0x00000000,0x000000000,OERROR},
    //{UD_Ipmovsxwd,0x00000000,0x000000000,OERROR},
    //{UD_Ipmovsxwq,0x00000000,0x000000000,OERROR},
    //{UD_Ipmovsxdq,0x00000000,0x000000000,OERROR},
    //{UD_Ipmovzxbw,0x00000000,0x000000000,OERROR},
    //{UD_Ipmovzxbd,0x00000000,0x000000000,OERROR},
    //{UD_Ipmovzxbq,0x00000000,0x000000000,OERROR},
    //{UD_Ipmovzxwd,0x00000000,0x000000000,OERROR},
    //{UD_Ipmovzxwq,0x00000000,0x000000000,OERROR},
    //{UD_Ipmovzxdq,0x00000000,0x000000000,OERROR},
    //{UD_Ipcmpeqq,0x00000000,0x000000000,OERROR},
    //{UD_Ipopcnt,0x00000000,0x000000000,OERROR},
    //{UD_Iptest,0x00000000,0x000000000,OERROR},
   // {UD_Ipcmpestri,0x00000000,0x000000000,OERROR},
    //{UD_Ipcmpestrm,0x00000000,0x000000000,OERROR},
    //{UD_Ipcmpgtq,0x00000000,0x000000000,OERROR},
    //{UD_Ipcmpistri,0x00000000,0x000000000,OERROR},
    //{UD_Ipcmpistrm,0x00000000,0x000000000,OERROR},
    //{UD_Imovbe,0x00000000,0x000000000,OERROR},
    //{UD_Icrc32,0x00000000,0x00000000}

};

class X86CodeAnalysis : public Analysis
{
 X86CodeAnalysis(ud_t & u)
 {
   std::vector <X86AnalysisOption*> arr;
   for (int i = 0 ; i < sizeof(X86AnalysisTable)/sizeof(X86AnalysisOption) ; i++)
   {
      X86AnalysisOption & o = X86AnalysisTable[i];
      if (u.mnemonic == o.get_mnemonic())
      {
         arr.push_back(&o);
      }
   }
 }
 ~X86CodeAnalysis()
 {

 }
 typedef X86AnalysisOption AnalysisOption;
};

*/
#endif /* end of include guard: ADVANCEDANALYSIS_HPP_2IOLFAJY */
