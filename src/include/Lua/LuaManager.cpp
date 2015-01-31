#include "LuaManager.h"
#include "stdio.h"
#include <string>

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

ProcessStatus::Enum LuaManager::CallLuaFunction(std::string fn)
{
	lua_getglobal(state, fn.c_str());

	if (lua_pcall(state, 0, 1, 0) != LUA_OK)
	{
		printf("error running function '%s': %s\n", fn.c_str(),
                lua_tostring(state, -1));
	}

	std::string output(lua_tostring(state, -1));
	lua_pop(state, 1);

	ProcessStatus::Enum processStatus;
	if (!output.compare("success"))
	{
		processStatus = ProcessStatus::Success;
	}
	else if (!output.compare("failure"))
	{
		processStatus = ProcessStatus::Failure;
	}
	else if (!output.compare("running"))
	{
		processStatus = ProcessStatus::Running;
	}
	else
	{
		// TODO: throw error
		printf("function must return correct string\n");
	}

	return processStatus;
}
