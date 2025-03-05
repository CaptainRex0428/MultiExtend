#pragma once

#include <vector>

#include "SDL.h"

#include "Component/Component.h"
#include "Actor/Actor.h"
#include "Texture/Texture.h"
#include "Renderer/Renderer.h"
#include "Debug/Message/Message.h"
#include "Debug/Message/MessageMicro.h"

namespace MultiExtend
{

	class GameState : public Object
	{
	public:
		MULTIEXTEND_API GameState();
		MULTIEXTEND_API virtual ~GameState() = default;

		MULTIEXTEND_API void AddActor(Actor* actor);
		MULTIEXTEND_API void RemoveActor(Actor* actor);
		
		MULTIEXTEND_API void AddTexture(Texture* texture);
		MULTIEXTEND_API void RemoveTexture(Texture* texture);


		MULTIEXTEND_API void Update(float delta);
		
		// MULTIEXTEND_API void Draw();

		
	private:
		std::vector<Actor*> m_actors;
		std::vector<Texture*> m_textures;
	};

}