#include "GraphicsDevice.h"

#include "Shader.h"
#include "VAO.h"
#include "VBO.h"
#include "IBO.h"
#include "Texture2D.h"

namespace Sand
{
	namespace Graphics
	{
		GraphicsDevice::GraphicsDevice(Game* game)
		{
			m_Game = game;
			m_Viewport = Viewport(m_Game->GetWidth(), m_Game->GetHeight(), -1.0f, 1.0f);

			glEnable(GL_BLEND);
			SetDepthTestMode(DepthTestMode::None);
			SetBlendState(BlendState::Opaque);
			glGenFramebuffers(1, &frameBuffer);
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

		void GraphicsDevice::SetRenderTarget(Texture2D* texture)
		{
			if (texture == NULL)
			{
				glBindFramebuffer(GL_FRAMEBUFFER, 0);
				m_Viewport = m_SavedViewport;
				glViewport(0, 0, m_Viewport.m_Width, m_Viewport.m_Height);
			}
			else
			{
				glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
				glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture->m_ID, 0);
				texture->m_Refreshable = true;
				GLenum buff[1] = { GL_COLOR_ATTACHMENT0 };
				glDrawBuffers(1, buff);
				m_SavedViewport = m_Viewport;
				m_Viewport = Viewport(texture->m_Width, texture->m_Height, m_SavedViewport.m_Near, m_SavedViewport.m_Far);
				glViewport(0, 0, m_Viewport.m_Width, m_Viewport.m_Height);
			}
		}

		void GraphicsDevice::SetRenderTargets(Texture2D** textures, unsigned int count)
		{
			if (count == 0) return;

			glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
			for (int i = 0; i < count; i++)
			{
				glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, textures[i]->m_ID, 0);
				textures[i]->m_Refreshable = true;
			}

			GLenum* buff = new GLenum[count];
			for (int i = 0; i < count; i++)
			{
				buff[i] = GL_COLOR_ATTACHMENT0 + i;
			}
			glDrawBuffers(count, buff);
			m_SavedViewport = m_Viewport;
			m_Viewport = Viewport(textures[0]->m_Width, textures[0]->m_Height, m_SavedViewport.m_Near, m_SavedViewport.m_Far);
			glViewport(0, 0, m_Viewport.m_Width, m_Viewport.m_Height);
		}

		void GraphicsDevice::SetDepthTestMode(DepthTestMode mode)
		{
			if (glstate_DepthTestMode != mode)
			{
				if (mode == DepthTestMode::None)
				{
					glDisable(GL_DEPTH_TEST);
				}
				else if (mode == DepthTestMode::BackToFront)
				{
					glEnable(GL_DEPTH_TEST);
					glDepthFunc(GL_LEQUAL);
				}
				else if (mode == DepthTestMode::FrontToBack)
				{
					glEnable(GL_DEPTH_TEST);
					glDepthFunc(GL_GEQUAL);
				}
				else if (mode == DepthTestMode::AlphaBackToFront)
				{
					glEnable(GL_ALPHA_TEST);
					glEnable(GL_DEPTH_TEST);
					glDepthFunc(GL_LEQUAL);
				}
				else if (mode == DepthTestMode::AlphaFrontToBack)
				{
					glEnable(GL_ALPHA_TEST);
					glEnable(GL_DEPTH_TEST);
					glDepthFunc(GL_GEQUAL);
				}

				glstate_DepthTestMode = mode;
			}
		}

		void GraphicsDevice::SetAlphaTestTreshold(float treshold)
		{
			glAlphaFunc(GL_GEQUAL, treshold);
		}

		void GraphicsDevice::SetBlendFactor(Color color)
		{
			if (glstate_ConstantColor != color)
			{
				glBlendColor(color.R, color.G, color.B, color.A);
				glstate_ConstantColor = color;
			}
		}

