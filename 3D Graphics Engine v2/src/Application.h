#pragma once

#include <memory>

#include "Window.h"

int main(int argc, char** argv);

namespace as3d
{
	class Application
	{
	private:
		Application();
		~Application();
		Application(const Application&) = delete;
		Application& operator=(const Application&) = delete;

		void Run();
		void Close();

		friend int ::main(int, char**);

	private:
		bool running = true;
		std::unique_ptr<Window> window;
	};
}
