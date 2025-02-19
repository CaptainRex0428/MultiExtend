#include "Object/Object.h"

Object::Object()
{
	this->m_hash = HashGenerator<Object>::generate(*this);
}

size_t Object::GetHash()
{
	return m_hash;
}

void Object::RefreshHash()
{
	this->m_hash = HashGenerator<Object>::generate(*this);
}
