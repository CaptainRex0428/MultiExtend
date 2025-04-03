#include "Math/Vector.h"
#include <utility>
#include <math.h>

bool MultiExtend::Math::NearZero(const MultiExtend::Vector2& src)
{
	return std::abs(src.Length()) < NEARZERO_THRESHOLD;
}

bool MultiExtend::Math::NearZero(const Vector3& src)
{
	return std::abs(src.Length()) < NEARZERO_THRESHOLD;
}

MultiExtend::Vector2 MultiExtend::Math::DegreeToRadians(const Vector2& degree)
{
	return Vector2{ Math::DegreeToRadians(degree[x]), Math::DegreeToRadians(degree[y]) };
}

MultiExtend::Vector3 MultiExtend::Math::DegreeToRadians(const Vector3& degree)
{
	return Vector3{ Math::DegreeToRadians(degree[x]), Math::DegreeToRadians(degree[y]), Math::DegreeToRadians(degree[z]) };
}

MultiExtend::Vector2 MultiExtend::Math::RadiansToDegree(Vector2& radians)
{
	return Vector2{ RadiansToDegree(radians[x]), RadiansToDegree(radians[y]) };
}

MultiExtend::Vector3 MultiExtend::Math::RadiansToDegree(Vector3& radians)
{
	return Vector3{ RadiansToDegree(radians[x]), RadiansToDegree(radians[y]),RadiansToDegree(radians[z]) };
}
