#include "AddrTable.h"
#include <stdio.h>

AddressTable::AddressTable():size(0),bufsize(0)
{
	table = NULL;
}

AddressTable::~AddressTable()
{
	if (table)
	{
		for (int i = 0; i < size ;i++)
		{
			delete [] table[i];
		}
		delete [] table;
	}
}

#define OLDADDR 0
#define NEWADDR 1
void AddressTable::add_address(unsigned long oldaddr,unsigned long newaddr)
{
	if (table == NULL)
	{
		bufsize = 0xfff;
		table = new unsigned long * [0xfff];
		for (int i = 0; i < 0xfff; i++)
		{
			table[i] = new unsigned long [2];  //[0]Ϊ�ϵ�ַ
		}
	}
	if (bufsize <= size +1)
	{
		unsigned long **newtable = new unsigned long *[bufsize + 0xfff];
		for (int i = 0;i < bufsize+0xfff; i++)
		{
			newtable[i] = new unsigned long [2];
			newtable[i][OLDADDR] = 0;
			newtable[i][NEWADDR] = 0;
		}
		for (int i = 0;i < bufsize; i++)
		{
			newtable [i][OLDADDR] = table[i][OLDADDR];
			newtable [i][NEWADDR] = table[i][NEWADDR];
			delete [] table[i];
		}
		delete [] table;
		table = newtable;
		bufsize += 0xfff;
	}
	table[size][OLDADDR] = oldaddr;
	table[size][NEWADDR] = newaddr;
	size++;
}
// 401000  405000  406000
unsigned long AddressTable::get_new_addr(unsigned long oldaddr)
{
	unsigned long addr = -1;
	bool next = true;
	while (next)
	{
		next = false;
		for (int i = 0; i < size; i++)
		{
			if (table[i][OLDADDR] == oldaddr)
			{
			      addr = table[i][NEWADDR];
				  oldaddr = addr;
				  next = true;
			}
		}
	}
	return addr;
}

unsigned long AddressTable::get_old_addr(unsigned long newaddr)
{
	unsigned long addr = -1;
	bool next = true;
	while (next)
	{
		next = false;
		for (int i = 0; i < size; i++)
		{
			if (table[i][NEWADDR] == newaddr)
			{
				addr = table[i][OLDADDR];
				newaddr = addr;
				next = true;
			}
		}
	}
	return addr;
}
