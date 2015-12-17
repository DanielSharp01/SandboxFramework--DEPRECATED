#include "Shader.h"

#include "../IO/TextReader.h"

namespace Sand
{
	namespace Graphics {
		Shader::Shader(GraphicsDevice* graphics, std::string vertexPath, std::string fragmentPath)
			: m_Graphics(graphics)
		{
			m_LocationCache = new Collections::Dictionary<std::string, GLint>();
			compile(IO::TextReader(vertexPath).ReadToEnd(), IO::TextReader(fragmentPath).ReadToEnd());
		}

		Shader::~Shader()
		{
			m_Graphics->gl_destroyShader(this);
			delete m_LocationCache;
		}

		bool Shader::compile(std::string vertexSrc, std::string fragmentSrc)
		{
			m_VertexSrc = vertexSrc;
			m_FragmentSrc = fragmentSrc;

			m_Program = m_Graphics->gl_createShaderProgram(vertexSrc, fragmentSrc) != 0;
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

		GLint Shader::getLocation(std::string uniformName) const
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
			m_Graphics->gl_setUniformInt(getLocation(name), value);
		}

		void Shader::SetUniformIntV(std::string name, int* value, unsigned int count)
		{
			m_Graphics->gl_setUniformIntV(getLocation(name), value, count);
		}

		void Shader::SetUniformDefaultIntV(std::string name, unsigned int count)
		{
			int* arr = new int[count];
			for (int i = 0; i < count; i++) arr[i] = i;
			SetUniformIntV(name, arr, count);
			delete arr;
		}

		void Shader::SetUniformFloat(std::string name, float value)
		{
			m_Graphics->gl_setUniformFloat(getLocation(name), value);
		}

		void Shader::SetUniformVector2(std::string name, Math::Vector2 vector)
		{
			m_Graphics->gl_setUniformVector2(getLocation(name), vector);
		}

		void Shader::SetUniformVector3(std::string name, Math::Vector3 vector)
		{
			m_Graphics->gl_setUniformVector3(getLocation(name), vector);
		}

		void Shader::SetUniformVector4(std::string name, Math::Vector4 vector)
		{
			m_Graphics->gl_setUniformVector4(getLocation(name), vector);
		}

		void Shader::SetUniformColor(std::string name, Color color)
		{
			m_Graphics->gl_setUniformVector4(getLocation(name), color.ToVector4());
		}

		void Shader::SetUniformMatrix(std::string name, Math::Matrix matrix)
		{
			m_Graphics->gl_setUniformMatrix(getLocation(name), matrix);
		}
	}
}
