#include "ELFFile.h"
#include <stdio.h>
#include <string.h>

CELFFile::CELFFile()
    :buffer(NULL),size(0)
{
}
CELFFile::~CELFFile(){
}

void CELFFile::FreeImage()
{
   if (buffer != NULL)
   {
       delete [] buffer;
       size = 0;
   }
   buffer = NULL;
   size = 0;
}

void *CELFFile::ReallocImage(size_t _size)
{
    if (_size > size && buffer != NULL)
    {
        unsigned char * new_buffer = new unsigned char [_size];
        memset(new_buffer,0xc3,_size);
        memcpy(new_buffer,buffer,size);
        FreeImage();
        size = _size;
        buffer = new_buffer;
    }
    return buffer;
}

bool CELFFile::LoadELFFile(char * elf_file_name)
{
    bool result = true;
    if (buffer)
    {
      delete [] reinterpret_cast<char *>(buffer);
      buffer = NULL;
      size = static_cast<size_t>(0);
    }
    FILE *file = NULL;
    file = fopen(elf_file_name,"rb");
    if (!file)
    {
      result =  false;
    }
    else
    {
      //const signed char size = 1;
      fseek(file,0,SEEK_END);
      size_t len = static_cast<size_t>(ftell(file));
      buffer = new unsigned char[len];
      rewind(file);
      fread(buffer,1,len,file);
      fclose(file);
      size = len;
    }
    return result;
}

bool CELFFile::IsELFFile()
{
    Elf32_Ehdr *elf_header = GetElfHeader();
    if (elf_header->e_ident[SELFMAG] == static_cast<unsigned char>(ELFCLASS32) &&
        static_cast<signed char>(elf_header->e_ident[EI_MAG0]) == ELFMAG0 &&
        static_cast<signed char>(elf_header->e_ident[EI_MAG1]) == ELFMAG1 &&
        static_cast<signed char>(elf_header->e_ident[EI_MAG2]) == ELFMAG2     )
    {
        return true;
    }
    return false;
}

void * CELFFile::GetImage()
{
    return buffer;
}

Elf32_Ehdr * CELFFile::GetElfHeader()
{
    return reinterpret_cast<Elf32_Ehdr*>(GetImage());
}

void * CELFFile::GetSegmentSectionData(int section_index,size_t * _size)
{
    if (section_index >= GetProgramCount())
       return NULL;
   Elf32_Phdr * phdr = GetProgramHeader(section_index);
   *_size = phdr->p_filesz;
   return phdr->p_offset + reinterpret_cast<char *>(GetImage());
}


void * CELFFile::GetSectionData(int section_index,size_t * _size)
{
    if (section_index >= GetSectionCount())
       return NULL;
   Elf32_Shdr * shdr = GetSectionHeader(section_index);
   *_size = shdr->sh_size;
   return shdr->sh_offset + reinterpret_cast<char *>(GetImage());
}

long  CELFFile::GetSectionVa(int section_index,size_t offset)
{
   if (section_index >= GetSectionCount())
        return NULL;
   Elf32_Shdr * shdr = GetSectionHeader(section_index);
   return shdr->sh_addr + offset;

}

void * CELFFile::GetSectionPtr(int section_index,size_t offset)
{
   if (section_index >= GetSectionCount())
       return NULL;
   Elf32_Shdr * shdr = GetSectionHeader(section_index);
   return shdr->sh_offset + reinterpret_cast<char *>(GetImage()) + offset;
}

long CELFFile::GetNewSegmentSectionBase()
{
    long max = 0;
    for (int i = 0; i < GetProgramCount(); i++)
    {
        Elf32_Phdr* section_header = GetProgramHeader(i);
        if (max < section_header->p_vaddr + section_header->p_filesz)
        {
            max = section_header->p_vaddr + section_header->p_filesz;
        }
    }
    max = 0x1000-(max %0x1000) + max;
    max = max + (sizeof(Elf32_Phdr) * (GetProgramCount() + 1)) + size;

    return max;
}

long CELFFile::GetNewSectionBase()
{
    long max = 0;
    for (int i = 0; i < GetSectionCount(); i++)
    {
        Elf32_Shdr* section_header = GetSectionHeader(i);
        if (max < section_header->sh_addr + section_header->sh_size)
        {
            max = section_header->sh_addr + section_header->sh_size;
        }
    }
    max = 0x1000-(max %0x1000) + max;
    max = max + (sizeof(Elf32_Shdr) * (GetSectionCount() + 1)) + size;

    return max;
}

