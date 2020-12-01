#include "pch.h"
#include <GL/glew.h>
#include "Application.h"
#include "Gldebug.h"

namespace as3d
{
	Application::Application()
	{
		window = std::make_unique<Window>(WindowProperties{});
		window->MakeCurrent();
		window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));

		if (glewInit() != GLEW_OK)
		{
			std::cerr << "glewInit failed!\n";
			__debugbreak();
		}
		InitDebug();
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (running)
		{
			window->Update();
		}
	}

	void Application::Close()
	{
		running = false;
	}

	void Application::OnEvent(Event& event)
	{
		switch (event.GetType())
		{
		case EventType::WindowCloseEvent: OnWindowClose(event); break;
		case EventType::WindowResizeEvent: OnWindowResize(event); break;
		}

		// We'll eventually call the OnEvent-method of other objects here

		// For now, we'll be tracing any implemented events for debugging
		std::cout << event << '\n';
	}

	void Application::OnWindowClose(Event& event)
	{
		event.handled = true;
		Close();
	}

	void Application::OnWindowResize(Event& event)
	{
		event.handled = true;
	}

}