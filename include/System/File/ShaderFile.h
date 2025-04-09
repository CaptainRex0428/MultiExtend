#pragma once

#include "MultiExtendAPI.h"

#include "File.h"

namespace MultiExtend
{
	class ShaderFile: public File
	{
	public:
		MULTIEXTEND_API ShaderFile();
		MULTIEXTEND_API ShaderFile(std::string filepath);
		MULTIEXTEND_API virtual ~ShaderFile();

		MULTIEXTEND_API std::string GetVertexShader();
		MULTIEXTEND_API std::string GetFragmentShader();
	};
}