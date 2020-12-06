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
			-1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,	// bottom left front	0	blue
			1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 1.0f,	// bottom right front	1	magenta
			1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,		// top right front		2	white
			-1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f,	// top left front		3	cyan
			-1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,	// bottom left back		4	black
			1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f,	// bottom right back	5	red
			1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 0.0f,	// top right back		6	yellow
			-1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,	// top left back		7	green
		};

		uint32_t testIndices[]
		{
			0,1,2,	// front face
			2,3,0,

			4,0,3,	// left face
			3,7,4,

			3,2,6,	// top face
			6,7,3,

			1,5,6,	// right face
			6,2,1,

			4,5,1,	// bottom face
			1,0,4,

			5,4,7,	// back face
			7,6,5
		};
		
		BufferLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(3);
		VertexBuffer vbo(test, sizeof(test));
		VertexArray vao;
		vao.AddBuffer(vbo, layout);

		Shader shader("src/shaders/vertex.glsl", "src/shaders/fragment.glsl");
		shader.Bind();

		uint32_t ibo;
		glGenBuffers(1, &ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(testIndices), testIndices, GL_STATIC_DRAW);

		renderer.SetClearColor(0.8f, 0.2f, 0.1f);

		lastFrameTime = timer.GetTime();

		renderer.EnableBackFaceCulling(true);
		renderer.EnableDepthTesting(true);

		while (running)
		{
			float deltaTime = timer.GetTime() - lastFrameTime;

			shader.SetMatrix4("viewMatrix", camera->GetViewMatrix());
			shader.SetMatrix4("projectionMatrix", camera->GetProjectionMatrix());

			renderer.Clear();
			vao.Bind();
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
			glDrawElements(GL_TRIANGLES, sizeof(testIndices)/sizeof(uint32_t), GL_UNSIGNED_INT, (void*)0);
			window->Update();

			camera->OnUpdate(deltaTime);

			lastFrameTime = timer.GetTime();
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