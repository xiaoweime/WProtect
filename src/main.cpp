// [AsmJit]
// Complete JIT Assembler for C++ Language.
//
// [License]
// Zlib - See COPYING file in this package.

// This file is only included as an example and simple test if jit
// compiler works.

#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>

//#include <WProtect.h>
#ifndef WPROTECT_CONFIG_H
#define WPROTECT_CONFIG_H
#include <WProtectConfig.h>
#endif

#ifndef ASMJIT_H
#define ASMJIT_H
#include <Assembl.h>
//#include <AsmJit.h>
#endif

//#ifndef UDIS86_H
//#define UDIS86_H
#include <udis86.h>
//#endif
//#include <udis86.h>

#include <OutOfOrder.hpp>
// This is type of functionwe will generate
typedef int (*MyFn)();

//#include <PEFile.h>
#include <PESection.h>
#include <PEReloc.h>
#ifndef LUA_H
#define LUA_H
extern "C"{
#include "Lua/lua.h"
#include "Lua/lualib.h"
#include "Lua/lauxlib.h"
}
#endif

#include "WProtect/Protect/EquivalentReplacement/LuaEquivalentReplacement.h"
#include <VirtualMachineManage.hpp>
#include <PCode.hpp>
#include <SeniorVMHandle.hpp>
#include <Analysis.hpp>
//#include <BuildVMCode.hpp>
#include <VMAddressTable.hpp>
#include <EquivalentReplacement.hpp>
#include <BuildVMByteCode.hpp>
#include "build_address.hpp"
#include "ELFFile.h"


static int show_version(lua_State *L)   //给lua调用的c函数必须定义成static int XXX(lua_State *L)
{
 //   char   path[MAX_PATH];
//    GetCurrentDirectory(MAX_PATH,path);
 //   lua_pushstring(L,path);
    lua_pushstring(L,"\r\nlua_5.1.1\r\n");
    return 1;   //为什么要返回1？这是有依据的，该函数把结果压入了栈，lua调用该函数将从栈中
//取1个结果
}


int run_lua ()
{
    int sum;
    lua_State* L;
    //创建一个指向lua解释器的指针
    L = luaL_newstate();
    //加载lua标准库
    luaL_openlibs(L);
         //注册C++函数
    lua_register(L,"show_version",show_version);
    //加载脚本
    luaL_dofile(L,"info.lua");
    //调用函数
    lua_getglobal(L,"run");
         //运行函数并把结果压入栈
    lua_pcall(L,0,0,0);
    //关闭并释放资源
    lua_close(L);
    return 0;
}

/*
void petest()
{
	CPEFile test;
    if (!test.LoadPEFile("test.exe"))
		{
			fprintf(stdout,"not find file");
			return;
		}
	if (test.IsPEFile())
	{
		fprintf(stdout,"the is pe\r\n");

		//CodeInformation info;
		//info.buf = (unsigned char*)test.VaToPtr(0x401000);
		//info.size = 0x932;
		//info.base = 0x401000;
		//OutOfOrder code;
		//info = *code.code_out_of_order(&info,0x405000);
		//FILE *pFile = fopen("testcode","wb");
		//if (pFile)
		//{
		//	fwrite(info.buf,info.size,1,pFile);
		//	fclose(pFile);
		//}

		CodeInformation info;
		info.buf = (unsigned char*)test.VaToPtr(0x401000);
		info.size = 0x932;
		info.base = 0x401000;
		OutOfOrder code;
		LuaInterface lua;
		info = *lua.lua_equivalent_replacement(&info,0x401000);
		//info = *lua_equivalent_replacement(&info,0x401000);
		FILE *pFile = fopen("testcode","wb");
		if (pFile)
		{
			fwrite(info.buf,info.size,1,pFile);
			fclose(pFile);
		}
	}
	else
		fprintf(stdout,"the not pe");
} */

void testasm()
{
  Assembl a;
	//a.Assemble("mov rax,rbx");
	//a.Assemble("call qword ptr[ rbx]");
	//a.Assemble("call Dword ptr[ ebx]");
}
int test()
{
	uint8_t raw[] = { 0xf0, 0x66, 0x36, 0x67, 0x65, 0x66, 0xf3, 0x67, 0xda };
	uint8_t len = 9;
	ud_t ud_obj;
	ud_init(&ud_obj);
	ud_set_mode(&ud_obj, 16);
	ud_set_input_buffer(&ud_obj, raw, len);
	ud_set_syntax(&ud_obj, UD_SYN_INTEL);
//	if (ud_disassemble(&ud_obj) != 0) {
//		fprintf(stdout,"%s",ud_insn_asm(&ud_obj));
//	}
return 0;
}

