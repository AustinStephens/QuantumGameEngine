#include <Quantum.h>
#include "ImGui/imgui.h"

class ExampleLayer : public Quantum::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		if (Quantum::Input::IsKeyPressed(QT_KEY_TAB))
			QT_TRACE("Tab key is pressed (poll)!");
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello World");
		ImGui::End();
	}

	void OnEvent(Quantum::Event& event) override
	{
		if (event.GetEventType() == Quantum::EventType::KeyPressed)
		{
			Quantum::KeyPressedEvent& e = (Quantum::KeyPressedEvent&)event;
			if (e.GetKeyCode() == QT_KEY_TAB)
				QT_TRACE("Tab key is pressed (event)!");
			QT_TRACE("{0}", (char)e.GetKeyCode());
		}
	}

};

class Sandbox : public Quantum::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}
	~Sandbox() {}
};

Quantum::Application* Quantum::CreateApplication() {
	return new Sandbox();
}