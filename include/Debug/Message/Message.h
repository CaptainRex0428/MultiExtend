#pragma once

#include "MultiExtendAPI.h"

#include "spdlog/spdlog.h"

namespace MultiExtend
{
	class Message
	{
	public:
		MULTIEXTEND_API Message();
		MULTIEXTEND_API virtual ~Message();

	public:
		MULTIEXTEND_API static void Init();

		MULTIEXTEND_API static std::shared_ptr<spdlog::logger>& GetTerminalMessager() ;
		MULTIEXTEND_API static std::shared_ptr<spdlog::logger>& GetClientMessager();

	private:
		inline static std::shared_ptr<spdlog::logger> m_TerminalMessager;
		inline static std::shared_ptr<spdlog::logger> m_ClientMessager;
	};
}