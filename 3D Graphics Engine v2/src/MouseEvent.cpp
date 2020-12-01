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
}