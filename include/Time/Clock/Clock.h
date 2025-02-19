#pragma once

#include "MultiExtendAPI.h"

#include <iostream>
#include <chrono>

#include "Time/Clock/ClockConfig.h"

namespace MultiExtend {

	struct ClockProfile
	{
		const tm * m_time;
		std::string m_time_str;
		MULTIEXTEND_CLOCK_STEADY::time_point m_time_highres;
	};

	// Clock is singleton
	class Clock {

	public:
		MULTIEXTEND_API Clock(Clock&) = delete;

		MULTIEXTEND_API static const tm* GetCurrentTime_sys();
		MULTIEXTEND_API static const ClockProfile GetCurrentTime_sys_profile(const char* _timepattern = MULTIEXTEND_TIME_STRING_PATTERN_CORE);

		MULTIEXTEND_API static const tm* GetCurrentTime_gm();;
		MULTIEXTEND_API static const ClockProfile GetCurrentTime_gm_profile(const char* _timepattern = MULTIEXTEND_TIME_STRING_PATTERN_CORE);;

		MULTIEXTEND_API static const MULTIEXTEND_CLOCK_STEADY::time_point GetCurrentTime_HighRes();
		
	protected:
		MULTIEXTEND_API Clock();
		MULTIEXTEND_API virtual ~Clock();

		MULTIEXTEND_API static Clock& Get();

		MULTIEXTEND_API static const time_t GetCurrentTime_time_t();
		
	};

	
}