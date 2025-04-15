#include <iostream>
#include <fstream>
#include <Windows.h>

#include "MultiExtend.h"
#include "Math/Math.h"
#include "Math/Color.h"
#include "Config/Game.h"
#include "Actor/Actor.h"
#include "Component/Sprite/SpriteSDLComponent.h"
#include "Component/Sprite/AnimateSpriteSDLComponent.h"
#include "Component/Sprite/ScrollSDLComponent.h"
#include "Component/Sprite/TileMapSDLComponent.h"
#include "Component/Sprite/DynamicAnimateSpriteSDLComponent.h"

#include "Object/GameObject.h"

class GameInstance: public GameObject
{
public:
	static GameInstance& Get();

	virtual bool Initialize(
		const char* windowTitle = "DefaultWindow",
		Vector2 position = { 100,100 },
		Vector2 size = { 1280,720 },
		InitFrameworkTag initTag = SDL,
		GameFrameMode mode = CUSTOM) override;

private:

	virtual void CustomProcessInput(const Uint8* state) override;
};

GameInstance& GameInstance::Get() {
	static GameInstance instance;
	return instance;
}

bool GameInstance::Initialize(
	const char* windowTitle,
	Vector2 position,
	Vector2 size,
	InitFrameworkTag initTag,
	GameFrameMode mode)
{
	MultiExtend::Trace::Start();

	GameObject::Initialize(windowTitle, position, size, initTag, mode);

	Actor* spriteStaticActor = MultiExtend::CreateActor<Actor>(Get().m_GameStat);
	MultiExtend::SpriteSDLComponent* spriteStatic = new MultiExtend::SpriteSDLComponent(Get().m_GameStat, Get().m_renderer, "../assets/Ship01.png");
	spriteStatic->SetSize(Vector2{ 64, 29 });
	spriteStatic->SetPositionRelative(Vector3{ spriteStatic->GetSize()[x] / 2, spriteStatic->GetSize()[y] / 2,0 });
	spriteStaticActor->AddChildActorComponent(spriteStatic);

	Actor* spriteAnimateActor = MultiExtend::CreateActor<Actor>(Get().m_GameStat);
	std::vector<const char*> textures =
	{
		"../assets/Ship01.png",
		"../assets/Ship02.png",
		"../assets/Ship03.png",
		"../assets/Ship04.png"
	};
	MultiExtend::AnimateSpriteSDLComponent* spriteAnimate = new MultiExtend::AnimateSpriteSDLComponent(10, Get().m_GameStat, Get().m_renderer, textures);
	spriteAnimate->SetSize(Vector2{ 64, 29 });
	spriteAnimate->SetPositionRelative(Vector3{ spriteAnimate->GetSize()[x] / 2, spriteAnimate->GetSize()[y] / 2, 0 });
	spriteAnimateActor->AddChildActorComponent(spriteAnimate);
	spriteAnimateActor->SetPositionRelative(Vector3{ spriteStatic->GetSize()[x],0,0 });

	Actor* spriteScrollActor = MultiExtend::CreateActor<Actor>(Get().m_GameStat);
	std::vector<const char*> scrolltextures =
	{
		"../assets/Farback01.png",
		"../assets/Farback02.png"
	};
	MultiExtend::ScrollSpriteSDLComponent* scrollSprite = new MultiExtend::ScrollSpriteSDLComponent(Get().m_GameStat, Get().m_renderer, scrolltextures);
	scrollSprite->SetRenderSize(Vector2{ 512,32 });
	scrollSprite->SetSourceSizeScale(Vector3{ .2f, .2f, 1 });
	scrollSprite->SetScrollSpeed(80);
	scrollSprite->SetOffset(300);
	spriteScrollActor->AddChildActorComponent(scrollSprite);
	spriteScrollActor->SetPositionRelative(Vector3{ spriteAnimateActor->GetPositionAbsolute()[x] + spriteAnimate->GetSize()[x], 0, 0 });

	Get().m_GameActor->AddChildActor(spriteStaticActor);
	Get().m_GameActor->AddChildActor(spriteAnimateActor);
	Get().m_GameActor->AddChildActor(spriteScrollActor);

	Actor* starScrollActor = MultiExtend::CreateActor<Actor>(Get().m_GameStat);
	std::vector<const char*> starScrolltextures =
	{
		"../assets/Stars.png",
	};
	MultiExtend::ScrollSpriteSDLComponent* starScrollSprite = new MultiExtend::ScrollSpriteSDLComponent(Get().m_GameStat, Get().m_renderer, starScrolltextures);
	starScrollSprite->SetRenderSize(Vector2{ 512, 32 });
	starScrollSprite->SetSourceSizeScale(Vector3{ .3f, .3f, 1 });
	starScrollSprite->SetScrollSpeed(40);
	starScrollSprite->SetOffset(0);
	starScrollActor->AddChildActorComponent(starScrollSprite);
	starScrollActor->SetPositionRelative(Vector3{ spriteAnimateActor->GetPositionAbsolute()[x] + spriteAnimate->GetSize()[x],0, 0 });

	Actor* tileMapActor = MultiExtend::CreateActor<Actor>(Get().m_GameStat);

	const char* tileMapPath = "../assets/Tiles.png";
	Texture* tileMap = MultiExtend::LoadTexture(Get().m_GameStat, Get().m_renderer, tileMapPath);

	MultiExtend::TileMapSDLComponent* tileMapA = new MultiExtend::TileMapSDLComponent(Get().m_renderer, tileMap);
	tileMapA->SetSrcPosition(Vector2{ 97,1 });
	tileMapA->SetSrcSize(Vector2{ 30, 30 });
	tileMapA->SetDstSize(Vector2{ 32, 32 });

	MultiExtend::TileMapSDLComponent* tileMapB = new MultiExtend::TileMapSDLComponent(Get().m_renderer, tileMap);
	tileMapB->SetSrcPosition(Vector2{ 65, 1 });
	tileMapB->SetSrcSize(Vector2{ 30, 30 });
	tileMapB->SetDstSize(Vector2{ 32, 32 });
	tileMapB->SetPositionRelative(Vector3{ 33,0,0 });

	tileMapActor->AddChildActorComponent(tileMapA);
	tileMapActor->AddChildActorComponent(tileMapB);
	tileMapActor->SetPositionRelative(Vector3{ starScrollActor->GetPositionAbsolute()[x] + starScrollSprite->GetRenderSize()[x], 0, 0 });

	std::vector<const char*> ActorStepTextures =
	{
		"../assets/Character01.png",
		"../assets/Character02.png",
		"../assets/Character03.png",
		"../assets/Character04.png",
		"../assets/Character05.png",
		"../assets/Character06.png"
	};
	DynamicAnimateSpriteSDLUnit* AnimateUnit_ActorStep = new DynamicAnimateSpriteSDLUnit(Get().m_GameStat, Get().m_renderer, ActorStepTextures, "Step", LOOP, nullptr);

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
	DynamicAnimateSpriteSDLUnit* AnimateUnit_ActorJump = new DynamicAnimateSpriteSDLUnit(Get().m_GameStat, Get().m_renderer, JUMPtextures, "Jump", ONCE, nullptr);

	std::vector<const char*> Punchtextures =
	{
		"../assets/Character16.png",
		"../assets/Character17.png",
		"../assets/Character18.png"
	};
	DynamicAnimateSpriteSDLUnit* AnimateUnit_ActorPunch = new DynamicAnimateSpriteSDLUnit(Get().m_GameStat, Get().m_renderer, Punchtextures, "Punch", ONCE, nullptr);

	std::vector<DynamicAnimateSpriteSDLUnit*> dynamicAnimateSpriteUnits =
	{
		AnimateUnit_ActorStep,
		AnimateUnit_ActorJump,
		AnimateUnit_ActorPunch
	};
	DynamicAnimateSpriteSDLComponent* PlayerBaseComp = new DynamicAnimateSpriteSDLComponent(Get().m_renderer, dynamicAnimateSpriteUnits);

	PlayerBaseComp->SetDefaultDynamicSpriteUnit("Step");
	PlayerBaseComp->SetCurrentDynamicSpriteUnit("Step");
	PlayerBaseComp->SetAnimFPS(12);
	PlayerBaseComp->SetSize(Vector2{ 64, 64 });
	PlayerBaseComp->SetTag("PlayerBaseComp");

	Actor* PlayerBaseActor = MultiExtend::CreateActor<Actor>(Get().m_GameStat, "PlayerBase");
	PlayerBaseActor->AddChildActorComponent(PlayerBaseComp);
	PlayerBaseActor->SetPositionRelative(Vector3{ PlayerBaseComp->GetSize()[x] / 2, spriteStatic->GetSize()[y] + PlayerBaseComp->GetSize()[y] / 2,0 });


	Get().m_GameActor->AddChildActor(spriteStaticActor);
	Get().m_GameActor->AddChildActor(spriteAnimateActor);
	Get().m_GameActor->AddChildActor(spriteScrollActor);
	Get().m_GameActor->AddChildActor(starScrollActor);
	Get().m_GameActor->AddChildActor(tileMapActor);
	Get().m_GameActor->AddChildActor(PlayerBaseActor);

	return true;
};

