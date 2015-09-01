#ifndef MYSTRING_H
#define MYSTRING_H
#include <WProtectConfig.h>
#ifndef WINDOWS
#include <datatype.h>
#endif
#include <ctype.h>
#include <string.h>

#ifndef WINDOWS
void * memccpy( void *dst, const void *src, int c, size_t n );
int  stricmp( LPCSTR str1, LPCSTR str2 );
INT  memicmp( LPCSTR s1, LPCSTR s2, DWORD len );
int  strnicmp( LPCSTR str1, LPCSTR str2, size_t n );
LPSTR  strupr( LPSTR str );
LPSTR  strlwr( LPSTR str );
#endif

#endif
