#pragma once

#include <vector>

#include "Component/Component.h"
#include "Actor/Actor.h"
#include "Texture/Texture.h"
#include "Renderer/Renderer.h"
#include "SDL.h"

namespace MultiExtend
{

	class GameObject : public Object
	{
	public:
		MULTIEXTEND_API GameObject(GameObject&) = delete;

		MULTIEXTEND_API static void AddActor(Actor* actor);
		MULTIEXTEND_API static void RemoveActor(Actor* actor);

		MULTIEXTEND_API static bool Update(float delta);
		MULTIEXTEND_API static void Draw();

		MULTIEXTEND_API static Texture * LoadTexture(Renderer * renderer, const char* filepath);

		MULTIEXTEND_API static Texture* LoadTexture(SDL_Renderer* renderer, const char* filepath);

	private:
		MULTIEXTEND_API GameObject();
		MULTIEXTEND_API virtual ~GameObject() = default;

		MULTIEXTEND_API static GameObject* Get();

		std::vector<Actor*> m_actors;
		std::vector<Texture*> m_textures;
	};

}