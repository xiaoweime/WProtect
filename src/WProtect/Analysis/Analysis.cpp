#include "Analysis.hpp"
#include <WProtectConfig.h>

Analysis::Analysis()
  :L(false),R(true),block_count(0),base(0),size(0)
{
  root = NULL;
}

Analysis::~Analysis()
{
  clean_tree();
}

pAssemblerTree Analysis::add_tree(pAssemblerTree parent,pAssemblerTree child,bool l_r) //left and right
{
  if (child == root)
  {
    return root;
  }
  if (l_r == L)
  {
    parent->LeftChild = child;
  }
  else
  {
    parent->RightChild = child;
  }
  return child;
}


void show_tree(pAssemblerTree root,char note[256])
{
  pAssemblerTree nowtree = root;
  while (nowtree)
  {
    for (std::vector <ud_t>::iterator iter = nowtree->asmpiece.begin(); iter != nowtree->asmpiece.end(); ++iter)
    {
      ud_t ud = *iter;
      printf("%s:%x:",note,ud.insn_offset); 
      printf("%s \r\n",ud.insn_buffer);
      
    }
      printf("Left %x\r\n",nowtree->LeftChild);
      printf("Right %x\r\n",nowtree->RightChild);
      //int n;
      //1scanf("%d",&n);    
      // printf("\r\n");
    /*
    if (nowtree->RightChild)
    {
      show_tree(nowtree->RightChild,"true:");
    }
    */
    nowtree = nowtree->LeftChild;
  }    
}

void show_tree(pAssemblerTree root)
{
  pAssemblerTree nowtree = root;
  while (nowtree)
  {
    printf ("base:%x,size:%x\r\n",nowtree->base,nowtree->size);
    
    for (std::vector <ud_t>::iterator iter = nowtree->asmpiece.begin(); iter != nowtree->asmpiece.end(); ++iter)
    {
      ud_t ud = *iter;
      printf("%x:",ud.insn_offset); 
      printf("%s \r\n",ud.insn_buffer);
    }
    printf("\r\n");
    nowtree = nowtree->LeftChild;
  }    
}

void Analysis::clean_tree()
{
  if (root)
  {
    pAssemblerTree nowtree = root;
    pAssemblerTree oldtree = NULL;
    while (nowtree)
    {
      oldtree = nowtree;
      nowtree = nowtree->LeftChild;
      delete oldtree;
    }
  }
}

pAssemblerTree Analysis::get_tree(long id)
{
  pAssemblerTree nowtree = root;
  while (nowtree)
  {
    if (nowtree->id == id)
    {
      return nowtree;
    }
    //nowtree = nowtree->RightChild;
    nowtree = nowtree->LeftChild;
  }
  return NULL;
}

pAssemblerTree Analysis::find_tree(long addr)
{
  pAssemblerTree nowtree = root;
  while (nowtree)
  {
    if (nowtree->base == addr)
    {
      return nowtree;
    }
    nowtree = nowtree->LeftChild;
  }
  return NULL;
}

size_t Analysis::reloc_asm_address(long old_address,long new_address) //返汇编块的地址
{
  size_t size;
  pAssemblerTree nowtree = root;
  while (nowtree)
  {
    if (nowtree->base == old_address)
    {
      nowtree->reloc_address = new_address;
      size++;
    }
    if (nowtree->jcc_addr == old_address)
    {
      nowtree->jcc_addr = new_address;
      size++;
    }
    if (nowtree->next_instruction == old_address)
    {
      nowtree->next_instruction = new_address;
      size++;
    }
    
    nowtree = nowtree->LeftChild;
  }
  return size;
}

size_t Analysis::reloc_asm_address()
{
  size_t size;
  pAssemblerTree nowtree = root;
  
  while (nowtree)
  {
    if (-1 != nowtree->reloc_address)
    {
      pAssemblerTree nowtree2 = root;
      while (nowtree2)
      {
        if (nowtree2->jcc_addr == nowtree->base)
        {
          nowtree2->jcc_addr = nowtree->reloc_address;
        }
        if (nowtree2->next_instruction == nowtree->base)
        {
          nowtree2->next_instruction = nowtree->reloc_address;
        }
        nowtree2 = nowtree2->LeftChild;
      }
    }
    
    nowtree = nowtree->LeftChild;
  }
  return size;  
}

