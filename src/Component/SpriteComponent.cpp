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

	QueryTexture(texture, m_TextureRender_w, m_TextureRender_h);

}

MULTIEXTEND_API void MultiExtend::SpriteComponent::Draw_SDL(SDL_Renderer * renderer)
{
	if (m_Texture->GetTextureAs<SDL_Texture>())
	{
		SDL_Rect r;
		const Vector3 scaleresult = GetScaleResult();
		const Vector3 posresult = GetPositionResult();

		r.w = (int)(m_TextureRender_w * scaleresult.x);
		r.h = (int)(m_TextureRender_h * scaleresult.y);
		r.x = (int)(posresult.x - r.w / 2);
		r.y = (int)(posresult.y - r.h / 2);

		SDL_RenderCopyEx(
			renderer,
			m_Texture->GetTextureAs<SDL_Texture>(),
			nullptr,
			&r,
			GetRotationResult().z,
			nullptr,
			SDL_FLIP_NONE);
	}
}

void MultiExtend::SpriteComponent::Draw()
{
	if(m_Renderer->IsA<SDL_Renderer>())
	{
		Draw_SDL(m_Renderer->GetRendererAs<SDL_Renderer>());
	}
		
	ActorComponent::Draw();
}