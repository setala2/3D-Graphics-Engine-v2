#pragma once
#include "pch.h"
#include "Event.h"

namespace as3d
{
	class WindowCloseEvent : public Event
	{
	public:
		EVENT_TYPE(WindowCloseEvent)
	};

	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(int width, int height);

		EVENT_TYPE(WindowResizeEvent)

		int32_t GetWidth() const { return width; }
		int32_t GetHeight() const { return height; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "Window resize event: " << width << ", " << height;
			return ss.str();
		}

	private:
		int32_t width, height;
	};
}
