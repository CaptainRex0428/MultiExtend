#include <iostream>
#include <fstream>
#include <Windows.h>

#include "MultiExtend.h"
#include "Math/Math.h"
#include "Math/Color.h"
#include "Config/Game.h"
#include "Actor/Actor.h"
#include "Component/Sprite/SpriteComponent.h"
#include "Component/Sprite/AnimateSpriteComponent.h"
#include "Component/Sprite/ScrollComponent.h"
#include "Component/Sprite/TileMapComponent.h"
#include "Component/Sprite/DynamicAnimateSpriteComponent.h"

#include "glew.h"


GameFrameMode frameMode = CUSTOM;
const int limitFPS = 60;
const int limitFrameTime = 1000 / limitFPS;

class GameObject
{
public:
	GameObject(GameObject&) = delete;

	static GameObject& Get()
	{
		static GameObject instance;
		return instance;
	};

	static bool Initialize()
	{
		MultiExtend::Trace::Start();

		if (!MultiExtend::Init())
		{
			return false;
		};

		Get().m_window = SDL_CreateWindow("OpenGL Test",
			100, 100,
			720, 462, SDL_WINDOW_OPENGL);

		if (!Get().m_window)
		{
			SDL_Log("SDL create window error:%s", SDL_GetError());
			return false;
		}

		void * context = SDL_GL_CreateContext(Get().m_window);
		
		Get().m_renderer = new RendererOpenGL(context);

		glewExperimental = GL_TRUE;
		
		if(glewInit() != GLEW_OK)
		{
			SDL_Log("Failed to initialize GLEW.");
			
			return false;
		}

		glGetError();

		// Get().m_renderer = new MultiExtend::RendererSDL(renderer);
		Get().m_isRunning = true;

		return true;
	};

	static void Runloop()
	{
		while (Get().m_isRunning)
		{

			{
				MULTIEXTEND_TIMER_TRACE_TAG(ProcessLoop);

				Get().ProcessInput();
				Get().UpdateGame();
				Get().GenerateOuput();
			}

			
		}
	};

	static void ShutDown()
	{

		MultiExtend::Trace::Stop();

		Get().m_isRunning = false;

		SDL_GL_DeleteContext(Get().m_renderer->GetRenderer());
	};

private:
	GameObject()
		:m_window(nullptr), m_renderer(nullptr), m_isRunning(false),
		m_tickcount(0), m_delta(0)
	{
		m_GameStat = MultiExtend::CreateGameStat<GameStat>();
		m_GameActor = MultiExtend::CreateActor<Actor>(m_GameStat);
	};

	virtual ~GameObject()
	{
		

	};

	void ProcessInput()
	{
		MULTIEXTEND_TIMER_TRACE_TAG(ProcessInput);

	};

	void UpdateGame()
	{
		MULTIEXTEND_TIMER_TRACE_TAG(UpdateGame);

		static auto last_time = MULTIEXTEND_CLOCK_HIGHRES::now();

		auto current_time = MULTIEXTEND_CLOCK_HIGHRES::now();

		m_delta = std::chrono::duration<float>(current_time - last_time).count();

		last_time = current_time;

		m_GameActor->Update(m_delta);
	};

	void GenerateOuput()
	{
		MULTIEXTEND_TIMER_TRACE_TAG(GenerateOuput);

		glClearColor(0.86f, 0.86f, 0.86f, 0.86f);
		glClear(GL_COLOR_BUFFER_BIT);

		SDL_GL_SwapWindow(Get().m_window);
	};

private:

	bool m_isRunning;
	SDL_Window* m_window;
	Renderer* m_renderer;

	long long int m_tickcount;
	float m_delta;

	GameStat* m_GameStat;
	Actor* m_GameActor;
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