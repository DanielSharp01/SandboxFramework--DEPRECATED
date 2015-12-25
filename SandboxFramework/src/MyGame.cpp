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
#include "Graphics/SpriteFont.h"

using namespace Sand;

MyGame::MyGame(std::string title)
	: Game(title), initialTitle(title)
{ }

void MyGame::Initialize() { }

Graphics::Shader *shader, *renderShader;
Graphics::SpriteBatch* spriteBatch;
Graphics::Color* colArray;
Graphics::SpriteFont *spriteFont, *spriteFont2;
Graphics::Texture2D** texArray;
Graphics::Texture2D *texture, *texture2, *renderTarget, *renderTarget2;
Chrono::TimerCounter* fpsTimer;

void MyGame::LoadContent()
{
	fpsTimer = new Chrono::TimerCounter();
	shader = Graphics::Shader::Load(this, "Resources/Shaders/simple.vert", "Resources/Shaders/simple.frag");
	renderShader = Graphics::Shader::Load(this, "Resources/Shaders/simple.vert", "Resources/Shaders/simpleLightless.frag");

	texture = Graphics::Texture2D::Load(this, "Resources/Textures/BoxTexture.jpg");
	texture2 = Graphics::Texture2D::Load(this, "Resources/Textures/add.png");
	spriteFont = Graphics::SpriteFont::CreateFromFont(this, "Resources/Fonts/arial.ttf", 28, 32, 128);
	spriteFont->Save("Resources/Fonts/test.xml");
	spriteFont2 = Graphics::SpriteFont::Load(this, "Resources/Fonts/test.xml");

	//texture2->SaveAsPNG("C:/Users/Danie/Desktop/random.jpg");
	
	renderTarget = new Graphics::Texture2D(m_Graphics, 800, 480);
	renderTarget2 = new Graphics::Texture2D(m_Graphics, 800, 480);
	spriteBatch = new Graphics::SpriteBatch(m_Graphics);

	colArray = new Graphics::Color[80 * 48];
	texArray = new Graphics::Texture2D*[80 * 48];
	for (int i = 0; i < 80 * 48; i++)
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

	shader->SetUniformVector2("light_pos", lastMState.GetPosition());
	shader->SetUniformFloat("light_rad", 100.0f);

	float size = 10.0f;
	
	Graphics::Texture2D** arr = new Graphics::Texture2D*[2]{ renderTarget, renderTarget2 };
	m_Graphics->SetRenderTargets(arr, 2);
	spriteBatch->Begin(renderShader);

	for (float x = 0; x < m_Graphics->GetViewport().GetWidth(); x += size)
		for (float y = 0; y < m_Graphics->GetViewport().GetHeight(); y += size)
		{
			int index = (int)((y / size * 80) + x / size);
			spriteBatch->Draw(texArray[index], Math::Rectangle(0, 0, 0, 0), Math::Rectangle(x, y, size, size),
				colArray[index],
				Math::Vector2(size / 2, size / 2), 0.0f, 1.0f);
		}

	spriteBatch->Draw(texture, Math::Rectangle(), Math::Vector2(400, 240), Graphics::Color(1, 1, 1, 1), Math::Vector2(256, 256), 0, 0.25f);
	spriteBatch->End();
	
	m_Graphics->SetRenderTarget(NULL);
	
	BYTE* white = new BYTE[50 * 50 * 4];
	for (int i = 0; i < 50 * 50; i++)
	{
		white[i * 4 + 0] = 255;
		white[i * 4 + 1] = 129;
		white[i * 4 + 2] = 41;
		white[i * 4 + 3] = 255;
	}
	renderTarget2->SetData(white, 750, 430, 50, 50);
	delete white;
	
	spriteBatch->Begin(shader);
	spriteBatch->Draw(renderTarget2, Math::Rectangle(), Math::Rectangle(0, 0, 800, 480), Graphics::Color(1, 1, 1, 1));
	spriteBatch->End();
	
	fpsTimer->AdvanceCounter();
	int fps = (int)fpsTimer->GetCountOver(1);
	spriteBatch->Begin(renderShader);
	//spriteBatch->Draw(spriteFont->GetTexture(), Math::Rectangle(), Math::Vector2(0, 0), Graphics::Color(1, 1, 1, 1));
	spriteBatch->Draw(spriteFont, "This is a text:\nIn a new line!", Math::Vector2(50, 50), Graphics::Color(1, 0, 0, 1));
	spriteBatch->Draw(spriteFont2, "This is a text:\nIn a new line!", Math::Vector2(50, 150), Graphics::Color(0, 1, 0, 1));
	spriteBatch->End();
	delete arr;
}

void MyGame::UnloadContent()
{
	delete shader;
	delete renderShader;
	delete[] colArray;
	delete[] texArray;
	delete texture;
	delete texture2;
	delete spriteFont;
	delete renderTarget;
	delete renderTarget2;
	delete fpsTimer;
}