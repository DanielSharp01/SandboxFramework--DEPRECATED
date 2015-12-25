#include "Game.h"
#include "Graphics/GraphicsDevice.h"
#include "Input/Keyboard.h"
#include "Input/Mouse.h"

namespace Sand {

	Game::Game(std::string title)
	{
		m_Width = 800;
		m_Height = 480;
		m_Title = title;
	}

	Game::~Game()
	{
		if (m_Window) glfwDestroyWindow(m_Window);
		glfwTerminate();
	}

	void Game::Run()
	{
		if (!init()) {
			glfwTerminate();
			std::cout << "Failed to run game (see errors above)!" << std::endl;
			system("pause");
			return;
		}
		Initialize();
		FT_Init_FreeType(&m_FreeType);
		LoadContent();
		FT_Done_FreeType(m_FreeType);

		while (!isClosing())
		{
			update();
			draw();
		}
	}

	void Game::SetSize(int width, int height)
	{
		glfwSetWindowSize(m_Window, width, height);
	}

	void Game::SetTitle(std::string title)
	{
		m_Title = title;
		glfwSetWindowTitle(m_Window, title.c_str());
	}

	bool Game::init()
	{
		srand(time(NULL));

		if (!glfwInit())
		{
			std::cout << "Failed to initialize GLFW!" << std::endl;
			return false;
		}
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
		m_Window = glfwCreateWindow(m_Width, m_Height, m_Title.c_str(), NULL, NULL);
		if (!m_Window)
		{
			std::cout << "Failed to create GLFW Window!" << std::endl;
			return false;
		}

		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, this);
		glfwSetWindowSizeCallback(m_Window, frameResizeCallback);
		glfwSetFramebufferSizeCallback(m_Window, frameResizeCallback);
		glfwSetCursorPosCallback(m_Window, Input::cursorPositionCallback);
		glfwSetMouseButtonCallback(m_Window, Input::mouseButtonCallback);
		glfwSetScrollCallback(m_Window, Input::mouseScrollCallback);
		glfwSetKeyCallback(m_Window, Input::keyboardCallback);

		if (glewInit() != GLEW_OK)
		{
			std::cout << "Failed to initialize GLEW!" << std::endl;
			return false;
		}

		m_Graphics = new Graphics::GraphicsDevice(this);

		return true;
	}

	void Game::update()
	{
		glfwPollEvents();
		Update();
		Input::mouseScrollCallback(m_Window, 0, 0);
	}

	void Game::draw()
	{
		Draw();
		glfwSwapBuffers(m_Window);
	}

	void Game::Exit()
	{
		UnloadContent();
		glfwSetWindowShouldClose(m_Window, GL_TRUE);
	}

	bool Game::isClosing() const
	{
		return glfwWindowShouldClose(m_Window) == 1;
	}

	void Game::setGraphicsDeviceViewport(int width, int height)
	{
		m_Graphics->setViewportSize(width, height);
	}

	void resizeCallback(GLFWwindow *sender, int width, int height)
	{
		Game* win = (Game*)glfwGetWindowUserPointer(sender);
		win->m_Width = width;
		win->m_Height = height;
	}

	void frameResizeCallback(GLFWwindow *sender, int width, int height)
	{
		Game* win = (Game*)glfwGetWindowUserPointer(sender);
		win->setGraphicsDeviceViewport(width, height);
		glViewport(0, 0, width, height);
	}
}