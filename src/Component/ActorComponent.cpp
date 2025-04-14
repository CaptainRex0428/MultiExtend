#include "Component/ActorComponent.h"
#include "MultiExtend.h"
#include "Math/Vector.h"

MultiExtend::ActorComponent::ActorComponent(
	const char* tag,
	Vector3 position,
	Vector3 scale,
	Vector3 rotation,
	int updateorder)
	:
	Component(tag, updateorder),
	m_ParentActorComponent(nullptr),
	m_position(position),
	m_scale(scale),
	m_rotation(rotation)
{
}

MultiExtend::ActorComponent::~ActorComponent()
{
	for (auto actor_component : m_ChildActorComponents)
	{
		actor_component->ClearParentActorComponent();
	}

	if(m_ParentActorComponent)
	{
		m_ParentActorComponent->RemoveChildActorComponent(this);
		m_ParentActorComponent = nullptr;
	}
	
}

void MultiExtend::ActorComponent::UpdateComponents(float delta)
{
	MULTIEXTEND_TIMER_TRACE_TAG(UpdateComponents);

	for (auto component : m_Components)
	{
		component->Update(delta);
	}
}

void MultiExtend::ActorComponent::AddComponent(MultiExtend::BasicComponent* component)
{
	if (std::find(m_Components.begin(), m_Components.end(),
		component) == m_Components.end())
	{
		int order = component->GetUpdateOrder();
		auto iter = m_Components.begin();
		for (; iter != m_Components.end(); ++iter)
		{
			if (order < (*iter)->GetUpdateOrder())
			{
				break;
			}
		}

		m_Components.insert(iter, component);

		component->SetOwner(this);
	}
}

void MultiExtend::ActorComponent::RemoveComponent(MultiExtend::BasicComponent* component)
{
	auto it = std::remove_if(m_Components.begin(), m_Components.end(),
		[component](Component* comp) -> bool {return *component->GetTag() == *comp->GetTag(); });
	m_Components.erase(it);
	(*it)->SetOwner(nullptr);
}

const std::vector<MultiExtend::BasicComponent*>& MultiExtend::ActorComponent::GetComponents() const
{
	return m_Components;
}

MultiExtend::BasicComponent* MultiExtend::ActorComponent::GetComponent(const char* component_tag) const
{
	for (auto component : m_Components)
	{
		if (*component->GetTag() == *component_tag)
		{
			return component;
		}
	}

	return nullptr;
}

void MultiExtend::ActorComponent::UpdateChildActorComponents(float delta)
{
	MULTIEXTEND_TIMER_TRACE_TAG(UpdateChildActorComponents);

	for (auto child : m_ChildActorComponents)
	{
		child->Update(delta);
	}
}

void MultiExtend::ActorComponent::AddChildActorComponent(MultiExtend::ActorComponent* child)
{
	if (std::find(m_ChildActorComponents.begin(),
		m_ChildActorComponents.end(),
		child) == m_ChildActorComponents.end())
	{
		int order = child->Component::GetUpdateOrder();
		auto iter = m_ChildActorComponents.begin();

		for (; iter != m_ChildActorComponents.end(); ++iter)
		{
			if (order < (*iter)->Component::GetUpdateOrder())
			{
				break;
			}
		}

		m_ChildActorComponents.insert(iter, child);
		child->SetParentActorComponent(this);

		
	}
}

void MultiExtend::ActorComponent::SetParentActorComponent(ActorComponent* parent)
{
	m_ParentActorComponent = parent;
}

void MultiExtend::ActorComponent::RemoveChildActorComponent(ActorComponent* child)
{
	auto it = std::remove_if(m_ChildActorComponents.begin(),
		m_ChildActorComponents.end(),
		[child](ActorComponent* ch) -> bool { return *child->Component::GetTag() == *ch->Component::GetTag(); });
	m_ChildActorComponents.erase(it);
}

const std::vector<MultiExtend::ActorComponent*>& MultiExtend::ActorComponent::GetChildActorComponents() const
{
	return m_ChildActorComponents;
}

MultiExtend::ActorComponent* MultiExtend::ActorComponent::GetChildActorComponent(const char* component_tag) const
{
	for (auto child : m_ChildActorComponents)
	{
		if (*child->Component::GetTag() == *component_tag)
		{
			return child;
		}
	}

	return nullptr;
}

ActorComponent* MultiExtend::ActorComponent::GetChildActorComponent(int component_idx) const
{
	if (component_idx > m_ChildActorComponents.size()-1 || component_idx < 0)
	{
		return nullptr;
	}

	return m_ChildActorComponents[component_idx];
}

void MultiExtend::ActorComponent::AttachParentActorComponent(MultiExtend::ActorComponent* parent)
{
	MULTIEXTEND_TIMER_TRACE_TAG(AttachParentActorComponent);

	if (std::find(m_ChildActorComponents.begin(),
		m_ChildActorComponents.end(),
		parent) == m_ChildActorComponents.end())
	{
		if (m_ParentActorComponent != parent)
		{
			if (m_ParentActorComponent != nullptr)
			{
				m_ParentActorComponent->RemoveChildActorComponent(this);
			}

			parent->AddChildActorComponent(this);

			m_ParentActorComponent = parent;
		}

		return;
	}
#ifdef DEBUG
	std::cout << "Cannot attach parent actor component to child actor component." << std::endl;
#endif
}

