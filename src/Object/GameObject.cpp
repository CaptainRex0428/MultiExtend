#include "Object/GameObject.h"
#include "MultiExtend.h"

#include <fstream>


GameObject::GameObject()
	:Object()
{
	MULTIEXTEND_MESSAGE_TERMINAL_DEBUG("{0}:{1}", "GameObject Constructed(Hash)", GetHash());
}

void GameObject::AddActor(Actor* actor)
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

void GameObject::RemoveActor(Actor* actor)
{
	auto it = std::remove_if(Get()->m_actors.begin(), Get()->m_actors.end(),
        [actor](Actor* ac) -> bool {return *actor->GetTag() == *ac->GetTag(); });
    Get()->m_actors.erase(it);
}

bool GameObject::Update(float delta)
{
	for (auto actor : Get()->m_actors)
	{
		actor->Update(delta);
	}

	return true;
}

void GameObject::Draw()
{
	for (auto actor : Get()->m_actors)
	{
		actor->Draw();
	}
}

GameObject* GameObject::Get()
{
    static GameObject instance;
    return &instance;
}
