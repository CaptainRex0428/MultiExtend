#pragma once

#include "MultiExtendAPI.h"
#include "Component/ActorComponent.h"

#include "Renderer/Renderer.h"
#include "Texture/Texture.h"
#include "Object/GameStat.h"

#include "SpriteComponentConfig.h"

#define BaseSpriteComponentTypeName "BaseSpriteComponent"

namespace MultiExtend
{
	class SpriteComponent : public ActorComponent
	{
	public:
		MULTIEXTEND_API SpriteComponent(
			GameStat * gameState,
			Renderer * renderer,
			const char* texturefilepath = nullptr,
			const char* tag = BaseSpriteComponentTypeName,
			Vector3 postion = Vector3{0.0f, 0.0f, 0.0f},
			Vector3 scale = Vector3{1.0f, 1.0f, 1.0f},
			Vector3 rotation = Vector3{0.0f, 0.0f, 0.0f},
			Vector2 size = Vector2{32, 32},
			int updateorder = DEFAULT_UPDATEORDER);

		MULTIEXTEND_API SpriteComponent(
			Renderer* renderer,
			Texture* texture = nullptr,
			const char* tag = BaseSpriteComponentTypeName,
			Vector3 postion = Vector3{ 0.0f, 0.0f, 0.0f },
			Vector3 scale = Vector3{ 1.0f, 1.0f, 1.0f },
			Vector3 rotation = Vector3{ 0.0f, 0.0f, 0.0f },
			Vector2 size = Vector2{ 32, 32 },
			int updateorder = DEFAULT_UPDATEORDER);

		MULTIEXTEND_API virtual ~SpriteComponent();

		MULTIEXTEND_API virtual void Update(float delta) override;
		MULTIEXTEND_API virtual void Draw() override;

		MULTIEXTEND_API virtual void SetTexture(Texture * texture);

		MULTIEXTEND_API virtual void SetSize(Vector2 size);
		MULTIEXTEND_API virtual Vector2 GetSize();
		

	protected:
		Texture * m_Texture;
		Renderer * m_Renderer;
		int m_TextureRender_w;
		int m_TextureRender_h;
	};
}