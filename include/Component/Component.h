#pragma once

#include "MultiExtendAPI.h"

#include "ComponentConfig.h"
#include "Object/Object.h"

#include <vector>
#include "API/IBasic.h"
#include "API/IInput.h"
#include "API/IUpdate.h"
#include "API/IDraw.h"

namespace MultiExtend
{
	class Component : public Object, public IBasic, public IInput, public IUpdate, public IDraw
	{
	public:
		MULTIEXTEND_API Component(
			const char* tag = DEFAULT_COMPONENTNAME,
			int updateorder = DEFAULT_UPDATEORDER);

		MULTIEXTEND_API virtual ~Component();

		MULTIEXTEND_API virtual void ProcessInput(const uint8_t* keyState) override = 0;
		MULTIEXTEND_API virtual void CustomInput(const uint8_t* keyState) override = 0;

		MULTIEXTEND_API void Update(float delta) = 0;
		MULTIEXTEND_API virtual void CustomUpdate(float delta) = 0;

		MULTIEXTEND_API void Draw(const float& ratio) = 0;
		MULTIEXTEND_API virtual void CustomDraw() = 0;

		MULTIEXTEND_API const char* GetTag() const override;
		MULTIEXTEND_API virtual void SetTag(const char* type) override;
		MULTIEXTEND_API const int& GetUpdateOrder() const override;
		MULTIEXTEND_API virtual void SetUpdateOrder(int order) override;

		MULTIEXTEND_API virtual int  GetState() const override;
		MULTIEXTEND_API virtual bool GetState(StateTag tag) const override;
		MULTIEXTEND_API virtual void SetState(int state) override;
		MULTIEXTEND_API virtual void ToggleState(StateTag tag) override;

		
	protected:
		int m_updateorder;

	private:
		char* m_Tag;
		int m_State;
	};
}