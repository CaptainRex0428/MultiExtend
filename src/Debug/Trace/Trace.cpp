#include "Debug/Trace/Trace.h"
#include "Debug/Trace/TraceConfig.h"

#include "System/File/File.h"
#include "Time/Clock/ClockConfig.h"

#include "Debug/Message/Message.h"
#include "Debug/Message/MessageMicro.h"

#include "Time/Clock/Clock.h"

#include <format>
#include <thread>


namespace MultiExtend
{
	Trace::Trace()
		:m_ProfileCount(0), m_isRecording(false),m_traceFile(nullptr)
	{
	}

	Trace::~Trace()
	{
		if(m_isRecording)
		{
			Stop();
		}
	}

	Trace& Trace::Get()
	{
		static Trace instance;
		return instance;
	}

	void Trace::BeginSession()
	{
		if (!m_isRecording)
		{
			auto _time = Clock::GetCurrentTime_sys_profile(MULTIEXTEND_TIME_STRING_PATTERN_FILE);
			size_t threadID = std::hash<std::thread::id>{}(std::this_thread::get_id());
			std::string filename = std::format("{0}-{1}", _time.m_time_str,threadID);

			std::string _path = std::format("{0}/{1}.json", MULTIEXTEND_DEFAULT_TRACE_FOLDER, filename);
			
			m_traceFile = new File(_path);

			if (m_traceFile->Open(true) == 0)
			{
				m_isRecording = true;

				WriteHeader();

				return;
			}

			m_traceFile->CloseStream();
			delete m_traceFile;
			m_traceFile = nullptr;
		}
	}

	void Trace::EndSession()
	{
		if (m_isRecording) 
		{
			WriteFooter();

			m_traceFile->CloseStream();
			delete m_traceFile;
			m_traceFile = nullptr;

			m_isRecording = false;
		}
	}

	void Trace::WriteProfile(const TraceProfile& result)
	{
		if (!m_isRecording)
		{
			return;
		}

		if (m_ProfileCount++ > 0)
			m_traceFile->Write(",");

		std::string name = result.RecordName;
		std::replace(name.begin(), name.end(), '"', '\'');

		m_traceFile->Write("{");
		m_traceFile->Write("\"cat\":\"function\",");
		m_traceFile->Write(std::format("\"dur\":{0},", std::to_string(result.End - result.Start)));
		m_traceFile->Write(std::format("\"name\":\"{0}\",", name));
		m_traceFile->Write("\"ph\":\"X\",");
		m_traceFile->Write(std::format("\"pid\":{0},",std::to_string(_getpid())));
		m_traceFile->Write(std::format("\"tid\":{0},", std::to_string(result.ThreadID)));
		m_traceFile->Write(std::format("\"ts\":{0}", std::to_string(result.Start)));
		m_traceFile->Write("}");
	}

	void Trace::WriteHeader()
	{
		if (m_isRecording) 
		{
			m_traceFile->Write("{\"otherData\": {},\"traceEvents\":[");
		}
	}

	void Trace::WriteFooter() {
		if (m_isRecording) 
		{
			m_traceFile->Write("]}");
		}
	}

	void Trace::Start()
	{
		Get().BeginSession();
	}

	void Trace::Stop()
	{
		Get().EndSession();
	}

	void Trace::Record(const TraceProfile& result)
	{
		if (Get().m_isRecording)
		{
			Get().WriteProfile(result);
		}
	}
}