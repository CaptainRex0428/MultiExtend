#pragma once

#include <vector>

#include "Component/ActorComponent.h"

#include "ActorConfig.h"

namespace MultiExtend
{
	enum ActorState
	{
		ATR_Alive = 0b00000001,
		ATR_EPaused = 0b00000010
	};

	class Actor : public Object
	{
	public:
		MULTIEXTEND_API Actor(const char* tag = DEFAULT_ACTORTAG,
			Vector3 position = Vector3(0.0f, 0.0f, 0.0f),
			Vector3 scale = Vector3(1.0f, 1.0f, 1.0f),
			Vector3 rotation = Vector3(0.0f, 0.0f, 0.0f),
			int updateorder = DEFAULT_UPDATEORDER_ACTOR);
		MULTIEXTEND_API virtual ~Actor();

		MULTIEXTEND_API virtual void Update(float delta);

		MULTIEXTEND_API virtual void Draw();

		MULTIEXTEND_API void UpdateComponents(float delta);
		MULTIEXTEND_API void AddComponent(Component* component);
		MULTIEXTEND_API void RemoveComponent(Component* component);
		MULTIEXTEND_API const std::vector<Component*>& GetComponents();
		MULTIEXTEND_API Component* GetComponent(const char* component_tag);

		MULTIEXTEND_API void AddActorComponent(ActorComponent* actor_component);
		MULTIEXTEND_API void RemoveActorComponent(ActorComponent* actor_component);
		MULTIEXTEND_API ActorComponent* GetActorComponent(const char* actor_component_tag);

		MULTIEXTEND_API ActorComponent* GetActorComponentRoot();
		MULTIEXTEND_API void SetActorComponentRoot(ActorComponent* actor_component);

		MULTIEXTEND_API void UpdateChildActors(float delta);
		MULTIEXTEND_API void AddChildActor(Actor* child);
		MULTIEXTEND_API void RemoveChildActor(Actor* child);
		MULTIEXTEND_API const std::vector<Actor*>& GetChildActors();
		MULTIEXTEND_API Actor* GetChildActor(const char* actor_tag);

		MULTIEXTEND_API void AttachParentActor(Actor* parent);
		MULTIEXTEND_API void DettachParentActor();
		MULTIEXTEND_API Actor* GetParentActor();

		MULTIEXTEND_API const char* GetTag();
		MULTIEXTEND_API const int& GetUpdateOrder();

		MULTIEXTEND_API const Vector3& GetPositionRelative();
		MULTIEXTEND_API const Vector3& GetRotationRelative();
		MULTIEXTEND_API const Vector3& GetScaleRelative();

		MULTIEXTEND_API void SetPosition(Vector3 pos);
		MULTIEXTEND_API void SetScale(Vector3 scale);
		MULTIEXTEND_API void SetRotation(Vector3 rotation);

		MULTIEXTEND_API const Vector3 GetPositionAbsolute();
		MULTIEXTEND_API const Vector3 GetScaleAbsolute();
		MULTIEXTEND_API const Vector3 GetRotationAbsolute();

		MULTIEXTEND_API void SetActorState(int state);

	protected:
		MULTIEXTEND_API virtual void SetTag(const char* tag);
		MULTIEXTEND_API void ClearParentActor();

	protected:
		Vector3 m_position;
		Vector3 m_rotation;
		Vector3 m_scale;


	private:
		int m_state;

		int m_updateorder;

		char* m_actor_tag;

		Actor* m_parent_actor;

		// need update and draw

		ActorComponent* m_actor_component_root;

		std::vector<Component*> m_components;

		std::vector<Actor*> m_child_actors;

	};

}

