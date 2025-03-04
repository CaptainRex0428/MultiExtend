#include "MultiExtend.h"

#include "SDL.h"

namespace MultiExtend
{

	int Init(int inittag)
	{
		MultiExtend::Message::Init();
		MultiExtend::GlobalClock::Init();

		MultiExtend::Operator::Get().Init();

		if (inittag & SDL)
		{
			if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
			{
				SDL_Log("SDL init error:%s", SDL_GetError());
				return 0;
			};
		}
		
		return 1;
	}
}