void Analysis::link_tree()
{
  pAssemblerTree nowtree = root;
  while (nowtree)
  {
    ud_t ud = nowtree->asmpiece.back();
    if (ud.operand[0].type == UD_OP_JIMM && ud.mnemonic != UD_Icall)
    {
      long addr = ud.operand[0].size == 8 ? ((signed char)ud.operand[0].lval.sbyte + ud.pc) : (ud.operand[0].lval.sdword + ud.pc);
      pAssemblerTree tree_R= find_tree(addr);
      if (tree_R)
      {
         nowtree->RightChild = tree_R;
         nowtree->jcc_addr = addr;
      }
    }  
    nowtree = nowtree->LeftChild;
  }
}

void Analysis::set_eflag(  )
{
  /*
  pAssemblerTree nowtree = root;
  while ( nowtree )
  {
     switch ( ud_obj.mnemonic )
     {
     case UD_Itest:
       break;
     case UD_Icmp:
       break;
     case UD_Iand:
       break;
     case UD_Ior:
       break;
     case UD_Ixor:
       break;
       case UD_I
     }
     nowtree = nowtree->LeftChild;
  }
  */
}

bool Analysis::check_address(long addr  )
{
  if (addr <= base + size && addr >= base)
  {
    return true;
  }
  else
    return false;
}
   

void Analysis::set_label_address(pCodeBufferInfo pinfo,
                                 AddressArray & _addra,
                                 std::map<long,int> & _map)
{
  ud_t ud_obj;
  ud_init(&ud_obj);

#ifndef PROTECT_X64
  ud_set_mode(&ud_obj,32);
#else
  ud_set_mode(&ud_obj,64);
#endif
  ud_set_pc(&ud_obj,pinfo->addr);
  ud_set_input_buffer(&ud_obj, (uint8_t*)pinfo->buf, pinfo->size);
  ud_set_syntax(&ud_obj,UD_SYN_INTEL);
  std::vector <ud_t> ud_obj_array;
  
  int label = 0;
  while (ud_disassemble(&ud_obj) != 0)
  {
     if (ud_obj.insn_offset > _addra[label])
     {
       //printf("当前地址不可能比分支地址大");
     }
     if (ud_obj.insn_offset == _addra[label])
     {
       _map.insert(std::make_pair(ud_obj.insn_offset,label));
       //printf("地址:%08x,标签:%d\n",ud_obj.insn_offset,label);
       label++;
     }
  } 

}

