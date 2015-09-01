/*********************************************************
 * 开发人员：XiaoWei
 * 创建时间：Thu Jan 16 10:35:34 2014
 * 描述说明：
 * 
 * 更改历史：
 * 
 * *******************************************************/

#include "elffile.hpp"
#include <iostream>
#include <stdio.h>

namespace wprotect
{
  
  wprotect_elf_file::wprotect_elf_file()
  {
  }

  wprotect_elf_file::~wprotect_elf_file()
  {
  }


  bool wprotect_elf_file::wprotect_elf_load_elf(char * file_name)
  {
	bool result = true;
	if (buffer)
	{
      delete [] reinterpret_cast<char *>(buffer);
	  buffer = NULL;
	  size = static_cast<size_t>(0);
	}
	FILE *file = NULL;
	file = fopen(file_name,"rb");
	if (!file)
	{
      result =  false;
	}
	else
	{
      //const signed char size = 1;
      fseek(file,0,SEEK_END);
      size_t len = static_cast<size_t>(ftell(file));
      buffer = new char[len];
      rewind(file);
      fread(buffer,1,len,file);
      fclose(file);
      size = len;
      wprotect_elf_set_mode();
	}
	return result;
  }


  bool wprotect_elf_file::wprotect_elf_load_elf(void *file_buf,size_t size)
  {
	if (buffer)
	{
      delete [] reinterpret_cast<char *>(buffer);
      buffer = NULL;
      size = static_cast<size_t>(0);
	}
	buffer = new char[size+static_cast<size_t>(1)];
	memcpy(buffer,file_buf,size);
    wprotect_elf_set_mode();    
	return true;  
  }


  bool wprotect_elf_file::wprotect_elf_check_elf_file()
  {
    bool result = false;
    Elf32_Ehdr * elf_header = wprotect_elf_get_elf_header32();
    if(
       static_cast<signed char>(elf_header->e_ident[EI_MAG0]) == ELFMAG0 &&
       static_cast<signed char>(elf_header->e_ident[EI_MAG1]) == ELFMAG1 &&
       static_cast<signed char>(elf_header->e_ident[EI_MAG2]) == ELFMAG2
       )
    {
      result = true;
    }
    return result;
  }

  long wprotect_elf_file::wprotect_elf_get_entry() const
  {
     Elf32_Ehdr *elf_header = wprotect_elf_get_elf_header32(); 
     return elf_header->e_entry;
  }

  long wprotect_elf_file::wprotect_elf_get_file_type() const
  {
      Elf32_Ehdr *elf_header = wprotect_elf_get_elf_header32();
      if (elf_header->e_ident[SELFMAG] == static_cast<unsigned char>(ELFCLASS64))
      {
          return 64;
      }
      else
      {
          return 32;
      }
  }
  /*
  void wprotect_elf_file::wprotect_elf_set_mode()
  {
    Elf32_Ehdr *elf_header = wprotect_elf_get_elf_header32();
    if (elf_header->e_ident[SELFMAG] == static_cast<unsigned char>(ELFCLASS32))
    {
      //file_handle.file_info |= WPROTECT_X86_32;
      //file_handle.oep = static_cast<unsigned long>(elf_header->e_entry);
    } else if (elf_header->e_ident[SELFMAG] == static_cast<unsigned char>(ELFCLASS64))
    {
      //file_handle.file_info |= WPROTECT_X86_64;
      //file_handle.oep = elf_header->e_entry;
    }

    if (elf_header->e_type == static_cast<Elf32_Half>(ET_REL))
    {
      file_handle.file_info |= WPROTECT_STATIC_LIBRARY;
    } else if(elf_header->e_type == static_cast<Elf32_Half>(ET_EXEC))
    {
      file_handle.file_info |= WPROTECT_EXECUTABLE_FILE;
    } else if (elf_header->e_type == static_cast<Elf32_Half>(ET_DYN))
    {
      file_handle.file_info |= WPROTECT_SHARED_LIBRARY;
    }

    if (elf_header->e_machine == static_cast<Elf32_Half>(EM_386))
    {
      file_handle.file_info |= WPROTECT_CPU_INTEL_86_32;
    } else if (elf_header->e_machine == static_cast<Elf32_Half>(EM_X86_64))
    {
      file_handle.file_info |= WPROTECT_CPU_AMD_86_64;
    }
  }*/

