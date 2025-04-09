#include "System/File/ShaderFile.h"

MultiExtend::ShaderFile::ShaderFile()
	:File()
{
}

MultiExtend::ShaderFile::ShaderFile(std::string filepath)
	:File(filepath)
{
	
}

MultiExtend::ShaderFile::~ShaderFile()
{
}

std::string MultiExtend::ShaderFile::GetVertexShader()
{
	std::vector<std::string> content = GetSubContent("#Vertex","#Fragment");
	
	std::string shader = "";

	for(auto str : content)
	{
		shader += str;
		shader += "\n";

	}

	return shader;
}

 std::string MultiExtend::ShaderFile::GetFragmentShader()
{
	std::vector<std::string> content = GetSubContent("#Fragment");

	std::string shader = "";

	for (auto str : content)
	{
		shader += str;
		shader += "\n";
	}

	return shader;
}
