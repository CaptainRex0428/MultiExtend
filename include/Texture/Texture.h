#pragma once

#include "SDL.h"

#include "MultiExtendAPI.h"
#include "Object/Object.h"

#include "Math/Vector.h" 

#include "Object/GameStat.h"


namespace MultiExtend
{

	// API
	class Texture : public Object
	{
	public:
		MULTIEXTEND_API Texture(const char * filePath);
		MULTIEXTEND_API virtual ~Texture();

		MULTIEXTEND_API virtual void * GetTexture() const = 0;

		template <typename T>
		inline T* GetTextureAs() const
		{
			return static_cast<T*>(GetTexture());
		}

		template <typename T>
		inline bool IsA()
		{
			return static_cast<T*>(GetTexture());
		}

		MULTIEXTEND_API const std::string& GetHash() const;
		MULTIEXTEND_API const char * GetFilePath() const;

	private:
		std::string m_hash;
		const char* m_FilePath;
	};

	class TextureSDL : public Texture
	{
	public:
		MULTIEXTEND_API TextureSDL(SDL_Texture* texture, const char * filePath);

		MULTIEXTEND_API virtual void* GetTexture() const override;

	private:
		SDL_Texture* m_Texture;
	};

	struct TextureRelocator
	{
		Vector2 offset = Vector2{0,0};
		Vector2 size = Vector2{32, 32};
	};

	enum TextureFlip
	{
		FLIP_NONE,
		FLIP_HORIZON,
		FLIP_VERTICAL
	};

	MULTIEXTEND_API TextureSDL* LoadTexture(GameStat* GameStat, SDL_Renderer* renderer, const char* filepath);

	MULTIEXTEND_API void QueryTexture(Texture * texture, Vector2 * sourceSize, Uint32* format = nullptr, int* access = nullptr);

	MULTIEXTEND_API void RenderTexture(SDL_Renderer * renderer, Texture* texture, TextureRelocator * srcLocator, TextureRelocator * dstLocator, float rotate = 0, Vector2 * point = nullptr, TextureFlip flip = FLIP_NONE);
}