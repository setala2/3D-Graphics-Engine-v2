#include "Application.h"

namespace as3d
{
	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (running)
		{

		}
	}

	void Application::Close()
	{
		running = false;
	}
}