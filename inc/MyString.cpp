#include "MyString.h"
#include <WProtectConfig.h>

#ifndef WINDOWS

void * memccpy( void *dst, const void *src, int c, size_t n )
{
    return memccpy( dst, src, c, n );
}


int  stricmp( LPCSTR str1, LPCSTR str2 )
{
    return strcasecmp( str1, str2 );
}

INT  memicmp( LPCSTR s1, LPCSTR s2, DWORD len )
{
    int ret = 0;
    while (len--)
    {
        if ((ret = tolower(*s1) - tolower(*s2))) break;
        s1++;
        s2++;
    }
    return ret;
}

int  strnicmp( LPCSTR str1, LPCSTR str2, size_t n )
{
    return strncasecmp( str1, str2, n );
}


LPSTR  strupr( LPSTR str )
{
    LPSTR ret = str;
    for ( ; *str; str++) *str = toupper(*str);
    return ret;
}


LPSTR  strlwr( LPSTR str )
{
    LPSTR ret = str;
    for ( ; *str; str++) *str = tolower(*str);
    return ret;
}

#endif
