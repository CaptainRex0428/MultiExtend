#include <iostream>

#include "MultiExtend.h"

extern "C" 
{
    #include "lua.h"
    #include "lauxlib.h"
    #include "lcrypto.h"
}


int main()
{
	MultiExtend::Init();
	
	luacrypto_init();

	std::cin.get();
	return 0;
}