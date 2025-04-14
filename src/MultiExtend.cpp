#include "MultiExtend.h"

#include "SDL.h"
#include "SDL_image.h"

#include "Texture/Texture.h"

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

	void ClearRenderer(SDL_Renderer* renderer)
	{
		if (renderer)
		{
			SDL_RenderClear(renderer);
			return;
		}
	}

	void RenderPresent(SDL_Renderer* renderer)
	{
		MULTIEXTEND_TIMER_TRACE_TAG(RenderPresent);

		if (renderer)
		{
			MULTIEXTEND_TIMER_TRACE_TAG(RenderPresent_SDL);

			SDL_RenderPresent(renderer);
			return;
		}
	}
}