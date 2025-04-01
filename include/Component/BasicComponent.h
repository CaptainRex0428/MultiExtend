#pragma once

#include "MultiExtend.h"
#include "Component/Component.h"
#include "Component/BasicComponentConfig.h"

#include "Actor/Actor.h"


namespace MultiExtend
{
	class BasicComponent : public Component
	{
	public:
		MULTIEXTEND_API BasicComponent(
			Actor * Owner = nullptr,
			const char* tag = DEFAULT_BASICCOMPONENTNAME,
			int updateorder = DEFAULT_UPDATEORDER);

		MULTIEXTEND_API ~BasicComponent();

		MULTIEXTEND_API Actor * GetOwner() const;
		MULTIEXTEND_API void SetOwner(Actor * owner);

	private:
		Actor * m_Owner;
	};
}