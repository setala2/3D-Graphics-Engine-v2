#include "pch.h"
#include "Window.h"
#include "ApplicationEvent.h"
#include "MouseEvent.h"

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

		GLFWwindow* GetWindowPointer() const;
		void SetEventCallback(const std::function<void(Event&)>& callback);
	private:
		static uint8_t windowCount;
		WindowProperties properties;
		GLFWwindow* glfwPointer;
		void SetGlfwCallbacks();
	};

	uint8_t Window::Impl::windowCount = 0;

	Window::Impl::Impl(const WindowProperties& props)
		:properties(props)
	{
		glfwSetErrorCallback([](int code, const char* description)
		{
			std::cerr << "[GLFW error " << code << "]: " << description << '\n';
			__debugbreak();
		});

		if (windowCount++ == 0)
			glfwInit();

		glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE); // Can't use functions that are deprecated in OpenGL 4.3 core
#ifdef _DEBUG
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#else
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_FALSE);
#endif

		glfwPointer = glfwCreateWindow(props.width, props.height, props.title.c_str(), nullptr, nullptr);
		glfwSetWindowUserPointer(glfwPointer, &properties);
		SetGlfwCallbacks();
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

	GLFWwindow* Window::Impl::GetWindowPointer() const
	{
		return glfwPointer;
	}

	void Window::Impl::SetEventCallback(const std::function<void(Event&)>& callback)
	{
		properties.EventCallback = callback;
	}

	void Window::Impl::SetGlfwCallbacks()
	{
		glfwSetWindowCloseCallback(glfwPointer, [](GLFWwindow* window)
		{
			WindowProperties& props = *(WindowProperties*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			props.EventCallback(event);
		});

		glfwSetWindowSizeCallback(glfwPointer, [](GLFWwindow* window, int width, int height)
		{
			WindowProperties& props = *(WindowProperties*)glfwGetWindowUserPointer(window);
			props.width = width;
			props.height = height;

			WindowResizeEvent event(width, height);
			props.EventCallback(event);
		});

		glfwSetCursorPosCallback(glfwPointer, [](GLFWwindow* window, double x, double y)
		{
			WindowProperties& props = *(WindowProperties*)glfwGetWindowUserPointer(window);
			MouseMoveEvent event(x, y);
			props.EventCallback(event);
		});

		glfwSetMouseButtonCallback(glfwPointer, [](GLFWwindow* window, int button, int action, int modifiers)
		{
			WindowProperties& props = *(WindowProperties*)glfwGetWindowUserPointer(window);
			MouseButtonEvent event(static_cast<Mousecode>(button), static_cast<Action>(action));
			props.EventCallback(event);
		});

		glfwSetScrollCallback(glfwPointer, [](GLFWwindow* window, double xoffset, double yoffset)
		{
			WindowProperties& props = *(WindowProperties*)glfwGetWindowUserPointer(window);
			MouseScrollEvent event(xoffset, yoffset);
			props.EventCallback(event);
		});
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

	void Window::SetEventCallback(const std::function<void(Event&)>& callback)
	{
		pImpl->SetEventCallback(callback);
	}

	void* Window::GetWindowPointer() const
	{
		return reinterpret_cast<void*>(pImpl->GetWindowPointer());
	}

}