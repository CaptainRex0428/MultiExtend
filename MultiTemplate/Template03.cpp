
#include <iostream>
#include <fstream>
#include <Windows.h>

#include "MultiExtend.h"
#include "Math/Math.h"
#include "Math/Color.h"
#include "Component/SpriteComponent.h"
#include "Component/AnimateSpriteComponent.h"
#include "Component/ScrollComponent.h"

#include "SDL.h"
#include "SDL_image.h"


class GameObject
{
public:
	GameObject(GameObject&) = delete;

	static GameObject & Get()
	{
		static GameObject instance;
		return instance;
	};

	static bool Initialize()
	{
		if (!MultiExtend::Init())
		{
			return false;
		};

		Get().m_window = SDL_CreateWindow("ObjectTest",
			100, 100,
			1920, 1080, 0);

		if (!Get().m_window)
		{
			SDL_Log("SDL create window error:%s", SDL_GetError());
			return false;
		}

		SDL_Renderer* renderer = SDL_CreateRenderer(Get().m_window, -1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

		if (!renderer)
		{
			SDL_Log("SDL create renderer error:%s", SDL_GetError());
			return false;
		}

		Get().m_renderer = new MultiExtend::RendererSDL(renderer);
		Get().m_isRunning = true;

		Actor * spriteStaticActor = MultiExtend::CreateActor<Actor>(Get().m_GameState);
		MultiExtend::SpriteComponent * spriteStatic = new MultiExtend::SpriteComponent(Get().m_GameState, Get().m_renderer, "../MultiTemplate/assets/Ship01.png");
		spriteStatic->SetSize(Vector2(64, 29));
		spriteStatic->SetPosition(Vector3(spriteStatic->GetSize().x/2, spriteStatic->GetSize().y/2,0));
		spriteStaticActor->AddActorComponent(spriteStatic);
		
		Actor* spriteAnimateActor = MultiExtend::CreateActor<Actor>(Get().m_GameState);
		std::vector<const char *> textures = 
		{
			"../MultiTemplate/assets/Ship01.png",
			"../MultiTemplate/assets/Ship02.png",
			"../MultiTemplate/assets/Ship03.png",
			"../MultiTemplate/assets/Ship04.png"
		};
		MultiExtend::AnimateSpriteComponent* spriteAnimate = new MultiExtend::AnimateSpriteComponent(10,Get().m_GameState, Get().m_renderer,textures);
		spriteAnimate->SetSize(Vector2(64, 29));
		spriteAnimate->SetPosition(Vector3(spriteAnimate->GetSize().x / 2, spriteAnimate->GetSize().y / 2, 0));
		spriteAnimateActor->AddActorComponent(spriteAnimate);
		spriteAnimateActor->SetPosition(Vector3(spriteStatic->GetSize().x,0,0));

		Actor* spriteScrollActor = MultiExtend::CreateActor<Actor>(Get().m_GameState);
		std::vector<const char*> scrolltextures =
		{
			"../MultiTemplate/assets/Farback01.png",
			"../MultiTemplate/assets/Farback02.png"
		};
		MultiExtend::ScrollSpriteComponent * scrollSprite = new MultiExtend::ScrollSpriteComponent(Get().m_GameState, Get().m_renderer, 100, scrolltextures);
		scrollSprite->SetRenderSize(Vector2(1024,100));
		scrollSprite->SetSourceSizeScale(Vector3(1.f,1.f,1));
		scrollSprite->SetScrollSpeed(100);
		spriteScrollActor->AddActorComponent(scrollSprite);
		spriteScrollActor->SetPosition(Vector3(spriteStatic->GetSize().x*2, 0, 0));

		Get().m_GameActor->AddChildActor(spriteStaticActor);
		Get().m_GameActor->AddChildActor(spriteAnimateActor);
		Get().m_GameActor->AddChildActor(spriteScrollActor);

		return true;
	};


	static void Runloop()
	{
		while (Get().m_isRunning)
		{
			Get().ProcessInput();
			Get().UpdateGame();
			Get().GenerateOuput();
		}
	};

	static void ShutDown()
	{
		IMG_Quit();

		SDL_DestroyWindow(Get().m_window);
		SDL_DestroyRenderer(Get().m_renderer->GetRendererAs<SDL_Renderer>());

		SDL_Quit();

		Get().m_isRunning = false;
	};

private:
	GameObject()
	:m_window(nullptr), m_renderer(nullptr), m_isRunning(false),
	m_tickcount(0),m_delta(0)
	{
		m_GameState = MultiExtend::CreateGameState<GameState>();
		m_GameActor = MultiExtend::CreateActor<Actor>(m_GameState);
	};
	
	virtual ~GameObject()
	{
		IMG_Quit();

		if (m_isRunning)
		{
			Get().ShutDown();
			m_isRunning = false;
		}

		if (m_window)
		{
			SDL_DestroyWindow(m_window);
		}

		if (m_renderer)
		{
			SDL_DestroyRenderer(m_renderer->GetRendererAs<SDL_Renderer>());
		}
	};

	void ProcessInput()
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				m_isRunning = false;
				break;
			default:
				continue;
			}
		}
	};
	
	void UpdateGame()
	{
		int ticks;

		// limit the frame time span to 16ms
		while (!SDL_TICKS_PASSED(ticks = SDL_GetTicks(), m_tickcount + 16));

		m_delta = (ticks - m_tickcount) / 1000.0f;
		m_tickcount = ticks;

		MultiExtend::Math::limit_min(m_delta, 0.05f);

		m_GameActor->Update(m_delta);
	};

	void GenerateOuput()
	{
		SDL_SetRenderDrawColor(Get().m_renderer->GetRendererAs<SDL_Renderer>(), 30,30,30,30);
		ClearRenderer(Get().m_renderer);

		m_GameActor->Draw();

		RenderPresent(Get().m_renderer);
	};

private:

	bool m_isRunning;
	SDL_Window* m_window;
	Renderer * m_renderer;

	long long int m_tickcount;
	float m_delta;

	GameState * m_GameState;
	Actor * m_GameActor;
};

int main(int argc, char** argv)
{
	{
		if (GameObject::Initialize())
		{
			GameObject::Runloop();
		};

		GameObject::ShutDown();
	}
	return 0;
}