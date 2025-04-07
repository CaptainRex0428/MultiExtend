#pragma once

#include "MultiExtendAPI.h"
#include "ITransform.h"

#include <vector>

namespace MultiExtend
{
	class BasicComponent;

	class IComponentOwner : public ITransform
	{
	public:
		MULTIEXTEND_API virtual void UpdateComponents(float delta) = 0;
		MULTIEXTEND_API virtual void AddComponent(BasicComponent* component) = 0;
		MULTIEXTEND_API virtual void RemoveComponent(BasicComponent* component) = 0;
		MULTIEXTEND_API virtual const std::vector<BasicComponent*>& GetComponents() const = 0;
		MULTIEXTEND_API virtual BasicComponent* GetComponent(const char* component_tag) const = 0;
	};
}