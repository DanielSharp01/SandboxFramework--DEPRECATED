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
#include "Chrono/TimerCounter.h"
#include "IO/TextReader.h"

using namespace Sand;

MyGame::MyGame(std::string title)
	: Game(title), initialTitle(title)
{ }

void MyGame::Initialize() { }

Graphics::Shader* shader;
Graphics::SpriteBatch* spriteBatch;
Graphics::Color* colArray;
Graphics::Texture2D** texArray;
Graphics::Texture2D *texture, *texture2;
Chrono::TimerCounter* fpsTimer;

void MyGame::LoadContent()
{
	m_Graphics->GetViewport().SetProjected(0, 16, 0, 9);
	fpsTimer = new Chrono::TimerCounter();
	shader = new Graphics::Shader(m_Graphics, IO::TextReader("Resources/Shaders/simple.vert").ReadToEnd(), IO::TextReader("Resources/Shaders/simple.frag").ReadToEnd());

	IO::ImageReader* reader = new IO::ImageReader("Resources/Textures/BoxTexture.jpg");
	texture = new Graphics::Texture2D(m_Graphics, reader->GetPixelData(), reader->GetWidth(), reader->GetHeight(), GL_BGR);
	delete reader;
	reader = new IO::ImageReader("Resources/Textures/outline.png");
	texture2 = new Graphics::Texture2D(m_Graphics, reader->GetPixelData(), reader->GetWidth(), reader->GetHeight(), GL_BGRA);
	delete reader;
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
	fpsTimer->Start();
}

Input::KeyboardState lastState;
Input::MouseState lastMState;

Math::Vector2 posA(2, 2);
Math::Vector2 posB(5, 5);
Math::Vector2 sizeA(1, 1);
Math::Vector2 sizeB(1, 1);
float rotA = 0;
float rotB = 0;
char rect = 'A';
char value = '\0';
bool zb = false;

void MyGame::Update()
{
	using namespace Input;
	KeyboardState currentState = Keyboard::GetState();
	Input::MouseState currentMState = Mouse::GetState();
	
	
	if (currentState.IsKeyDown(GLFW_KEY_A) && lastState.IsKeyUp(GLFW_KEY_A))
	{
		rect = 'A';
	}
	else if (currentState.IsKeyDown(GLFW_KEY_B) && lastState.IsKeyUp(GLFW_KEY_B))
	{
		rect = 'B';
	}
	
	if (currentState.IsKeyDown(GLFW_KEY_P) && lastState.IsKeyUp(GLFW_KEY_P))
	{
		value = (value == 'P') ? '\0' : 'P';
	}
	else if (currentState.IsKeyDown(GLFW_KEY_S) && lastState.IsKeyUp(GLFW_KEY_S))
	{
		value = (value == 'S') ? '\0' : 'S';
	}
	else if (currentState.IsKeyDown(GLFW_KEY_R) && lastState.IsKeyUp(GLFW_KEY_R))
	{
		value = (value == 'R') ? '\0' : 'R';
	}

	if (currentMState.IsButtonDown(GLFW_MOUSE_BUTTON_1) && lastMState.IsButtonUp(GLFW_MOUSE_BUTTON_1)) value = '\0';

	float mx = currentMState.GetPosition().X;
	float my = currentMState.GetPosition().Y;
	mx = mx * 16.0f / m_Graphics->GetViewport().GetWidth();
	my = my * 9.0f / m_Graphics->GetViewport().GetHeight();
	Math::Vector2 mouseVector = Math::Vector2(mx, my);

	if (rect == 'A')
	{
		zb = false;
		if (value == 'P')
		{
			posA = mouseVector;
		}
		else if (value == 'S')
		{
			sizeA = (mouseVector - posA) * 2;
		}
		else if (value == 'R')
		{
			rotA = Math::Radian2Degree(posA.Angle(mouseVector)) + 90;
		}
	}
	else if (rect == 'B')
	{
		zb = true;
		if (value == 'P')
		{
			posB = mouseVector;
		}
		else if (value == 'S')
		{
			sizeB = (mouseVector - posB) * 2;
		}
		else if (value == 'R')
		{
			rotB = Math::Radian2Degree(posB.Angle(mouseVector)) + 90;
		}
	}

	lastState = currentState;
	lastMState = currentMState;
}

