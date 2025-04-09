#include "Shader/Shader.h"

#include "MultiExtend.h"

#include <glew.h>
#include <GLFW/glfw3.h>

bool MultiExtend::ShaderGL::IsShaderCompiled(unsigned int shader)
{
	GLint status;

	//Query the compile status
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

	if(status != GL_TRUE)
	{
		char buffer[512];
		memset(buffer, 0, 512);
		glGetShaderInfoLog(shader, 511, nullptr, buffer);
		MULTIEXTEND_MESSAGE_CLIENT_WARN("GLSL Compile Faild:\n{0}", buffer);

		return false;
	}

	return true;
}

bool MultiExtend::ShaderGL::IsProgramValid(unsigned int shaderProgram)
{
	GLint status;

	//Query the compile status
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);

	if (status != GL_TRUE)
	{
		char buffer[512];
		memset(buffer, 0, 512);
		glGetProgramInfoLog(shaderProgram, 511, nullptr, buffer);
		MULTIEXTEND_MESSAGE_CLIENT_WARN("GLSL Program Link Faild:\n{0}", buffer);

		return false;
	}

	return true;
}

unsigned int MultiExtend::ShaderGL::Create(const char* vertexShader, const char* fragmentShader)
{
	
	unsigned int program = glCreateProgram();
	unsigned int VS = Compile(GL_VERTEX_SHADER, vertexShader);
	unsigned int FS = Compile(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, VS);
	glAttachShader(program, FS);
	glLinkProgram(program);
	glValidateProgram(program);

	if(!IsProgramValid(program))
	{
		MULTIEXTEND_MESSAGE_CLIENT_WARN("[Failed] Link Program:\n Vertex Shader:\n{0}\nFragment Shader:\n{1}", vertexShader, fragmentShader);
		return 0;
	}

	glDeleteShader(VS);
	glDeleteShader(FS);

	MULTIEXTEND_MESSAGE_CLIENT_DEBUG("[Shader Program Linked]:{0}", program);

	return program;
	
}

unsigned int MultiExtend::ShaderGL::Create(unsigned int vertexShader, unsigned int fragmentShader)
{
	if(!(IsShaderCompiled(vertexShader) && IsShaderCompiled(fragmentShader)))
	{
		return 0;
	}

	unsigned int program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);
	glValidateProgram(program);

	if (!IsProgramValid(program))
	{
		MULTIEXTEND_MESSAGE_CLIENT_WARN("[Failed] Link Program:\n Vertex Shader:\n{0}\nFragment Shader:\n{1}", vertexShader, fragmentShader);
		return 0;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	MULTIEXTEND_MESSAGE_CLIENT_DEBUG("[Shader Program Linked]:{0}", program);

	return program;
}

GLuint MultiExtend::ShaderGL::Compile(unsigned int type, const char* source)
{
	unsigned int id = glCreateShader(type);

	glShaderSource(id, 1, &source, nullptr);
	glCompileShader(id);

	const char* TypeTag = type == GL_VERTEX_SHADER ? "Vertex" : "Fragment";

	if(!IsShaderCompiled(id))
	{
		MULTIEXTEND_MESSAGE_CLIENT_WARN("[Failed] [{0}] shader:{1}", TypeTag, source);
		return 0;
	}
	
	MULTIEXTEND_MESSAGE_CLIENT_DEBUG("[Shader Compiled]:{0}[{1}]", TypeTag, id);

	return id;
}

MultiExtend::ShaderGL::ShaderGL(const char* vertexShader, const char* fragShader)
	:m_vertexShader(vertexShader), m_fragmentShader(fragShader)
{
	VertexShader = Compile(GL_VERTEX_SHADER, vertexShader);
	FragmentShader = Compile(GL_FRAGMENT_SHADER, fragShader);
	ShaderProgram = Create(VertexShader,FragmentShader);
}

MultiExtend::ShaderGL::ShaderGL(const char* filePath)
	:m_vertexShader(""), m_fragmentShader(""), VertexShader(0), FragmentShader(0), ShaderProgram(0)
{
	if(ShaderFile::IsFilePathValid(filePath))
	{
		ShaderFile shaderFile(filePath);
		
		shaderFile.Open();

		m_vertexShader = shaderFile.GetVertexShader();
		m_fragmentShader = shaderFile.GetFragmentShader();

		shaderFile.Close();

		VertexShader = Compile(GL_VERTEX_SHADER, m_vertexShader.c_str());
		FragmentShader = Compile(GL_FRAGMENT_SHADER, m_fragmentShader.c_str());
		ShaderProgram = Create(VertexShader, FragmentShader);
	};
}

MultiExtend::ShaderGL::~ShaderGL()
{
	if(this->IsValid())
	{
		this->UnLoad();
	}

	m_vertexShader = nullptr;
	m_fragmentShader = nullptr;
}

const char* MultiExtend::ShaderGL::GetVertexShaderContent()
{
	return m_vertexShader.c_str();
}

unsigned int MultiExtend::ShaderGL::GetVertexShader()
{
	return VertexShader;
}

const char* MultiExtend::ShaderGL::GetFragmentShaderContent()
{
	return m_fragmentShader.c_str();
}

unsigned int MultiExtend::ShaderGL::GetFragmentShader()
{
	return FragmentShader;
}

unsigned int MultiExtend::ShaderGL::GetShaderProgram()
{
	return ShaderProgram;
}

bool MultiExtend::ShaderGL::IsValid()
{
	return IsShaderCompiled(VertexShader) && IsShaderCompiled(FragmentShader) && IsProgramValid(ShaderProgram);
}

void MultiExtend::ShaderGL::UnLoad()
{
	glDeleteProgram(ShaderProgram);
	glDeleteShader(VertexShader);
	glDeleteShader(FragmentShader);
}
