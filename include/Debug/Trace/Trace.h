#pragma once

#include "MultiExtendAPI.h"

#include "System/File/File.h"

#include <string>
#include <fstream>
#include <iostream>

namespace MultiExtend
{
	struct TraceProfile
	{
		std::string RecordName;
		long long Start, End;
		size_t ThreadID;
	};

	class Trace
	{
	public:
		MULTIEXTEND_API Trace(Trace&) = delete;

		MULTIEXTEND_API static void Start();
		MULTIEXTEND_API static void Stop();
		MULTIEXTEND_API static void Record(const TraceProfile& result);

	private:

		MULTIEXTEND_API Trace();
		MULTIEXTEND_API virtual ~Trace();

		MULTIEXTEND_API static Trace& Get();

		MULTIEXTEND_API void BeginSession();
		MULTIEXTEND_API void EndSession();
		MULTIEXTEND_API void WriteProfile(const TraceProfile& result);
		MULTIEXTEND_API void WriteHeader();
		MULTIEXTEND_API void WriteFooter();

	private:
		File* m_traceFile;
		bool m_isRecording;
		int m_ProfileCount;
	};

}