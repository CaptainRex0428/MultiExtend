#pragma once

#include "MultiExtendAPI.h"
#include "IComponentOwner.h"

#include <vector>

namespace MultiExtend
{
	class ActorComponent;

	class IActorComponentOwner : public IComponentOwner
	{
	public:
		MULTIEXTEND_API virtual void UpdateChildActorComponents(float delta) = 0;
		MULTIEXTEND_API virtual void AddChildActorComponent(ActorComponent* child) = 0;
		MULTIEXTEND_API virtual void RemoveChildActorComponent(ActorComponent* child) = 0;
		MULTIEXTEND_API virtual const std::vector<ActorComponent*>& GetChildActorComponents() const = 0;
		MULTIEXTEND_API virtual ActorComponent* GetChildActorComponent(const char* component_tag) const = 0;
		MULTIEXTEND_API virtual ActorComponent* GetChildActorComponent(int component_idx) const = 0;
	};
}