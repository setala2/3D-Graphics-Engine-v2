#include "pch.h"
#include "Window.h"
#include "ApplicationEvent.h"
#include "MouseEvent.h"
#include "KeyEvent.h"

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

		int32_t GetWidth() const;
		int32_t GetHeight() const;
		float GetAspectRatio() const;

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

	int32_t Window::Impl::GetWidth() const
	{
		return properties.width;
	}

	int32_t Window::Impl::GetHeight() const
	{
		return properties.height;
	}

	float Window::Impl::GetAspectRatio() const
	{
		return static_cast<float>(GetWidth()) / static_cast<float>(GetHeight());
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
			MouseMoveEvent event(static_cast<float>(x), static_cast<float>(y));
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
			MouseScrollEvent event(static_cast<float>(xoffset), static_cast<float>(yoffset));
			props.EventCallback(event);
		});

		glfwSetKeyCallback(glfwPointer, [](GLFWwindow* window, int key, int scancode, int action, int modifiers)
		{
			WindowProperties& props = *(WindowProperties*)glfwGetWindowUserPointer(window);
			KeyEvent event(static_cast<Keycode>(key), static_cast<Action>(action));
			props.EventCallback(event);
		});

		glfwSetCharCallback(glfwPointer, [](GLFWwindow* window, uint32_t codePoint)
		{
			WindowProperties& props = *(WindowProperties*)glfwGetWindowUserPointer(window);
			CharEvent event(codePoint);
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

	int32_t Window::GetWidth() const
	{
		return pImpl->GetWidth();
	}

	int32_t Window::GetHeight() const
	{
		return pImpl->GetHeight();
	}

	float Window::GetAspectRatio() const
	{
		return pImpl->GetAspectRatio();
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