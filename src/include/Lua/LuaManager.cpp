#include "LuaManager.h"
#include "stdio.h"

extern "C"
{
	#include "lua.h"
	#include "lualib.h"
	#include "lauxlib.h"
}

LuaManager* LuaManager::manager = nullptr;

LuaManager::LuaManager()
{
	state = luaL_newstate();
	luaL_openlibs(state);
	luaL_dofile(state, "test.lua");
}

LuaManager::~LuaManager()
{
	lua_close(state);
    delete manager;
    manager = nullptr;
}

LuaManager* LuaManager::GetInstance()
{
    if (manager == nullptr)
    {
        manager = new LuaManager();
    }
    return manager;
}

void LuaManager::CallLuaFunction(std::string fn)
{
	lua_getglobal(state, fn.c_str());

	if (lua_pcall(state, 0, 0, 0) != LUA_OK)
	{
		printf("error running function 'f': %s\n",
                lua_tostring(state, -1));
	}
}



// double f (lua_State *L, double x, double y) {
//      int isnum;
//      double z;
//      /* push functions and arguments */
//      lua_getglobal(L, "f");  /* function to be called */
//      lua_pushnumber(L, x);   /* push 1st argument */
//      lua_pushnumber(L, y);   /* push 2nd argument */
//      /* do the call (2 arguments, 1 result) */
//      if (lua_pcall(L, 2, 1, 0) != LUA_OK)
       // error(L, "error running function 'f': %s",
       //          lua_tostring(L, -1));
//      /* retrieve result */
//      z = lua_tonumberx(L, -1, &isnum);
//      if (!isnum)
//        error(L, "function 'f' must return a number");
//      lua_pop(L, 1);  /* pop returned value */
//      return z;
// }