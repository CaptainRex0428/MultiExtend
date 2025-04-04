#pragma once

#include <stdint.h>

#include "MultiExtendAPI.h"
#include "Vector.h"

#include <iostream>

namespace MultiExtend
{
	template<typename T>
	class Color : public Vector<T, 4>
	{
	public:
		static_assert(std::is_same_v<T, float> || std::is_same_v<T, double> || std::is_same_v<T, long double>, "Member of color must be float, double or long double.");

		Color()
			:Vector<T, 4>{ (T)0, (T)0, (T)0, (T)1}
		{
		};

		Color(const T& r, const T& g, const T& b, const T& a)
			:Vector<T, 4>{ r, g, b, a }
		{
		};

		Color(std::initializer_list<T> InitializeList)
		{
			assert(InitializeList.size() == 4 && "[Color] Invalid initializer list size");
			std::copy(InitializeList.begin(), InitializeList.end(), this->data.begin());
		};

		Color(const Vector<T, 4>& color)
			:Vector<T, 4>(color)
		{
		};

		Color(const Vector<T, 3>& color)
			:Vector<T, 4>{ color[0], color[1], color[2], (T)1 }
		{
		
		};

		template<typename V>
		Color(const V& r, const V& g, const V& b, const V& a = 255)
			:Vector<T, 4>{ (T)r / 255, (T)g / 255, (T)b / 255, (T)a / 255 }
		{
		};

		T GetBrightness()
		{	
			return this->data[0] * 0.299 + this->data[1] * 0.587 + this->data[2] * 0.114;
		}

		T GetSaturation()
		{
			T max = Math::Max(this->data[0], this->data[1], this->data[2]);
			T min = Math::Min(this->data[0], this->data[1], this->data[2]);

			if (max == 0) return 0;

			return ((max - min)/max);
		}
	};

}