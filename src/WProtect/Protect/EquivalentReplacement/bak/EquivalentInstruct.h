#include <WPStruct.h>

#ifndef ASMJIT_H
#define ASMJIT_H
#include <AsmJit.h>
#endif

class EquivalentInstruct
{
public:
	EquivalentInstruct();
	~EquivalentInstruct();
public:
	pCodeInformation code_equivalent_replacement(pCodeInformation info,unsigned long imagebase);
	pCodeInformation lua_code_equivalent_replacement(pCodeInformation info,unsigned long imagebase);
	lua_State * L;
	bool m_b_load_lua;
};