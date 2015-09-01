#ifndef CPERELOC
#define CPERELOC




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

class CPEReloc : public CPEFile
{
    public:
        CPEReloc() ;
        ~CPEReloc() ;
    public:
        void operator=(CPEFile &PeFile);
        DWORD GetBaseReloc();
        void DeleteReloc();
};

#endif /* end of include guard: CPERELOC */ 
