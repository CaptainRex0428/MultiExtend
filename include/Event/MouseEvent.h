#pragma once

#include "Event/Event.h"
#include "Config/MouseCodes.h"

namespace MultiExtend
{
	class MouseMovedEvent : public Event
	{
	public:
		MULTIEXTEND_API MouseMovedEvent(const float x, const float y)
			: m_MouseX(x), m_MouseY(y) {}

		MULTIEXTEND_API float GetX() const { return m_MouseX; }
		MULTIEXTEND_API float GetY() const { return m_MouseY; }

		MULTIEXTEND_API std::string ToString() const override
		{
			std::stringstream ss;
			ss << MULTIEXTEND_CNAME(MouseMovedEvent) << ":(" << m_MouseX << ", " << m_MouseY << ")";
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	
	private:
		float m_MouseX, m_MouseY;
	};

	class MouseScrolledEvent : public Event
	{
	public:
		MULTIEXTEND_API MouseScrolledEvent(const float xOffset, const float yOffset)
			: m_XOffset(xOffset), m_YOffset(yOffset) {}

		MULTIEXTEND_API float GetXOffset() const { return m_XOffset; }
		MULTIEXTEND_API float GetYOffset() const { return m_YOffset; }

		MULTIEXTEND_API std::string ToString() const override
		{
			std::stringstream ss;
			ss << MULTIEXTEND_CNAME(MouseScrolledEvent) << ":(" << GetXOffset() << ", " << GetYOffset() << ")";
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	
	private:
		float m_XOffset, m_YOffset;
	};

	class MouseButtonEvent : public Event
	{
	public:
		MULTIEXTEND_API MouseCode GetMouseButton() const { return m_Button; }

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput | EventCategoryMouseButton)
	
	protected:
		MULTIEXTEND_API MouseButtonEvent(const MouseCode button)
			: m_Button(button) {}
	
	protected:
		MouseCode m_Button;
	};

	class MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MULTIEXTEND_API MouseButtonPressedEvent(const MouseCode button)
			: MouseButtonEvent(button) {}

		MULTIEXTEND_API std::string ToString() const override
		{
			std::stringstream ss;
			ss << MULTIEXTEND_CNAME(MouseButtonPressedEvent) << ":" << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MULTIEXTEND_API MouseButtonReleasedEvent(const MouseCode button)
			: MouseButtonEvent(button) {}

		MULTIEXTEND_API std::string ToString() const override
		{
			std::stringstream ss;
			ss << MULTIEXTEND_CNAME(MouseButtonReleasedEvent) << ":" << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};

}