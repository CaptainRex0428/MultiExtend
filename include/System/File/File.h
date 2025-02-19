#pragma once

#include "MultiExtendAPI.h"

#include "MultiExtendConfig.h"

#include "System/File/FileConfig.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>


namespace MultiExtend
{
	class File
	{
	// static
	public:
		MULTIEXTEND_API static bool isFilePathValid(std::string filepath);

	// class
	public:
		MULTIEXTEND_API File();
		MULTIEXTEND_API File(std::string filepath);
		MULTIEXTEND_API virtual ~File();

		MULTIEXTEND_API virtual int Open(bool force = false);
		MULTIEXTEND_API virtual int Open(std::string filepath, bool force = false);

		MULTIEXTEND_API virtual void CloseStream();
		MULTIEXTEND_API virtual void Close();
		
		MULTIEXTEND_API virtual bool Write(std::string Content);

		MULTIEXTEND_API virtual void Print();
		MULTIEXTEND_API virtual void Clear();

		MULTIEXTEND_API std::string GetFullPath();
		MULTIEXTEND_API std::vector<std::string> GetContent();
		MULTIEXTEND_API uintmax_t GetFileByteSize();

	protected:
		MULTIEXTEND_API virtual int OpenWriteStream();
		MULTIEXTEND_API virtual int OpenReadStream();
		MULTIEXTEND_API virtual void CloseWriteStream();
		MULTIEXTEND_API virtual void CloseReadStream();
	
	//var
	protected:
		bool m_valid;
		std::string m_filefolder;
		std::string m_filename;
		std::ifstream * m_ifstream;
		std::ofstream * m_ofstream;
	};

}