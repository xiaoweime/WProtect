#ifndef WPROTECTCONFIG_H
#define WPROTECTCONFIG_H
#include <WProtectConfig.h>
#endif

#include <stdio.h>
#include "PEImport.h"
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


CPEImport::CPEImport(void)
{
}


CPEImport::~CPEImport(void)
{
}


void CPEImport::operator =(CPEFile& lPeFile)
{
	SetInfo(lPeFile.GetInfo());
}

//µÃµœÕûžöÊ×žöµŒÈë±í
PIMAGE_IMPORT_DESCRIPTOR CPEImport::GetFirstImportDesc()
{
	PIMAGE_IMPORT_DESCRIPTOR pImportDesc;
	pImportDesc=(PIMAGE_IMPORT_DESCRIPTOR)GetDirectoryEntryToData(IMAGE_DIRECTORY_ENTRY_IMPORT);
	if(!pImportDesc)
		return NULL;	 
	return  pImportDesc;
}
//µÃµœ¹²ÓÐ¶àÉÙžödll
int CPEImport::GetImportDesCount()
{
	int i=0;
	PIMAGE_IMPORT_DESCRIPTOR pTempImport=GetFirstImportDesc();
	while (pTempImport->FirstThunk)
	{
		++i;
		++pTempImport;
	}
	return i;
}

// µÃµœÄ³žödllµŒÈë±í
PIMAGE_IMPORT_DESCRIPTOR CPEImport::GetImportDesc(int index)
{
	int i=GetImportDesCount();
	if (index>=i)
	{
		return NULL;
	}
	PIMAGE_IMPORT_DESCRIPTOR pTempImport=GetFirstImportDesc();
	return &pTempImport[index];
}

// Ç¿ÖÆµÃµœÄ³žödllµŒÈë±í
PIMAGE_IMPORT_DESCRIPTOR CPEImport::ForceGetImportDesc(int index)
{
	PIMAGE_IMPORT_DESCRIPTOR pTempImport=GetFirstImportDesc();
	return &pTempImport[index];
}

//µÃµœÄ³žöAPI º¯ÊýµÄÃû×Ö
PIMAGE_IMPORT_BY_NAME CPEImport::GetImportFucByName(DWORD RavThunk)
{
	PIMAGE_NT_HEADERS32     pNtH=NULL;
	PIMAGE_IMPORT_BY_NAME pApiName=NULL;

	pApiName=(PIMAGE_IMPORT_BY_NAME)RvaToPtr(RavThunk);

	return pApiName;
}

DWORD CPEImport::GetImportThunk(PIMAGE_IMPORT_DESCRIPTOR pImportDesc)
{
	return pImportDesc->OriginalFirstThunk?pImportDesc->OriginalFirstThunk:pImportDesc->FirstThunk;
}


BOOL CPEImport::ReLocalImport(DWORD dwRVA)
{
	int iCount=GetImportDesCount();
	CPEImport  lPeSection;
	lPeSection.SetInfo(GetInfo());

	for (int i=0;i<iCount;i++)
	{
		PIMAGE_IMPORT_DESCRIPTOR  pImport=GetImportDesc(i);
		DWORD dwOrThunk=pImport->OriginalFirstThunk;
		DWORD dwIatThunk=pImport->FirstThunk;

		pImport->OriginalFirstThunk+=(dwRVA-0x2000);
		pImport->Name+=(dwRVA-0x2000);
		pImport->FirstThunk+=(dwRVA-0x2000);

		while(*(DWORD*)RvaToPtr(dwOrThunk)!=0)
		{
			*(DWORD*)RvaToPtr(dwOrThunk)+=(dwRVA-0x2000);
			*(DWORD*)RvaToPtr(dwIatThunk)+=(dwRVA-0x2000);
			dwOrThunk+=sizeof(DWORD);
			dwIatThunk+=sizeof(DWORD);
		}
	}
	return TRUE;
}