void Analysis::disasm(pCodeBufferInfo pinfo,std::vector<CodePiece> & code)
{
    ud_t ud_obj;
    ud_init(&ud_obj);

#ifndef PROTECT_X64
    ud_set_mode(&ud_obj,32);
#else
    ud_set_mode(&ud_obj,64);
#endif
    ud_set_pc(&ud_obj,pinfo->addr);
    ud_set_input_buffer(&ud_obj, (uint8_t*)pinfo->buf, pinfo->size);
    ud_set_syntax(&ud_obj,UD_SYN_INTEL);

    base = pinfo->addr;
    size = pinfo->size;
    AddressArray a_array = analysis_code_piece_address(pinfo);

    int point = 0;
    const bool begin = true;
    const bool end = false;
    bool status = end;
    std::map<long,int> addr_id;

    set_label_address(pinfo,a_array,addr_id);
    CodePiece *piece = NULL;
    while (ud_disassemble(&ud_obj) != 0)
    {

        if (ud_obj.insn_offset == a_array[point] && status == end)
        {
            piece = new CodePiece;
            piece->set_label(point);
            point++;
            status = begin;
        }
        if (a_array.get_size() > point)
        {
            if (ud_obj.pc == a_array[point])
            {
                if (addr_id.find(ud_obj.pc) == addr_id.end()) //下条指令没有找到
                {
#ifdef DEBUG
                    printf("没有查找到数据,地址%08x\n",ud_obj.pc)  ;
#endif
                    //piece->set_jmplabel(PC_NONE);
                    if (ud_obj.mnemonic == UD_Iret)
                    {
                        //piece->set_jmplabel(PC_NONE);
                        piece->set_opcode_attribute(OPCODE_ATTRIBUTE_RET);
                    }
                    else if (ud_insn_mnemonic(&ud_obj) == UD_Ijmp)
                    {
                        long addr = ud_obj.operand[0].size == 8
                                            ? ((signed char)ud_obj.operand[0].lval.sbyte + ud_obj.pc) :
                                    (ud_obj.operand[0].lval.sdword + ud_obj.pc);
                        if (addr >= pinfo->addr && addr <= pinfo->addr + pinfo->size
                                && ud_obj.operand[0].type == UD_OP_JIMM)
                        {
                            piece->set_opcode_attribute(OPCODE_ATTRIBUTE_JMP);
                            piece->set_jmplabel(addr_id[addr]);
                        }
                        else
                        {
                           piece->set_opcode_attribute(OPCODE_ATTRIBUTE_EXTERNAL_JMP);
                           if (ud_obj.operand[0].type == UD_OP_JIMM)
                               piece->set_jmplabel(addr);
                           else
                               piece->set_jmplabel(PC_NONE);

                        }
                    }
                    else if (ud_insn_mnemonic(&ud_obj) == UD_Icall)
                    {
                        long addr = ud_obj.operand[0].size == 8
                                            ? ((signed char)ud_obj.operand[0].lval.sbyte + ud_obj.pc) :
                                    (ud_obj.operand[0].lval.sdword + ud_obj.pc);
                        //if (addr >= pinfo->addr && addr <= pinfo->addr + pinfo->size &&
                        if (addr >= pinfo->addr && addr < pinfo->addr + pinfo->size &&
                                ud_obj.operand[0].type == UD_OP_JIMM)
                        {
                            piece->set_opcode_attribute(OPCODE_ATTRIBUTE_CALL);
                            piece->set_jmplabel(addr_id[addr]);
                        }
                        else
                        {
                           piece->set_opcode_attribute(OPCODE_ATTRIBUTE_EXTERNAL_CALL);
                           if (ud_obj.operand[0].type == UD_OP_JIMM)
                               piece->set_jmplabel(addr);
                           else
                               piece->set_jmplabel(PC_NONE);
                        }
                    }
                    else
                    {
                        piece->set_opcode_attribute(OPCODE_ATTRIBUTE_EXIT);
                        piece->set_jmplabel(ud_obj.pc);
                    }
                }
                else
                {
                    if (ud_obj.operand[0].type == UD_OP_JIMM
                            || ud_obj.mnemonic == UD_Icall
                            || ud_obj.mnemonic == UD_Ijmp)//&& ud_obj.mnemonic != UD_Icall)
                    {
                        piece->set_is_jcc(ud_obj.mnemonic != UD_Icall &&
                                        ud_obj.mnemonic != UD_Iret &&
                                        ud_obj.mnemonic != UD_Ijmp);
                        if (ud_obj.operand[0].type == UD_OP_MEM
                                || ud_obj.operand[0].type == UD_OP_REG)
                        {
                            if (ud_insn_mnemonic(&ud_obj) == UD_Ijmp)
                            {
                                piece->set_opcode_attribute(OPCODE_ATTRIBUTE_EXTERNAL_JMP);
                            }
                            else if (ud_insn_mnemonic(&ud_obj) == UD_Icall)
                            {
                                piece->set_opcode_attribute(OPCODE_ATTRIBUTE_EXTERNAL_CALL);
                            }
                            else
                            {
                               //piece->set_opcode_attribute(OPCODE_ATTRIBUTE_JCC);
                            }
                            piece->set_jmplabel(PC_NONE);
                        }
                        else
                        {
                            long addr = ud_obj.operand[0].size == 8
                                            ? ((signed char)ud_obj.operand[0].lval.sbyte + ud_obj.pc) :
                                    (ud_obj.operand[0].lval.sdword + ud_obj.pc);
                            if (addr >= pinfo->addr && addr < pinfo->addr + pinfo->size) //<=pinfo->addr + pinfo->size将导致跳转到最后一条指令的下一条还是在范围之内
                            {
                                if (addr_id.find(addr) == addr_id.end())
                                {
                                    printf("没有找到跳转地址:%08x\n",addr );
                                }
                                if (ud_insn_mnemonic(&ud_obj) == UD_Ijmp)
                                {
                                   piece->set_opcode_attribute(OPCODE_ATTRIBUTE_JMP);
                                   piece->set_jmplabel(addr_id[addr]);
                                }
                                else if (ud_insn_mnemonic(&ud_obj) == UD_Icall)
                                {
                                   piece->set_opcode_attribute(OPCODE_ATTRIBUTE_CALL);
                                   piece->set_jmplabel(addr);
                                }
                                else
                                {
                                   piece->set_opcode_attribute(OPCODE_ATTRIBUTE_JCC);
                                   piece->set_jmplabel( addr_id[addr] );
                                }
                            }
                            else
                            {
                                if (ud_insn_mnemonic(&ud_obj) == UD_Ijmp)
                                {
                                   piece->set_opcode_attribute(OPCODE_ATTRIBUTE_EXTERNAL_JMP);
                                   //piece->set_jmplabel(addr_id[addr]);
                                }
                                else if (ud_insn_mnemonic(&ud_obj) == UD_Icall)
                                {
                                   piece->set_opcode_attribute(OPCODE_ATTRIBUTE_EXTERNAL_CALL);
                                   //piece->set_jmplabel(addr);
                                }
                                else
                                {
                                   //piece->set_opcode_attribute(OPCODE_ATTRIBUTE_JCC);
                                   printf("jcc不能跳转到虚拟机外部\n");
                                   //piece->set_jmplabel( addr_id[addr] );
                                }
                                piece->set_jmplabel(addr);
                            }
                        }
                    }
                    else
                    {
                        piece->set_jmplabel( addr_id[ud_obj.pc] );
                        piece->set_opcode_attribute(OPCODE_ATTRIBUTE_NORMAL);
                    }
                }
                if (ud_obj.mnemonic == UD_Iret)
                {
                    piece->set_jmplabel(PC_NONE);
                    piece->set_opcode_attribute(OPCODE_ATTRIBUTE_RET);
                    //piece->set_jmplabel(PC_RET);
                }
                piece->add_assemble(ud_obj);
                code.push_back(*piece);
                delete piece;
                piece = NULL;
                status = end;

            }
        }
        if (status == begin)
        {
            if (piece == NULL) {
                printf("没有为piece分配空间");
            }
            piece->add_assemble(ud_obj);
        }

    }
}

