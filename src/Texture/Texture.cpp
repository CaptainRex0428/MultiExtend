#include "Texture/Texture.h"

MultiExtend::Texture::Texture()
{
}

MultiExtend::Texture::~Texture()
{
}

MultiExtend::TextureSDL::TextureSDL(SDL_Texture* texture) 
	:m_Texture(texture)
{
}

void* MultiExtend::TextureSDL::GetTexture() const
{
    return m_Texture;
}
