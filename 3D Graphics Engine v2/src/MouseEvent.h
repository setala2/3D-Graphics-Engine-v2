#pragma once

#include "Event.h"

namespace as3d
{
	class MouseMoveEvent : public Event
	{
	public:
		MouseMoveEvent(double x, double y);

		EVENT_TYPE(MouseMoveEvent);

		double GetX() const { return x; }
		double GetY() const { return y; }
		virtual std::string ToString() const override;

	private:
		double x, y;
	};
}