Elf32_Phdr * CELFFile::AddProgramHeader()
{
    size_t old_size = size;
    ReallocImage(((GetProgramCount() + 1) * sizeof(Elf32_Phdr)) + size);
    Elf32_Phdr * new_phdr = (Elf32_Phdr*)((size_t)GetImage() + old_size);
    for (int i = 0 ; i < GetProgramCount(); i++)
    {
        Elf32_Phdr cur_phdr = *GetProgramHeader(i);

        /*if (i == GetProgramCount() - 1)
        {
           Elf32_Phdr *last_phdr = new_phdr+1;
           *last_phdr = cur_phdr;
        }
        else*/
        {
           *new_phdr = cur_phdr;
            new_phdr++;
        }
    }
    GetElfHeader()->e_phnum++;
    GetElfHeader()->e_phoff = old_size;
    return new_phdr;
}

Elf32_Phdr * CELFFile::GetProgramHeader(int index)
{
    Elf32_Ehdr * elf_header = GetElfHeader();
    if (index < GetProgramCount())
    {
      Elf32_Phdr * program_header = reinterpret_cast<Elf32_Phdr*>(
                                         (elf_header->e_phoff +
                                          reinterpret_cast<Elf32_Off>(GetImage())));
      return reinterpret_cast<Elf32_Phdr*>(
                                             reinterpret_cast<Elf32_Phdr*>(program_header) +
                                              index
                                             );
    }
    return NULL;
}



Elf32_Shdr * CELFFile::GetSectionHeader(int index)
{
    Elf32_Ehdr * elf_header = GetElfHeader();
    if (index < GetSectionCount())
    {
      Elf32_Shdr * section_header = reinterpret_cast<Elf32_Shdr*>(
                                         (elf_header->e_shoff +
                                          reinterpret_cast<Elf32_Off>(GetImage())));
      return reinterpret_cast<Elf32_Shdr*>(
                                             reinterpret_cast<Elf32_Shdr*>(section_header) + index
                                             //elf_header->e_shentsize * index
                                             //sizeof(Elf32_Shdr) * index
                                             );
    }
    return NULL;

}

size_t CELFFile::GetSectionCount()
{
    Elf32_Ehdr * elf_header = GetElfHeader();
    return elf_header->e_shnum;
}

size_t CELFFile::GetProgramCount()
{
    Elf32_Ehdr * elf_header = GetElfHeader();
    return elf_header->e_phnum;
}

void * CELFFile::VaToPtr(long va)
{
    for (int i = 0; i < GetSectionCount();i++)
    {
        Elf32_Shdr *shdr = GetSectionHeader(i);
        if (va <= shdr->sh_addr + shdr->sh_size &&
                va >= shdr->sh_addr)
        {
            return  (char *)GetImage() + shdr->sh_offset + (va - shdr->sh_addr);
        }
    }
    return NULL;
}

long CELFFile::GetSectionMaxAddress()
{
    long max = 0;
    unsigned long min = -1;
    for (int i = 0; i < GetSectionCount(); i++)
    {
        Elf32_Shdr* section_header = GetSectionHeader(i);
        if (max < section_header->sh_addr + section_header->sh_size)
        {
            max = section_header->sh_addr + section_header->sh_size;
        }
        if (min < section_header->sh_addr && section_header->sh_addr != 0)
        {
            min = section_header->sh_addr;
        }
    }
    return max;
}

long CELFFile::GetSectionMinAddress()
{
    long max = 0;
    unsigned long min = -1;
    for (int i = 0; i < GetSectionCount(); i++)
    {
        Elf32_Shdr* section_header = GetSectionHeader(i);
        if (max < section_header->sh_addr + section_header->sh_size)
        {
            max = section_header->sh_addr + section_header->sh_size;
        }
        if (min < (unsigned long)(section_header->sh_addr) && section_header->sh_addr != 0)
        {
            min = section_header->sh_addr;
        }
    }
    return min;
}

long CELFFile::GetEntry()
{
	return 0;
}

Elf32_Shdr * CELFFile::GetFirstSectionHeader()
{
   return GetSectionHeader(0);
}

char * CELFFile::GetStringTableStr(int str_offset)
{
    Elf32_Ehdr * elf_header = GetElfHeader();
    Elf32_Shdr * section_header = GetSectionHeader( elf_header->e_shstrndx );
    return reinterpret_cast<char*>(GetImage()) + section_header->sh_offset + str_offset;
}


