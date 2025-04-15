#include "MultiExtendAPI.h"
#include "MultiExtend.h"

#include "Object/Object.h"
#include "Object/GameStat.h"

#define COLORBUFFERSIZE 8

struct SDL_Renderer;

namespace MultiExtend
{
	class TextureSDL;
	class Renderer;
	class GameStat;
	class Component;

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

	template <typename T, typename... Args>
	inline T* CreateActor(GameStat* GameStat, Args&&... args)
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
	inline T* CreateComponent(GameStat* GameStat, Args&&... args)
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

	namespace SDLRender
	{
		MULTIEXTEND_API void ClearRenderer(SDL_Renderer* renderer);

		MULTIEXTEND_API void RenderPresent(SDL_Renderer* renderer);
	}

}