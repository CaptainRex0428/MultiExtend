#pragma once

#include "MultiExtendAPI.h"

namespace MultiExtend
{
	template <typename T, size_t Rows, size_t Cols>
	class Matrix
	{
		
	public:
		static_assert(Rows > 0 && Cols > 0, "Matrix row & column must be greater than zero.");

		Matrix()
			:data({}) 
		{
		}

		// 访问元素（行主序）
		Matrix(std::initializer_list<T> InitializeList) 
		{
			assert(InitializeList.size() == Rows * Cols && "Invalid initializer list size");
			std::copy(InitializeList.begin(), InitializeList.end(), data.begin());
		}

		T& operator()(size_t row, size_t col) 
		{
			return data[row * Cols + col];
		}

		const T& operator()(size_t row, size_t col) const 
		{
			return data[row * Cols + col];
		}

		// 获取矩阵维度
		static constexpr size_t rows() { return Rows; }
		static constexpr size_t cols() { return Cols; }

	private:
		std::array<T, Rows* Cols> data;
	};


	typedef Matrix<float, 3, 3> Matrix3x3;
	typedef Matrix<float, 4, 4> Matrix4x4;
}