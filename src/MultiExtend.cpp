#include "MultiExtend.h"

namespace MultiExtend
{
	int Init()
	{
		MULTIEXTEND_TIMER_TRACE_TAG(InitMultiExtend);

		MultiExtend::Message::Init();
		MultiExtend::GlobalClock::Init();

		MultiExtend::Operator::Get().Init();

		return 1;
	};
}