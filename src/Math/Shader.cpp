#include "Shader/Shader.h"

#include "MultiExtend.h"

#include <glew.h>
#include <GLFW/glfw3.h>

bool MultiExtend::ShaderGL::IsShaderCompiled(unsigned int shader, bool LogOut)
{
	GLint status;

	//Query the compile status
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

	if(status != GL_TRUE)
	{
		char buffer[512];
		memset(buffer, 0, 512);
		glGetShaderInfoLog(shader, 511, nullptr, buffer);

		if(LogOut) MULTIEXTEND_MESSAGE_CLIENT_ERROR("GLSL Compile Faild:\n{0}", buffer);

		return false;
	}

	return true;
}

bool MultiExtend::ShaderGL::IsProgramValid(unsigned int shaderProgram, bool LogOut)
{
	GLint status;

	//Query the compile status
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);

	if (status != GL_TRUE)
	{
		char buffer[512];
		memset(buffer, 0, 512);
		glGetProgramInfoLog(shaderProgram, 511, nullptr, buffer);

		if(LogOut) MULTIEXTEND_MESSAGE_CLIENT_ERROR("GLSL Program Link Faild:\n{0}", buffer);

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
		MULTIEXTEND_MESSAGE_CLIENT_ERROR("[Failed] Link Program:\n Vertex Shader:\n{0}\nFragment Shader:\n{1}", vertexShader, fragmentShader);
		return 0;
	}

	glDeleteShader(VS);
	glDeleteShader(FS);

	MULTIEXTEND_MESSAGE_CLIENT_TRACE("[Shader Program Linked]:{0}", program);

	return program;
	
}

unsigned int MultiExtend::ShaderGL::Create(unsigned int vertexShader, unsigned int fragmentShader)
{
	if(!(IsShaderCompiled(vertexShader, false) && IsShaderCompiled(fragmentShader, false)))
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
		MULTIEXTEND_MESSAGE_CLIENT_ERROR("[Failed] Link Program:\n Vertex Shader:\n{0}\nFragment Shader:\n{1}", vertexShader, fragmentShader);
		return 0;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	MULTIEXTEND_MESSAGE_CLIENT_TRACE("[Shader Program Linked]:{0}", program);

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
		MULTIEXTEND_MESSAGE_CLIENT_ERROR("[Failed] [{0}] shader:\n{1}", TypeTag, source);
		return id;
	}
	
	MULTIEXTEND_MESSAGE_CLIENT_TRACE("[Shader Compiled]:{0}[{1}]", TypeTag, id);

	return id;
}

void MultiExtend::ShaderGL::GenerateHash()
{
	MULTIEXTEND_TIMER_TRACE_TAG(GenerateShaderGLHash);

	std::string mac = Operator::Get().GetMacAddress();
	std::string time = Clock::GetCurrentTimeStamp_sys();
	std::string content = m_fragmentShader + m_vertexShader;
	m_hash = SHAGenerator::GenerateSHA256Hash(mac, time, content);
}

const std::string& MultiExtend::ShaderGL::GetHash() const
{
	return this->m_hash;
}

const std::string & MultiExtend::ShaderGL::GetFilePath() const
{
	return this->m_filePath;
}

MultiExtend::ShaderGL::ShaderGL(const char* vertexShader, const char* fragShader)
	:m_vertexShader(vertexShader), m_fragmentShader(fragShader)
{
	VertexShader = Compile(GL_VERTEX_SHADER, vertexShader);
	FragmentShader = Compile(GL_FRAGMENT_SHADER, fragShader);
	ShaderProgram = Create(VertexShader,FragmentShader);

	GenerateHash();
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

		GenerateHash();
	};
}

MultiExtend::ShaderGL::~ShaderGL()
{
	if(this->IsValid())
	{
		this->Unload();
	}
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
	return IsShaderCompiled(VertexShader,false) && IsShaderCompiled(FragmentShader,false) && IsProgramValid(ShaderProgram);
}

void MultiExtend::ShaderGL::Unload()
{
	glDeleteProgram(ShaderProgram);
	glDeleteShader(VertexShader);
	glDeleteShader(FragmentShader);

	MULTIEXTEND_MESSAGE_CLIENT_TRACE("Unload shader:{}", ShaderProgram);
}


ShaderGL* MultiExtend::CreateShaderGL(GameStat * gameStat, const char* filePath)
{
	if(!File::IsFilePathValid(filePath))
	{
		return nullptr;
	}

	ShaderGL* shader = new ShaderGL(filePath);

	if(!shader->IsValid())
	{
		delete shader;
		return nullptr;
	}

	gameStat->AddShaderGL(shader);

	return shader;
}
