#pragma once
#include "Keycodes.h"
#include "Event.h"
#include "MouseEvent.h"
#include "KeyEvent.h"
#include <glm/vec2.hpp>

/*
 *
 *	Input is implemented as an object that changes it state by receiving relevant events from the application.
 *	I considered making it a global or a singleton but opted for this instead.
 *
 */

namespace as3d
{
	class Input
	{
	public:
		Input();

		bool IsKeyDown(Keycode keycode) const;

		bool IsMouseButtonDown(Mousecode mousecode) const;
		glm::vec2 GetMousePosition() const;
		float GetMouseX() const;
		float GetMouseY() const;

		void OnEvent(Event& e);

	private:
		std::vector<bool> keyStates;
		std::vector<bool> mouseStates;
		glm::vec2 mousePosition;

	private:
		void OnKeyEvent(KeyEvent& e);
		void OnMouseButtonEvent(MouseButtonEvent& e);
		void OnMouseMoveEvent(MouseMoveEvent& e);
	};
}
