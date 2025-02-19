#pragma once

#include "MultiExtendAPI.h"

#include "System/File/File.h"
#include "Time/Clock/Clock.h"

namespace MultiExtend
{
	enum LogLevel
	{
		Trace = 0,
		Debug = 1,
		Info = 2,
		Warning = 3,
		Error = 4,
		Critical = 5
	};

	class Log: virtual public File, virtual public Clock
	{
	public:
		MULTIEXTEND_API Log();
		MULTIEXTEND_API Log(std::string _tag);
		MULTIEXTEND_API Log(std::string _tag,std::string filepath);
		MULTIEXTEND_API virtual ~Log();

		MULTIEXTEND_API int SetTag(std::string _tag);
	
		MULTIEXTEND_API virtual bool Write(std::string Content, LogLevel _level);
		MULTIEXTEND_API virtual bool Write(std::string Content) override;

	protected:
		MULTIEXTEND_API virtual void Clear() override;

	protected:
		std::string m_Tag;
	};
}