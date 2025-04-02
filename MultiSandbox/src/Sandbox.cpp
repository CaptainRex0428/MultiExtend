#include "Sandbox.h"

#include <Windows.h>
#include "MultiExtendMicro.h"

namespace MultiExtendSandbox
{
	Sandbox::Sandbox()
		:m_isRunning(false),m_f(nullptr)
	{
	}

	Sandbox::~Sandbox()
	{
		if(m_isRunning == true || m_f != nullptr)
		{
			m_isRunning = false;

			m_f->Close();
			delete m_f;
			m_f = nullptr;
		}
	}

	Sandbox& Sandbox::Get()
	{
		static Sandbox instance;
		return instance;
	}

	int Sandbox::Init()
	{
		MultiExtend::Message::Init();
		MultiExtend::GlobalClock::Init();

		Get().m_f = new MultiExtend::File("./log/GameRun.log");
		Get().m_f->Open(true);
		Get().m_f->Write("Game init");

		Get().m_isRunning = true;

		return 1;
	}

	void Sandbox::RunLoop()
	{
		MultiExtend::Trace::Start();

		long double loopFrame = 0;

		int loopTime = 0;

		while (Get().m_isRunning)
		{
			MULTIEXTEND_TIMER_TRACE_RETURN(loopFrame);
			
			MULTIEXTEND_THREAD_DELAY_MICRO(1);

			MULTIEXTEND_MESSAGE_TERMINAL_WARN("{:.1f} ms",loopFrame);

			if (Get().PullEvents() != 0 || Get().Update() != 0)
			{
				Get().m_isRunning = false;
			};
			
			Get().Output();

			if (loopTime++ > 20)
			{
				Get().m_isRunning = false;
			};


		}
	}

	void Sandbox::ShutDown()
	{
		if (Get().m_isRunning)
		{
			Get().m_isRunning = false;
		}

		MultiExtend::Trace::Stop();

		std::cin.get();
	}

	int Sandbox::PullEvents()
	{
		MULTIEXTEND_TIMER_TRACE_TAG(DealEvents);

		MULTIEXTEND_THREAD_DELAY_MICRO(3000);

		return 0;
	}

	int Sandbox::Update()
	{
		MULTIEXTEND_TIMER_TRACE_TAG(UpdateFrame);

		MULTIEXTEND_THREAD_DELAY_MICRO(3000);

		return 0;
	}

	int Sandbox::Output()
	{
		MULTIEXTEND_TIMER_TRACE_TAG(GenerateOutput);

		MULTIEXTEND_THREAD_DELAY_MICRO(3000);

		return 0;
	}
}