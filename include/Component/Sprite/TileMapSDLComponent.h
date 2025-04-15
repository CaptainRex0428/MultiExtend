#pragma once

#include "MultiExtendAPI.h"
#include "Component/ActorComponent.h"

#include "Texture/Texture.h"
#include "Object/GameStat.h"

#include "TileMapSDLComponentConfig.h"

namespace MultiExtend
{
	class TileMapSDLComponent : public ActorComponent
	{
	public:
		MULTIEXTEND_API TileMapSDLComponent(
			GameStat* gameState,
			SDL_Renderer* renderer,
			const char* texturefilepath = nullptr,
			Vector2 srcPosition = Vector2{0, 0},
			Vector2 srcSize = Vector2{256, 256},
			Vector2 dstSize = Vector2{256,256},
			const char* tag = DEFAULT_TILEMAPCOMPONENTNAME,
			Vector3 postion = Vector3{0.0f, 0.0f, 0.0f},
			Vector3 scale = Vector3{1.0f, 1.0f, 1.0f},
			Vector3 rotation = Vector3{0.0f, 0.0f, 0.0f},
			int updateorder = DEFAULT_UPDATEORDER);

		MULTIEXTEND_API TileMapSDLComponent(
			SDL_Renderer* renderer,
			Texture* texture = nullptr,
			Vector2 srcPosition = Vector2{ 0, 0 },
			Vector2 srcSize = Vector2{ 256, 256 },
			Vector2 dstSize = Vector2{ 256,256 },
			const char* tag = DEFAULT_TILEMAPCOMPONENTNAME,
			Vector3 postion = Vector3{ 0.0f, 0.0f, 0.0f },
			Vector3 scale = Vector3{ 1.0f, 1.0f, 1.0f },
			Vector3 rotation = Vector3{ 0.0f, 0.0f, 0.0f },
			int updateorder = DEFAULT_UPDATEORDER);

		MULTIEXTEND_API virtual ~TileMapSDLComponent();

		MULTIEXTEND_API virtual void Update(float delta) override;
		MULTIEXTEND_API virtual void Draw(const float& ratio) override;

		MULTIEXTEND_API virtual void SetTexture(Texture* texture);

		MULTIEXTEND_API virtual void SetDstSize(Vector2 size);
		MULTIEXTEND_API virtual Vector2 GetDstSize() const;

		MULTIEXTEND_API virtual void SetSrcSize(Vector2 size);
		MULTIEXTEND_API virtual Vector2 GetSrcSize() const;

		MULTIEXTEND_API virtual void SetSrcPosition(Vector2 position);
		MULTIEXTEND_API virtual Vector2 GetSrcPosition() const;

	private:
		Texture * m_Texture;
		SDL_Renderer * m_Renderer;
		Vector2 m_srcPosition;
		Vector2 m_srcSize;
		Vector2 m_dstSize;
	};
}