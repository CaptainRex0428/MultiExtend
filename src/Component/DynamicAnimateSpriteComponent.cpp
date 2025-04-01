#include "Component/DynamicAnimateSpriteComponent.h"
#include "MultiExtend.h"
#include "Math/Math.h"

MultiExtend::DynamicAnimateSpriteUnit::DynamicAnimateSpriteUnit(
	GameStat* gameStat,
	Renderer* renderer,
	std::vector<const char*> textureFilePaths,
	const char* groupTag,
	DynamicAnimateSpriteUnitUpdateType updateType,
	DynamicAnimateSpriteUnit* animateUnitNext)
	:m_GroupTag(groupTag),
	m_UpdateType(updateType),
	m_AnimateUnitNext(animateUnitNext)
{
	m_AnimateTextures.clear();

	auto iter = textureFilePaths.begin();
	for (; iter != textureFilePaths.end(); ++iter)
	{
		Texture* texture = MultiExtend::LoadTexture(gameStat, renderer, *iter);
		m_AnimateTextures.emplace_back(texture);
	};
}

MultiExtend::DynamicAnimateSpriteUnit::DynamicAnimateSpriteUnit(
	std::vector<Texture*> textures,
	const char* groupTag,
	DynamicAnimateSpriteUnitUpdateType updateType,
	DynamicAnimateSpriteUnit* animateUnitNext)
	:m_GroupTag(groupTag),
	m_UpdateType(updateType),
	m_AnimateTextures(textures),
	m_AnimateUnitNext(animateUnitNext)
{
}

MultiExtend::DynamicAnimateSpriteUnit::~DynamicAnimateSpriteUnit()
{
}

const char* MultiExtend::DynamicAnimateSpriteUnit::GetGroupTag() const
{
	return m_GroupTag;
}

void MultiExtend::DynamicAnimateSpriteUnit::SetGroupTag(const char* tag)
{
	m_GroupTag = tag;
}

MultiExtend::DynamicAnimateSpriteUnitUpdateType MultiExtend::DynamicAnimateSpriteUnit::GetUpdateType() const
{
	return m_UpdateType;
}

void MultiExtend::DynamicAnimateSpriteUnit::SetUpdateType(DynamicAnimateSpriteUnitUpdateType updateType)
{
	m_UpdateType = updateType;
}

std::vector<Texture*> MultiExtend::DynamicAnimateSpriteUnit::GetAnimateTextures() const
{
	return m_AnimateTextures;
}

void MultiExtend::DynamicAnimateSpriteUnit::SetAnimateTextures(std::vector<Texture*>& textures)
{
	if (textures.size() > 0)
	{
		m_AnimateTextures = textures;
	}
}

MultiExtend::DynamicAnimateSpriteUnit* MultiExtend::DynamicAnimateSpriteUnit::GetAnimateUnitNext() const
{
	return m_AnimateUnitNext;
}

void MultiExtend::DynamicAnimateSpriteUnit::SetAnimateUnitNext(DynamicAnimateSpriteUnit* animateUnitNext)
{
	this->m_AnimateUnitNext = animateUnitNext;
}

MultiExtend::DynamicAnimateSpriteComponent::DynamicAnimateSpriteComponent(
	Renderer* renderer, 
	std::vector<DynamicAnimateSpriteUnit*> dynamicAnimateSpriteUnits, 
	float FPS, const char* tag, 
	Vector3 position, 
	Vector3 scale, 
	Vector3 rotation, 
	Vector2 size, 
	int updateorder)
	:SpriteComponent(renderer, dynamicAnimateSpriteUnits[0]->GetAnimateTextures()[0], tag, position, scale, rotation, size, updateorder),
	m_FPS(FPS),
	m_currentFrame(0),
	bResetCurrentFrame(false),
	m_DynamicAnimateSpriteUnit_Default(dynamicAnimateSpriteUnits[0]),
	m_DynamicAnimateSpriteUnit_Current(dynamicAnimateSpriteUnits[0]),
	m_DynamicAnimateSpriteUnits(dynamicAnimateSpriteUnits)
{
}

MultiExtend::DynamicAnimateSpriteComponent::~DynamicAnimateSpriteComponent()
{
}

void MultiExtend::DynamicAnimateSpriteComponent::Update(float delta)
{
	if (m_DynamicAnimateSpriteUnit_Current->GetAnimateTextures().size() > 0)
	{
		if(m_DynamicAnimateSpriteUnit_Current->GetUpdateType() == ONCE && isFinished())
		{
			auto next = m_DynamicAnimateSpriteUnit_Current->GetAnimateUnitNext();

			m_DynamicAnimateSpriteUnit_Current =  next ? next : m_DynamicAnimateSpriteUnit_Default;
			
			SetCurrentFrame(0);
		}
		else if (this->bResetCurrentFrame)
		{
			SetCurrentFrame(0);
			this->bResetCurrentFrame = false;
		}
		else
		{
			SetCurrentFrame(m_currentFrame + m_FPS * delta);
		}
		
		size_t resetIdx = (int)m_currentFrame;
		resetIdx = resetIdx < m_DynamicAnimateSpriteUnit_Current->GetAnimateTextures().size() ? resetIdx : (m_DynamicAnimateSpriteUnit_Current->GetAnimateTextures().size() - 1);
		SpriteComponent::SetTexture(m_DynamicAnimateSpriteUnit_Current->GetAnimateTextures()[resetIdx]);

		// MULTIEXTEND_MESSAGE_CLIENT_DEBUG(m_DynamicAnimateSpriteUnit_Current->GetAnimateTextures().size());
		// MULTIEXTEND_MESSAGE_CLIENT_DEBUG(m_DynamicAnimateSpriteUnit_Current->GetAnimateTextures()[resetIdx]->GetHash());
	}

	SpriteComponent::Update(delta);
}

