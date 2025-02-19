#pragma once

#include "Event/Event.h"
#include "Config/KeyCodes.h"

namespace MultiExtend
{
	class KeyEvent : public Event
	{
	public:
		MULTIEXTEND_API KeyCode GetKeyCode() const { return m_KeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	
	protected:
		MULTIEXTEND_API KeyEvent(const KeyCode keycode)
			: m_KeyCode(keycode) {}

	protected:
		KeyCode m_KeyCode;
	};

	class KeyPressedEvent : public KeyEvent
	{
	public:
		MULTIEXTEND_API KeyPressedEvent(const KeyCode keycode, bool isRepeat = false)
			: KeyEvent(keycode), m_IsRepeat(isRepeat) {}

		MULTIEXTEND_API bool IsRepeat() const { return m_IsRepeat; }

		MULTIEXTEND_API std::string ToString() const override
		{
			std::stringstream ss;
			ss << MULTIEXTEND_CNAME(KeyPressedEvent) << ":" << m_KeyCode << " (repeat = " << m_IsRepeat << ")";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
	
	private:
		bool m_IsRepeat;
	};

	class KeyReleasedEvent : public KeyEvent
	{
	public:
		MULTIEXTEND_API KeyReleasedEvent(const KeyCode keycode)
			: KeyEvent(keycode) {}

		MULTIEXTEND_API std::string ToString() const override
		{
			std::stringstream ss;
			ss << MULTIEXTEND_CNAME(KeyReleasedEvent) << ":" << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};

	class KeyTypedEvent : public KeyEvent
	{
	public:
		MULTIEXTEND_API KeyTypedEvent(const KeyCode keycode)
			: KeyEvent(keycode) {}

		MULTIEXTEND_API std::string ToString() const override
		{
			std::stringstream ss;
			ss << MULTIEXTEND_CNAME(KeyTypedEvent) << ":" << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyTyped)
	};
}