#pragma once

#include <iostream>

#include "MultiExtendAPI.h"

namespace MultiExtend
{

	class Vector3
	{
	public:
		MULTIEXTEND_API Vector3();
		MULTIEXTEND_API Vector3(float num);
		MULTIEXTEND_API Vector3(float i_x, float i_y,float i_z);
		MULTIEXTEND_API Vector3(Vector3&& other) noexcept;
		MULTIEXTEND_API Vector3(const Vector3 & other);
		MULTIEXTEND_API ~Vector3();

		MULTIEXTEND_API Vector3& operator=(Vector3&& other) noexcept;
		MULTIEXTEND_API Vector3& operator=(const Vector3& other);

	public:
		float x, y, z;

	};

	class Vector2
	{
	public:
		MULTIEXTEND_API Vector2();
		MULTIEXTEND_API Vector2(float num);
		MULTIEXTEND_API Vector2(float i_x, float i_y);
		MULTIEXTEND_API ~Vector2();

		MULTIEXTEND_API Vector2(const Vector2& other);
		MULTIEXTEND_API Vector2(Vector2&& other) noexcept;

		MULTIEXTEND_API Vector2& operator=(const Vector2& other);

		MULTIEXTEND_API Vector2 operator+(Vector2& other);
		MULTIEXTEND_API Vector2 operator+(float num);

		MULTIEXTEND_API Vector2 operator-(Vector2& other);
		MULTIEXTEND_API Vector2 operator-(float num);

		MULTIEXTEND_API Vector2 operator*(Vector2& other);
		MULTIEXTEND_API Vector2 operator*(float num);

		MULTIEXTEND_API Vector2& operator+=(Vector2&& other);
		MULTIEXTEND_API Vector2& operator+=(Vector2& other);
		MULTIEXTEND_API Vector2& operator+=(float num);

		MULTIEXTEND_API float length();
		MULTIEXTEND_API Vector2 normalize();

		MULTIEXTEND_API static float dot(Vector2& va, Vector2& vb);
		MULTIEXTEND_API static Vector3 cross(Vector2& va, Vector2& vb);

	public:
		float x, y;

	};

	class Vector4
	{

	};


}

MULTIEXTEND_API std::ostream& operator<<(std::ostream& out, const MultiExtend::Vector2& vector);
MULTIEXTEND_API std::ostream& operator<<(std::ostream& out, const MultiExtend::Vector3& vector);