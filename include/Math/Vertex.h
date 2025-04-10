#pragma once 

#include "MultiExtendAPI.h"

#include <glew.h>
#include <GLFW/glfw3.h>
#include "Math/Vector.h"
#include "Math/Color.h"
#include "Shader/Shader.h"

#include "linmath.h"

#include <type_traits>
#include <stddef.h>

#include "MultiExtend.h"

namespace MultiExtend
{

	template<typename T, size_t colorDepth>
	struct Vertex
	{
		Vector<T,4> pos;
		Color<T, colorDepth> color;
		Vector<T,4> normal;
	};

	struct VertexAttribute 
	{
		const char* name;    // 属性名
		GLint size;          // 分量个数
		GLenum type;         // 数据类型
		size_t offset;       // 结构体偏移量
	};

	template<typename T, size_t colorDepth>
	class VertexBuffer
	{
	public:
		static_assert(std::is_floating_point<T>::value,
			"Vertex component type must be floating point");

		VertexBuffer
		(const std::vector<Vertex<T,colorDepth>> & vertices, const std::vector<unsigned int> & indices)
		: m_Vertices(vertices), m_Indices(indices)
		{

			glGenVertexArrays(1, &m_VAO);
			glGenBuffers(1, &m_VBO);
			if (!m_Indices.empty()) 
			{
				glGenBuffers(1, &m_EBO);
			}

			this->Bind();

			// 上传顶点数据
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
			glBufferData(GL_ARRAY_BUFFER,
				m_Vertices.size() * sizeof(Vertex<T, colorDepth>),
				m_Vertices.data(),
				GL_STATIC_DRAW);

			// 上传索引数据（可选）
			if (!m_Indices.empty()) 
			{
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER,
					m_Indices.size() * sizeof(unsigned int),
					m_Indices.data(),
					GL_STATIC_DRAW);
			}

			this->Unbind();
		}

		void Bind() const 
		{
			glBindVertexArray(m_VAO);
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
			if (m_EBO && (!m_Indices.empty())) glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
		}

		void Unbind() const 
		{
			glBindVertexArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			if (m_EBO) glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}

		void UpdateVertexData(const std::vector<Vertex<T,colorDepth>> & data, size_t count) 
		{
			m_Vertices = data;

			Bind();
			
			glBufferData(GL_ARRAY_BUFFER,  data.size() * sizeof(Vertex<T, colorDepth>), data.data(), GL_STATIC_DRAW);
			Unbind();
		}

