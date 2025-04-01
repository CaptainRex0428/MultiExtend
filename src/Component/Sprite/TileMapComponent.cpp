#include "Component/Sprite/TileMapComponent.h"

#include "MultiExtend.h"

MultiExtend::TileMapComponent::TileMapComponent(
	GameStat* gameStat,
	Renderer* renderer,
	const char* texturefilepath,
	Vector2 srcPosition,
	Vector2 srcSize,
	Vector2 dstSize,
	const char* tag,
	Vector3 postion,
	Vector3 scale,
	Vector3 rotation,
	int updateorder)
	:MultiExtend::ActorComponent(tag, postion, scale, rotation, updateorder),
	m_Texture(nullptr),
	m_Renderer(renderer),
	m_srcPosition(srcPosition),
	m_srcSize(srcSize),
	m_dstSize(dstSize)
{
	if (texturefilepath)
	{
		m_Texture = MultiExtend::LoadTexture(gameStat, renderer, texturefilepath);
	}
}

MultiExtend::TileMapComponent::TileMapComponent(
	Renderer* renderer,
	Texture* texture,
	Vector2 srcPosition,
	Vector2 srcSize,
	Vector2 dstSize,
	const char* tag,
	Vector3 postion,
	Vector3 scale,
	Vector3 rotation,
	int updateorder)
	:MultiExtend::ActorComponent(tag, postion, scale, rotation, updateorder),
	m_Texture(texture),
	m_Renderer(renderer),
	m_srcPosition(srcPosition),
	m_srcSize(srcSize),
	m_dstSize(dstSize)
{

}


MultiExtend::TileMapComponent::~TileMapComponent()
{
	m_Texture = nullptr;
	m_Renderer = nullptr;
}

void MultiExtend::TileMapComponent::Update(float delta)
{	
	MULTIEXTEND_TIMER_TRACE_TAG(UpdateTileMapComponent);

	ActorComponent::Update(delta);
}

void MultiExtend::TileMapComponent::Draw()
{
	MULTIEXTEND_TIMER_TRACE_TAG(DrawTileMapComponent);

	const Vector3 scaleResult = GetScaleAbsolute();
	const Vector3 posResult = GetPositionAbsolute();

	if (m_Texture)
	{
		TextureRelocator dstRenderSize;
		TextureRelocator srcRenderSize;

		srcRenderSize.size.x = m_srcSize.x;
		srcRenderSize.size.y = m_srcSize.y;
		srcRenderSize.offset.x = m_srcPosition.x;
		srcRenderSize.offset.y = m_srcPosition.y;
		
		dstRenderSize.size.x = m_dstSize.x * scaleResult.x;
		dstRenderSize.size.y = m_dstSize.y * scaleResult.y;
		dstRenderSize.offset.x = posResult.x;
		dstRenderSize.offset.y = posResult.y;

		MultiExtend::RenderTexture(m_Renderer, m_Texture,
			&srcRenderSize, &dstRenderSize,
			GetRotationAbsolute().z);
	}

	ActorComponent::Draw();
}

void MultiExtend::TileMapComponent::SetTexture(Texture* texture)
{
	if (m_Texture)
	{
		m_Texture = texture;
	}

	// Vector2 sourceSize;
	// QueryTexture(texture, &sourceSize);
}

void MultiExtend::TileMapComponent::SetDstSize(Vector2 size)
{
	m_dstSize = size;
}

Vector2 MultiExtend::TileMapComponent::GetDstSize() const
{
	return m_dstSize;
}

void MultiExtend::TileMapComponent::SetSrcSize(Vector2 size)
{
	m_srcSize = size;
}

Vector2 MultiExtend::TileMapComponent::GetSrcSize() const
{
	return m_srcSize;
}

void MultiExtend::TileMapComponent::SetSrcPosition(Vector2 position)
{
	m_srcPosition = position;
}

Vector2 MultiExtend::TileMapComponent::GetSrcPosition() const
{
	return m_srcPosition;
}


