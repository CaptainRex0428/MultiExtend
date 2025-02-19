#include "Component/Component.h"

#include <cstring>

Component::Component(const char* name, int updateorder)
	:Object(),
	m_updateorder(updateorder),m_component_state(COMPONENT_Valid | COMPONENT_Display)
{
	SetTag(name);
}

Component::~Component()
{
	delete m_component_tag;
}

int Component::GetUpdateOrder() const
{
	return m_updateorder;
}

const char* Component::GetTag()
{
	return m_component_tag;
}

void Component::SetComponentState(int state)
{
	m_component_state = state;
}

const int& Component::GetComponentState()
{
	return m_component_state;
}

void Component::SetTag(const char * tag)
{
	size_t len = std::strlen(tag);
	m_component_tag = new char[len];
	memcpy(m_component_tag, tag, len);
}
