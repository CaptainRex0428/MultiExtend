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

void MultiExtend::QueryTexture(TextureRelocator& textureRelocator, float Width, float Height, Uint32* format, int* access)
{
	Texture * texture = textureRelocator.texture;

	QueryTexture(texture, Width, Height, format, access);
}

MULTIEXTEND_API void MultiExtend::QueryTexture(Texture* texture, int Width, int Height, Uint32* format, int* access)
{
	if (texture->IsA<SDL_Texture>())
	{
		SDL_QueryTexture(texture->GetTextureAs<SDL_Texture>(), nullptr, nullptr, &Width, &Height);
	}
}