int vmtest()
{
  //VirtualMachine vm(0x401000);
  VirtualMachineManage vm;
  PCode pcode;
  SeniorVMHandle vmhandle(&pcode);
  FILE *file;
  VirtualMachine * pvm = vm.add_virtual_machine(0x401000); //可能发生溢出
  vm.rand_virtual_machine();
  // PCode *pcode = new PCode;
  vm.moc(pvm,&pcode);
  unsigned char * buf = new unsigned char [0xffff];
  unsigned long size;

  size = pvm->vm_info.size;
   memcpy(buf,pvm->vm_info.buf,pvm->vm_info.size);

  //pcode->v_pop_register(T_EAX);
  // pcode->v_pop_register(T_EBX);
  //pcode->v_push_register(T_AX);
  //pcode->v_push_register(T_BX);
  //pcode->v_pop_register(T_BX);
  // pcode->v_pop_register(T_AX);
   //vmhandle.d_and(T_EAX,T_EBX);
   // vmhandle.d_xor(T_EAX);
   //vmhandle.d_or(T_EAX,T_EBX);
  // vmhandle.d_xor(T_EAX,T_EBX);

   // vmhandle.d_xor(T_EAX,T_EBX);

   // pcode->v_pop_register(T_INVALID);

   //pcode->v_push_register(T_EAX);
   // pcode->v_push_register(T_EBX);


   //   vmhandle.w_push_imm_sx(0xf7ea);

   vmhandle.upset_register_array( vmhandle.pcode->register_store_in );

    vmhandle.start();

    //vmhandle.r_get_mem(T_ESP,T_EAX,0,0);
    // vmhandle.push(T_ESP,false);
    // vmhandle.d_sub(T_EAX,T_EBX);
    //pcode->v_pop_register(T_EFLAG);
    //pcode->v_pop_register(T_EAX);
    //vmhandle.set_protect_grade(true);
    //vmhandle.d_add(T_EAX,T_EBX);
    //vmhandle.pop(T_INVALID);
    //vmhandle.pop(T_INVALID);
    //vmhandle.r_get_mem( T_ESP,0,0,0 );
    //vmhandle.pop( T_EAX );
    //vmhandle.d_and( T_EAX,0 ,true);
    //vmhandle.pop( T_INVALID );
    // vmhandle.pop( T_EAX );
    //vmhandle.upset_register_array( vmhandle.pcode->register_store_out );
   //vmhandle.recover_vm_context(  );
   //RegisterStore reg_bak;
   //reg_bak = vmhandle.pcode->register_store_in ;

   //vmhandle.pcode->register_store_in = vmhandle.pcode->register_store_out;
   //vmhandle.save_vm_context(  );

    vmhandle.popf(  );
   //vmhandle.pushf(  );
   //vmhandle.pushad(  );

   //vmhandle.push( T_EAX )   ;

   vmhandle.exit(  );


   // vmhandle.pcode->register_store_in = reg_bak;
   //vmhandle.exit(  );

    //vmhandle.push( T_EFLAG );

    //vmhandle.pop(T_EAX);
    //vmhandle.d_push_imm(0xffffffff);
    //vmhandle.pop(T_EBX);
    //vmhandle.b_push_imm(0xFF);
  //  vmhandle.d_not(T_EAX);
  //vmhandle.d_xor(T_EAX,T_EDX);
  //pcode->v_pop_register(T_EFLAG32);
  // vmhandle.w_xor(T_DX,T_BX);
  // vmhandle.w_xor(T_DX,T_AX);
   //pcode->v_push_register(T_DL);
   //pcode->v_push_register(T_DH);
   // pcode->v_pop_register(T_AL);

  //vmhandle.d_not(T_EDX);
  //vmhandle.popf();
  //pcode->v_pop_register(T_EDX);
  //pcode->v_pop_register(T_AH);

   //vmhandle.b_or(T_AL,T_DH);
   //vmhandle.popf();
   //pcode->v_pop_register(T_AL);
   //vmhandle.d_add(T_EBX,T_EDX);
   // pcode->v_pop_register(T_ECX);
   //pcode->v_pop_register(T_AL);

   // vmhandle.w_xor(T_AX,T_DX);
   //vmhandle.popf();
   //pcode->v_pop_register(T_DX);

   //vmhandle.exit();

   long key = pcode.get_original_key();

   ppcode_block_info info =  pvm->add_new_function(0x401000+pvm->vm_info.size,&pcode,0x401000,123456,key);

  memcpy(&buf[size],info->buf,info->size);
    size += info->size;
    //delete  pcode;


  file = fopen("code","wb");
  fwrite(buf,1,size,file);
  fclose(file);
  delete [] buf;
  // delete pcode;

  return 0;
}

void analysistest()
{
  Analysis a;
  CodeBufferInfo o;
  CPEFile file;

  file.LoadPEFile("mfc.exe");
  if (!file.IsPEFile())
  {
    return ;
  }
  o.buf = file.VaToPtr(0x4014a0);
  for (int i = 0; i < 0x21; ++i)
  {
    printf("i = %d,%x\r\n",i,((char*)o.buf)[i]);
  }
  o.addr = 0x4014a0;
  o.size = 0x3a;
  a.disasm(&o);
}

void assemblertest()
{
  Assembler a;


  // Log assembler output.
  FileLogger logger(stderr);
  a.setLogger(&logger);

  //// Prolog.
  a.push(nbp);
  a.mov(nbp, nsp);

  // Mov 1024 to EAX/RAX, EAX/RAX is also return value.
  a.mov(nax, 1024);

  // Epilog.
  a.mov(nsp, nbp);
  a.pop(nbp);
  a.ret();


  // ==========================================================================

  // NOTE:
  // This function can be also completely rewritten to this form:
  //   a.mov(nax, 1024);
  //   a.ret();
  // If you are interested in removing prolog and epilog, please
  // study calling conventions and check register preservations.

  // ==========================================================================
  // Make the function.
  MyFn fn = function_cast<MyFn>(a.make());

  // Call it.
  int result = fn();
  printf("Result from jit function: %d\n", result);
  printf("Status: %s\n", result == 1024 ? "Success" : "Failure");

  // Free the generated function if it's not needed anymore.
  MemoryManager::getGlobal()->free((void*)fn);
  // ==========================================================================
}


