#include "Shader.h"

#include "../IO/FileStream.h"
#include "../IO/StreamReader.h"

namespace Sand
{
	namespace Graphics {
		Shader::Shader(GraphicsDevice* graphics, std::string vertexSrc, std::string fragmentSrc)
			: m_Graphics(graphics)
		{
			m_LocationCache = new Collections::Dictionary<std::string, int>();
			compile(vertexSrc, fragmentSrc); 
		}

		Shader::~Shader()
		{
			m_Graphics->gl_destroyShader(this);
			delete m_LocationCache;
		}

		Shader* Shader::Load(Game* game, std::string vertPath, std::string fragPath)
		{
			IO::StreamReader readerVert(new IO::
				FileStream(vertPath, IO::FileAccess::ReadText, IO::FileOpenMode::Open));
			IO::StreamReader readerFrag(new IO::FileStream(fragPath, IO::FileAccess::ReadText, IO::FileOpenMode::Open));
			return new Shader(game->GetGraphics(), readerVert.ReadToEnd(), readerFrag.ReadToEnd());
		}

		bool Shader::compile(std::string vertexSrc, std::string fragmentSrc)
		{
			m_VertexSrc = vertexSrc;
			m_FragmentSrc = fragmentSrc;

			m_Program = m_Graphics->gl_createShaderProgram(vertexSrc, fragmentSrc);
			return m_Program != 0;
		}

		void Shader::Bind() const
		{
			m_Graphics->gl_bindShader(this);
		}

		void Shader::Unbind() const
		{
			m_Graphics->gl_unbindShader(this);
		}

		int Shader::getLocation(std::string uniformName) const
		{
			if (m_LocationCache->ContainsKey(uniformName))
			{
				return (*m_LocationCache)[uniformName];
			}

			m_LocationCache->Add(uniformName, m_Graphics->gl_getLocation(this, uniformName));

			return (*m_LocationCache)[uniformName];
		}

		void Shader::SetUniformInt(std::string name, int value)
		{
			Bind();
			m_Graphics->gl_setUniformInt(getLocation(name), value);
		}

		void Shader::SetUniformIntV(std::string name, int* value, unsigned int count)
		{
			Bind();
			m_Graphics->gl_setUniformIntV(getLocation(name), value, count);
		}

		void Shader::SetUniformDefaultIntV(std::string name, unsigned int count)
		{
			Bind();
			int* arr = new int[count];
			for (int i = 0; i < count; i++) arr[i] = i;
			SetUniformIntV(name, arr, count);
			delete arr;
		}

		void Shader::SetUniformFloat(std::string name, float value)
		{
			Bind();
			m_Graphics->gl_setUniformFloat(getLocation(name), value);
		}

		void Shader::SetUniformVector2(std::string name, Math::Vector2 vector)
		{
			Bind();
			m_Graphics->gl_setUniformVector2(getLocation(name), vector);
		}

		void Shader::SetUniformVector3(std::string name, Math::Vector3 vector)
		{
			Bind();
			m_Graphics->gl_setUniformVector3(getLocation(name), vector);
		}

		void Shader::SetUniformVector4(std::string name, Math::Vector4 vector)
		{
			Bind();
			m_Graphics->gl_setUniformVector4(getLocation(name), vector);
		}

		void Shader::SetUniformColor(std::string name, Color color)
		{
			Bind();
			m_Graphics->gl_setUniformVector4(getLocation(name), color.ToVector4());
		}

		void Shader::SetUniformMatrix(std::string name, Math::Matrix matrix)
		{
			Bind();
			m_Graphics->gl_setUniformMatrix(getLocation(name), matrix);
		}
	}
}
