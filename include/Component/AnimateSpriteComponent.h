#pragma once

#include <vector>

#include "MultiExtendAPI.h"
#include "SpriteComponent.h"

#define BaseAnimSpriteComponentTypeName "BaseAnimSpriteComponent"

namespace MultiExtend
{
	class AnimateSpriteComponent: public SpriteComponent
	{
	public:
		MULTIEXTEND_API AnimateSpriteComponent(
			Renderer* renderer,
			const char* canva_path,
			const char* tag = BaseAnimSpriteComponentTypeName,
			Vector3 postion = Vector3(0.0f, 0.0f, 0.0f),
			Vector3 scale = Vector3(1.0f, 1.0f, 1.0f),
			Vector3 rotation = Vector3(0.0f, 0.0f, 0.0f),
			int updateorder = DEFAULT_UPDATEORDER);
		virtual ~AnimateSpriteComponent();

		virtual void Update(float delta) override;

		void SetAnimTextures(const std::vector<Texture*>& animateTextures);

		float GetAnimFPS() const;
		void SetAnimFPS(float fps);

	private:
		std::vector<Texture*> m_animateTextures;

		float m_FPS;
		float m_currentFrame;
	};
}