void add_jmp_addr(CPEFile pe,long base,long jmp_address)
{
  char * c = (char*)pe.VaToPtr(base);
  *(char*)c = 0xe9;
  *(long*)(c + 1) = jmp_address - base - 5;
}

void add_jmp_addr_elf(CELFFile file,long base,long jmp_address)
{
   char * c = (char*)file.VaToPtr(base);
  *(char*)c = 0xe9;
  *(long*)(c + 1) = jmp_address - base - 5;
}

void get_wprotect_sdk_address_elf(CELFFile & section,
                              BuildCodeInfo & build_info,
                              char *sz_sdk_begin_name,
                              char *sz_sdk_end_name)
{
  int section_count = section.GetSectionCount();
  for (int index = 0;index <  section_count;index++)
  {
      int sdk_begin_count = 0;
      int sdk_end_count = 0;
      int protect_begin_address = 0;
      int protect_end_address = 0;

      size_t section_size;
      unsigned char * ptr_section_data = (unsigned char*)section.GetSectionData(index,&section_size);
      printf("\n第%d个区段，大小%d\n",index,section_size);
      for (int offset = 0;offset < section_size;offset++)
      {
          //printf("%x ",(unsigned char)ptr_section_data[offset]);
          if ((offset + 1) % 16 == 0)
          {
            //  printf("\n");
          }
          if ((unsigned char)ptr_section_data[offset] == 0xeb
                  && sdk_begin_count==0
                  && sdk_end_count==0
                  && offset + max(strlen(sz_sdk_begin_name)+1,strlen(sz_sdk_end_name)+1) < section_size
                  )
          {
              sdk_begin_count++;
              sdk_end_count++;
              if (ptr_section_data[offset + sdk_begin_count] == strlen(sz_sdk_begin_name) + 1
                  && sdk_begin_count == 1)
              {
                  sdk_begin_count++;
                  sdk_end_count = 0;
                  continue;
              }
              else
              {
                  sdk_begin_count = 0;
              }
              if (ptr_section_data[offset + sdk_end_count] == strlen(sz_sdk_end_name) + 1
                  && sdk_end_count == 1)
              {
                  sdk_end_count++;
                  continue;
              }
              else
              {
                  sdk_end_count = 0;
              }

          }
          if (sdk_begin_count > 1)
          {
              if (ptr_section_data[offset + 1] == sz_sdk_begin_name[sdk_begin_count-2])
              {
                  sdk_begin_count++;
              }
              else
              {
                  sdk_begin_count = 0;
                  offset--;
                  continue;
              }

          }
          if (sdk_end_count > 1)
          {
              if (ptr_section_data[offset + 1] == sz_sdk_end_name[sdk_end_count-2])
              {
                  sdk_end_count++;
              }
              else
              {
                  sdk_end_count = 0;
                  offset--;
                  continue;
              }
          }
          if (sdk_begin_count == strlen(sz_sdk_begin_name) + 3)
          {
              int sdk_begin_str_size = strlen(sz_sdk_begin_name) + 1;
              printf("找到SDK BEGIN offset:%x,addr:%x\n",
                     offset - sdk_begin_str_size,
                     section.GetSectionVa(index,offset - sdk_begin_str_size));
              protect_begin_address = section.GetSectionVa(index,offset - sdk_begin_str_size);
              memset((void*)section.GetSectionPtr(index,offset - sdk_begin_str_size),0x90,sdk_begin_count);
              sdk_begin_count = 0;

              //__asm__("int3");
          }
          if (sdk_end_count == strlen(sz_sdk_end_name) + 3)
          {
              printf("找到SDK END offset:%x\n",offset - strlen(sz_sdk_end_name) - 1);
              int sdk_end_str_size = strlen(sz_sdk_end_name) + 1;
              protect_end_address = section.GetSectionVa(index,offset - sdk_end_str_size);
              if (protect_begin_address == 0 )
              {
                  printf("%x这个WProtect End没有匹配的WProtect Begin\n",protect_end_address);
              }
              else
              {
                  build_piece piece;
                  piece.build_exec_addr = protect_begin_address;
                  piece.build_exec_size = protect_end_address - protect_begin_address + sdk_end_str_size + 2;
                  printf("保护地址%x - %x\n",piece.build_exec_addr,piece.build_exec_addr+piece.build_exec_size);
                  build_info.push_back(piece);
              }
              protect_begin_address = 0;
              protect_end_address = 0;
              memset((void*)section.GetSectionPtr(index,offset - sdk_end_str_size),0x90,sdk_end_count);

              sdk_end_count = 0;
          }
          //printf("%x\n",offset);
          //printf("%x ",ptr_section_data[offset]);
          //if ((offset)%16==0)
          //{
          //    printf("\n");
          //}
      }
   }
  //throw;

}
void get_wprotect_sdk_address(CPESection & section,
                              BuildCodeInfo & build_info,
                              char *sz_sdk_begin_name,
                              char *sz_sdk_end_name)
{
  int sdk_begin_count = 0;
  int sdk_end_count = 0;
  int protect_begin_address = 0;
  int protect_end_address = 0;
  int section_count = section.GetSectionCount();
  for (int index = 0;index <  section_count;index++)
  {
      DWORD section_size;
      BYTE * ptr_section_data = section.GetSectionData(index,&section_size);
      printf("第%d个区段，大小%d\n",index,section_size);
      for (int offset = 0;offset < section_size;offset++)
      {
          if (ptr_section_data[offset] == 0xeb
                  && sdk_begin_count==0
                  && sdk_end_count==0
                  && offset + max(strlen(sz_sdk_begin_name)+1,strlen(sz_sdk_end_name)+1) < section_size
                  )
          {
              sdk_begin_count++;
              sdk_end_count++;
              if (ptr_section_data[offset + sdk_begin_count] == strlen(sz_sdk_begin_name) + 1
                  && sdk_begin_count == 1)
              {
                  sdk_begin_count++;
                  sdk_end_count = 0;
                  continue;
              }
              else
              {
                  sdk_begin_count = 0;
              }
              if (ptr_section_data[offset + sdk_end_count] == strlen(sz_sdk_end_name) + 1
                  && sdk_end_count == 1)
              {
                  sdk_end_count++;
                  continue;
              }
              else
              {
                  sdk_end_count = 0;
              }

          }
          if (sdk_begin_count > 1)
          {
              if (ptr_section_data[offset + 1] == sz_sdk_begin_name[sdk_begin_count-2])
              {
                  sdk_begin_count++;
              }
              else
              {
                  sdk_begin_count = 0;
                  offset--;
                  continue;
              }

          }
          if (sdk_end_count > 1)
          {
              if (ptr_section_data[offset + 1] == sz_sdk_end_name[sdk_end_count-2])
              {
                  sdk_end_count++;
              }
              else
              {
                  sdk_end_count = 0;
                  offset--;
                  continue;
              }
          }
          if (sdk_begin_count == strlen(sz_sdk_begin_name) + 3)
          {
              int sdk_begin_str_size = strlen(sz_sdk_begin_name) + 1;
              /*printf("找到SDK BEGIN offset:%x,addr:%x\n",
                     offset - sdk_begin_str_size,
                     section.GetSectionVa(index,offset - sdk_begin_str_size));*/
              protect_begin_address = section.GetSectionVa(index,offset - sdk_begin_str_size);
              memset((void*)section.GetSectionPtr(index,offset - sdk_begin_str_size),0x90,sdk_begin_count);
              sdk_begin_count = 0;

              //__asm__("int3");
          }
          if (sdk_end_count == strlen(sz_sdk_end_name) + 3)
          {
              //printf("找到SDK END offset:%x\n",offset - strlen(sz_sdk_end_name) - 1);
              int sdk_end_str_size = strlen(sz_sdk_end_name) + 1;
              protect_end_address = section.GetSectionVa(index,offset - sdk_end_str_size);
              if (protect_begin_address == 0 )
              {
                  printf("%x这个WProtect End没有匹配的WProtect Begin\n",protect_end_address);
              }
              else
              {
                  build_piece piece;
                  piece.build_exec_addr = protect_begin_address;
                  piece.build_exec_size = protect_end_address - protect_begin_address + sdk_end_str_size + 2;
                  printf("保护地址%x - %x\n",piece.build_exec_addr,piece.build_exec_addr+piece.build_exec_size);
                  build_info.push_back(piece);
              }
              protect_begin_address = 0;
              protect_end_address = 0;
              memset((void*)section.GetSectionPtr(index,offset - sdk_end_str_size),0x90,sdk_end_count);

              sdk_end_count = 0;
          }
          //printf("%x\n",offset);
          //printf("%x ",ptr_section_data[offset]);
          //if ((offset)%16==0)
          //{
          //    printf("\n");
          //}
      }
   }
  //throw;

}
void get_table_addr_elf(CELFFile &section, std::vector<long> & addr_table_entry,std::vector<long *> & addr_table_entry_point)
{
    for (std::vector<long>::iterator iter = addr_table_entry.begin();
         iter != addr_table_entry.end();iter++)
    {
        if (section.CheckAddressValidity(*iter))
        {
            long *addr = (long*)section.VaToPtr(*iter);
            //printf("table addr:%08x\r\n",*addr);
            if (addr)
            while (section.CheckAddressValidity(*addr))
            {
                printf ("table addr:%08x\n",*addr);
                addr_table_entry_point.push_back(addr);
                addr++;
            }
            //addr++;
        }
    }
}

