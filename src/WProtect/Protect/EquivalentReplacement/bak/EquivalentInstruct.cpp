#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>


#include "EquivalentInstruct.h"





char * g_buf;
unsigned long g_size;


EquivalentInstruct::EquivalentInstruct()
{
	m_b_load_lua = false;
	L = luaL_newstate();
	luaL_openlibs(L);

	if (luaL_loadfile(L,"H:\\CMake\\WProtect\\build\\wprotect_config.lua"))
	{
		fprintf(stdout,"not file wprotect_config.lua")
	}
	else if (lua_pcall(L,0,0,0))
	{
		fprintf(stdout,"lua_pcall error");
	}
	else
		m_b_load_lua = true;

	if (m_b_load_lua)
	{
		lua_getglobal(L,"mov");
		lua_getglobal(L,"push");
		lua_getglobal(L,"pushad");
		lua_getglobal(L,"pushfd");
		lua_getglobal(L,"add");
		lua_getglobal(L,"add");
		lua_getglobal(L,"add");
		lua_getglobal(L,"add");
		lua_getglobal(L,"add");
		lua_getglobal(L,"add");
		lua_getglobal(L,"add");
		lua_getglobal(L,"add");
		lua_getglobal(L,"add");
		lua_getglobal(L,"add");
		lua_getglobal(L,"add");
		lua_getglobal(L,"add");
		lua_getglobal(L,"add");
		lua_getglobal(L,"add");
		lua_getglobal(L,"add");
		lua_getglobal(L,"add");
		lua_getglobal(L,"add");
		lua_getglobal(L,"add");
		lua_getglobal(L,"add");
		lua_getglobal(L,"add");
		lua_getglobal(L,"add");
		lua_getglobal(L,"add");
		lua_getglobal(L,"add");
		lua_getglobal(L,"add");
		lua_getglobal(L,"add");
	}
}


pCodeInformation EquivalentInstruct::lua_code_equivalent_replacement(pCodeInformation info,unsigned long imagebase)
{
	ud_t ud_obj;
	ud_init(&ud_obj);
	ud_set_mode(&ud_obj, 32);
	ud_set_pc(&ud_obj,info->base);
	ud_set_input_buffer(&ud_obj, info->buf, info->size);
	ud_set_syntax(&ud_obj, UD_SYN_INTEL);

	char buff[0xFFF];
	int error;

	while (ud_disassemble(&ud_obj) != 0)
	{
		switch (ud_obj.mnemonic)
		{
		case UD_NONE:
			break;
		case UD_Imov:
			{
				dword_ptr()
			}
			break;
		}
	}
}

pCodeInformation EquivalentInstruct::code_equivalent_replacement(pCodeInformation info,unsigned long imagebase)
{
	ud_t ud_obj;
	ud_init(&ud_obj);
	ud_set_mode(&ud_obj, 32);
	ud_set_pc(&ud_obj,info->base);
	ud_set_input_buffer(&ud_obj, info->buf, info->size);
	ud_set_syntax(&ud_obj, UD_SYN_INTEL);

	char buff[0xFFF];
	int error;

	while (ud_disassemble(&ud_obj) != 0)
	{
		switch (ud_obj.mnemonic)
		{
		case UD_NONE:
				break;
		case UD_Imov:
			{
			//	dword_ptr()
			}
			break;
		}
	}
}