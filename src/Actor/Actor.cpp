#include "Actor/Actor.h"

Actor::Actor(const char* tag,
	Vector3 position,
	Vector3 scale,
	Vector3 rotation,
	int updateorder)
	:
	m_state(ATR_Alive),
	m_parent_actor(nullptr),
	m_updateorder(updateorder),
	m_position(position),
	m_scale(scale),
	m_rotation(rotation)
{
	size_t len = std::strlen(tag);
	m_actor_tag = new char[len];
	memcpy(m_actor_tag, tag, len);

	SetTag(tag);

	m_actor_component_root = new ActorComponent(DEFAULT_ROOTCOMPONENTTAG);
}

Actor::~Actor()
{
	delete m_actor_tag;

	for (auto child : m_child_actors)
	{
		child->ClearParentActor();
	}

	delete m_actor_component_root;

	m_parent_actor->RemoveChildActor(this);
	m_parent_actor = nullptr;
}

void Actor::SetTag(const char* tag)
{
	size_t len = std::strlen(tag);
	m_actor_tag = new char[len];
	memcpy(m_actor_tag, tag, len);
}

void Actor::UpdateComponents(float delta)
{
	for (auto component : m_components)
	{
		component->Update(delta);
	}
}

void Actor::AddComponent(Component* component)
{
	if (std::find(m_components.begin(),
		m_components.end(),
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

void Actor::RemoveComponent(Component* component)
{
	auto it = std::remove_if(m_components.begin(),
		m_components.end(),
		[component](Component* comp) -> bool { return *component->GetTag() == *comp->GetTag(); });
	m_components.erase(it);
}

void Actor::AddActorComponent(ActorComponent* actor_component)
{
	m_actor_component_root->AddChildActorComponent(actor_component);
}

void Actor::RemoveActorComponent(ActorComponent* actor_component)
{
	m_actor_component_root->RemoveChildActorComponent(actor_component);
}

void Actor::AddChildActor(Actor* child)
{
	if (std::find(m_child_actors.begin(),
		m_child_actors.end(),
		child) == m_child_actors.end())
	{
		int order = child->GetUpdateOrder();
		auto iter = m_child_actors.begin();
		for (; iter != m_child_actors.end(); ++iter)
		{
			if (order < (*iter)->GetUpdateOrder())
			{
				break;
			}
		}

		m_child_actors.insert(iter, child);
	}
}

void Actor::RemoveChildActor(Actor* child)
{
	auto it = std::remove_if(m_child_actors.begin(),
		m_child_actors.end(),
		[child](Actor* ch) -> bool { return *child->GetTag() == *ch->GetTag(); });
	m_child_actors.erase(it);
}

void Actor::UpdateChildActors(float delta)
{
	for (auto actor : m_child_actors)
	{
		actor->Update(delta);
	}
}

void Actor::AttachParentActor(Actor* parent)
{
	if (std::find(m_child_actors.begin(),
		m_child_actors.end(),
		parent)
		== m_child_actors.end())
	{
		if (m_parent_actor != parent)
		{
			if (m_parent_actor != nullptr)
			{
				m_parent_actor->RemoveChildActor(this);
			}

			parent->AddChildActor(this);

			m_parent_actor = parent;
		}

		return;
	}
#ifdef DEBUG
	std::cout << "Cannot attach parent actor to child actor." << std::endl;
#endif
}

void Actor::DettachParentActor()
{
	if (m_parent_actor != nullptr)
	{
		m_parent_actor->RemoveChildActor(this);
		m_parent_actor = nullptr;
	}
}

void Actor::ClearParentActor()
{
	if (m_parent_actor->GetParentActor() != nullptr)
	{
		m_parent_actor = m_parent_actor->GetParentActor();
		return;
	}

	m_parent_actor = nullptr;
}

Actor* Actor::GetParentActor()
{
	return m_parent_actor;
}

const Vector3& Actor::GetPosition()
{
	return m_position;
}

const Vector3& Actor::GetRotation()
{
	return m_rotation;
}

const Vector3& Actor::GetScale()
{
	return m_scale;
}

void Actor::SetPosition(Vector3 pos)
{
	m_position = pos;
}

void Actor::SetScale(Vector3 scale)
{
	m_scale = scale;
}

void Actor::SetRotation(Vector3 rotation)
{
	m_rotation = rotation;
}

const Vector3 Actor::GetPositionResult()
{
	float p_x = m_position.x;
	float p_y = m_position.y;
	float p_z = m_position.z;
	Actor* parent = GetParentActor();

	while (parent)
	{
		p_x += parent->GetPosition().x;
		p_y += parent->GetPosition().y;
		p_z += parent->GetPosition().z;

		parent = parent->GetParentActor();
	}

	return Vector3(p_x, p_y, p_z);
}

const Vector3 Actor::GetScaleResult()
{
	float scalesize_x = m_scale.x;
	float scalesize_y = m_scale.y;
	float scalesize_z = m_scale.z;
	Actor* parent = GetParentActor();

	while (parent)
	{
		scalesize_x *= parent->GetScale().x;
		scalesize_y *= parent->GetScale().y;
		scalesize_z *= parent->GetScale().z;

		parent = parent->GetParentActor();
	}

	return Vector3(scalesize_x, scalesize_y, scalesize_z);
}

const Vector3 Actor::GetRotationResult()
{
	float r_x = m_rotation.x;
	float r_y = m_rotation.y;
	float r_z = m_rotation.z;
	Actor* parent = GetParentActor();

	while (parent)
	{
		r_x *= parent->GetRotation().x;
		r_y *= parent->GetRotation().y;
		r_z *= parent->GetRotation().z;

		parent = parent->GetParentActor();
	}

	return Vector3(r_x, r_y, r_z);
}

MULTIEXTEND_API void Actor::SetActorState(int state)
{
	this->m_state = state;
}

const std::vector<Actor*>& Actor::GetChildActors()
{
	return m_child_actors;
}

Actor* Actor::GetChildActor(const char* actor_tag)
{
	for (auto actor : m_child_actors)
	{
		if (*actor->m_actor_tag == *actor_tag)
		{
			return actor;
		}
	}

	return nullptr;
}

ActorComponent* Actor::GetActorComponent(const char* actor_component_tag)
{
	m_actor_component_root->GetChildActorComponent(actor_component_tag);

	return nullptr;
}

ActorComponent* Actor::GetActorComponentRoot()
{
	return m_actor_component_root;
}

void Actor::SetActorComponentRoot(ActorComponent* actor_component)
{
	m_actor_component_root = actor_component;
}

const std::vector<Component*>& Actor::GetComponents()
{
	return m_components;
}

Component* Actor::GetComponent(const char* component_tag)
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

const char* Actor::GetTag()
{
	return m_actor_tag;
}

const int& Actor::GetUpdateOrder()
{
	return m_updateorder;
}

void Actor::Update(float delta)
{
	// update self

	m_actor_component_root->SetPosition(m_position);
	m_actor_component_root->SetScale(m_scale);
	m_actor_component_root->SetRotation(m_rotation);

	// std::cout << "in update actor:" << m_position << std::endl;
	// std::cout << "in update root:" << m_actor_component_root->GetPosition() << std::endl;

	m_actor_component_root->Update(delta);
	UpdateComponents(delta);
	UpdateChildActors(delta);
}

void Actor::Draw()
{
	m_actor_component_root->Draw();

	for (auto component : m_components)
	{
		component->Draw();
	}

	for (auto child : m_child_actors)
	{
		child->Draw();
	}
}