void Analysis::analysis_address_table(pCodeBufferInfo pinfo,
                                      std::vector<long> & addr_entry_table,
                                      long addr_min,
                                      long addr_max) //jmp [addr_table + reg] 查找addr_table里面的值
{
/*#define WINDOWS
#include <Windows.h>
    HMODULE module = LoadLibrary("");
#endif
*/
    ud_t ud_obj;
    ud_init(&ud_obj);

#ifndef PROTECT_X64
    ud_set_mode(&ud_obj,32);
#else
    ud_set_mode(&ud_obj,64);
#endif
    ud_set_pc(&ud_obj,pinfo->addr);
    ud_set_input_buffer(&ud_obj, (uint8_t*)pinfo->buf, pinfo->size);
    ud_set_syntax(&ud_obj,UD_SYN_INTEL);
    while(ud_disassemble(&ud_obj) != 0)
    {
        if (ud_obj.operand[0].type == UD_OP_MEM)
        {
            if (ud_obj.operand[0].offset == 32)
            {
                long addr = ud_obj.operand[0].lval.sdword;
                if (addr <= addr_max && addr >= addr_min)
                  addr_entry_table.push_back(addr);
            }
        }
        if (ud_obj.operand[1].type == UD_OP_MEM)
        {
            if (ud_obj.operand[1].offset == 32)
            {
                long addr = ud_obj.operand[1].lval.sdword;
                if (addr <= addr_max && addr >= addr_min)
                   addr_entry_table.push_back(addr);
            }
        }
        //if (ud_insn_mnemonic(&ud_obj) == UD_Ijmp && ud_obj.operand[0].type == UD_OP_MEM)
        //{
        //}
    }
}

