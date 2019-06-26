#include "qtpch.h"
#include "WindowsInput.h"

#include "Quantum/Application.h"
#include <GLFW/glfw3.h>

namespace Quantum {

	Input* Input::s_Instance = new WindowsInput();

	bool WindowsInput::IsKeyPressedImpl(int keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInput::IsMouseButtonPressedImpl(int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}

	Vector2 WindowsInput::GetMousePositionImpl()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		return Vector2((float)xpos, (float)ypos);
	}

	float WindowsInput::GetMouseXImpl()
	{
		Vector2 v = GetMousePositionImpl();
		return v.GetX();
	}

	float WindowsInput::GetMouseYImpl()
	{
		Vector2 v = GetMousePositionImpl();
		return v.GetY();
	}

}