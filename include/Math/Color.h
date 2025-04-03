#pragma once

#include <stdint.h>

#include "MultiExtendAPI.h"
#include "Vector.h"

namespace MultiExtend
{
	class Color
	{
	public:
		MULTIEXTEND_API Color();
		MULTIEXTEND_API Color(float r,float g,float b, float a);
		MULTIEXTEND_API Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
		MULTIEXTEND_API Color(int r, int g, int b, int a);

		MULTIEXTEND_API Color(Color& other);
		MULTIEXTEND_API Color(Color&& other) noexcept;

		MULTIEXTEND_API float operator[](VectorFilterDimension1D index);

		MULTIEXTEND_API Color& operator=(const Color& other);

	private:
		float m_r, m_g, m_b, m_a;


	};

}