void Analysis::printf_piece(std::vector<CodePiece> & var_piece)
{
#ifdef DEBUG
   for (std::vector<CodePiece>::iterator iter = var_piece.begin();
      iter != var_piece.end();iter++)
  {
    char * opcode_attribute = NULL;
    switch (iter->get_opcode_attribute()) {
    case OPCODE_ATTRIBUTE_CALL:
        opcode_attribute = "OPCODE_ATTRIBUTE_CALL";
        break;
    case OPCODE_ATTRIBUTE_EXIT:
        opcode_attribute = "OPCODE_ATTRIBUTE_EXIT";
        break;
    case OPCODE_ATTRIBUTE_JCC:
        opcode_attribute = "OPCODE_ATTRIBBUTE_JCC";
        break;
    case OPCODE_ATTRIBUTE_NORMAL:
        opcode_attribute = "OPCODE_ATTRIBUTE_NORMAL";
        break;
    case OPCODE_ATTRIBUTE_RET:
        opcode_attribute = "OPCODE_ATTRIBUTE_RET";
        break;
    case OPCODE_ATTRIBUTE_JMP:
        opcode_attribute = "OPCODE_ATTRIBUTE_JMP";
        break;
    case OPCODE_ATTRIBUTE_EXTERNAL_JMP:
        opcode_attribute = "OPCODE_ATTRIBUTE_EXTERNAL_JMP";
        break;
    case OPCODE_ATTRIBUTE_EXTERNAL_JCC:
        opcode_attribute = "OPCODE_ATTRIBUTE_EXTERNAL_JCC";
        break;
    case OPCODE_ATTRIBUTE_EXTERNAL_CALL:
        opcode_attribute = "OPCODE_ATTRIBUTE_EXTERNAL_CALL";
        break;
    default:
        opcode_attribute = "NO_ATTRIBUTE";
        break;
    }
    printf("\033[31m标签:%08x,\033[34m跳转到:%08x\033[0m,条件跳转:%d,代码块属性%s\n",
           iter->get_label(),
           iter->get_jmplabel(),
           iter->get_is_jcc(),
           opcode_attribute);
    for (std::list<ud_t>::iterator xiter = iter->get_piece().begin();
        xiter != iter->get_piece().end();xiter++)
    {
        printf("%s\n",xiter->insn_buffer);
    }
  }
#endif
           
}           

