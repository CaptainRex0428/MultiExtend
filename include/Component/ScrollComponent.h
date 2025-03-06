#pragma once

#include "MultiExtendAPI.h"
#include "Component/SpriteComponent.h"
#include "Texture/Texture.h"
#include "Object/GameState.h"

namespace MultiExtend
{
	struct TextureScroll
	{
		Texture * texture;
		TextureRelocator locator;
	};

	enum ScrollDirect
	{
		SCROLL_NONE = 0b00000001,
		SCROLL_HORIZON = 0b00000010,
		SCROLL_VERTICAL = 0b00000100
	};

	class ScrollComponent : public SpriteComponent
	{
	public:
		MULTIEXTEND_API ScrollComponent(
			GameState* gameState,
			Renderer* renderer,
			Vector2 screensize,
			float scrollspeed,
			int updateorder = DEFAULT_UPDATEORDER,
			const char* tag = BaseSpriteComponentTypeName,
			const char* texturefilepath = nullptr,
			Vector3 position = Vector3(0.0f, 0.0f, 0.0f),
			Vector3 scale = Vector3(1.0f, 1.0f, 1.0f),
			Vector3 rotation = Vector3(0.0f, 0.0f, 0.0f));

		MULTIEXTEND_API virtual ~ScrollComponent();

		MULTIEXTEND_API virtual void Update(float delta) override;
		MULTIEXTEND_API virtual void Draw() override;

		MULTIEXTEND_API virtual void SetScrollTextures(const std::vector<Texture*>& textures);

		MULTIEXTEND_API virtual void SetScreenSize(const Vector2 size);

		MULTIEXTEND_API void SetScrollSpeed(float speed);
		MULTIEXTEND_API float GetScrollSpeed() const;

	private:
		std::vector<TextureScroll *> m_ScrollTextures;
		Vector2 m_ScreenSize;
		
		float m_ScrollSpeed;
		float m_ScrollWidth;
	};
}