void MultiExtend::ActorComponent::DettachParentActorComponent()
{
	if (m_ParentActorComponent != nullptr)
	{
		m_ParentActorComponent->RemoveChildActorComponent(this);
		m_ParentActorComponent = nullptr;
	}
}

MultiExtend::ActorComponent* MultiExtend::ActorComponent::GetParentActorComponent() const
{
	return m_ParentActorComponent;
}

const MultiExtend::Vector3& MultiExtend::ActorComponent::GetPositionRelative() const
{
	return m_position;
}

const MultiExtend::Vector3& MultiExtend::ActorComponent::GetScaleRelative() const
{
	return m_scale;
}

const MultiExtend::Vector3& MultiExtend::ActorComponent::GetRotationRelative() const
{
	return m_rotation;
}

void MultiExtend::ActorComponent::SetPositionRelative(Vector3 pos)
{
	m_position = pos;
}

void MultiExtend::ActorComponent::SetScaleRelative(Vector3 scale)
{
	m_scale = scale;
}

void MultiExtend::ActorComponent::SetRotationRelative(Vector3 rotation)
{
	m_rotation = rotation;
}

const MultiExtend::Vector3 MultiExtend::ActorComponent::GetPositionAbsolute() const
{
	MULTIEXTEND_TIMER_TRACE_TAG(GetActorComponentWorldPosition);

	float p_x = m_position[x];
	float p_y = m_position[y];
	float p_z = m_position[z];

	MultiExtend::ActorComponent* parent = GetParentActorComponent();

	while (parent)
	{
		p_x += parent->GetPositionRelative()[x];
		p_y += parent->GetPositionRelative()[y];
		p_z += parent->GetPositionRelative()[z];

		parent = parent->GetParentActorComponent();
	}

	return Vector3{p_x, p_y, p_z};

}

const MultiExtend::Vector3 MultiExtend::ActorComponent::GetScaleAbsolute() const
{
	MULTIEXTEND_TIMER_TRACE_TAG(GetActorComponentWorldScale);

	float scalesize_x = m_scale[x];
	float scalesize_y = m_scale[y];
	float scalesize_z = m_scale[z];
	ActorComponent* parent = GetParentActorComponent();

	while (parent)
	{
		scalesize_x *= parent->GetScaleRelative()[x];
		scalesize_y *= parent->GetScaleRelative()[y];
		scalesize_z *= parent->GetScaleRelative()[z];

		parent = parent->GetParentActorComponent();
	}

	return Vector3{scalesize_x, scalesize_y, scalesize_z};

}

const MultiExtend::Vector3 MultiExtend::ActorComponent::GetRotationAbsolute() const
{
	MULTIEXTEND_TIMER_TRACE_TAG(GetActorComponentWorldRotation);

	float r_x = m_rotation[x];
	float r_y = m_rotation[y];
	float r_z = m_rotation[z];
	ActorComponent* parent = GetParentActorComponent();

	while (parent)
	{
		r_x *= parent->GetRotationRelative()[x];
		r_y *= parent->GetRotationRelative()[y];
		r_z *= parent->GetRotationRelative()[z];

		parent = parent->GetParentActorComponent();
	}

	return Vector3{r_x, r_y, r_z};

}

MULTIEXTEND_API void MultiExtend::ActorComponent::SetUpdateOrder(int order)
{
	Component::SetUpdateOrder(order);

	// may reorder
}

bool MultiExtend::ActorComponent::operator==(ActorComponent* other)
{
	return this->Component::GetTag() == other->Component::GetTag();
}

void MultiExtend::ActorComponent::ClearParentActorComponent()
{
	if (m_ParentActorComponent->GetParentActorComponent() != nullptr)
	{
		m_ParentActorComponent = m_ParentActorComponent->GetParentActorComponent();
		return;
	}

	m_ParentActorComponent = nullptr;
}

void MultiExtend::ActorComponent::Update(float delta)
{
	MULTIEXTEND_TIMER_TRACE_TAG(UpdateActorComponent);

	if(GetState(Tag_UPDATE))
	{
		CustomUpdate(delta);

		UpdateChildActorComponents(delta);
		UpdateComponents(delta);		
	}

	return;
}

void MultiExtend::ActorComponent::CustomUpdate(float delta)
{
	
}

void MultiExtend::ActorComponent::Draw(const float& ratio)
{
	MULTIEXTEND_TIMER_TRACE_TAG(DrawActorComponent);
	if (GetState(Tag_DISPLAY))
	{
		CustomDraw();

		for (auto component : m_Components)
		{
			component->Draw(ratio);
		}

		for (auto child : m_ChildActorComponents)
		{
			child->Draw(ratio);
		}
	}
	
}

void MultiExtend::ActorComponent::CustomDraw()
{
	
}

void MultiExtend::ActorComponent::ProcessInput(const uint8_t* keyState)
{
	if (GetState(Tag_DISPLAY))
	{
		for (auto ac : m_ChildActorComponents)
		{
			ac->ProcessInput(keyState);
		}

		for (auto comp : m_Components)
		{
			comp->ProcessInput(keyState);
		}

		CustomInput(keyState);
	}
}

void MultiExtend::ActorComponent::CustomInput(const uint8_t* keyState)
{
}
