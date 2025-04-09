#include "MultiExtend.h"

#include "SDL.h"

#include "Math/Vertex.h"
#include "Renderer/Renderer.h"

#include "Actor/Actor.h"

#include <glew.h>
#include <GLFW/glfw3.h>


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
		
		glewExperimental = GL_TRUE;
		
		if(glewInit() != GLEW_OK)
		{
			SDL_Log("Failed to initialize GLEW.");
			
			return false;
		}

		glGetError();

		const unsigned char * version = glGetString(GL_VERSION);
		MULTIEXTEND_MESSAGE_CLIENT_DEBUG("OpenGL Version :{}", reinterpret_cast<const char*>(version));

		Get().m_renderer = new RendererOpenGL(context);
		Get().m_isRunning = true;

		MultiExtend::VertexGL<float,7> v;
		MULTIEXTEND_MESSAGE_CLIENT_DEBUG("VertexGL Class size :{}", sizeof(MultiExtend::VertexGL<float, 7>));
		MULTIEXTEND_MESSAGE_CLIENT_DEBUG("VertexGL size :{}", sizeof(v));
		MULTIEXTEND_MESSAGE_CLIENT_DEBUG("VertexGL size :{}", MultiExtend::VertexGL<float, 7>::stride());

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