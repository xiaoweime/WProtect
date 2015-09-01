#ifndef WPROTECTCONFIG_H
#define WPROTECTCONFIG_H
#include <WProtectConfig.h>
#endif

#include <stdio.h>

#ifndef PEEXPORT_H
#define PEEXPORT_H
#include "PEExport.h"
#endif

#ifndef WINDOWS
#ifndef PESTRUCT_H
#define PESTRUCT_H
#include <PEStruct.h>
//#pragma message("PEExport")
#endif
#else
#ifndef WINDOWS_H
#define WINDOWS_H
#include <Windows.h>
#endif
#endif


CPEExport::CPEExport(void)
{
}


CPEExport::~CPEExport(void)
{
}

void CPEExport::operator =(CPEFile& PeFile)
{
	SetInfo(PeFile.GetInfo());
}

PIMAGE_EXPORT_DIRECTORY CPEExport::GetExportTab()
{
	PIMAGE_EXPORT_DIRECTORY pExportDesc;
	pExportDesc=(PIMAGE_EXPORT_DIRECTORY)GetDirectoryEntryToData(IMAGE_DIRECTORY_ENTRY_EXPORT);
	if (pExportDesc==NULL)
	{
		return NULL;
	}
	return pExportDesc;
}

int CPEExport::GetFuncCount()
{
	PIMAGE_EXPORT_DIRECTORY pExportDesc=GetExportTab();
	if (pExportDesc)
	{
		return pExportDesc->NumberOfFunctions;
	}
	return -1;
}

int CPEExport::GetNameCount()
{
	PIMAGE_EXPORT_DIRECTORY pExportDesc=GetExportTab();
	if (pExportDesc)
	{
		return pExportDesc->NumberOfNames;
	}
	return -1;
}

DWORD CPEExport::GetFirstFunc()
{
	PIMAGE_EXPORT_DIRECTORY pExportDesc=GetExportTab();
	if (pExportDesc)
	{
		return pExportDesc->AddressOfFunctions;
	}
	return 0;
}

DWORD CPEExport::GetFunc(int nIndex)
{
	if (nIndex<GetFuncCount())
	{
		DWORD dwFirstFunc=GetFirstFunc();
		return dwFirstFunc+nIndex*4;
	}
	return 0;
}

DWORD CPEExport::GetFuncValue(int nIndex)
{
	DWORD dwFuncRva=GetFunc(nIndex);
	if (dwFuncRva)
	{
		return *(DWORD*)RvaToPtr(dwFuncRva);
	}
	return NULL;
}

DWORD CPEExport::GetFirstName()
{
	PIMAGE_EXPORT_DIRECTORY pExportDesc=GetExportTab();
	if (pExportDesc)
	{
		return pExportDesc->AddressOfNames;
	}
	return 0;
}

DWORD CPEExport::GetName(int nIndex)
{
	if (nIndex<GetNameCount())
	{
		DWORD dwFirstName=GetFirstName();
		return dwFirstName+nIndex*4;
	}
	return 0;
} 

char* CPEExport::GetNameValue(int nIndex)
{
	DWORD dwNameRva=GetName(nIndex);
	if (dwNameRva)
	{
		DWORD dwNameValueRva=*(DWORD*)RvaToPtr(dwNameRva);
		return (char*)RvaToPtr(dwNameValueRva);
	}
	return NULL;
}

DWORD CPEExport::GetFirstNameOrd()
{
	PIMAGE_EXPORT_DIRECTORY pExportDesc=GetExportTab();
	if (pExportDesc)
	{
		return pExportDesc->AddressOfNameOrdinals;
	}
	return 0;
}

DWORD CPEExport::GetNameOrd(int nIndex)
{
	if (nIndex<GetNameCount())
	{
		DWORD dwFirstNameOrd=GetFirstNameOrd();
		return dwFirstNameOrd+nIndex*2;
	}
	return 0;
}

WORD CPEExport::GetNameOrdValue(int nIndex)
{
	DWORD dwNameOrdRva=GetNameOrd(nIndex);
	if (dwNameOrdRva)
	{
		return *(WORD*)RvaToPtr(dwNameOrdRva);
	}
	return NULL;
}
