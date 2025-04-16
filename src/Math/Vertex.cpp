#include "Math/Vertex.h"

std::map<std::string, int> MultiExtend::InitUniformVariablesGL(ShaderGL* shader, const float& ratio)
{
	std::map<std::string, int> valueMap;

	// time

	float glfwTime = (float)glfwGetTime();

	std::chrono::steady_clock::duration startTime = GlobalClock::GetProcessStartTime()->m_time_highres.time_since_epoch();
	std::chrono::steady_clock::duration now = MULTIEXTEND_CLOCK_HIGHRES::now().time_since_epoch();

	double startTimeDurationDouble = std::chrono::duration<double>(startTime).count();
	double nowTimeDurationDouble = std::chrono::duration<double>(now).count();
	float timeSpanFromStart_Double = (float)(nowTimeDurationDouble - startTimeDurationDouble);

	const unsigned int uTime = glGetUniformLocation(shader->GetShaderProgram(), "uTime");

	if (uTime != -1)
	{
		glUniform1f(uTime, glfwTime);
	}

	valueMap.insert({"uTime",uTime});

	// MVP
	mat4x4 m, p, mvp;
	mat4x4_identity(m);
	mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
	mat4x4_mul(mvp, p, m);

	const unsigned int uMVP = glGetUniformLocation(shader->GetShaderProgram(), "uMVP");
	if (uMVP != -1)
	{
		glUniformMatrix4fv(uMVP, 1, GL_FALSE, (const GLfloat*)&mvp);
	}

	valueMap.insert({ "uMVP",uMVP });

	return valueMap;
}
