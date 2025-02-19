#pragma once

#include "Component.h"

#include "ActorComponentConfig.h"

#include "Math/Vector.h"

class ActorComponent : public Component
{
public:
	MULTIEXTEND_API ActorComponent(
		const char* tag = DEFAULT_ACTORCOMPONENTNAME,
		Vector3 postion = Vector3(0.0f, 0.0f, 0.0f),
		Vector3 scale = Vector3(1.0f, 1.0f, 1.0f),
		Vector3 rotation = Vector3(0.0f, 0.0f, 0.0f),
		int updateorder = DEFAULT_UPDATEORDER);
	MULTIEXTEND_API virtual ~ActorComponent();

	MULTIEXTEND_API virtual void Update(float delta) override;

	MULTIEXTEND_API virtual void Draw() override;

	MULTIEXTEND_API void UpdateComponents(float delta);
	MULTIEXTEND_API void AddComponent(Component* component);
	MULTIEXTEND_API void RemoveComponent(Component* component);
	MULTIEXTEND_API const std::vector<Component*>& GetComponents();
	MULTIEXTEND_API Component* GetComponent(const char* component_tag);

	MULTIEXTEND_API void UpdateChildActorComponents(float delta);
	MULTIEXTEND_API void AddChildActorComponent(ActorComponent* child);
	MULTIEXTEND_API void RemoveChildActorComponent(ActorComponent* child);
	MULTIEXTEND_API const std::vector<ActorComponent*>& GetChildActorComponents();
	MULTIEXTEND_API ActorComponent* GetChildActorComponent(const char* component_tag);

	MULTIEXTEND_API void AttachParentActorComponent(ActorComponent* parent);
	MULTIEXTEND_API void DettachParentActorComponent();
	MULTIEXTEND_API ActorComponent* GetParentActorComponent();

	MULTIEXTEND_API const Vector3& GetPosition();
	MULTIEXTEND_API const Vector3& GetScale();
	MULTIEXTEND_API const Vector3& GetRotation();

	MULTIEXTEND_API void SetPosition(Vector3 pos);
	MULTIEXTEND_API void SetScale(Vector3 scale);
	MULTIEXTEND_API void SetRotation(Vector3 rotation);

	MULTIEXTEND_API const Vector3 GetPositionResult();
	MULTIEXTEND_API const Vector3 GetScaleResult();
	MULTIEXTEND_API const Vector3 GetRotationResult();

	MULTIEXTEND_API bool operator==(ActorComponent* other);

protected:
	MULTIEXTEND_API void ClearParentActorComponent();

	MULTIEXTEND_API void SetParentActorComponent(ActorComponent* parent);

protected:

	Vector3 m_position;
	Vector3 m_scale;
	Vector3 m_rotation;

private:

	ActorComponent* m_parent_component;

	// need update & draw
	std::vector<Component*> m_components;
	std::vector<ActorComponent*> m_child_actor_components;

};