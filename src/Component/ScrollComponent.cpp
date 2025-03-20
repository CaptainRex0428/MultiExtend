#include "Component/ScrollComponent.h"
#include "MultiExtend.h"

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
	m_renderSize(renderSize),
	m_scrollDirect(direct),
	bReverse(false),
	m_headTextureIdx(0),
	m_headTextureOffset(0)
{
	m_Textures.clear();
	m_Textures.emplace_back(m_Texture);

	auto iter = texturefilepaths.begin() + 1;
	for (; iter != texturefilepaths.end(); ++iter)
	{
		Texture* texture = MultiExtend::LoadTexture(gameState, renderer, *iter);
		m_Textures.emplace_back(texture);
	};
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
	m_renderSize(renderSize),
	m_scrollDirect(direct),
	bReverse(false),
	m_headTextureIdx(0),
	m_headTextureOffset(0)
{
	m_Textures = textures;
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
	ScaleSourceSize(SourceSize);

	m_headTextureOffset += offset;

	// 处理正向溢出
	while (m_headTextureOffset > (m_scrollDirect == SCROLL_HORIZON ? SourceSize.x : SourceSize.y)) {
		m_headTextureOffset -= (m_scrollDirect == SCROLL_HORIZON ? SourceSize.x : SourceSize.y);
		m_headTextureIdx = (m_headTextureIdx + 1) % m_Textures.size();
		QueryTexture(m_Textures[m_headTextureIdx], &SourceSize);
		ScaleSourceSize(SourceSize);
	}

	// 处理反向溢出（新增负偏移处理）
	while (m_headTextureOffset < 0) {
		m_headTextureIdx = (m_headTextureIdx - 1 + m_Textures.size()) % m_Textures.size();
		QueryTexture(m_Textures[m_headTextureIdx], &SourceSize);
		ScaleSourceSize(SourceSize);
		m_headTextureOffset += (m_scrollDirect == SCROLL_HORIZON ? SourceSize.x : SourceSize.y);
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

	// 根据反向标志决定绘制递进方向
	int step = bReverse ? -1 : 1;

	while (drawDistance < maxRenderSize)
	{

		MultiExtend::TextureRelocator srcLocator, dstLocator;

		Vector2 SourceSize, SourceSizeScaled;

		QueryTexture(m_Textures[drawIdx], &SourceSize);
		SourceSizeScaled = SourceSize;
		ScaleSourceSize(SourceSizeScaled);

		int renderTag = 1;

		// --- 计算裁剪参数（横向示例）---
		float remainingSpace = maxRenderSize - drawDistance;
		float srcClipStart = bReverse ?
			(SourceSizeScaled.x - m_headTextureOffset) :
			m_headTextureOffset;

		srcLocator.offset.x = m_scrollDirect == SCROLL_HORIZON ?
			(bReverse ? (SourceSize.x - m_headTextureOffset / scale.x) : m_headTextureOffset / scale.x) : 0;
		srcLocator.size.x = m_scrollDirect == SCROLL_HORIZON ?
			(remainingSpace / scale.x) : SourceSize.x;

		dstLocator.offset.x = pos.x + (m_scrollDirect == SCROLL_HORIZON ? drawDistance : 0);
		dstLocator.size.x = m_scrollDirect == SCROLL_HORIZON ?
			remainingSpace : m_renderSize.x * scale.x;
		
		
		// --- 类似逻辑处理垂直方向 ---
		srcLocator.offset.y = m_scrollDirect == SCROLL_HORIZON ?
			0 : (bReverse ? (SourceSize.y - m_headTextureOffset / scale.y) : m_headTextureOffset / scale.y);
		srcLocator.size.y = m_scrollDirect == SCROLL_HORIZON ?
			SourceSize.y : (remainingSpace / scale.y);

		dstLocator.offset.y = pos.y + (m_scrollDirect == SCROLL_HORIZON ?  0 : drawDistance );
		dstLocator.size.y = m_scrollDirect == SCROLL_HORIZON ?
			m_renderSize.y * scale.y : remainingSpace;

		MultiExtend::RenderTexture(m_Renderer, m_Textures[drawIdx], &srcLocator, &dstLocator);


		// 更新索引和距离（考虑反向）
		drawIdx = (drawIdx + step + m_Textures.size()) % m_Textures.size();
		drawDistance += (m_scrollDirect == SCROLL_HORIZON) ?
			dstLocator.size.x : dstLocator.size.y;

	}

	ActorComponent::Draw();

}

void MultiExtend::ScrollSpriteComponent::SetScrollTextures(const std::vector<Texture*>& textures)
{
	m_Textures = textures;
}

void MultiExtend::ScrollSpriteComponent::SetRenderSize(const Vector2 size)
{
	m_renderSize = size;
}

MULTIEXTEND_API Vector2 MultiExtend::ScrollSpriteComponent::GetRenderSize()
{
	return m_renderSize;
}

MULTIEXTEND_API void MultiExtend::ScrollSpriteComponent::SetSourceSizeScale(const Vector3 size)
{
	m_sourceSizeScale = size;
}

MULTIEXTEND_API Vector3 MultiExtend::ScrollSpriteComponent::GetSourceSizeScale()
{
	return m_sourceSizeScale;
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

void MultiExtend::ScrollSpriteComponent::ScaleSourceSize(Vector2& sourceSize)
{
	Vector3 absoluteScale = GetScaleAbsolute();
	Vector3 scaleResult = m_sourceSizeScale * absoluteScale;

	if (m_scrollDirect == SCROLL_HORIZON)
	{
		if (sourceSize.y * scaleResult.y < m_renderSize.y)
		{
			scaleResult.y = m_renderSize.y / sourceSize.y;
		}

		sourceSize *= scaleResult;

		return;
	}

	if (m_scrollDirect == SCROLL_VERTICAL)
	{
		if (sourceSize.x * scaleResult.x < m_renderSize.x)
		{
			scaleResult.x = m_renderSize.x / sourceSize.x;
		}

		sourceSize *= scaleResult;

		return;
	}
}
