#include "pch.h"
#include "Application.h"
#include "Gldebug.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Input.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace as3d
{
	Application::Application()
	{
		window = std::make_unique<Window>(WindowProperties{});
		window->MakeCurrent();
		window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));

		glm::mat4 projectionMatrix = glm::perspective(Camera::defaultFOV, window->GetAspectRatio(), 0.1f, 100.0f);
		camera = std::make_unique<Camera>(projectionMatrix, input);

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
		////////////////////////////////////////////////////////////////////////////////////////
		//	There will be a lot of stuff here before I figure out a better way to organize it
		////////////////////////////////////////////////////////////////////////////////////////

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
			shader.SetMatrix4("viewMatrix", camera->GetViewMatrix());
			shader.SetMatrix4("projectionMatrix", camera->GetProjectionMatrix());

			renderer.Clear();
			vao.Bind();
			glDrawArrays(GL_TRIANGLES, 0, 3);
			window->Update();

			camera->OnUpdate(1.0f);
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
		camera->SetProjectionMatrix(glm::perspective(Camera::defaultFOV, window->GetAspectRatio(), 0.1f, 100.0f));
		renderer.SetViewPort(window->GetWidth(), window->GetHeight());
		event.handled = true;
	}

}