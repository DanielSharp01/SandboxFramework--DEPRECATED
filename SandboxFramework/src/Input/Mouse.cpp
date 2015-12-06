#include "Mouse.h"

namespace SandboxFramework
{
	namespace Input
	{
		MouseState Mouse::actual = MouseState();

		void Mouse::setButtonState(int button, bool state)
		{
			Mouse::actual.states[button] = state;
		}

		void Mouse::setCursorState(float x, float y)
		{
			Mouse::actual.position = Math::Vector2(x, y);
		}

		void Mouse::setScrollState(float xoffs, float yoffs)
		{
			Mouse::actual.scroll = Math::Vector2(xoffs, yoffs);
		}

		void cursorPositionCallback(GLFWwindow* sender, double xpos, double ypos)
		{
			Mouse::setCursorState(xpos, ypos);
		}

		void mouseButtonCallback(GLFWwindow* sender, int button, int action, int mods)
		{
			Mouse::setButtonState(button, action == GLFW_PRESS);
		}

		void mouseScrollCallback(GLFWwindow *sender, double xoffs, double yoffs)
		{
			Mouse::setScrollState(xoffs, yoffs);
		}
	}
}