void MyGame::Draw()
{
	m_Graphics->Clear(Graphics::Color(0.0f, 0.0f, 0.0f, 1));
	Math::Vector2 mouse = lastMState.GetPosition() / Math::Vector2(m_Graphics->GetViewport().GetWidth(), m_Graphics->GetViewport().GetHeight());
	mouse *= Math::Vector2(m_Graphics->GetViewport().GetProjectedWidth(), m_Graphics->GetViewport().GetProjectedHeight());
	
	Math::Vector2 lightVector = mouse;
	shader->SetUniformVector2("light_pos", lightVector);

	float size = 0.125f;

	Math::Rectangle rectA(posA.X - sizeA.X / 2, posA.Y - sizeA.Y / 2, sizeA.X, sizeA.Y);
	rectA.Rotate(rotA);

	Math::Rectangle rectB(posB.X - sizeB.X / 2, posB.Y - sizeB.Y / 2, sizeB.X, sizeB.Y);
	rectB.Rotate(rotB);

	/*bool containedA = rectB.Contains(rectA);
	bool containedB = rectA.Contains(rectB);
	//bool intersects = containedA || containedB || rectA.Intersects(rectB);
	bool intersects = rectA.Intersects(rectB);
	//Graphics::Color colA = containedA ? Graphics::Color(0.0f, 1.0f, 0.0f, 1) : (intersects ? Graphics::Color(1.0f, 0.0f, 0.0f, 1) : (rect == 'A' ? Graphics::Color(0.5f, 0.5f, 1.0f, 1) : Graphics::Color(1.0f, 1.0f, 1.0f, 1)));
	//Graphics::Color colB = containedB ? Graphics::Color(0.0f, 1.0f, 0.0f, 1) : (intersects ? Graphics::Color(1.0f, 0.0f, 0.0f, 1) : (rect == 'B' ? Graphics::Color(0.5f, 0.5f, 1.0f, 1) : Graphics::Color(1.0f, 1.0f, 1.0f, 1)));
	Graphics::Color colA = intersects ? Graphics::Color(1.0f, 0.0f, 0.0f, 1) : (rect == 'A' ? Graphics::Color(0.5f, 0.5f, 1.0f, 1) : Graphics::Color(1, 1, 1, 1));
	Graphics::Color colB = intersects ? Graphics::Color(1.0f, 0.0f, 0.0f, 1) : (rect == 'B' ? Graphics::Color(0.5f, 0.5f, 1.0f, 1) : Graphics::Color(1, 1, 1, 1));*/

	spriteBatch->Begin(shader);
	
	
	spriteBatch->Draw(texture2, Math::Vector2(2, 2), Graphics::Color(0, 0, 1, 1), 0.1f);
	for (float x = 0; x < m_Graphics->GetViewport().GetProjectedWidth(); x += size)
		for (float y = 0; y < m_Graphics->GetViewport().GetProjectedHeight(); y += size)
		{
			Math::Rectangle rect = Math::Rectangle(x - size / 2, y - size / 2, size, size);
			spriteBatch->Draw(texArray[(int)(y * 8) + (int)(x * 8) * 9], Math::Rectangle(0, 0, 0, 0), Math::Rectangle(x, y, size, size),
				colArray[(int)(y * 8) + (int)(x * 8) * 9],
				Math::Vector2(size / 2, size / 2), 0.0f, 1.0f);
		}
	
	/*if (zb)
	{
		spriteBatch->Draw(texture2, rectA, colA);
		spriteBatch->Draw(texture2, rectB, colB);
	}
	else
	{
		spriteBatch->Draw(texture2, rectB, colB);
		spriteBatch->Draw(texture2, rectA, colA);
	}*/

	spriteBatch->End();
	fpsTimer->AdvanceCounter();
	SetTitle(initialTitle + " @ FPS " + std::to_string((int)fpsTimer->GetCountOver(1)));
}

void MyGame::UnloadContent()
{
	delete[] colArray;
	delete[] texArray;
	delete texture;
	delete texture2;
	delete fpsTimer;
}