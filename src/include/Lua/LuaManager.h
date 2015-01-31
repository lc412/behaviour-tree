#ifndef _luamanager_h
#define _luamanager_h

#include <string>

// Forward declarations
class lua_State;

class LuaManager final
{
public:
	static LuaManager* GetInstance();

	~LuaManager();

	void CallLuaFunction(std::string fn);
private:
	LuaManager();

	static LuaManager* manager;

	lua_State* state;
};

#endif