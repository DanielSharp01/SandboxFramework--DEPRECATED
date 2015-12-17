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
#include "Graphics/Texture2D.h"
#include "IO/ImageReader.h"

using namespace Sand;

MyGame::MyGame(std::string title)
	: Game(title)
{ }

void MyGame::Initialize() { }

Graphics::Shader* shader;
Graphics::SpriteBatch* spriteBatch;
Graphics::Color* colArray;
Graphics::Texture2D** texArray;
Graphics::Texture2D *texture, *texture2;

void MyGame::LoadContent()
{
	shader = new Graphics::Shader(m_Graphics, "Resources/Shaders/simple.vert", "Resources/Shaders/simple.frag");
	shader->Bind();

	IO::ImageReader* reader = new IO::ImageReader("Resources/Textures/white.png");
	texture = new Graphics::Texture2D(m_Graphics, reader->GetPixelData(), reader->GetWidth(), reader->GetHeight(), GL_BGRA);
	delete reader;
	reader = new IO::ImageReader("Resources/Textures/red.png");
	texture2 = new Graphics::Texture2D(m_Graphics, reader->GetPixelData(), reader->GetWidth(), reader->GetHeight(), GL_BGRA);
	delete reader;

	shader->SetUniformDefaultIntV("textures", 32);
	//shader->SetUniformColor("tint", Graphics::Color(1, 1, 1, 1));
	shader->SetUniformMatrix("proj", Math::Matrix::Orthographic(0.0f, 16.0f, 9.0f, 0.0f, -1.0f, 1.0f));
	spriteBatch = new Graphics::SpriteBatch(m_Graphics);

	colArray = new Graphics::Color[128 * 72];
	texArray = new Graphics::Texture2D*[128 * 72];
	for (int i = 0; i < 128 * 72; i++)
	{
		//colArray[i] = Graphics::Color(1.0f, 1.0f, 1.0f, 1.0f);
		colArray[i] = Graphics::Color(Math::RandomLinearInterpolation(0.0f, 1.0f), Math::RandomLinearInterpolation(0.0f, 1.0f), Math::RandomLinearInterpolation(0.0f, 1.0f), 1.0f);
		texArray[i] = texture;
		//texArray[i] = Math::Random(0, 1) ? texture : texture2;
	}
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
	shader->SetUniformVector2("light_pos", lightVector);

	float size = 0.125f;

	spriteBatch->Begin();
	for (float x = 0; x < 16.0f; x += 0.125f)
		for (float y = 0; y < 9.0f; y += 0.125f)
		spriteBatch->Draw(texArray[(int)(y * 8) + (int)(x * 8) * 9], Math::Vector2(x + size / 2, y + size / 2), Math::Vector2(size, size),
			colArray[(int)(y * 8) + (int)(x * 8) * 9],
			Math::Vector2(size / 2, size / 2), 0.0f, 1.0f);

	/*spriteBatch->Draw(texture, Math::Vector2(10, 2), Math::Vector2(2, 2), Graphics::Color(1, 1, 1, 1));
	spriteBatch->Draw(texture2, Math::Vector2(2, 2), Math::Vector2(2, 2), Graphics::Color(1, 1, 1, 1));*/

	spriteBatch->End();
}

void MyGame::UnloadContent()
{
	delete[] colArray;
	delete[] texArray;
	delete texture;
	delete texture2;
}