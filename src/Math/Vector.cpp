#include "Math/Vector.h"

#include <utility>
#include <math.h>

#include "Math/Math.h"

#define VectorNDebug

MultiExtend::Vector2::Vector2()
	:x(0),y(0)
{
}

MultiExtend::Vector2::Vector2(float num)
	:x(num), y(num)
{
}

MultiExtend::Vector2::Vector2(float i_x, float i_y)
	:x(i_x), y(i_y)
{
}

MultiExtend::Vector2::~Vector2() = default;

MultiExtend::Vector2::Vector2(const Vector2& other)
{
	x = other.x;
	y = other.y;
}

MultiExtend::Vector2::Vector2(Vector2&& other) noexcept
{
	x = other.x;
	y = other.y;
}

MultiExtend::Vector2& MultiExtend::Vector2::operator=(const MultiExtend::Vector2& other)
{
	x = other.x;
	y = other.y;

	return *this;
}


MultiExtend::Vector2 MultiExtend::Vector2::operator+(MultiExtend::Vector2& other)
{
	return Vector2(x + other.x, y + other.y);
}

MultiExtend::Vector2 MultiExtend::Vector2::operator+(float& num)
{
	return Vector2(x + num, y + num);
}

MultiExtend::Vector2 MultiExtend::Vector2::operator-(MultiExtend::Vector2& other)
{
	return Vector2(x - other.x, y - other.y);
}

MultiExtend::Vector2 MultiExtend::Vector2::operator-(float& num)
{
	return Vector2(x - num, y - num);
}

MultiExtend::Vector2 MultiExtend::Vector2::operator*(Vector3&& other)
{
	Vector3 o = other;
	return *this * o;
}

MultiExtend::Vector2 MultiExtend::Vector2::operator*(Vector3& other)
{
	return Vector2(x * other.x, y * other.y);
}

MultiExtend::Vector2 MultiExtend::Vector2::operator*(MultiExtend::Vector2& other)
{
	return Vector2(x*other.x,y*other.y);
}

MultiExtend::Vector2 MultiExtend::Vector2::operator*(Vector2&& other)
{
	Vector2 o = other;
	return *this * o;
}

MultiExtend::Vector2 MultiExtend::Vector2::operator*(float& num)
{
	return MultiExtend::Vector2(x*num, y*num);
}

MultiExtend::Vector2& MultiExtend::Vector2::operator+=(MultiExtend::Vector2& other)
{
#ifdef VectorDebug
	std::cout << "value:(" << other.x << "," << other.y << ")\n";
#endif
	*this += (std::move(other));
	return *this;
}

MultiExtend::Vector2& MultiExtend::Vector2::operator+=(MultiExtend::Vector2&& other)
{
#ifdef VectorDebug
	std::cout << "value:(" << other.x << "," << other.y << ")\n";
#endif
	this->x += other.x;
	this->y += other.y;
	return *this;
}

MultiExtend::Vector2& MultiExtend::Vector2::operator+=(float& num)
{
	this->x += num;
	this->y += num;
	return *this;
}

float MultiExtend::Vector2::length()
{
	return (float)(sqrt(pow(x, 2) + pow(y, 2)));
}

MultiExtend::Vector2 MultiExtend::Vector2::normalize()
{
	float len = length();
	return Vector2(x/ len, y/ len);
}

float MultiExtend::Vector2::dot(Vector2& va, Vector2& vb)
{
	return va.x * vb.x + va.y * vb.y;
}

MultiExtend::Vector3 MultiExtend::Vector2::cross(Vector2& va, Vector2& vb)
{
	return Vector3(0, 0, va.x * vb.y - va.y * vb.x);
}

MultiExtend::Vector2& MultiExtend::Vector2::operator=(Vector2&& other) noexcept
{
	this->x = other.x;
	this->y = other.y;

	return *this;
}

MultiExtend::Vector2& MultiExtend::Vector2::operator*=(float& other)
{
	this->x *= other;
	this->y *= other;

	return *this;
}

