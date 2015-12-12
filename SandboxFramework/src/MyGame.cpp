#include "MyGame.h"
#include "Graphics/GraphicsDevice.h"
#include "Graphics/Shader.h"
#include "Graphics/VAO.h"
#include "Graphics/VBO.h"
#include "Graphics/IBO.h"
#include "Input/Keyboard.h"
#include "Input/Mouse.h"

using namespace SandboxFramework;

MyGame::MyGame(std::string title)
	: Game(title)
{ }

void MyGame::Initialize() { }

Graphics::Shader* shader;
Graphics::VAO* vao;
Graphics::VBO* vbo;
Graphics::IBO* ibo;

void MyGame::LoadContent()
{
	GLfloat* vertices = new GLfloat[9]
	{
		0, 0, 0,
		0, 1, 0,
		1, 1, 0
	};

	GLushort* indices = new GLushort[3]
	{
		0, 1, 2
	};

	//In case anyone else is looking at GitHub
	//Change this to your own filesystem
	shader = new Graphics::Shader(m_Graphics, "C:/Users/Danie/Documents/Visual Studio 2015/Projects/SandboxFramework/SandboxFramework/src/simple.vt", "C:/Users/Danie/Documents/Visual Studio 2015/Projects/SandboxFramework/SandboxFramework/src/simple.fg");
	shader->Bind();
	shader->setUniformVector4("color", Math::Vector4(0, 1, 0, 1));
	vao = new Graphics::VAO(m_Graphics);
	vbo = new Graphics::VBO(m_Graphics, vertices, 3, 3);
	ibo = new Graphics::IBO(m_Graphics, indices, 3);

	vao->BindVBOToLocation(vbo, 0, 0, 0);


	//TODO: might move them inside VBO and IBO
	delete vertices;
	delete indices;
}

Input::KeyboardState lastState;
Input::MouseState lastMState;

void MyGame::Update()
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
void MyGame::Draw()
{
	m_Graphics->Clear(Graphics::Color(0.392f, 0.584f, 0.929f, 1));
	m_Graphics->Draw(vao, ibo);

	std::cout << glGetError() << std::endl;
}
void MyGame::UnloadContent()
{
	delete vao;
	delete vbo;
	delete ibo;
}