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
		Texture * texture;
		Vector2 offset;
		Vector2 tiling;
	};

	MULTIEXTEND_API void QueryTexture(TextureRelocator & textureRelocator, float Width, float Height, Uint32* format = nullptr, int* access = nullptr);
	MULTIEXTEND_API void QueryTexture(Texture * texture, int Width, int Height, Uint32* format = nullptr, int* access = nullptr);

	MULTIEXTEND_API void RenderTexture(TextureRelocator & textureRelocator, float Width, float Height);
}