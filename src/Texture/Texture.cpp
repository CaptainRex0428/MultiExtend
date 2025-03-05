#include "Texture/Texture.h"
#include "System/Hash/HashGenerator.h"
#include "System/Operator.h"
#include "Time/Clock/Clock.h"

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


MULTIEXTEND_API MultiExtend::Texture* MultiExtend::QueryTexture(Texture* texture, Vector2 querySize, Uint32* format, int* access)
{
	if (texture->IsA<SDL_Texture>())
	{
		int Width, Height;
		Width = (int)querySize.x;
		Height = (int)querySize.y;
		SDL_QueryTexture(texture->GetTextureAs<SDL_Texture>(), format, access, &Width, &Height);
		return texture;
	}
}

MULTIEXTEND_API void MultiExtend::RenderTexture(TextureRelocator& textureRelocator, float Width, float Height)
{
	SDL_Rect dst;
	dst.x = textureRelocator.offset.x;
	dst.y = textureRelocator.offset.y;
	dst.w = Width * textureRelocator.tiling.x;
	dst.h = Height * textureRelocator.tiling.y;
	SDL_RenderCopy(, textureRelocator.texture->GetTextureAs<SDL_Texture>(), nullptr, &dst);
}
