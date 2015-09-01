#ifndef WPROTECTCONFIG_H
#define WPROTECTCONFIG_H
#include <WProtectConfig.h>
#endif

#ifndef PEFILE_H
#define PEFILE_H
#include "PEFile.h"
#endif

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
class CPEImport :
	public CPEFile
{
public:
	CPEImport(void);
	~CPEImport(void);
public:
	void operator =(CPEFile& lPeFile);
	PIMAGE_IMPORT_DESCRIPTOR GetFirstImportDesc();
	int GetImportDesCount();
	PIMAGE_IMPORT_DESCRIPTOR GetImportDesc(int index);
	PIMAGE_IMPORT_BY_NAME GetImportFucByName(DWORD RavThunk);
	DWORD GetImportThunk(PIMAGE_IMPORT_DESCRIPTOR pImportDesc);
	BOOL ReLocalImport(DWORD dwRVA);
	PIMAGE_IMPORT_DESCRIPTOR ForceGetImportDesc(int index);
};
