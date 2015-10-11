Include_directories (${CMAKE_CURRENT_SOURCE_DIR})
Set (LUA_SOURCES
lapi.c
lauxlib.c
lbaselib.c
lbitlib.c
lcode.c
lcode.h
lcorolib.c
lctype.c
lctype.h
ldblib.c
ldebug.c
ldo.c
ldump.c
lfunc.c
lfunc.h
lgc.c
lgc.h
linit.c
liolib.c
llex.c
lmathlib.c
lmem.c
loadlib.c
lobject.c
lobject.h
lopcodes.c
lopcodes.h
loslib.c
lparser.c
lstate.c
lstring.c
lstrlib.c
ltable.c
ltablib.c
ltm.c
lua.c
luac.c
luaconf.h
lundump.c
lutf8lib.c
lvm.c
lzio.c

)

#add_library ("Lua${Lua_Version}" STATIC ${LUA_SOURCES})

if (LIBRARY_TYPE_SHARED)
add_library ("Lua${Lua_Version}" SHARED ${LUA_SOURCES})
endif ()

if (LIBRARY_TYPE_STATIC) 
add_library ("Lua${Lua_Version}_Static" STATIC ${LUA_SOURCES})
#set_target_properties ("Lua${Lua_Version}_Static" PROPERTIES OUTPUT_NAME "Lua${Lua_Version}")
endif ()

