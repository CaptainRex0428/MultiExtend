#pragma once 

#include "MultiExtendAPI.h"

#include <glew.h>
#include <GLFW/glfw3.h>

#include "Shader/Shader.h"

namespace MultiExtend
{
	struct VertexAttributeDesc {
		const char* name;      // 着色器中属性名称
		GLint size;            // 分量数量 (vec3=3, vec4=4)
		GLenum type;           // 数据类型 (GL_FLOAT等)
		GLboolean normalized;  // 是否归一化
		size_t offset;         // 在Vertex结构体中的偏移量
	};

	template<typename T, size_t colorDepth>
	struct Vertex
	{
		Vector<T,4> pos;
		Color<T, colorDepth> color;
		Vector<T,4> normal;

		static const std::vector<VertexAttributeDesc> DefaultAttributes;
	};

	template<typename T, size_t colorDepth>
	const std::vector<VertexAttributeDesc> Vertex<T, colorDepth>::DefaultAttributes =
	{
		{"vPos",   4, std::is_same_v<T,float> ? GL_FLOAT : GL_DOUBLE, GL_FALSE, offsetof(Vertex, pos)},
		{"vCol",   4, std::is_same_v<T,float> ? GL_FLOAT : GL_DOUBLE, GL_FALSE, offsetof(Vertex, color)},
		{"vNormal",4, std::is_same_v<T,float> ? GL_FLOAT : GL_DOUBLE, GL_FALSE, offsetof(Vertex, normal)}
	};

	template<typename T, size_t colorDepth>
	class VertexBuffer
	{
	public:
		VertexBuffer
		(std::vector<Vertex<T,colorDepth>> vertices, std::vector<int> indices, ShaderGL * shader)
		: m_Vertices(vertices), m_Indices(indices)m, m_shader(shader)
		{
			if (!m_Shader || !m_Shader->IsValid()) 
			{
				throw std::runtime_error("Invalid shader provided");
			}

			glGenVertexArrays(1, &m_VAO);
			glGenBuffers(1, &m_VBO);
			glGenBuffers(1, &m_EBO);


			
		}
	
	private:
		std::vector<Vertex<T, colorDepth>> m_Vertices;
		std::vector<int> m_Indices;
		ShaderGL* m_shader;
		GLuint m_VAO = 0, m_VBO = 0, m_EBO = 0;
	};

	template<typename T, size_t colorDepth>
	int Render(const Vertex<T,colorDepth>* vertices, unsigned int size, ShaderGL * shader)
	{
		if(!shader->IsValid())
		{
			
		}
	};
}
