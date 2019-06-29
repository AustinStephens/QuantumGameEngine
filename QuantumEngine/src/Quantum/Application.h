#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Window.h"
#include "Quantum/LayerStack.h"
#include "Quantum/Events/Event.h"
#include "Quantum/Events/ApplicationEvent.h"
#include "Quantum/ImGui/ImGuiLayer.h"
#include "Quantum/Renderer/Shader.h"
#include "Quantum/Renderer/Buffer.h"
#include "Quantum/Renderer/VertexArray.h"

namespace Quantum {

	class QUANTUM_API Application
	{
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool OnWindowClose(WindowCloseEvent& e);
		LayerStack m_LayerStack;
		static Application* s_Instance;

		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<VertexArray> m_VertexArray;

		std::shared_ptr<Shader> m_BlueShader;
		std::shared_ptr<VertexArray> m_SquareVA;
	public:
		Application();
		virtual ~Application() = default;

		void Run();
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }
	};

	// Client defines this
	Application* CreateApplication();
}