#include "Math/Math.h"
#include "Math/Color.h"

MultiExtend::Color::Color()
	:m_r(0),m_g(0),m_b(0),m_a(1)
{}

MultiExtend::Color::Color(Color& other)
{
	this->m_r = other.m_r;
	this->m_g = other.m_g;
	this->m_b = other.m_b;
	this->m_a = other.m_a;
}

MultiExtend::Color::Color(Color&& other) noexcept
{
	this->m_r = other.m_r;
	this->m_g = other.m_g;
	this->m_b = other.m_b;
	this->m_a = other.m_a;
}

float MultiExtend::Color::operator[](VectorFilterDimension1D index)
{
	uint8_t idx = (uint8_t)index % 4;

	if (idx == 0)
	{
		return m_r;
	}

	if (idx == 1)
	{
		return m_g;
	}

	if (idx == 2)
	{
		return m_b;
	}

	if (idx == 3)
	{
		return m_a;
	}

	return 0;
}

MultiExtend::Color::Color(float r, float g, float b, float a)
{
	this->m_r = MultiExtend::Math::Clamp(r);
	this->m_g = MultiExtend::Math::Clamp(g);
	this->m_b = MultiExtend::Math::Clamp(b);
	this->m_a = MultiExtend::Math::Clamp(a);
}

MultiExtend::Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	this->m_r = ((float)MultiExtend::Math::Clamp(r, (uint8_t)0, (uint8_t)255)) / (uint8_t)255;
	this->m_g = ((float)MultiExtend::Math::Clamp(g, (uint8_t)0, (uint8_t)255)) / (uint8_t)255;
	this->m_b = ((float)MultiExtend::Math::Clamp(b, (uint8_t)0, (uint8_t)255)) / (uint8_t)255;
	this->m_a = ((float)MultiExtend::Math::Clamp(a, (uint8_t)0, (uint8_t)255)) / (uint8_t)255;
}

MultiExtend::Color::Color(int r, int g, int b, int a)
{
	this->m_r = ((float)MultiExtend::Math::Clamp(r, 0, 255)) / 255;
	this->m_g = ((float)MultiExtend::Math::Clamp(g, 0, 255)) / 255;
	this->m_b = ((float)MultiExtend::Math::Clamp(b, 0, 255)) / 255;
	this->m_a = ((float)MultiExtend::Math::Clamp(a, 0, 255)) / 255;
}

MultiExtend::Color& MultiExtend::Color::operator=(const Color& other)
{
	m_r = other.m_r;
	m_g = other.m_g;
	m_b = other.m_b;
	m_a = other.m_a;

	return *this;
}
