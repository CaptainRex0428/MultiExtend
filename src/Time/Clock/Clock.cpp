//
// Created by rvo04 on 2024/3/31.
//

#include "Time/Clock/Clock.h"

#include "Debug/Message/Message.h"
#include "MultiExtendConfig.h"

#include <windows.h>
#include <minwindef.h>

namespace MultiExtend {

	// Definitions

	Clock::Clock()
	{
	}

	Clock::~Clock()
	{
	}

	Clock& Clock::Get() {
		static Clock instance;
		return instance;
	}

	const time_t Clock::GetCurrentTime_time_t() {
		return MULTIEXTEND_CLOCK_SYSTEM::to_time_t(MULTIEXTEND_CLOCK_SYSTEM::now());
	}

	const tm* Clock::GetCurrentTime_sys() {
		auto time = GetCurrentTime_time_t();
		return localtime(&time);
	}

	const ClockProfile Clock::GetCurrentTime_sys_profile(const char * _timepattern)
	{
		const tm* s_time = GetCurrentTime_sys();
		
		char s_time_str[MULTIEXTEND_MAX_TIME_STRING_SIZE];
		strftime(s_time_str, MULTIEXTEND_MAX_TIME_STRING_SIZE, _timepattern, s_time);

		MULTIEXTEND_CLOCK_STEADY::time_point s_time_point = GetCurrentTime_HighRes();
		
		return {s_time,s_time_str, s_time_point};
	}

	MULTIEXTEND_API const std::string Clock::GetCurrentTimeStamp_sys()
	{
		auto now = std::chrono::system_clock::now();
		auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());

		return std::to_string(ms.count());
	}

	const tm* Clock::GetCurrentTime_gm() {
		auto time = GetCurrentTime_time_t();
		return gmtime(&time);
	}

	const ClockProfile Clock::GetCurrentTime_gm_profile(const char* _timepattern)
	{
		const tm* s_time = GetCurrentTime_gm();

		char s_time_str[MULTIEXTEND_MAX_TIME_STRING_SIZE];
		strftime(s_time_str, MULTIEXTEND_MAX_TIME_STRING_SIZE, _timepattern, s_time);

		MULTIEXTEND_CLOCK_STEADY::time_point s_time_point = GetCurrentTime_HighRes();

		return { s_time,s_time_str, s_time_point };
	}

	const std::chrono::steady_clock::time_point Clock::GetCurrentTime_HighRes()
	{
		return MULTIEXTEND_CLOCK_HIGHRES::now();
	}
	
}