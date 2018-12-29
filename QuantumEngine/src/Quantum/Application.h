#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Window.h"

namespace Quantum {

	class QUANTUM_API Application
	{
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		bool OnWindowClose(WindowCloseEvent& e);
	public:
		Application();
		virtual ~Application();

		void Run();
		void OnEvent(Event& e);
	};

	// Client defines this
	Application* CreateApplication();
}