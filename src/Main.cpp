#include "Core/Window.h"
#include "Core/Base.h"
#include "Core/Application.h"

#include "Core/Layer.h"
#include "Core/LayerStack.h"

#include "ImGui_Layer/ImGuiLayer.h"
#include "ImGui/imgui.h"

#include "Core/Input.h"
#include "Core/KeyCodes.h"
#include "Core/MouseButtonCodes.h"

#include "Event/Event.h"
#include "Event/ApplicationEvent.h"

#include "Platform/Win32Window.h"
#include "Renderer/Renderer.h"
#include "Renderer/Buffer.h"
#include "Renderer/VertexArray.h"
#include "Renderer/Shader.h"

class ExampleLayer : public Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		if (Input::IsKeyPressed(GFX_KEY_TAB))
			GFX_TRACE("Tab key is pressed (poll)!");
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello World");
		ImGui::End();
	}

	void OnEvent(Event& event) override
	{
		if (event.GetEventType() == EventType::KeyPressed)
		{
			KeyPressedEvent& e = (KeyPressedEvent&)event;
			if (e.GetKeyCode() == GFX_KEY_TAB)
				GFX_TRACE("Tab key is pressed (event)!");
			GFX_TRACE("{0}", (char)e.GetKeyCode());
		}
	}

};


int main()
{
	Log::Init();
	GFX_WARN("Log Init");
	
	if (!glfwInit())
	{
		GFX_ERROR("Failed to initialise GLFW. Exiting...");
	}

	Application* game = new Application();
	game->PushLayer(new ExampleLayer());
	game->Run();

	delete game;
	
}