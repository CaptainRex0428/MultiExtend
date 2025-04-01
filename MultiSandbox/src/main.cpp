#include "Sandbox.h"

int main(int argc, char * argv[])
{
	if (MultiExtendSandbox::Sandbox::Init())
	{
		MultiExtendSandbox::Sandbox::RunLoop();
		MultiExtendSandbox::Sandbox::ShutDown();
	}

	auto time = MultiExtend::GlobalClock::GetProcessStartTime();

	return 0;
}