void get_table_addr(CPESection &section, std::vector<long> & addr_table_entry,std::vector<long *> & addr_table_entry_point)
{
    for (std::vector<long>::iterator iter = addr_table_entry.begin();
         iter != addr_table_entry.end();iter++)
    {
        if (section.CheckAddressValidity(*iter))
        {
            long *addr = (long*)section.VaToPtr(*iter);
            //printf("table addr:%08x\r\n",*addr);
            if (addr)
            while (section.CheckAddressValidity(*addr))
            {
#ifdef DEBUG
                printf ("table addr:%08x\n",*addr);
#endif
                addr_table_entry_point.push_back(addr);
                addr++;

            }
            //addr++;
        }
    }
}
void buildvmtest_elf(BuildCodeInfo & build_info)
{
  VirtualMachineManage vm;
  CodeBufferInfo info;

  CELFFile file;

  char * build_exec_name = build_info.get_filename();
  bool b = file.LoadELFFile(build_exec_name);
  if (!b)
  {
    printf("file is not find\r\n");
    return;
  }
  get_wprotect_sdk_address_elf(file,build_info,"WProtect Begin","WProtect End");
  unsigned long section_size;

  VMAddressTable table(   file.GetNewSegmentSectionBase(),0x512,false);

  bool t_sign = table.get_sign();
  table.set_sign(true);
  long virtualmachine_address = table.assign_address(0x1024);
  table.set_sign(t_sign);
  VirtualMachine *pvm = vm.add_virtual_machine(virtualmachine_address,false);

  table.copy(virtualmachine_address,pvm->vm_info.buf,pvm->vm_info.size);


  for (BuildCodeInfo::iterator iter = build_info.begin(); iter != build_info.end(); iter++)
  {
    long build_exec_addr = iter->build_exec_addr;
    long build_exec_size = iter->build_exec_size;
    info.buf = file.VaToPtr(build_exec_addr);
    info.addr = build_exec_addr;
    info.size = 0x40194f - 0x4014a0;
    info.size = build_exec_size;
    if (info.size < 5)
    {
      printf("编译内容不能小于5Byte,容不下一个跳转\n");
      return;
    }
//#define VM_DEBUG_BUILD
#ifdef VM_DEBUG_BUILD
    Analysis analysis;
    std::vector<CodePiece> code_list;
    analysis.disasm(&info,code_list);
    bool next = true;
    for (std::vector<CodePiece>::iterator iter = code_list.begin();
         iter != code_list.end();iter++)
    {
        bool begin = true;
        //info.addr = 0;
        //info.buf = 0;
        if (iter->get_is_jcc())
         info.size = iter->get_piece().back().insn_offset - iter->get_piece().front().insn_offset;
        else
         info.size = iter->get_piece().back().pc - iter->get_piece().front().insn_offset;
        info.addr = iter->get_piece().front().insn_offset;
        info.buf = section.VaToPtr(info.addr);

        if (info.size < 5 )
        {
            printf("编译的地址不能小于5Byte,这段指令编译失败\n");
            //return;
            continue;
        }
        void * ptr_old_code = info.buf;
        size_t old_code_size = info.size;
        long old_addr = info.addr;
        BuildVMByteCode build(&vm,&info,&table);
        memset(ptr_old_code,0x90,old_code_size);
        add_jmp_addr(file,old_addr,info.addr);
    }
#else
    void * ptr_old_code = info.buf;
    size_t old_code_size = info.size;

    Analysis analysis;
    std::vector<long> addr_table;
    std::vector<long*> addr_entry_point;
    analysis.analysis_address_table(&info,addr_table,file.GetSectionMinAddress(),file.GetSectionMaxAddress());
    get_table_addr_elf(file,addr_table,addr_entry_point);

    BuildVMByteCode build(&vm,&info,&table,addr_entry_point);
    memset(ptr_old_code,0,old_code_size);
    add_jmp_addr_elf(file,build_exec_addr,info.addr);
#endif
  }


  FILE *pfile;

  //  VirtualMachine *pvm = vm.rand_virtual_machine();


  //t_sign = table.get_sign();
  //table.set_sign(true);
  //  long virtualmachine_address = table.assign_address(pvm->vm_info.size);
  //table.set_sign(t_sign);

  //  table.copy(virtualmachine_address,pvm->vm_info.buf,pvm->vm_info.size);

  section_size = (unsigned long)( table.buffer_size);
  file.AddSegmentSection(".WProtect",section_size,PF_X|PF_R|PF_W);
  file.WriteSegmentSectionData(file.GetProgramCount()-1,0,
      (unsigned char*)table.buffer,(unsigned long *)&table.buffer_size);
  char new_file_name[256];
  //memset(new_file_name,0,256);
  //memcpy(new_file_name,build_exec_name,strlen(build_exec_name)-3);
  strcpy(new_file_name,build_exec_name);
  strcat(new_file_name,"_WP");
  file.SavePEFile(new_file_name);
  printf("Out File:%s\n",new_file_name);
  //pfile = fopen( "virtualmachine","wb" );
  //fwrite( pvm->vm_info.buf,1,pvm->vm_info.size,pfile );
  //fclose( file );

  //delete [  ] buf;
}

