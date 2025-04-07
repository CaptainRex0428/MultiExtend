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
	m_State(State_VALID | State_INPUT | State_UPDATE | State_DISPLAY),
	m_parent_actor(nullptr),
	m_updateorder(updateorder),
	m_position(position),
	m_scale(scale),
	m_rotation(rotation)
{
	size_t len = std::strlen(tag);
	m_Tag = new char[len];
	memcpy(m_Tag, tag, len);

	SetTag(tag);

	m_ActorComponentRoot = new ActorComponent(DEFAULT_ROOTCOMPONENTTAG);
}

MultiExtend::Actor::~Actor()
{
	delete m_Tag;

	for (Actor * child : m_ChildActors)
	{
		child->ClearParentActor();
	}

	delete m_ActorComponentRoot;

	m_parent_actor->RemoveChildActor(this);
	m_parent_actor = nullptr;
}

void MultiExtend::Actor::SetTag(const char* tag)
{
	size_t len = std::strlen(tag);
	m_Tag = new char[len];
	memcpy(m_Tag, tag, len);
}

void MultiExtend::Actor::UpdateComponents(float delta)
{
	for (Component * component : m_Components)
	{
		component->Update(delta);
	}
}

void MultiExtend::Actor::AddComponent(BasicComponent* component)
{

	if (std::find(m_Components.begin(),
		m_Components.end(),
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

void MultiExtend::Actor::RemoveComponent(BasicComponent* component)
{
	auto it = std::remove_if(m_Components.begin(),
		m_Components.end(),
		[component](BasicComponent* comp) -> bool { return *component->GetTag() == *comp->GetTag(); });
	m_Components.erase(it);
	(*it)->SetOwner(nullptr);
}

void MultiExtend::Actor::UpdateChildActorComponents(float delta)
{
	m_ActorComponentRoot->Update(delta);
}

void MultiExtend::Actor::AddChildActorComponent(ActorComponent* actor_component)
{
	m_ActorComponentRoot->AddChildActorComponent(actor_component);
}

void MultiExtend::Actor::RemoveChildActorComponent(ActorComponent* actor_component)
{
	m_ActorComponentRoot->RemoveChildActorComponent(actor_component);
}

const std::vector<ActorComponent*>& MultiExtend::Actor::GetChildActorComponents() const
{
	return m_ActorComponentRoot->GetChildActorComponents();
}

void MultiExtend::Actor::AddChildActor(Actor* child)
{
	if (std::find(m_ChildActors.begin(),
		m_ChildActors.end(),
		child) == m_ChildActors.end())
	{

		child->DettachParentActor();

		int order = child->GetUpdateOrder();
		auto iter = m_ChildActors.begin();
		for (; iter != m_ChildActors.end(); ++iter)
		{
			if (order < (*iter)->GetUpdateOrder())
			{
				break;
			}
		}

		m_ChildActors.insert(iter, child);

		child->m_parent_actor = this;
	}
}

void MultiExtend::Actor::RemoveChildActor(Actor* child)
{
	auto it = std::remove_if(m_ChildActors.begin(),
		m_ChildActors.end(),
		[child](Actor* ch) -> bool { return *child->GetTag() == *ch->GetTag(); });
	m_ChildActors.erase(it);
}

void MultiExtend::Actor::UpdateChildActors(float delta)
{
	MULTIEXTEND_TIMER_TRACE_TAG(UpdateChildActors);

	for (auto actor : m_ChildActors)
	{
		actor->Update(delta);
	}
}

void MultiExtend::Actor::AttachParentActor(Actor* parent)
{
	if (std::find(m_ChildActors.begin(),
		m_ChildActors.end(),
		parent)
		== m_ChildActors.end())
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

MultiExtend::Actor* MultiExtend::Actor::GetParentActor() const
{
	return m_parent_actor;
}

const MultiExtend::Vector3& MultiExtend::Actor::GetPositionRelative() const
{
	return m_position;
}

const MultiExtend::Vector3& MultiExtend::Actor::GetRotationRelative() const
{
	return m_rotation;
}

const MultiExtend::Vector3& MultiExtend::Actor::GetScaleRelative() const
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

const MultiExtend::Vector3 MultiExtend::Actor::GetPositionAbsolute() const
{
	MULTIEXTEND_TIMER_TRACE_TAG(CalculateWorldPosition);

	float p_x = m_position[x];
	float p_y = m_position[y];
	float p_z = m_position[z];
	Actor* parent = GetParentActor();

	while (parent)
	{
		p_x += parent->GetPositionRelative()[x];
		p_y += parent->GetPositionRelative()[y];
		p_z += parent->GetPositionRelative()[z];

		parent = parent->GetParentActor();
	}

	return Vector3{p_x, p_y, p_z};
}

const MultiExtend::Vector3 MultiExtend::Actor::GetScaleAbsolute() const
{
	MULTIEXTEND_TIMER_TRACE_TAG(CalculateWorldScale);

	float scalesize_x = m_scale[x];
	float scalesize_y = m_scale[y];
	float scalesize_z = m_scale[z];
	Actor* parent = GetParentActor();

	while (parent)
	{
		scalesize_x *= parent->GetScaleRelative()[x];
		scalesize_y *= parent->GetScaleRelative()[y];
		scalesize_z *= parent->GetScaleRelative()[z];

		parent = parent->GetParentActor();
	}

	return Vector3{scalesize_x, scalesize_y, scalesize_z};
}

const MultiExtend::Vector3 MultiExtend::Actor::GetRotationAbsolute() const
{
	MULTIEXTEND_TIMER_TRACE_TAG(CalculateWorldRotation);

	float r_x = m_rotation[x];
	float r_y = m_rotation[y];
	float r_z = m_rotation[z];
	Actor* parent = GetParentActor();

	while (parent)
	{
		r_x *= parent->GetRotationRelative()[x];
		r_y *= parent->GetRotationRelative()[y];
		r_z *= parent->GetRotationRelative()[z];

		parent = parent->GetParentActor();
	}

	return Vector3{r_x, r_y, r_z};
}

const std::vector<MultiExtend::Actor*>& MultiExtend::Actor::GetChildActors() const
{
	return m_ChildActors;
}

MultiExtend::Actor* MultiExtend::Actor::GetChildActor(const char* actor_tag) const
{
	MULTIEXTEND_TIMER_TRACE_TAG(GetChildActor);

	for (auto actor : m_ChildActors)
	{
		if (*actor->m_Tag == *actor_tag)
		{
			return actor;
		}
	}

	return nullptr;
}

MultiExtend::ActorComponent* MultiExtend::Actor::GetChildActorComponent(const char* actor_component_tag) const
{
	return m_ActorComponentRoot->GetChildActorComponent(actor_component_tag);
}

MultiExtend::ActorComponent* MultiExtend::Actor::GetChildActorComponent(int actor_component_idx) const
{
	return m_ActorComponentRoot->GetChildActorComponent(actor_component_idx);
}

MultiExtend::ActorComponent* MultiExtend::Actor::GetActorComponentRoot() const
{
	return m_ActorComponentRoot;
}

void MultiExtend::Actor::SetActorComponentRoot(ActorComponent* actor_component)
{
	m_ActorComponentRoot = actor_component;
}

const std::vector<MultiExtend::BasicComponent*>& MultiExtend::Actor::GetComponents() const
{
	return m_Components;
}

MultiExtend::BasicComponent* MultiExtend::Actor::GetComponent(const char* component_tag) const
{
	MULTIEXTEND_TIMER_TRACE_TAG(GetComponent);

	for (auto component : m_Components)
	{
		if (*component->GetTag() == *component_tag)
		{
			return component;
		}
	}

	return nullptr;
}

const char* MultiExtend::Actor::GetTag() const
{
	return m_Tag;
}

const int& MultiExtend::Actor::GetUpdateOrder() const
{
	return m_updateorder;
}

void MultiExtend::Actor::Update(float delta)
{
	MULTIEXTEND_TIMER_TRACE_TAG(UpdateBasicActor);

	if(m_State & State::State_UPDATE)
	{
		CustomUpdate(delta);

		m_ActorComponentRoot->SetPositionRelative(m_position);
		m_ActorComponentRoot->SetScaleRelative(m_scale);
		m_ActorComponentRoot->SetRotationRelative(m_rotation);

		// std::cout << "in update actor:" << m_position << std::endl;
		// std::cout << "in update root:" << m_ActorComponentRoot->GetPositionRelative() << std::endl;

		UpdateChildActorComponents(delta);
		UpdateComponents(delta);
		UpdateChildActors(delta);
	}
}

void MultiExtend::Actor::CustomUpdate(float delta)
{
	
}

void MultiExtend::Actor::Draw()
{
	MULTIEXTEND_TIMER_TRACE_TAG(DrawBasicActor);
	
	if (m_State & State::State_DISPLAY)
	{
		CustomDraw();

		m_ActorComponentRoot->Draw();

		for (auto component : m_Components)
		{
			component->Draw();
		}

		for (auto child : m_ChildActors)
		{
			child->Draw();
		}
		
	}
}

void MultiExtend::Actor::CustomDraw()
{
	
}

void MultiExtend::Actor::ProcessInput(const uint8_t* keyState)
{
	if(m_State & State::State_INPUT)
	{
		for (auto comp : m_Components)
		{
			comp->ProcessInput(keyState);
		}

		for (auto childActor : m_ChildActors)
		{
			childActor->ProcessInput(keyState);
		}

		m_ActorComponentRoot->ProcessInput(keyState);
		
		CustomInput(keyState);
	}
}

void MultiExtend::Actor::CustomInput(const uint8_t* keyState)
{
	
}

void MultiExtend::Actor::SetUpdateOrder(int order)
{
	m_updateorder = order;

	// may need reorder
}

int MultiExtend::Actor::GetState() const
{
	return this->m_State;
}

bool MultiExtend::Actor::GetState(StateTag tag) const
{
	switch (tag)
	{
	
	case MultiExtend::Tag_VALID:
	{
		return m_State & State_VALID;
		break;
	}
		
	case MultiExtend::Tag_INPUT:
	{
		return m_State & State_INPUT;
		break;
	}

	case MultiExtend::Tag_UPDATE:
	{
		return m_State & State_UPDATE;
		break;
	}

	case MultiExtend::Tag_DISPLAY:
	default:
	{
		return m_State & State_DISPLAY;
		break;
	}

	}
}

void MultiExtend::Actor::SetState(int state)
{
	this->m_State = state;
}

void MultiExtend::Actor::ToggleState(StateTag tag)
{
	switch (tag)
	{

	case MultiExtend::Tag_VALID:
	{
		m_State ^= State_VALID;
		break;
	}

	case MultiExtend::Tag_INPUT:
	{
		m_State ^= State_INPUT;
		break;
	}

	case MultiExtend::Tag_UPDATE:
	{
		m_State ^= State_UPDATE;
		break;
	}

	case MultiExtend::Tag_DISPLAY:
	default:
	{
		m_State ^= State_DISPLAY;
		break;
	}

	}
}