MultiExtend::Vector2& MultiExtend::Vector2::operator*=(Vector2&& other)
{
	this->x *= other.x;
	this->y *= other.y;

	return *this;
}

MultiExtend::Vector2& MultiExtend::Vector2::operator*=(Vector2& other)
{
	*this *= (std::move(other));

	return *this;
}

MultiExtend::Vector2& MultiExtend::Vector2::operator*=(Vector3&& other)
{
	this->x *= other.x;
	this->y *= other.y;

	return *this;
}

MultiExtend::Vector2& MultiExtend::Vector2::operator*=(Vector3& other)
{
	*this *= (std::move(other));

	return *this;
}

std::ostream& operator<<(std::ostream& out, const MultiExtend::Vector2& vector)
{
	out << "(" << vector.x << "," << vector.y << ")";
	return out;
}

MultiExtend::Vector3::Vector3()
	:x(0),y(0),z(0)
{
}


MultiExtend::Vector3::Vector3(float num)
	:x(num), y(num), z(num)
{}

MultiExtend::Vector3::Vector3(float i_x, float i_y, float i_z)
	:x(i_x), y(i_y), z(i_z)
{}

MultiExtend::Vector3::Vector3(const Vector3& other)
{
	this->x = other.x;
	this->y = other.y;
	this->z = other.z;
}

MultiExtend::Vector3::Vector3(Vector2&& other) noexcept
{
	this->x = other.x;
	this->y = other.y;
	this->z = 0;
}

MultiExtend::Vector3::Vector3(const Vector2& other)
{
	this->x = other.x;
	this->y = other.y;
	this->z = 0;
}

MultiExtend::Vector3::Vector3(Vector3&& other) noexcept
{
	this->x = other.x;
	this->y = other.y;
	this->z = other.z;
}

MultiExtend::Vector3& MultiExtend::Vector3::operator=(MultiExtend::Vector3&& other) noexcept
{
	this->x = other.x;
	this->y = other.y;
	this->z = other.z;

	return *this;
}

MultiExtend::Vector3& MultiExtend::Vector3::operator=(const MultiExtend::Vector3& other)
{
	this->x = other.x;
	this->y = other.y;
	this->z = other.z;

	return *this;
}

MultiExtend::Vector3 MultiExtend::Vector3::operator*(Vector3& other)
{
	return Vector3(x*other.x,y*other.y,z*other.z);
}

MultiExtend::Vector3 MultiExtend::Vector3::operator*(float num)
{
	
	return Vector3(x * num, y * num, z * num);
}

MultiExtend::Vector3& MultiExtend::Vector3::operator+=(float& num)
{
	this->x += num;
	this->y += num;
	this->z += num;

	return *this;
}

MultiExtend::Vector3& MultiExtend::Vector3::operator+=(Vector3& other)
{
	*this += std::move(other);
	return *this;
}

MultiExtend::Vector3& MultiExtend::Vector3::operator+=(Vector3&& other)
{
	this->x += other.x;
	this->y += other.y;
	this->z += other.z;

	return *this;
}

float MultiExtend::Vector3::length()
{
	return (float)(sqrt(pow(x, 2) + pow(y, 2) + pow(z,2)));
}

MultiExtend::Vector3 MultiExtend::Vector3::normalize()
{
	float len = length();

	return Vector3(x/len,y/len,z/len);
}

MultiExtend::Vector3::~Vector3() = default;

std::ostream& operator<<(std::ostream& out, const MultiExtend::Vector3& vector)
{
	out << "(" << vector.x << "," << vector.y << "," << vector.z << ")";
	return out;
}

std::ostream& operator<<(std::ostream& out, const MultiExtend::Vector4& vector)
{
	out << "(" << vector.x << "," << vector.y << "," << vector.z << "," << vector.w << ")";
	return out;
}

MultiExtend::Vector4::Vector4()
	:x(0),y(0),z(0),w(0)
{
}

MultiExtend::Vector4::~Vector4()
{
}
