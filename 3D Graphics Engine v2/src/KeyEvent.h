#pragma once

#include "Keycodes.h"
#include "Event.h"

namespace as3d
{
	class KeyEvent : public Event
	{
	public:
		KeyEvent(Keycode key, Action action);
		EVENT_TYPE(KeyEvent);

		Keycode GetKey() const { return key; }
		Action GetAction() const { return action; }
		virtual std::string ToString() const override;

	private:
		Keycode key;
		Action action;
	};
}