#include "Component/ScrollComponent.h"
#include "MultiExtend.h"
#include "Math/Math.h"

MultiExtend::ScrollSpriteComponent::ScrollSpriteComponent(
	GameState* gameState,
	Renderer* renderer,
	float scrollspeed,
	std::vector<const char*> texturefilepaths,
	const char* tag,
	int updateorder,
	ScrollDirect direct,
	Vector3 sourceSizeScale,
	Vector3 position, Vector3 scale,
	Vector3 rotation, Vector2 renderSize)
	:
	SpriteComponent(gameState, renderer, texturefilepaths[0], tag, position, scale, rotation, Vector2(0, 0), updateorder),
	m_ScrollSpeed(scrollspeed),
	m_sourceSizeScale(sourceSizeScale),
	m_limitedSourceSizeScale(sourceSizeScale),
	m_renderSize(renderSize),
	m_scrollDirect(direct),
	bReverse(false),
	m_headTextureIdx(0),
	m_headTextureOffsetAfterScale(0)
{
	m_Textures.clear();
	m_Textures.emplace_back(m_Texture);

	auto iter = texturefilepaths.begin() + 1;
	for (; iter != texturefilepaths.end(); ++iter)
	{
		Texture* texture = MultiExtend::LoadTexture(gameState, renderer, *iter);
		m_Textures.emplace_back(texture);
	};

	RefreshLimitedSizeScale();
}

MultiExtend::ScrollSpriteComponent::ScrollSpriteComponent(
	GameState* gameState,
	Renderer* renderer,
	float scrollspeed,
	std::vector<Texture*> textures,
	const char* tag,
	int updateorder,
	ScrollDirect direct,
	Vector3 sourceSizeScale,
	Vector3 position, Vector3 scale,
	Vector3 rotation, Vector2 renderSize)
	:
	SpriteComponent(gameState, renderer, textures[0], tag, position, scale, rotation, Vector2(0, 0), updateorder),
	m_ScrollSpeed(scrollspeed),
	m_sourceSizeScale(sourceSizeScale),
	m_limitedSourceSizeScale(sourceSizeScale),
	m_renderSize(renderSize),
	m_scrollDirect(direct),
	bReverse(false),
	m_headTextureIdx(0),
	m_headTextureOffsetAfterScale(0)
{
	m_Textures = textures;

	RefreshLimitedSizeScale();
}

MultiExtend::ScrollSpriteComponent::~ScrollSpriteComponent()
{
	for (Texture* texture : m_Textures)
	{
		delete texture;
	}

	m_Textures.clear();
}

void MultiExtend::ScrollSpriteComponent::Update(float delta)
{
	SpriteComponent::Update(delta);

	float direction = bReverse ? -1.0f : 1.0f;
	float offset = direction * m_ScrollSpeed * delta;

	Vector2 SourceSize;
	QueryTexture(m_Textures[m_headTextureIdx], &SourceSize);
	Vector2 SourceSizeScaled = SourceSize * m_limitedSourceSizeScale;

	m_headTextureOffsetAfterScale += offset;

	// 处理正向溢出
	while (m_headTextureOffsetAfterScale > (m_scrollDirect == SCROLL_HORIZON ? SourceSizeScaled.x : SourceSizeScaled.y)) 
	{
		m_headTextureOffsetAfterScale -= (m_scrollDirect == SCROLL_HORIZON ? SourceSizeScaled.x : SourceSizeScaled.y);
		m_headTextureIdx = (m_headTextureIdx + 1) % m_Textures.size();
		QueryTexture(m_Textures[m_headTextureIdx], &SourceSize);
		SourceSizeScaled = SourceSize * m_limitedSourceSizeScale;
	}

	// 处理反向溢出
	while (m_headTextureOffsetAfterScale < 0) {

		m_headTextureIdx = (m_headTextureIdx - 1 + m_Textures.size()) % m_Textures.size();

		QueryTexture(m_Textures[m_headTextureIdx], &SourceSize);
		SourceSizeScaled = SourceSize * m_limitedSourceSizeScale;

		m_headTextureOffsetAfterScale += (m_scrollDirect == SCROLL_HORIZON ? SourceSizeScaled.x : SourceSizeScaled.y);
	}
}

