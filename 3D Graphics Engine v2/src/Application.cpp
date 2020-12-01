#include "pch.h"
#include "Application.h"
#include "Gldebug.h"
#include "VertexArray.h"

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
		// Making sure it doesn't instantly crash
		float test[]{ 1.0f, 2.0f, 3.0f, 4.0f };
		BufferLayout layout;
		layout.Push<float>(2);
		layout.Push<float>(2);
		VertexBuffer vbo(test, sizeof(test));
		VertexArray vao;
		vao.AddBuffer(vbo, layout);

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