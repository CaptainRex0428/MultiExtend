#include "Math/Vector.h"

#include <utility>
#include <math.h>

#include "Math/Math.h"

#define VectorNDebug

Vector2::Vector2()
	:x(0),y(0)
{
}

Vector2::Vector2(float num)
	:x(num), y(num)
{
}

Vector2::Vector2(float i_x, float i_y)
	:x(i_x), y(i_y)
{
}

Vector2::~Vector2() = default;

Vector2::Vector2(const Vector2& other)
{
	x = other.x;
	y = other.y;
}

Vector2::Vector2(Vector2&& other) noexcept
{
	x = other.x;
	y = other.y;
}

Vector2& Vector2::operator=(const Vector2& other)
{
	x = other.x;
	y = other.y;

	return *this;
}


Vector2 Vector2::operator+(Vector2& other)
{
	return Vector2(x + other.x, y + other.y);
}

Vector2 Vector2::operator+(float num)
{
	return Vector2(x + num, y + num);
}

Vector2 Vector2::operator-(Vector2& other)
{
	return Vector2(x - other.x, y - other.y);
}

Vector2 Vector2::operator-(float num)
{
	return Vector2(x - num, y - num);
}

Vector2 Vector2::operator*(Vector2& other)
{
	return Vector2(x*other.x,y*other.y);
}

Vector2 Vector2::operator*(float num)
{
	return Vector2(x*num, y*num);
}

Vector2& Vector2::operator+=(Vector2& other)
{
#ifdef VectorDebug
	std::cout << "value:(" << other.x << "," << other.y << ")\n";
#endif
	*this += (std::move(other));
	return *this;
}

Vector2& Vector2::operator+=(Vector2&& other)
{
#ifdef VectorDebug
	std::cout << "value:(" << other.x << "," << other.y << ")\n";
#endif
	this->x += other.x;
	this->y += other.y;
	return *this;
}

Vector2& Vector2::operator+=(float num)
{
	this->x += num;
	this->y += num;
	return *this;
}

float Vector2::length()
{
	return (float)(sqrt(pow(x, 2) + pow(y, 2)));
}

Vector2 Vector2::normalize()
{
	return Vector2(x/length(), y/length());
}

float Vector2::dot(Vector2& va, Vector2& vb)
{
	return va.x * vb.x + va.y * vb.y;
}

Vector3 Vector2::cross(Vector2& va, Vector2& vb)
{
	return Vector3(0, 0, va.x * vb.y - va.y * vb.x);
}

std::ostream& operator<<(std::ostream& out, const Vector2& vector)
{
	out << "(" << vector.x << "," << vector.y << ")";
	return out;
}

Vector3::Vector3()
	:x(0),y(0),z(0)
{
}


Vector3::Vector3(float num)
	:x(num), y(num), z(num)
{}

Vector3::Vector3(float i_x, float i_y, float i_z)
	:x(i_x), y(i_y), z(i_z)
{}

Vector3::Vector3(const Vector3& other)
{
	this->x = other.x;
	this->y = other.y;
	this->z = other.z;
}

Vector3::Vector3(Vector3&& other) noexcept
{
	this->x = other.x;
	this->y = other.y;
	this->z = other.z;
}

Vector3& Vector3::operator=(Vector3&& other) noexcept
{
	this->x = other.x;
	this->y = other.y;
	this->z = other.z;

	return *this;
}

Vector3& Vector3::operator=(const Vector3& other)
{
	this->x = other.x;
	this->y = other.y;
	this->z = other.z;

	return *this;
}

Vector3::~Vector3() = default;

std::ostream& operator<<(std::ostream& out, const Vector3& vector)
{
	out << "(" << vector.x << "," << vector.y << "," << vector.z << ")";
	return out;
}