#include "Game.h"
#include "Graphics/GraphicsDevice.h"

namespace SandboxFramework {

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
		Game::LoadContent();

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
		glfwSetCursorPosCallback(m_Window, cursorPositionCallback);
		glfwSetMouseButtonCallback(m_Window, mouseButtonCallback);
		glfwSetScrollCallback(m_Window, mouseScrollCallback);
		glfwSetKeyCallback(m_Window, keyboardCallback);

		if (glewInit() != GLEW_OK)
		{
			std::cout << "Failed to initialize GLEW!" << std::endl;
			return false;
		}

		return true;
	}

	void Game::update()
	{
		glfwPollEvents();
		Game::Update();

		fh_mouseScrCB(0, 0); //Hotfix for no infinite scroll
	}

	void Game::draw()
	{
		Game::Draw();
		glfwSwapBuffers(m_Window);
	}

	void Game::Exit()
	{
		Game::UnloadContent();
		glfwSetWindowShouldClose(m_Window, GL_TRUE);
	}

	bool Game::isClosing() const
	{
		return glfwWindowShouldClose(m_Window) == 1;
	}

	void resizeCallback(GLFWwindow *sender, int width, int height)
	{
		Game* win = (Game*)glfwGetWindowUserPointer(sender);
		win->m_Width = width;
		win->m_Height = height;
	}

	void frameResizeCallback(GLFWwindow *sender, int width, int height)
	{
		glViewport(0, 0, width, height);
	}

	void keyboardCallback(GLFWwindow* sender, int key, int scancode, int action, int mods)
	{
		Game::fh_keyCB(key, action == GLFW_PRESS);
	}

	void cursorPositionCallback(GLFWwindow* sender, double xpos, double ypos)
	{
		Game::fh_mouseCrsCB((float)xpos, (float)ypos);
	}

	void mouseButtonCallback(GLFWwindow* sender, int button, int action, int mods)
	{
		Game::fh_mouseBtnCB(button, action == GLFW_PRESS);
	}

	void mouseScrollCallback(GLFWwindow *sender, double xoffs, double yoffs)
	{
		Game::fh_mouseScrCB((float)xoffs, (float)yoffs);
	}

	void Game::fh_keyCB(int key, bool state)
	{
		Input::Keyboard::setState(key, state);
	}

	void Game::fh_mouseBtnCB(int button, bool state)
	{
		Input::Mouse::setButtonState(button, state);
	}

	void Game::fh_mouseCrsCB(float x, float y)
	{
		Input::Mouse::setCursorState(x, y);
	}

	void Game::fh_mouseScrCB(float xoffs, float yoffs)
	{
		Input::Mouse::setScrollState(xoffs, yoffs);
	}

	//TODO: Get Rid of this
	void Game::Initialize() { m_Graphics = new Graphics::GraphicsDevice(this); }
	void Game::LoadContent() {}

	Input::KeyboardState lastState;
	Input::MouseState lastMState;
	void Game::Update()
	{
		using namespace Input;
		KeyboardState currentState = Keyboard::GetState();
		Input::MouseState currentMState = Mouse::GetState();
		if (currentState.IsKeyDown(GLFW_KEY_A) && lastState.IsKeyUp(GLFW_KEY_A)) std::cout << "Key \"A\" down!" << std::endl;
		if (currentMState.IsButtonDown(GLFW_MOUSE_BUTTON_MIDDLE) && lastMState.IsButtonUp(GLFW_MOUSE_BUTTON_MIDDLE)) std::cout << "Middle MButton down!" << std::endl;
		float scroll = currentMState.GetScroll().Y;
		if (scroll != 0) std::cout << "Delta scroll " << scroll << std::endl;
		lastState = currentState;
		lastMState = currentMState;
	}
	void Game::Draw() { m_Graphics->Clear(Graphics::Color(0.392f, 0.584f, 0.929f, 1)); }
	void Game::UnloadContent() {}
}
