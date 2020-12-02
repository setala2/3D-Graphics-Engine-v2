#pragma once

#include "Event.h"
#include "Keycodes.h"

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

	class MouseButtonEvent : public Event
	{
	public:
		MouseButtonEvent(Mousecode button, Action action);

		EVENT_TYPE(MouseButtonEvent);

		virtual std::string ToString() const override;

	private:
		Mousecode button;
		Action action;
	};

	class MouseScrollEvent : public Event
	{
	public:
		MouseScrollEvent(double x, double y);

		EVENT_TYPE(MouseScrollEvent);

		double GetXOffset() const { return xOffset; }
		double GetYOffset() const { return yOffset; }
		virtual std::string ToString() const override;

	private:
		double xOffset, yOffset;
	};
}