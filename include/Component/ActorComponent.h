#pragma once

#include "MultiExtendAPI.h"
#include "ActorComponentConfig.h"

#include "API/IActorComponentOwner.h"

#include "Component.h"
#include "BasicComponent.h"

namespace MultiExtend
{
	class ActorComponent : public Component, public IActorComponentOwner
	{
	public:
		MULTIEXTEND_API ActorComponent(
			const char* tag = DEFAULT_ACTORCOMPONENTNAME,
			Vector3 postion = Vector3{0.0f, 0.0f, 0.0f},
			Vector3 scale = Vector3{1.0f, 1.0f, 1.0f},
			Vector3 rotation = Vector3{0.0f, 0.0f, 0.0f},
			int updateorder = DEFAULT_UPDATEORDER);
		MULTIEXTEND_API virtual ~ActorComponent();

		MULTIEXTEND_API void ProcessInput(const uint8_t* keyState) override;
		MULTIEXTEND_API virtual void CustomInput(const uint8_t* keyState) override;

		MULTIEXTEND_API void Update(float delta) override;
		MULTIEXTEND_API virtual void CustomUpdate(float delta) override;

		MULTIEXTEND_API void Draw(const float& ratio) override;
		MULTIEXTEND_API virtual void CustomDraw() override;

		MULTIEXTEND_API void UpdateComponents(float delta) override;
		MULTIEXTEND_API void AddComponent(BasicComponent* component) override;
		MULTIEXTEND_API void RemoveComponent(BasicComponent* component) override;
		MULTIEXTEND_API const std::vector<BasicComponent*>& GetComponents() const override;
		MULTIEXTEND_API BasicComponent* GetComponent(const char* component_tag) const override;

		MULTIEXTEND_API void UpdateChildActorComponents(float delta) override;
		MULTIEXTEND_API void AddChildActorComponent(ActorComponent* child) override;
		MULTIEXTEND_API void RemoveChildActorComponent(ActorComponent* child) override;
		MULTIEXTEND_API const std::vector<ActorComponent*>& GetChildActorComponents() const override;
		MULTIEXTEND_API ActorComponent* GetChildActorComponent(const char* component_tag) const override;
		MULTIEXTEND_API virtual ActorComponent* GetChildActorComponent(int component_idx) const override;

		MULTIEXTEND_API const Vector3& GetPositionRelative() const override;
		MULTIEXTEND_API const Vector3& GetScaleRelative() const override;
		MULTIEXTEND_API const Vector3& GetRotationRelative() const override;

		MULTIEXTEND_API void SetPositionRelative(Vector3 pos) override;
		MULTIEXTEND_API void SetScaleRelative(Vector3 scale) override;
		MULTIEXTEND_API void SetRotationRelative(Vector3 rotation) override;

		MULTIEXTEND_API const Vector3 GetPositionAbsolute() const override;
		MULTIEXTEND_API const Vector3 GetScaleAbsolute() const override;
		MULTIEXTEND_API const Vector3 GetRotationAbsolute() const override;

		MULTIEXTEND_API virtual void SetUpdateOrder(int order) override;

		MULTIEXTEND_API void AttachParentActorComponent(ActorComponent* parent);
		MULTIEXTEND_API void DettachParentActorComponent();
		MULTIEXTEND_API ActorComponent* GetParentActorComponent() const;

		MULTIEXTEND_API bool operator==(ActorComponent* other);

	protected:
		MULTIEXTEND_API void ClearParentActorComponent();

		MULTIEXTEND_API void SetParentActorComponent(ActorComponent* parent);

	protected:

		Vector3 m_position;
		Vector3 m_scale;
		Vector3 m_rotation;

	private:

		ActorComponent* m_ParentActorComponent;

		// need update & draw
		std::vector<BasicComponent*> m_Components;
		std::vector<ActorComponent*> m_ChildActorComponents;

	};
}