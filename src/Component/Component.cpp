#include "Component/Component.h"

#include <cstring>

MultiExtend::Component::Component(const char* name, int updateorder)
	:Object(),
	m_updateorder(updateorder),
	m_State(State_VALID | State_UPDATE | State_DISPLAY | State_INPUT)
{
	SetTag(name);
}

MultiExtend::Component::~Component()
{
	delete m_Tag;
}

const int& MultiExtend::Component::GetUpdateOrder() const
{
	return m_updateorder;
}

const char* MultiExtend::Component::GetTag() const
{
	return m_Tag;
}

void MultiExtend::Component::SetUpdateOrder(int order)
{
	m_updateorder = order;

	// may need reorder
}

void MultiExtend::Component::SetTag(const char * tag)
{
	size_t len = std::strlen(tag);
	m_Tag = new char[len];
	memcpy(m_Tag, tag, len);
}

int MultiExtend::Component::GetState() const
{
	return this->m_State;
}

bool MultiExtend::Component::GetState(StateTag tag) const
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

void MultiExtend::Component::SetState(int state)
{
	this->m_State = state;
}

void MultiExtend::Component::ToggleState(StateTag tag)
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
