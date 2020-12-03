#include "pch.h"
#include "MouseEvent.h"

namespace as3d
{
	MouseMoveEvent::MouseMoveEvent(float x, float y)
		:x(x), y(y)
	{	}

	std::string MouseMoveEvent::ToString() const
	{
		std::stringstream ss;
		ss << "Mouse move event: " << x << ", " << y;
		return ss.str();
	}

	MouseButtonEvent::MouseButtonEvent(Mousecode button, Action action)
		: button(button), action(action)
	{	}

	// For testing and debugging
	std::string MouseButtonEvent::ToString() const
	{
		std::stringstream ss;
		ss << "Mouse button event:\n" <<
			"Button " << AsInt(button) << '\n' <<
			"Action " << AsInt(action);
		return ss.str();
	}

	MouseScrollEvent::MouseScrollEvent(float x, float y)
		:xOffset(x), yOffset(y)
	{	}

	std::string MouseScrollEvent::ToString() const
	{
		std::stringstream ss;
		ss << "Mouse scroll event: " << xOffset << ", " << yOffset;
		return ss.str();
	}
}