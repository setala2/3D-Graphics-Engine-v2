#include "pch.h"
#include "ApplicationEvent.h"

namespace as3d
{
    WindowResizeEvent::WindowResizeEvent(int width, int height)
        :width(width), height(height)
    {}

	std::string WindowResizeEvent::ToString() const
	{
		std::stringstream ss;
		ss << "Window resize event: " << width << ", " << height;
		return ss.str();
	}
}