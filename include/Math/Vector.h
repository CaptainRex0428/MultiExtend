#pragma once

#include <iostream>

#include "MultiExtendAPI.h"

namespace MultiExtend
{
	class Vector2;
	class Vector3;
	class Vector4;

	class Vector2
	{
	public:
		MULTIEXTEND_API Vector2();
		MULTIEXTEND_API Vector2(float& num);

		MULTIEXTEND_API Vector2(Vector2&& other) noexcept;
		MULTIEXTEND_API Vector2(const Vector2& other);

		MULTIEXTEND_API Vector2(std::initializer_list<float> InitializeList);

		MULTIEXTEND_API ~Vector2();

		MULTIEXTEND_API float length();
		MULTIEXTEND_API Vector2 normalize();

		MULTIEXTEND_API Vector2& operator=(Vector2&& other) noexcept;
		MULTIEXTEND_API Vector2& operator=(const Vector2& other);

		MULTIEXTEND_API Vector2 operator+(float& num);
		MULTIEXTEND_API Vector2 operator+(Vector2& other);

		MULTIEXTEND_API Vector2 operator-(float& num);
		MULTIEXTEND_API Vector2 operator-(Vector2& other);

		MULTIEXTEND_API Vector2 operator*(float& num);
		MULTIEXTEND_API Vector2 operator*(Vector2&& other);
		MULTIEXTEND_API Vector2 operator*(Vector2& other);
		MULTIEXTEND_API Vector2 operator*(Vector3&& other);
		MULTIEXTEND_API Vector2 operator*(Vector3& other);


		MULTIEXTEND_API Vector2& operator+=(float& num);
		MULTIEXTEND_API Vector2& operator+=(Vector2&& other);
		MULTIEXTEND_API Vector2& operator+=(Vector2& other);

		MULTIEXTEND_API Vector2& operator*=(float& other);
		MULTIEXTEND_API Vector2& operator*=(Vector2&& other);
		MULTIEXTEND_API Vector2& operator*=(Vector2& other);
		MULTIEXTEND_API Vector2& operator*=(Vector3&& other);
		MULTIEXTEND_API Vector2& operator*=(Vector3& other);

	public:
		float x, y;

	};

	class Vector3
	{
	public:
		MULTIEXTEND_API Vector3();
		MULTIEXTEND_API Vector3(float& num);

		MULTIEXTEND_API Vector3(Vector3&& other) noexcept;
		MULTIEXTEND_API Vector3(const Vector3& other);

		MULTIEXTEND_API Vector3(Vector2&& other) noexcept;
		MULTIEXTEND_API Vector3(const Vector2& other);

		MULTIEXTEND_API Vector3(std::initializer_list<float> InitializeList);

		MULTIEXTEND_API ~Vector3();

		MULTIEXTEND_API float length();
		MULTIEXTEND_API Vector3 normalize();

		MULTIEXTEND_API Vector3& operator=(Vector3&& other) noexcept;
		MULTIEXTEND_API Vector3& operator=(const Vector3& other);

		MULTIEXTEND_API Vector3 operator*(Vector3& other);
		MULTIEXTEND_API Vector3 operator*(float& num);

		MULTIEXTEND_API Vector3& operator+=(float& num);
		MULTIEXTEND_API Vector3& operator+=(Vector3&& other);
		MULTIEXTEND_API Vector3& operator+=(Vector3& other);

	public:
		float x, y, z;

	};

	class Vector4
	{
	public:
		MULTIEXTEND_API Vector4();
		MULTIEXTEND_API Vector4(float& num);

		MULTIEXTEND_API Vector4(Vector4&& other) noexcept;
		MULTIEXTEND_API Vector4(const Vector4& other);

		MULTIEXTEND_API Vector4(Vector2&& other) noexcept;
		MULTIEXTEND_API Vector4(const Vector2& other);
		MULTIEXTEND_API Vector4(const Vector2& otherA, const Vector2& otherB);

		MULTIEXTEND_API Vector4(Vector3&& other, float w = 0) noexcept;
		MULTIEXTEND_API Vector4(const Vector3& other, float w = 0);

		MULTIEXTEND_API Vector4(std::initializer_list<float> InitializeList);

		MULTIEXTEND_API ~Vector4();

		MULTIEXTEND_API float length(bool dimensionalityReduction = true);
		MULTIEXTEND_API Vector4 normalize(bool dimensionalityReduction = true);

	public:
		float x, y, z, w;
	};


	MULTIEXTEND_API Vector3 Cross(const Vector2& vectorA, const Vector2& vectorB);
	MULTIEXTEND_API Vector3 Cross(const Vector3& vectorA, const Vector3& vectorB);

	MULTIEXTEND_API float Dot(const Vector2& vectorA, const Vector2& vectorB);
	MULTIEXTEND_API float Dot(const Vector3& vectorA, const Vector3& vectorB);
	MULTIEXTEND_API float Dot(const Vector4& vectorA, const Vector4& vectorB, bool dimensionalityReduction = true);

}

MULTIEXTEND_API std::ostream& operator<<(std::ostream& out, const MultiExtend::Vector2& vector);
MULTIEXTEND_API std::ostream& operator<<(std::ostream& out, const MultiExtend::Vector3& vector);
MULTIEXTEND_API std::ostream& operator<<(std::ostream& out, const MultiExtend::Vector4& vector);