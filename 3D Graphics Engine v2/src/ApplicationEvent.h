#pragma once
#include "Event.h"

namespace as3d
{
	class WindowCloseEvent : public Event
	{
	public:
		EVENT_TYPE(WindowCloseEvent);
	};

	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(int width, int height);

		EVENT_TYPE(WindowResizeEvent);

		int32_t GetWidth() const { return width; }
		int32_t GetHeight() const { return height; }

		std::string ToString() const override;

	private:
		int32_t width, height;
	};
}
