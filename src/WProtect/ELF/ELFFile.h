/*********************************************************
 * 开发人员：XiaoWei
 * 创建时间：Thu Jan 16 10:35:45 2014
 * 描述说明：
 *
 * 更改历史：
 *
 * *******************************************************/

#include <iostream>
#include "elf.h"

class CELFFile
{
public:
    CELFFile();
    ~CELFFile();
    void FreeImage();
    void *ReallocImage(size_t _size);
    bool LoadELFFile(char * elf_file_name);
    bool IsELFFile();
    Elf32_Ehdr * GetElfHeader();
    Elf32_Phdr * GetProgramHeader(int index);
    Elf32_Shdr * GetSectionHeader(int index);
    size_t GetSectionCount();
    size_t GetProgramCount();
    void *GetImage();
    void * VaToPtr(long va);
    long GetEntry();
    char * GetStringTableStr(int str_offset);
    void * GetSectionData(int section_index,size_t * _size);
    long  GetSectionVa(int section_index,size_t offset);
    void * GetSectionPtr(int section_index,size_t offset);
    long GetNewSectionBase();
    long GetNewSegmentSectionBase();
    long GetSectionMaxAddress();
    long GetSectionMinAddress();
    bool CheckAddressValidity(long Addr);
    Elf32_Shdr * GetFirstSectionHeader();

    void AddSegmentSection(char * new_section_name,size_t new_section_size,long new_section_flag);
    void AddSection(char * new_section_name,size_t new_section_size,long new_section_flag);
    bool WriteSectionData(int section_index,size_t offset,unsigned char * buffer,unsigned long* buffer_size);
    bool WriteSegmentSectionData(int section_index,size_t offset,unsigned char * buffer,unsigned long* buffer_size);

    bool SavePEFile(char *save_file_name);
    void * GetSegmentSectionData(int section_index,size_t * _size);

    Elf32_Phdr * AddProgramHeader();



private:
    void * buffer;
    size_t size;
};
