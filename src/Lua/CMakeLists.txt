Include_directories (${CMAKE_CURRENT_SOURCE_DIR})
Set (LUA_SOURCES
lapi.c 
lcode.c 
lctype.c 
ldebug.c 
ldo.c 
ldump.c 
lfunc.c 
lgc.c 
llex.c 
lmem.c 
lobject.c 
lopcodes.c 
lparser.c 
lstate.c 
lstring.c 
ltable.c 
ltm.c 
lundump.c 
lvm.c 
lzio.c 
lauxlib.c 
lbaselib.c 
lbitlib.c 
lcorolib.c 
ldblib.c 
liolib.c 
lmathlib.c 
loslib.c 
lstrlib.c 
ltablib.c 
loadlib.c 
linit.c
lua.c
)

#add_library ("Lua${Lua_Version}" STATIC ${LUA_SOURCES})

if (LIBRARY_TYPE_SHARED)
add_library ("Lua${Lua_Version}" SHARED ${LUA_SOURCES})
endif ()

if (LIBRARY_TYPE_STATIC) 
add_library ("Lua${Lua_Version}_Static" STATIC ${LUA_SOURCES})
#set_target_properties ("Lua${Lua_Version}_Static" PROPERTIES OUTPUT_NAME "Lua${Lua_Version}")
endif ()

