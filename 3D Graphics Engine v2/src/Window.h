#pragma once
#include <cstdint>
#include <string>
#include <memory>

namespace as3d
{
	struct WindowProperties
	{
		uint32_t width = 720;
		uint32_t height = 480;

		std::string title = "Graphics Engine v2";
	};

	class Window
	{
		class Impl;
		std::unique_ptr<Impl> pImpl;
	public:
		Window(const WindowProperties& props);
		~Window();
		Window(const Window&) = delete;
		Window& operator=(const Window&) = delete;

		void MakeCurrent();
		void Update();

		void* GetWindowPointer() const;
	};
}
