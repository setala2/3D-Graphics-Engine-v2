#pragma once

#include <string>
#include <ostream>

// totally stole the idea from the hazel engine
#define EVENT_TYPE(type) virtual EventType GetType() const { return EventType::type; }\
							virtual const char* GetName() const { return #type; }

namespace as3d
{
	enum class EventType
	{
		WindowCloseEvent, WindowResizeEvent, MouseMoveEvent, MouseButtonEvent, MouseScrollEvent, KeyEvent
	};

	class Event
	{
	public:
		virtual ~Event() {};
		bool handled = false;

		virtual EventType GetType() const = 0;
		virtual const char* GetName() const = 0;
		virtual std::string ToString() const { return GetName(); }

		friend std::ostream& operator<<(std::ostream&, const Event& e);
	};
}
