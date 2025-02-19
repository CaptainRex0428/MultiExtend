#include "Math/Math.h"
#include "Math/Color.h"

Color::Color()
	:m_r(0),m_g(0),m_b(0),m_a(1)
{}

Color::Color(Color& other) 
{
	this->m_r = other.m_r;
	this->m_g = other.m_g;
	this->m_b = other.m_b;
	this->m_a = other.m_a;
}

Color::Color(Color&& other) noexcept
{
	this->m_r = other.m_r;
	this->m_g = other.m_g;
	this->m_b = other.m_b;
	this->m_a = other.m_a;
}

Color::Color(float r, float g, float b, float a)
{
	this->m_r = MultiExtendMath::Clamp(r);
	this->m_g = MultiExtendMath::Clamp(g);
	this->m_b = MultiExtendMath::Clamp(b);
	this->m_a = MultiExtendMath::Clamp(a);
}

Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	this->m_r = ((float)MultiExtendMath::Clamp(r, (uint8_t)0, (uint8_t)255)) / (uint8_t)255;
	this->m_g = ((float)MultiExtendMath::Clamp(g, (uint8_t)0, (uint8_t)255)) / (uint8_t)255;
	this->m_b = ((float)MultiExtendMath::Clamp(b, (uint8_t)0, (uint8_t)255)) / (uint8_t)255;
	this->m_a = ((float)MultiExtendMath::Clamp(a, (uint8_t)0, (uint8_t)255)) / (uint8_t)255;
}

Color::Color(int r, int g, int b, int a)
{
	this->m_r = ((float)MultiExtendMath::Clamp(r, 0, 255)) / 255;
	this->m_g = ((float)MultiExtendMath::Clamp(g, 0, 255)) / 255;
	this->m_b = ((float)MultiExtendMath::Clamp(b, 0, 255)) / 255;
	this->m_a = ((float)MultiExtendMath::Clamp(a, 0, 255)) / 255;
}

float Color::operator[](ColorFloatIndex index)
{
	if (index == r || index == x)
	{
		return m_r;
	}

	if (index == g || index == y)
	{
		return m_g;
	}

	if (index == b || index == z)
	{
		return m_b;
	}

	if (index == a || index == w)
	{
		return m_a;
	}

	return 0;
}

int Color::operator[](ColorByteIndex index)
{
	if (index == R || index == X)
	{
		return (int) (m_r * 255);
	}

	if (index == G || index == Y)
	{
		return (int) (m_g * 255);
	}

	if (index == B || index == Z)
	{
		return (int) (m_b * 255);
	}

	if (index == A || index == W)
	{
		return (int) (m_a * 255);
	}

	return 0;
}

Color& Color::operator=(const Color& other)
{
	m_r = other.m_r;
	m_g = other.m_g;
	m_b = other.m_b;
	m_a = other.m_a;

	return *this;
}
