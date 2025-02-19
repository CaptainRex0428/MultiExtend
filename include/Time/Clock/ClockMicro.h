#pragma once

#define MULTIEXTEND_CLOCK_CURRENT_TIME_SYS(...) MultiExtend::Clock::GetCurrentTime_sys(__VA_ARGS__)
#define MULTIEXTEND_CLOCK_CURRENT_TIME_GM(...) MultiExtend::Clock::GetCurrentTime_gm(__VA_ARGS__)

#define MULTIEXTEND_CLOCK_CURRENT_TIME_HIGHRES(...) MultiExtend::Clock::GetCurrentTime_HighRes(__VA_ARGS__)

#define MULTIEXTEND_CLOCK_PROCESS_START_SYS_TIME(...) MultiExtend::Clock::GetProcessStartTime(__VA_ARGS__)
#define MULTIEXTEND_CLOCK_PROCESS_START_SYS_TIME_CHAR(...) MultiExtend::Clock::GetProcessStartTime_CHAR(__VA_ARGS__)
#define MULTIEXTEND_CLOCK_PROCESS_START_SYS_TIME_HIGHRES(...) MultiExtend::Clock::GetProcessStartTime_HIGHRES(__VA_ARGS__)