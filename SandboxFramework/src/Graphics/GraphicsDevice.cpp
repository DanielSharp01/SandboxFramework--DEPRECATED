#include "GraphicsDevice.h"
#include "Shader.h"

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
			if (glstate_ClearColor != color)
			{
				glClearColor(color.R, color.G, color.B, color.A);
				glstate_ClearColor = color;
			}
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		GLuint GraphicsDevice::gl_createShaderProgram(std::string vertexSrc, std::string fragmentSrc)
		{
			const char* cstrVert = vertexSrc.c_str();
			const char* cstrFrag = fragmentSrc.c_str();

			GLuint program = glCreateProgram();

			GLuint vs = glCreateShader(GL_VERTEX_SHADER);
			glShaderSource(vs, 1, &cstrVert, NULL);
			glCompileShader(vs);

			GLint result;
			glGetShaderiv(vs, GL_COMPILE_STATUS, &result);
			if (result == GL_FALSE)
			{
				GLint length;
				glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &length);
				GLchar* error = new GLchar[length + 1];
				glGetShaderInfoLog(vs, length, &length, error);
				std::cout << "Failed to compile vertex shader! " << error << std::endl;
				delete error;
				glDeleteShader(vs);
				return 0;
			}

			GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
			glShaderSource(fs, 1, &cstrFrag, NULL);
			glCompileShader(fs);

			result;
			glGetShaderiv(fs, GL_COMPILE_STATUS, &result);
			if (result == GL_FALSE)
			{
				GLint length;
				glGetShaderiv(fs, GL_INFO_LOG_LENGTH, &length);
				GLchar* error = new GLchar[length + 1];
				glGetShaderInfoLog(fs, length, &length, error);
				std::cout << "Failed to compile fragment shader! " << error << std::endl;
				delete error;
				glDeleteShader(fs);
				return 0;
			}

			glAttachShader(program, vs);
			glAttachShader(program, fs);
			glLinkProgram(program);
			glValidateProgram(program);

			glDeleteShader(vs);
			glDeleteShader(fs);

			return program;
		}

		void GraphicsDevice::gl_bindShader(Shader* shader)
		{
			if (glstate_ActiveProgram != shader->m_Program)
			{
				glUseProgram(shader->m_Program);
				glstate_ActiveProgram = shader->m_Program;
			}
		}

		void GraphicsDevice::gl_destroyShader(Shader* shader)
		{
			if (glstate_ActiveProgram == shader->m_Program) glstate_ActiveProgram = 0;
			glDeleteProgram(shader->m_Program);
		}

		GLint GraphicsDevice::gl_getLocation(Shader* shader, std::string uniformName)
		{
			return glGetUniformLocation(shader->m_Program, uniformName.c_str());
		}

		void GraphicsDevice::gl_setUniformInt(GLint location, int value)
		{
			glUniform1i(location, value);
		}

		void GraphicsDevice::gl_setUniformFloat(GLint location, float value)
		{
			glUniform1f(location, value);
		}

		void GraphicsDevice::gl_setUniformVector2(GLint location, Math::Vector2 vector)
		{
			glUniform2f(location, vector.X, vector.Y);
		}

		void GraphicsDevice::gl_setUniformVector3(GLint location, Math::Vector3 vector)
		{
			glUniform3f(location, vector.X, vector.Y, vector.Z);
		}

		void GraphicsDevice::gl_setUniformVector4(GLint location, Math::Vector4 vector)
		{
			glUniform4f(location, vector.X, vector.Y, vector.Z, vector.W);
		}

		void GraphicsDevice::gl_setUniformMatrix(GLint location, Math::Matrix matrix)
		{
			glUniformMatrix4fv(location, 1, GL_FALSE, matrix.Elements);
		}
	}
}
