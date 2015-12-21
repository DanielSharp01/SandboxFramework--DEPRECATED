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

Graphics::Shader *shader, *renderShader;
Graphics::SpriteBatch* spriteBatch;
Graphics::Color* colArray;
Graphics::Texture2D** texArray;
Graphics::Texture2D *texture, *texture2, *renderTarget, *renderTarget2;
Chrono::TimerCounter* fpsTimer;

void MyGame::LoadContent()
{
	m_Graphics->GetViewport().SetProjected(0, 16, 0, 9);
	fpsTimer = new Chrono::TimerCounter();
	shader = new Graphics::Shader(m_Graphics, IO::TextReader("Resources/Shaders/simple.vert").ReadToEnd(), IO::TextReader("Resources/Shaders/simple.frag").ReadToEnd());
	renderShader = new Graphics::Shader(m_Graphics, IO::TextReader("Resources/Shaders/simple.vert").ReadToEnd(), IO::TextReader("Resources/Shaders/simpleLightless.frag").ReadToEnd());

	IO::ImageReader* reader = new IO::ImageReader("Resources/Textures/BoxTexture.jpg");
	texture = new Graphics::Texture2D(m_Graphics, reader->GetPixelData(true), reader->GetWidth(), reader->GetHeight(), Graphics::ImageFormat::BGR);
	delete reader;
	reader = new IO::ImageReader("Resources/Textures/add.png");
	texture2 = new Graphics::Texture2D(m_Graphics, reader->GetPixelData(true), reader->GetWidth(), reader->GetHeight(), Graphics::ImageFormat::BGR);
	delete reader;
	
	renderTarget = new Graphics::Texture2D(m_Graphics, 800, 480);
	renderTarget2 = new Graphics::Texture2D(m_Graphics, 800, 480);
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

void MyGame::Update()
{
	using namespace Input;
	KeyboardState currentState = Keyboard::GetState();
	Input::MouseState currentMState = Mouse::GetState();

	lastState = currentState;
	lastMState = currentMState;
}

void MyGame::Draw()
{
	m_Graphics->SetBlendState(Graphics::BlendState::Alpha);
	m_Graphics->Clear(Graphics::Color(0.0f, 0.0f, 0.0f, 1));
	Math::Vector2 mouse = lastMState.GetPosition() / Math::Vector2(m_Graphics->GetViewport().GetWidth(), m_Graphics->GetViewport().GetHeight());
	mouse *= Math::Vector2(m_Graphics->GetViewport().GetProjectedWidth(), m_Graphics->GetViewport().GetProjectedHeight());
	
	Math::Vector2 lightVector = mouse;
	shader->SetUniformVector2("light_pos", lightVector);

	float size = 0.125f;
	
	Graphics::Texture2D** arr = new Graphics::Texture2D*[2]{ renderTarget, renderTarget2 };
	m_Graphics->SetRenderTargets(arr, 2);
	m_Graphics->GetViewport().SetProjected(0, 16, 0, 9);
	spriteBatch->Begin(shader);

	for (float x = 0; x < m_Graphics->GetViewport().GetProjectedWidth(); x += size)
		for (float y = 0; y < m_Graphics->GetViewport().GetProjectedHeight(); y += size)
		{
			Math::Rectangle rect = Math::Rectangle(x - size / 2, y - size / 2, size, size);
			spriteBatch->Draw(texArray[(int)(y * 8) + (int)(x * 8) * 9], Math::Rectangle(0, 0, 0, 0), Math::Rectangle(x, y, size, size),
				colArray[(int)(y * 8) + (int)(x * 8) * 9],
				Math::Vector2(size / 2, size / 2), 0.0f, 1.0f);

		}

	spriteBatch->End();
	
	m_Graphics->SetRenderTarget(NULL);

	spriteBatch->Begin(shader);

	spriteBatch->Draw(renderTarget2, Math::Rectangle(), Math::Vector2(0, 0), Graphics::Color(1, 1, 1, 1));

	spriteBatch->End();

	delete arr;

	fpsTimer->AdvanceCounter();
	SetTitle(initialTitle + " @ FPS " + std::to_string((int)fpsTimer->GetCountOver(1)));
}

void MyGame::UnloadContent()
{
	delete shader;
	delete renderShader;
	delete[] colArray;
	delete[] texArray;
	delete texture;
	delete texture2;
	delete renderTarget;
	delete renderTarget2;
	delete fpsTimer;
}