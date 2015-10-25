/****************************************************************************
 *
 * Copyright (C)	2015-10-24 22:09	XiaoWei
 *
 * handsomexiaowei@gmail.com
 *
 * Last modified: 	2015-10-24 22:09
 *
 * Filename: 		vm_protect.h
 *
 * Description: 
 *
 ****************************************************************************/

#ifndef VM_PROTECT_H
#define VM_PROTECT_H

#ifndef WPROTECT_CONFIG_H
#define WPROTECT_CONFIG_H
#include <WProtectConfig.h>
#endif


#ifndef LUA_H
#define LUA_H
extern "C"{
#include "Lua/lua.h"
#include "Lua/lualib.h"
#include "Lua/lauxlib.h"
}
#endif


#include <PESection.h>
#include <PEReloc.h>
#include <VirtualMachineManage.hpp>
#include <PCode.hpp>
#include <SeniorVMHandle.hpp>
#include <Analysis.hpp>
#include <VMAddressTable.hpp>
#include <BuildVMByteCode.hpp>
#include "build_address.hpp"
#include "ELFFile.h"
#include <AdvancedAnalysis.hpp>
#include <logfunctions.h>
 
#ifdef WPROTECT_USE_QT
#include <QTreeWidget>
extern QTreeWidget * ptr_protect_address_tree;
#endif   

