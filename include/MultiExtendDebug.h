#pragma once

#include "MultiExtendAPI.h"
#include "Debug/Log/Log.h"
#include "Debug/Message/Message.h"

namespace MultiExtend 
{
	inline void MsgLog(std::string Content, Log* logger, LogLevel _Level = MultiExtend::Trace)
	{
		logger->Write(Content, _Level);

		switch (_Level)
		{
		case MultiExtend::Trace:
			MultiExtend::Message::GetClientMessager()->trace(Content);
			break;
		case MultiExtend::Debug:
			MultiExtend::Message::GetClientMessager()->debug(Content);
			break;
		case MultiExtend::Info:
			MultiExtend::Message::GetClientMessager()->info(Content);
			break;
		case MultiExtend::Warning:
			MultiExtend::Message::GetClientMessager()->warn( Content);
			break;
		case MultiExtend::Error:
			MultiExtend::Message::GetClientMessager()->error(Content);
			break;
		case MultiExtend::Critical:
			MultiExtend::Message::GetClientMessager()->critical(Content);
			break;
		default:
			MultiExtend::Message::GetClientMessager()->trace(Content);
			break;
		}
	}

	inline void MsgLog(std::string Content, LogLevel _Level = MultiExtend::Trace)
	{
		Log* logger = new Log();

		MsgLog(Content, logger, _Level);
	}
}