  void *wprotect_elf_file::wprotect_elf_get_file_buffer() const 
  {
    return buffer;
  }


  Elf32_Ehdr * wprotect_elf_file::wprotect_elf_get_elf_header32() const
  {
    return reinterpret_cast<Elf32_Ehdr *>(wprotect_elf_get_file_buffer());
  }

  Elf64_Ehdr * wprotect_elf_file::wprotect_elf_get_elf_header64() const
  {
    return reinterpret_cast<Elf64_Ehdr*>(wprotect_elf_get_file_buffer());
  }


  Elf32_Phdr * wprotect_elf_file::wprotect_elf_get_program_header32() const
  {
    Elf32_Ehdr * elf_header = wprotect_elf_get_elf_header32();
    return reinterpret_cast<Elf32_Phdr*>(
                                         (elf_header->e_phoff +
                                          reinterpret_cast<char*>(wprotect_elf_get_file_buffer())));
  }

  Elf32_Phdr * wprotect_elf_file::wprotect_elf_get_program_header32(unsigned int index) const
  {
    Elf32_Phdr * result = NULL;
    Elf32_Ehdr * elf_header = wprotect_elf_get_elf_header32();  
    if (index < elf_header->e_phnum)
    {
	  Elf32_Phdr * program_header = wprotect_elf_get_program_header32();
	  result = reinterpret_cast<Elf32_Phdr*>(
                                             reinterpret_cast<char *>(program_header) +
                                             elf_header->e_phentsize * index
                                             );
    }
    return result;
  }

  Elf64_Phdr * wprotect_elf_file::wprotect_elf_get_program_header64() const
  {
    Elf64_Ehdr * elf_header = wprotect_elf_get_elf_header64();
    return reinterpret_cast<Elf64_Phdr *>(
                                          elf_header->e_phoff + reinterpret_cast<char *>(wprotect_elf_get_file_buffer())
                                          );
  }

  Elf64_Phdr * wprotect_elf_file::wprotect_elf_get_program_header64(unsigned int index) const
  {
    Elf64_Phdr * result = NULL;
    Elf64_Ehdr * elf_header = wprotect_elf_get_elf_header64();  
    if (index < elf_header->e_phnum)
    {
      Elf64_Phdr * program_header = wprotect_elf_get_program_header64();
      result = reinterpret_cast<Elf64_Phdr*>(
                                             reinterpret_cast<char *>(program_header) +
                                             elf_header->e_phentsize * index
                                             );
    }
    return result;
  }

  Elf32_Shdr * wprotect_elf_file::wprotect_elf_get_section_header32() const
  {
    Elf32_Ehdr * elf_header = wprotect_elf_get_elf_header32();
    return reinterpret_cast<Elf32_Shdr *>(elf_header->e_shoff +
                                          reinterpret_cast<char *>(wprotect_elf_get_file_buffer()));
  }

  Elf32_Shdr * wprotect_elf_file::wprotect_elf_get_section_header32(unsigned int index) const
  {
    Elf32_Shdr * result = NULL;
    Elf32_Ehdr * elf_header = wprotect_elf_get_elf_header32();    
    if (index < elf_header->e_shnum)
    {
      Elf32_Shdr * section_header = wprotect_elf_get_section_header32();
      result = reinterpret_cast<Elf32_Shdr*>(
                                             reinterpret_cast<char *>(section_header) +
                                             elf_header->e_shentsize * index
                                             );
    }
    return result;
  }

  Elf64_Shdr * wprotect_elf_file::wprotect_elf_get_section_header64() const
  {
    Elf64_Ehdr * elf_header = wprotect_elf_get_elf_header64();
    return reinterpret_cast<Elf64_Shdr*>(
                                         elf_header->e_shoff + reinterpret_cast<char *>(wprotect_elf_get_file_buffer())
                                         );
  }



