#include "MultiExtend.h"

#include "SDL.h"
#include "SDL_image.h"

#include "Texture/Texture.h"

namespace MultiExtend
{
	int Init(int inittag)
	{
		MULTIEXTEND_TIMER_TRACE_TAG(InitMultiExtend);

		MultiExtend::Message::Init();
		MultiExtend::GlobalClock::Init();

		MultiExtend::Operator::Get().Init();
		
		if (inittag & InitFrameworkTag::SDL)
		{
			MULTIEXTEND_TIMER_TRACE_TAG(InitSDL);

			if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
			{
				SDL_Log("SDL init error:%s", SDL_GetError());
				return 0;
			};

			if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
			{
				SDL_Log("SDL init PNG image module error:%s", SDL_GetError());
				return 0;
			};
		}

		if (inittag & InitFrameworkTag::OpenGL)
		{
			MULTIEXTEND_TIMER_TRACE_TAG(InitOpenGL);

			// use the core OpenGL Profile
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,SDL_GL_CONTEXT_PROFILE_CORE);

			//Specify Version 3.3
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

			// request a color buffer per RGBA channel
			SDL_GL_SetAttribute(SDL_GL_RED_SIZE, COLORBUFFERSIZE);
			SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, COLORBUFFERSIZE);
			SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, COLORBUFFERSIZE);
			SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, COLORBUFFERSIZE);

			// Enable double buffering
			SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

			// Force OpenGL to use hardware acceleration
			SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
		}

		if (inittag & InitFrameworkTag::DirectX)
		{
			MULTIEXTEND_TIMER_TRACE_TAG(InitDirectX);
		}

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