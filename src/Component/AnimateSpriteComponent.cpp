#include "Component/AnimateSpriteComponent.h"

MultiExtend::AnimateSpriteComponent::AnimateSpriteComponent(
	float FPS,
	GameState* gameState,
	Renderer* renderer, 
	const char* canva_path, 
	const char* tag, 
	Vector3 position, 
	Vector3 scale,
	Vector3 rotation, 
	int updateorder):
	SpriteComponent(gameState, renderer,canva_path,tag,position,scale,rotation),
	m_FPS(FPS),
	m_currentFrame(0)
{
}

MultiExtend::AnimateSpriteComponent::~AnimateSpriteComponent()
{
}

void MultiExtend::AnimateSpriteComponent::Update(float delta)
{
	if (m_animateTextures.size() > 0)
	{
		m_currentFrame += m_FPS * delta;

		// Wrap current frame if needed (set from begin)
		while (m_currentFrame > m_animateTextures.size())
		{
			m_currentFrame -= m_animateTextures.size();
		}

		size_t resetIdx = (int)m_currentFrame;

		resetIdx = resetIdx < m_animateTextures.size() ? resetIdx :(m_animateTextures.size()-1);

		SetSingleTexture(m_animateTextures[resetIdx]);
	}

	SpriteComponent::Update(delta);
}

void MultiExtend::AnimateSpriteComponent::SetAnimTextures(std::vector<Texture*>& animateTextures)
{
	if(animateTextures.size() > 0)
	{
		m_animateTextures = animateTextures;
	}
	
}

float MultiExtend::AnimateSpriteComponent::GetAnimFPS() const
{
	return m_FPS;
}

void MultiExtend::AnimateSpriteComponent::SetAnimFPS(float fps)
{
	m_FPS = fps > 0? fps : 0;
}


