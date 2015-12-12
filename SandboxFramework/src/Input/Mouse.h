#pragma once

#include "MouseState.h"
#include <GLFW\glfw3.h>

namespace SandboxFramework {
	namespace Input {
		class Mouse
		{
		private:
			static MouseState actual;
		public:
			inline static MouseState GetState() { return actual; }
		private:
			static void setButtonState(int button, bool state);
			static void setCursorState(float x, float y);
			static void setScrollState(float x, float y);

			friend void cursorPositionCallback(GLFWwindow* sender, double xpos, double ypos);
			friend void mouseButtonCallback(GLFWwindow* sender, int button, int action, int mods);
			friend void mouseScrollCallback(GLFWwindow *sender, double xoffs, double yoffs);
		};
	}
}