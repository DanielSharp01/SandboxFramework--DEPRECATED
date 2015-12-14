#include "MyGame.h"
#include "Graphics/GraphicsDevice.h"
#include "Graphics/SpriteBatch.h"
#include "Graphics/Shader.h"
#include "Graphics/VAO.h"
#include "Graphics/VBO.h"
#include "Graphics/IBO.h"
#include "Input/Keyboard.h"
#include "Input/Mouse.h"
#include "Math/Functions.h"

using namespace SandboxFramework;

MyGame::MyGame(std::string title)
	: Game(title)
{ }

void MyGame::Initialize() { }

Graphics::Shader* shader;
Graphics::SpriteBatch* spriteBatch;

void MyGame::LoadContent()
{
	shader = new Graphics::Shader(m_Graphics, "C:/Users/Danie/Documents/Visual Studio 2015/Projects/SandboxFramework/SandboxFramework/src/simple.vt", "C:/Users/Danie/Documents/Visual Studio 2015/Projects/SandboxFramework/SandboxFramework/src/simple.fg");
	shader->Bind();
	shader->setUniformVector4("color", Graphics::Color(1, 1, 1, 1).ToVector4());
	shader->setUniformMatrix("proj", Math::Matrix::Orthographic(0.0f, 16.0f, 9.0f, 0.0f, -1.0f, 1.0f));
	spriteBatch = new Graphics::SpriteBatch(m_Graphics);
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
	float x = lastMState.GetPosition().X;
	float y = lastMState.GetPosition().Y;
	x = x * 16.0f / m_Width;
	y = y * 9.0f / m_Height;
	
	Math::Vector2 lightVector = Math::Vector2(x, y);
	shader->setUniformVector2("light_pos", lightVector);

	float size = 0.1f;

	spriteBatch->Begin();
	
	for (float x = 0; x < 16.0f; x += 0.1f)
		for (float y = 0; y < 9.0f; y += 0.1f)
		spriteBatch->Draw(Math::Vector2(x + size / 2, y + size / 2), Math::Vector2(size, size),
			Graphics::Color(Math::RandomLinearInterpolation(0.0f, 1.0f), Math::RandomLinearInterpolation(0.0f, 1.0f), Math::RandomLinearInterpolation(0.0f, 1.0f), 1.0f),
			Math::Vector2(size / 2, size / 2), 0.0f, 1.0f);

	spriteBatch->End();
}

void MyGame::UnloadContent()
{

}