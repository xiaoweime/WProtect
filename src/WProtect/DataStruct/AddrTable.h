#ifndef  ADDRTABLE_H
#define  ADDRTABLE_H
class AddressTable 
{
public:
	AddressTable();
	AddressTable(const AddressTable & copy);
	~AddressTable();
public:
	void add_address(unsigned long oldaddr,unsigned long newaddr);
	unsigned long get_new_addr(unsigned long oldaddr);
	unsigned long get_old_addr(unsigned long newaddr);
	unsigned long ** table;
	int size;
	int bufsize;

};
#endif
