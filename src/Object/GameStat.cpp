#include <fstream>

#include "MultiExtend.h"
#include "Object/GameStat.h"

#include "SDL.h"

#include "Actor/Actor.h"
#include "Texture/Texture.h"
#include "Shader/Shader.h"
#include "Component/Component.h"
#include "Renderer/Renderer.h"
#include "Debug/Message/Message.h"
#include "Debug/Message/MessageMicro.h"


MultiExtend::GameStat::GameStat()
	:Object()
{
}

MultiExtend::GameStat::~GameStat()
{
	for(auto shader : m_ShaderGLs)
	{
		delete shader;
	}
}

void MultiExtend::GameStat::AddActor(Actor* actor)
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

void MultiExtend::GameStat::RemoveActor(Actor* actor)
{
	auto it = std::remove_if(m_actors.begin(), m_actors.end(),
        [actor](Actor* ac) -> bool {return *actor->GetTag() == *ac->GetTag(); });
    m_actors.erase(it);
}

void MultiExtend::GameStat::AddTexture(Texture* texture)
{
	
	m_textures.emplace_back(texture);
	
}

void MultiExtend::GameStat::RemoveTexture(Texture* texture)
{
	auto it = std::remove_if(m_textures.begin(), m_textures.end(),
		[texture](Texture* tx) -> bool {return texture->GetHash() == tx->GetHash(); });
	m_textures.erase(it);
}

void MultiExtend::GameStat::AddShaderGL(ShaderGL* shader)
{
	m_ShaderGLs.emplace_back(shader);
}

void MultiExtend::GameStat::RemoveShaderGL(ShaderGL* shader)
{
	auto it = std::remove_if(m_ShaderGLs.begin(), m_ShaderGLs.end(),
		[shader](ShaderGL* sh) -> bool {return shader->GetHash() == sh->GetHash(); });
	m_ShaderGLs.erase(it);
}

void MultiExtend::GameStat::Update(float delta)
{
	MULTIEXTEND_TIMER_TRACE_TAG(UpdateGameStat);

	CustomUpdate(delta);
}

void MultiExtend::GameStat::CustomUpdate(float delta)
{
	
}
