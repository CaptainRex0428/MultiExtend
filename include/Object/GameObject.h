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
		SDL = 0,
		OpenGL,
		DirectX
	};

	class GameObject : public Object
	{
	public:
		
		MULTIEXTEND_API GameObject();
		MULTIEXTEND_API virtual ~GameObject();

		MULTIEXTEND_API GameObject(GameObject&) = delete;

		MULTIEXTEND_API virtual bool Initialize(
			const char * windowTitle = "DefaultWindow", 
			Vector2 position = {100,100},
			Vector2 size = {1280,720},
			InitFrameworkTag initTag = SDL,
			GameFrameMode mode = CUSTOM);

		MULTIEXTEND_API virtual void Runloop();

		MULTIEXTEND_API virtual void ShutDown();

	protected:

		

		MULTIEXTEND_API void ProcessInput();
		MULTIEXTEND_API virtual void CustomProcessInput(const Uint8* state);

		MULTIEXTEND_API void UpdateGame();
		MULTIEXTEND_API virtual void CustomUpdateGame(float m_delta);

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

		InitFrameworkTag m_InitTag;
		GameFrameMode m_FrameMode;

		Vector2 m_InitSize;
	};
}