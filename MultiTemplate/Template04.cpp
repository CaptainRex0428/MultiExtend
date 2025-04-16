#include "MultiExtend.h"

#include "Math/Vertex.h"

#include "Math/Vertex.h"
#include "Shader/Shader.h"

#include "Object/GameObject.h"

#include "glew.h"
#include <GLFW/glfw3.h>

class GameInstance : public GameObject
{
public:
	static GameInstance& Get();

	virtual bool Initialize(
		const char* windowTitle = "DefaultWindow",
		Vector2 position = { 100,100 },
		Vector2 size = { 1280,720 },
		InitFrameworkTag initTag = OpenGL,
		GameFrameMode mode = CUSTOM) override;

	virtual void CustomGenerateOuput(const Vector2& size) override;

private:

	ShaderGL * m_shader;
	VertexBufferGL<float, 8> * m_buffer;
};

GameInstance& GameInstance::Get() {
	static GameInstance instance;
	return instance;
}

bool GameInstance::Initialize(
	const char* windowTitle,
	Vector2 position,
	Vector2 size,
	InitFrameworkTag initTag,
	GameFrameMode mode)
{
	MultiExtend::Trace::Start();

	GameObject::Initialize(windowTitle, position, size, initTag, mode);

	m_shader = CreateShaderGL(m_GameStat, "../shader/Basic.glsl");

	std::vector<MultiExtend::Vertex<float, 8>> vertices =
	{
		{{ -.5f,  .5f, 0.f, 1.f}, {0.0f,0.5f}, {1.f, 1.f, 0.f, 1.f}, {0.f, 0.f, 1.f, 1.f}},
		{{  .5f,  .5f, 0.f, 1.f}, {0.0f,0.5f}, {0.f, 1.f, 1.f, 1.f}, {0.f, 0.f, 1.f, 1.f}},
		{{  .5f, -.5f, 0.f, 1.f}, {0.0f,0.5f}, {0.f, 0.f, 1.f, 1.f}, {0.f, 0.f, 1.f, 1.f}},
		{{ -.5f, -.5f, 0.f, 1.f}, {0.0f,0.5f}, {1.f, 0.f, 1.f, 1.f}, {0.f, 0.f, 1.f, 1.f}}
	};

	std::vector<unsigned int> indices = 
	{
		0,1,2,
		2,3,0
	};

	m_buffer = new MultiExtend::VertexBufferGL<float, 8>(vertices, indices);
	m_buffer->ConfigureAttributes(m_shader, DefaultFloatVertexAttributes);

	return true;
}

void GameInstance::CustomGenerateOuput(const Vector2& size)
{
	DrawSpinningVerticesGL(m_buffer, m_shader, GL_TRIANGLES, size[x]/size[y]);
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

