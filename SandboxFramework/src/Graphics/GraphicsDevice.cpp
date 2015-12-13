#include "GraphicsDevice.h"

#include "Shader.h"
#include "VAO.h"
#include "VBO.h"
#include "IBO.h"

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

		void GraphicsDevice::Draw(int indexCount)
		{
			glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_SHORT, NULL);
		}

		void GraphicsDevice::Draw(VAO* vao, IBO* ibo)
		{
			vao->Bind();
			ibo->Bind();
			glDrawElements(GL_TRIANGLES, ibo->m_Count, GL_UNSIGNED_SHORT, NULL);
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

		void GraphicsDevice::gl_bindShader(const Shader* shader)
		{
			if (shader == NULL)
			{
				if (glstate_ActiveShaderProgram == NULL) return;
				glUseProgram(NULL);
				glstate_ActiveShaderProgram = NULL;
			}
			if (glstate_ActiveShaderProgram != shader->m_Program)
			{
				glUseProgram(shader->m_Program);
				glstate_ActiveShaderProgram = shader->m_Program;
			}
		}

		void GraphicsDevice::gl_unbindShader(const Shader* shader)
		{
			if (glstate_ActiveShaderProgram == shader->m_Program)
			{
				glUseProgram(NULL);
				glstate_ActiveShaderProgram = NULL;
			}
		}

		void GraphicsDevice::gl_destroyShader(Shader* shader)
		{
			gl_unbindShader(shader);
			glDeleteProgram(shader->m_Program);
		}

		GLuint GraphicsDevice::gl_createVAO()
		{
			GLuint ret;
			glGenVertexArrays(1, &ret);
			return ret;
		}

		void GraphicsDevice::gl_bindVAO(const VAO* vao)
		{
			if (vao == NULL)
			{
				if (glstate_ActiveVAO == NULL) return;
				glBindVertexArray(NULL);
				glstate_ActiveVAO = NULL;
			}
			if (glstate_ActiveVAO != vao->m_ID)
			{
				glBindVertexArray(vao->m_ID);
				glstate_ActiveVAO = vao->m_ID;
			}
		}

		void GraphicsDevice::gl_unbindVAO(const VAO* vao)
		{
			if (glstate_ActiveVAO == vao->m_ID)
			{
				glBindVertexArray(NULL);
				glstate_ActiveVAO = NULL;
			}
		}

		void GraphicsDevice::gl_destroyVAO(VAO* vao)
		{
			gl_unbindVAO(vao);
			glDeleteVertexArrays(1, &vao->m_ID);
		}

		void GraphicsDevice::gl_bindVBOToLocation(const VBO* vbo, GLint location, GLenum componentType, GLsizei componentCount, GLsizei stride, const GLvoid* offset)
		{
			vbo->Bind();
			glEnableVertexAttribArray(location);
			glVertexAttribPointer(location, componentCount, componentType, GL_FALSE, stride, offset);
		}

		

		GLuint GraphicsDevice::gl_createVBO(GLsizei maxSize)
		{
			GLuint ret;
			glGenBuffers(1, &ret);
			glBindBuffer(GL_ARRAY_BUFFER, ret);
			glBufferData(GL_ARRAY_BUFFER, maxSize, NULL, GL_DYNAMIC_DRAW);
			return ret;
		}

		GLuint GraphicsDevice::gl_createVBO(GLvoid* data, GLsizei size)
		{
			GLuint ret;
			glGenBuffers(1, &ret);
			glBindBuffer(GL_ARRAY_BUFFER, ret);
			glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
			return ret;
		}

		void GraphicsDevice::gl_bindVBO(const VBO* vbo)
		{
			if (vbo == NULL)
			{
				if (glstate_ActiveVBO == NULL) return;
				glBindBuffer(GL_ARRAY_BUFFER, NULL);
				glstate_ActiveVBO = NULL;
			}
			if (glstate_ActiveVBO != vbo->m_ID)
			{
				glBindBuffer(GL_ARRAY_BUFFER, vbo->m_ID);
				glstate_ActiveVBO = vbo->m_ID;
			}
		}

		void GraphicsDevice::gl_unbindVBO(const VBO* vbo)
		{
			if (glstate_ActiveVBO == vbo->m_ID)
			{
				glBindBuffer(GL_ARRAY_BUFFER, NULL);
				glstate_ActiveVBO = NULL;
			}
		}

		void GraphicsDevice::gl_destroyVBO(VBO* vbo)
		{
			gl_unbindVBO(vbo);
			glDeleteBuffers(1, &vbo->m_ID);
		}

		GLvoid* GraphicsDevice::gl_mapVBO(VBO* vbo)
		{
			vbo->Bind();
			return glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		}

		void GraphicsDevice::gl_unmapVBO(VBO* vbo)
		{
			vbo->Bind();
			glUnmapBuffer(GL_ARRAY_BUFFER);
		}

		GLuint GraphicsDevice::gl_createIBO(GLushort* indices, GLsizei count)
		{
			GLuint ret;
			glGenBuffers(1, &ret);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ret);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLushort), indices, GL_STATIC_DRAW);
			return ret;
		}

		void GraphicsDevice::gl_bindIBO(const IBO* ibo)
		{
			if (ibo == NULL)
			{
				if (glstate_ActiveIBO == NULL) return;
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);
				glstate_ActiveIBO = NULL;
			}
			if (glstate_ActiveIBO != ibo->m_ID)
			{
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo->m_ID);
				glstate_ActiveIBO = ibo->m_ID;
			}
		}

		void GraphicsDevice::gl_unbindIBO(const IBO* ibo)
		{
			if (glstate_ActiveIBO == ibo->m_ID)
			{
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);
				glstate_ActiveIBO = NULL;
			}
		}

		void GraphicsDevice::gl_destroyIBO(IBO* ibo)
		{
			gl_unbindIBO(ibo);
			glDeleteBuffers(1, &ibo->m_ID);
		}

		GLint GraphicsDevice::gl_getLocation(const Shader* shader, std::string uniformName)
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
