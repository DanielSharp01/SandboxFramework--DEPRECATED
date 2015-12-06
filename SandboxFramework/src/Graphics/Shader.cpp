#include "Shader.h"

namespace SandboxFramework
{
	namespace Graphics {
		Shader::Shader(GraphicsDevice* graphics, std::string vertexPath, std::string fragmentPath)
			: m_Graphics(graphics), m_VertexPath(vertexPath), m_FragmentPath(fragmentPath)
		{
			locationCache = new Collections::Dictionary<std::string, GLint>();
			compile(Content::FileReader(vertexPath, "rt").ReadToEnd(), Content::FileReader(vertexPath, "rt").ReadToEnd());
		}

		Shader::~Shader()
		{
			m_Graphics->gl_destroyShader(this);
			delete locationCache;
		}

		bool Shader::compile(std::string vertexSrc, std::string fragmentSrc)
		{
			return m_Graphics->gl_createShaderProgram(vertexSrc, fragmentSrc) != 0;
		}

		void Shader::Use()
		{
			m_Graphics->gl_bindShader(this);
		}

		GLint Shader::getLocation(std::string uniformName)
		{
			if (locationCache->ContainsKey(uniformName))
			{
				return (*locationCache)[uniformName];
			}

			locationCache->Add(uniformName, m_Graphics->gl_getLocation(this, uniformName));

			return (*locationCache)[uniformName];
		}

		void Shader::setUniformInt(std::string name, int value)
		{
			m_Graphics->gl_setUniformInt(getLocation(name), value);
		}

		void Shader::setUniformFloat(std::string name, float value)
		{
			m_Graphics->gl_setUniformFloat(getLocation(name), value);
		}

		void Shader::setUniformVector2(std::string name, Math::Vector2 vector)
		{
			m_Graphics->gl_setUniformVector2(getLocation(name), vector);
		}

		void Shader::setUniformVector3(std::string name, Math::Vector3 vector)
		{
			m_Graphics->gl_setUniformVector3(getLocation(name), vector);
		}

		void Shader::setUniformVector4(std::string name, Math::Vector4 vector)
		{
			m_Graphics->gl_setUniformVector4(getLocation(name), vector);
		}

		void Shader::setUniformMatrix(std::string name, Math::Matrix matrix)
		{
			m_Graphics->gl_setUniformMatrix(getLocation(name), matrix);
		}
	}
}
