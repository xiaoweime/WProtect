#ifndef  LUAINTERFACE_H
#define  LUAINTERFACE_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <Assembl.h>


#include <WProtectConfig.h>


#include <WPStruct.h>
//#include <CodeList.h>

#ifndef LUA_H
#define LUA_H
extern "C" {
#include "Lua/lua.h"
#include "Lua/lualib.h"
#include "Lua/lauxlib.h"
}
#endif

class LuaInterface{
public:
      LuaInterface();
    ~LuaInterface();
public:
     Assembl a;   
	 lua_State *L ;
	 pCodeInformation lua_equivalent_replacement(pCodeInformation info,unsigned long imagebase);
	 bool call_lua_fuc(const char * fucname);
	 unsigned long get_jcc_addr(ud_t ud_obj);
	 void set_jcc(pCodeInformation info,ud_t ud_obj,const char *opname);
};
#endif