void MultiExtend::ScrollSpriteComponent::Draw()
{
	float drawDistance = 0;
	int drawIdx = m_headTextureIdx;

	Vector3 pos = GetPositionAbsolute();
	Vector3 scale = GetScaleAbsolute();
	float maxRenderSize = (m_scrollDirect == SCROLL_HORIZON) ?
		(m_renderSize.x * scale.x) : (m_renderSize.y * scale.y);

	while (drawDistance < maxRenderSize)
	{
		MultiExtend::TextureRelocator srcLocator, dstLocator;

		Vector2 SourceSize, SourceSizeScaled;
		QueryTexture(m_Textures[drawIdx], &SourceSize);
		SourceSizeScaled = SourceSize * m_limitedSourceSizeScale;

		float remainingSpace = maxRenderSize - drawDistance;

		int drawTag = 1;

		if (drawDistance == 0)
		{
			drawTag = 0;
		}
		else if (remainingSpace < (m_scrollDirect == SCROLL_HORIZON ? SourceSizeScaled.x : SourceSizeScaled.y))
		{
			drawTag = 2;
		}

		switch (drawTag)
		{
		case(0):
		{
			
			srcLocator.offset.x = m_scrollDirect == SCROLL_HORIZON ? (m_headTextureOffsetAfterScale / m_limitedSourceSizeScale.x) : 0;
			srcLocator.offset.y = m_scrollDirect == SCROLL_HORIZON ? 0 : (m_headTextureOffsetAfterScale / m_limitedSourceSizeScale.y);

			dstLocator.offset.x = pos.x;
			dstLocator.offset.y = pos.y;

			float dstRemain = m_scrollDirect == SCROLL_HORIZON ? SourceSizeScaled.x - m_headTextureOffsetAfterScale : SourceSizeScaled.y - m_headTextureOffsetAfterScale;
			float maxRenderSize = m_scrollDirect == SCROLL_HORIZON ? m_renderSize.x * scale.x : m_renderSize.y * scale.y;
			Math::limit_max(dstRemain, maxRenderSize);

			dstLocator.size.x = m_scrollDirect == SCROLL_HORIZON ? dstRemain : (m_renderSize.x * scale.x);
			dstLocator.size.y = m_scrollDirect == SCROLL_HORIZON ? (m_renderSize.y * scale.y) : dstRemain;

			float srcRemain = m_scrollDirect == SCROLL_HORIZON ? dstRemain / m_limitedSourceSizeScale.x : dstRemain / m_limitedSourceSizeScale.y;

			srcLocator.size.x = m_scrollDirect == SCROLL_HORIZON ? srcRemain : (m_renderSize.x * scale.x / m_limitedSourceSizeScale.x);
			srcLocator.size.y = m_scrollDirect == SCROLL_HORIZON ? (m_renderSize.y * scale.y / m_limitedSourceSizeScale.y) : srcRemain;
			

			break;
		}
		case(2):
		{
			srcLocator.offset.x = 0;
			srcLocator.offset.y = 0;
			srcLocator.size.x = m_scrollDirect == SCROLL_HORIZON ? (remainingSpace * SourceSize.x / SourceSizeScaled.x) : (m_renderSize.x * scale.x / m_limitedSourceSizeScale.x);
			srcLocator.size.y = m_scrollDirect == SCROLL_HORIZON ? (m_renderSize.y * scale.y / m_limitedSourceSizeScale.y) : (remainingSpace * SourceSize.y / SourceSizeScaled.y);

			dstLocator.offset.x = m_scrollDirect == SCROLL_HORIZON ? (pos.x + drawDistance) : pos.x;
			dstLocator.offset.y = m_scrollDirect == SCROLL_HORIZON ? pos.y : (pos.y + drawDistance);
			dstLocator.size.x = m_scrollDirect == SCROLL_HORIZON ? remainingSpace : (m_renderSize.x * scale.x);
			dstLocator.size.y = m_scrollDirect == SCROLL_HORIZON ? (m_renderSize.y * scale.y) : remainingSpace;
			
			break;
		}
		case(1):
		default:
		{
			srcLocator.offset.x = 0;
			srcLocator.offset.y = 0;
			srcLocator.size.x = m_scrollDirect == SCROLL_HORIZON ? SourceSize.x : (m_renderSize.x * scale.x / m_limitedSourceSizeScale.x);
			srcLocator.size.y = m_scrollDirect == SCROLL_HORIZON ? (m_renderSize.y * scale.y / m_limitedSourceSizeScale.y) : SourceSize.y;

			dstLocator.offset.x = m_scrollDirect == SCROLL_HORIZON ? (pos.x + drawDistance) : pos.x;
			dstLocator.offset.y = m_scrollDirect == SCROLL_HORIZON ? pos.y : (pos.y + drawDistance);
			dstLocator.size.x = m_scrollDirect == SCROLL_HORIZON ? SourceSizeScaled.x : (m_renderSize.x * scale.x);
			dstLocator.size.y = m_scrollDirect == SCROLL_HORIZON ? (m_renderSize.y * scale.y) : SourceSizeScaled.y;
			break;
		}
		}

		drawDistance += m_scrollDirect == SCROLL_HORIZON ? dstLocator.size.x : dstLocator.size.y;

		MultiExtend::RenderTexture(m_Renderer, m_Textures[drawIdx], &srcLocator, &dstLocator);

		drawIdx = (drawIdx + 1) % m_Textures.size();
	}

	ActorComponent::Draw();

}

