#include "MultiExtend.h"
#include "Actor/Actor.h"
#include "Object/GameStat.h"

#include "Component/BasicComponent.h"

MultiExtend::Actor::Actor(const char* tag,
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

MultiExtend::Actor::~Actor()
{
	delete m_actor_tag;

	for (Actor * child : m_child_actors)
	{
		child->ClearParentActor();
	}

	delete m_actor_component_root;

	m_parent_actor->RemoveChildActor(this);
	m_parent_actor = nullptr;
}

void MultiExtend::Actor::SetTag(const char* tag)
{
	size_t len = std::strlen(tag);
	m_actor_tag = new char[len];
	memcpy(m_actor_tag, tag, len);
}

void MultiExtend::Actor::UpdateComponents(float delta)
{
	for (Component * component : m_components)
	{
		component->Update(delta);
	}
}

void MultiExtend::Actor::AddComponent(BasicComponent* component)
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

		component->SetOwner(this);
	}
}

void MultiExtend::Actor::RemoveComponent(BasicComponent* component)
{
	auto it = std::remove_if(m_components.begin(),
		m_components.end(),
		[component](BasicComponent* comp) -> bool { return *component->GetTag() == *comp->GetTag(); });
	m_components.erase(it);
	(*it)->SetOwner(nullptr);
}

void MultiExtend::Actor::AddActorComponent(ActorComponent* actor_component)
{
	m_actor_component_root->AddChildActorComponent(actor_component);
}

void MultiExtend::Actor::RemoveActorComponent(ActorComponent* actor_component)
{
	m_actor_component_root->RemoveChildActorComponent(actor_component);
}

void MultiExtend::Actor::AddChildActor(Actor* child)
{
	if (std::find(m_child_actors.begin(),
		m_child_actors.end(),
		child) == m_child_actors.end())
	{

		child->DettachParentActor();

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

		child->m_parent_actor = this;
	}
}

void MultiExtend::Actor::RemoveChildActor(Actor* child)
{
	auto it = std::remove_if(m_child_actors.begin(),
		m_child_actors.end(),
		[child](Actor* ch) -> bool { return *child->GetTag() == *ch->GetTag(); });
	m_child_actors.erase(it);
}

void MultiExtend::Actor::UpdateChildActors(float delta)
{
	MULTIEXTEND_TIMER_TRACE_TAG(UpdateChildActors);

	for (auto actor : m_child_actors)
	{
		actor->Update(delta);
	}
}

void MultiExtend::Actor::AttachParentActor(Actor* parent)
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

void MultiExtend::Actor::DettachParentActor()
{
	if (m_parent_actor != nullptr)
	{
		m_parent_actor->RemoveChildActor(this);
		m_parent_actor = nullptr;
	}
}

void MultiExtend::Actor::ClearParentActor()
{
	if (m_parent_actor->GetParentActor() != nullptr)
	{
		m_parent_actor = m_parent_actor->GetParentActor();
		return;
	}

	m_parent_actor = nullptr;
}

MultiExtend::Actor* MultiExtend::Actor::GetParentActor()
{
	return m_parent_actor;
}

const MultiExtend::Vector3& MultiExtend::Actor::GetPositionRelative()
{
	return m_position;
}

const MultiExtend::Vector3& MultiExtend::Actor::GetRotationRelative()
{
	return m_rotation;
}

const MultiExtend::Vector3& MultiExtend::Actor::GetScaleRelative()
{
	return m_scale;
}

void MultiExtend::Actor::SetPositionRelative(Vector3 pos)
{
	m_position = pos;
}

void MultiExtend::Actor::SetScaleRelative(Vector3 scale)
{
	m_scale = scale;
}

void MultiExtend::Actor::SetRotationRelative(Vector3 rotation)
{
	m_rotation = rotation;
}

const MultiExtend::Vector3 MultiExtend::Actor::GetPositionAbsolute()
{
	MULTIEXTEND_TIMER_TRACE_TAG(CalculateWorldPosition);

	float p_x = m_position.x;
	float p_y = m_position.y;
	float p_z = m_position.z;
	Actor* parent = GetParentActor();

	while (parent)
	{
		p_x += parent->GetPositionRelative().x;
		p_y += parent->GetPositionRelative().y;
		p_z += parent->GetPositionRelative().z;

		parent = parent->GetParentActor();
	}

	return Vector3{p_x, p_y, p_z};
}

