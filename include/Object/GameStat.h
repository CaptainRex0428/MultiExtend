#pragma once

#include <vector>

#include "GameStatConfig.h"
#include "API/IUpdate.h"

namespace MultiExtend
{
	class Actor;
	class Texture;

	class GameStat : public Object, public IUpdate
	{
	public:
		MULTIEXTEND_API GameStat();
		MULTIEXTEND_API virtual ~GameStat() = default;

		MULTIEXTEND_API void AddActor(Actor* actor);
		MULTIEXTEND_API void RemoveActor(Actor* actor);
		
		MULTIEXTEND_API void AddTexture(Texture* texture);
		MULTIEXTEND_API void RemoveTexture(Texture* texture);


		MULTIEXTEND_API void Update(float delta) override;
		MULTIEXTEND_API virtual void CustomUpdate(float delta) override;
		
		// MULTIEXTEND_API void Draw();

		
	private:
		std::vector<Actor*> m_actors;
		std::vector<Texture*> m_textures;
	};

}