		void UpdateIndexData(const std::vector<unsigned int>& data, size_t count)
		{
			m_Indices = data;

			if(m_Indices.empty()) m_EBO = 0;

			Bind();
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size() * sizeof(unsigned int), data.data(), GL_STATIC_DRAW);
			Unbind();
		}

		void ConfigureAttributes(ShaderGL* shader, const std::vector<VertexAttribute>& attributes)
		{
			if (!shader || !shader->IsValid()) 
			{
				MULTIEXTEND_MESSAGE_CLIENT_ERROR("Invalid shader program");
				throw std::runtime_error("Invalid shader program");
			}

			// 保存前一个状态
			GLint prevVAO, prevVBO;
			glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &prevVAO);
			glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &prevVBO);

			this->Bind();

			std::vector<GLint> enabledAttributes;

			for(auto attr : attributes)
			{
				AddAttribute(shader,attr.name,attr.size,attr.type,attr.offset,enabledAttributes);
			}
			
			this->Unbind();

			// 恢复环境到绑定前的状态
			glBindVertexArray(prevVAO);
			glBindBuffer(GL_ARRAY_BUFFER, prevVBO);

			// 恢复被覆盖的enable状态（可选）
			for (GLint loc : enabledAttributes) 
			{
				glEnableVertexAttribArray(loc);
			}
		}

		
		virtual ~VertexBuffer()
		{
			Release();
		}


		bool HasIndices() const { return !m_Indices.empty(); }
		size_t GetIndexCount() const { return m_Indices.size(); }
		size_t GetVertexCount() const { return m_Vertices.size(); }
		bool IsIndexBufferValid() const { return (m_EBO != 0) && HasIndices(); }
	
	private:

		void AddAttribute(ShaderGL* shader, const char* name, GLint size, GLenum type, size_t offset, std::vector<GLint> & enabledAttributes)
		{
			if (!shader->IsValid())
			{
				MULTIEXTEND_MESSAGE_CLIENT_WARN(
					"Shader is not valid :\n{0}\n{1}",
					shader->GetVertexShaderContent(),
					shader->GetFragmentShader());
				return;
			}
			
			const GLint location = glGetAttribLocation
			(
				shader->GetShaderProgram(),
				name
			);

			if (location == -1)
			{
				MULTIEXTEND_MESSAGE_CLIENT_WARN(
					"Attribute {0} not found in shader program {1}",
					name,
					shader->GetShaderProgram());
				return;
			}

			// 保存前一个enabled状态
			GLint enabled;
			glGetVertexAttribiv(location, GL_VERTEX_ATTRIB_ARRAY_ENABLED, &enabled);
			if (enabled) enabledAttributes.push_back(location);

			// 属性配置
			glEnableVertexAttribArray(location);
			glVertexAttribPointer(
				location,
				size,
				type,
				GL_FALSE,
				sizeof(Vertex<T, colorDepth>),
				(void*)offset);
		}

		void Release() 
		{
			if (m_VAO) 
			{
				glDeleteVertexArrays(1, &m_VAO); 
				MULTIEXTEND_MESSAGE_CLIENT_TRACE("Released Vertex Arrays:{}", m_VAO);
			}

			if (m_VBO)
			{
				glDeleteBuffers(1, &m_VBO);
				MULTIEXTEND_MESSAGE_CLIENT_TRACE("Released Vertex Buffer:{}", m_VBO);
			} 

			if (m_EBO)
			{
				glDeleteBuffers(1, &m_EBO);
				MULTIEXTEND_MESSAGE_CLIENT_TRACE("Released Vertex Element buffer:{}", m_EBO);
			} 
			
			m_VAO = m_VBO = m_EBO = 0;
		}


	private:
		std::vector<Vertex<T, colorDepth>> m_Vertices;
		std::vector<unsigned int> m_Indices;
		GLuint m_VAO = 0, m_VBO = 0, m_EBO = 0;
	};

	template<typename T, size_t colorDepth>
	void DrawVertices(VertexBuffer<T,colorDepth> * buffer, ShaderGL * shader, GLenum mode, const float & ratio)
	{
		if(!shader)
		{
			MULTIEXTEND_MESSAGE_CLIENT_ERROR("Shader ptr is null.");
			return;
		}

		if(!shader->IsValid())
		{
			MULTIEXTEND_MESSAGE_CLIENT_ERROR("Shader is not valid.\n{0}\n{1}",
				shader->GetVertexShaderContent(),
				shader->GetFragmentShaderContent());
			return;
		}

		buffer->Bind();
		glUseProgram(shader->GetShaderProgram());

		const unsigned int MVP_Idx = glGetUniformLocation(shader->GetShaderProgram(), "MVP");

		mat4x4 m, p, mvp;
		mat4x4_identity(m);
		mat4x4_rotate_Z(m, m, (float)glfwGetTime());
		mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 1.f, -1.f);
		mat4x4_mul(mvp, p, m);

		glUniformMatrix4fv(MVP_Idx, 1, GL_FALSE, (const GLfloat*)&mvp);

		if (buffer->HasIndices() && buffer->IsIndexBufferValid())
		{
			MULTIEXTEND_MESSAGE_CLIENT_DEBUG("Draw with index buffer");
			glDrawElements(mode,
				static_cast<GLsizei>(buffer->GetIndexCount()),
				GL_UNSIGNED_INT,
				nullptr);
		}
		else
		{
			MULTIEXTEND_MESSAGE_CLIENT_DEBUG("Draw without index buffer");

			glDrawArrays(mode,
				0,
				static_cast<GLsizei>(buffer->GetVertexCount()));
		}

		// 可选：错误检查
		GLenum err = glGetError();
		if (err != GL_NO_ERROR)
		{
			MULTIEXTEND_MESSAGE_CLIENT_ERROR("OpenGL draw error: {0}",
				reinterpret_cast<const char*>(glGetString(err)));
		}
	};

	typedef Vertex<double, 8> VertexDouble;
	typedef Vertex<float, 8> VertexFloat;

	static std::vector<MultiExtend::VertexAttribute> DefaultDoubleVertexAttributes =
	{
		{"vPos",   4, GL_DOUBLE, offsetof(VertexDouble,pos) },
		{"vColor", 4, GL_DOUBLE, offsetof(VertexDouble,color)},
		{"vNormal",4, GL_DOUBLE, offsetof(VertexDouble,normal)}
	};

	static std::vector<MultiExtend::VertexAttribute> DefaultFloatVertexAttributes =
	{
		{"vPos",   4, GL_FLOAT, offsetof(VertexFloat,pos) },
		{"vColor", 4, GL_FLOAT, offsetof(VertexFloat,color)},
		{"vNormal",4, GL_FLOAT, offsetof(VertexFloat,normal)}
	};
}
