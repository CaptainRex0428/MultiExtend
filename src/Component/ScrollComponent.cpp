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
	SpriteComponent(gameState, renderer, texturefilepaths[0], tag, position, scale, rotation, Vector2(0,0), updateorder),
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

	float offset = m_ScrollSpeed * delta;

	Vector2 SourceSize;
	QueryTexture(m_Textures[m_headTextureIdx], &SourceSize);

	m_headTextureOffset += offset;
	
	while(m_headTextureOffset > (m_scrollDirect==SCROLL_HORIZON ? SourceSize.x : SourceSize.y))
	{
		m_headTextureOffset -= (m_scrollDirect == SCROLL_HORIZON ? SourceSize.x : SourceSize.y);
		m_headTextureIdx += 1;

		if(m_headTextureIdx >= m_Textures.size())
		{
			m_headTextureIdx = 0;
		}

		QueryTexture(m_Textures[m_headTextureIdx], &SourceSize);
	}
}

void MultiExtend::ScrollSpriteComponent::Draw()
{
	float drawDistance = 0;

	int drawIdx = m_headTextureIdx;

	while (drawDistance < (m_scrollDirect == SCROLL_HORIZON ? m_renderSize.x : m_renderSize.y))
	{
		
		MultiExtend::TextureRelocator srcLocator;
		MultiExtend::TextureRelocator dstLocator;

		Vector2 SourceSize;
		QueryTexture(m_Textures[drawIdx], &SourceSize);

		dstLocator.size.x = m_scrollDirect == SCROLL_HORIZON? :m_renderSize.x;
		dstLocator.size.y = m_scrollDirect == SCROLL_HORIZON? m_renderSize.y:;
		dstLocator.offset.x = ;
		dstLocator.offset.y = ;

		srcLocator.size.x = m_scrollDirect == SCROLL_HORIZON ? : m_renderSize.x;
		srcLocator.size.y = m_scrollDirect == SCROLL_HORIZON ? m_renderSize.y : ;
		srcLocator.offset.x =;
		srcLocator.offset.y =;

		MultiExtend::RenderTexture(m_Renderer,m_Textures[drawIdx],&srcLocator,&dstLocator);

		drawIdx++;

		if(drawIdx >= m_Textures.size())
		{
			drawIdx = 0;
		}

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
