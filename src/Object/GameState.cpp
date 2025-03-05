#include <fstream>

#include "MultiExtend.h"
#include "Object/GameState.h"

MultiExtend::GameState::GameState()
	:Object()
{
}

void MultiExtend::GameState::AddActor(Actor* actor)
{
	if (std::find(this->m_actors.begin(), m_actors.end(), actor) == m_actors.end())
	{
		int order = actor->GetUpdateOrder();
		auto iter = m_actors.begin();
		for (;iter != m_actors.end();++iter)
		{
			if (order < (*iter)->GetUpdateOrder())
			{
				break;
			}
		}
        m_actors.insert(iter,actor);
	}
}

void MultiExtend::GameState::RemoveActor(Actor* actor)
{
	auto it = std::remove_if(m_actors.begin(), m_actors.end(),
        [actor](Actor* ac) -> bool {return *actor->GetTag() == *ac->GetTag(); });
    m_actors.erase(it);
}

void MultiExtend::GameState::AddTexture(Texture* texture)
{
	
	m_textures.emplace_back(texture);
	
}

void MultiExtend::GameState::RemoveTexture(Texture* texture)
{
	auto it = std::remove_if(m_textures.begin(), m_textures.end(),
		[texture](Texture* tx) -> bool {return texture->GetHash() == tx->GetHash(); });
	m_textures.erase(it);
}

void MultiExtend::GameState::Update(float delta)
{
	/*for (auto actor : Get()->m_actors)
	{
		actor->Update(delta);
	}*/
}
