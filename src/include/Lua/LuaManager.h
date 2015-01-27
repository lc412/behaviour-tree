#ifndef _luamanager_h
#define _luamanager_h

// Forward declarations
class lua_State;

class LuaManager final
{
public:
	static LuaManager* GetInstance();

	~LuaManager();

	void CallLuaFunction(const char* fn);
private:
	LuaManager();

	static LuaManager* manager;

	lua_State* state;
};

#endif