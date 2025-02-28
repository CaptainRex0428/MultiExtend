#pragma once
#include <functional>

#include <type_traits>
#include <string>
#include <initializer_list>

#include "MultiExtendAPI.h"

#include "sha.h"
#include "hex.h"

namespace MultiExtend
{
	class SHAGenerator
	{
	public:
		template <typename... Args>
		inline static std::string GenerateSHA256Hash(Args&&... args)
		{
			auto ToString = [](const auto& arg) {
				std::ostringstream oss;
				oss << arg;
				return oss.str();
				};

			std::string combined;
			size_t n = 0;
			((combined += ToString(args) + (++n < sizeof...(Args) ? "|" : "")), ...);

			// 后续哈希计算逻辑保持不变
			CryptoPP::SHA256 hash;
			std::string digest;

			CryptoPP::StringSource(combined, true,
				new CryptoPP::HashFilter(hash,
					new CryptoPP::HexEncoder(
						new CryptoPP::StringSink(digest))));

			return digest;
		};
	};
	
}