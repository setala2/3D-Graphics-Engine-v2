#include "pch.h"
#include "Application.h"
#include "Gldebug.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Input.h"
#include "IndexBuffer.h"
#include "TestModel.h"

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

		imgui = std::make_unique<ImGuiHandler>(window.get());

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

		Shader shader("res/shaders/vertex.glsl", "res/shaders/fragment.glsl");
		shader.Bind();

		renderer.SetClearColor(0.8f, 0.2f, 0.1f);

		renderer.EnableBackFaceCulling(true);
		renderer.EnableDepthTesting(true);

		// Testing the new model class. The constructor doesn't load anything from disk,
		// it creates the same hardcoded, colorful cube, we've been using before.
		TestModel testModel;

		bool demo = true;
		lastFrameTime = timer.GetTime();

		while (running)
		{
			float deltaTime = timer.GetTime() - lastFrameTime;

			shader.SetMatrix4("viewMatrix", camera->GetViewMatrix());
			shader.SetMatrix4("projectionMatrix", camera->GetProjectionMatrix());

			renderer.Clear();
			testModel.Draw(shader);
			// vao.Bind();
			// ibo.Bind();
			// glDrawElements(GL_TRIANGLES, ibo.GetCount(), ibo.GetType(), (void*)0);

			// ImGui render
			imgui->BeginFrame();

			renderer.DrawControlWindow("Rendering settigns");

			imgui->EndFrame();

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
		
		// Don't even bother sending events forward, if they have been dealt with
		if (!event.handled)
		{
			imgui->OnEvent(event);
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
		// We'll not mark it as handled, since ImGui is interested in window resize events as well
	}

}