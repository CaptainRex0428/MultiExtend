#pragma once

#include "MultiExtendAPI.h"
#include "Time/Clock/Clock.h"

namespace MultiExtend
{
	class Timer : virtual public Clock
	{
	public:
		MULTIEXTEND_API Timer(const char * _tag, const char * _obj, bool _traced, long double & _ms);
		MULTIEXTEND_API virtual ~Timer();

	protected:
		const char* m_tag;
		const char* m_obj;
		bool m_traced;
		long double* m_ms;
		MULTIEXTEND_CLOCK_HIGHRES::time_point m_ConstructedTime;
		MULTIEXTEND_CLOCK_HIGHRES::time_point m_DestructedTime;
	};
}