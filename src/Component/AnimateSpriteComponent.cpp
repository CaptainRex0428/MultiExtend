#include "Component/AnimateSpriteComponent.h"

MultiExtend::AnimateSpriteComponent::AnimateSpriteComponent(
	Renderer* renderer, 
	const char* canva_path, 
	const char* tag, 
	Vector3 position, 
	Vector3 scale,
	Vector3 rotation, 
	int updateorder):
	SpriteComponent(renderer,canva_path,tag,position,scale,rotation)
{
}

MultiExtend::AnimateSpriteComponent::~AnimateSpriteComponent()
{
}
