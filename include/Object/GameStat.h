#pragma once

#include <vector>

#include "GameStatConfig.h"
#include "Object/Object.h"
#include "API/IUpdate.h"

namespace MultiExtend
{
	class Actor;
	class Texture;
	class ShaderGL;

	class GameStat : public Object, public IUpdate
	{
	public:
		MULTIEXTEND_API GameStat();
		MULTIEXTEND_API virtual ~GameStat();

		MULTIEXTEND_API void AddActor(Actor* actor);
		MULTIEXTEND_API void RemoveActor(Actor* actor);
		
		MULTIEXTEND_API void AddTexture(Texture* texture);
		MULTIEXTEND_API void RemoveTexture(Texture* texture);

		MULTIEXTEND_API void AddShaderGL(ShaderGL* shader);
		MULTIEXTEND_API void RemoveShaderGL(ShaderGL* shader);

		MULTIEXTEND_API void Update(float delta) override;
		MULTIEXTEND_API virtual void CustomUpdate(float delta) override;


		
	private:
		std::vector<Actor*> m_actors;
		std::vector<Texture*> m_textures;
		std::vector<ShaderGL*> m_ShaderGLs;
	};

}