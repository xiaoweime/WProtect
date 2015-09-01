#include <LuaEquivalentReplacement.h>
#include <udis86.h>

Assembl *Asm;
char asmcmd[256];

static int lua_assemble(lua_State *L)
{
	if (!lua_isstring(L,-1))
	{
		fprintf(stderr,"Assemble参数不匹配!");
	}
	const char *lua_asm_buf = lua_tostring(L,-1);
	char asmbuf[256];
	strcpy(asmbuf,lua_asm_buf);
	//char perror[256];

	//int size = Assemble((char*)asm_buf,ip+g_size,&model,0,0,perror);
	if (Asm->Assemble(asmbuf) != -1)
		lua_pushboolean(L,1);
	else
	{
		fprintf(stderr,"Assemble指令不正确:%s,原指令\r\n",asmbuf);
		lua_pushboolean(L,0);
		return 1;
	}
#ifdef DEBUG
	printf("asm:%s\r\n",asmbuf);
#endif
	return 1;
}

static int lua_oldcode(lua_State *L)
{
	Asm->Assemble(asmcmd);
	return 1;
}

static int lua_rand(lua_State *L)
{
	lua_pushinteger(L,rand());
	return 1;
}

void error(lua_State *L,const char *fmt,...)
{
	va_list argp;
	va_start(argp,fmt);
	vfprintf(stderr,fmt,argp);
	va_end(argp);
	lua_close(L);
	exit(1);
}

LuaInterface::LuaInterface()
{
	Asm = &a;
	L = luaL_newstate();
	if( luaL_loadfile(L,"wprotect_config.lua") || lua_pcall(L,0,0,0))
	{
		error (L,"cannot run config. file:%s\r\n",lua_tostring(L,-1));
	}
	luaL_openlibs(L);
	lua_register(L,"Assemble",lua_assemble);
	lua_register(L,"OldCode",lua_oldcode);
	lua_register(L,"Rand",lua_rand);
	call_lua_fuc("initializer");
}

LuaInterface::~LuaInterface()
{

}


bool LuaInterface::call_lua_fuc(const char * fucname)
{
	lua_getglobal(L,fucname);
	if (0 != lua_iscfunction(L,-1))
	{
		//fprintf(stderr,"lua文件没有找到:%s函数\r\n",fucname);
		fprintf(stderr,"没有找到:%s函数\r\n",fucname);
		return false;
	}
	int top = lua_gettop(L);
	if (0 != lua_pcall(L,0,0,0))
	{
		//fprintf(stderr,"lua文件没有找到:%s函数\r\n",fucname);
		//fprintf(stderr,"lua文件没有找到:%s函数\r\n",fucname);
		FILE *file = fopen("lua fuc error.log","wb");
		const char * perror = lua_tostring(L,-1);
		fwrite(perror,1,strlen(perror),file);
		error(L,lua_tostring(L,-1));
		fclose(file);
		return false;
	}
	return true;
}

char * get_base_register(ud_operand ud_op)
{
	switch (ud_op.base)
	{
	case UD_R_EAX:	return "eax";
	case UD_R_EBX:  return "ebx";
	case UD_R_ECX:  return "ecx";
	case UD_R_EDX:  return "edx";
	case UD_R_EBP:  return "ebp";
	case UD_R_ESP:  return "esp";
	case UD_R_EDI:  return "edi";
	case UD_R_ESI:  return "esi";
	case UD_R_AX:   return "ax";
	case UD_R_BX:   return "bx";
	case UD_R_CX:   return "cx";
	case UD_R_DX:   return "dx";
	case UD_R_SP:   return "sp";
	case UD_R_BP:   return "bp";
	case UD_R_SI:   return "si";
	case UD_R_DI:   return "di";
	case UD_R_AL:   return "al";
	case UD_R_AH:   return "ah";
	case UD_R_BL:   return "bl";
	case UD_R_BH:   return "bh";
	case UD_R_CL:   return "cl";
	case UD_R_CH:   return "ch";
	case UD_R_DL:   return "dl";
	case UD_R_DH:   return "dh";
	}
	return "";
}

char * get_index_register(ud_operand ud_op)
{
	switch (ud_op.index)
	{
	case UD_R_EAX:	return "eax";
	case UD_R_EBX:  return "ebx";
	case UD_R_ECX:  return "ecx";
	case UD_R_EDX:  return "edx";
	case UD_R_EBP:  return "ebp";
	case UD_R_ESP:  return "esp";
	case UD_R_EDI:  return "edi";
	case UD_R_ESI:  return "esi";
	case UD_R_AX:   return "ax";
	case UD_R_BX:   return "bx";
	case UD_R_CX:   return "cx";
	case UD_R_DX:   return "dx";
	case UD_R_SP:   return "sp";
	case UD_R_BP:   return "bp";
	case UD_R_SI:   return "si";
	case UD_R_DI:   return "di";
	case UD_R_AL:   return "al";
	case UD_R_AH:   return "ah";
	case UD_R_BL:   return "bl";
	case UD_R_BH:   return "bh";
	case UD_R_CL:   return "cl";
	case UD_R_CH:   return "ch";
	case UD_R_DL:   return "dl";
	case UD_R_DH:   return "dh";
	}
	return "";
}

unsigned long LuaInterface::get_jcc_addr(ud_t ud_obj)
{
	return (ud_obj.pc + (ud_obj.operand[0].size == 8 ? ud_obj.operand[0].lval.sbyte : ud_obj.operand[0].lval.sdword)); 
}

