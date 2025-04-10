#pragma once

#include "MultiExtendAPI.h"

#include "System/File/ShaderFile.h"
#include "Object/Object.h"
#include "Object/GameStat.h"

namespace MultiExtend
{
	class ShaderGL : public Object
	{
	public:
		MULTIEXTEND_API ShaderGL(const char * VertexShader, const char * FragShader);
		MULTIEXTEND_API ShaderGL(const char * filePath);
		MULTIEXTEND_API virtual ~ShaderGL();

		MULTIEXTEND_API const char* GetVertexShaderContent();
		MULTIEXTEND_API unsigned int GetVertexShader();

		MULTIEXTEND_API const char* GetFragmentShaderContent();
		MULTIEXTEND_API unsigned int GetFragmentShader();

		MULTIEXTEND_API unsigned int GetShaderProgram();

		MULTIEXTEND_API bool IsValid();

		MULTIEXTEND_API void Unload();

		MULTIEXTEND_API const std::string& GetHash() const;
		MULTIEXTEND_API const std::string& GetFilePath() const;
	
		MULTIEXTEND_API static bool IsShaderCompiled(unsigned int shader , bool LogOut = true);
		MULTIEXTEND_API static bool IsProgramValid(unsigned int shaderProgram, bool LogOut = true);

		MULTIEXTEND_API static unsigned int Create(const char * vertexShader, const char * fragmentShader);
		MULTIEXTEND_API static unsigned int Create(unsigned int vertexShader, unsigned int fragmentShader);
		MULTIEXTEND_API static unsigned int Compile(unsigned int type, const char * source);

	private:
		MULTIEXTEND_API void GenerateHash();

	private:
		std::string m_vertexShader;
		std::string m_fragmentShader;

		unsigned int VertexShader;
		unsigned int FragmentShader;
		unsigned int ShaderProgram;

		std::string m_hash;
		std::string m_filePath;
	};

	MULTIEXTEND_API ShaderGL * CreateShaderGL(GameStat * gameStat ,const char * filePath);
}