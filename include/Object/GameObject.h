#pragma once

#include "SDL.h"

#include "MultiExtend.h"
#include "MultiExtendAPI.h"

#include "Object/Object.h"
#include "Object/GameStat.h"

#include "Actor/Actor.h"

#include "Config/Game.h"

namespace MultiExtend
{
	const int limitFPS = 60;
	const int limitFrameTime = 1000 / limitFPS;

	enum InitFrameworkTag : int
	{
		NONE = 0b00000000,
		SDL = MULTIEXTEND_BIT(0),
		OpenGL = MULTIEXTEND_BIT(1),
		DirectX = MULTIEXTEND_BIT(2),
		ALL = 0b11111111
	};

	class GameObject : public Object
	{
	public:
		MULTIEXTEND_API GameObject(GameObject&) = delete;

		MULTIEXTEND_API static GameObject& Get();

		MULTIEXTEND_API virtual bool Initialize(
			const char * windowTitle = "DefaultWindow", 
			Vector2 position = {100,100},
			Vector2 size = {1280,720},
			int initTag = (int)InitFrameworkTag::ALL, 
			GameFrameMode mode = CUSTOM);

		MULTIEXTEND_API virtual void Runloop();

		MULTIEXTEND_API virtual void ShutDown();

	protected:

		MULTIEXTEND_API GameObject();
		MULTIEXTEND_API virtual ~GameObject();

		MULTIEXTEND_API void ProcessInput();
		MULTIEXTEND_API virtual void CustomProcessInput(const Uint8* state);

		MULTIEXTEND_API void UpdateGame();
		MULTIEXTEND_API virtual void CustomUpdateGame();

		MULTIEXTEND_API void GenerateOuput();
		MULTIEXTEND_API virtual void CustomGenerateOuput(const float& ratio);

	protected:

		bool m_isRunning;

		SDL_Window* m_window;
		SDL_Renderer* m_renderer;
		void * m_GLContext;

		long long int m_tickcount;
		float m_delta;

		GameStat* m_GameStat;
		Actor* m_GameActor;

		int m_Initialized;
		GameFrameMode m_FrameMode;

		Vector2 m_InitSize;
	};
}