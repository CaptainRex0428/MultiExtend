#pragma once 

#include "MultiExtendAPI.h"
#include "MultiExtendMicro.h"

#include <string>
#include <functional>

#include <sstream>

namespace MultiExtend
{
	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory
	{
		None = 0,
		EventCategoryApplication = MULTIEXTEND_BIT(0),
		EventCategoryInput = MULTIEXTEND_BIT(1),
		EventCategoryKeyboard = MULTIEXTEND_BIT(2),
		EventCategoryMouse = MULTIEXTEND_BIT(3),
		EventCategoryMouseButton = MULTIEXTEND_BIT(4)
	};

#define EVENT_CLASS_TYPE(type)  MULTIEXTEND_API static EventType StaticType() { return EventType::##type; }\
								MULTIEXTEND_API virtual EventType Type() const override { return StaticType(); }\
								MULTIEXTEND_API virtual const char* Name() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) MULTIEXTEND_API virtual int GetCategoryFlags() const override { return category; }

	class Event
	{
	public:
		MULTIEXTEND_API virtual ~Event() = default;

		MULTIEXTEND_API virtual EventType Type() const = 0;
		MULTIEXTEND_API virtual const char* Name() const = 0;
		MULTIEXTEND_API virtual int GetCategoryFlags() const = 0;
		MULTIEXTEND_API virtual std::string ToString() const { return Name(); }

		MULTIEXTEND_API bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}

	public:
		bool m_Handled = false;
	};

	MULTIEXTEND_API std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}

	class EventDispatcher
	{
	public:
		MULTIEXTEND_API EventDispatcher(Event& event)
			: m_Event(event)
		{
		}

		// F will be deduced by the compiler
		template<typename _T, typename _F>
		MULTIEXTEND_API bool Dispatch(const _F& func)
		{
			if (m_Event.Type() == _T::StaticType())
			{
				m_Event.m_Handled |= func(static_cast<_T&>(m_Event));
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};
}