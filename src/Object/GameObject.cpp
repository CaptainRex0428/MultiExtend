#include "Object/GameObject.h"
#include "MultiExtend.h"

#include <fstream>


MultiExtend::GameObject::GameObject()
	:Object()
{
}

void MultiExtend::GameObject::AddActor(Actor* actor)
{
	if (std::find(Get()->m_actors.begin(), Get()->m_actors.end(), actor) == Get()->m_actors.end())
	{
		int order = actor->GetUpdateOrder();
		auto iter = Get()->m_actors.begin();
		for (;iter != Get()->m_actors.end();++iter)
		{
			if (order < (*iter)->GetUpdateOrder())
			{
				break;
			}
		}
        Get()->m_actors.insert(iter,actor);
	}
}

void MultiExtend::GameObject::RemoveActor(Actor* actor)
{
	auto it = std::remove_if(Get()->m_actors.begin(), Get()->m_actors.end(),
        [actor](Actor* ac) -> bool {return *actor->GetTag() == *ac->GetTag(); });
    Get()->m_actors.erase(it);
}

bool MultiExtend::GameObject::Update(float delta)
{
	for (auto actor : Get()->m_actors)
	{
		actor->Update(delta);
	}

	return true;
}

void MultiExtend::GameObject::Draw()
{
	for (auto actor : Get()->m_actors)
	{
		actor->Draw();
	}
}

GameObject* MultiExtend::GameObject::Get()
{
    static GameObject instance;
    return &instance;
}
