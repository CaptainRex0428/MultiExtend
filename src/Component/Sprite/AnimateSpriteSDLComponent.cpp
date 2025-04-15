#include "Component/Sprite/AnimateSpriteSDLComponent.h"
#include "MultiExtend.h"

MultiExtend::AnimateSpriteSDLComponent::AnimateSpriteSDLComponent(
	float FPS,
	GameStat* gameStat,
	SDL_Renderer* renderer, 
	std::vector<const char*> textureFilePaths,
	const char* tag, 
	Vector3 position, 
	Vector3 scale,
	Vector3 rotation,
	Vector2 size,
	int updateorder):
	SpriteSDLComponent(gameStat, renderer, textureFilePaths[0], tag, position, scale, rotation, size, updateorder),
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

MultiExtend::AnimateSpriteSDLComponent::AnimateSpriteSDLComponent(
	float FPS,
	SDL_Renderer* renderer,
	std::vector<Texture*> textures,
	const char* tag,
	Vector3 position,
	Vector3 scale,
	Vector3 rotation,
	Vector2 size,
	int updateorder) :
	SpriteSDLComponent(renderer, textures[0], tag, position, scale, rotation, size, updateorder),
	m_FPS(FPS),
	m_currentFrame(0)
{
	m_animateTextures = textures;
}

MultiExtend::AnimateSpriteSDLComponent::~AnimateSpriteSDLComponent()
{
}

void MultiExtend::AnimateSpriteSDLComponent::Update(float delta)
{
	MULTIEXTEND_TIMER_TRACE_TAG(UpdateAnimateSpriteComponent);

	if (m_animateTextures.size() > 0)
	{
		SetCurrentFrame(m_currentFrame + m_FPS * delta);

		size_t resetIdx = (int)m_currentFrame;

		resetIdx = resetIdx < m_animateTextures.size() ? resetIdx :(m_animateTextures.size()-1);

		SpriteSDLComponent::SetTexture(m_animateTextures[resetIdx]);
	}

	SpriteSDLComponent::Update(delta);
}

void MultiExtend::AnimateSpriteSDLComponent::SetAnimTextures(std::vector<Texture*>& animateTextures)
{
	if(animateTextures.size() > 0)
	{
		m_animateTextures = animateTextures;
	}
	
}

float MultiExtend::AnimateSpriteSDLComponent::GetAnimFPS() const
{
	return m_FPS;
}

void MultiExtend::AnimateSpriteSDLComponent::SetAnimFPS(float fps)
{
	m_FPS = fps > 0? fps : 0;
}

void MultiExtend::AnimateSpriteSDLComponent::SetCurrentFrame(float frame)
{
	m_currentFrame = frame;

	// Wrap current frame if needed (set from begin)
	while (m_currentFrame > m_animateTextures.size())
	{
		m_currentFrame -= m_animateTextures.size();
	}
}