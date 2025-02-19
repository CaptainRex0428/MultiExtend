#include "Object/Object.h"

MultiExtend::Object::Object()
{
	this->m_hash = MultiExtend::HashGenerator<Object>::generate(*this);
}

size_t MultiExtend::Object::GetHash()
{
	return m_hash;
}

void MultiExtend::Object::RefreshHash()
{
	this->m_hash = MultiExtend::HashGenerator<Object>::generate(*this);
}
