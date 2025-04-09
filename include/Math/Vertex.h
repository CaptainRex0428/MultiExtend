#pragma once 

#include "MultiExtendAPI.h"

#include <cassert>
#include <vector>

#include <glew.h>
#include <GLFW/glfw3.h>

namespace MultiExtend
{
	struct VertexAttributeGL 
	{
		const char * tag;
		GLuint index;			// 属性位置（对应着色器中的 layout(location=X)）
		GLint size;				// 分量数（如 vec3 → 3）
		GLenum type;			// 数据类型（如 GL_FLOAT）
		GLboolean normalized;	// 是否归一化
		size_t offset;			// 在顶点结构体中的字节偏移
	};

	template <typename T, size_t NumAttributes>
	class VertexGL {
	public:
		VertexGL() = default;
		
		VertexGL(std::initializer_list<T> init) {
			assert(init.size() == NumAttributes && "Initializer size mismatch");
			std::copy(init.begin(), init.end(), data.begin());
		}
		
		T& operator[](size_t index) { return data.at(index); }
		const T& operator[](size_t index) const { return data.at(index); }

		
		const T* raw() const { return data.data(); }
		static constexpr size_t stride() { return sizeof(T) * NumAttributes; }

	private:
		std::array<T, NumAttributes> data{};
	};

	template <size_t NumIndicesPerElement>
	class IndexGL {
	public:
		IndexGL() = default;
		
		IndexGL(std::initializer_list<uint32_t> init) {
			assert(init.size() == NumIndicesPerElement && "Initializer size mismatch");
			std::copy(init.begin(), init.end(), data.begin());
		}

		uint32_t& operator[](size_t index) { return data.at(index); }
		const uint32_t& operator[](size_t index) const { return data.at(index); }

		const uint32_t* raw() const { return data.data(); }
		static constexpr size_t count() { return NumIndicesPerElement; }

	private:
		std::array<uint32_t, NumIndicesPerElement> data{};
	};
	
	template <typename T, size_t NumVertexAttributes, size_t NumIndicesPerElement>
	class VertexArrayGL {
	public:
		
		VertexArrayGL(
			const std::vector<VertexGL<T, NumVertexAttributes>>& vertices,
			const std::vector<IndexGL<NumIndicesPerElement>>& indices,
			const std::vector<VertexAttributeGL>& attributes
		) : m_Vertices(vertices), m_Indices(indices) 
		{
			// 生成 OpenGL 对象
			glGenVertexArrays(1, &m_VAO);
			glGenBuffers(1, &m_VBO);
			glGenBuffers(1, &m_EBO);

			// 绑定 VAO（记录后续配置）
			glBindVertexArray(m_VAO);

			// 上传顶点数据到 VBO
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
			glBufferData(GL_ARRAY_BUFFER,
				m_Vertices.size() * sizeof(VertexGL<T, NumVertexAttributes>),
				m_Vertices.data(),
				GL_STATIC_DRAW);

			// 配置顶点属性
			for (const auto& attr : attributes) 
			{
				glEnableVertexAttribArray(attr.index);
				glVertexAttribPointer(
					attr.index,
					attr.size,
					attr.type,
					attr.normalized,
					sizeof(VertexGL<T, NumVertexAttributes>), // 步长
					reinterpret_cast<void*>(attr.offset)     // 偏移
				);
			}

			// 上传索引数据到 EBO
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER,
				m_Indices.size() * sizeof(IndexGL<NumIndicesPerElement>),
				m_Indices.data(),
				GL_STATIC_DRAW);

			// 解绑
			glBindVertexArray(0);
		}

		// 析构函数：释放资源
		~VertexArrayGL() {
			glDeleteBuffers(1, &m_VBO);
			glDeleteBuffers(1, &m_EBO);
			glDeleteVertexArrays(1, &m_VAO);
		}

		// 动态更新顶点数据
		void UpdateVertices(const std::vector<VertexGL<T, NumVertexAttributes>>& newVertices) {
			m_Vertices = newVertices;
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
			glBufferSubData(GL_ARRAY_BUFFER,
				0,
				m_Vertices.size() * sizeof(VertexGL<T, NumVertexAttributes>),
				m_Vertices.data());
		}

		/**
		 * 更新部分顶点数据（同时更新CPU和GPU数据）
		 * @param offset    要更新的起始顶点索引（以顶点为单位，非字节）
		 * @param data      顶点数据指针（必须包含 count 个连续顶点）
		 * @param count     要更新的顶点数量
		 */
		void UpdateSubVertices(size_t offset, const std::vector <VertexGL<T, NumVertexAttributes>> & data)
		{
			// 参数合法性检查
			if (offset + data.size() > m_Vertices.size()) {
				throw std::out_of_range("VertexArray::UpdateSubVertices - offset + count exceeds vertex buffer size");
			}

			// 更新 CPU 端数据
			std::copy(data.begin(), data.end(), m_Vertices.begin() + offset);

			// 更新 GPU 端数据
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
			glBufferSubData(GL_ARRAY_BUFFER,
				offset * sizeof(VertexGL<T, NumVertexAttributes>),			// 字节偏移
				data.size() * sizeof(VertexGL<T, NumVertexAttributes>),     // 字节大小
				data.data()													// 数据指针
			);

			glBindBuffer(GL_ARRAY_BUFFER, 0); // 解绑
		}


		// 绘制方法
		void Draw(GLenum mode = GL_TRIANGLES) const 
		{
			glBindVertexArray(m_VAO);
			glDrawElements(mode,
				m_Indices.size() * NumIndicesPerElement,
				GL_UNSIGNED_INT,
				0);
			glBindVertexArray(0);
		}
	private:
		std::vector<VertexGL<T, NumVertexAttributes>> m_Vertices;
		std::vector<IndexGL<NumIndicesPerElement>> m_Indices;
		GLuint m_VAO = 0, m_VBO = 0, m_EBO = 0;
	};
}