const MultiExtend::Vector3 MultiExtend::Actor::GetScaleAbsolute()
{
	MULTIEXTEND_TIMER_TRACE_TAG(CalculateWorldScale);

	float scalesize_x = m_scale.x;
	float scalesize_y = m_scale.y;
	float scalesize_z = m_scale.z;
	Actor* parent = GetParentActor();

	while (parent)
	{
		scalesize_x *= parent->GetScaleRelative().x;
		scalesize_y *= parent->GetScaleRelative().y;
		scalesize_z *= parent->GetScaleRelative().z;

		parent = parent->GetParentActor();
	}

	return Vector3{scalesize_x, scalesize_y, scalesize_z};
}

const MultiExtend::Vector3 MultiExtend::Actor::GetRotationAbsolute()
{
	MULTIEXTEND_TIMER_TRACE_TAG(CalculateWorldRotation);

	float r_x = m_rotation.x;
	float r_y = m_rotation.y;
	float r_z = m_rotation.z;
	Actor* parent = GetParentActor();

	while (parent)
	{
		r_x *= parent->GetRotationRelative().x;
		r_y *= parent->GetRotationRelative().y;
		r_z *= parent->GetRotationRelative().z;

		parent = parent->GetParentActor();
	}

	return Vector3{r_x, r_y, r_z};
}

MULTIEXTEND_API void MultiExtend::Actor::SetActorState(int state)
{

	this->m_state = state;
}

const std::vector<MultiExtend::Actor*>& MultiExtend::Actor::GetChildActors()
{
	return m_child_actors;
}

MultiExtend::Actor* MultiExtend::Actor::GetChildActor(const char* actor_tag)
{
	MULTIEXTEND_TIMER_TRACE_TAG(GetChildActor);

	for (auto actor : m_child_actors)
	{
		if (*actor->m_actor_tag == *actor_tag)
		{
			return actor;
		}
	}

	return nullptr;
}

MultiExtend::ActorComponent* MultiExtend::Actor::GetActorComponent(const char* actor_component_tag)
{
	return m_actor_component_root->GetChildActorComponent(actor_component_tag);
}

MultiExtend::ActorComponent* MultiExtend::Actor::GetActorComponentRoot()
{
	return m_actor_component_root;
}

void MultiExtend::Actor::SetActorComponentRoot(ActorComponent* actor_component)
{
	m_actor_component_root = actor_component;
}

const std::vector<MultiExtend::BasicComponent*>& MultiExtend::Actor::GetComponents()
{
	return m_components;
}

MultiExtend::BasicComponent* MultiExtend::Actor::GetComponent(const char* component_tag)
{
	MULTIEXTEND_TIMER_TRACE_TAG(GetComponent);

	for (auto component : m_components)
	{
		if (*component->GetTag() == *component_tag)
		{
			return component;
		}
	}

	return nullptr;
}

const char* MultiExtend::Actor::GetTag()
{
	return m_actor_tag;
}

const int& MultiExtend::Actor::GetUpdateOrder()
{
	return m_updateorder;
}

void MultiExtend::Actor::Update(float delta)
{
	MULTIEXTEND_TIMER_TRACE_TAG(UpdateBasicActor);

	// update self

	m_actor_component_root->SetPositionRelative(m_position);
	m_actor_component_root->SetScaleRelative(m_scale);
	m_actor_component_root->SetRotationRelative(m_rotation);

	// std::cout << "in update actor:" << m_position << std::endl;
	// std::cout << "in update root:" << m_actor_component_root->GetPositionRelative() << std::endl;

	m_actor_component_root->Update(delta);
	UpdateComponents(delta);
	UpdateChildActors(delta);
}

void MultiExtend::Actor::Draw()
{
	MULTIEXTEND_TIMER_TRACE_TAG(DrawBasicActor);

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

void MultiExtend::Actor::SetUpdateOrder(int order)
{
	m_updateorder = order;

	// may need reorder
}