pAssemblerTree Analysis::disasm(pCodeBufferInfo pinfo)
{
  std::vector<CodePiece> piece_test;
  disasm(pinfo,piece_test) ;
  for (std::vector<CodePiece>::iterator iter = piece_test.begin();
      iter != piece_test.end();iter++)
  {
    printf("\033[31m标签:%08x,\033[34m跳转到:%08x\033[0m,条件跳转:%d\n",iter->get_label(),iter->get_jmplabel(),iter->get_is_jcc());   
    for (std::list<ud_t>::iterator xiter = iter->get_piece().begin();
        xiter != iter->get_piece().end();xiter++)
    {
        printf("%s\n",xiter->insn_buffer);
    }
  }

  //__asm("int3");
  ud_t ud_obj;
  ud_init(&ud_obj);

#ifndef PROTECT_X64
  ud_set_mode(&ud_obj,32);
#else
  ud_set_mode(&ud_obj,64);
#endif
  ud_set_pc(&ud_obj,pinfo->addr);
  ud_set_input_buffer(&ud_obj, (uint8_t*)pinfo->buf, pinfo->size);
  ud_set_syntax(&ud_obj,UD_SYN_INTEL);

  base = pinfo->addr;
  size = pinfo->size;
  
  std::vector <long> address_array;
  //pAssemblerTree root =  new AssemblerTree;
  //  pAssemblerTree nowtree = root;
  std::vector <ud_t> ud_obj_array;
  address_array.push_back(pinfo->addr);
  address_array.push_back(pinfo->addr + pinfo->size);
  while (ud_disassemble(&ud_obj) != 0)
  {
    ud_obj_array.push_back(ud_obj);
    //    nowtree.asmpiect.push_back(ud_obj);
    if (ud_obj.operand[0].type == UD_OP_JIMM || ud_obj.mnemonic == UD_Icall )//&& ud_obj.mnemonic != UD_Icall)
    {
          long addr = ud_obj.operand[0].size == 8
            ? ((signed char)ud_obj.operand[0].lval.sbyte + ud_obj.pc) :
            (ud_obj.operand[0].lval.sdword + ud_obj.pc);
      if (addr >= pinfo->addr && addr <= pinfo->addr + pinfo->size)
      {
         address_array.push_back(addr);
         address_array.push_back(ud_obj.pc);        
      }
    }
  }

  long count = 0;
  long *a_array;
  size_t address_size = address_array.size();
  a_array = new long[address_size];
  for (std::vector <long>::iterator iter = address_array.begin() ;
       iter != address_array.end() ; ++iter)
  {
    bool fk = true;
    for (int i = 0; i < count; ++i)
    {
      if (*iter == a_array[i])
      {
        fk = false;
      }
    }
    if (fk)
      a_array[count++] = *iter;
  }
  for (int i = 0; i < count; ++i)
  {
    for (int j = i; j < count ; ++j)
    {
      if (a_array[i] > a_array[j])
      {
        long t = a_array[i];
        a_array[i] = a_array[j];
        a_array[j] = t;
      }
    }
  }

  for (int i = 0; i < count; ++i)
  {
    printf("%08x\r\n",a_array[i]);
  }
  int point = 0;
  pAssemblerTree nowtree = NULL;
  pAssemblerTree parent = NULL;
      const bool begin = true;
    const bool end = false;
    bool status = end;
  for (std::vector <ud_t>::iterator iter = ud_obj_array.begin();
       iter != ud_obj_array.end(); ++iter)
  {
    //typedef  true begin;
    //typedef false end;
    // ud_t *p = iter;
    ud_t ud = *iter;
    if (ud.insn_offset == a_array[point] && status == end)
    {
      point++;
      status = begin;
      nowtree = new AssemblerTree;
      root ? NULL : root = nowtree;
      nowtree->LeftChild = NULL;
      nowtree->RightChild = NULL;

      nowtree->id = point - 1;


      //      nowtree.asmpiect.push_back(ud);
    }
    if (nowtree)
    {
      nowtree->asmpiece.push_back(ud);
    }
    if (ud.pc == a_array[point] && status == begin)
    {
      nowtree->base = a_array[point-1];
      
      //point++;
      nowtree->size = ud.pc - a_array[point-1]; //代码块大小
      status = end;
      parent = add_tree(parent,nowtree,L);
      
      //nowtree = new AssemblerTree;
      //nowtree->LeftChild = NULL;
      //nowtree->RightChild = NULL;
    }
    nowtree->reloc_address = -1;    
    nowtree->next_instruction = ud.pc;   
  }
  block_count = point;
  link_tree();
#ifdef DEBUG
  show_tree(root,"false:");
#endif
  delete [] a_array;
  // show_tree(root);
  
  /*for (std::vector <long>::iterator iter = address_array.begin() ;
       iter != address_array.end() ; ++iter)
  {
    int addr = *iter;
    printf("%08x\r\n",addr);
    }*/
  return NULL;
}

  

 //分析代码块地址

