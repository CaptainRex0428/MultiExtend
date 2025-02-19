#include "System/Directory/Directory.h"
#include "System/Directory/DirectoryConfig.h"

#include "MultiExtendConfig.h"
#include "MultiExtendMicro.h" 

#include "Debug/Message/Message.h"
#include "Debug/Message/MessageMicro.h"

#include <filesystem>

namespace MultiExtend
{
	Directory::Directory()
	{
	}

	Directory::~Directory()
	{
	}

	Directory& Directory::Get()
	{
		static Directory instance;
		return instance;
	}

	bool Directory::isDirectoryPathValid(std::string directoryPath)
	{
		MULTIEXTEND_FILESYSTEM::path _p(directoryPath);
		return MULTIEXTEND_FILESYSTEM::status(_p).type() == MULTIEXTEND_TAG_FILESYSTEM_TYPE_DIRECTORY;
	}

	bool Directory::Create(std::string directoryPath, bool force)
	{
		if (isDirectoryPathValid(directoryPath))
		{
		#ifdef _DEBUG
			MULTIEXTEND_MESSAGE_TERMINAL_ERROR(MULTIEXTEND_PATTERN_DIRECTORY_PATH_EXIST_ERROR, directoryPath, MULTIEXTEND_TAG_DEBUG_DETAIL_OUT ? __FUNCSIG__ : __FUNCTION__);
		#endif
			return false;
		}

		std::filesystem::path targetPath(directoryPath);

		if (force)
		{
			MULTIEXTEND_FILESYSTEM::create_directories(targetPath);
			return(isDirectoryPathValid(directoryPath));
		}
		else
		{
			MULTIEXTEND_FILESYSTEM::create_directory(targetPath);
			return(isDirectoryPathValid(directoryPath));
		}
	}

	int Directory::Walk(std::string directoryPath, std::vector<std::string>& files, std::vector<std::string>& folders, bool recursion)
	{
		if (!isDirectoryPathValid(directoryPath))
		{
			return -1;
		}

		intptr_t pathHandle;
		struct _finddata_t pathInfo;

		std::string pathTemp;

		if ((pathHandle = _findfirst(pathTemp.assign(directoryPath).append("/*").c_str(), &pathInfo)) != -1)
		{
			do
			{
				if (pathInfo.attrib & _A_SUBDIR)
				{
					if (strcmp(pathInfo.name, ".") != 0 && strcmp(pathInfo.name, "..") != 0)
					{
						folders.push_back(pathTemp.assign(directoryPath).append("/").append(pathInfo.name));
						
						if (recursion) 
						{
							Walk(pathTemp.assign(directoryPath).append("/").append(pathInfo.name).c_str(), files, folders, recursion);
						}
					}
				}
				else
				{
					files.push_back(pathTemp.assign(directoryPath).append("/").append(pathInfo.name));
				}
			} while (_findnext(pathHandle, &pathInfo) == 0);

		}

		return 0;
	}

	int Directory::Walk(std::string directoryPath, bool clear, std::vector<std::string>& files, std::vector<std::string>& folders, bool recursion)
	{
		if (clear)
		{
			if (!files.empty()) 
			{
				files.clear();
			};

			if (!folders.empty()) 
			{

				folders.clear();
			};
		}

		return Walk(directoryPath, files, folders, recursion);
	}

	std::string Directory::GetParentPath(std::string directoryPath)
	{
		std::filesystem::path dict_path(directoryPath);
		return dict_path.parent_path().string();
	}
}
