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

struct VertexData
{
	Math::Vector3 Position;
	Math::Vector4 Color;

	VertexData(Math::Vector3 position, Math::Vector4 color)
	{
		Position = position;
		Color = color;
	}
};

float sx = 3.0f;
float sy = 3.0f;
float vx = 0;
float vy = 4.5f - sy / 2;
void MyGame::LoadContent()
{
	VertexData* vertices = new VertexData[4]
	{
		VertexData(Math::Vector3(vx, vy, 0), Graphics::Color(1, 1, 1, 1).ToVector4()),
		VertexData(Math::Vector3(vx + sx, vy, 0), Graphics::Color(1, 1, 1, 1).ToVector4()),
		VertexData(Math::Vector3(vx + sx, vy + sy, 0), Graphics::Color(1, 1, 0, 1).ToVector4()),
		VertexData(Math::Vector3(vx, vy + sy, 0), Graphics::Color(1, 1, 0, 1).ToVector4())
	};

	GLushort* indices = new GLushort[6]
	{
		0, 1, 2, 2, 3, 0
	};

	//In case anyone else is looking at GitHub
	//Change this to your own filesystem
	shader = new Graphics::Shader(m_Graphics, "C:/Users/Danie/Documents/Visual Studio 2015/Projects/SandboxFramework/SandboxFramework/src/simple.vt", "C:/Users/Danie/Documents/Visual Studio 2015/Projects/SandboxFramework/SandboxFramework/src/simple.fg");
	shader->Bind();
	shader->setUniformVector4("color", Graphics::Color(1, 1, 1, 1).ToVector4());
	shader->setUniformMatrix("proj", Math::Matrix::Orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f));
	vao = new Graphics::VAO(m_Graphics);
	vbo = new Graphics::VBO(m_Graphics, 4, sizeof(VertexData));
	ibo = new Graphics::IBO(m_Graphics, indices, 6);

	vao->BindVBOToLocation(vbo, 1, 3, GL_FLOAT, sizeof(VertexData), (const GLvoid*)offsetof(VertexData, Position));
	vao->BindVBOToLocation(vbo, 0, 4, GL_FLOAT, sizeof(VertexData), (const GLvoid*)offsetof(VertexData, Color));


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
	m_Graphics->Clear(Graphics::Color(0.0f, 0.0f, 0.0f, 1));
	//m_Graphics->Clear(Graphics::Color(0.392f, 0.584f, 0.929f, 1));
	float x = lastMState.GetPosition().X;
	float y = lastMState.GetPosition().Y;
	x = x * 16.0f / m_Width;
	y = 9.0f * (1 - y / m_Height);
	vx = x - sx / 2;
	vy = y - sy / 2;
	Math::Vector2 lightVector = Math::Vector2(x, y);
	shader->setUniformVector2("light_pos", lightVector);

	VertexData* data = (VertexData*)vbo->Map();
	data->Position = Math::Vector3(vx, vy, 0);
	data->Color = Graphics::Color(x / 16.0f, 1, 1, 1).ToVector4();
	data++;

	data->Position = Math::Vector3(vx + sx, vy, 0);
	data->Color = Graphics::Color(x / 16.0f, 1, 1, 1).ToVector4();
	data++;

	data->Position = Math::Vector3(vx + sx, vy + sy, 0);
	data->Color = Graphics::Color(1, 1, 0, 1).ToVector4();
	data++;

	data->Position = Math::Vector3(vx, vy + sy, 0);
	data->Color = Graphics::Color(1, 1, 0, 1).ToVector4();
	data++;

	vbo->Unmap();

	m_Graphics->Draw(vao, ibo);

	//std::cout << glGetError() << std::endl;
}
void MyGame::UnloadContent()
{
	delete vao;
	delete vbo;
	delete ibo;
}