AddressArray Analysis::analysis_code_piece_address(pCodeBufferInfo pinfo)
{
  ud_t ud_obj;
  ud_init(&ud_obj);

#ifndef PROTECT_X64
  ud_set_mode(&ud_obj,32);
#else
  ud_set_mode(&ud_obj,64);
#endif
  ud_set_pc(&ud_obj,pinfo->addr);
  ud_set_input_buffer(&ud_obj, (uint8_t*)pinfo->buf, pinfo->size);
  ud_set_syntax(&ud_obj,UD_SYN_INTEL);

  base = pinfo->addr;
  size = pinfo->size;
  
  std::vector <long> address_array;
  //pAssemblerTree root =  new AssemblerTree;
  //  pAssemblerTree nowtree = root;
  
  address_array.push_back(pinfo->addr);
  address_array.push_back(pinfo->addr + pinfo->size);
  while (ud_disassemble(&ud_obj) != 0)
  {
    //if (ud_obj.operand[0].type == UD_OP_JIMM || ud_obj.mnemonic == UD_Icall )//&& ud_obj.mnemonic != UD_Icall)
    if (ud_obj.pfx_rep != 0 || ud_obj.pfx_repe != 0 || ud_obj.pfx_repne != 0)   //有前缀
    {
      address_array.push_back(ud_obj.pc);
      address_array.push_back(ud_obj.insn_offset);
    }
    if (ud_obj.operand[0].type == UD_OP_JIMM )
    {

          long addr = ud_obj.operand[0].size == 8
            ? ((signed char)ud_obj.operand[0].lval.sbyte + ud_obj.pc) :
            (ud_obj.operand[0].lval.sdword + ud_obj.pc);

      if (addr >= pinfo->addr && addr <= pinfo->addr + pinfo->size)
      {
         address_array.push_back(addr);
         address_array.push_back(ud_obj.pc);        
      }
      else
      {
        //address_array.push_back(ud_obj.pc);
        if (ud_obj.mnemonic != UD_Icall && ud_obj.mnemonic != UD_Ijmp)
        {
          printf("%x:跳转的地址无法找到:",ud_obj.insn_offset);
          printf("%x\n",addr);
         // __asm("int3");         //表示跳转地址是一个jcc指令
        }
        else
        {
          address_array.push_back(ud_obj.pc);
        }
      }
    }
    if (ud_obj.mnemonic == UD_Iret || ud_obj.mnemonic == UD_Icall || ud_obj.mnemonic == UD_Ijmp)
    {
      address_array.push_back(ud_obj.pc);
    }
    /*if (ud_obj.mnemonic == UD_Icall || ud_obj.mnemonic == UD_Iret)
    {
      address_array.push_back(ud_obj.pc);
    }*/
  }
  long count = 0;
  
  size_t address_size = address_array.size();
  AddressArray a_array(address_size);  
  for (std::vector <long>::iterator iter = address_array.begin() ;
       iter != address_array.end() ; ++iter)
  {
    bool fk = true;
    for (int i = 0; i < count; ++i)
    {
      if (*iter == a_array[i])
      {
        fk = false;
      }
    }
    if (fk)
      a_array[count++] = *iter;
  }
  for (int i = 0; i < count; ++i)
  {
    for (int j = i; j < count ; ++j)
    {
      if (a_array[i] > a_array[j])
      {
        long t = a_array[i];
        a_array[i] = a_array[j];
        a_array[j] = t;
      }
    }
  }
  a_array.set_size(count); 
#ifdef DEBUG
  //printf("a_array size:%08x",a_array.get_size()); 
  for (int i = 0; i < count - 1; ++i)
  {
    
    printf("标签%x,分支地址:%08x - %08x\n",i,a_array[i],a_array[i+1]-1);
  }
//__asm ("int3");
#endif
  
  return a_array;
} 
