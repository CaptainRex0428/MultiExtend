#pragma once


#ifdef _DEBUG 

	#define MULTIEXTEND_MESSAGE_TERMINAL_TRACE(...) MultiExtend::Message::GetTerminalMessager()->trace(__VA_ARGS__)
	#define MULTIEXTEND_MESSAGE_TERMINAL_INFO(...) MultiExtend::Message::GetTerminalMessager()->info(__VA_ARGS__)
	#define MULTIEXTEND_MESSAGE_TERMINAL_DEBUG(...) MultiExtend::Message::GetTerminalMessager()->debug(__VA_ARGS__)

	#define MULTIEXTEND_MESSAGE_CLIENT_INFO(...) MultiExtend::Message::GetClientMessager()->info(__VA_ARGS__)
	#define MULTIEXTEND_MESSAGE_CLIENT_TRACE(...) MultiExtend::Message::GetClientMessager()->trace(__VA_ARGS__)
	#define MULTIEXTEND_MESSAGE_CLIENT_DEBUG(...)  MultiExtend::Message::GetClientMessager()->debug(__VA_ARGS__) 
#else

	#define MULTIEXTEND_MESSAGE_TERMINAL_TRACE(...)
	#define MULTIEXTEND_MESSAGE_TERMINAL_INFO(...)
	#define MULTIEXTEND_MESSAGE_TERMINAL_DEBUG(...)
	
	#define MULTIEXTEND_MESSAGE_CLIENT_INFO(...)
	#define MULTIEXTEND_MESSAGE_CLIENT_TRACE(...)
	#define MULTIEXTEND_MESSAGE_CLIENT_DEBUG(...)
#endif


#define MULTIEXTEND_MESSAGE_TERMINAL_WARN(...) MultiExtend::Message::GetTerminalMessager()->warn(__VA_ARGS__)
#define MULTIEXTEND_MESSAGE_TERMINAL_ERROR(...) MultiExtend::Message::GetTerminalMessager()->error(__VA_ARGS__)
#define MULTIEXTEND_MESSAGE_TERMINAL_CRITICAL(...) MultiExtend::Message::GetTerminalMessager()->critical(__VA_ARGS__)

#define MULTIEXTEND_MESSAGE_CLIENT_WARN(...) MultiExtend::Message::GetClientMessager()->warn(__VA_ARGS__)
#define MULTIEXTEND_MESSAGE_CLIENT_ERROR(...) MultiExtend::Message::GetClientMessager()->error(__VA_ARGS__)
#define MULTIEXTEND_MESSAGE_CLIENT_CRITICAL(...) MultiExtend::Message::GetClientMessager()->critical(__VA_ARGS__)