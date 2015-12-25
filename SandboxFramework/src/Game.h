#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#include <time.h>
#include <iostream>
#include <GLFW/glfw3.h>
#include "Graphics/Color.h"
#include <ft2build.h>
#include <freetype/freetype.h>

namespace Sand {
	
	namespace Graphics
	{
		class GraphicsDevice;
	}
	
	class Game
	{
	protected:
		int m_Width;
		int m_Height;
		std::string m_Title;

		GLFWwindow* m_Window;
		Graphics::GraphicsDevice* m_Graphics;
		FT_Library m_FreeType;
	public:
		Game(std::string title);
		~Game();

		void Run();

		inline Graphics::GraphicsDevice* GetGraphics() const { return m_Graphics; }
		inline FT_Library GetFreeType() const { return m_FreeType; }
		inline int GetWidth() const { return m_Width; }
		inline int GetHeight() const { return m_Height; }

		void SetSize(int width, int height);
		void SetTitle(std::string title);
	protected:
		virtual void Initialize() = 0;
		virtual void LoadContent() = 0;
		virtual void Update() = 0;
		virtual void Draw() = 0;
		virtual void UnloadContent() = 0;

		void Exit();
	private:
		bool init();
		void update();
		void draw();

		bool isClosing() const;

		void setGraphicsDeviceViewport(int width, int height);

		friend void resizeCallback(GLFWwindow* sender, int width, int height);
		friend void frameResizeCallback(GLFWwindow* sender, int width, int height);
	};
}