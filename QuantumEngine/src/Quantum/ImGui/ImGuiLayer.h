#pragma once

#include "Quantum/Core/Layer.h"
#include "Quantum/Events/ApplicationEvent.h"
#include "Quantum/Events/KeyEvent.h"
#include "Quantum/Events/MouseEvent.h"

namespace Quantum {

	class QUANTUM_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};
}