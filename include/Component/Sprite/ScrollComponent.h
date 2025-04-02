#pragma once

#include "MultiExtendAPI.h"
#include "Component/Sprite/SpriteComponent.h"
#include "Texture/Texture.h"

namespace MultiExtend
{
	enum ScrollDirect
	{
		SCROLL_HORIZON = 0b00000001,
		SCROLL_VERTICAL = 0b00000010
	};

	class ScrollSpriteComponent : public SpriteComponent
	{
	public:
		MULTIEXTEND_API ScrollSpriteComponent(
			GameStat* GameStat,
			Renderer* renderer,
			std::vector<const char*> texturefilepaths,
			float scrollspeed = 88,
			float offset = 0,
			const char* tag = BaseSpriteComponentTypeName,
			int updateorder = DEFAULT_UPDATEORDER,
			ScrollDirect direct = SCROLL_HORIZON,
			Vector3 sourceSizeScale = Vector3{1.0f, 1.0f, 1.0f},
			Vector3 position = Vector3{ 0.0f, 0.0f, 0.0f },
			Vector3 scale = Vector3{ 1.0f, 1.0f, 1.0f },
			Vector3 rotation = Vector3{ 0.0f, 0.0f, 0.0f },
			Vector2 renderSize = Vector2{256,32});

		MULTIEXTEND_API ScrollSpriteComponent(
			Renderer* renderer,
			std::vector<Texture*> textures,
			float scrollspeed = 88,
			float offset = 0,
			const char* tag = BaseSpriteComponentTypeName,
			int updateorder = DEFAULT_UPDATEORDER,
			ScrollDirect direct = SCROLL_HORIZON,
			Vector3 sourceSizeScale = Vector3{ 1.0f, 1.0f, 1.0f },
			Vector3 postion = Vector3{ 0.0f, 0.0f, 0.0f },
			Vector3 scale = Vector3{ 1.0f, 1.0f, 1.0f },
			Vector3 rotation = Vector3{ 0.0f, 0.0f, 0.0f },
			Vector2 renderSize = Vector2{ 256,32 });

		MULTIEXTEND_API virtual ~ScrollSpriteComponent();

		MULTIEXTEND_API virtual void Update(float delta) override;
		MULTIEXTEND_API virtual void Draw() override;

		MULTIEXTEND_API virtual void SetScrollTextures(const std::vector<Texture*>& textures);

		MULTIEXTEND_API virtual void SetRenderSize(const Vector2 size);
		MULTIEXTEND_API virtual Vector2 GetRenderSize();

		MULTIEXTEND_API virtual void SetSourceSizeScale(const Vector3 size);
		MULTIEXTEND_API virtual Vector3 GetSourceSizeScale();
		MULTIEXTEND_API virtual Vector3 GetLimitedSourceSizeScale();

		MULTIEXTEND_API virtual void SetOffset(float offset);
		MULTIEXTEND_API virtual const float & GetOffset();
		MULTIEXTEND_API virtual const float & GetLimitedOffset();

		MULTIEXTEND_API void SetScrollSpeed(float speed);
		MULTIEXTEND_API float GetScrollSpeed() const;

		MULTIEXTEND_API void ReverseScroll();

	protected:
		void RefreshLimit();
		void RefreshLimitedSizeScale();
		void RefreshLimitedOffset();

		std::vector<Texture *> m_Textures;
		Vector3 m_sourceSizeScale;
		Vector3 m_limitedSourceSizeScale;

		Vector2 m_renderSize;
		float m_ScrollSpeed;

		int m_headTextureIdx;
		float m_headTextureOffsetAfterScale;
		
		ScrollDirect m_scrollDirect;
		bool bReverse;

		float m_offset;
		float m_limitOffset;
	};
}