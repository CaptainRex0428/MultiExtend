#include "Component/Component.h"

#include <cstring>

MultiExtend::Component::Component(const char* name, int updateorder)
	:Object(),
	m_updateorder(updateorder),m_component_state(COMPONENT_Valid | COMPONENT_Display)
{
	SetTag(name);
}

MultiExtend::Component::~Component()
{
	delete m_component_tag;
}

int MultiExtend::Component::GetUpdateOrder() const
{
	return m_updateorder;
}

const char* MultiExtend::Component::GetTag()
{
	return m_component_tag;
}

void MultiExtend::Component::SetComponentState(int state)
{
	m_component_state = state;
}

const int& MultiExtend::Component::GetComponentState()
{
	return m_component_state;
}

MULTIEXTEND_API void MultiExtend::Component::SetUpdateOrder(int order)
{
	m_updateorder = order;

	// may need reorder
}

void MultiExtend::Component::SetTag(const char * tag)
{
	size_t len = std::strlen(tag);
	m_component_tag = new char[len];
	memcpy(m_component_tag, tag, len);
}
