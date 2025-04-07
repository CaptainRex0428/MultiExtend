#pragma once

#include <vector>

#include "ActorConfig.h"

#include "API/IActorComponentOwner.h"
#include "API/IBasic.h"
#include "API/IInput.h"
#include "API/IUpdate.h"
#include "API/IDraw.h"

#include "Component/ActorComponent.h"
#include "Component/BasicComponent.h"

namespace MultiExtend
{

	class Actor : public Object, public IBasic, public IActorComponentOwner, public IInput, public IUpdate, public IDraw
	{
	public:
		MULTIEXTEND_API Actor(const char* tag = DEFAULT_ACTORTAG,
			Vector3 position = Vector3{0.0f, 0.0f, 0.0f},
			Vector3 scale = Vector3{1.0f, 1.0f, 1.0f},
			Vector3 rotation = Vector3{0.0f, 0.0f, 0.0f},
			int updateorder = DEFAULT_UPDATEORDER_ACTOR);
		MULTIEXTEND_API virtual ~Actor();

		MULTIEXTEND_API void Update(float delta) override;
		MULTIEXTEND_API virtual void CustomUpdate(float delta) override;

		MULTIEXTEND_API void Draw() override;
		MULTIEXTEND_API virtual void CustomDraw() override;

		MULTIEXTEND_API void ProcessInput(const uint8_t * keyState) override;
		MULTIEXTEND_API virtual void CustomInput(const uint8_t * keyState) override;

		MULTIEXTEND_API void UpdateComponents(float delta) override;
		MULTIEXTEND_API void AddComponent(BasicComponent* component) override;
		MULTIEXTEND_API void RemoveComponent(BasicComponent* component) override;
		MULTIEXTEND_API const std::vector<BasicComponent*>& GetComponents() const override;
		MULTIEXTEND_API BasicComponent* GetComponent(const char* component_tag) const override;

		MULTIEXTEND_API virtual void UpdateChildActorComponents(float delta) override;
		MULTIEXTEND_API void AddChildActorComponent(ActorComponent* actor_component) override;
		MULTIEXTEND_API void RemoveChildActorComponent(ActorComponent* actor_component) override;
		MULTIEXTEND_API virtual const std::vector<ActorComponent*>& GetChildActorComponents() const override;
		MULTIEXTEND_API ActorComponent* GetChildActorComponent(const char* actor_component_tag) const override;
		MULTIEXTEND_API ActorComponent* GetChildActorComponent(int actor_component_idx) const override;		

		MULTIEXTEND_API virtual const char* GetTag() const override;
		MULTIEXTEND_API virtual void SetTag(const char* tag) override;
		MULTIEXTEND_API virtual const int& GetUpdateOrder() const override;
		MULTIEXTEND_API virtual void SetUpdateOrder(int order) override;

		MULTIEXTEND_API virtual int  GetState() const override;
		MULTIEXTEND_API virtual bool GetState(StateTag tag) const override;
		MULTIEXTEND_API virtual void SetState(int state) override;
		MULTIEXTEND_API virtual void ToggleState(StateTag tag) override;

		MULTIEXTEND_API const Vector3& GetPositionRelative() const override;
		MULTIEXTEND_API const Vector3& GetRotationRelative() const override;
		MULTIEXTEND_API const Vector3& GetScaleRelative() const override;

		MULTIEXTEND_API void SetPositionRelative(Vector3 pos) override;
		MULTIEXTEND_API void SetScaleRelative(Vector3 scale) override;
		MULTIEXTEND_API void SetRotationRelative(Vector3 rotation) override;

		MULTIEXTEND_API const Vector3 GetPositionAbsolute() const override;
		MULTIEXTEND_API const Vector3 GetScaleAbsolute() const override;
		MULTIEXTEND_API const Vector3 GetRotationAbsolute() const override;

		MULTIEXTEND_API ActorComponent* GetActorComponentRoot() const;
		MULTIEXTEND_API void SetActorComponentRoot(ActorComponent* actor_component);

		MULTIEXTEND_API void UpdateChildActors(float delta);
		MULTIEXTEND_API void AddChildActor(Actor* child);
		MULTIEXTEND_API void RemoveChildActor(Actor* child);
		MULTIEXTEND_API const std::vector<Actor*>& GetChildActors() const;
		MULTIEXTEND_API Actor* GetChildActor(const char* actor_tag) const;

		MULTIEXTEND_API void AttachParentActor(Actor* parent);
		MULTIEXTEND_API void DettachParentActor();
		MULTIEXTEND_API Actor* GetParentActor() const;

	protected:
		MULTIEXTEND_API void ClearParentActor();

	protected:
		Vector3 m_position;
		Vector3 m_rotation;
		Vector3 m_scale;

	private:
		int m_State;

		int m_updateorder;

		char* m_Tag;

		Actor* m_parent_actor;

		// need update and draw

		ActorComponent* m_ActorComponentRoot;
		std::vector<BasicComponent*> m_Components;
		std::vector<Actor*> m_ChildActors;

	};

}

