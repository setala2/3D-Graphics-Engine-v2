#include "pch.h"
#include "ImGui/imgui_impl_opengl3.h"
#include "ImGuiHandler.h"

namespace as3d
{
	ImGuiHandler::ImGuiHandler(const Window* window)
	{
		if (refCount++ == 0)
		{
			IMGUI_CHECKVERSION();
			ImGui::CreateContext();
			
			ImGuiIO& io = ImGui::GetIO();

			io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

			/////////////////////////////////////////////////////////////////////////////////////////////
			// Apparently the event system that we use to update imgui is slow as hell.
			// We'll have to make the double click time longer, to be able to double click anything
			// in imgui. This will fix it for now, but we might want to look at it in the future.
			/////////////////////////////////////////////////////////////////////////////////////////////
			io.MouseDoubleClickTime = 0.80f;

			io.DisplaySize = ImVec2(window->GetWidth(), window->GetHeight());

			io.KeyMap[ImGuiKey_Tab]			= AsInt(Keycode::Tab);
			io.KeyMap[ImGuiKey_LeftArrow]	= AsInt(Keycode::Left);
			io.KeyMap[ImGuiKey_RightArrow]	= AsInt(Keycode::Right);
			io.KeyMap[ImGuiKey_UpArrow]		= AsInt(Keycode::Up);
			io.KeyMap[ImGuiKey_DownArrow]	= AsInt(Keycode::Down);
			io.KeyMap[ImGuiKey_PageUp]		= AsInt(Keycode::Page_up);
			io.KeyMap[ImGuiKey_PageDown]	= AsInt(Keycode::Page_down);
			io.KeyMap[ImGuiKey_Home]		= AsInt(Keycode::Home);
			io.KeyMap[ImGuiKey_End]			= AsInt(Keycode::End);
			io.KeyMap[ImGuiKey_Insert]		= AsInt(Keycode::Insert);
			io.KeyMap[ImGuiKey_Delete]		= AsInt(Keycode::Del);
			io.KeyMap[ImGuiKey_Backspace]	= AsInt(Keycode::Backspace);
			io.KeyMap[ImGuiKey_Space]		= AsInt(Keycode::Space);
			io.KeyMap[ImGuiKey_Enter]		= AsInt(Keycode::Enter);
			io.KeyMap[ImGuiKey_Escape]		= AsInt(Keycode::Escape);
			io.KeyMap[ImGuiKey_KeyPadEnter]	= AsInt(Keycode::Kp_enter);
			io.KeyMap[ImGuiKey_A]			= AsInt(Keycode::A);
			io.KeyMap[ImGuiKey_C]			= AsInt(Keycode::C);
			io.KeyMap[ImGuiKey_V]			= AsInt(Keycode::V);
			io.KeyMap[ImGuiKey_X]			= AsInt(Keycode::X);
			io.KeyMap[ImGuiKey_Y]			= AsInt(Keycode::Y);
			io.KeyMap[ImGuiKey_Z]			= AsInt(Keycode::Z);

			ImGui::StyleColorsDark();
			ImGui_ImplOpenGL3_Init("#version 430");
		}
	}

	ImGuiHandler::~ImGuiHandler()
	{
		if (--refCount == 0)
		{
			ImGui_ImplOpenGL3_Shutdown();
			ImGui::DestroyContext();
		}
	}

	void ImGuiHandler::BeginFrame() const
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();
	}

	void ImGuiHandler::EndFrame() const
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGuiHandler::OnEvent(Event& event)
	{
		// No dynamic casting or pointers, since we check the event type anyway
		switch (event.GetType())
		{
		case EventType::MouseButtonEvent: OnMouseButtonEvent(static_cast<MouseButtonEvent&>(event)); break;
		case EventType::MouseScrollEvent: OnMouseScrollEvent(static_cast<MouseScrollEvent&>(event)); break;
		case EventType::MouseMoveEvent: OnMouseMoveEvent(static_cast<MouseMoveEvent&>(event)); break;
		case EventType::KeyEvent: OnKeyEvent(static_cast<KeyEvent&>(event)); break;
		case EventType::CharEvent: OnCharEvent(static_cast<CharEvent&>(event)); break;
		case EventType::WindowResizeEvent: OnWindowResize(static_cast<WindowResizeEvent&>(event)); break;
		}

	}

	void ImGuiHandler::OnMouseButtonEvent(MouseButtonEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();
		if (event.GetAction() == Action::Press)
			io.MouseDown[AsInt(event.GetButton())] = true;
		else
			io.MouseDown[AsInt(event.GetButton())] = false;

		event.handled = io.WantCaptureMouse;
	}

	void ImGuiHandler::OnMouseScrollEvent(MouseScrollEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseWheel += event.GetYOffset();
		io.MouseWheelH += event.GetXOffset();

		event.handled = io.WantCaptureMouse;
	}

	void ImGuiHandler::OnMouseMoveEvent(MouseMoveEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MousePos = ImVec2(event.GetX(), event.GetY());

		event.handled = io.WantCaptureMouse;
	}

	void ImGuiHandler::OnKeyEvent(KeyEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();
		if(event.GetAction() == Action::Press)
			io.KeysDown[AsInt(event.GetKey())] = true;
		else
			io.KeysDown[AsInt(event.GetKey())] = false;

		// Modifiers are not reliable across systems
		io.KeyCtrl	= io.KeysDown[AsInt(Keycode::Left_control)]	|| io.KeysDown[AsInt(Keycode::Right_control)];
		io.KeyShift	= io.KeysDown[AsInt(Keycode::Left_shift)]	|| io.KeysDown[AsInt(Keycode::Right_shift)];
		io.KeyAlt	= io.KeysDown[AsInt(Keycode::Left_alt)]		|| io.KeysDown[AsInt(Keycode::Right_alt)];
		io.KeySuper = io.KeysDown[AsInt(Keycode::Left_super)]	|| io.KeysDown[AsInt(Keycode::Right_super)];

		event.handled = io.WantCaptureKeyboard && event.GetAction() != Action::Release;	// Never block key release events
	}

	void ImGuiHandler::OnCharEvent(CharEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddInputCharacter(event.GetCodePoint());
	}

	void ImGuiHandler::OnWindowResize(WindowResizeEvent& event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(event.GetWidth(), event.GetHeight());
	}

	uint8_t ImGuiHandler::refCount = 0;
}