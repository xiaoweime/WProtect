#ifndef WPROTECTCONFIG_H
#define WPROTECTCONFIG_H
#include <WProtectConfig.h>
#endif

#ifndef PEFILE_H
#define PEFILE_H
#include <PEFile.h>
#endif 

#ifndef WINDOWS

#ifndef PESTRUCT_H
#define PESTRUCT_H
#include <PEStruct.h>
#endif

#else

#ifndef WINDOWS_H
#define WINDOWS_H
#include <windows.h>
#endif

#endif


class CPEExport :
	public CPEFile
{
public:
	CPEExport(void);
	~CPEExport(void);
public:
	void operator =(CPEFile& PeFile);
	PIMAGE_EXPORT_DIRECTORY GetExportTab();
	int GetFuncCount();
	int GetNameCount();
	DWORD GetFirstFunc();
	DWORD GetFunc(int nIndex);
	DWORD GetFuncValue(int nIndex);
	DWORD GetFirstName();
	DWORD GetName(int nIndex);
	char* GetNameValue(int nIndex);
	DWORD GetFirstNameOrd();
	DWORD GetNameOrd(int nIndex);
	WORD GetNameOrdValue(int nIndex);
};

