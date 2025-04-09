#pragma once 

#include "MultiExtendAPI.h"

#include <glew.h>
#include <GLFW/glfw3.h>
#include <type_traits>

namespace MultiExtend
{
	
	struct VertexAttribute 
	{
		const char* name;    // 属性名
		GLint size;          // 分量个数
		GLenum type;         // 数据类型
		size_t offset;       // 结构体偏移量
	};

	template<typename T, size_t colorDepth>
	struct Vertex
	{
		Vector<T,4> pos;
		Color<T, colorDepth> color;
		Vector<T,4> normal;
	};

	template<typename T, size_t colorDepth>
	class VertexBuffer
	{
	public:
		static_assert(std::is_floating_point<T>::value,
			"Vertex component type must be floating point");

		VertexBuffer
		(std::vector<Vertex<T,colorDepth>> vertices, std::vector<int> indices)
		: m_Vertices(vertices), m_Indices(indices)m, m_shader(shader)
		{
			if (!m_Shader || !m_Shader->IsValid()) 
			{
				throw std::runtime_error("Invalid shader provided");
			}

			glGenVertexArrays(1, &m_VAO);
			glGenBuffers(1, &m_VBO);
			if (!m_Indices.empty()) 
			{
				glGenBuffers(1, &m_EBO);
			}



			
		}
	
	private:
		std::vector<Vertex<T, colorDepth>> m_Vertices;
		std::vector<int> m_Indices;
		GLuint m_VAO = 0, m_VBO = 0, m_EBO = 0;
	};
}
