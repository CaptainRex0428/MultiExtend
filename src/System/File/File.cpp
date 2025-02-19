#include "System/File/File.h"
#include "System/File/FileConfig.h"

#include "Math/Math.h"

#include "MultiExtendMicro.h" 
#include "MultiExtendConfig.h"

#include "Debug/Message/Message.h"
#include "Debug/Message/MessageMicro.h"

#include "System/Directory/Directory.h"

#include <filesystem>
#include <cassert>
#include <format>

namespace MultiExtend 
{
	bool File::isFilePathValid(std::string filepath)
	{
		MULTIEXTEND_FILESYSTEM::path _p(filepath);
		return MULTIEXTEND_FILESYSTEM::status(_p).type() == MULTIEXTEND_TAG_FILESYSTEM_TYPE_FILE;
	}

	File::File()
		:m_valid(false), 
		m_filefolder(""), 
		m_filename(""),
		m_ofstream(nullptr),
		m_ifstream(nullptr)
	{
	}

	File::File(std::string filepath)
		:m_valid(false), 
		m_ofstream(nullptr),
		m_ifstream(nullptr)
	{
		if (filepath.empty())
		{
			return;
		}

		MULTIEXTEND_FILESYSTEM::path p(filepath);
		m_filename = p.filename().string();
		m_filefolder = p.parent_path().string();

		if (m_filefolder.empty())
		{
			m_filefolder = "./";
		}
	}

	File::~File()
	{
		CloseStream();
	}

	int File::Open(bool force)
	{
		if (!m_filefolder.empty() && !m_filename.empty())
		{
			if (m_valid) 
			{
			#ifdef _DEBUG
				MULTIEXTEND_MESSAGE_TERMINAL_WARN(MULTIEXTEND_PATTERN_FILE_REOPEN_WARN, GetFullPath(), MULTIEXTEND_TAG_DEBUG_DETAIL_OUT);
			#endif
				return 0;
			}

			if (force)
			{
				if (MULTIEXTEND_FILESYSTEM::status(m_filefolder).type() != MULTIEXTEND_TAG_FILESYSTEM_TYPE_DIRECTORY)
				{
					MULTIEXTEND_FILESYSTEM::create_directories(m_filefolder);
				#ifdef _DEBUG
					MULTIEXTEND_MESSAGE_TERMINAL_DEBUG(MULTIEXTEND_PATTERN_FILE_FOLDER_CREATED, m_filefolder, MULTIEXTEND_TAG_DEBUG_DETAIL_OUT);
				#endif
				}

				if (OpenWriteStream() == -1)
				{
				#ifdef _DEBUG
					MULTIEXTEND_MESSAGE_TERMINAL_ERROR(MULTIEXTEND_PATTERN_FILE_OPEN_FAILED, GetFullPath(), MULTIEXTEND_TAG_DEBUG_DETAIL_OUT);
				#endif
					return -1;
				}
				
				m_valid = true;
				return 0;
			}
			else
			{
				if (MULTIEXTEND_FILESYSTEM::status(GetFullPath()).type() != MULTIEXTEND_TAG_FILESYSTEM_TYPE_FILE)
				{
				#ifdef _DEBUG
					MULTIEXTEND_MESSAGE_TERMINAL_ERROR(MULTIEXTEND_PATTERN_PATH_NEXIST_ERROR,GetFullPath(), MULTIEXTEND_TAG_DEBUG_DETAIL_OUT);
				#endif
					return -2;
				}

				if (OpenWriteStream() == -1)
				{
				#ifdef _DEBUG
					MULTIEXTEND_MESSAGE_TERMINAL_ERROR(MULTIEXTEND_PATTERN_FILE_OPEN_FAILED, GetFullPath(), MULTIEXTEND_TAG_DEBUG_DETAIL_OUT);
				#endif
					return -1;
				}

				m_valid = true;
				return 0;
			}

		}
	#ifdef _DEBUG
		MULTIEXTEND_MESSAGE_TERMINAL_ERROR(MULTIEXTEND_PATTERN_FILE_PATH_NULL, MULTIEXTEND_TAG_DEBUG_DETAIL_OUT);
	#endif
		return -3;
	}

