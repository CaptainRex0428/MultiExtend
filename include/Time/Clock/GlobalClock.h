#pragma once

#include "MultiExtendAPI.h"
#include "Clock.h"

namespace MultiExtend
{
	class GlobalClock : virtual public Clock
	{
	public:
		MULTIEXTEND_API GlobalClock(GlobalClock&) = delete;

		MULTIEXTEND_API static int Init();

		MULTIEXTEND_API static const ClockProfile * GetProcessStartTime();

	protected:
		MULTIEXTEND_API virtual int Initialize();

	private:
		MULTIEXTEND_API GlobalClock();
		MULTIEXTEND_API virtual ~GlobalClock() override;

		MULTIEXTEND_API static GlobalClock& Get();
	
	private:
		bool m_initialized;

		ClockProfile * m_processStartTime;

	};
}