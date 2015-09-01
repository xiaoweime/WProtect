/*********************************************************
 * 开发人员：XiaoWei
 * 创建时间：Thu Jan 16 10:35:45 2014
 * 描述说明：
 * 
 * 更改历史：
 * 
 * *******************************************************/


#ifndef _ELFFILE_H_
#define _ELFFILE_H_

//#include <load_file.hpp>
#include <elf.h>
#include <string.h>


#define WPROTECT_ASSIST(test) if (test)\
{\
}\

namespace wprotect
{
  
  class wprotect_elf_file
  {
  public:
    wprotect_elf_file();
    virtual ~wprotect_elf_file();

    bool wprotect_elf_load_elf(char * file_name);

    bool wprotect_elf_load_elf(void *file_buf,size_t size);

    bool wprotect_elf_check_elf_file();
  
    void wprotect_elf_set_mode();
  
    void *wprotect_elf_get_file_buffer()  const;
  
    Elf32_Ehdr * wprotect_elf_get_elf_header32() const;
  
    Elf64_Ehdr * wprotect_elf_get_elf_header64() const ;
  
    Elf32_Phdr * wprotect_elf_get_program_header32() const;
  
    Elf32_Phdr * wprotect_elf_get_program_header32(unsigned int index) const;
  
    Elf64_Phdr * wprotect_elf_get_program_header64() const;
  
    Elf64_Phdr * wprotect_elf_get_program_header64(unsigned int index) const;
  
    Elf32_Shdr * wprotect_elf_get_section_header32() const;
  
    Elf32_Shdr * wprotect_elf_get_section_header32(unsigned int index) const;
  
    Elf64_Shdr * wprotect_elf_get_section_header64()const;
  
    Elf64_Shdr * wprotect_elf_get_section_header64(unsigned int index) const;
  
    unsigned int wprotect_elf_get_program_count() const;

    unsigned int wprotect_elf_get_section_count() const;

    unsigned int  wprotect_elf_get_va_program_count32(unsigned long va) const;

    unsigned int  wprotect_elf_get_va_program_count64(unsigned long long va) const;

    unsigned int wprotect_elf_get_oep_program_count() const;

    void * wprotect_elf_va_to_ptr(unsigned long va) const;

    long wprotect_elf_get_entry() const;

    long wprotect_elf_get_file_type() const;

    //wprotect_file_handle file_handle;
  private:
    char *buffer;
    size_t size;
  };

}

#endif /* _ELFFILE_H_ */
