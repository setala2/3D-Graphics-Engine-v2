#include "pch.h"
#include "Application.h"
#include "Gldebug.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Input.h"

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
		float test[]
		{
			-0.75f, -0.5f, 1.0f, 0.0f, 0.0f,
			0.75f, -0.5f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.75f, 0.0f, 0.0f, 1.0f
		};
		
		BufferLayout layout;
		layout.Push<float>(2);
		layout.Push<float>(3);
		VertexBuffer vbo(test, sizeof(test));
		VertexArray vao;
		vao.AddBuffer(vbo, layout);

		Shader shader("src/shaders/vertex.glsl", "src/shaders/fragment.glsl");
		shader.Bind();

		renderer.SetClearColor(0.8f, 0.2f, 0.1f);

		while (running)
		{
			// std::cout << "Space: " << input.IsKeyDown(Keycode::Space) << '\n';

			renderer.Clear();
			vao.Bind();
			glDrawArrays(GL_TRIANGLES, 0, 3);
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

		// We'll eventually need to get some kind of a container to loop through any objects that listen to events
		if (!event.handled)
		{
			input.OnEvent(event);
		}
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