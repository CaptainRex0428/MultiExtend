#include <iostream>

#include "MultiExtend.h"

extern "C"
{
	#include "lua.h"
	#include "lauxlib.h"
	#include "lualib.h"
	#include "lcrypto.h"
}



int TestFunction_LuaWrapper(lua_State* L, int x, int y)
{
	//将“TestFunction”压入栈
	lua_getglobal(L, "TestFunction");

	//往栈中压入参数
	lua_pushnumber(L, x);
	lua_pushnumber(L, y);

	//调用函数，结果会压入栈
	lua_pcall(L
		, 2     //nargs：几个参数
		, 1     //nresults：几个返回值
		, 0);   //msgh：If msgh is 0, then the error object returned on the stack is exactly the original error object. Otherwise, msgh is the stack index of a message handler. 

	//获得结果，就是栈内的第一个元素
	int result = (int)lua_tonumber(L, -1);

	//出栈
	lua_pop(L, 1);

	return result;
}


int main()
{
	/*L = luaL_newstate();
	luaL_openlibs(L);
	luaL_dofile(L, "test.lua");
	std::cout << "调用TestFunction(3,7)的结果：" << TestFunction_LuaWrapper(3, 7) << std::endl;
	lua_close(L);*/

	lua_State* L;
	L = luaL_newstate();
	luaopen_crypto(L);
	lua_setglobal(L,"crypto");
	
	std::cin.get();
	return 0;
}