void LuaInterface::set_jcc(pCodeInformation info,ud_t ud_obj,const char *opname)
{
	if (ud_obj.operand[0].type == UD_OP_IMM || ud_obj.operand[0].type == UD_OP_JIMM)
	{
		char label[256];
		unsigned long jmpoffset = get_jcc_addr(ud_obj);
		if (info->base < jmpoffset && info->size + info->base > jmpoffset)
		{
			//sprintf(label,"call L%08x",jmpoffset);
			sprintf(label,"%s L%08x",opname,jmpoffset);
			a.Assemble(label);
		}
		else
		{
			a.Assemble(ud_obj.insn_buffer);
		}
	}
	else
	{
		//call_lua_fuc("call");
		call_lua_fuc(opname);
	}
};
pCodeInformation LuaInterface::lua_equivalent_replacement(pCodeInformation info,unsigned long imagebase)
{
    srand((int)time(0));
    
	ud_t ud_obj;
	ud_init(&ud_obj);
	ud_set_mode(&ud_obj, 32);
	ud_set_pc(&ud_obj,info->base);
	ud_set_input_buffer(&ud_obj, info->buf, info->size);
	ud_set_syntax(&ud_obj, UD_SYN_INTEL);
   while (ud_disassemble(&ud_obj) != 0)
   {
	   if (ud_obj.mnemonic == UD_Ipush &&ud_obj.operand[0].type == UD_OP_IMM)
	   {
		   sprintf(ud_obj.insn_buffer,"push 0%08x",ud_obj.operand[0].size == 8 ? ud_obj.operand[0].lval.sbyte : ud_obj.operand[0].lval.sdword); //如果是dword会显示大小比如push dword 123456
	   }
	   if (ud_obj.operand[0].type == UD_OP_IMM )
	   {
		   if (ud_obj.operand[0].lval.sdword >= info->base && ud_obj.operand[0].lval.sdword <= info->base + info->size)
		   {
			   printf("类似需要重定位的代码我就不帮忙了自己搞定,地址:%08x",info->base + a.get_code_size());
			   char c;
			   scanf("%c",&c);
			   if (c == 'y')
			   {
				   //char opop[50];
				   //if (opop)
					  // sprintf(opop,"%s L%08x",ud_lookup_mnemonic(ud_obj.mnemonic),ud_obj.operand[0].lval.sdword);
				   //a.Assemble(opop);
			   }
		   }
	   }
	   
	   strcpy(asmcmd,ud_obj.insn_buffer);
	   char label[20];
	   sprintf(label,"L%08x:",ud_obj.insn_offset);
	   a.Assemble(label);

	   lua_pushstring(L,ud_lookup_mnemonic(ud_obj.mnemonic));
	   lua_setglobal(L,"MNEMONIC");
       	for (int i = 0;i<3;i++)
		{
			char op[0x10];
			switch (ud_obj.operand[i].type)
			{
			case UD_OP_IMM:
				{
					lua_pushstring(L,"IMM");
					sprintf(op,"op%d_type",i+1);
					lua_setglobal(L,op);
	
					sprintf(op,"0%x",ud_obj.operand[i].size == 32 ? ud_obj.operand[i].lval.sdword : ud_obj.operand[i].lval.sbyte);
					//lua_pushstring(L,get_base_register(ud_obj.operand[i]));
					lua_pushstring(L,op);
					sprintf(op,"IMM%d",i+1);
					lua_setglobal(L,op);
					break;
				}
			case UD_OP_MEM:
				{
					lua_pushnumber(L,ud_obj.operand[i].size);
					lua_setglobal(L,"SIZE");
					
					lua_pushstring(L,"MEM");
					sprintf(op,"op%d_type",i+1);
					lua_setglobal(L,op);

					lua_pushstring(L,get_base_register(ud_obj.operand[i]));
					sprintf(op,"BASE%d",i+1);
					lua_setglobal(L,op);

					lua_pushstring(L,get_index_register(ud_obj.operand[i]));
					sprintf(op,"INDEX%d",i+1);
					lua_setglobal(L,op);

					sprintf(op,"0%x",ud_obj.operand[0].scale);
					lua_pushstring(L,op);
					sprintf(op,"SCALE%d",i+1);
					lua_setglobal(L,op);

					sprintf(op,"0%x",ud_obj.operand[i].offset == 32 ? ud_obj.operand[i].lval.sdword : ud_obj.operand[i].lval.sbyte);
					lua_pushstring(L,op);
					sprintf(op,"LVAL%d",i+1);
					lua_setglobal(L,op);
				
					break;
				}
			case UD_OP_REG:
				{
					lua_pushstring(L,"REG");
					sprintf(op,"op%d_type",i+1);
					lua_setglobal(L,op);

					lua_pushstring(L,get_base_register(ud_obj.operand[i]));
					sprintf(op,"REG%d",i+1);
					lua_setglobal(L,op);
					break;
				}
			}
		}
		switch (ud_obj.mnemonic)
		{
			case  UD_I3dnow: { call_lua_fuc("_3dnow");break;}
			case  UD_Iaaa: { call_lua_fuc("aaa");break;}
			case  UD_Iaad: { call_lua_fuc("aad");break;}
			case  UD_Iaam: { call_lua_fuc("aam");break;}
			case  UD_Iaas: { call_lua_fuc("aas");break;}
			case  UD_Iadc: { call_lua_fuc("adc");break;}
			case  UD_Iadd: { call_lua_fuc("add");break;}
			case  UD_Iaddpd: { call_lua_fuc("addpd");break;}
			case  UD_Iaddps: { call_lua_fuc("addps");break;}
			case  UD_Iaddsd: { call_lua_fuc("addsd");break;}
			case  UD_Iaddss: { call_lua_fuc("addss");break;}
			case  UD_Iaddsubpd: { call_lua_fuc("addsubpd");break;}
			case  UD_Iaddsubps: { call_lua_fuc("addsubps");break;}
			case  UD_Iand: { call_lua_fuc("_and");break;}
			case  UD_Iandpd: { call_lua_fuc("andpd");break;}
			case  UD_Iandps: { call_lua_fuc("andps");break;}
			case  UD_Iandnpd: { call_lua_fuc("andnpd");break;}
			case  UD_Iandnps: { call_lua_fuc("andnps");break;}
			case  UD_Iarpl: { call_lua_fuc("arpl");break;}
			case  UD_Imovsxd: { call_lua_fuc("movsxd");break;}
			case  UD_Ibound: { call_lua_fuc("bound");break;}
			case  UD_Ibsf: { call_lua_fuc("bsf");break;}
			case  UD_Ibsr: { call_lua_fuc("bsr");break;}
			case  UD_Ibswap: { call_lua_fuc("bswap");break;}
			case  UD_Ibt: { call_lua_fuc("bt");break;}
			case  UD_Ibtc: { call_lua_fuc("btc");break;}
			case  UD_Ibtr: { call_lua_fuc("btr");break;}
			case  UD_Ibts: { call_lua_fuc("bts");break;}
			//case  UD_Icall: { call_lua_fuc("call");break;}
		    case  UD_Icall: { 
				//if (ud_obj.operand[0].type == UD_OP_IMM || ud_obj.operand[0].type == UD_OP_JIMM)
				//{
				//	unsigned long jmpoffset = get_jcc_addr(ud_obj);
				//	if (info->base < jmpoffset && info->size + info->base > jmpoffset)
				//	{
				//		sprintf(label,"call L%08x",jmpoffset);
				//		a.Assemble(label);
				//	}
				//	else
				//	{
				//		a.Assemble(ud_obj.insn_buffer);
				//	}
				//}
				//else
				//{
				//	call_lua_fuc("call");
				//}
				set_jcc(info,ud_obj,"call");
				break;
							}
			//case  UD_Icall: { for (int i=0;i<8;i++) {g_buf[g_size+i] = 0x90;} pInstructionList list = NULL;
			//	add_instruction_block_list(add_instruction_list(list,&ud_obj));g_size+=8; break;}
			case  UD_Icbw: { call_lua_fuc("cbw");break;}
			case  UD_Icwde: { call_lua_fuc("cwde");break;}
			case  UD_Icdqe: { call_lua_fuc("cdqe");break;}
			case  UD_Iclc: { call_lua_fuc("clc");break;}
			case  UD_Icld: { call_lua_fuc("cld");break;}
			case  UD_Iclflush: { call_lua_fuc("clflush");break;}
			case  UD_Iclgi: { call_lua_fuc("clgi");break;}
			case  UD_Icli: { call_lua_fuc("cli");break;}
			case  UD_Iclts: { call_lua_fuc("clts");break;}
			case  UD_Icmc: { call_lua_fuc("cmc");break;}
			case  UD_Icmovo: { call_lua_fuc("cmovo");break;}
			case  UD_Icmovno: { call_lua_fuc("cmovno");break;}
			case  UD_Icmovb: { call_lua_fuc("cmovb");break;}
			case  UD_Icmovae: { call_lua_fuc("cmovae");break;}
			case  UD_Icmovz: { call_lua_fuc("cmovz");break;}
			case  UD_Icmovnz: { call_lua_fuc("cmovnz");break;}
			case  UD_Icmovbe: { call_lua_fuc("cmovbe");break;}
			case  UD_Icmova: { call_lua_fuc("cmova");break;}
			case  UD_Icmovs: { call_lua_fuc("cmovs");break;}
			case  UD_Icmovns: { call_lua_fuc("cmovns");break;}
			case  UD_Icmovp: { call_lua_fuc("cmovp");break;}
			case  UD_Icmovnp: { call_lua_fuc("cmovnp");break;}
			case  UD_Icmovl: { call_lua_fuc("cmovl");break;}
			case  UD_Icmovge: { call_lua_fuc("cmovge");break;}
			case  UD_Icmovle: { call_lua_fuc("cmovle");break;}
			case  UD_Icmovg: { call_lua_fuc("cmovg");break;}
			case  UD_Icmp: { call_lua_fuc("cmp");break;}
			case  UD_Icmppd: { call_lua_fuc("cmppd");break;}
			case  UD_Icmpps: { call_lua_fuc("cmpps");break;}
			case  UD_Icmpsb: { call_lua_fuc("cmpsb");break;}
			case  UD_Icmpsw: { call_lua_fuc("cmpsw");break;}
			case  UD_Icmpsd: { call_lua_fuc("cmpsd");break;}
			case  UD_Icmpsq: { call_lua_fuc("cmpsq");break;}
			case  UD_Icmpss: { call_lua_fuc("cmpss");break;}
			case  UD_Icmpxchg: { call_lua_fuc("cmpxchg");break;}
			case  UD_Icmpxchg8b: { call_lua_fuc("cmpxchg8b");break;}
			case  UD_Icomisd: { call_lua_fuc("comisd");break;}
			case  UD_Icomiss: { call_lua_fuc("comiss");break;}
			case  UD_Icpuid: { call_lua_fuc("cpuid");break;}
			case  UD_Icvtdq2pd: { call_lua_fuc("cvtdq2pd");break;}
			case  UD_Icvtdq2ps: { call_lua_fuc("cvtdq2ps");break;}
			case  UD_Icvtpd2dq: { call_lua_fuc("cvtpd2dq");break;}
			case  UD_Icvtpd2pi: { call_lua_fuc("cvtpd2pi");break;}
			case  UD_Icvtpd2ps: { call_lua_fuc("cvtpd2ps");break;}
			case  UD_Icvtpi2ps: { call_lua_fuc("cvtpi2ps");break;}
			case  UD_Icvtpi2pd: { call_lua_fuc("cvtpi2pd");break;}
			case  UD_Icvtps2dq: { call_lua_fuc("cvtps2dq");break;}
			case  UD_Icvtps2pi: { call_lua_fuc("cvtps2pi");break;}
			case  UD_Icvtps2pd: { call_lua_fuc("cvtps2pd");break;}
			case  UD_Icvtsd2si: { call_lua_fuc("cvtsd2si");break;}
			case  UD_Icvtsd2ss: { call_lua_fuc("cvtsd2ss");break;}
			case  UD_Icvtsi2ss: { call_lua_fuc("cvtsi2ss");break;}
			case  UD_Icvtss2si: { call_lua_fuc("cvtss2si");break;}
			case  UD_Icvtss2sd: { call_lua_fuc("cvtss2sd");break;}
			case  UD_Icvttpd2pi: { call_lua_fuc("cvttpd2pi");break;}
			case  UD_Icvttpd2dq: { call_lua_fuc("cvttpd2dq");break;}
			case  UD_Icvttps2dq: { call_lua_fuc("cvttps2dq");break;}
			case  UD_Icvttps2pi: { call_lua_fuc("cvttps2pi");break;}
			case  UD_Icvttsd2si: { call_lua_fuc("cvttsd2si");break;}
			case  UD_Icvtsi2sd: { call_lua_fuc("cvtsi2sd");break;}
			case  UD_Icvttss2si: { call_lua_fuc("cvttss2si");break;}
			case  UD_Icwd: { call_lua_fuc("cwd");break;}
			case  UD_Icdq: { call_lua_fuc("cdq");break;}
			case  UD_Icqo: { call_lua_fuc("cqo");break;}
			case  UD_Idaa: { call_lua_fuc("daa");break;}
			case  UD_Idas: { call_lua_fuc("das");break;}
			case  UD_Idec: { call_lua_fuc("dec");break;}
			case  UD_Idiv: { call_lua_fuc("div");break;}
			case  UD_Idivpd: { call_lua_fuc("divpd");break;}
			case  UD_Idivps: { call_lua_fuc("divps");break;}
			case  UD_Idivsd: { call_lua_fuc("divsd");break;}
			case  UD_Idivss: { call_lua_fuc("divss");break;}
			case  UD_Iemms: { call_lua_fuc("emms");break;}
			case  UD_Ienter: { call_lua_fuc("enter");break;}
			case  UD_If2xm1: { call_lua_fuc("f2xm1");break;}
			case  UD_Ifabs: { call_lua_fuc("fabs");break;}
			case  UD_Ifadd: { call_lua_fuc("fadd");break;}
			case  UD_Ifaddp: { call_lua_fuc("faddp");break;}
			case  UD_Ifbld: { call_lua_fuc("fbld");break;}
			case  UD_Ifbstp: { call_lua_fuc("fbstp");break;}
			case  UD_Ifchs: { call_lua_fuc("fchs");break;}
			case  UD_Ifclex: { call_lua_fuc("fclex");break;}
			case  UD_Ifcmovb: { call_lua_fuc("fcmovb");break;}
			case  UD_Ifcmove: { call_lua_fuc("fcmove");break;}
			case  UD_Ifcmovbe: { call_lua_fuc("fcmovbe");break;}
			case  UD_Ifcmovu: { call_lua_fuc("fcmovu");break;}
			case  UD_Ifcmovnb: { call_lua_fuc("fcmovnb");break;}
			case  UD_Ifcmovne: { call_lua_fuc("fcmovne");break;}
			case  UD_Ifcmovnbe: { call_lua_fuc("fcmovnbe");break;}
			case  UD_Ifcmovnu: { call_lua_fuc("fcmovnu");break;}
			case  UD_Ifucomi: { call_lua_fuc("fucomi");break;}
			case  UD_Ifcom: { call_lua_fuc("fcom");break;}
			case  UD_Ifcom2: { call_lua_fuc("fcom2");break;}
			case  UD_Ifcomp3: { call_lua_fuc("fcomp3");break;}
			case  UD_Ifcomi: { call_lua_fuc("fcomi");break;}
			case  UD_Ifucomip: { call_lua_fuc("fucomip");break;}
			case  UD_Ifcomip: { call_lua_fuc("fcomip");break;}
			case  UD_Ifcomp: { call_lua_fuc("fcomp");break;}
			case  UD_Ifcomp5: { call_lua_fuc("fcomp5");break;}
			case  UD_Ifcompp: { call_lua_fuc("fcompp");break;}
			case  UD_Ifcos: { call_lua_fuc("fcos");break;}
			case  UD_Ifdecstp: { call_lua_fuc("fdecstp");break;}
			case  UD_Ifdiv: { call_lua_fuc("fdiv");break;}
			case  UD_Ifdivp: { call_lua_fuc("fdivp");break;}
			case  UD_Ifdivr: { call_lua_fuc("fdivr");break;}
			case  UD_Ifdivrp: { call_lua_fuc("fdivrp");break;}
			case  UD_Ifemms: { call_lua_fuc("femms");break;}
			case  UD_Iffree: { call_lua_fuc("ffree");break;}
			case  UD_Iffreep: { call_lua_fuc("ffreep");break;}
			case  UD_Ificom: { call_lua_fuc("ficom");break;}
			case  UD_Ificomp: { call_lua_fuc("ficomp");break;}
			case  UD_Ifild: { call_lua_fuc("fild");break;}
			case  UD_Ifncstp: { call_lua_fuc("fncstp");break;}
			case  UD_Ifninit: { call_lua_fuc("fninit");break;}
			case  UD_Ifiadd: { call_lua_fuc("fiadd");break;}
			case  UD_Ifidivr: { call_lua_fuc("fidivr");break;}
			case  UD_Ifidiv: { call_lua_fuc("fidiv");break;}
			case  UD_Ifisub: { call_lua_fuc("fisub");break;}
			case  UD_Ifisubr: { call_lua_fuc("fisubr");break;}
			case  UD_Ifist: { call_lua_fuc("fist");break;}
			case  UD_Ifistp: { call_lua_fuc("fistp");break;}
			case  UD_Ifisttp: { call_lua_fuc("fisttp");break;}
			case  UD_Ifld: { call_lua_fuc("fld");break;}
			case  UD_Ifld1: { call_lua_fuc("fld1");break;}
			case  UD_Ifldl2t: { call_lua_fuc("fldl2t");break;}
			case  UD_Ifldl2e: { call_lua_fuc("fldl2e");break;}
			case  UD_Ifldlpi: { call_lua_fuc("fldlpi");break;}
			case  UD_Ifldlg2: { call_lua_fuc("fldlg2");break;}
			case  UD_Ifldln2: { call_lua_fuc("fldln2");break;}
			case  UD_Ifldz: { call_lua_fuc("fldz");break;}
			case  UD_Ifldcw: { call_lua_fuc("fldcw");break;}
			case  UD_Ifldenv: { call_lua_fuc("fldenv");break;}
			case  UD_Ifmul: { call_lua_fuc("fmul");break;}
			case  UD_Ifmulp: { call_lua_fuc("fmulp");break;}
			case  UD_Ifimul: { call_lua_fuc("fimul");break;}
			case  UD_Ifnop: { call_lua_fuc("fnop");break;}
			case  UD_Ifpatan: { call_lua_fuc("fpatan");break;}
			case  UD_Ifprem: { call_lua_fuc("fprem");break;}
			case  UD_Ifprem1: { call_lua_fuc("fprem1");break;}
			case  UD_Ifptan: { call_lua_fuc("fptan");break;}
			case  UD_Ifrndint: { call_lua_fuc("frndint");break;}
			case  UD_Ifrstor: { call_lua_fuc("frstor");break;}
			case  UD_Ifnsave: { call_lua_fuc("fnsave");break;}
			case  UD_Ifscale: { call_lua_fuc("fscale");break;}
			case  UD_Ifsin: { call_lua_fuc("fsin");break;}
			case  UD_Ifsincos: { call_lua_fuc("fsincos");break;}
			case  UD_Ifsqrt: { call_lua_fuc("fsqrt");break;}
			case  UD_Ifstp: { call_lua_fuc("fstp");break;}
			case  UD_Ifstp1: { call_lua_fuc("fstp1");break;}
			case  UD_Ifstp8: { call_lua_fuc("fstp8");break;}
			case  UD_Ifstp9: { call_lua_fuc("fstp9");break;}
			case  UD_Ifst: { call_lua_fuc("fst");break;}
			case  UD_Ifnstcw: { call_lua_fuc("fnstcw");break;}
			case  UD_Ifnstenv: { call_lua_fuc("fnstenv");break;}
			case  UD_Ifnstsw: { call_lua_fuc("fnstsw");break;}
			case  UD_Ifsub: { call_lua_fuc("fsub");break;}
			case  UD_Ifsubp: { call_lua_fuc("fsubp");break;}
			case  UD_Ifsubr: { call_lua_fuc("fsubr");break;}
			case  UD_Ifsubrp: { call_lua_fuc("fsubrp");break;}
			case  UD_Iftst: { call_lua_fuc("ftst");break;}
			case  UD_Ifucom: { call_lua_fuc("fucom");break;}
			case  UD_Ifucomp: { call_lua_fuc("fucomp");break;}
			case  UD_Ifucompp: { call_lua_fuc("fucompp");break;}
			case  UD_Ifxam: { call_lua_fuc("fxam");break;}
			case  UD_Ifxch: { call_lua_fuc("fxch");break;}
			case  UD_Ifxch4: { call_lua_fuc("fxch4");break;}
			case  UD_Ifxch7: { call_lua_fuc("fxch7");break;}
			case  UD_Ifxrstor: { call_lua_fuc("fxrstor");break;}
			case  UD_Ifxsave: { call_lua_fuc("fxsave");break;}
			case  UD_Ifpxtract: { call_lua_fuc("fpxtract");break;}
			case  UD_Ifyl2x: { call_lua_fuc("fyl2x");break;}
			case  UD_Ifyl2xp1: { call_lua_fuc("fyl2xp1");break;}
			case  UD_Ihaddpd: { call_lua_fuc("haddpd");break;}
			case  UD_Ihaddps: { call_lua_fuc("haddps");break;}
			case  UD_Ihlt: { call_lua_fuc("hlt");break;}
			case  UD_Ihsubpd: { call_lua_fuc("hsubpd");break;}
			case  UD_Ihsubps: { call_lua_fuc("hsubps");break;}
			case  UD_Iidiv: { call_lua_fuc("idiv");break;}
			case  UD_Iin: { call_lua_fuc("_in");break;}
			case  UD_Iimul: { call_lua_fuc("imul");break;}
			case  UD_Iinc: { call_lua_fuc("inc");break;}
			case  UD_Iinsb: { call_lua_fuc("insb");break;}
			case  UD_Iinsw: { call_lua_fuc("insw");break;}
			case  UD_Iinsd: { call_lua_fuc("insd");break;}
			case  UD_Iint1: { call_lua_fuc("int1");break;}
			case  UD_Iint3: { call_lua_fuc("int3");break;}
			case  UD_Iint: { call_lua_fuc("int");break;}
			case  UD_Iinto: { call_lua_fuc("into");break;}
			case  UD_Iinvd: { call_lua_fuc("invd");break;}
			case  UD_Iinvlpg: { call_lua_fuc("invlpg");break;}
			case  UD_Iinvlpga: { call_lua_fuc("invlpga");break;}
			case  UD_Iiretw: { call_lua_fuc("iretw");break;}
			case  UD_Iiretd: { call_lua_fuc("iretd");break;}
			case  UD_Iiretq: { call_lua_fuc("iretq");break;}
			//case  UD_Ijo: { call_lua_fuc("jo");break;}
			//case  UD_Ijno: { call_lua_fuc("jno");break;}
			//case  UD_Ijb: { call_lua_fuc("jb");break;}
			//case  UD_Ijae: { call_lua_fuc("jae");break;}
			//case  UD_Ijz: { call_lua_fuc("jz");break;}
			//case  UD_Ijnz: { call_lua_fuc("jnz");break;}
			//case  UD_Ijbe: { call_lua_fuc("jbe");break;}
			//case  UD_Ija: { call_lua_fuc("ja");break;}
			//case  UD_Ijs: { call_lua_fuc("js");break;}
			//case  UD_Ijns: { call_lua_fuc("jns");break;}
			//case  UD_Ijp: { call_lua_fuc("jp");break;}
			//case  UD_Ijnp: { call_lua_fuc("jnp");break;}
			//case  UD_Ijl: { call_lua_fuc("jl");break;}
			//case  UD_Ijge: { call_lua_fuc("jge");break;}
			//case  UD_Ijle: { call_lua_fuc("jle");break;}
			//case  UD_Ijg: { call_lua_fuc("jg");break;}
			//case  UD_Ijcxz: { call_lua_fuc("jcxz");break;}
			//case  UD_Ijecxz: { call_lua_fuc("jecxz");break;}
			//case  UD_Ijrcxz: { call_lua_fuc("jrcxz");break;}
			//case  UD_Ijmp: { call_lua_fuc("jmp");break;}
			case  UD_Ijo: { set_jcc(info,ud_obj,"jo");break;}
			case  UD_Ijno: { set_jcc(info,ud_obj,"jno");break;}
			case  UD_Ijb: { set_jcc(info,ud_obj,"jb");break;}
			case  UD_Ijae: { set_jcc(info,ud_obj,"jae");break;}
			case  UD_Ijz: { set_jcc(info,ud_obj,"jz");break;}
			case  UD_Ijnz: { set_jcc(info,ud_obj,"jnz");break;}
			case  UD_Ijbe: { set_jcc(info,ud_obj,"jbe");break;}
			case  UD_Ija: { set_jcc(info,ud_obj,"ja");break;}
			case  UD_Ijs: { set_jcc(info,ud_obj,"js");break;}
			case  UD_Ijns: { set_jcc(info,ud_obj,"jns");break;}
			case  UD_Ijp: { set_jcc(info,ud_obj,"jp");break;}
			case  UD_Ijnp: { set_jcc(info,ud_obj,"jnp");break;}
			case  UD_Ijl: { set_jcc(info,ud_obj,"jl");break;}
			case  UD_Ijge: { set_jcc(info,ud_obj,"jge");break;}
			case  UD_Ijle: { set_jcc(info,ud_obj,"jle");break;}
			case  UD_Ijg: { set_jcc(info,ud_obj,"jg");break;}
			case  UD_Ijcxz: { set_jcc(info,ud_obj,"jcxz");break;}
			case  UD_Ijecxz: { set_jcc(info,ud_obj,"jecxz");break;}
			case  UD_Ijrcxz: { set_jcc(info,ud_obj,"jrcxz");break;}
			case  UD_Ijmp: { set_jcc(info,ud_obj,"jmp");break;}

			//case  UD_Ijo: { for (int i=0;i<8;i++) {g_buf[g_size+i] = 0x90;} pInstructionList list = NULL;
			//	add_instruction_block_list(add_instruction_list(list,&ud_obj));g_size+=8; break;}
			//case  UD_Ijno: { for (int i=0;i<8;i++) {g_buf[g_size+i] = 0x90;} pInstructionList list = NULL;
			//	add_instruction_block_list(add_instruction_list(list,&ud_obj));g_size+=8; break;}
			//case  UD_Ijb:{ for (int i=0;i<8;i++) {g_buf[g_size+i] = 0x90;} pInstructionList list = NULL;
			//	add_instruction_block_list(add_instruction_list(list,&ud_obj));g_size+=8; break;}
			//case  UD_Ijae: { for (int i=0;i<8;i++) {g_buf[g_size+i] = 0x90;} pInstructionList list = NULL;
			//	add_instruction_block_list(add_instruction_list(list,&ud_obj));g_size+=8; break;}
			//case  UD_Ijz: { for (int i=0;i<8;i++) {g_buf[g_size+i] = 0x90;} pInstructionList list = NULL;
			//	add_instruction_block_list(add_instruction_list(list,&ud_obj));g_size+=8; break;}
			//case  UD_Ijnz: { for (int i=0;i<8;i++) {g_buf[g_size+i] = 0x90;} pInstructionList list = NULL;
			//	add_instruction_block_list(add_instruction_list(list,&ud_obj));g_size+=8; break;}
			//case  UD_Ijbe: { for (int i=0;i<8;i++) {g_buf[g_size+i] = 0x90;} pInstructionList list = NULL;
			//	add_instruction_block_list(add_instruction_list(list,&ud_obj));g_size+=8; break;}
			//case  UD_Ija: { for (int i=0;i<8;i++) {g_buf[g_size+i] = 0x90;} pInstructionList list = NULL;
			//	add_instruction_block_list(add_instruction_list(list,&ud_obj));g_size+=8; break;}
			//case  UD_Ijs: { for (int i=0;i<8;i++) {g_buf[g_size+i] = 0x90;} pInstructionList list = NULL;
			//	add_instruction_block_list(add_instruction_list(list,&ud_obj));g_size+=8; break;}
			//case  UD_Ijns: { for (int i=0;i<8;i++) {g_buf[g_size+i] = 0x90;} pInstructionList list = NULL;
			//	add_instruction_block_list(add_instruction_list(list,&ud_obj));g_size+=8; break;}
			//case  UD_Ijp: { for (int i=0;i<8;i++) {g_buf[g_size+i] = 0x90;} pInstructionList list = NULL;
			//	add_instruction_block_list(add_instruction_list(list,&ud_obj));g_size+=8; break;}
			//case  UD_Ijnp: { for (int i=0;i<8;i++) {g_buf[g_size+i] = 0x90;} pInstructionList list = NULL;
			//	add_instruction_block_list(add_instruction_list(list,&ud_obj));g_size+=8; break;}
			//case  UD_Ijl: { for (int i=0;i<8;i++) {g_buf[g_size+i] = 0x90;} pInstructionList list = NULL;
			//	add_instruction_block_list(add_instruction_list(list,&ud_obj));g_size+=8; break;}
			//case  UD_Ijge: { for (int i=0;i<8;i++) {g_buf[g_size+i] = 0x90;} pInstructionList list = NULL;
			//	add_instruction_block_list(add_instruction_list(list,&ud_obj));g_size+=8; break;}
			//case  UD_Ijle: { for (int i=0;i<8;i++) {g_buf[g_size+i] = 0x90;} pInstructionList list = NULL;
			//	add_instruction_block_list(add_instruction_list(list,&ud_obj));g_size+=8; break;}
			//case  UD_Ijg: { for (int i=0;i<8;i++) {g_buf[g_size+i] = 0x90;} pInstructionList list = NULL;
			//	add_instruction_block_list(add_instruction_list(list,&ud_obj));g_size+=8; break;}
			//case  UD_Ijcxz: { for (int i=0;i<8;i++) {g_buf[g_size+i] = 0x90;} pInstructionList list = NULL;
			//	add_instruction_block_list(add_instruction_list(list,&ud_obj));g_size+=8; break;}
			//case  UD_Ijecxz: { for (int i=0;i<8;i++) {g_buf[g_size+i] = 0x90;} pInstructionList list = NULL;
			//	add_instruction_block_list(add_instruction_list(list,&ud_obj));g_size+=8; break;}
			//case  UD_Ijrcxz: { for (int i=0;i<8;i++) {g_buf[g_size+i] = 0x90;} pInstructionList list = NULL;
			//	add_instruction_block_list(add_instruction_list(list,&ud_obj));g_size+=8; break;}
			//case  UD_Ijmp: { for (int i=0;i<8;i++) {g_buf[g_size+i] = 0x90;} pInstructionList list = NULL;
			//	add_instruction_block_list(add_instruction_list(list,&ud_obj));g_size+=8; break;}

			case  UD_Ilahf: { call_lua_fuc("lahf");break;}
			case  UD_Ilar: { call_lua_fuc("lar");break;}
			case  UD_Ilddqu: { call_lua_fuc("lddqu");break;}
			case  UD_Ildmxcsr: { call_lua_fuc("ldmxcsr");break;}
			case  UD_Ilds: { call_lua_fuc("lds");break;}
			case  UD_Ilea: { call_lua_fuc("lea");break;}
			case  UD_Iles: { call_lua_fuc("les");break;}
			case  UD_Ilfs: { call_lua_fuc("lfs");break;}
			case  UD_Ilgs: { call_lua_fuc("lgs");break;}
			case  UD_Ilidt: { call_lua_fuc("lidt");break;}
			case  UD_Ilss: { call_lua_fuc("lss");break;}
			case  UD_Ileave: { call_lua_fuc("leave");break;}
			case  UD_Ilfence: { call_lua_fuc("lfence");break;}
			case  UD_Ilgdt: { call_lua_fuc("lgdt");break;}
			case  UD_Illdt: { call_lua_fuc("lldt");break;}
			case  UD_Ilmsw: { call_lua_fuc("lmsw");break;}
			case  UD_Ilock: { call_lua_fuc("lock");break;}
			case  UD_Ilodsb: { call_lua_fuc("lodsb");break;}
			case  UD_Ilodsw: { call_lua_fuc("lodsw");break;}
			case  UD_Ilodsd: { call_lua_fuc("lodsd");break;}
			case  UD_Ilodsq: { call_lua_fuc("lodsq");break;}
			case  UD_Iloopnz: { call_lua_fuc("loopnz");break;}
			case  UD_Iloope: { call_lua_fuc("loope");break;}
			case  UD_Iloop: { call_lua_fuc("loop");break;}
			case  UD_Ilsl: { call_lua_fuc("lsl");break;}
			case  UD_Iltr: { call_lua_fuc("ltr");break;}
			case  UD_Imaskmovq: { call_lua_fuc("maskmovq");break;}
			case  UD_Imaxpd: { call_lua_fuc("maxpd");break;}
			case  UD_Imaxps: { call_lua_fuc("maxps");break;}
			case  UD_Imaxsd: { call_lua_fuc("maxsd");break;}
			case  UD_Imaxss: { call_lua_fuc("maxss");break;}
			case  UD_Imfence: { call_lua_fuc("mfence");break;}
			case  UD_Iminpd: { call_lua_fuc("minpd");break;}
			case  UD_Iminps: { call_lua_fuc("minps");break;}
			case  UD_Iminsd: { call_lua_fuc("minsd");break;}
			case  UD_Iminss: { call_lua_fuc("minss");break;}
			case  UD_Imonitor: { call_lua_fuc("monitor");break;}
			case  UD_Imov: { call_lua_fuc("mov");break;}
			case  UD_Imovapd: { call_lua_fuc("movapd");break;}
			case  UD_Imovaps: { call_lua_fuc("movaps");break;}
			case  UD_Imovd: { call_lua_fuc("movd");break;}
			case  UD_Imovddup: { call_lua_fuc("movddup");break;}
			case  UD_Imovdqa: { call_lua_fuc("movdqa");break;}
			case  UD_Imovdqu: { call_lua_fuc("movdqu");break;}
			case  UD_Imovdq2q: { call_lua_fuc("movdq2q");break;}
			case  UD_Imovhpd: { call_lua_fuc("movhpd");break;}
			case  UD_Imovhps: { call_lua_fuc("movhps");break;}
			case  UD_Imovlhps: { call_lua_fuc("movlhps");break;}
			case  UD_Imovlpd: { call_lua_fuc("movlpd");break;}
			case  UD_Imovlps: { call_lua_fuc("movlps");break;}
			case  UD_Imovhlps: { call_lua_fuc("movhlps");break;}
			case  UD_Imovmskpd: { call_lua_fuc("movmskpd");break;}
			case  UD_Imovmskps: { call_lua_fuc("movmskps");break;}
			case  UD_Imovntdq: { call_lua_fuc("movntdq");break;}
			case  UD_Imovnti: { call_lua_fuc("movnti");break;}
			case  UD_Imovntpd: { call_lua_fuc("movntpd");break;}
			case  UD_Imovntps: { call_lua_fuc("movntps");break;}
			case  UD_Imovntq: { call_lua_fuc("movntq");break;}
			case  UD_Imovq: { call_lua_fuc("movq");break;}
			case  UD_Imovqa: { call_lua_fuc("movqa");break;}
			case  UD_Imovq2dq: { call_lua_fuc("movq2dq");break;}
			case  UD_Imovsb: { call_lua_fuc("movsb");break;}
			case  UD_Imovsw: { call_lua_fuc("movsw");break;}
			case  UD_Imovsd: { call_lua_fuc("movsd");break;}
			case  UD_Imovsq: { call_lua_fuc("movsq");break;}
			case  UD_Imovsldup: { call_lua_fuc("movsldup");break;}
			case  UD_Imovshdup: { call_lua_fuc("movshdup");break;}
			case  UD_Imovss: { call_lua_fuc("movss");break;}
			case  UD_Imovsx: { call_lua_fuc("movsx");break;}
			case  UD_Imovupd: { call_lua_fuc("movupd");break;}
			case  UD_Imovups: { call_lua_fuc("movups");break;}
			case  UD_Imovzx: { call_lua_fuc("movzx");break;}
			case  UD_Imul: { call_lua_fuc("mul");break;}
			case  UD_Imulpd: { call_lua_fuc("mulpd");break;}
			case  UD_Imulps: { call_lua_fuc("mulps");break;}
			case  UD_Imulsd: { call_lua_fuc("mulsd");break;}
			case  UD_Imulss: { call_lua_fuc("mulss");break;}
			case  UD_Imwait: { call_lua_fuc("mwait");break;}
			case  UD_Ineg: { call_lua_fuc("neg");break;}
			case  UD_Inop: { call_lua_fuc("nop");break;}
			case  UD_Inot: { call_lua_fuc("_not");break;}
			case  UD_Ior: { call_lua_fuc("_or");break;}
			case  UD_Iorpd: { call_lua_fuc("orpd");break;}
			case  UD_Iorps: { call_lua_fuc("orps");break;}
			case  UD_Iout: { call_lua_fuc("out");break;}
			case  UD_Ioutsb: { call_lua_fuc("outsb");break;}
			case  UD_Ioutsw: { call_lua_fuc("outsw");break;}
			case  UD_Ioutsd: { call_lua_fuc("outsd");break;}
			case  UD_Ioutsq: { call_lua_fuc("outsq");break;}
			case  UD_Ipacksswb: { call_lua_fuc("packsswb");break;}
			case  UD_Ipackssdw: { call_lua_fuc("packssdw");break;}
			case  UD_Ipackuswb: { call_lua_fuc("packuswb");break;}
			case  UD_Ipaddb: { call_lua_fuc("paddb");break;}
			case  UD_Ipaddw: { call_lua_fuc("paddw");break;}
			case  UD_Ipaddq: { call_lua_fuc("paddq");break;}
			case  UD_Ipaddsb: { call_lua_fuc("paddsb");break;}
			case  UD_Ipaddsw: { call_lua_fuc("paddsw");break;}
			case  UD_Ipaddusb: { call_lua_fuc("paddusb");break;}
			case  UD_Ipaddusw: { call_lua_fuc("paddusw");break;}
			case  UD_Ipand: { call_lua_fuc("pand");break;}
			case  UD_Ipandn: { call_lua_fuc("pandn");break;}
			case  UD_Ipause: { call_lua_fuc("pause");break;}
			case  UD_Ipavgb: { call_lua_fuc("pavgb");break;}
			case  UD_Ipavgw: { call_lua_fuc("pavgw");break;}
			case  UD_Ipcmpeqb: { call_lua_fuc("pcmpeqb");break;}
			case  UD_Ipcmpeqw: { call_lua_fuc("pcmpeqw");break;}
			case  UD_Ipcmpeqd: { call_lua_fuc("pcmpeqd");break;}
			case  UD_Ipcmpgtb: { call_lua_fuc("pcmpgtb");break;}
			case  UD_Ipcmpgtw: { call_lua_fuc("pcmpgtw");break;}
			case  UD_Ipcmpgtd: { call_lua_fuc("pcmpgtd");break;}
			case  UD_Ipextrw: { call_lua_fuc("pextrw");break;}
			case  UD_Ipinsrw: { call_lua_fuc("pinsrw");break;}
			case  UD_Ipmaddwd: { call_lua_fuc("pmaddwd");break;}
			case  UD_Ipmaxsw: { call_lua_fuc("pmaxsw");break;}
			case  UD_Ipmaxub: { call_lua_fuc("pmaxub");break;}
			case  UD_Ipminsw: { call_lua_fuc("pminsw");break;}
			case  UD_Ipminub: { call_lua_fuc("pminub");break;}
			case  UD_Ipmovmskb: { call_lua_fuc("pmovmskb");break;}
			case  UD_Ipmulhuw: { call_lua_fuc("pmulhuw");break;}
			case  UD_Ipmulhw: { call_lua_fuc("pmulhw");break;}
			case  UD_Ipmullw: { call_lua_fuc("pmullw");break;}
			case  UD_Ipmuludq: { call_lua_fuc("pmuludq");break;}
			case  UD_Ipop: { call_lua_fuc("pop");break;}
			case  UD_Ipopa: { call_lua_fuc("popa");break;}
			case  UD_Ipopad: { call_lua_fuc("popad");break;}
			case  UD_Ipopfw: { call_lua_fuc("popfw");break;}
			case  UD_Ipopfd: { call_lua_fuc("popfd");break;}
			case  UD_Ipopfq: { call_lua_fuc("popfq");break;}
			case  UD_Ipor: { call_lua_fuc("por");break;}
			case  UD_Iprefetch: { call_lua_fuc("prefetch");break;}
			case  UD_Iprefetchnta: { call_lua_fuc("prefetchnta");break;}
			case  UD_Iprefetcht0: { call_lua_fuc("prefetcht0");break;}
			case  UD_Iprefetcht1: { call_lua_fuc("prefetcht1");break;}
			case  UD_Iprefetcht2: { call_lua_fuc("prefetcht2");break;}
			case  UD_Ipsadbw: { call_lua_fuc("psadbw");break;}
			case  UD_Ipshufd: { call_lua_fuc("pshufd");break;}
			case  UD_Ipshufhw: { call_lua_fuc("pshufhw");break;}
			case  UD_Ipshuflw: { call_lua_fuc("pshuflw");break;}
			case  UD_Ipshufw: { call_lua_fuc("pshufw");break;}
			case  UD_Ipslldq: { call_lua_fuc("pslldq");break;}
			case  UD_Ipsllw: { call_lua_fuc("psllw");break;}
			case  UD_Ipslld: { call_lua_fuc("pslld");break;}
			case  UD_Ipsllq: { call_lua_fuc("psllq");break;}
			case  UD_Ipsraw: { call_lua_fuc("psraw");break;}
			case  UD_Ipsrad: { call_lua_fuc("psrad");break;}
			case  UD_Ipsrlw: { call_lua_fuc("psrlw");break;}
			case  UD_Ipsrld: { call_lua_fuc("psrld");break;}
			case  UD_Ipsrlq: { call_lua_fuc("psrlq");break;}
			case  UD_Ipsrldq: { call_lua_fuc("psrldq");break;}
			case  UD_Ipsubb: { call_lua_fuc("psubb");break;}
			case  UD_Ipsubw: { call_lua_fuc("psubw");break;}
			case  UD_Ipsubd: { call_lua_fuc("psubd");break;}
			case  UD_Ipsubq: { call_lua_fuc("psubq");break;}
			case  UD_Ipsubsb: { call_lua_fuc("psubsb");break;}
			case  UD_Ipsubsw: { call_lua_fuc("psubsw");break;}
			case  UD_Ipsubusb: { call_lua_fuc("psubusb");break;}
			case  UD_Ipsubusw: { call_lua_fuc("psubusw");break;}
			case  UD_Ipunpckhbw: { call_lua_fuc("punpckhbw");break;}
			case  UD_Ipunpckhwd: { call_lua_fuc("punpckhwd");break;}
			case  UD_Ipunpckhdq: { call_lua_fuc("punpckhdq");break;}
			case  UD_Ipunpckhqdq: { call_lua_fuc("punpckhqdq");break;}
			case  UD_Ipunpcklbw: { call_lua_fuc("punpcklbw");break;}
			case  UD_Ipunpcklwd: { call_lua_fuc("punpcklwd");break;}
			case  UD_Ipunpckldq: { call_lua_fuc("punpckldq");break;}
			case  UD_Ipunpcklqdq: { call_lua_fuc("punpcklqdq");break;}
			case  UD_Ipi2fw: { call_lua_fuc("pi2fw");break;}
			case  UD_Ipi2fd: { call_lua_fuc("pi2fd");break;}
			case  UD_Ipf2iw: { call_lua_fuc("pf2iw");break;}
			case  UD_Ipf2id: { call_lua_fuc("pf2id");break;}
			case  UD_Ipfnacc: { call_lua_fuc("pfnacc");break;}
			case  UD_Ipfpnacc: { call_lua_fuc("pfpnacc");break;}
			case  UD_Ipfcmpge: { call_lua_fuc("pfcmpge");break;}
			case  UD_Ipfmin: { call_lua_fuc("pfmin");break;}
			case  UD_Ipfrcp: { call_lua_fuc("pfrcp");break;}
			case  UD_Ipfrsqrt: { call_lua_fuc("pfrsqrt");break;}
			case  UD_Ipfsub: { call_lua_fuc("pfsub");break;}
			case  UD_Ipfadd: { call_lua_fuc("pfadd");break;}
			case  UD_Ipfcmpgt: { call_lua_fuc("pfcmpgt");break;}
			case  UD_Ipfmax: { call_lua_fuc("pfmax");break;}
			case  UD_Ipfrcpit1: { call_lua_fuc("pfrcpit1");break;}
			case  UD_Ipfrspit1: { call_lua_fuc("pfrspit1");break;}
			case  UD_Ipfsubr: { call_lua_fuc("pfsubr");break;}
			case  UD_Ipfacc: { call_lua_fuc("pfacc");break;}
			case  UD_Ipfcmpeq: { call_lua_fuc("pfcmpeq");break;}
			case  UD_Ipfmul: { call_lua_fuc("pfmul");break;}
			case  UD_Ipfrcpit2: { call_lua_fuc("pfrcpit2");break;}
			case  UD_Ipmulhrw: { call_lua_fuc("pmulhrw");break;}
			case  UD_Ipswapd: { call_lua_fuc("pswapd");break;}
			case  UD_Ipavgusb: { call_lua_fuc("pavgusb");break;}
			case  UD_Ipush: { call_lua_fuc("push");break;}
			case  UD_Ipusha: { call_lua_fuc("pusha");break;}
			case  UD_Ipushad: { call_lua_fuc("pushad");break;}
			case  UD_Ipushfw: { call_lua_fuc("pushfw");break;}
			case  UD_Ipushfd: { call_lua_fuc("pushfd");break;}
			case  UD_Ipushfq: { call_lua_fuc("pushfq");break;}
			case  UD_Ipxor: { call_lua_fuc("pxor");break;}
			case  UD_Ircl: { call_lua_fuc("rcl");break;}
			case  UD_Ircr: { call_lua_fuc("rcr");break;}
			case  UD_Irol: { call_lua_fuc("rol");break;}
			case  UD_Iror: { call_lua_fuc("ror");break;}
			case  UD_Ircpps: { call_lua_fuc("rcpps");break;}
			case  UD_Ircpss: { call_lua_fuc("rcpss");break;}
			case  UD_Irdmsr: { call_lua_fuc("rdmsr");break;}
			case  UD_Irdpmc: { call_lua_fuc("rdpmc");break;}
			case  UD_Irdtsc: { call_lua_fuc("rdtsc");break;}
			case  UD_Irdtscp: { call_lua_fuc("rdtscp");break;}
			case  UD_Irepne: { call_lua_fuc("repne");break;}
			case  UD_Irep: { call_lua_fuc("rep");break;}
			case  UD_Iret: { call_lua_fuc("ret");break;}
			case  UD_Iretf: { call_lua_fuc("retf");break;}
			case  UD_Irsm: { call_lua_fuc("rsm");break;}
			case  UD_Irsqrtps: { call_lua_fuc("rsqrtps");break;}
			case  UD_Irsqrtss: { call_lua_fuc("rsqrtss");break;}
			case  UD_Isahf: { call_lua_fuc("sahf");break;}
			case  UD_Isal: { call_lua_fuc("sal");break;}
			case  UD_Isalc: { call_lua_fuc("salc");break;}
			case  UD_Isar: { call_lua_fuc("sar");break;}
			case  UD_Ishl: { call_lua_fuc("shl");break;}
			case  UD_Ishr: { call_lua_fuc("shr");break;}
			case  UD_Isbb: { call_lua_fuc("sbb");break;}
			case  UD_Iscasb: { call_lua_fuc("scasb");break;}
			case  UD_Iscasw: { call_lua_fuc("scasw");break;}
			case  UD_Iscasd: { call_lua_fuc("scasd");break;}
			case  UD_Iscasq: { call_lua_fuc("scasq");break;}
			case  UD_Iseto: { call_lua_fuc("seto");break;}
			case  UD_Isetno: { call_lua_fuc("setno");break;}
			case  UD_Isetb: { call_lua_fuc("setb");break;}
			case  UD_Isetnb: { call_lua_fuc("setnb");break;}
			case  UD_Isetz: { call_lua_fuc("setz");break;}
			case  UD_Isetnz: { call_lua_fuc("setnz");break;}
			case  UD_Isetbe: { call_lua_fuc("setbe");break;}
			case  UD_Iseta: { call_lua_fuc("seta");break;}
			case  UD_Isets: { call_lua_fuc("sets");break;}
			case  UD_Isetns: { call_lua_fuc("setns");break;}
			case  UD_Isetp: { call_lua_fuc("setp");break;}
			case  UD_Isetnp: { call_lua_fuc("setnp");break;}
			case  UD_Isetl: { call_lua_fuc("setl");break;}
			case  UD_Isetge: { call_lua_fuc("setge");break;}
			case  UD_Isetle: { call_lua_fuc("setle");break;}
			case  UD_Isetg: { call_lua_fuc("setg");break;}
			case  UD_Isfence: { call_lua_fuc("sfence");break;}
			case  UD_Isgdt: { call_lua_fuc("sgdt");break;}
			case  UD_Ishld: { call_lua_fuc("shld");break;}
			case  UD_Ishrd: { call_lua_fuc("shrd");break;}
			case  UD_Ishufpd: { call_lua_fuc("shufpd");break;}
			case  UD_Ishufps: { call_lua_fuc("shufps");break;}
			case  UD_Isidt: { call_lua_fuc("sidt");break;}
			case  UD_Isldt: { call_lua_fuc("sldt");break;}
			case  UD_Ismsw: { call_lua_fuc("smsw");break;}
			case  UD_Isqrtps: { call_lua_fuc("sqrtps");break;}
			case  UD_Isqrtpd: { call_lua_fuc("sqrtpd");break;}
			case  UD_Isqrtsd: { call_lua_fuc("sqrtsd");break;}
			case  UD_Isqrtss: { call_lua_fuc("sqrtss");break;}
			case  UD_Istc: { call_lua_fuc("stc");break;}
			case  UD_Istd: { call_lua_fuc("std");break;}
			case  UD_Istgi: { call_lua_fuc("stgi");break;}
			case  UD_Isti: { call_lua_fuc("sti");break;}
			case  UD_Iskinit: { call_lua_fuc("skinit");break;}
			case  UD_Istmxcsr: { call_lua_fuc("stmxcsr");break;}
			case  UD_Istosb: { call_lua_fuc("stosb");break;}
			case  UD_Istosw: { call_lua_fuc("stosw");break;}
			case  UD_Istosd: { call_lua_fuc("stosd");break;}
			case  UD_Istosq: { call_lua_fuc("stosq");break;}
			case  UD_Istr: { call_lua_fuc("str");break;}
			case  UD_Isub: { call_lua_fuc("sub");break;}
			case  UD_Isubpd: { call_lua_fuc("subpd");break;}
			case  UD_Isubps: { call_lua_fuc("subps");break;}
			case  UD_Isubsd: { call_lua_fuc("subsd");break;}
			case  UD_Isubss: { call_lua_fuc("subss");break;}
			case  UD_Iswapgs: { call_lua_fuc("swapgs");break;}
			case  UD_Isyscall: { call_lua_fuc("syscall");break;}
			case  UD_Isysenter: { call_lua_fuc("sysenter");break;}
			case  UD_Isysexit: { call_lua_fuc("sysexit");break;}
			case  UD_Isysret: { call_lua_fuc("sysret");break;}
			case  UD_Itest: { call_lua_fuc("test");break;}
			case  UD_Iucomisd: { call_lua_fuc("ucomisd");break;}
			case  UD_Iucomiss: { call_lua_fuc("ucomiss");break;}
			case  UD_Iud2: { call_lua_fuc("ud2");break;}
			case  UD_Iunpckhpd: { call_lua_fuc("unpckhpd");break;}
			case  UD_Iunpckhps: { call_lua_fuc("unpckhps");break;}
			case  UD_Iunpcklps: { call_lua_fuc("unpcklps");break;}
			case  UD_Iunpcklpd: { call_lua_fuc("unpcklpd");break;}
			case  UD_Iverr: { call_lua_fuc("verr");break;}
			case  UD_Iverw: { call_lua_fuc("verw");break;}
			case  UD_Ivmcall: { call_lua_fuc("vmcall");break;}
			case  UD_Ivmclear: { call_lua_fuc("vmclear");break;}
			case  UD_Ivmxon: { call_lua_fuc("vmxon");break;}
			case  UD_Ivmptrld: { call_lua_fuc("vmptrld");break;}
			case  UD_Ivmptrst: { call_lua_fuc("vmptrst");break;}
			case  UD_Ivmresume: { call_lua_fuc("vmresume");break;}
			case  UD_Ivmxoff: { call_lua_fuc("vmxoff");break;}
			case  UD_Ivmrun: { call_lua_fuc("vmrun");break;}
			case  UD_Ivmmcall: { call_lua_fuc("vmmcall");break;}
			case  UD_Ivmload: { call_lua_fuc("vmload");break;}
			case  UD_Ivmsave: { call_lua_fuc("vmsave");break;}
			case  UD_Iwait: { call_lua_fuc("wait");break;}
			case  UD_Iwbinvd: { call_lua_fuc("wbinvd");break;}
			case  UD_Iwrmsr: { call_lua_fuc("wrmsr");break;}
			case  UD_Ixadd: { call_lua_fuc("xadd");break;}
			case  UD_Ixchg: { call_lua_fuc("xchg");break;}
			case  UD_Ixlatb: { call_lua_fuc("xlatb");break;}
			case  UD_Ixor: { call_lua_fuc("xor");break;}
			case  UD_Ixorpd: { call_lua_fuc("xorpd");break;}
			case  UD_Ixorps: { call_lua_fuc("xorps");break;}
			case  UD_Idb: { call_lua_fuc("db");break;}
			case  UD_Iinvalid: { call_lua_fuc("invalid");break;}
			case  UD_Id3vil: { call_lua_fuc("d3vil");break;}
			case  UD_Ina: { call_lua_fuc("na");break;}
			case  UD_Igrp_reg: { call_lua_fuc("grp_reg");break;}
			case  UD_Igrp_rm: { call_lua_fuc("grp_rm");break;}
			case  UD_Igrp_vendor: { call_lua_fuc("grp_vendor");break;}
			case  UD_Igrp_x87: { call_lua_fuc("grp_x87");break;}
			case  UD_Igrp_mode: { call_lua_fuc("grp_mode");break;}
			case  UD_Igrp_osize: { call_lua_fuc("grp_osize");break;}
			case  UD_Igrp_asize: { call_lua_fuc("grp_asize");break;}
			case  UD_Igrp_mod: { call_lua_fuc("grp_mod");break;}
			case  UD_Inone: {break;}
		}
   }
   info->base = imagebase;
   a.reloc(imagebase); 
   info->buf = a.get_code();
   info->size = a.get_code_size();
   return info;
}


