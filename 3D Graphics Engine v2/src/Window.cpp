#include "Window.h"

namespace as3d
{
	class Window::Impl
	{
	public:
		Impl(const WindowProperties& props);
		~Impl();

		void MakeCurrent();
		void Update();

		void* GetWindowPointer();
	private:
		static uint8_t windowCount;
		WindowProperties properties;
	};

	uint8_t Window::Impl::windowCount = 0;

	Window::Impl::Impl(const WindowProperties& props)
	{
	}

	Window::Impl::~Impl()
	{
	}

	void Window::Impl::MakeCurrent()
	{
	}

	void Window::Impl::Update()
	{
	}

	void* Window::Impl::GetWindowPointer()
	{
		return nullptr;
	}

	Window::Window(const WindowProperties& props)
		:pImpl(std::make_unique<Impl>(props))
	{
	}

	Window::~Window()
	{
	}

	void Window::MakeCurrent()
	{
	}

	void Window::Update()
	{
	}

	void* Window::GetWindowPointer() const
	{
		return nullptr;
	}

}