class vm_protect : public logfunctions
{
        public:
        void protect_address_disas(const char * _filename,std::map<long,long> & user_protect_address)
        {
#ifdef WPROTECT_USE_QT
                    ptr_protect_address_tree->clear();
#endif


                               CPESection file;
                bool b = file.LoadPEFile(_filename);
                if (!b)
                {
                        error("file is not find\r\n");
                        return;
                }
                if (!file.IsPEFile())
                {
                        error("executable file type error\n");
                        return;
                }
                BuildCodeInfo build_info;
                get_sdk_protect_address(file,build_info,"WProtect Begin","WProtect End");
                for (std::map<long,long>::iterator iter = user_protect_address.begin();
                     iter != user_protect_address.end();iter++)
                {
                    BuildCodeInfo::data_type data;
                    data.build_exec_addr = iter->first;
                    data.build_exec_size = iter->second - iter->first  ;
                    info("User Protect Address:%x - %x",iter->first,iter->second);
                    build_info.push_back(data);
                }
                for (BuildCodeInfo::iterator iter = build_info.begin(); iter != build_info.end(); iter++)
                {
#ifdef WPROTECT_USE_QT
                        //error("abc");
                        QString item_name = QString("0x%0").arg(QString::number(iter->build_exec_addr,16)) ;
                        QTreeWidgetItem * cur_item = new QTreeWidgetItem(ptr_protect_address_tree,QStringList() << item_name);
                        //ptr_protect_address_tree->addChild(cur_iter);
                        ud_t ud_obj;
                        ud_init(&ud_obj);

#ifndef PROTECT_X64
                        ud_set_mode(&ud_obj,32);
#else
                        ud_set_mode(&ud_obj,64);
#endif
                        ud_set_pc(&ud_obj,iter->build_exec_addr);
                        ud_set_input_buffer(&ud_obj, (unsigned char*)file.VaToPtr(iter->build_exec_addr), iter->build_exec_size);
                        ud_set_syntax(&ud_obj,UD_SYN_INTEL);
                        while (ud_disassemble(&ud_obj) != 0)
                        {
                            QTreeWidgetItem * sub_item = new QTreeWidgetItem(cur_item,QStringList() << ud_obj.insn_buffer);
                            //cur_item->addChlid(sub_item);
                        }

#endif
                }
        }
                void add_jmp_addr(CPEFile pe,long base,long jmp_address)
                {
                        char * c = (char*)pe.VaToPtr(base);
                        *(char*)c = 0xe9;
                        *(long*)(c + 1) = jmp_address - base - 5;
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
                                                        info ("table addr:%08x\n",*addr);
#endif
                                                        addr_table_entry_point.push_back(addr);
                                                        addr++;

                                                }
                                        //addr++;
                                }
                        }
                }

                void get_gui_protect_address()
                {
                }

                void get_sdk_protect_address(
                                CPESection & section,
                                BuildCodeInfo & build_info,
                                char *sz_sdk_begin_name,
                                char *sz_sdk_end_name)
                {/*{{{*/
                        int sdk_begin_count = 0;
                        int sdk_end_count = 0;
                        int protect_begin_address = 0;
                        int protect_end_address = 0;
                        int section_count = section.GetSectionCount();
                        for (int index = 0;index <  section_count;index++)
                        {
                                DWORD section_size;
                                BYTE * ptr_section_data = section.GetSectionData(index,&section_size);
                                info("\nSection No.%02d Size 0x%04X Flags 0x%8X IsExecute: %s\n",index,section_size,section.GetCharacteristics(index),(section.GetCharacteristics(index) & 0x20000000)?"true":"false");
                                if (! (section.GetCharacteristics(index) & 0x20000000))
                                {
                                        continue;
                                }
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
                                                pass("Found WProtect Begin offset:%08X, va:%08X\n",
                                                       offset - sdk_begin_str_size,
                                                       section.GetSectionVa(index,offset - sdk_begin_str_size));
                                                protect_begin_address = section.GetSectionVa(index,offset - sdk_begin_str_size);
                                                memset((void*)section.GetSectionPtr(index,offset - sdk_begin_str_size),0x90,sdk_begin_count);
                                                sdk_begin_count = 0;

                                                //__asm__("int3");
                                        }
                                        if (sdk_end_count == strlen(sz_sdk_end_name) + 3)
                                        {
                                                pass("Found WProtect End   offset:%08X\n",offset - strlen(sz_sdk_end_name) - 1);
                                                int sdk_end_str_size = strlen(sz_sdk_end_name) + 1;
                                                protect_end_address = section.GetSectionVa(index,offset - sdk_end_str_size);
                                                if (protect_begin_address == 0 )
                                                {
                                                        printf("%08X Can not find a mathing WProtect Begin\n",protect_end_address);
                                                }
                                                else
                                                {
                                                        build_piece piece;
                                                        piece.build_exec_addr = protect_begin_address;
                                                        piece.build_exec_size = protect_end_address - protect_begin_address + sdk_end_str_size + 2;
                                                        info("Protect Address: %08X - %08X\n",piece.build_exec_addr,piece.build_exec_addr+piece.build_exec_size);
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

                }/*}}}*/
                void load(const char * _filename)
                {
                }
                void protect_code(const char * _filename,std::map<long,long> & user_protect_address)
                {
                        BuildCodeInfo build_info;
                        build_info.set_filename(_filename);  
                        VirtualMachineManage vm;
                        CodeBufferInfo info;
                        CPEFile file;

                        const char * build_exec_name = build_info.get_filename();
                        bool b = file.LoadPEFile(build_exec_name);
                        if (!b)
                        {
                                error("file is not find\r\n");
                                return;
                        }
                        if (!file.IsPEFile())
                        {
                                error("executable file type error\n");
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
                        get_sdk_protect_address(section,build_info,"WProtect Begin","WProtect End");
                        for (std::map<long,long>::iterator iter = user_protect_address.begin();
                     iter != user_protect_address.end();iter++)
                {
                    BuildCodeInfo::data_type data;
                    data.build_exec_addr = iter->first;
                    data.build_exec_size = iter->second - iter->first;
                    logfunctions::info("User Protect Address:%x - %x",iter->first,iter->second);
                    build_info.push_back(data);
                }

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
                                        panic("Protect Size less than 5 Byte\n");
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
                                                panic("编译的地址不能小于5Byte,这段指令编译失败\n");
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
                        pass("Out File:%s\n",new_file_name);
                        //pfile = fopen( "virtualmachine","wb" );
                        //fwrite( pvm->vm_info.buf,1,pvm->vm_info.size,pfile );
                        //fclose( file );

                        //delete [  ] buf;
                }
        private:
                //BuildCodeInfo build_info;
                bool load_file_ok;
                CPEFile dis_file; 
};

#endif /* end of include guard: VM_PROTECT_H */
