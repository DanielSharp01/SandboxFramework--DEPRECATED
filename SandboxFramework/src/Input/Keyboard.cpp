#include "Keyboard.h"

namespace Sand {
	namespace Input {

		KeyboardState Keyboard::actual = KeyboardState();

		void Keyboard::setState(int key, bool state)
		{
			Keyboard::actual.m_States[key] = state;
		}

		void keyboardCallback(GLFWwindow* sender, int key, int scancode, int action, int mods)
		{
			Keyboard::setState(key, action == GLFW_PRESS);
		}
	}
}