bool MultiExtend::DynamicAnimateSpriteComponent::isFinished()
{
	return m_DynamicAnimateSpriteUnit_Current->GetUpdateType() == ONCE && (int)m_currentFrame == m_DynamicAnimateSpriteUnit_Current->GetAnimateTextures().size()-1;
}

bool MultiExtend::DynamicAnimateSpriteComponent::bCanChangeCurrentUnit()
{
	return m_DynamicAnimateSpriteUnit_Current->GetUpdateType() == LOOP || isFinished();
}

float MultiExtend::DynamicAnimateSpriteComponent::GetAnimFPS() const
{
	return m_FPS;
}

void MultiExtend::DynamicAnimateSpriteComponent::SetAnimFPS(float fps)
{
	m_FPS = fps > 0 ? fps : 0;
}

void MultiExtend::DynamicAnimateSpriteComponent::SetCurrentDynamicSpriteUnit(int idx)
{
	if(bCanChangeCurrentUnit())
	{
		MultiExtend::Math::limit_max(idx,(int)m_DynamicAnimateSpriteUnits.size()-1);

		this->m_DynamicAnimateSpriteUnit_Current = m_DynamicAnimateSpriteUnits[idx];
		this->bResetCurrentFrame = true;
	}
}

void MultiExtend::DynamicAnimateSpriteComponent::SetCurrentDynamicSpriteUnit(const char* tag)
{

	// MULTIEXTEND_MESSAGE_CLIENT_DEBUG(this->m_DynamicAnimateSpriteUnits.size());

	auto iter = m_DynamicAnimateSpriteUnits.begin();
	for (; iter != m_DynamicAnimateSpriteUnits.end(); ++iter)
	{
		DynamicAnimateSpriteUnit * SpriteUnit = *iter;
		const char * groupTag = SpriteUnit->GetGroupTag();

		if(*groupTag == *tag)
		{
			this->m_DynamicAnimateSpriteUnit_Current = *iter;
			this->bResetCurrentFrame = true;

			return;
		}
	};
}

void MultiExtend::DynamicAnimateSpriteComponent::SetDefaultDynamicSpriteUnit(int idx)
{
	if (bCanChangeCurrentUnit())
	{
		MultiExtend::Math::limit_max(idx, (int)m_DynamicAnimateSpriteUnits.size() - 1);

		this->m_DynamicAnimateSpriteUnit_Default = m_DynamicAnimateSpriteUnits[idx];
		// this->bResetCurrentFrame = true;
	}
}

void MultiExtend::DynamicAnimateSpriteComponent::SetDefaultDynamicSpriteUnit(const char* tag)
{
	auto iter = m_DynamicAnimateSpriteUnits.begin();
	for (; iter != m_DynamicAnimateSpriteUnits.end(); ++iter)
	{
		DynamicAnimateSpriteUnit* SpriteUnit = *iter;
		const char* groupTag = SpriteUnit->GetGroupTag();

		if (groupTag == tag)
		{
			this->m_DynamicAnimateSpriteUnit_Default = *iter;
			// this->bResetCurrentFrame = true;

			return;
		}
	};
}

void MultiExtend::DynamicAnimateSpriteComponent::AddAnimateSpriteUnit(DynamicAnimateSpriteUnit* dynamicAnimateSpriteUnit)
{
	if (std::find(m_DynamicAnimateSpriteUnits.begin(), m_DynamicAnimateSpriteUnits.end(),
		dynamicAnimateSpriteUnit) == m_DynamicAnimateSpriteUnits.end())
	{
		m_DynamicAnimateSpriteUnits.push_back(dynamicAnimateSpriteUnit);
	}
}

void MultiExtend::DynamicAnimateSpriteComponent::RemoveAnimateSpriteUnit(DynamicAnimateSpriteUnit* dynamicAnimateSpriteUnit)
{
	auto it = std::remove_if(m_DynamicAnimateSpriteUnits.begin(), m_DynamicAnimateSpriteUnits.end(),
		[dynamicAnimateSpriteUnit](DynamicAnimateSpriteUnit* SpriteUnit) -> bool {return *dynamicAnimateSpriteUnit->GetGroupTag() == *SpriteUnit->GetGroupTag(); });
	
	m_DynamicAnimateSpriteUnits.erase(it);
}

void MultiExtend::DynamicAnimateSpriteComponent::SetCurrentFrame(float frame)
{
	m_currentFrame = frame;

	if(m_DynamicAnimateSpriteUnit_Current->GetUpdateType() == LOOP)
	{
		// Wrap current frame if needed (set from begin)
		size_t len = m_DynamicAnimateSpriteUnit_Current->GetAnimateTextures().size();

		while (m_currentFrame > len)
		{
			m_currentFrame -= len;
		}
	}
	
	if (m_DynamicAnimateSpriteUnit_Current->GetUpdateType() == ONCE)
	{
		MultiExtend::Math::limit_max(m_currentFrame, float(m_DynamicAnimateSpriteUnit_Current->GetAnimateTextures().size()-1));
	}
}