bool CELFFile::CheckAddressValidity(long Addr)
{
   if (Addr <= GetSectionMaxAddress() && Addr >= GetSectionMinAddress())
   {
       return true;
   }
   return false;
}
void CELFFile::AddSection(char * new_section_name,size_t new_section_size,long new_section_flag)
{
    if (buffer == NULL || new_section_size == 0)
        return;
    size_t old_size = size;
    Elf32_Shdr * t_shdr_header =  GetFirstSectionHeader() + GetSectionCount();
    if (reinterpret_cast<size_t>(t_shdr_header) - reinterpret_cast<size_t>(GetImage()) == old_size)
    {
        ReallocImage(size + new_section_size + sizeof(Elf32_Shdr));
    }
    else
    {
        ReallocImage(size + new_section_size );
    }


    Elf32_Ehdr * elf_header = GetElfHeader();

    Elf32_Shdr * string_section_header = GetSectionHeader( elf_header->e_shstrndx );

    size_t str_table_last_offset = string_section_header->sh_size + string_section_header->sh_offset;
    char * new_string_begin_addr = reinterpret_cast<char*>(GetImage()) + str_table_last_offset;
    strcpy(new_string_begin_addr,new_section_name);
    string_section_header->sh_size += strlen(new_section_name);
    //Elf32_Shdr * new_shdr_header = GetSectionHeader(GetSectionCount() - 1);
    //Elf32_Shdr * new_shdr_header = GetSectionHeader(0) + GetSectionCount();
    //printf ("last section:%s\n",GetStringTableStr( new_shdr_header->sh_name));
    Elf32_Shdr * new_shdr_header = reinterpret_cast<Elf32_Shdr*>(
                                         (elf_header->e_shoff +
                                          reinterpret_cast<Elf32_Off>(GetImage())));
    new_shdr_header += GetSectionCount();

    //new_shdr_header++;
    printf("Elf32_Shdr Size:%x\n",sizeof(Elf32_Shdr));
    if (reinterpret_cast<size_t>(new_shdr_header) - reinterpret_cast<size_t>(GetImage()) == old_size)
    {
        new_shdr_header->sh_offset = old_size + sizeof(Elf32_Shdr);
    }
    else
    {
        new_shdr_header->sh_offset = old_size;
    }

    printf("offset :%x\n",reinterpret_cast<size_t>(new_shdr_header) - reinterpret_cast<size_t>(GetImage()));
    new_shdr_header->sh_name = str_table_last_offset - string_section_header->sh_offset;
    printf ("last section:%s\n",GetStringTableStr( new_shdr_header->sh_name));
    new_shdr_header->sh_addr = GetNewSectionBase();
    new_shdr_header->sh_size = new_section_size;
    printf("size :%#x\n",new_shdr_header->sh_size);
    new_shdr_header->sh_flags = new_section_flag;

    //new_shdr_header->sh_offset = old_size;
    new_shdr_header->sh_type = 1;
    new_shdr_header->sh_link = 0;
    new_shdr_header->sh_info = 0;
    new_shdr_header->sh_addralign = 16;
    new_shdr_header->sh_entsize = 0;
    ++elf_header->e_shnum;


}

