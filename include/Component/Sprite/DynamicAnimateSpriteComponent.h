#pragma once

#include <vector>

#include "MultiExtendAPI.h"
#include "SpriteComponent.h"

#include "DynamicAnimateSpriteComponentConfig.h"

namespace MultiExtend
{
	enum DynamicAnimateSpriteUnitUpdateType
	{
		LOOP,
		ONCE,
		CIRCLE
	};

	class DynamicAnimateSpriteUnit
	{
	public:
		MULTIEXTEND_API DynamicAnimateSpriteUnit(
			GameStat* gameStat,
			Renderer* renderer,
			std::vector<const char*> textureFilePaths,
			const char* groupTag,
			DynamicAnimateSpriteUnitUpdateType updateType = LOOP,
			DynamicAnimateSpriteUnit* animateUnitNext = nullptr);

		MULTIEXTEND_API DynamicAnimateSpriteUnit(
			std::vector<Texture*> textures,
			const char* groupTag,
			DynamicAnimateSpriteUnitUpdateType updateType = LOOP,
			DynamicAnimateSpriteUnit* animateUnitNext = nullptr);

		MULTIEXTEND_API virtual ~DynamicAnimateSpriteUnit();

		MULTIEXTEND_API const char* GetGroupTag() const;
		MULTIEXTEND_API void SetGroupTag(const char* tag);

		MULTIEXTEND_API DynamicAnimateSpriteUnitUpdateType GetUpdateType() const;
		MULTIEXTEND_API void SetUpdateType(DynamicAnimateSpriteUnitUpdateType updateType);

		MULTIEXTEND_API std::vector<Texture*> GetAnimateTextures() const;
		MULTIEXTEND_API void SetAnimateTextures(std::vector<Texture*>& textures);

		MULTIEXTEND_API DynamicAnimateSpriteUnit* GetAnimateUnitNext() const;
		MULTIEXTEND_API void SetAnimateUnitNext(DynamicAnimateSpriteUnit* animateUnitNext);

	private:
		const char* m_GroupTag;
		DynamicAnimateSpriteUnitUpdateType m_UpdateType;
		std::vector<Texture*> m_AnimateTextures;
		DynamicAnimateSpriteUnit* m_AnimateUnitNext;
	};

	class DynamicAnimateSpriteComponent : public SpriteComponent
	{
	public:

		MULTIEXTEND_API DynamicAnimateSpriteComponent(
			Renderer* renderer,
			std::vector<DynamicAnimateSpriteUnit*> dynamicAnimateSpriteUnits,
			float FPS = 60,
			const char* tag = BaseDynamicAnimSpriteComponentTypeName,
			Vector3 position = Vector3{0.0f, 0.0f, 0.0f},
			Vector3 scale = Vector3{1.0f, 1.0f, 1.0f},
			Vector3 rotation = Vector3{0.0f, 0.0f, 0.0f},
			Vector2 size = Vector2{32, 32},
			int updateorder = DEFAULT_UPDATEORDER);

		MULTIEXTEND_API virtual ~DynamicAnimateSpriteComponent();

		MULTIEXTEND_API virtual void Update(float delta) override;

		MULTIEXTEND_API virtual bool isFinished();
		MULTIEXTEND_API virtual bool bCanChangeCurrentUnit();

		MULTIEXTEND_API float GetAnimFPS() const;
		MULTIEXTEND_API void SetAnimFPS(float fps);

		MULTIEXTEND_API void SetCurrentDynamicSpriteUnit(int idx);
		MULTIEXTEND_API void SetCurrentDynamicSpriteUnit(const char * tag);

		MULTIEXTEND_API void SetDefaultDynamicSpriteUnit(int idx);
		MULTIEXTEND_API void SetDefaultDynamicSpriteUnit(const char* tag);

		MULTIEXTEND_API void AddAnimateSpriteUnit(DynamicAnimateSpriteUnit * dynamicAnimateSpriteUnit);
		MULTIEXTEND_API void RemoveAnimateSpriteUnit(DynamicAnimateSpriteUnit * dynamicAnimateSpriteUnit);

	private:
		MULTIEXTEND_API void SetCurrentFrame(float frame);

	private:
		std::vector<DynamicAnimateSpriteUnit*> m_DynamicAnimateSpriteUnits;

		DynamicAnimateSpriteUnit * m_DynamicAnimateSpriteUnit_Default;
		DynamicAnimateSpriteUnit * m_DynamicAnimateSpriteUnit_Current;

		float m_FPS;
		float m_currentFrame;

		bool bResetCurrentFrame;
	};
}