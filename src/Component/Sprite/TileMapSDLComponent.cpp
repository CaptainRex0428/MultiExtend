#include "Component/Sprite/TileMapSDLComponent.h"

#include "MultiExtend.h"

MultiExtend::TileMapSDLComponent::TileMapSDLComponent(
	GameStat* gameStat,
	SDL_Renderer* renderer,
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

MultiExtend::TileMapSDLComponent::TileMapSDLComponent(
	SDL_Renderer* renderer,
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


MultiExtend::TileMapSDLComponent::~TileMapSDLComponent()
{
	m_Texture = nullptr;
	m_Renderer = nullptr;
}

void MultiExtend::TileMapSDLComponent::CustomUpdate(float delta)
{	
	MULTIEXTEND_TIMER_TRACE_TAG(UpdateTileMapComponent);

	ActorComponent::CustomUpdate(delta);
}

void MultiExtend::TileMapSDLComponent::CustomDraw(const Vector2& size)
{
	MULTIEXTEND_TIMER_TRACE_TAG(DrawTileMapComponent);

	const Vector3 scaleResult = GetScaleAbsolute();
	const Vector3 posResult = GetPositionAbsolute();

	if (m_Texture)
	{
		TextureRelocator dstRenderSize;
		TextureRelocator srcRenderSize;

		srcRenderSize.size[x] = m_srcSize[x];
		srcRenderSize.size[y] = m_srcSize[y];
		srcRenderSize.offset[x] = m_srcPosition[x];
		srcRenderSize.offset[y] = m_srcPosition[y];
		
		dstRenderSize.size[x] = m_dstSize[x] * scaleResult[x];
		dstRenderSize.size[y] = m_dstSize[y] * scaleResult[y];
		dstRenderSize.offset[x] = posResult[x];
		dstRenderSize.offset[y] = posResult[y];

		MultiExtend::RenderTexture(m_Renderer, m_Texture,
			&srcRenderSize, &dstRenderSize,
			GetRotationAbsolute()[z]);
	}

	ActorComponent::CustomDraw(size);
}

void MultiExtend::TileMapSDLComponent::SetTexture(Texture* texture)
{
	if (m_Texture)
	{
		m_Texture = texture;
	}

	// Vector2 sourceSize;
	// QueryTexture(texture, &sourceSize);
}

void MultiExtend::TileMapSDLComponent::SetDstSize(Vector2 size)
{
	m_dstSize = size;
}

Vector2 MultiExtend::TileMapSDLComponent::GetDstSize() const
{
	return m_dstSize;
}

void MultiExtend::TileMapSDLComponent::SetSrcSize(Vector2 size)
{
	m_srcSize = size;
}

Vector2 MultiExtend::TileMapSDLComponent::GetSrcSize() const
{
	return m_srcSize;
}

void MultiExtend::TileMapSDLComponent::SetSrcPosition(Vector2 position)
{
	m_srcPosition = position;
}

Vector2 MultiExtend::TileMapSDLComponent::GetSrcPosition() const
{
	return m_srcPosition;
}


