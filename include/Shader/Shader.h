#pragma once

#include "MultiExtendAPI.h"

#include "System/File/File.h"
#include "Object/Object.h"

namespace MultiExtend
{
	class ShaderGL : public Object
	{
	public:
		MULTIEXTEND_API ShaderGL(const char * VertexShader, const char * FragShader);
		// MULTIEXTEND_API ShaderGL(const char * filePath);
		// MULTIEXTEND_API ShaderGL(const File & file);
		MULTIEXTEND_API virtual ~ShaderGL();

		const char* GetVertexShaderContent();
		unsigned int GetVertexShader();

		const char* GetFragmentShaderContent();
		unsigned int GetFragmentShader();

		unsigned int GetShaderProgram();

		bool IsValid();

		void UnLoad();

		static bool IsShaderCompiled(unsigned int shader);
		static bool IsProgramValid(unsigned int shaderProgram);

		static unsigned int Create(const char * vertexShader, const char * fragmentShader);
		static unsigned int Create(unsigned int vertexShader, unsigned int fragmentShader);
		static unsigned int Compile(unsigned int type, const char * source);

	private:
		const char * m_vertexShader;
		const char* m_fragmentShader;

		unsigned int VertexShader;
		unsigned int FragmentShader;
		unsigned int ShaderProgram;
	};
}