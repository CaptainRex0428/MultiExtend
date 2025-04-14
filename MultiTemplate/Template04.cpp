#include "MultiExtend.h"

#include "Math/Vertex.h"

#include "Math/Vertex.h"
#include "Shader/Shader.h"

#include "Object/GameObject.h"


class GameInstance : public GameObject
{
public:
	static GameInstance& Get();

	virtual bool Initialize(
		const char* windowTitle = "DefaultWindow",
		Vector2 position = { 100,100 },
		Vector2 size = { 1280,720 },
		int initTag = (int)InitFrameworkTag::ALL,
		GameFrameMode mode = CUSTOM) override;

	virtual void CustomGenerateOuput(const float& ratio) override;

private:

	ShaderGL * m_shader;
	VertexBuffer<float, 8> * m_buffer;
};

GameInstance& GameInstance::Get() {
	static GameInstance instance;
	return instance;
}

bool GameInstance::Initialize(
	const char* windowTitle,
	Vector2 position,
	Vector2 size,
	int initTag,
	GameFrameMode mode)
{
	GameObject::Initialize(windowTitle, position, size, initTag, mode);

	MultiExtend::Trace::Start();

	m_shader = CreateShaderGL(m_GameStat, "../shader/basic.glsl");

	std::vector<MultiExtend::Vertex<float, 8>> vertices =
	{
		{{ -.6f, -.4f, 0.f, 1.f},{0.0f,0.5f},{1.f, 0.f, 0.f, 1.f},{0.f, 0.f, 1.f, 1.f}},
		{{  .6f, -.4f, 0.f, 1.f},{0.0f,0.5f} ,{ 0.f, 1.f, 0.f, 1.f },{ 0.f, 0.f, 1.f, 1.f }},
		{{  0.f,  .6f, 0.f, 1.f},{0.0f,0.5f} ,{ 0.f, 0.f, 1.f, 1.f },{ 0.f, 0.f, 1.f, 1.f }}
	};

	std::vector<unsigned int> indices;

	m_buffer = new MultiExtend::VertexBuffer<float, 8>(vertices, indices);
	m_buffer->ConfigureAttributes(m_shader, DefaultFloatVertexAttributes);

	return true;
}

void GameInstance::CustomGenerateOuput(const float& ratio)
{
	DrawVertices(m_buffer, m_shader, GL_TRIANGLES, ratio);
}


int main(int argc, char** argv)
{
	{
		if (GameInstance::Get().Initialize())
		{
			GameInstance::Get().Runloop();
		};

		GameInstance::Get().ShutDown();
	}
	return 0;
}

