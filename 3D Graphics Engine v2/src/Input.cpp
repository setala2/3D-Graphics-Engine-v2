#include "pch.h"
#include "Input.h"

namespace as3d
{
	Input::Input()
		: keyStates(348, false), mouseStates(8, false), mousePosition(0.0f)
	{	}

	bool Input::IsKeyDown(Keycode keycode) const
	{
		return keyStates.at(static_cast<size_t>(keycode));
	}

	bool Input::IsMouseButtonDown(Mousecode mousecode) const
	{
		return mouseStates.at(static_cast<size_t>(mousecode));
	}

	glm::vec2 Input::GetMousePosition() const
	{
		return mousePosition;
	}

	float Input::GetMouseX() const
	{
		return mousePosition.x;
	}

	float Input::GetMouseY() const
	{
		return mousePosition.y;
	}

	void Input::OnEvent(Event& e)
	{
		// Don't react to input events, if they have been handled by imgui
		if(!e.handled)
		switch (e.GetType())
		{
		case EventType::KeyEvent: OnKeyEvent(static_cast<KeyEvent&>(e)); break;
		case EventType::MouseButtonEvent: OnMouseButtonEvent(static_cast<MouseButtonEvent&>(e)); break;
		case EventType::MouseMoveEvent: OnMouseMoveEvent(static_cast<MouseMoveEvent&>(e)); break;
		}

	}

	void Input::OnKeyEvent(KeyEvent& e)
	{
		keyStates[static_cast<size_t>(e.GetKey())] = static_cast<bool>(e.GetAction());
	}

	void Input::OnMouseButtonEvent(MouseButtonEvent& e)
	{
		mouseStates[static_cast<size_t>(e.GetButton())] = static_cast<bool>(e.GetAction());
	}

	void Input::OnMouseMoveEvent(MouseMoveEvent& e)
	{
		mousePosition.x = e.GetX();
		mousePosition.y = e.GetY();
	}
}