void GameInstance::CustomProcessInput(const Uint8* state)
{
	MULTIEXTEND_TIMER_TRACE_TAG(CustomProcessInput);

	if (state[SDL_SCANCODE_ESCAPE])
	{
		m_isRunning = false;
	}

	if (state[SDL_SCANCODE_SPACE])
	{
		// player base
		Actor* PlayerBase = Get().m_GameActor->GetChildActor("PlayerBase");

		if (PlayerBase)
		{
			MultiExtend::Component* BaseComp = PlayerBase->GetChildActorComponent("PlayerBaseComp");
			MultiExtend::DynamicAnimateSpriteSDLComponent* PlayerBaseComp = static_cast<MultiExtend::DynamicAnimateSpriteSDLComponent*>(BaseComp);

			if (PlayerBaseComp && PlayerBaseComp->bCanChangeCurrentUnit())
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
			MultiExtend::Component* BaseComp = PlayerBase->GetChildActorComponent("PlayerBaseComp");
			MultiExtend::DynamicAnimateSpriteSDLComponent* PlayerBaseComp = static_cast<MultiExtend::DynamicAnimateSpriteSDLComponent*>(BaseComp);

			if (PlayerBaseComp && PlayerBaseComp->bCanChangeCurrentUnit())
			{
				PlayerBaseComp->SetCurrentDynamicSpriteUnit("Punch");
			}
		};
	}
};

int main(int argc, char** argv)
{
	{
		if (GameInstance::Get().Initialize())
		{
			GameInstance::Get().Runloop();
		};

		GameInstance::Get().ShutDown();
	}
	return 0;
}