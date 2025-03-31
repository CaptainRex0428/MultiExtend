#pragma once

//------------------ Dependencies -----------------
#include "SDL_image.h"

//------------------ Base tool ---------------
#include "System/File/File.h"
#include "System/Directory/Directory.h"
#include "System/Operator.h"
#include "System/Hash/HashGenerator.h"

#include "Time/Clock/Clock.h"
#include "Time/Clock/GlobalClock.h"
#include "Time/Timer/Timer.h"

#include "Debug/Message/Message.h"
#include "Debug/Trace/Trace.h"
#include "Debug/Log/Log.h"

#include "Object/GameStat.h"
#include "Texture/Texture.h"
#include "Renderer/Renderer.h"

#include "MultiExtendDebug.h"

//---------------------------------------------

//----------------- Micro Define --------------
#include "MultiExtendMicro.h"
#include "Debug/Message/MessageMicro.h"
#include "Time/Clock/ClockMicro.h"
#include "Time/Clock/GlobalClockMicro.h"
#include "System/File/FileMicro.h"
#include "System/Directory/DirectoryMicro.h"
#include "Math/MathMicro.h"
#include "Time/Timer/TimerMicro.h"
#include "Debug/Trace/TraceMicro.h"
//---------------------------------------------

namespace MultiExtend
{
	enum InitFrameworkTag: int
	{
		SDL = 0b00000001,
		openGL = 0b00000010,
		ALL = 0b11111111
	};

	MULTIEXTEND_API int Init(int inttag = ALL);

	MULTIEXTEND_API Texture* LoadTexture(GameStat* GameStat, Renderer* renderer, const char* filepath);

	MULTIEXTEND_API Texture* LoadTexture(GameStat* GameStat, SDL_Renderer* renderer, const char* filepath);

	template <typename T, typename... Args>
	inline T* CreateActor(GameStat * GameStat,Args&&... args)
	{
		T* ActorCreate = new T(std::forward<Args>(args)...);

		if (!dynamic_cast<Actor*>(ActorCreate))
		{
			MULTIEXTEND_MESSAGE_CLIENT_WARN("Faild to create a actor. Class Error.");
			delete ActorCreate;
			return nullptr;
		};

		GameStat->AddActor(ActorCreate);
		return ActorCreate;
	};

	template <typename T, typename... Args>
	inline T* CreateComponent(GameStat * GameStat, Args&&... args)
	{
		T* ComponentCreate = new T(std::forward<Args>(args)...);

		if (!dynamic_cast<Component*>(ComponentCreate))
		{
			MULTIEXTEND_MESSAGE_CLIENT_WARN("Faild to create a component. Class Error.");
			delete ComponentCreate;
			return nullptr;
		};

		return ComponentCreate;
	};

	template <typename T, typename... Args>
	inline T* CreateGameStat(Args&&... args)
	{
		T* GameStatCreate = new T(std::forward<Args>(args)...);

		if (!dynamic_cast<GameStat*>(GameStatCreate))
		{
			MULTIEXTEND_MESSAGE_CLIENT_WARN("Faild to create a GameStat. Class Error.");
			delete GameStatCreate;
			return nullptr;
		};

		return GameStatCreate;
	};

	MULTIEXTEND_API void ClearRenderer(Renderer * renderer);

	MULTIEXTEND_API void RenderPresent(Renderer* renderer);
}

using namespace MultiExtend;