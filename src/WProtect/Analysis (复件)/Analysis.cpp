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
  printf("a_array size:%08x",a_array.get_size()); 
  for (int i = 0; i < count - 1; ++i)
  {
    
    printf("分支地址:%08x - %08x\r\n",a_array[i],a_array[i+1]-1);
  }
//__asm ("int3");
#endif
  
  return a_array;
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
  std::vector <ud_t> ud_obj_array; 
  while (ud_disassemble(&ud_obj) != 0)
  {
    ud_obj_array.push_back(ud_obj);
  } 
  base = pinfo->addr;
  size = pinfo->size;
  AddressArray a_array = analysis_code_piece_address(pinfo);

  int point = 0;
  pAssemblerTree nowtree = NULL;
  pAssemblerTree parent = NULL;
  const bool begin = true;
  const bool end = false;
  bool status = true;
  std::map<int,long> addr_id;
  CodePiece piece; 
  for (std::vector <ud_t>::iterator iter = ud_obj_array.begin();
       iter != ud_obj_array.end(); ++iter)
  {
    
    ud_t ud = *iter;
    if (ud.insn_offset == a_array[point] && status == begin)
    {
       piece.set_label(point);
       addr_id.insert(std::make_pair<int,long>(point,ud.insn_offset));
       point++;
    }
    if (a_array.get_size() <= point)
    {
      if (ud.pc == a_array[point]) {
         status = end;
      }
    }
    if (status == begin)
    {
       piece.add_assemble(ud);
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
  
  }
  block_count = point;
  link_tree();
#ifdef DEBUG
  show_tree(root,"false:");
#endif
  // show_tree(root);
  
  /*for (std::vector <long>::iterator iter = address_array.begin() ;
       iter != address_array.end() ; ++iter)
  {
    int addr = *iter;
    printf("%08x\r\n",addr);
    }*/
}
 

pAssemblerTree Analysis::disasm(pCodeBufferInfo pinfo)
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


