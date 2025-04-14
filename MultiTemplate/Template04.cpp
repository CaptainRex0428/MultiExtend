#include "MultiExtend.h"

#include "SDL.h"

#include "Math/Vertex.h"

#include "Actor/Actor.h"

#include "Math/Vertex.h"
#include "Shader/Shader.h"


class GameInstance
{
public:
	GameInstance(GameInstance&) = delete;

	static GameInstance& Get()
	{
		static GameInstance instance;
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
		
		if(glfwInit() != GLFW_TRUE || glewInit() != GLEW_OK)
		{
			SDL_Log("Failed to initialize GLEW && GLFW.");
			
			return false;
		}

		glGetError();

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);

		const unsigned char * version = glGetString(GL_VERSION);
		MULTIEXTEND_MESSAGE_CLIENT_DEBUG("OpenGL Version :{}", reinterpret_cast<const char*>(version));

		Get().m_isRunning = true;

		Get().m_shader = CreateShaderGL(Get().m_GameStat,"../shader/basic.glsl");

		std::vector<MultiExtend::Vertex<float, 8>> vertices =
		{
			{{ -.6f, -.4f, 0.f, 1.f},{0.0f,0.5f},{1.f, 0.f, 0.f, 1.f},{0.f, 0.f, 1.f, 1.f}},
			{{  .6f, -.4f, 0.f, 1.f},{0.0f,0.5f} ,{ 0.f, 1.f, 0.f, 1.f },{ 0.f, 0.f, 1.f, 1.f }},
			{{  0.f,  .6f, 0.f, 1.f},{0.0f,0.5f} ,{ 0.f, 0.f, 1.f, 1.f },{ 0.f, 0.f, 1.f, 1.f }}
		};

		std::vector<unsigned int> indices;

		Get().m_buffer = new MultiExtend::VertexBuffer<float, 8>(vertices, indices);
		Get().m_buffer->ConfigureAttributes(Get().m_shader, DefaultFloatVertexAttributes);
		
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

		// SDL_GL_DeleteContext(Get().m_renderer->GetRenderer());

		delete Get().m_GameStat;
		delete Get().m_GameActor;

		glfwTerminate();
	};

private:
	GameInstance()
		:m_window(nullptr), m_renderer(nullptr), m_isRunning(false),
		m_tickcount(0), m_delta(0)
	{
		m_GameStat = MultiExtend::CreateGameStat<GameStat>();
		m_GameActor = MultiExtend::CreateActor<Actor>(m_GameStat);
	};

	virtual ~GameInstance()
	{
		
	};

	void ProcessInput()
	{
		MULTIEXTEND_TIMER_TRACE_TAG(ProcessInput);
		
		/* Poll for and process events */
		glfwPollEvents();

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

		int width, height;
		SDL_GL_GetDrawableSize(m_window, &width, &height);
		glViewport(0, 0, width, height);

		const float ratio = width / (float)height;

		/* Render here */
		glViewport(0, 0, width, height);

		Color<float,8> c((int)30,30,30,30);
		glClearColor(c[r], c[g], c[b], c[a]);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		DrawVertices(Get().m_buffer, Get().m_shader, GL_TRIANGLES, ratio);

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

	ShaderGL * m_shader;

	VertexBuffer<float, 8> * m_buffer;
};

int main(int argc, char** argv)
{
	{
		if (GameInstance::Initialize())
		{
			GameInstance::Runloop();
		};

		GameInstance::ShutDown();
	}
	return 0;
}