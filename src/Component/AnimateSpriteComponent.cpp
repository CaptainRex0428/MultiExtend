#include "Component/AnimateSpriteComponent.h"
#include "MultiExtend.h"

MultiExtend::AnimateSpriteComponent::AnimateSpriteComponent(
	float FPS,
	GameStat* gameStat,
	Renderer* renderer, 
	std::vector<const char*> textureFilePaths,
	const char* tag, 
	Vector3 position, 
	Vector3 scale,
	Vector3 rotation,
	Vector2 size,
	int updateorder):
	SpriteComponent(gameStat, renderer, textureFilePaths[0], tag, position, scale, rotation, size, updateorder),
	m_FPS(FPS),
	m_currentFrame(0)
{
	m_animateTextures.clear();
	m_animateTextures.emplace_back(m_Texture);

	auto iter = textureFilePaths.begin()+1;
	for(;iter != textureFilePaths.end(); ++iter)
	{
		Texture * texture = MultiExtend::LoadTexture(gameStat,renderer,*iter);
		m_animateTextures.emplace_back(texture);
	};
}

MultiExtend::AnimateSpriteComponent::AnimateSpriteComponent(
	float FPS,
	Renderer* renderer,
	std::vector<Texture*> textures,
	const char* tag,
	Vector3 position,
	Vector3 scale,
	Vector3 rotation,
	Vector2 size,
	int updateorder) :
	SpriteComponent(renderer, textures[0], tag, position, scale, rotation, size, updateorder),
	m_FPS(FPS),
	m_currentFrame(0)
{
	m_animateTextures = textures;
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

		SetTexture(m_animateTextures[resetIdx]);
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


