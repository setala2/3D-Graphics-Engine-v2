#pragma once

#include "Event.h"
#include "Keycodes.h"

namespace as3d
{
	class MouseMoveEvent : public Event
	{
	public:
		MouseMoveEvent(float x, float y);

		EVENT_TYPE(MouseMoveEvent);

		float GetX() const { return x; }
		float GetY() const { return y; }
		virtual std::string ToString() const override;

	private:
		float x, y;
	};

	class MouseButtonEvent : public Event
	{
	public:
		MouseButtonEvent(Mousecode button, Action action);

		EVENT_TYPE(MouseButtonEvent);

		Mousecode GetButton() { return button; }
		Action GetAction() { return action; }
		virtual std::string ToString() const override;

	private:
		Mousecode button;
		Action action;
	};

	class MouseScrollEvent : public Event
	{
	public:
		MouseScrollEvent(float x, float y);

		EVENT_TYPE(MouseScrollEvent);

		float GetXOffset() const { return xOffset; }
		float GetYOffset() const { return yOffset; }
		virtual std::string ToString() const override;

	private:
		float xOffset, yOffset;
	};
}