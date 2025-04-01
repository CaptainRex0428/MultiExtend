#include "Debug/Message/Message.h"

#include "MultiExtendMicro.h"
#include "Debug/Message/MessageConfig.h"
#include "Time/Clock/ClockConfig.h"

#include "MultiExtend.h"

#include <iostream>

#include "spdlog/sinks/stdout_color_sinks.h"

namespace MultiExtend
{
	/*std::shared_ptr<spdlog::logger> Message::m_TerminalMessager = spdlog::stderr_color_mt("Terminal");
	std::shared_ptr<spdlog::logger> Message::m_ClientMessager = spdlog::stderr_color_mt("Client");*/

	Message::Message()
	{
		std::cout << "M Cons" << std::endl;
	};

	Message::~Message()
	{
		std::cout << "M Dest" << std::endl;
	}

	void Message::Init()
	{
		MULTIEXTEND_TIMER_TRACE_TAG(InitMultiMessage);

		spdlog::set_pattern(MULTIEXTEND_MICRO_CONTACT(MULTIEXTEND_MICRO_CONTACT(MULTIEXTEND_PATTERN_SPDLOG_HEADER, MULTIEXTEND_TIME_STRING_PATTERN_CORE), MULTIEXTEND_PATTERN_SPDLOG_INFO));

		m_TerminalMessager = spdlog::stderr_color_mt("Terminal");
		m_TerminalMessager->set_level(spdlog::level::trace);

		#ifdef _DEBUG
		if (m_TerminalMessager)
		{
			m_TerminalMessager->trace("Screw Message[Terminal] Initialized.");
		}
		#endif

		m_ClientMessager = spdlog::stderr_color_mt("Client");
		m_ClientMessager->set_level(spdlog::level::trace);

		#ifdef _DEBUG
		if (m_ClientMessager)
		{
			m_ClientMessager->trace("Screw Message[Client] Initialized.");
		}
		#endif
	}

	std::shared_ptr<spdlog::logger>& Message::GetTerminalMessager()
	{
		return m_TerminalMessager; 
	}

	std::shared_ptr<spdlog::logger>& Message::GetClientMessager()
	{
		return m_ClientMessager; 
	}
}