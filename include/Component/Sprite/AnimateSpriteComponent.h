#pragma once

#include <vector>

#include "MultiExtendAPI.h"
#include "SpriteComponent.h"

#include "AnimateSpriteComponentConfig.h"

namespace MultiExtend
{
	class AnimateSpriteComponent: public SpriteComponent
	{
	public:
		MULTIEXTEND_API AnimateSpriteComponent(
			float FPS,
			GameStat* gameStat,
			Renderer* renderer,
			std::vector<const char *> textureFilePaths,
			const char* tag = BaseAnimSpriteComponentTypeName,
			Vector3 position = Vector3{0.0f, 0.0f, 0.0f},
			Vector3 scale = Vector3{1.0f, 1.0f, 1.0f},
			Vector3 rotation = Vector3{0.0f, 0.0f, 0.0f},
			Vector2 size = Vector2{32,32},
			int updateorder = DEFAULT_UPDATEORDER);

		MULTIEXTEND_API AnimateSpriteComponent(
			float FPS,
			Renderer* renderer,
			std::vector<Texture*> textures,
			const char* tag = BaseAnimSpriteComponentTypeName,
			Vector3 position = Vector3{ 0.0f, 0.0f, 0.0f },
			Vector3 scale = Vector3{ 1.0f, 1.0f, 1.0f },
			Vector3 rotation = Vector3{ 0.0f, 0.0f, 0.0f },
			Vector2 size = Vector2{ 32,32 },
			int updateorder = DEFAULT_UPDATEORDER);

		MULTIEXTEND_API virtual ~AnimateSpriteComponent();

		MULTIEXTEND_API virtual void Update(float delta) override;

		MULTIEXTEND_API void SetAnimTextures(std::vector<Texture*>& animateTextures);

		MULTIEXTEND_API float GetAnimFPS() const;
		MULTIEXTEND_API void SetAnimFPS(float fps);

	private:
		MULTIEXTEND_API void SetCurrentFrame(float frame);

	private:
		std::vector<Texture*> m_animateTextures;

		float m_FPS;
		float m_currentFrame;
	};
}