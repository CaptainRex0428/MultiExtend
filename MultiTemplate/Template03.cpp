
#include <iostream>
#include <fstream>
#include <Windows.h>

#include "MultiExtend.h"


int main()
{
	MultiExtend::Init();

	std::string timeStamp = MultiExtend::Clock::GetCurrentTimeStamp_sys();
	std::string taga = "taga";
	std::string tagb = "tagb";
	std::string hashResult = MultiExtend::SHAGenerator::GenerateSHA256Hash(timeStamp,taga,tagb);

	MULTIEXTEND_MESSAGE_CLIENT_DEBUG(hashResult);

	std::cin.get();
}