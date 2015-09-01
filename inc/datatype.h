#include <WProtectConfig.h>
#ifndef WINDOWS
#ifdef X86

#define far
#define near
typedef char *LPSTR;
typedef char *LPCSTR;
typedef void VOID; 
typedef char CHAR;
typedef short SHORT;
typedef long LONG;
typedef unsigned long ULONG;
typedef unsigned long ULONG_PTR;
typedef long            LONG_PTR;
typedef unsigned short USHORT;
typedef unsigned long       DWORD;
typedef int                 BOOL;
typedef unsigned char       BYTE;
typedef unsigned short      WORD;
typedef float               FLOAT;
typedef FLOAT               *PFLOAT;
typedef BOOL near           *PBOOL;
typedef BOOL far            *LPBOOL;
typedef BYTE near           *PBYTE;
typedef BYTE far            *LPBYTE;
typedef int near            *PINT;
typedef int far             *LPINT;
typedef WORD near           *PWORD;
typedef WORD far            *LPWORD;
typedef long far            *LPLONG;
typedef DWORD near          *PDWORD;
typedef DWORD far           *LPDWORD;
typedef void far            *LPVOID;
typedef const void far      *LPCVOID;

typedef int                 INT;
typedef unsigned int        UINT;
typedef unsigned int        *PUINT;
typedef void                 *PVOID;
typedef void                 *LPVOID;
#define FALSE  0
#define TRUE   1
#ifndef null
#define null 0
#endif

#ifndef NULL
#define NULL 0
#endif

typedef  long LONG_PTR, *PLONG_PTR;
#define FIELD_OFFSET(type, field)    ((LONG)(LONG_PTR)&(((type *)0)->field))
typedef unsigned long ULONG_PTR;
#else //64位系统


#define far
#define near
typedef char *LPSTR;
typedef char *LPCSTR;
typedef void VOID; 
typedef char CHAR;
typedef short SHORT;
typedef long LONG;
typedef unsigned long ULONG;
typedef unsigned long ULONG_PTR;
typedef long            LONG_PTR;
typedef unsigned short      USHORT;
typedef unsigned long      DWORD;
typedef int                 BOOL;
typedef unsigned char       BYTE;
typedef unsigned short      WORD;
typedef float               FLOAT;
typedef FLOAT               *PFLOAT;
typedef BOOL near           *PBOOL;
typedef BOOL far            *LPBOOL;
typedef BYTE near           *PBYTE;
typedef BYTE far            *LPBYTE;
typedef int near            *PINT;
typedef int far             *LPINT;
typedef WORD near           *PWORD;
typedef WORD far            *LPWORD;
typedef long far            *LPLONG;
typedef DWORD near          *PDWORD;
typedef DWORD far           *LPDWORD;
typedef void far            *LPVOID;
typedef const void far      *LPCVOID;

typedef int                 INT;
typedef unsigned int        UINT;
typedef unsigned int        *PUINT;
typedef void                 *PVOID;
typedef void                 *LPVOID;
#define FALSE  0
#define TRUE   1
#ifndef null
#define null 0
#endif

#ifndef NULL
#define NULL 0
#endif

typedef  long LONG_PTR, *PLONG_PTR;
#define FIELD_OFFSET(type, field)    ((LONG)(LONG_PTR)&(((type *)0)->field))
typedef unsigned long ULONG_PTR;

#endif
#else
#include <windows.h>
#endif
