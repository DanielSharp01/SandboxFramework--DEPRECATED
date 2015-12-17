#include "Mouse.h"

namespace Sand
{
	namespace Input
	{
		MouseState Mouse::actual = MouseState();

		void Mouse::setButtonState(int button, bool state)
		{
			Mouse::actual.m_States[button] = state;
		}

		void Mouse::setCursorState(float x, float y)
		{
			Mouse::actual.m_Position = Math::Vector2(x, y);
		}

		void Mouse::setScrollState(float xoffs, float yoffs)
		{
			Mouse::actual.m_Scroll = Math::Vector2(xoffs, yoffs);
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