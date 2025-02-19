#pragma once
#include <functional>

#include <type_traits>
#include "MultiExtendAPI.h"

#include <string>

// 前置声明
template <typename T>
class HashGenerator;

// 基础哈希实现
namespace HashGeneratorImpl {
	template <typename T>
	size_t hash_impl(const T& value) {
		return std::hash<std::decay_t<T>>{}(value);
	}

	template <typename T>
	size_t hash_pointer_impl(const T* ptr) {
		return ptr ? HashGenerator<T>::generate(*ptr) : 0;
	}

	template <typename T, size_t N>
	size_t hash_array_impl(const T(&arr)[N]) {
		size_t hash = 0;
		for (const auto& item : arr) {
			hash ^= HashGenerator<T>::generate(item) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
		}
		return hash;
	}
}

// 主模板类
template <typename T>
class HashGenerator {
public:
	static size_t generate(const T& value) {
		if constexpr (std::is_array_v<T>) {
			return HashGeneratorImpl::hash_array_impl(value);
		}
		else if constexpr (std::is_pointer_v<T>) {
			return HashGeneratorImpl::hash_pointer_impl(value);
		}
		else {
			return HashGeneratorImpl::hash_impl(value);
		}
	}
};