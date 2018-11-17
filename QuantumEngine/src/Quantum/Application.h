#pragma once

#include "Core.h"

namespace Quantum {

	class QUANTUM_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// Client defines this
	Application* CreateApplication();
}