void CELFFile::AddSegmentSection(char * new_section_name,size_t new_section_size,long new_section_flag)
{
    printf("new base:%x\n",GetNewSegmentSectionBase() );
    long new_section_addr = GetNewSegmentSectionBase();
    Elf32_Phdr * new_phdr_header = AddProgramHeader();


    new_phdr_header->p_align = 0x1000;//new_section_size + (0x1000 - (new_section_size % 0x1000));
    new_phdr_header->p_filesz = new_section_size;
    new_phdr_header->p_memsz = new_section_size;
    new_phdr_header->p_offset = size;
    new_phdr_header->p_flags = new_section_flag;//PF_X|PF_W|PF_R;
    new_phdr_header->p_vaddr = new_section_addr;
    new_phdr_header->p_type = PT_LOAD;
    new_phdr_header->p_paddr = new_section_addr;


    //asm("int3");
    ReallocImage(size+new_section_size);
    return ;
    if (buffer == NULL || new_section_size == 0)
        return;
    size_t old_size = size;
    Elf32_Shdr * t_shdr_header =  GetFirstSectionHeader() + GetSectionCount();
    if (reinterpret_cast<size_t>(t_shdr_header) - reinterpret_cast<size_t>(GetImage()) == old_size)
    {
        ReallocImage(size + new_section_size + sizeof(Elf32_Shdr));
    }
    else
    {
        ReallocImage(size + new_section_size );
    }


    Elf32_Ehdr * elf_header = GetElfHeader();

    Elf32_Shdr * string_section_header = GetSectionHeader( elf_header->e_shstrndx );

    size_t str_table_last_offset = string_section_header->sh_size + string_section_header->sh_offset;
    char * new_string_begin_addr = reinterpret_cast<char*>(GetImage()) + str_table_last_offset;
    strcpy(new_string_begin_addr,new_section_name);
    string_section_header->sh_size += strlen(new_section_name);
    //Elf32_Shdr * new_shdr_header = GetSectionHeader(GetSectionCount() - 1);
    //Elf32_Shdr * new_shdr_header = GetSectionHeader(0) + GetSectionCount();
    //printf ("last section:%s\n",GetStringTableStr( new_shdr_header->sh_name));
    Elf32_Shdr * new_shdr_header = reinterpret_cast<Elf32_Shdr*>(
                                         (elf_header->e_shoff +
                                          reinterpret_cast<Elf32_Off>(GetImage())));
    new_shdr_header += GetSectionCount();

    //new_shdr_header++;
    printf("Elf32_Shdr Size:%x\n",sizeof(Elf32_Shdr));
    if (reinterpret_cast<size_t>(new_shdr_header) - reinterpret_cast<size_t>(GetImage()) == old_size)
    {
        new_shdr_header->sh_offset = old_size + sizeof(Elf32_Shdr);
    }
    else
    {
        new_shdr_header->sh_offset = old_size;
    }

    printf("offset :%x\n",reinterpret_cast<size_t>(new_shdr_header) - reinterpret_cast<size_t>(GetImage()));
    new_shdr_header->sh_name = str_table_last_offset - string_section_header->sh_offset;
    printf ("last section:%s\n",GetStringTableStr( new_shdr_header->sh_name));
    new_shdr_header->sh_addr = GetNewSectionBase();
    new_shdr_header->sh_size = new_section_size;
    printf("size :%#x\n",new_shdr_header->sh_size);
    new_shdr_header->sh_flags = new_section_flag;

    //new_shdr_header->sh_offset = old_size;
    new_shdr_header->sh_type = 1;
    new_shdr_header->sh_link = 0;
    new_shdr_header->sh_info = 0;
    new_shdr_header->sh_addralign = 16;
    new_shdr_header->sh_entsize = 0;
    ++elf_header->e_shnum;


    /*
    Elf32_Phdr * new_phdr_header = GetProgramHeader(GetProgramCount() - 1);
    new_phdr_header++;
    printf("new_phdr_header offset:%#x\n",(size_t)new_phdr_header - (size_t)GetImage());
    new_phdr_header->p_align = 0x1000;//new_section_size + (0x1000 - (new_section_size % 0x1000));
    new_phdr_header->p_filesz = new_section_size;
    new_phdr_header->p_memsz = new_section_size;
    new_phdr_header->p_offset = new_shdr_header->sh_offset;
    new_phdr_header->p_flags = 5;
    new_phdr_header->p_vaddr = new_shdr_header->sh_addr;
    new_phdr_header->p_type = 1;
    new_phdr_header->p_paddr = new_phdr_header->p_vaddr;
    elf_header->e_phnum += 1;*/
}

bool CELFFile::WriteSegmentSectionData(int section_index,size_t offset,unsigned char * buffer,unsigned long* buffer_size)
{
    bool success = false;
    size_t section_size;
    char * section_buffer  = reinterpret_cast<char*>(GetSegmentSectionData(section_index,&section_size));
    if (offset + *buffer_size <= section_size && section_buffer != NULL)
    {
        memcpy(section_buffer + offset,buffer,*buffer_size);
        success = true;
    }
    return success;
}

bool CELFFile::WriteSectionData(int section_index,size_t offset,unsigned char * buffer,unsigned long* buffer_size)
{
    bool success = false;
    size_t section_size;
    char * section_buffer  = reinterpret_cast<char*>(GetSectionData(section_index,&section_size));
    if (offset + *buffer_size <= section_size && section_buffer != NULL)
    {
        memcpy(section_buffer + offset,buffer,*buffer_size);
        success = true;
    }
    return success;
}
bool CELFFile::SavePEFile(char *save_file_name)
{
    FILE * pFile;
    pFile = fopen(save_file_name,"wb");
    if (pFile)
        {
            fwrite(buffer,size,1,pFile);
            fclose(pFile);
            return true;
        }
    return false;
}
