#pragma once
#include <string>
#include <mutex>

#include "MultiExtendAPI.h"

namespace MultiExtend
{
	class Operator {
	public:

		MULTIEXTEND_API Operator(const Operator&) = delete;
		MULTIEXTEND_API Operator& operator=(const Operator&) = delete;

		MULTIEXTEND_API static Operator& Get();

		MULTIEXTEND_API int Init();

		// 获取MAC地址
		MULTIEXTEND_API std::string GetMacAddress() const;
		MULTIEXTEND_API int GetHardwareConcurrency() const;

	private:
		MULTIEXTEND_API Operator();

		static std::mutex instanceMutex;

	private:
		std::string m_macAddress;
		int m_hardwareConcurrency;
	};
}