		void GraphicsDevice::SetBlendState(BlendState state)
		{
			if (glstate_BlendState != state)
			{
				glBlendFunc(state.Source, state.Destination);
				glstate_BlendState = state;
			}
		}

		void GraphicsDevice::SetBlendState(Blend source, Blend destination)
		{
			BlendState state(source, destination);
			if (glstate_BlendState != state)
			{
				glBlendFunc(state.Source, state.Destination);
				glstate_BlendState = state;
			}
		}

		void GraphicsDevice::setViewportSize(unsigned int width, unsigned int height)
		{
			m_Viewport.m_Width = width;
			m_Viewport.m_Height = height;
			glViewport(0, 0, width, height);
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

		GLint GraphicsDevice::gl_getLocation(const Shader* shader, std::string uniformName)
		{
			gl_bindShader(shader);
			return glGetUniformLocation(shader->m_Program, uniformName.c_str());
		}

		void GraphicsDevice::gl_setUniformInt(GLint location, int value)
		{
			glUniform1i(location, value);
		}

		void GraphicsDevice::gl_setUniformIntV(GLint location, int* value, unsigned int count)
		{
			glUniform1iv(location, count, value);
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

		void GraphicsDevice::gl_bindVBOToLocation(const VBO* vbo, GLint location, GLType componentType, GLsizei componentCount, GLsizei stride, const GLvoid* offset)
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

		GLuint GraphicsDevice::gl_createTexture2D(BYTE* data, GLsizei width, GLsizei height, ImageFormat imageFormat)
		{
			GLuint ret;
			glGenTextures(1, &ret);
			glBindTexture(GL_TEXTURE_2D, ret);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, imageFormat, GL_UNSIGNED_BYTE, data);
			
			return ret;
		}

		void GraphicsDevice::gl_setTextureFilters(const Texture2D* texture, TextureFilter minFilter, TextureFilter magFilter)
		{
			gl_bindTexture2D(texture);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
		}

		void GraphicsDevice::gl_bindTexture2D(const Texture2D* texture)
		{
			if (texture == NULL)
			{
				if (glstate_ActiveTexture2D == NULL) return;
				glBindTexture(GL_TEXTURE_2D, NULL);
				glstate_ActiveTexture2D = NULL;
			}
			if (glstate_ActiveTexture2D != texture->m_ID)
			{
				glBindTexture(GL_TEXTURE_2D, texture->m_ID);
				glstate_ActiveTexture2D = texture->m_ID;
			}
		}

		void GraphicsDevice::gl_unbindTexture2D(const Texture2D* texture)
		{
			if (glstate_ActiveTexture2D == texture->m_ID)
			{
				glBindTexture(GL_TEXTURE_2D, NULL);
				glstate_ActiveTexture2D = NULL;
			}
		}

		//TODO: Think about throwing an exception
		void GraphicsDevice::gl_SetActiveTexture(GLuint slot)
		{	
			glActiveTexture(GL_TEXTURE0 + slot);
		}

		void GraphicsDevice::gl_destroyTexture2D(Texture2D* texture)
		{
			gl_unbindTexture2D(texture);
			glDeleteTextures(1, &texture->m_ID);
		}

		void GraphicsDevice::gl_refreshPixelData(Texture2D* texture)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
			glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture->m_ID, 0);
			glViewport(0, 0, texture->m_Width, texture->m_Height);
			glReadBuffer(GL_COLOR_ATTACHMENT0);
			BYTE* data = new BYTE[texture->m_Width * texture->m_Height * 4];
			glReadPixels(0, 0, texture->m_Width, texture->m_Height, GL_RGBA, GL_UNSIGNED_BYTE, data);
			texture->m_Data = data;
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			glViewport(0, 0, m_Viewport.m_Width, m_Viewport.m_Height);
		}

		void GraphicsDevice::gl_setSubTexture2D(Texture2D* texture, BYTE* data, GLuint x, GLuint y, GLuint width, GLuint height)
		{
			gl_bindTexture2D(texture);
			glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
		}
	}
}
