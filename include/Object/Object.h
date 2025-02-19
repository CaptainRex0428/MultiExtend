#pragma once

#include "MultiExtendAPI.h"
#include "System/Hash/HashGenerator.h"
#include "Time/Clock/Clock.h"
#include "System/Operator.h"

namespace MultiExtend
{
	class Object
	{
	public:
		MULTIEXTEND_API Object();
		MULTIEXTEND_API virtual ~Object() = default;

		MULTIEXTEND_API size_t GetHash();

		MULTIEXTEND_API void RefreshHash();

	private:
		size_t m_hash;
	};

	template<>
	inline size_t MultiExtend::HashGenerator<Object>::generate(const Object& value)
	{
		const long long time = MultiExtend::Clock::GetCurrentTime_HighRes().time_since_epoch().count();
		std::string mac = MultiExtend::Operator::Get().GetMacAddress();

		size_t timeHash = HashGenerator<long long>::generate(time);
		size_t macHash = HashGenerator<std::string>::generate(mac);

		return timeHash ^ (macHash << 1);
	}
}