#include "pch.h"
#include "Application.h"

namespace as3d
{
	Application::Application()
	{
		window = std::make_unique<Window>(WindowProperties{});
		window->MakeCurrent();
		window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
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
		// For now, we'll be tracing any implemented events for debugging

		switch (event.GetType())
		{
		case EventType::WindowCloseEvent: OnWindowClose(event); break;
		case EventType::WindowResizeEvent: OnWindowResize(event); break;
		case EventType::MouseMoveEvent: OnMouseMove(event); break;
		}

		// We'll eventually call the OnEvent-method of other objects here

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

	void Application::OnMouseMove(Event& event)
	{
		event.handled = true;
	}
}