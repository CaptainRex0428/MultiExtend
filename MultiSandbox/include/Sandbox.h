#pragma once

#include "MultiExtend.h"

namespace MultiExtendSandbox
{
	class Sandbox
	{
	public:
		Sandbox(Sandbox&) = delete;

		static int Init();
		static void RunLoop();
		static void ShutDown();

	public:
		int PullEvents();
		int Update();
		int Output();
	
	private:
		Sandbox();
		~Sandbox();

		static Sandbox& Get() ;

	private:
		bool m_isRunning;
		MULTIEXTEND_FILE* m_f;
	};
}