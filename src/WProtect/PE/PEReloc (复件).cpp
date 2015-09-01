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
// 重定向PE用到的地址
void CMemLoadDll::DoRelocation( void *NewBase)
{
    /* 重定位表的结构：
    // DWORD sectionAddress, DWORD size (包括本节需要重定位的数据)
    // 例如 1000节需要修正5个重定位数据的话，重定位表的数据是
    // 00 10 00 00   14 00 00 00      xxxx xxxx xxxx xxxx xxxx 0000
    // -----------   -----------      ----
    // 给出节的偏移  总尺寸=8+6*2     需要修正的地址           用于对齐4字节
    // 重定位表是若干个相连，如果address 和 size都是0 表示结束
    // 需要修正的地址是12位的，高4位是形态字，intel cpu下是3
    */
    //假设NewBase是0x600000,而文件中设置的缺省ImageBase是0x400000,则修正偏移量就是0x200000
    DWORD Delta = (DWORD)NewBase - pNTHeader->OptionalHeader.ImageBase;

    //注意重定位表的位置可能和硬盘文件中的偏移地址不同，应该使用加载后的地址
    PIMAGE_BASE_RELOCATION pLoc = (PIMAGE_BASE_RELOCATION)((unsigned long)NewBase 
            + pNTHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].VirtualAddress);
    while((pLoc->VirtualAddress + pLoc->SizeOfBlock) != 0) //开始扫描重定位表
    {
        WORD *pLocData = (WORD *)((int)pLoc + sizeof(IMAGE_BASE_RELOCATION));
        //计算本节需要修正的重定位项（地址）的数目
        int NumberOfReloc = (pLoc->SizeOfBlock - sizeof(IMAGE_BASE_RELOCATION))/sizeof(WORD);
        for( int i=0 ; i < NumberOfReloc; i++)
        {
            if( (DWORD)(pLocData[i] & 0xF000) == 0x00003000) //这是一个需要修正的地址
            {
                // 举例： 
                // pLoc->VirtualAddress = 0x1000; 
                // pLocData[i] = 0x313E; 表示本节偏移地址0x13E处需要修正
                // 因此 pAddress = 基地址 + 0x113E
                // 里面的内容是 A1 ( 0c d4 02 10)  汇编代码是： mov eax , [1002d40c]
                // 需要修正1002d40c这个地址
                DWORD * pAddress = (DWORD *)((unsigned long)NewBase + pLoc->VirtualAddress + (pLocData[i] & 0x0FFF));
                *pAddress += Delta;
            }
        }
        //转移到下一个节进行处理
        pLoc = (PIMAGE_BASE_RELOCATION)((DWORD)pLoc + pLoc->SizeOfBlock);
    }
}

//填充引入地址表
BOOL CMemLoadDll::FillRavAddress(void *pImageBase)
{
    // 引入表实际上是一个 IMAGE_IMPORT_DESCRIPTOR 结构数组，全部是0表示结束
    // 数组定义如下：
    // 
    // DWORD   OriginalFirstThunk;         // 0表示结束，否则指向未绑定的IAT结构数组
    // DWORD   TimeDateStamp; 
    // DWORD   ForwarderChain;             // -1 if no forwarders
    // DWORD   Name;                       // 给出dll的名字
    // DWORD   FirstThunk;                 // 指向IAT结构数组的地址(绑定后，这些IAT里面就是实际的函数地址)
    unsigned long Offset = pNTHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress ;
    if(Offset == 0) return TRUE; //No Import Table
    PIMAGE_IMPORT_DESCRIPTOR pID = (PIMAGE_IMPORT_DESCRIPTOR)((unsigned long) pImageBase + Offset);
    while(pID->Characteristics != 0 )
    {
        PIMAGE_THUNK_DATA pRealIAT = (PIMAGE_THUNK_DATA)((unsigned long)pImageBase + pID->FirstThunk);
        PIMAGE_THUNK_DATA pOriginalIAT = (PIMAGE_THUNK_DATA)((unsigned long)pImageBase + pID->OriginalFirstThunk);
        //获取dll的名字
        char buf[256]; //dll name;
        BYTE* pName = (BYTE*)((unsigned long)pImageBase + pID->Name);
        for(int i=0;i<256;i++)
        {
            if(pName[i] == 0)break;
            buf[i] = pName[i];
        }
        if(i>=256) return FALSE;  // bad dll name
        else buf[i] = 0;
        HMODULE hDll = GetModuleHandle(buf);
        if(hDll == NULL)return FALSE; //NOT FOUND DLL
        //获取DLL中每个导出函数的地址，填入IAT
        //每个IAT结构是 ：
        // union { PBYTE  ForwarderString;
        //   PDWORD Function;
        //   DWORD Ordinal;
        //   PIMAGE_IMPORT_BY_NAME  AddressOfData;
        // } u1;
        // 长度是一个DWORD ，正好容纳一个地址。
        for(i=0; ;i++)
        {
            if(pOriginalIAT[i].u1.Function == 0)break;
            FARPROC lpFunction = NULL;
            if(pOriginalIAT[i].u1.Ordinal & IMAGE_ORDINAL_FLAG) //这里的值给出的是导出序号
            {
                lpFunction = GetProcAddress(hDll, (LPCSTR)(pOriginalIAT[i].u1.Ordinal & 0x0000FFFF));
            }
            else //按照名字导入
            {
                //获取此IAT项所描述的函数名称
                PIMAGE_IMPORT_BY_NAME pByName = (PIMAGE_IMPORT_BY_NAME)
                    ((DWORD)pImageBase + (DWORD)(pOriginalIAT[i].u1.AddressOfData));
                //    if(pByName->Hint !=0)
                //     lpFunction = GetProcAddress(hDll, (LPCSTR)pByName->Hint);
                //    else
                lpFunction = GetProcAddress(hDll, (char *)pByName->Name);
            }
            if(lpFunction != NULL)   //找到了！
            {
                pRealIAT[i].u1.Function = (PDWORD) lpFunction;
            }
            else return FALSE;
        }

        //move to next 
        pID = (PIMAGE_IMPORT_DESCRIPTOR)( (DWORD)pID + sizeof(IMAGE_IMPORT_DESCRIPTOR));
    }
    return TRUE;
}