  Elf64_Shdr * wprotect_elf_file::wprotect_elf_get_section_header64(unsigned int index) const
  {
    Elf64_Shdr * result = NULL;
    Elf64_Ehdr * elf_header = wprotect_elf_get_elf_header64();    
    if (index < elf_header->e_shnum)
    {
      Elf64_Shdr * section_header = wprotect_elf_get_section_header64();
      result = reinterpret_cast<Elf64_Shdr *>(
                                              reinterpret_cast<char *>(section_header) +
                                              elf_header->e_shentsize * index
                                              );
    }
    return result;
  }

  unsigned int wprotect_elf_file::wprotect_elf_get_program_count() const
  {
	unsigned int result = static_cast<unsigned int>(0);
    if (wprotect_elf_get_file_type() == 32)
	{
      Elf32_Ehdr * elf_header = wprotect_elf_get_elf_header32();
      result = elf_header->e_phnum;
	}
    else if (wprotect_elf_get_file_type() == 64)
	{
      Elf64_Ehdr * elf_header = wprotect_elf_get_elf_header64();
      result = elf_header->e_phnum;
	}
	return result;
  }

  unsigned int wprotect_elf_file::wprotect_elf_get_section_count() const
  {
	unsigned int result = static_cast<unsigned int>(0);
    if (wprotect_elf_get_file_type() == 32 )
	{
      Elf32_Ehdr * elf_header = wprotect_elf_get_elf_header32();
      result = elf_header->e_shnum;
	}
    else if (wprotect_elf_get_file_type() == 64 )
	{
      Elf64_Ehdr * elf_header = wprotect_elf_get_elf_header64();
      result = elf_header->e_shnum;
	}
	return result;
  }

  unsigned int  wprotect_elf_file::wprotect_elf_get_va_program_count32(unsigned long va) const
  {
	unsigned int result = static_cast<unsigned int>(-1);
	unsigned int program_count = wprotect_elf_get_program_count();
	while (program_count--)
	{
      Elf32_Phdr * program_header = wprotect_elf_get_program_header32(program_count);
      if (program_header)
      {
        if (va >= program_header->p_vaddr &&
            va <= (program_header->p_vaddr + program_header->p_memsz))
        {
          result = program_count;
          break;
        }
      }
	}
	return result;
  }

  unsigned int  wprotect_elf_file::wprotect_elf_get_va_program_count64(unsigned long long va) const
  {
	unsigned int result = static_cast<unsigned int>(-1);
	unsigned int program_count = wprotect_elf_get_program_count();
	while (program_count--)
	{
      Elf64_Phdr * program_header = wprotect_elf_get_program_header64(program_count);
      if (program_header)
      {
        if (va >= program_header->p_vaddr &&
            va <= (program_header->p_vaddr + program_header->p_memsz))
        {
          result = program_count;
          break;
        }
      }
	}
	return result;
  }

  unsigned int  wprotect_elf_file::wprotect_elf_get_oep_program_count() const
  {
	unsigned int result = static_cast<unsigned int>(-1);
    if (wprotect_elf_get_file_type() == 32)
	{
      result = wprotect_elf_get_va_program_count32(static_cast<unsigned long>(wprotect_elf_get_entry()));
    } else if (wprotect_elf_get_file_type() == 64)
	{
      result = wprotect_elf_get_va_program_count64(static_cast<unsigned long>(wprotect_elf_get_entry()));
	}
	return result;
  }

  void * wprotect_elf_file::wprotect_elf_va_to_ptr(unsigned long va) const
  {
	void * result = NULL;

    if (wprotect_elf_get_file_type() == 32)
	{
      unsigned int index = static_cast<unsigned int>(0);
      index = wprotect_elf_get_va_program_count32(static_cast<unsigned long>(va));
      Elf32_Phdr * program_header = wprotect_elf_get_program_header32(index);
      result = reinterpret_cast<char *>(wprotect_elf_get_file_buffer()) +
        program_header->p_offset + ( static_cast<unsigned long>(va) - program_header->p_vaddr);

    } else if (wprotect_elf_get_file_type() == 64)
	{
      unsigned int index = static_cast<unsigned int>(0);
      index = wprotect_elf_get_va_program_count64(va);
      Elf64_Phdr * program_header = wprotect_elf_get_program_header64(index);
      result = reinterpret_cast<char *>(wprotect_elf_get_file_buffer()) +
        program_header->p_offset + ( va - program_header->p_vaddr);
	}
	return result;
  }

}
