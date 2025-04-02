#include "Math/Vector.h"

#include <utility>
#include <math.h>

#include "Math/Math.h"

#define VectorNDebug

MultiExtend::Vector2::Vector2()
	:x(0),y(0)
{
}

MultiExtend::Vector2::Vector2(float& num)
{	
	x = num;
	y = num;
}

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

MultiExtend::Vector2::Vector2(std::initializer_list<float> InitializeList)
	:x(0), y(0)
{
	size_t size = InitializeList.size();

	if (size == 1)
	{
		x = *InitializeList.begin();
		y = 0;
	}

	if (size > 1)
	{
		x = *InitializeList.begin();
		y = *(InitializeList.begin()+1);
	}
}

MultiExtend::Vector2::~Vector2() = default;

MultiExtend::Vector2& MultiExtend::Vector2::operator=(const MultiExtend::Vector2& other)
{
	x = other.x;
	y = other.y;

	return *this;
}


MultiExtend::Vector2 MultiExtend::Vector2::operator+(MultiExtend::Vector2& other)
{
	return Vector2{x + other.x, y + other.y};
}

MultiExtend::Vector2 MultiExtend::Vector2::operator+(float& num)
{
	return Vector2{x + num, y + num};
}

MultiExtend::Vector2 MultiExtend::Vector2::operator-(MultiExtend::Vector2& other)
{
	return Vector2{x - other.x, y - other.y};
}

MultiExtend::Vector2 MultiExtend::Vector2::operator-(float& num)
{
	return Vector2{x - num, y - num};
}

MultiExtend::Vector2 MultiExtend::Vector2::operator*(Vector3&& other)
{
	Vector3 o = other;
	return *this * o;
}

MultiExtend::Vector2 MultiExtend::Vector2::operator*(Vector3& other)
{
	return Vector2{x * other.x, y * other.y};
}

MultiExtend::Vector2 MultiExtend::Vector2::operator*(MultiExtend::Vector2& other)
{
	return Vector2{x*other.x,y*other.y};
}

MultiExtend::Vector2 MultiExtend::Vector2::operator*(Vector2&& other)
{
	Vector2 o = other;
	return *this * o;
}

MultiExtend::Vector2 MultiExtend::Vector2::operator*(float& num)
{
	return MultiExtend::Vector2{x*num, y*num};
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
	
	if (len == 0)
	{
		return {0,0};
	}

	if(len!=1)
	{
		return Vector2{x / len, y / len};
	}
	
	return *this;
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

MultiExtend::Vector3::Vector3(float& num)
{
	x = num;
	y = num;
	z = num;
}

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

MultiExtend::Vector3::Vector3(std::initializer_list<float> InitializeList)
	:x(0), y(0), z(0)
{
	size_t size = InitializeList.size();

	if (size == 1)
	{
		x = *InitializeList.begin();
		y = 0;
		z = 0;
	}

	if (size == 2)
	{
		x = *InitializeList.begin();
		y = *(InitializeList.begin() + 1);
		z = 0;
	}

	if (size > 2)
	{
		x = *InitializeList.begin();
		y = *(InitializeList.begin() + 1);
		z = *(InitializeList.begin() + 2);
	}
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
	return Vector3{x*other.x,y*other.y,z*other.z};
}

MultiExtend::Vector3 MultiExtend::Vector3::operator*(float& num)
{
	
	return Vector3{x * num, y * num, z * num};
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

	if (len == 0)
	{
		return {0,0,0};
	}

	if(len != 1)
	{
		return Vector3{x / len, y / len, z / len};
	}

	return *this;
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

MultiExtend::Vector4::Vector4(float& num)
{
	x = num;
	y = num;
	z = num;
	w = num;
}

MultiExtend::Vector4::Vector4(Vector4&& other) noexcept
{
	x = other.x;
	y = other.y;
	z = other.z;
	w = other.w;
}

MultiExtend::Vector4::Vector4(const Vector4& other)
{
	x = other.x;
	y = other.y;
	z = other.z;
	w = other.w;
}

MultiExtend::Vector4::Vector4(Vector2&& other) noexcept
{
	x = other.x;
	y = other.y;
	z = 0;
	w = 0;
}

MultiExtend::Vector4::Vector4(const Vector2& other)
{
	x = other.x;
	y = other.y;
	z = 0;
	w = 0;
}

MultiExtend::Vector4::Vector4(const Vector2& otherA, const Vector2& otherB)
{
	x = otherA.x;
	y = otherA.y;
	z = otherB.x;
	w = otherB.y;
}

MultiExtend::Vector4::Vector4(Vector3&& other, float w_in) noexcept
{
	x = other.x;
	y = other.y;
	z = other.z;
	w = w_in;
}

MultiExtend::Vector4::Vector4(const Vector3& other, float w_in)
{
	x = other.x;
	y = other.y;
	z = other.z;
	w = w_in;
}

MultiExtend::Vector4::Vector4(std::initializer_list<float> InitializeList)
	:x(0), y(0), z(0), w(0)
{
	size_t size = InitializeList.size();

	if (size == 1)
	{
		x = *InitializeList.begin();
		y = 0;
		z = 0;
		w = 0;
	}

	if (size == 2)
	{
		x = *InitializeList.begin();
		y = *(InitializeList.begin() + 1);
		z = 0;
		w = 0;
	}

	if (size == 3)
	{
		x = *InitializeList.begin();
		y = *(InitializeList.begin() + 1);
		z = *(InitializeList.begin() + 2);
		w = 0;
	}

	if (size == 4)
	{
		x = *InitializeList.begin();
		y = *(InitializeList.begin() + 1);
		z = *(InitializeList.begin() + 2);
		w = *(InitializeList.begin() + 3);
	}
}


MultiExtend::Vector4::~Vector4()
{
}

float MultiExtend::Vector4::length(bool dimensionalityReduction)
{
	return (float)(sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2) + dimensionalityReduction ? 0 : pow(w,2)));
}

MultiExtend::Vector4 MultiExtend::Vector4::normalize(bool dimensionalityReduction)
{
	float len = length(dimensionalityReduction);

	if (len == 0)
	{
		return { 0,0,0,(dimensionalityReduction ? 1.f : 0 )};
	}

	if (len != 1)
	{
		return Vector3{ x / len, y / len, z / len, dimensionalityReduction ? 1 : w/len };
	}

	return *this;
}

MultiExtend::Vector3 MultiExtend::Cross(const Vector2& vectorA, const Vector2& vectorB)
{
	return Vector3{0,0,vectorA.x * vectorB.y - vectorA.y * vectorB.x};
}

MultiExtend::Vector3 MultiExtend::Cross(const Vector3& vectorA, const Vector3& vectorB)
{
	return Vector3{vectorA.y*vectorB.z-vectorA.z*vectorB.y,
				   vectorA.z*vectorB.x-vectorA.x*vectorB.z,
				   vectorA.x*vectorB.y-vectorA.y*vectorB.x};
}

float MultiExtend::Dot(const Vector2& vectorA, const Vector2& vectorB)
{
	return vectorA.x*vectorB.x + vectorA.y*vectorB.y;
}

float MultiExtend::Dot(const Vector3& vectorA, const Vector3& vectorB)
{
	return vectorA.x * vectorB.x + vectorA.y * vectorB.y + vectorA.z * vectorB.z;
}

float MultiExtend::Dot(const Vector4& vectorA, const Vector4& vectorB, bool dimensionalityReduction)
{
	return vectorA.x * vectorB.x + vectorA.y * vectorB.y + vectorA.z * vectorB.z + dimensionalityReduction ? 0 : (vectorA.w * vectorB.w);
}
