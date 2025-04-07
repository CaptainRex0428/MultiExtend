#pragma once

#include "Component/Component.h"
#include "Component/BasicComponentConfig.h"

#include "API/IComponentOwner.h"
#include "API/IInput.h"

namespace MultiExtend
{
	class BasicComponent : public Component
	{
	public:
		MULTIEXTEND_API BasicComponent(
			IComponentOwner* Owner = nullptr,
			const char* tag = DEFAULT_BASICCOMPONENTNAME,
			int updateorder = DEFAULT_UPDATEORDER);

		MULTIEXTEND_API ~BasicComponent();

		MULTIEXTEND_API IComponentOwner* GetOwner() const;
		MULTIEXTEND_API void SetOwner(IComponentOwner* owner);

		MULTIEXTEND_API void ProcessInput(const uint8_t* keyState) override { if (GetState(Tag_INPUT)) CustomInput(keyState); };
		MULTIEXTEND_API virtual void CustomInput(const uint8_t* keyState) override = 0;

		MULTIEXTEND_API void Update(float delta) override { if(GetState(Tag_UPDATE)) CustomUpdate(delta);};
		MULTIEXTEND_API virtual void CustomUpdate(float delta) override = 0;

		MULTIEXTEND_API void Draw() override { if (GetState(Tag_DISPLAY)) CustomDraw() ;};
		MULTIEXTEND_API virtual void CustomDraw() override = 0;

	private:
		IComponentOwner* m_Owner;
	};
}