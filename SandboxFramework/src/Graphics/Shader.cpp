#include "Shader.h"

namespace SandboxFramework
{
	namespace Graphics {
		Shader::Shader(std::string vertexPath, std::string fragmentPath)
		{
			locationCache = new Collections::Dictionary<std::string, GLint>();
			compile(Content::FileReader(vertexPath, "rt").ReadToEnd(), Content::FileReader(vertexPath, "rt").ReadToEnd());
		}

		Shader::~Shader()
		{
			glDeleteProgram(m_Program);
			delete locationCache;
		}

		bool Shader::compile(std::string vertexSrc, std::string fragmentSrc)
		{
			const char* cstrVert = vertexSrc.c_str();
			const char* cstrFrag = fragmentSrc.c_str();

			m_Program = glCreateProgram();

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
				return false;
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
				return false;
			}

			glAttachShader(m_Program, vs);
			glAttachShader(m_Program, fs);
			glLinkProgram(m_Program);
			glValidateProgram(m_Program);

			glDeleteShader(vs);
			glDeleteShader(fs);

			return true;
		}

		void Shader::Use()
		{
			glUseProgram(m_Program);
		}

		GLint Shader::getLocation(std::string uniformName)
		{
			if (locationCache->ContainsKey(uniformName))
			{
				return (*locationCache)[uniformName];
			}

			locationCache->Add(uniformName, glGetUniformLocation(m_Program, uniformName.c_str()));

			return (*locationCache)[uniformName];
		}

		void Shader::setUniformInt(std::string name, int value)
		{
			glUniform1i(getLocation(name), value);
		}

		void Shader::setUniformFloat(std::string name, float value)
		{
			glUniform1f(getLocation(name), value);
		}

		void Shader::setUniformVector2(std::string name, Math::Vector2 vector)
		{
			glUniform2f(getLocation(name), vector.X, vector.Y);
		}

		void Shader::setUniformVector3(std::string name, Math::Vector3 vector)
		{
			glUniform3f(getLocation(name), vector.X, vector.Y, vector.Z);
		}

		void Shader::setUniformVector4(std::string name, Math::Vector4 vector)
		{
			glUniform4f(getLocation(name), vector.X, vector.Y, vector.Z, vector.W);
		}

		void Shader::setUniforMatrix(std::string name, Math::Matrix matrix)
		{
			glUniformMatrix4fv(getLocation(name), 1, GL_FALSE, matrix.Elements);
		}
	}
}
