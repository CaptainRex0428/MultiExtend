#pragma once

#include "SDL.h"

#include "MultiExtendAPI.h"
#include "Object/Object.h"
#include "Renderer/Renderer.h"
#include "Math/Vector.h" 


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

		MULTIEXTEND_API const std::string& GetHash() const;

	private:
		std::string m_hash;
		
	};

	class TextureSDL : public Texture
	{
	public:
		MULTIEXTEND_API TextureSDL(SDL_Texture* texture);

		MULTIEXTEND_API virtual void* GetTexture() const override;

	private:
		SDL_Texture* m_Texture;

	};

	struct TextureRelocator
	{
		Vector2 offset;
		Vector2 scale;
		Vector2 size;
	};

	enum TextureFlip
	{
		FLIP_NONE,
		FLIP_HORIZON,
		FLIP_VERTICAL
	};

	MULTIEXTEND_API void QueryTexture(Texture * texture, Vector2 * sourceSize, Uint32* format = nullptr, int* access = nullptr);

	MULTIEXTEND_API void RenderTexture(Renderer * renderer, Texture* texture, TextureRelocator * srcLocator, TextureRelocator * dstLocator, float rotate = 0, Vector2 * point = nullptr, TextureFlip flip = FLIP_NONE);
}