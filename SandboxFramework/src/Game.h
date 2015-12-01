#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#include <time.h>
#include <iostream>
#include <GLFW/glfw3.h>

#include "Input/Keyboard.h"
#include "Input/Mouse.h"
#include "Graphics/Color.h"

namespace SandboxFramework {
	
	namespace Graphics
	{
		class GraphicsDevice;
	}
	
	class Game
	{
	private:
		int m_Width;
		int m_Height;
		std::string m_Title;

		GLFWwindow *m_Window;
		Graphics::GraphicsDevice* m_Graphics;
	public:
		Game(std::string title);
		~Game();

		void Run();

		inline int GetWidth() const { return m_Width; }
		inline int GetHeight() const { return m_Height; }
		void SetSize(int width, int height);
	protected:
		/*virtual void Initialize() = 0;
		virtual void LoadContent() = 0;
		virtual void Update() = 0;
		virtual void Draw() = 0;
		virtual void UnloadContent() = 0;*/

		void Initialize();
		void LoadContent();
		void Update();
		void Draw();
		void UnloadContent();

		void Exit();
	private:
		bool init();
		void update();
		void draw();

		bool isClosing() const;

		friend static void resizeCallback(GLFWwindow *sender, int width, int height);
		friend static void frameResizeCallback(GLFWwindow *sender, int width, int height);
		friend static void cursorPositionCallback(GLFWwindow *sender, double xpos, double ypos);
		friend static void mouseButtonCallback(GLFWwindow *sender, int button, int action, int mods);
		friend static void mouseScrollCallback(GLFWwindow *sender, double xoffs, double yoffs);
		friend static void keyboardCallback(GLFWwindow *sender, int key, int scancode, int action, int mods);

		static void fh_keyCB(int key, bool action);
		static void fh_mouseBtnCB(int button, bool action);
		static void fh_mouseCrsCB(float x, float y);
		static void fh_mouseScrCB(float xoffs, float yoffs);
	};
}