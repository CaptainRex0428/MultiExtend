#include "Component/Sprite/SpriteSDLComponent.h"

#include "MultiExtend.h"

#include "SDL.h"

MultiExtend::SpriteSDLComponent::SpriteSDLComponent(
	GameStat* gameStat, 
	SDL_Renderer* renderer, 
	const char* texturefilepath, 
	const char* tag, 
	Vector3 postion, 
	Vector3 scale, 
	Vector3 rotation, 
	Vector2 size,
	int updateorder)
	:MultiExtend::ActorComponent(tag, postion, scale, rotation, updateorder),
	m_Texture(nullptr),
	m_TextureRender_h((int)size[y]),
	m_TextureRender_w((int)size[x]),
	m_Renderer(renderer)
{
	if(texturefilepath)
	{
		m_Texture = MultiExtend::LoadTexture(gameStat,renderer,texturefilepath);
	}
}

MultiExtend::SpriteSDLComponent::SpriteSDLComponent(
	SDL_Renderer* renderer, 
	Texture* texture, 
	const char* tag, 
	Vector3 postion, 
	Vector3 scale, 
	Vector3 rotation, 
	Vector2 size,
	int updateorder)
	:MultiExtend::ActorComponent(tag, postion, scale, rotation, updateorder),
	m_Texture(texture),
	m_TextureRender_h((int)size[y]),
	m_TextureRender_w((int)size[x]),
	m_Renderer(renderer)
{
}

MultiExtend::SpriteSDLComponent::~SpriteSDLComponent()
{
}

void MultiExtend::SpriteSDLComponent::CustomUpdate(float delta)
{
	MULTIEXTEND_TIMER_TRACE_TAG(CustomUpdateSpriteComponent);

	ActorComponent::CustomUpdate(delta);
}

void MultiExtend::SpriteSDLComponent::SetTexture(Texture* texture)
{
	if(m_Texture)
	{
		m_Texture = texture;
	}

	// Vector2 sourceSize;
	// QueryTexture(texture, &sourceSize);

}

MULTIEXTEND_API void MultiExtend::SpriteSDLComponent::SetSize(Vector2 size)
{
	m_TextureRender_w = (int)size[x];
	m_TextureRender_h = (int)size[y];
}

MULTIEXTEND_API Vector2 MultiExtend::SpriteSDLComponent::GetSize()
{
	return Vector2{(float)m_TextureRender_w,(float)m_TextureRender_h};
}

void MultiExtend::SpriteSDLComponent::CustomDraw(const Vector2& size)
{
	MULTIEXTEND_TIMER_TRACE_TAG(DrawSpriteComponent);

	const Vector3 scaleResult = GetScaleAbsolute();
	const Vector3 posResult = GetPositionAbsolute();

	if(m_Texture)
	{
		TextureRelocator renderSize;

		// offset pivot to image center
		renderSize.size[x] = m_TextureRender_w * scaleResult[x];
		renderSize.size[y] = m_TextureRender_h * scaleResult[y];
		renderSize.offset[x] = posResult[x] - renderSize.size[x] / 2;
		renderSize.offset[y] = posResult[y] - renderSize.size[y] / 2;

		MultiExtend::RenderTexture(m_Renderer, m_Texture,
			nullptr, &renderSize,
			GetRotationAbsolute()[z]);
	}

	ActorComponent::CustomDraw(size);
}