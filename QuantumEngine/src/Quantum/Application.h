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

namespace Quantum {

	class QUANTUM_API Application
	{
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool OnWindowClose(WindowCloseEvent& e);
		LayerStack m_LayerStack;
		static Application* s_Instance;

		unsigned int m_VertexArray;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
	public:
		Application();
		virtual ~Application();

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