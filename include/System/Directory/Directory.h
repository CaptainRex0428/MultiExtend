#pragma once 

#include "MultiExtendAPI.h"

#include <iostream>
#include <vector>
#include <string>
#include <tuple>

namespace MultiExtend
{
	class Directory
	{
	//static 
	public:

		MULTIEXTEND_API static bool isDirectoryPathValid(std::string directoryPath);
		
		MULTIEXTEND_API static bool Create(std::string directoryPath,bool force = false);

		MULTIEXTEND_API static int Walk(std::string directoryPath, std::vector<std::string>& files, std::vector<std::string>& folders, bool recursion = false);
		MULTIEXTEND_API static int Walk(std::string directoryPath, bool clear, std::vector<std::string>& files, std::vector<std::string>& folders, bool recursion = false);
		
		MULTIEXTEND_API static std::string GetParentPath(std::string directoryPath);

	private:
		MULTIEXTEND_API static Directory& Get();

	// class is singleton 
	public:
		MULTIEXTEND_API Directory(Directory&) = delete;

	private:
		MULTIEXTEND_API Directory();
		MULTIEXTEND_API virtual ~Directory();

	};
}