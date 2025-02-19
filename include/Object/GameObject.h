#pragma once

#include <vector>

#include "Component/Component.h"
#include "Actor/Actor.h"

// Singleton Class
class GameObject : public Object
{
public:
	MULTIEXTEND_API GameObject(GameObject&) = delete;

	MULTIEXTEND_API static void AddActor(Actor* actor);
	MULTIEXTEND_API static void RemoveActor(Actor* actor);

	MULTIEXTEND_API static bool Update(float delta);
	MULTIEXTEND_API static void Draw();


private:
	MULTIEXTEND_API GameObject();
	MULTIEXTEND_API virtual ~GameObject() = default;

	MULTIEXTEND_API static GameObject* Get();

	std::vector<Actor*> m_actors;
};