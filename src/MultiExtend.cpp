#include "MultiExtend.h"

#include "SDL.h"

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
				SDL_Log("SDL init image module error:%s", SDL_GetError());
				return 0;
			};
		}

		return 1;
	};
	
	Texture* LoadTexture(GameStat* GameStat, Renderer* renderer, const char* filepath)
	{
		MULTIEXTEND_TIMER_TRACE_TAG(LoadTexture);

		if(!GameStat) return nullptr;

		if (renderer->IsA<SDL_Renderer>())
		{
			return LoadTexture(GameStat,renderer->GetRendererAs<SDL_Renderer>(), filepath);
		}

		return nullptr;
	}
	
	TextureSDL* LoadTexture(GameStat* GameStat, SDL_Renderer* renderer, const char* filepath)
	{
		MULTIEXTEND_TIMER_TRACE_TAG(LoadSDLTexture);

		if (!GameStat) return nullptr;

		std::ifstream f(filepath);

		if (!f.good())
		{
			SDL_Log("File Doesn't exist :%s", filepath);
			return nullptr;
		}

		SDL_Surface* surf = IMG_Load(filepath);

		if (!surf)
		{
			SDL_Log("Failed to load texture file :%s", filepath);
			return nullptr;
		}

		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surf);

		SDL_FreeSurface(surf);

		if (texture == nullptr)
		{
			SDL_Log("Failed to convert surface to texture :%s", filepath);
			return nullptr;
		}

		TextureSDL* textureSDL = new TextureSDL(texture, filepath);

		GameStat->AddTexture(textureSDL);

		MULTIEXTEND_MESSAGE_CLIENT_TRACE("Loaded Texture:{0}",filepath);

		return textureSDL;
	}

	void ClearRenderer(Renderer* renderer)
	{
		if (renderer->IsA<SDL_Renderer>())
		{
			SDL_RenderClear(renderer->GetRendererAs<SDL_Renderer>());
			return;
		}
	}

	void RenderPresent(Renderer* renderer)
	{
		MULTIEXTEND_TIMER_TRACE_TAG(RenderPresent);

		if (renderer->IsA<SDL_Renderer>())
		{
			MULTIEXTEND_TIMER_TRACE_TAG(RenderPresent_SDL);

			SDL_RenderPresent(renderer->GetRendererAs<SDL_Renderer>());
			return;
		}
	}
}