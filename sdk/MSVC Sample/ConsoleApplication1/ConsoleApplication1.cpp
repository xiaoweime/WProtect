// ConsoleApplication1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "WProtect.h"

int _tmain(int argc, _TCHAR* argv[])
{
	WProtectBegin();
	printf("Shit\r\n");
	WProtectEnd();
	getchar();
	return 0;
}

