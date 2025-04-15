#pragma once

#include "MultiExtendAPI.h"
#include "Component/ActorComponent.h"

#include "Texture/Texture.h"
#include "Object/GameStat.h"

#include "SpriteSDLComponentConfig.h"

namespace MultiExtend
{
	class SpriteSDLComponent : public ActorComponent
	{
	public:
		MULTIEXTEND_API SpriteSDLComponent(
			GameStat * gameStat,
			SDL_Renderer * renderer,
			const char* texturefilepath = nullptr,
			const char* tag = BaseSpriteSDLComponentTypeName,
			Vector3 postion = Vector3{0.0f, 0.0f, 0.0f},
			Vector3 scale = Vector3{1.0f, 1.0f, 1.0f},
			Vector3 rotation = Vector3{0.0f, 0.0f, 0.0f},
			Vector2 size = Vector2{32, 32},
			int updateorder = DEFAULT_UPDATEORDER);

		MULTIEXTEND_API SpriteSDLComponent(
			SDL_Renderer * renderer,
			Texture* texture = nullptr,
			const char* tag = BaseSpriteSDLComponentTypeName,
			Vector3 postion = Vector3{ 0.0f, 0.0f, 0.0f },
			Vector3 scale = Vector3{ 1.0f, 1.0f, 1.0f },
			Vector3 rotation = Vector3{ 0.0f, 0.0f, 0.0f },
			Vector2 size = Vector2{ 32, 32 },
			int updateorder = DEFAULT_UPDATEORDER);

		MULTIEXTEND_API virtual ~SpriteSDLComponent();

		MULTIEXTEND_API virtual void CustomUpdate(float delta) override;
		MULTIEXTEND_API virtual void CustomDraw(const Vector2& size) override;

		MULTIEXTEND_API virtual void SetTexture(Texture * texture);

		MULTIEXTEND_API virtual void SetSize(Vector2 size);
		MULTIEXTEND_API virtual Vector2 GetSize();
		

	protected:
		Texture * m_Texture;
		SDL_Renderer * m_Renderer;
		int m_TextureRender_w;
		int m_TextureRender_h;
	};
}