
#include <iostream>
#include <fstream>
#include <Windows.h>

#include "MultiExtend.h"
#include "Math/Math.h"
#include "Math/Color.h"
#include "Component/SpriteComponent.h"
#include "Component/AnimateSpriteComponent.h"
#include "Component/ScrollComponent.h"
#include "Component/TileMapComponent.h"
#include "Component/DynamicAnimateSpriteComponent.h"

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
			720,462, 0);

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

		Actor * spriteStaticActor = MultiExtend::CreateActor<Actor>(Get().m_GameStat);
		MultiExtend::SpriteComponent * spriteStatic = new MultiExtend::SpriteComponent(Get().m_GameStat, Get().m_renderer, "../assets/Ship01.png");
		spriteStatic->SetSize(Vector2(64, 29));
		spriteStatic->SetPositionRelative(Vector3(spriteStatic->GetSize().x/2, spriteStatic->GetSize().y/2,0));
		spriteStaticActor->AddActorComponent(spriteStatic);
		
		Actor* spriteAnimateActor = MultiExtend::CreateActor<Actor>(Get().m_GameStat);
		std::vector<const char *> textures = 
		{
			"../assets/Ship01.png",
			"../assets/Ship02.png",
			"../assets/Ship03.png",
			"../assets/Ship04.png"
		};
		MultiExtend::AnimateSpriteComponent* spriteAnimate = new MultiExtend::AnimateSpriteComponent(10,Get().m_GameStat, Get().m_renderer,textures);
		spriteAnimate->SetSize(Vector2(64, 29));
		spriteAnimate->SetPositionRelative(Vector3(spriteAnimate->GetSize().x / 2, spriteAnimate->GetSize().y / 2, 0));
		spriteAnimateActor->AddActorComponent(spriteAnimate);
		spriteAnimateActor->SetPositionRelative(Vector3(spriteStatic->GetSize().x,0,0));

		Actor* spriteScrollActor = MultiExtend::CreateActor<Actor>(Get().m_GameStat);
		std::vector<const char*> scrolltextures =
		{
			"../assets/Farback01.png",
			"../assets/Farback02.png"
		};
		MultiExtend::ScrollSpriteComponent * scrollSprite = new MultiExtend::ScrollSpriteComponent(Get().m_GameStat, Get().m_renderer,scrolltextures);
		scrollSprite->SetRenderSize(Vector2(512,32));
		scrollSprite->SetSourceSizeScale(Vector3(.2f,.2f,1));
		scrollSprite->SetScrollSpeed(80);
		scrollSprite->SetOffset(300);
		spriteScrollActor->AddActorComponent(scrollSprite);
		spriteScrollActor->SetPositionRelative(Vector3(spriteAnimateActor->GetPositionAbsolute().x + spriteAnimate->GetSize().x, 0, 0));

		Get().m_GameActor->AddChildActor(spriteStaticActor);
		Get().m_GameActor->AddChildActor(spriteAnimateActor);
		Get().m_GameActor->AddChildActor(spriteScrollActor);

		Actor* starScrollActor = MultiExtend::CreateActor<Actor>(Get().m_GameStat);
		std::vector<const char*> starScrolltextures =
		{
			"../assets/Stars.png",
		};
		MultiExtend::ScrollSpriteComponent* starScrollSprite = new MultiExtend::ScrollSpriteComponent(Get().m_GameStat, Get().m_renderer, starScrolltextures);
		starScrollSprite->SetRenderSize(Vector2(512, 32));
		starScrollSprite->SetSourceSizeScale(Vector3(.3f, .3f, 1));
		starScrollSprite->SetScrollSpeed(40);
		starScrollSprite->SetOffset(0);
		starScrollActor->AddActorComponent(starScrollSprite);
		starScrollActor->SetPositionRelative(Vector3(spriteAnimateActor->GetPositionAbsolute().x + spriteAnimate->GetSize().x,0, 0));

		Actor* tileMapActor = MultiExtend::CreateActor<Actor>(Get().m_GameStat);

		const char * tileMapPath = "../assets/Tiles.png";
		Texture * tileMap = MultiExtend::LoadTexture(Get().m_GameStat, Get().m_renderer, tileMapPath);

		MultiExtend::TileMapComponent* tileMapA = new MultiExtend::TileMapComponent(Get().m_renderer, tileMap);
		tileMapA->SetSrcPosition(Vector2(97,1));
		tileMapA->SetSrcSize(Vector2(30, 30));
		tileMapA->SetDstSize(Vector2(32, 32));

		MultiExtend::TileMapComponent* tileMapB = new MultiExtend::TileMapComponent(Get().m_renderer, tileMap);
		tileMapB->SetSrcPosition(Vector2(65, 1));
		tileMapB->SetSrcSize(Vector2(30, 30));
		tileMapB->SetDstSize(Vector2(32, 32));
		tileMapB->SetPositionRelative(Vector3(33,0,0));

		tileMapActor->AddActorComponent(tileMapA);
		tileMapActor->AddActorComponent(tileMapB);
		tileMapActor->SetPositionRelative(Vector3(starScrollActor->GetPositionAbsolute().x + starScrollSprite->GetRenderSize().x, 0, 0));

		std::vector<const char*> ActorStepTextures =
		{
			"../assets/Character01.png",
			"../assets/Character02.png",
			"../assets/Character03.png",
			"../assets/Character04.png",
			"../assets/Character05.png",
			"../assets/Character06.png"
		};
		DynamicAnimateSpriteUnit * AnimateUnit_ActorStep = new DynamicAnimateSpriteUnit(Get().m_GameStat,Get().m_renderer, ActorStepTextures,"Step",LOOP,nullptr);

		std::vector<const char*> JUMPtextures =
		{
			"../assets/Character07.png",
			"../assets/Character08.png",
			"../assets/Character09.png",
			"../assets/Character10.png",
			"../assets/Character11.png",
			"../assets/Character12.png",
			"../assets/Character13.png",
			"../assets/Character14.png",
			"../assets/Character15.png",
		};
		DynamicAnimateSpriteUnit* AnimateUnit_ActorJump = new DynamicAnimateSpriteUnit(Get().m_GameStat, Get().m_renderer, JUMPtextures, "Jump", ONCE, nullptr);

		std::vector<const char*> Punchtextures =
		{
			"../assets/Character16.png",
			"../assets/Character17.png",
			"../assets/Character18.png"
		};
		DynamicAnimateSpriteUnit* AnimateUnit_ActorPunch = new DynamicAnimateSpriteUnit(Get().m_GameStat, Get().m_renderer, Punchtextures, "Punch", ONCE, nullptr);

		std::vector<DynamicAnimateSpriteUnit*> dynamicAnimateSpriteUnits = 
		{
			AnimateUnit_ActorStep,
			AnimateUnit_ActorJump,
			AnimateUnit_ActorPunch
		};
		DynamicAnimateSpriteComponent * PlayerBaseComp = new DynamicAnimateSpriteComponent(Get().m_renderer, dynamicAnimateSpriteUnits);

		PlayerBaseComp->SetDefaultDynamicSpriteUnit("Step");
		PlayerBaseComp->SetCurrentDynamicSpriteUnit("Step");
		PlayerBaseComp->SetAnimFPS(12);
		PlayerBaseComp->SetSize(Vector2(64, 64));
		PlayerBaseComp->SetTag("PlayerBaseComp");

		Actor* PlayerBaseActor = MultiExtend::CreateActor<Actor>(Get().m_GameStat, "PlayerBase");
		PlayerBaseActor->AddActorComponent(PlayerBaseComp);
		PlayerBaseActor->SetPositionRelative(Vector3(PlayerBaseComp->GetSize().x/2, spriteStatic->GetSize().y + PlayerBaseComp->GetSize().y / 2,0));
		

		Get().m_GameActor->AddChildActor(spriteStaticActor);
		Get().m_GameActor->AddChildActor(spriteAnimateActor);
		Get().m_GameActor->AddChildActor(spriteScrollActor);
		Get().m_GameActor->AddChildActor(starScrollActor);
		Get().m_GameActor->AddChildActor(tileMapActor);
		Get().m_GameActor->AddChildActor(PlayerBaseActor);

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
		m_GameStat = MultiExtend::CreateGameStat<GameStat>();
		m_GameActor = MultiExtend::CreateActor<Actor>(m_GameStat);
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

		// handle keyboard input
		const Uint8* state = SDL_GetKeyboardState(NULL);

		if (state[SDL_SCANCODE_ESCAPE])
		{
			m_isRunning = false;
		}

		if (state[SDL_SCANCODE_SPACE])
		{
			// player base
			Actor * PlayerBase = Get().m_GameActor->GetChildActor("PlayerBase");

			if(PlayerBase)
			{	
				MultiExtend::Component* BaseComp = PlayerBase->GetActorComponent("PlayerBaseComp");
				MultiExtend::DynamicAnimateSpriteComponent* PlayerBaseComp = static_cast<MultiExtend::DynamicAnimateSpriteComponent*>(BaseComp);

				if(PlayerBaseComp && PlayerBaseComp->bCanChangeCurrentUnit())
				{
					PlayerBaseComp->SetCurrentDynamicSpriteUnit("Jump");
				}
			};
		}

		if (state[SDL_SCANCODE_Q])
		{
			// player base
			Actor* PlayerBase = Get().m_GameActor->GetChildActor("PlayerBase");

			if (PlayerBase)
			{
				MultiExtend::Component* BaseComp = PlayerBase->GetActorComponent("PlayerBaseComp");
				MultiExtend::DynamicAnimateSpriteComponent* PlayerBaseComp = static_cast<MultiExtend::DynamicAnimateSpriteComponent*>(BaseComp);

				if (PlayerBaseComp && PlayerBaseComp->bCanChangeCurrentUnit())
				{
					PlayerBaseComp->SetCurrentDynamicSpriteUnit("Punch");
				}
			};
		}
	};
	
	void UpdateGame()
	{
		int ticks = SDL_GetTicks();

		// limit the frame time span to 16ms
		// while (!SDL_TICKS_PASSED(ticks = SDL_GetTicks(), m_tickcount + 16));

		m_delta = (ticks - m_tickcount) / 1000.0f;
		m_tickcount = ticks;

		// MultiExtend::Math::limit_min(m_delta, 0.05f);

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

	GameStat * m_GameStat;
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