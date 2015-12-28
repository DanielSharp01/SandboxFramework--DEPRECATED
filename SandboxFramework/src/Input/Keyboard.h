#pragma once

#include <GLFW\glfw3.h>
#include "KeyboardState.h"

namespace Sand {
	namespace Input {
		class Keyboard
		{
		private:
			static KeyboardState actual;
		public:
			inline static KeyboardState GetState() { return actual; }
			friend void keyboardCallback(GLFWwindow* sender, int key, int scancode, int action, int mods);
		private:
			static void setState(int key, bool state);
		};
	}
}