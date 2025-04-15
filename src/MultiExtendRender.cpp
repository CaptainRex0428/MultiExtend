#include "MultiExtendRender.h"

#include "SDL.h"
#include "SDL_image.h"

#include "Texture/Texture.h"

namespace MultiExtend
{

	void SDLRender::ClearRenderer(SDL_Renderer* renderer)
	{
		if (renderer)
		{
			SDL_RenderClear(renderer);
		}
	}

	void SDLRender::RenderPresent(SDL_Renderer* renderer)
	{
		MULTIEXTEND_TIMER_TRACE_TAG(RenderPresent);

		if (renderer)
		{
			SDL_RenderPresent(renderer);
		}
	}
}