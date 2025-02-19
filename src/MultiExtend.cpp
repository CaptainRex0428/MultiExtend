#include "MultiExtend.h"

namespace MultiExtend
{
	int Init()
	{
		MultiExtend::Message::Init();
		MultiExtend::GlobalClock::Init();

		MultiExtend::Operator::Get().Init();

		return 1;
	}
}