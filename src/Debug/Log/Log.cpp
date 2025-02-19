#include "Debug/Log/Log.h"
#include "MultiExtendConfig.h"

namespace MultiExtend
{
	Log::Log()
		:m_Tag("CustomLog"),File(MULTIEXTEND_DEFAULT_LOG_PATH_REL)
	{
		Open(true);
	}

	Log::Log(std::string _tag)
		:m_Tag(_tag),File(MULTIEXTEND_DEFAULT_LOG_PATH_REL)
	{
		Open(true);
	}

	Log::Log(std::string _tag,std::string filepath)
		:m_Tag(_tag),File(filepath)
	{
		Open(true);
	}

	Log::~Log()
	{
	}

	int Log::SetTag(std::string _tag)
	{
		if (m_Tag.empty())
		{
			m_Tag = _tag;

			return 0;
		}

		return -1;
	}
	
	bool Log::Write(std::string Content, LogLevel _level)
	{
		if (!m_Tag.empty())
		{
			std::string level;
			
			switch (_level)
			{
			case MultiExtend::Trace:
				level = "Trace";
				break;
			case MultiExtend::Debug:
				level = "Debug";
				break;
			case MultiExtend::Info:
				level = "Info";
				break;
			case MultiExtend::Warning:
				level = "Warning";
				break;
			case MultiExtend::Error:
				level = "Error";
				break;
			case MultiExtend::Critical:
				level = "Critical";
				break;
			default:
				level = "Undefined";
				break;
			}

			std::string ContentResult = std::format("[{0}] [{1}] [{2}]:{3}", GetCurrentTime_sys_profile().m_time_str, m_Tag, level, Content);
			return File::Write(ContentResult);
		}

		return false;
	}

	bool Log::Write(std::string Content)
	{	
		return Write(Content, MultiExtend::Trace);
	}

	void Log::Clear()
	{
		return;
	}
}