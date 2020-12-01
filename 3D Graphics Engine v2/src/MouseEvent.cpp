#include "pch.h"
#include "MouseEvent.h"

namespace as3d
{
	MouseMoveEvent::MouseMoveEvent(double x, double y)
		:x(x), y(y)
	{	}

	std::string MouseMoveEvent::ToString() const
	{
		std::stringstream ss;
		ss << "Mouse move event: " << x << ", " << y;
		return ss.str();
	}

	MouseButtonEvent::MouseButtonEvent(int32_t button, int32_t action, int32_t modifiers)
		: button(button), action(action), modifiers(modifiers)
	{	}

	// For testing and debugging
	std::string MouseButtonEvent::ToString() const
	{
		std::stringstream ss;
		ss << "Mouse button event:\n" <<
			"Button " << button << '\n' <<
			"Action " << action;
		return ss.str();
	}

	MouseScrollEvent::MouseScrollEvent(double x, double y)
		:xOffset(x), yOffset(y)
	{	}

	std::string MouseScrollEvent::ToString() const
	{
		std::stringstream ss;
		ss << "Mouse scroll event: " << xOffset << ", " << yOffset;
		return ss.str();
	}
}