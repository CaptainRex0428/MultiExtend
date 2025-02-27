#include <iostream>
#include <iostream>
#include <fstream>
#include <Windows.h>

#include "MultiExtend.h"

extern "C"
{
	#include "lua.h"
	#include "lauxlib.h"
	#include "lualib.h"
	#include "lcrypto.h"
}

#include "sha.h"
#include "files.h"
#include "hex.h"


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


int main(int argc, const char argv[])
{
	MultiExtend::Init();

	// lua test
	lua_State *L = luaL_newstate();
	luaL_openlibs(L);
	luaL_dofile(L, "test.lua");
	MULTIEXTEND_MESSAGE_CLIENT_DEBUG("TestFunction(3,7) >> {0}",TestFunction_LuaWrapper(L, 3, 7));
	lua_close(L);

	//cryptopp test
	std::ifstream input("test.lua",std::ios::binary);
	if (!input)
	{
		MULTIEXTEND_MESSAGE_CLIENT_ERROR("cannot open input file.");
		return 1;
	}

	CryptoPP::SHA256 hash;
	CryptoPP::byte digest[CryptoPP::SHA256::DIGESTSIZE];

	/*while (!input.eof())
	{
		char buffer[1024];
		input.read(buffer, sizeof(buffer));
		hash.Update((const byte*)buffer, input.gcount());
	}

	hash.Final(digest);

	CryptoPP::HexEncoder encoder(new CryptoPP::FileSink(std::cout));
	encoder.Put(digest, sizeof(digest));
	encoder.MessageEnd();*/

	
	std::cin.get();
	return 0;
}