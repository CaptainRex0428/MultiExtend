#include "Component/ActorComponent.h"


#include "Component/ActorComponent.h"

MultiExtend::ActorComponent::ActorComponent(
	const char* tag,
	Vector3 position,
	Vector3 scale,
	Vector3 rotation,
	int updateorder)
	:
	Component(tag, updateorder),
	m_parent_component(nullptr),
	m_position(position),
	m_scale(scale),
	m_rotation(rotation)
{
}

MultiExtend::ActorComponent::~ActorComponent()
{
	for (auto actor_component : m_child_actor_components)
	{
		actor_component->ClearParentActorComponent();
	}

	m_parent_component->RemoveChildActorComponent(this);
	m_parent_component = nullptr;
}

void MultiExtend::ActorComponent::UpdateComponents(float delta)
{
	for (auto component : m_components)
	{
		component->Update(delta);
	}
}

void MultiExtend::ActorComponent::AddComponent(MultiExtend::Component* component)
{
	if (std::find(m_components.begin(), m_components.end(),
		component) == m_components.end())
	{
		int order = component->GetUpdateOrder();
		auto iter = m_components.begin();
		for (; iter != m_components.end(); ++iter)
		{
			if (order < (*iter)->GetUpdateOrder())
			{
				break;
			}
		}

		m_components.insert(iter, component);
	}
}

void MultiExtend::ActorComponent::RemoveComponent(MultiExtend::Component* component)
{
	auto it = std::remove_if(m_components.begin(), m_components.end(),
		[component](Component* comp) -> bool {return *component->GetTag() == *comp->GetTag(); });
	m_components.erase(it);
}

const std::vector<MultiExtend::Component*>& MultiExtend::ActorComponent::GetComponents()
{
	return m_components;
}

MultiExtend::Component* MultiExtend::ActorComponent::GetComponent(const char* component_tag)
{
	for (auto component : m_components)
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
	for (auto child : m_child_actor_components)
	{
		child->Update(delta);
	}
}

void MultiExtend::ActorComponent::AddChildActorComponent(MultiExtend::ActorComponent* child)
{
	if (std::find(m_child_actor_components.begin(),
		m_child_actor_components.end(),
		child) == m_child_actor_components.end())
	{
		int order = child->GetUpdateOrder();
		auto iter = m_child_actor_components.begin();

		for (; iter != m_child_actor_components.end(); ++iter)
		{
			if (order < (*iter)->GetUpdateOrder())
			{
				break;
			}
		}

		m_child_actor_components.insert(iter, child);
		child->SetParentActorComponent(this);

		
	}
}

void MultiExtend::ActorComponent::SetParentActorComponent(ActorComponent* parent)
{
	m_parent_component = parent;
}

void MultiExtend::ActorComponent::RemoveChildActorComponent(ActorComponent* child)
{
	auto it = std::remove_if(m_child_actor_components.begin(),
		m_child_actor_components.end(),
		[child](ActorComponent* ch) -> bool { return *child->GetTag() == *ch->GetTag(); });
	m_child_actor_components.erase(it);
}

const std::vector<MultiExtend::ActorComponent*>& MultiExtend::ActorComponent::GetChildActorComponents()
{
	return m_child_actor_components;
}

MultiExtend::ActorComponent* MultiExtend::ActorComponent::GetChildActorComponent(const char* component_tag)
{
	for (auto child : m_child_actor_components)
	{
		if (*child->GetTag() == *component_tag)
		{
			return child;
		}
	}

	return nullptr;
}

void MultiExtend::ActorComponent::AttachParentActorComponent(MultiExtend::ActorComponent* parent)
{
	if (std::find(m_child_actor_components.begin(),
		m_child_actor_components.end(),
		parent) == m_child_actor_components.end())
	{
		if (m_parent_component != parent)
		{
			if (m_parent_component != nullptr)
			{
				m_parent_component->RemoveChildActorComponent(this);
			}

			parent->AddChildActorComponent(this);

			m_parent_component = parent;
		}

		return;
	}
#ifdef DEBUG
	std::cout << "Cannot attach parent actor component to child actor component." << std::endl;
#endif
}

void MultiExtend::ActorComponent::DettachParentActorComponent()
{
	if (m_parent_component != nullptr)
	{
		m_parent_component->RemoveChildActorComponent(this);
		m_parent_component = nullptr;
	}
}

MultiExtend::ActorComponent* MultiExtend::ActorComponent::GetParentActorComponent()
{
	return m_parent_component;
}

const MultiExtend::Vector3& MultiExtend::ActorComponent::GetPositionRelative()
{
	return m_position;
}

const MultiExtend::Vector3& MultiExtend::ActorComponent::GetScaleRelative()
{
	return m_scale;
}

const MultiExtend::Vector3& MultiExtend::ActorComponent::GetRotationRelative()
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

const MultiExtend::Vector3 MultiExtend::ActorComponent::GetPositionAbsolute()
{


	float p_x = m_position.x;
	float p_y = m_position.y;
	float p_z = m_position.z;

	MultiExtend::ActorComponent* parent = GetParentActorComponent();

	while (parent)
	{
		p_x += parent->GetPositionRelative().x;
		p_y += parent->GetPositionRelative().y;
		p_z += parent->GetPositionRelative().z;

		parent = parent->GetParentActorComponent();
	}

	return Vector3(p_x, p_y, p_z);

}

const MultiExtend::Vector3 MultiExtend::ActorComponent::GetScaleAbsolute()
{
	float scalesize_x = m_scale.x;
	float scalesize_y = m_scale.y;
	float scalesize_z = m_scale.z;
	ActorComponent* parent = GetParentActorComponent();

	while (parent)
	{
		scalesize_x *= parent->GetScaleRelative().x;
		scalesize_y *= parent->GetScaleRelative().y;
		scalesize_z *= parent->GetScaleRelative().z;

		parent = parent->GetParentActorComponent();
	}

	return Vector3(scalesize_x, scalesize_y, scalesize_z);

}

const MultiExtend::Vector3 MultiExtend::ActorComponent::GetRotationAbsolute()
{
	float r_x = m_rotation.x;
	float r_y = m_rotation.y;
	float r_z = m_rotation.z;
	ActorComponent* parent = GetParentActorComponent();

	while (parent)
	{
		r_x *= parent->GetRotationRelative().x;
		r_y *= parent->GetRotationRelative().y;
		r_z *= parent->GetRotationRelative().z;

		parent = parent->GetParentActorComponent();
	}

	return Vector3(r_x, r_y, r_z);

}

MULTIEXTEND_API void MultiExtend::ActorComponent::SetUpdateOrder(int order)
{
	Component::SetUpdateOrder(order);

	// may reorder
}

bool MultiExtend::ActorComponent::operator==(ActorComponent* other)
{
	return this->GetTag() == other->GetTag();;
}

void MultiExtend::ActorComponent::ClearParentActorComponent()
{
	if (m_parent_component->GetParentActorComponent() != nullptr)
	{
		m_parent_component = m_parent_component->GetParentActorComponent();
		return;
	}

	m_parent_component = nullptr;
}

void MultiExtend::ActorComponent::Update(float delta)
{
	// update self

	for (auto child : m_child_actor_components)
	{
		child->Update(delta);
	}

	for (auto component : m_components)
	{
		component->Update(delta);
	}

	return;
}

void MultiExtend::ActorComponent::Draw()
{
	// draw self

	for (auto component : m_components)
	{
		component->Draw();
	}

	for (auto child : m_child_actor_components)
	{
		child->Draw();
	}
}