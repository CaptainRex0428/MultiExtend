#include "Texture/Texture.h"
#include "System/Hash/HashGenerator.h"
#include "System/Operator.h"
#include "Time/Clock/Clock.h"
#include "MultiExtend.h"

#include "SDL_image.h"

MultiExtend::Texture::Texture(const char * filePath)
	:m_FilePath(filePath)
{
	{
		MULTIEXTEND_TIMER_TRACE_TAG(GenerateTextureHash);

		std::string mac = Operator::Get().GetMacAddress();
		std::string time = Clock::GetCurrentTimeStamp_sys();
		m_hash = SHAGenerator::GenerateSHA256Hash(mac, time);
	}
	
}

MultiExtend::Texture::~Texture()
{
	m_FilePath = nullptr;
}

const std::string& MultiExtend::Texture::GetHash() const
{
	return m_hash;
}

const char* MultiExtend::Texture::GetFilePath() const
{
	return m_FilePath;
}

MultiExtend::TextureSDL::TextureSDL(SDL_Texture* texture, const char * filePath) 
	:Texture(filePath),m_Texture(texture)
{
}

void* MultiExtend::TextureSDL::GetTexture() const
{
    return m_Texture;
}

TextureSDL* MultiExtend::LoadTexture(GameStat* gameStat, SDL_Renderer* renderer, const char* filepath)
{
	MULTIEXTEND_TIMER_TRACE_TAG(LoadSDLTexture);

	if (!gameStat) return nullptr;

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

	TextureSDL* textureSDL = new TextureSDL(texture, filepath);

	gameStat->AddTexture(textureSDL);

	MULTIEXTEND_MESSAGE_CLIENT_TRACE("Loaded Texture:{0}", filepath);

	return textureSDL;
}

void MultiExtend::QueryTexture(Texture* texture, Vector2 * sourceSize, Uint32* format, int* access)
{
	if (texture->IsA<SDL_Texture>())
	{
		int w,h;
		SDL_QueryTexture(texture->GetTextureAs<SDL_Texture>(), format, access, &w, &h);

		(*sourceSize)[x] = (float)w;
		(*sourceSize)[y] = (float)h;
	}
}

void MultiExtend::RenderTexture(
	SDL_Renderer * renderer,
	Texture* texture,
	TextureRelocator* srcLocator,
	TextureRelocator* dstLocator,
	float rotate, Vector2 * point, TextureFlip flip)
{
	if(renderer && texture->IsA<SDL_Texture>())
	{
		SDL_Rect srcRect;
		SDL_Rect dstRect;

		if(srcLocator)
		{
			srcRect.w = (int)srcLocator->size[x];
			srcRect.h = (int)srcLocator->size[y];
			srcRect.x = (int)srcLocator->offset[x];
			srcRect.y = (int)srcLocator->offset[y];
		}

		
		dstRect.w = (int)dstLocator->size[x];
		dstRect.h = (int)dstLocator->size[y];
		dstRect.x = (int)dstLocator->offset[x];
		dstRect.y = (int)dstLocator->offset[y];

		SDL_Point center;
		if(point)
		{
			center.x = (int)((*point)[x]);
			center.y = (int)((*point)[y]);
		}

		SDL_RendererFlip textureFlip;
		switch (flip)
		{
		case FLIP_NONE:
			textureFlip = SDL_FLIP_NONE;
			break;
		case FLIP_HORIZON:
			textureFlip = SDL_FLIP_HORIZONTAL;
			break;
		case FLIP_VERTICAL:
			textureFlip = SDL_FLIP_VERTICAL;
			break;
		default:
			textureFlip = SDL_FLIP_NONE;
			break;
		}
		
		SDL_RenderCopyEx(
			renderer, 
			texture->GetTextureAs<SDL_Texture>(), 
			(srcLocator ? &srcRect : NULL), &dstRect,
			rotate, point ? &center : NULL, textureFlip);
	}
}
