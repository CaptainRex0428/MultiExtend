#include "Time/Timer/Timer.h"

#include "Debug/Message/Message.h"
#include "Debug/Trace/Trace.h"

#include <thread>

namespace MultiExtend {
	Timer::Timer(const char* _tag, const char* _obj, bool _traced, double& _ms)
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
		*m_ms = (_duration.count() / 1000000.0f);

	#ifdef _DEBUG
		MultiExtend::Message::GetTerminalMessager()->debug("{0} cost {1:.2f} ms",m_obj,*m_ms);
	#endif

		if (m_traced)
		{
			long long start = m_ConstructedTime.time_since_epoch().count() / 1000000;
			long long end = m_DestructedTime.time_since_epoch().count() / 1000000;
			size_t threadID = std::hash<std::thread::id>{}(std::this_thread::get_id());

			MultiExtend::TraceProfile result{m_obj,start,end,threadID};
			
			Trace::Record(result);
		}
	}
}
