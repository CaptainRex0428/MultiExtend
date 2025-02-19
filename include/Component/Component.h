#pragma once

#include <vector>

#include "MultiExtendAPI.h"

#include "Object/Object.h"

#include "ComponentConfig.h"

enum ComponentState 
{
	COMPONENT_Valid = 0b00000001,
	COMPONENT_Display = 0b00000010
};

class Component : public Object
{
public:
	MULTIEXTEND_API Component(
		const char* tag = DEFAULT_COMPONENTNAME,
		int updateorder = DEFAULT_UPDATEORDER);

	MULTIEXTEND_API virtual ~Component();

	MULTIEXTEND_API virtual void Update(float delta) = 0;
	MULTIEXTEND_API virtual void Draw() = 0;

	MULTIEXTEND_API int GetUpdateOrder() const;
	MULTIEXTEND_API const char* GetTag();
	MULTIEXTEND_API const int& GetComponentState();

	MULTIEXTEND_API void SetComponentState(int state);

protected:
	MULTIEXTEND_API virtual void SetTag(const char * type);

protected:
	int m_updateorder;

private:
	char* m_component_tag;
	int m_component_state;
};