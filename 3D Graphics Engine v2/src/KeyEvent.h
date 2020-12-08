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

	class CharEvent : public Event
	{
	public:
		// https://www.glfw.org/docs/latest/input_guide.html#input_char
		CharEvent(uint32_t codePoint);
		EVENT_TYPE(CharEvent);

		uint32_t GetCodePoint() const { return codePoint; }
		virtual std::string ToString() const override;

	private:
		uint32_t codePoint;
	};
}