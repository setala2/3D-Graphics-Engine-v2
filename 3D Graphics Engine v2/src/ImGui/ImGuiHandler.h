#pragma once
#include <cstdint>
#include "imgui.h"
#include "Event.h"
#include "KeyEvent.h"
#include "MouseEvent.h"
#include "Window.h"

namespace as3d
{
	class ImGuiHandler
	{
	public:
		ImGuiHandler(const Window* window);
		~ImGuiHandler();
		ImGuiHandler(const ImGuiHandler&) = delete;
		ImGuiHandler& operator=(const ImGuiHandler&) = delete;

		void BeginFrame() const;
		void EndFrame() const;

		void OnEvent(Event& event);

	private:
		static uint8_t refCount;

		void OnMouseButtonEvent(MouseButtonEvent& event);
		void OnMouseScrollEvent(MouseScrollEvent& event);
		void OnMouseMoveEvent(MouseMoveEvent& event);
		void OnKeyEvent(KeyEvent& event);
	};
}