void buildvmtest(BuildCodeInfo & build_info)
{
  VirtualMachineManage vm;
  CodeBufferInfo info;
 
  CPEFile file;

  char * build_exec_name = build_info.get_filename();
  bool b = file.LoadPEFile(build_exec_name);
  if (!b)
  {
    printf("file is not find\r\n");
    return;
  }
  CPESection section;
  CPEReloc reloc;
  section = file;
  reloc = file;
  reloc.DeleteReloc();
  reloc.GetBaseReloc();
  for (int i = 0;i<section.GetSectionCount();i++)
  {
      //section.GetRelocations(i);
  }
  //printf ("一共有%d个区段\r\n");
  /*for (int i = 0;i < section.GetSectionCount();i++)
  {

      DWORD size;
      BYTE * data = section.GetSectionData(i,&size);
      printf("第%d个区段，大小%d\n",i,size);

      for (int x = 0;x<size;x++)
      {
          printf("%x ",data[x]);
          if ((x+1)%16==0)
          {
              printf("\n");
          }
      }
   }*/
  get_wprotect_sdk_address(section,build_info,"WProtect Begin","WProtect End");
  unsigned long section_size;

  VMAddressTable table(   section.GetNewSectionBase(),0x512,false);

  bool t_sign = table.get_sign();
  table.set_sign(true);
  long virtualmachine_address = table.assign_address(0x1024);
  table.set_sign(t_sign);
  VirtualMachine *pvm = vm.add_virtual_machine(virtualmachine_address,false);

  table.copy(virtualmachine_address,pvm->vm_info.buf,pvm->vm_info.size);     


  for (BuildCodeInfo::iterator iter = build_info.begin(); iter != build_info.end(); iter++)
  {
    long build_exec_addr = iter->build_exec_addr;
    long build_exec_size = iter->build_exec_size;
    info.buf = file.VaToPtr(build_exec_addr);
    info.addr = build_exec_addr;   
    info.size = 0x40194f - 0x4014a0;
    info.size = build_exec_size;
    if (info.size < 5)
    {
      printf("编译内容不能小于5Byte,容不下一个跳转\n");
      return;
    }
//#define VM_DEBUG_BUILD
#ifdef VM_DEBUG_BUILD
    Analysis analysis;
    std::vector<CodePiece> code_list;
    analysis.disasm(&info,code_list);
    bool next = true;
    for (std::vector<CodePiece>::iterator iter = code_list.begin();
         iter != code_list.end();iter++)
    {
        bool begin = true;
        //info.addr = 0;
        //info.buf = 0;
        if (iter->get_is_jcc())
         info.size = iter->get_piece().back().insn_offset - iter->get_piece().front().insn_offset;
        else
         info.size = iter->get_piece().back().pc - iter->get_piece().front().insn_offset;
        info.addr = iter->get_piece().front().insn_offset;
        info.buf = section.VaToPtr(info.addr);

        if (info.size < 5 )
        {
            printf("编译的地址不能小于5Byte,这段指令编译失败\n");
            //return;
            continue;
        }
        void * ptr_old_code = info.buf;
        size_t old_code_size = info.size;
        long old_addr = info.addr;
        BuildVMByteCode build(&vm,&info,&table);
        memset(ptr_old_code,0x90,old_code_size);
        add_jmp_addr(file,old_addr,info.addr);
    }
#else
    void * ptr_old_code = info.buf;
    size_t old_code_size = info.size;

    Analysis analysis;
    std::vector<long> addr_table;
    std::vector<long*> addr_entry_point;
    analysis.analysis_address_table(&info,addr_table,section.GetSectionMinAddress(),section.GetSectionMaxAddress());
    get_table_addr(section,addr_table,addr_entry_point);

    BuildVMByteCode build(&vm,&info,&table,addr_entry_point);
    memset(ptr_old_code,0,old_code_size);
    add_jmp_addr(file,build_exec_addr,info.addr);    
#endif
  }


  FILE *pfile;

  //  VirtualMachine *pvm = vm.rand_virtual_machine();


  //t_sign = table.get_sign();
  //table.set_sign(true);
  //  long virtualmachine_address = table.assign_address(pvm->vm_info.size);
  //table.set_sign(t_sign);

  //  table.copy(virtualmachine_address,pvm->vm_info.buf,pvm->vm_info.size);

  section_size = (unsigned long)( table.buffer_size);
  section.AddSection(".WProtect",section_size,0xE0000020);
  section.WriteSectionData(file.GetSectionCount()-1,0,
      (unsigned char*)table.buffer,(unsigned long *)&table.buffer_size);
  char new_file_name[256];
  memset(new_file_name,0,256);
  memcpy(new_file_name,build_exec_name,strlen(build_exec_name)-3); 
  strcat(new_file_name,"wp.exe");
  file.SavePEFile(new_file_name);
  printf("Out File:%s\n",new_file_name);
  //pfile = fopen( "virtualmachine","wb" );
  //fwrite( pvm->vm_info.buf,1,pvm->vm_info.size,pfile );
  //fclose( file );

  //delete [  ] buf;
}

