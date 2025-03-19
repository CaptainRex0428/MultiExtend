#include "Texture/Texture.h"
#include "System/Hash/HashGenerator.h"
#include "System/Operator.h"
#include "Time/Clock/Clock.h"
#include "MultiExtend.h"

MultiExtend::Texture::Texture()
{
	std::string mac = Operator::Get().GetMacAddress();
	std::string time = Clock::GetCurrentTimeStamp_sys();
	m_hash = SHAGenerator::GenerateSHA256Hash(mac, time);
}

MultiExtend::Texture::~Texture()
{
}

MULTIEXTEND_API const std::string& MultiExtend::Texture::GetHash() const
{
	return m_hash;
}

MultiExtend::TextureSDL::TextureSDL(SDL_Texture* texture) 
	:m_Texture(texture)
{
}

void* MultiExtend::TextureSDL::GetTexture() const
{
    return m_Texture;
}

void MultiExtend::QueryTexture(Texture* texture, Vector2 * sourceSize, Uint32* format, int* access)
{
	if (texture->IsA<SDL_Texture>())
	{
		int w,h;
		SDL_QueryTexture(texture->GetTextureAs<SDL_Texture>(), format, access, &w, &h);

		sourceSize->x = (float)w;
		sourceSize->y = (float)h;
	}
}

void MultiExtend::RenderTexture(
	Renderer* renderer,
	Texture* texture,
	TextureRelocator* srcLocator,
	TextureRelocator* dstLocator,
	float rotate, Vector2 * point, TextureFlip flip)
{
	if(renderer->IsA<SDL_Renderer>() && texture->IsA<SDL_Texture>())
	{
		SDL_Rect srcRect;
		SDL_Rect dstRect;

		if(srcLocator)
		{
			srcRect.w = (int)srcLocator->size.x;
			srcRect.h = (int)srcLocator->size.y;
			srcRect.x = (int)srcLocator->offset.x;
			srcRect.y = (int)srcLocator->offset.y;
		}

		
		dstRect.w = (int)dstLocator->size.x;
		dstRect.h = (int)dstLocator->size.y;
		dstRect.x = (int)dstLocator->offset.x;
		dstRect.y = (int)dstLocator->offset.y;

		SDL_Point center;
		if(point)
		{
			center.x = (int)point->x;
			center.y = (int)point->y;
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
			renderer->GetRendererAs<SDL_Renderer>(), 
			texture->GetTextureAs<SDL_Texture>(), 
			(srcLocator ? &srcRect : NULL), &dstRect,
			rotate, point ? &center : NULL, textureFlip);
	}
}
