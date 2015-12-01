#include "GraphicsDevice.h"

namespace SandboxFramework
{
	namespace Graphics
	{
		GraphicsDevice::GraphicsDevice(Game* game)
		{
			m_Game = game;
		}

		GraphicsDevice::~GraphicsDevice()
		{ }

		void GraphicsDevice::Clear(Color color)
		{
			if (gl_ClearColor != color)
			{
				glClearColor(color.R, color.G, color.B, color.A);
				gl_ClearColor = color;
			}
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		Shader* GraphicsDevice::CreateShader(std::string vertexPath, std::string fragmentPath)
		{
			return new Shader(vertexPath, fragmentPath);
		}

		void GraphicsDevice::DestroyShader(Shader* shader)
		{
			delete shader;
			shader = NULL;
		}

		void GraphicsDevice::UseShader(Shader* shader)
		{
			if (shader == NULL) glUseProgram(0);
			else shader->Use();
		}
	}
}