void MultiExtend::ScrollSpriteComponent::SetScrollTextures(const std::vector<Texture*>& textures)
{
	if(m_Textures.empty()) return;

	m_Textures = textures;

	RefreshLimitedSizeScale();
}

void MultiExtend::ScrollSpriteComponent::SetRenderSize(const Vector2 size)
{
	m_renderSize = size;

	RefreshLimitedSizeScale();
}

MULTIEXTEND_API Vector2 MultiExtend::ScrollSpriteComponent::GetRenderSize()
{
	return m_renderSize;
}

MULTIEXTEND_API void MultiExtend::ScrollSpriteComponent::SetSourceSizeScale(const Vector3 size)
{
	m_sourceSizeScale = size;

	RefreshLimitedSizeScale();
}

MULTIEXTEND_API Vector3 MultiExtend::ScrollSpriteComponent::GetSourceSizeScale()
{
	return m_sourceSizeScale;
}

MULTIEXTEND_API Vector3 MultiExtend::ScrollSpriteComponent::GetLimitedSourceSizeScale()
{
	return m_limitedSourceSizeScale;
}

void MultiExtend::ScrollSpriteComponent::SetScrollSpeed(float speed)
{
	m_ScrollSpeed = speed;
}

float MultiExtend::ScrollSpriteComponent::GetScrollSpeed() const
{
	return m_ScrollSpeed;
}

MULTIEXTEND_API void MultiExtend::ScrollSpriteComponent::ReverseScroll()
{
	this->bReverse = this->bReverse ? false : true;
}

void MultiExtend::ScrollSpriteComponent::RefreshLimitedSizeScale()
{
	auto iter = m_Textures.begin();
	
	m_limitedSourceSizeScale = m_sourceSizeScale;

	Vector3 scaleGlobal = GetScaleAbsolute();

	for (;iter != m_Textures.end(); ++iter)
	{
		Vector2 SourceSize;
		QueryTexture(*iter, &SourceSize);

		if(m_scrollDirect == SCROLL_HORIZON && (m_renderSize.y * scaleGlobal.y) > (SourceSize.y * m_sourceSizeScale.y))
		{
			
			float scaleY = m_renderSize.y * scaleGlobal.y / SourceSize.y;

			if (scaleY > m_limitedSourceSizeScale.y)
			{
				m_limitedSourceSizeScale.y = scaleY;
			}
			
		}

		if (m_scrollDirect == SCROLL_VERTICAL && (m_renderSize.x * scaleGlobal.x) > (SourceSize.x * m_sourceSizeScale.x))
		{

			float scaleX = m_renderSize.x * scaleGlobal.x / SourceSize.x;

			if (scaleX > m_limitedSourceSizeScale.x)
			{
				m_limitedSourceSizeScale.x = scaleX;
			}

		}
	}
}
