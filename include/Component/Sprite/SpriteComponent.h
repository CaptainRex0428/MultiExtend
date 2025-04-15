#pragma once

#include "MultiExtendAPI.h"
#include "SpriteComponentConfig.h"

#include "Component/ActorComponent.h"
#include "Texture/Texture.h"

namespace MultiExtend
{
	class SpriteComponent : public ActorComponent
	{
		MULTIEXTEND_API SpriteComponent(
			Texture* texture = nullptr,
			const char* tag = BaseSpriteComponentTypeName,
			Vector3 postion = Vector3{ 0.0f, 0.0f, 0.0f },
			Vector3 scale = Vector3{ 1.0f, 1.0f, 1.0f },
			Vector3 rotation = Vector3{ 0.0f, 0.0f, 0.0f },
			Vector2 size = Vector2{ 32, 32 },
			int updateorder = DEFAULT_UPDATEORDER);
	};
}