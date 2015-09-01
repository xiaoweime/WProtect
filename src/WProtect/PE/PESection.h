#ifndef WPROTECTCONFIG_H
#define WPROTECTCONFIG_H
#include <WProtectConfig.h>
#endif

#ifndef PEFILE_H
#define PEFILE_H
#include "PEFile.h"
#endif

#ifndef WINDOWS

#ifndef DATATYPE_H
#define DATATYPE_H
#include <datatype.h>
#endif

#else

#ifndef WINDOWS_H
#define WINDOWS_H
#include <Windows.h>
#endif

#endif

class CPESection : public CPEFile
{
 public:
	CPESection();
 public:
	void operator=(CPEFile &PeFile);
	int RvaToSectionIndex(DWORD dwRva);
	int OffsetToSectionIndex(DWORD dwOffset);
	DWORD GetVRk(int nSectionIndex);
    DWORD RvaToOffset(DWORD dwRva);
	DWORD OffsetToRva(DWORD dwOffset);
	DWORD RvaToVa(DWORD dwRva);
	BOOL AddSection(char *pSectionName, DWORD &dwSectionSize,DWORD dwSectionStact);
	BYTE* GetSectionData(int nIndex, DWORD *rdwSize);
	BOOL WriteSectionData(int nIndex, DWORD dwOffset, BYTE *lpBuffer, DWORD *dwSize);
	DWORD VaToOffset(DWORD dwVa);
    DWORD GetSectionVa(int nIndex, DWORD dwOffset);

    DWORD GetSectionPtr(int nIndex, DWORD dwOffset);

	DWORD GetNewSectionBase();
    DWORD GetSectionMaxAddress();
    DWORD GetSectionMinAddress();
    BOOL CheckAddressValidity(DWORD Addr);


};
