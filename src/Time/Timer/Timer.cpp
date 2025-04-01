#include "Time/Timer/Timer.h"

#include "Debug/Message/Message.h"
#include "Debug/Trace/Trace.h"

#include <thread>

namespace MultiExtend {
	Timer::Timer(const char* _tag, const char* _obj, bool _traced, long double& _ms)
		:m_tag(_tag),
		m_obj(_obj),
		m_ms(&_ms),
		m_traced(_traced),
		m_ConstructedTime(GetCurrentTime_HighRes()),
		m_DestructedTime(GetCurrentTime_HighRes())
	{
	}

	Timer::~Timer()
	{
		m_DestructedTime = GetCurrentTime_HighRes();

		MULTIEXTEND_CLOCK_HIGHRES::duration _duration= m_DestructedTime - m_ConstructedTime;
		auto duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(_duration);
		*m_ms = (long double)duration_ms.count();

	#ifdef _DEBUG_TIMER
		MultiExtend::Message::GetTerminalMessager()->debug("{0} cost {1:.2f} ms",m_obj,*m_ms);
	#endif

		if (m_traced)
		{
			auto start_ms = std::chrono::time_point_cast<std::chrono::microseconds>(m_ConstructedTime);
			long long start = start_ms.time_since_epoch().count();

			auto end_ms = std::chrono::time_point_cast<std::chrono::microseconds>(m_DestructedTime);
			long long end = end_ms.time_since_epoch().count();

			size_t threadID = std::hash<std::thread::id>{}(std::this_thread::get_id());

			MultiExtend::TraceProfile result{m_obj,start,end,threadID};
			
			Trace::Record(result);
		}
	}
}
