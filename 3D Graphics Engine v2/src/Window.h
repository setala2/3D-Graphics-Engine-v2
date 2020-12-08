#pragma once
#include <cstdint>
#include <string>
#include <memory>
#include <functional>

#include "Event.h"

namespace as3d
{
	struct WindowProperties
	{
		// Using signed ints here since glfw size callback uses them as well
		int32_t width = 1280;
		int32_t height = 720;

		std::string title = "Graphics Engine v2";
		std::function<void(Event&)> EventCallback;
	};

	class Window
	{
		// I'll probably never change the windowing library from glfw but I'm going to abstract it away anyway
		class Impl;
		std::unique_ptr<Impl> pImpl;
	public:
		Window(const WindowProperties& props);
		~Window();
		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;

		int32_t GetWidth() const;
		int32_t GetHeight() const;
		float GetAspectRatio() const;

		void MakeCurrent();
		void Update();

		void SetEventCallback(const std::function<void(Event&)>& callback);

		void* GetWindowPointer() const;
	};
}
