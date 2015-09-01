static int lua_Assemble(lua_State *L);
bool call_lua_fuc(char * fucname);
pCodeInformation lua_equivalent_replacement(pCodeInformation info,unsigned long imagebase);
void reloc_jcc_addr();
unsigned long get_old_addr(int oldaddr,int table_max_size = 0);

void clean_addr_table();
void set_buf_addr(unsigned char * buf);