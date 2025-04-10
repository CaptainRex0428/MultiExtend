#include "Object/Object.h"

MultiExtend::Object::Object()
{
	this->m_constructedTime = Clock::GetCurrentTime_gm();
}

MultiExtend::Object::~Object()
{
}

MULTIEXTEND_API const tm* MultiExtend::Object::GetConstructedTime()
{
	return this->m_constructedTime;
}
