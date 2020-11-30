#include "pch.h"
#include "Window.h"

#ifdef WINDOWLIB_GLFW
#include <GLFW/glfw3.h>
#endif

namespace as3d
{
#ifdef WINDOWLIB_GLFW
	class Window::Impl
	{
	public:
		Impl(const WindowProperties& props);
		~Impl();

		void MakeCurrent();
		void Update();

		GLFWwindow* GetWindowPointer();
	private:
		static uint8_t windowCount;
		WindowProperties properties;
		GLFWwindow* glfwPointer;
	};

	uint8_t Window::Impl::windowCount = 0;

	Window::Impl::Impl(const WindowProperties& props)
		:properties(props)
	{
		glfwSetErrorCallback([](int code, const char* description)
		{
			std::cerr << "[GLFW error " << code << "]: " << description << '\n';
		});

		if (windowCount++ == 0)
			glfwInit();

		glfwPointer = glfwCreateWindow(props.width, props.height, props.title.c_str(), nullptr, nullptr);
		glfwSetWindowUserPointer(glfwPointer, &properties);
	}

	Window::Impl::~Impl()
	{
		if (--windowCount == 0)
			glfwTerminate();
	}

	void Window::Impl::MakeCurrent()
	{
		glfwMakeContextCurrent(glfwPointer);
	}

	void Window::Impl::Update()
	{
		glfwPollEvents();
		glfwSwapBuffers(glfwPointer);
	}

	GLFWwindow* Window::Impl::GetWindowPointer()
	{
		return glfwPointer;
	}

#endif

	Window::Window(const WindowProperties& props)
		:pImpl(std::make_unique<Impl>(props))
	{
	}

	Window::~Window()
	{
	}

	void Window::MakeCurrent()
	{
		pImpl->MakeCurrent();
	}

	void Window::Update()
	{
		pImpl->Update();
	}

	void* Window::GetWindowPointer() const
	{
		return reinterpret_cast<void*>(pImpl->GetWindowPointer());
	}

}