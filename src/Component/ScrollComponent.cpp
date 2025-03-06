#include "Component/ScrollComponent.h"

MultiExtend::ScrollComponent::ScrollComponent(
	GameState* gameState,
	Renderer* renderer,
	Vector2 screensize,
	float scrollspeed,
	int updateorder,
	const char* tag ,
	const char* texturefilepath,
	Vector3 position,
	Vector3 scale,
	Vector3 rotation)
	:
	SpriteComponent(gameState,renderer, texturefilepath, tag, position, scale, rotation, updateorder),
	m_ScrollSpeed(scrollspeed),
	m_ScreenSize(screensize),
	m_ScrollWidth(0)
{
}

MultiExtend::ScrollComponent::~ScrollComponent()
{
	for (TextureScroll* scroll : m_ScrollTextures) 
	{
		delete scroll;
	}

	m_ScrollTextures.clear();
}

void MultiExtend::ScrollComponent::Update(float delta)
{
	SpriteComponent::Update(delta);

	for (TextureScroll * scrollTexture : m_ScrollTextures)
	{
		scrollTexture->locator.offset.x += m_ScrollSpeed * delta;

		Vector2 sourceSize;
		QueryTexture(scrollTexture->texture,&sourceSize);

		if (scrollTexture->locator.offset.x < -sourceSize.x)
		{

			scrollTexture->locator.offset.x += m_ScrollWidth;
		}
	}
}

void MultiExtend::ScrollComponent::Draw()
{
	for (TextureScroll * scrollTexture : m_ScrollTextures)
	{
		Vector2 sourceSize;
		QueryTexture(scrollTexture->texture, & sourceSize);

		TextureRelocator dst;		

		dst.size.x = m_ScreenSize.x;
		dst.size.y = m_ScreenSize.y;
		dst.offset.x = scrollTexture->locator.offset.x;
		dst.offset.y = 0;

		RenderTexture(m_Renderer,scrollTexture->texture,nullptr,&dst);
	}

	ActorComponent::Draw();

}

void MultiExtend::ScrollComponent::SetScrollTextures(const std::vector<Texture*>& textures)
{
	int count = 0;

	float offsetcount = 0;

	for (Texture * tex : textures)
	{
		TextureScroll * temp = new TextureScroll();

		temp->texture = tex;
		temp->locator.offset.x = offsetcount;
		temp->locator.offset.y = 0;

		m_ScrollTextures.emplace_back(temp);

		Vector2 sourceSize;
		QueryTexture(tex,&sourceSize);

		offsetcount += sourceSize.x;

		count++;
	}

	m_ScrollWidth = offsetcount;
}

void MultiExtend::ScrollComponent::SetScreenSize(const Vector2 size)
{
	m_ScreenSize = size;
}

void MultiExtend::ScrollComponent::SetScrollSpeed(float speed)
{
	m_ScrollSpeed = speed;
}

float MultiExtend::ScrollComponent::GetScrollSpeed() const
{
	return m_ScrollSpeed;
}
