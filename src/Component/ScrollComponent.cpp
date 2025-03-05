#include "Component/ScrollComponent.h"

MultiExtend::ScrollComponent::ScrollComponent(
	GameState* gameState,
	Renderer* renderer,
	Vector2 screensize,
	float scrollspeed,
	int updateorder = DEFAULT_UPDATEORDER,
	const char* tag = BaseSpriteComponentTypeName,
	const char* texturefilepath = nullptr,
	Vector3 position = Vector3(0.0f, 0.0f, 0.0f),
	Vector3 scale = Vector3(1.0f, 1.0f, 1.0f),
	Vector3 rotation = Vector3(0.0f, 0.0f, 0.0f))
	:
	SpriteComponent(gameState,renderer, texturefilepath, tag, position, scale, rotation, updateorder),
	m_ScrollSpeed(scrollspeed),
	m_ScreenSize(screensize),
	m_ScrollWidth(0)
{
}

MultiExtend::ScrollComponent::~ScrollComponent()
{
}

void MultiExtend::ScrollComponent::Update(float delta)
{
	SpriteComponent::Update(delta);

	for (auto& scrollTexture : m_ScrollTextures)
	{
		scrollTexture.offset.x += m_ScrollSpeed * delta;

		int w, h = 0;
		SDL_QueryTexture(scrollTexture.texture, nullptr, nullptr, &w, &h);

		if (scrollTexture.offset.x < -w)
		{

			scrollTexture.offset.x += m_ScrollWidth;
		}
	}
}

void MultiExtend::ScrollComponent::Draw()
{
	for (auto& scrollTexture : m_ScrollTextures)
	{
		SDL_Rect rc;
		SDL_Rect t;

		int w, h = 0;
		SDL_QueryTexture(scrollTexture.texture, nullptr, nullptr, &w, &h);

		rc.w = (int)(w);
		rc.h = (int)(h);
		rc.x = (int)(scrollTexture.offset.x);
		rc.y = 0;

		t.w = (int)(m_ScreenSize.x);
		t.h = (int)(m_ScreenSize.y);
		t.x = (int)(scrollTexture.offset.x);
		t.y = 0;

		SDL_RenderCopy(m_renderer, scrollTexture.texture, nullptr, &rc);
	}

	ActorComponent::Draw();

}

void MultiExtend::ScrollComponent::SetBGTextures(const std::vector<Texture*>& textures)
{
	int count = 0;

	float offsetcount = 0;

	for (auto tex : textures)
	{
		TextureRelocator temp;

		temp.texture = tex;
		temp.offset.x = offsetcount;
		temp.offset.y = 0;

		m_ScrollTextures.emplace_back(temp);

		int w, h = 0;
		SDL_QueryTexture(tex, nullptr, nullptr, &w, &h);

		offsetcount += w;

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
