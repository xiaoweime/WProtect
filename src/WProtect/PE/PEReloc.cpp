#ifndef WPROTECTCONFIG_H
#define WPROTECTCONFIG_H
#include <WProtectConfig.h>
#endif

#include <stdio.h>
#include <string.h>

#ifndef WINDOWS

#ifndef PESTRUCT_H
#define PESTRUCT_H
#include <PEStruct.h>
#endif

#else

#ifndef WINDOWS_H
#define WINDOWS_H
#include <Windows.h>
#endif

#endif

#define  ZALIGN(x,a)(((x-1)/a+1)*a)


#include "PEReloc.h"



CPEReloc::CPEReloc()
{

}

CPEReloc::~CPEReloc()
{

}

void CPEReloc::operator=(CPEFile &PeFile)
{
   SetInfo(PeFile.GetInfo());
}

#include <stdio.h>
DWORD CPEReloc::GetBaseReloc() 
{
   PIMAGE_OPTIONAL_HEADER32 NtOptionHead = GetNtOptionalHeader();
   IMAGE_DATA_DIRECTORY Roc = NtOptionHead->DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC];
   return Roc.VirtualAddress;
   PIMAGE_BASE_RELOCATION pLoc= (PIMAGE_BASE_RELOCATION)VaToPtr(NtOptionHead->ImageBase + Roc.VirtualAddress);
   printf ("datadirectory %x \n",NtOptionHead->ImageBase + Roc.VirtualAddress);
   while (pLoc->VirtualAddress + pLoc->SizeOfBlock != 0)
   {
       WORD *pLocData = (WORD *)((int)pLoc + sizeof(IMAGE_BASE_RELOCATION));
       int NumberOfReloc = (pLoc->SizeOfBlock - sizeof(IMAGE_BASE_RELOCATION))/sizeof(WORD);
       printf ("VirtualAddress:%x\n ",pLoc->VirtualAddress);

       for (int i = 0;i<NumberOfReloc;i++)
       {
           printf("LocData:%x\n",pLocData[i]);
       }
        pLoc = (PIMAGE_BASE_RELOCATION)((DWORD)pLoc + pLoc->SizeOfBlock);
   }

   // asm("int3");
}

void CPEReloc::DeleteReloc()
{
    PIMAGE_OPTIONAL_HEADER32 NtOptionHead = GetNtOptionalHeader();

    IMAGE_DATA_DIRECTORY DataReloc = NtOptionHead->DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC];
    if (DataReloc.VirtualAddress == 0)  return;
    PIMAGE_BASE_RELOCATION pLoc= (PIMAGE_BASE_RELOCATION)VaToPtr(NtOptionHead->ImageBase + DataReloc.VirtualAddress);
    pLoc->VirtualAddress = 0;
    pLoc->SizeOfBlock = 0;
    //DataReloc.VirtualAddress = 0;
    //DataReloc.Size = 0;
}

