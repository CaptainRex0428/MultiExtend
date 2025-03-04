#include <fstream>

#include "SDL_image.h"

#include "Object/GameObject.h"
#include "MultiExtend.h"

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

Texture* MultiExtend::GameObject::LoadTexture(Renderer* renderer, const char* filepath)
{

	if(renderer->IsA<SDL_Renderer>())
	{
		return LoadTexture(renderer->GetRendererAs<SDL_Renderer>(),filepath);
	}

	return nullptr;
}

Texture* MultiExtend::GameObject::LoadTexture(SDL_Renderer* renderer, const char* filepath)
{
	std::ifstream f(filepath);

	if (!f.good())
	{
		SDL_Log("File Doesn't exist :%s", filepath);
		return nullptr;
	}

	SDL_Surface* surf = IMG_Load(filepath);

	if (!surf)
	{
		SDL_Log("Failed to load texture file :%s", filepath);
		return nullptr;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surf);

	SDL_FreeSurface(surf);

	if (texture == nullptr)
	{
		SDL_Log("Failed to convert surface to texture :%s", filepath);
		return nullptr;
	}

	TextureSDL* textureSDL = new TextureSDL(texture);

	Get()->m_textures.emplace_back(textureSDL);

	return textureSDL;
}

GameObject* MultiExtend::GameObject::Get()
{
    static GameObject instance;
    return &instance;
}
