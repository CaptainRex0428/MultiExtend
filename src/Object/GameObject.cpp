#include "Object/GameObject.h"

#include "MultiExtend.h"

#include "SDL.h"
#include "SDL_image.h"

#include "glew.h"
#include "GLFW/glfw3.h"

#include "Math/Color.h"
#include "Math/Vertex.h"

bool MultiExtend::GameObject::Initialize(
	const char* windowTitle,
	Vector2 position,
	Vector2 size,
	int initTag,
	GameFrameMode mode)
{
	if (!MultiExtend::Init())
	{
		return false;
	};

	m_FrameMode = mode;

	m_InitSize = size;

	if (initTag & InitFrameworkTag::SDL)
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

		if (!(initTag & InitFrameworkTag::OpenGL))
		{
			m_window = SDL_CreateWindow(windowTitle,
				position[x], position[y],
				size[x], size[y], 0);

			if (!m_window)
			{
				MULTIEXTEND_MESSAGE_CLIENT_CRITICAL("SDL create window error:{}", SDL_GetError());
				return false;
			}

			m_renderer = SDL_CreateRenderer(m_window, -1,
				SDL_RENDERER_ACCELERATED | (m_FrameMode == VSYNC ? SDL_RENDERER_PRESENTVSYNC : 0));

			if (!m_renderer)
			{
				MULTIEXTEND_MESSAGE_CLIENT_CRITICAL("SDL create renderer error:{}", SDL_GetError());
				return false;
			}

			Color<float, 8> c((int)30, 30, 30, 30);
			SDL_SetRenderDrawColor(m_renderer, c[r], c[g], c[b], c[a]);
		}

		m_Initialized = m_Initialized | (int)InitFrameworkTag::SDL;
	}

	if (initTag & InitFrameworkTag::OpenGL)
	{
		MULTIEXTEND_TIMER_TRACE_TAG(InitOpenGL);

		// use the core OpenGL Profile
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

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

		m_window = SDL_CreateWindow(windowTitle,
			position[x], position[y],
			size[x], size[y], SDL_WINDOW_OPENGL);

		if (!m_window)
		{
			MULTIEXTEND_MESSAGE_CLIENT_CRITICAL("SDL create window error:{}", SDL_GetError());
			return false;
		}

		m_GLContext = SDL_GL_CreateContext(m_window);

		glewExperimental = GL_TRUE;

		if (glfwInit() != GLFW_TRUE || glewInit() != GLEW_OK)
		{
			MULTIEXTEND_MESSAGE_CLIENT_CRITICAL("Failed to initialize GLEW && GLFW.");

			return false;
		}

		glGetError();

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);

		const unsigned char* version = glGetString(GL_VERSION);
		MULTIEXTEND_MESSAGE_CLIENT_DEBUG("OpenGL Version :{}", reinterpret_cast<const char*>(version));

		Color<float, 8> c((int)30, 30, 30, 30);
		glClearColor(c[r], c[g], c[b], c[a]);

		m_Initialized = m_Initialized | (int)InitFrameworkTag::OpenGL;
	}

	if (initTag & InitFrameworkTag::DirectX)
	{
		MULTIEXTEND_TIMER_TRACE_TAG(InitDirectX);

		m_Initialized = m_Initialized | (int)InitFrameworkTag::DirectX;
	}

	m_isRunning = true;
}

void MultiExtend::GameObject::Runloop()
{
	while (m_isRunning)
	{
		// 返回自 SDL 库初始化（通过 SDL_Init()）以来经过的毫秒数（ms）
		Uint32 frame_start = SDL_GetTicks();

		{
			MULTIEXTEND_TIMER_TRACE_TAG(ProcessLoop);

			ProcessInput();
			UpdateGame();
			GenerateOuput();

			switch (m_FrameMode) 
			{
			case CUSTOM:
			{
				Uint32 frame_time = SDL_GetTicks() - frame_start;
				if (frame_time < limitFrameTime) {
					SDL_Delay(limitFrameTime - frame_time);
				}
				break;
			}
			case VSYNC:
			case UNLIMITED:
			default:
				break;
			}
		}

		// 统计帧率
		Uint32 frameCost = SDL_GetTicks() - frame_start;
		// MULTIEXTEND_MESSAGE_CLIENT_DEBUG("FPS:{0:.2f}", 1000.0f / frameCost);
	}
}

void MultiExtend::GameObject::ShutDown()
{
	m_isRunning = false;
	
	IMG_Quit();

	if(m_Initialized & InitFrameworkTag::OpenGL)
	{
		SDL_GL_DeleteContext(m_GLContext);
		glfwTerminate();
	}

	SDL_DestroyWindow(m_window);
	SDL_DestroyRenderer(m_renderer);

	SDL_Quit();

	// delete m_GameStat;
	// delete m_GameActor;

	MultiExtend::Trace::Stop();
}

MultiExtend::GameObject::GameObject()
	:m_window(nullptr), m_renderer(nullptr), m_isRunning(false),
	m_tickcount(0), m_delta(0), m_GLContext(nullptr), m_Initialized(0), m_FrameMode(CUSTOM),
	m_InitSize({0,0})
{
	m_GameStat = MultiExtend::CreateGameStat<GameStat>();
	m_GameActor = MultiExtend::CreateActor<Actor>(m_GameStat);
}

MultiExtend::GameObject::~GameObject()
{
	IMG_Quit();

	if (m_isRunning)
	{
		ShutDown();
		m_isRunning = false;
	}

	if (m_window)
	{
		SDL_DestroyWindow(m_window);
	}

	if (m_renderer)
	{
		SDL_DestroyRenderer(m_renderer);
	}

	if (m_GLContext)
	{
		SDL_GL_DeleteContext(m_GLContext);
	}
}

void MultiExtend::GameObject::ProcessInput()
{
	MULTIEXTEND_TIMER_TRACE_TAG(ProcessInput);

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

	CustomProcessInput(state);
}

void MultiExtend::GameObject::CustomProcessInput(const Uint8* state)
{}

void MultiExtend::GameObject::UpdateGame()
{
	MULTIEXTEND_TIMER_TRACE_TAG(UpdateGame);

	static auto last_time = MULTIEXTEND_CLOCK_HIGHRES::now();
	auto current_time = MULTIEXTEND_CLOCK_HIGHRES::now();
	m_delta = std::chrono::duration<float>(current_time - last_time).count();
	last_time = current_time;

	m_GameActor->Update(m_delta);

	CustomUpdateGame();
}

void MultiExtend::GameObject::CustomUpdateGame()
{
}

void MultiExtend::GameObject::GenerateOuput()
{
	MULTIEXTEND_TIMER_TRACE_TAG(GenerateOuput);

	int width, height;
	float ratio;

	width = m_InitSize[x];
	height = m_InitSize[y];

	if (m_Initialized & InitFrameworkTag::OpenGL) 
	{
		int width, height;
		float ratio;
		SDL_GL_GetDrawableSize(m_window, &width, &height);

		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		ratio = width / (float)height;

		m_GameActor->Draw(ratio);
		CustomGenerateOuput(ratio);

		SDL_GL_SwapWindow(m_window);
	}
	else if (m_Initialized & InitFrameworkTag::SDL) 
	{

		SDL_RenderClear(m_renderer);

		m_GameActor->Draw(0);
		CustomGenerateOuput(0);

		SDL_RenderPresent(m_renderer);
	}
}

void MultiExtend::GameObject::CustomGenerateOuput(const float& ratio)
{
	
}
