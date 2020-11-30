#pragma once

int main(int argc, char** argv);

namespace as3d
{
	class Application
	{
	private:
		Application();
		~Application();

		void Run();
		void Close();

		friend int ::main(int, char**);
	private:
		bool running = true;
	};
}
