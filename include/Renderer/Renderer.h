#pragma once

#include "SDL.h"

#include "MultiExtendAPI.h"
#include "Object/Object.h"


namespace MultiExtend
{
	// API
	class Renderer : public Object
	{
	public:
		MULTIEXTEND_API Renderer();
		MULTIEXTEND_API virtual ~Renderer();

		MULTIEXTEND_API virtual void* GetRenderer() const = 0;

		template <typename T>
		MULTIEXTEND_API T* GetRendererAs() const
		{
			return static_cast<T*>(GetRenderer());
		}

		template <typename T>
		MULTIEXTEND_API bool IsA()
		{
			return static_cast<T*>(GetRenderer());
		}
	};

	class RendererSDL : public Renderer
	{
	public:
		MULTIEXTEND_API RendererSDL(SDL_Renderer* renderer);

		MULTIEXTEND_API virtual void* GetRenderer() const override;

	private:
		SDL_Renderer* m_Renderer;

	};
}