void outofordertest(  )
{
  CodeBufferInfo info;
  info.addr = 0x401000;
  CPEFile file;
  bool b = file.LoadPEFile("test32.exe");
  if (!b)
  {
    printf("file is not find\r\n");
    return;
  }
  //  info.buf = file.VaToPtr(0x4015d0);
  info.buf = file.VaToPtr( 0X401000 );
  //info.size = 0x7e;
  info.size = 0xd;

  OutOfOrder build;
  build.BuildCode(&info);
}

/*
void equivalentreplacement_test(  )
{
  CodeBufferInfo info;
  info.addr = 0x401010;
  CPEFile file;
  bool b = file.LoadPEFile( "test.exe" );
  info.buf = file.VaToPtr( 0x401010 );
  info.size = 0x21;
  CodeAddressTable table( 0x401010,0x512,true );
  EquivalentReplacement er;
   er.BuildCode( &info,&table );

  FILE *pfile;
  pfile = fopen( "eqre","wb" );
  char* buf = new char [ er.a.getCodeSize(  ) ];
  memcpy( buf,er.a.make(  ) ,er.a.getCodeSize(  ));
  fwrite( buf,1,er.a.getCodeSize(  ) ,pfile);
  fclose( pfile );

  delete [  ] buf;
}             */

BuildCodeInfo get()
{
  build_piece build_wmov_test = {
    .build_exec_addr = 0x401008,
    .build_exec_size = 5
  };
  build_piece build_dmov_test = {
    .build_exec_addr = 0x401002,
    .build_exec_size = 6
  };                
  build_piece build_blmov_test = {
    .build_exec_addr = 0x40100d,
    .build_exec_size = 5
  };  
  build_piece build_bhmov_test = {
    .build_exec_addr = 0x401012,
    .build_exec_size = 5
  }; 

  BuildCodeInfo build_mov_test("../test/insn/mov_test.exe");    
  build_mov_test.push_back(build_dmov_test);
  build_mov_test.push_back(build_wmov_test);
  build_mov_test.push_back(build_blmov_test);
  build_mov_test.push_back(build_bhmov_test);


  build_piece build_wadd_test = {
    .build_exec_addr = 0x401007,
    .build_exec_size = 5
  };
  build_piece build_dadd_test = {
    .build_exec_addr = 0x401002,
    .build_exec_size = 5
  };                
  build_piece build_bladd_test = {
    .build_exec_addr = 0x40100c,
    .build_exec_size = 5
  };  
  build_piece build_bhadd_test = {
    .build_exec_addr = 0x401011,
    .build_exec_size = 5
  }; 

  BuildCodeInfo build_add_test("../test/insn/add_test.exe");    
  build_add_test.push_back(build_dadd_test);
  build_add_test.push_back(build_wadd_test);
  build_add_test.push_back(build_bladd_test);
  build_add_test.push_back(build_bhadd_test);  


 

  build_piece build_wsub_test = {
    .build_exec_addr = 0x401007,
    .build_exec_size = 5
  };
  build_piece build_dsub_test = {
    .build_exec_addr = 0x401002,
    .build_exec_size = 5
  };                
  build_piece build_blsub_test = {
    .build_exec_addr = 0x40100c,
    .build_exec_size = 5
  };  
  build_piece build_bhsub_test = {
    .build_exec_addr = 0x401011,
    .build_exec_size = 5
  }; 

  BuildCodeInfo build_sub_test("../test/insn/sub_test.exe");    
  build_sub_test.push_back(build_dsub_test);
  build_sub_test.push_back(build_wsub_test);
  build_sub_test.push_back(build_blsub_test);
  build_sub_test.push_back(build_bhsub_test);


  BuildCodeInfo build_sar_test("../test/insn/sar_test.exe");
  build_sar_test.push_back(build_dsub_test);
  build_sar_test.push_back(build_wsub_test);
  build_sar_test.push_back(build_blsub_test);
  build_sar_test.push_back(build_bhsub_test);

  build_piece build_brepne_test = {
    .build_exec_addr = 0x401002,
    .build_exec_size = 5
  };

  BuildCodeInfo build_repne_test("../test/insn/repne_test.exe");
  build_repne_test.push_back(build_brepne_test);


  build_piece build_scasb_test= {
    .build_exec_addr = 0x401002,
    .build_exec_size = 5
  };

  BuildCodeInfo build_scas_test("../test/insn/scasb_test.exe");
  build_scas_test.push_back(build_scasb_test);

  build_piece build_movsb_test= {
    .build_exec_addr = 0x401002,
    .build_exec_size = 5
  };
  build_piece build_movsd_test= {
    .build_exec_addr = 0x401007,
    .build_exec_size = 5
  };


  BuildCodeInfo build_movs_test("../test/insn/movs_test.exe");
  build_movs_test.push_back(build_movsb_test);
  build_movs_test.push_back(build_movsd_test);

  BuildCodeInfo build_rep_test("../test/insn/rep_test.exe");
  build_rep_test.push_back(build_movsb_test);
  build_rep_test.push_back(build_movsd_test);

  build_piece build_dstack_point_test = {
      .build_exec_addr = 0x401002,
      .build_exec_size = 12
  };

  BuildCodeInfo build_stack_point_test("../test/insn/stackpoint_test.exe");
  build_stack_point_test.push_back(build_dstack_point_test);

  build_piece build_fmovaddr_test = {
      .build_exec_addr = 0x401002,
      .build_exec_size = 16
  };

  BuildCodeInfo build_fmov_test("../test/insn/fcmov_test.exe");
  build_fmov_test.push_back(build_fmovaddr_test);

  BuildCodeInfo build_sdk_test("../test/insn/sdk_test.exe");
  return build_sdk_test;
}

