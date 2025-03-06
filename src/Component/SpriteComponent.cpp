#include "Component/SpriteComponent.h"

#include "MultiExtend.h"


#include "SDL.h"

MultiExtend::SpriteComponent::SpriteComponent(
	GameState* gameState, 
	Renderer* renderer, 
	const char* texturefilepath, 
	const char* tag, 
	Vector3 postion, 
	Vector3 scale, 
	Vector3 rotation, 
	int updateorder)
	:MultiExtend::ActorComponent(tag, postion, scale, rotation, updateorder),
	m_Texture(nullptr),
	m_TextureRender_h(0),
	m_TextureRender_w(0),
	m_Renderer(renderer)
{
}

MultiExtend::SpriteComponent::~SpriteComponent()
{
}

void MultiExtend::SpriteComponent::Update(float delta)
{
	ActorComponent::Update(delta);
}

void MultiExtend::SpriteComponent::SetSingleTexture(Texture* texture)
{
	m_Texture = texture;

	Vector2 sourceSize;
	QueryTexture(texture, &sourceSize);

}

void MultiExtend::SpriteComponent::Draw()
{
	const Vector3 scaleResult = GetScaleResult();
	const Vector3 posResult = GetPositionResult();

	TextureRelocator renderSize;

	renderSize.size.x = m_TextureRender_w * scaleResult.x;
	renderSize.size.y = m_TextureRender_h * scaleResult.y;
	renderSize.offset.x = posResult.x - renderSize.size.x / 2;
	renderSize.offset.y = posResult.y - renderSize.size.y / 2;

	RenderTexture(m_Renderer,m_Texture,
		nullptr, &renderSize,
		GetRotationResult().z);
}