	int File::Open(std::string filepath, bool force)
	{
		if (filepath.empty())
		{
		#ifdef _DEBUG
			MULTIEXTEND_MESSAGE_TERMINAL_ERROR(MULTIEXTEND_PATTERN_FILE_PATH_NULL, MULTIEXTEND_TAG_DEBUG_DETAIL_OUT);
		#endif
			return -1;
		}

		Close();

		MULTIEXTEND_FILESYSTEM::path p(filepath);
		m_filename = p.filename().string();
		m_filefolder = p.parent_path().string();

		if (m_filefolder.empty())
		{
			m_filefolder = "./";
		}

		return Open(force);
	}

	int File::OpenWriteStream()
	{
		std::string _Path = GetFullPath();

		m_ofstream = new std::ofstream(_Path.c_str(), std::ios_base::out | std::ios_base::app, _SH_DENYNO);

		return m_ofstream->is_open() ? 0 : -1;
	}

	int File::OpenReadStream()
	{
		std::string _Path = GetFullPath();

		m_ifstream = new std::ifstream(_Path.c_str(), std::ios_base::in, _SH_DENYNO);

		return m_ifstream->is_open() ? 0 : -1;
	}

	void File::CloseWriteStream()
	{
		if (m_ofstream != nullptr) 
		{
			if (m_ofstream->is_open())
			{
				m_ofstream->flush();
				m_ofstream->close();
			}

			delete m_ofstream;
			m_ofstream = nullptr;
		}
	}

	void File::CloseReadStream()
	{
		if (m_ifstream != nullptr) 
		{
			if (m_ifstream->is_open())
			{
				m_ifstream->close();
			}

			delete m_ifstream;
			m_ifstream = nullptr;
		}
	}

	void File::CloseStream()
	{
		CloseWriteStream();
		CloseReadStream();
	}

	void File::Close()
	{
		CloseStream();

		m_valid = false;

		m_filename = "";
		m_filefolder = "";
	}

	bool File::Write(std::string Content)
	{
		if (m_valid && m_ofstream!= nullptr)
		{
			*m_ofstream << Content << std::endl;
			m_ofstream->flush();

			return true;
		}

		return false;
	}

	void File::Print()
	{
		if (!m_valid)
		{
			return;
		}

		auto vector = GetContent();
		auto [_unit, _size] = MultiExtend::Math::ByteSizeConvert(GetFileByteSize());

		MULTIEXTEND_MESSAGE_TERMINAL_TRACE(MULTIEXTEND_PATTERN_OUTFILE_TILTE, MULTIEXTEND_PATTERN_OUTFILE_FORMATDASH, m_filename, _size, _unit);

		for (auto list : vector)
		{
			MULTIEXTEND_MESSAGE_TERMINAL_TRACE(list);
		}

		MULTIEXTEND_MESSAGE_TERMINAL_TRACE(MULTIEXTEND_PATTERN_OUTFILE_FOOTER, MULTIEXTEND_PATTERN_OUTFILE_FORMATDASH, m_filename, _size, _unit);
	}

	void File::Clear()
	{
		if (!m_valid)
		{
			return;
		}

		CloseStream();

		m_ofstream = new std::ofstream(GetFullPath(), std::ios::out | std::ios::trunc);

	#ifdef _DEBUG
		MULTIEXTEND_MESSAGE_TERMINAL_TRACE(MULTIEXTEND_PATTERN_FILE_RESET_TIP,GetFullPath(), MULTIEXTEND_TAG_DEBUG_DETAIL_OUT);
	#endif

	}

	std::vector<std::string> File::GetContent()
	{
		std::vector<std::string> *vector = new std::vector<std::string>();

		if (!m_valid)
		{
			return *vector;
		}

		CloseReadStream();
		OpenReadStream();

		std::string line;
		
		if (m_ifstream->is_open())
		{
			while (getline(*m_ifstream, line))
			{
				vector->push_back(line);
			}

			CloseReadStream();
		}

		return *vector;
	}

	uintmax_t File::GetFileByteSize()
	{
		if (!m_valid)
		{
			return 0;
		}

		return MULTIEXTEND_FILESYSTEM::file_size(GetFullPath());
	}

	std::string File::GetFullPath()
	{
		if (!m_filename.empty() && !m_filefolder.empty())
			return std::format("{0}/{1}", m_filefolder, m_filename);

		return "";
	}

}