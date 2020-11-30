#include "Application.h"

namespace as3d
{
	Application::Application()
	{
		window = std::make_unique<Window>(WindowProperties{});
		window->MakeCurrent();
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
}