struct CommandOption{
  const char * Option;
  size_t arg_count;
};

char * file;
void parse_commandline_options(int argc,char * argv[])
{
  /*if (argc > 1)
  {
     for (int i = 1;i < argc;i++)
     {
        if (strcmp(argv[i],"-f") {
            
        }
     }
     
  }*/ 
}

int main(int argc, char* argv[])
{
//	Assembl ss;
//	ss.Assemble("hello:");
	// 显示版本号
	if (argc < 2)
		{
			fprintf(stdout,"%s Version %d.%d\n",
					argv[0],
					WPROTECT_VERSION_MAJOR,
					WPROTECT_VERSION_MINOR);
		}
//	printf("WProtect-%d.%d\r\n",WPROTECT_V,WPROTECT_VERSION_MINOR);
	//


  using namespace AsmJit;
    
  if (argc >= 3)
  {
    if ( strcmp(argv[1],"-f" ) == 0)
    {
      BuildCodeInfo build_pe(argv[2]);
      buildvmtest(build_pe);
      return 0;
    }
  }
  else
  {
    printf("输入错误,WProtect -f 文件名\n");
    return -1;
  }
    

    //return 0;
    //elf_file.AddSection(".WP",1000,6);
    //elf_file.SavePEFile("eee");
    //return 0;
    BuildCodeInfo build_elf_test("./helloWProtect_ELF");
    buildvmtest_elf(build_elf_test);
    CELFFile elf_file;
    if (elf_file.LoadELFFile("helloWProtect_ELF_WP"))
    //if (elf_file.LoadELFFile("elf_wprotect_WP"))
    if (elf_file.IsELFFile())
    {
        printf("Section Count:%d,Program Count:%d\n",elf_file.GetSectionCount(),elf_file.GetProgramCount());
        for (int i = 0; i < elf_file.GetSectionCount();i++)
        {
            Elf32_Shdr * shdr =  elf_file.GetSectionHeader(i);
            printf("sh_name : %s\n", elf_file.GetStringTableStr( shdr->sh_name ));
            printf("sh_type : %#x\n", shdr->sh_type);
            printf("sh_flags : %d\n", shdr->sh_flags);
            printf("sh_addr : %#x\n", shdr->sh_addr);
            printf("sh_offset : %d\n", shdr->sh_offset);
            printf("sh_size : %d\n", shdr->sh_size);
            printf("sh_link : %d\n", shdr->sh_link);
            printf("sh_info : %d\n", shdr->sh_info);
            printf("sh_addralign : %d\n", shdr->sh_addralign);
            printf("sh_entsize : %d\n\n", shdr->sh_entsize);
        }
        for (int i = 0; i < elf_file.GetProgramCount();i++)
        {
            Elf32_Phdr *phdr = elf_file.GetProgramHeader(i);
            printf("p_paddr : %#x\n",phdr->p_paddr);
            printf("p_vaddr : %#x\n",phdr->p_vaddr);
            printf("p_align : %#d\n",phdr->p_align);
            printf("p_offset : %#x\n",phdr->p_offset);
            printf("p_type : %#d\n",phdr->p_type);
            printf("p_flags : %#d\n",phdr->p_flags);
            printf("p_filesz : %#x\n",phdr->p_filesz);
            printf("p_memsz : %#x\n\n",phdr->p_memsz);

        }
    }
    else
    {
        printf("不是ELF文件\n");
    }

    return 0;
    //using namespace wprotect;

    /*
    wprotect::wprotect_elf_file elf_file;
    elf_file.wprotect_elf_load_elf("helloWProtect_ELF");
    if (elf_file.wprotect_elf_check_elf_file())
    {
        //elf_file.wprotect_elf_va_to_ptr()
    }
    else
    {
        printf("不是一个ELF文件\n");
    }*/
  //outofordertest(  );

  //equivalentreplacement_test(  );

  //BuildCodeInfo b_i = get();
  //buildvmtest(b_i);
    BuildCodeInfo b_i = BuildCodeInfo("../test/app/Rubic_Cube1.exe");
    //buildvmtest(b_i);
    BuildCodeInfo b_i1 = BuildCodeInfo("../test/app/Rubic_Cube2.exe");
    //buildvmtest(b_i1);
    BuildCodeInfo b_i2 = BuildCodeInfo("../test/app/Rubic_Cube3.exe");
    //buildvmtest(b_i2);
    BuildCodeInfo b_all = BuildCodeInfo("../test/app/Rubic_Cube.exe");
    buildvmtest(b_all);

    BuildCodeInfo b = BuildCodeInfo("../test/insn/jcc_test.exe");
    //buildvmtest(b);
  //vmtest();
  srand( time( NULL ) );
   getchar();

  //analysistest();

  // ==========================================================================  // Create assembler.

   /*
  Compiler a;
  FileLogger logger(stderr);
  a.setLogger(&logger);
  a.newFunction(CALL_CONV_DEFAULT, FunctionBuilder1<unsigned char,unsigned char*>());
  GPVar result(a.newGP());
  a.add(byte_ptr(a.argGP(0)),12);
  a.movzx(result,byte_ptr(a.argGP(0)));
  a.ret(result);
  a.endFunction();
  typedef unsigned char  (*fuc) (unsigned char &) ;
  fuc f = function_cast<fuc>(a.make());

  unsigned char c = 10;8
  printf ("%d\r\n",c);
  //f(&c);
  printf ("%d\r\n",f(c));*/
  ///////printf("test ret :%d\r\n",test());
	//   return 1;
   return 0;
   //petest();
    run_lua();

  testasm();
  getchar();
  return 0;
}



