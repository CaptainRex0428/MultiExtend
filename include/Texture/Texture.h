#pragma once

#include "SDL.h"

#include "MultiExtendAPI.h"
#include "Object/Object.h"


namespace MultiExtend
{

	// API
	class Texture : public Object
	{
	public:
		MULTIEXTEND_API Texture();
		MULTIEXTEND_API virtual ~Texture();

		MULTIEXTEND_API virtual void * GetTexture() const = 0;

		template <typename T>
		MULTIEXTEND_API T* GetTextureAs() const
		{
			return static_cast<T*>(GetTexture());
		}

		template <typename T>
		MULTIEXTEND_API bool IsA()
		{
			return static_cast<T*>(GetTexture());
		}
		
	};

	class TextureSDL : public Texture
	{
	public:
		MULTIEXTEND_API TextureSDL(SDL_Texture* texture);

		MULTIEXTEND_API virtual void* GetTexture() const override;

	private:
		SDL_Texture* m_Texture;

	};
}