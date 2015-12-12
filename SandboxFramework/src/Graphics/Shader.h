#pragma once

#include "GraphicsDevice.h"
#include "../Math/structs.h"
#include "../Collections/Dictionary.h"
#include "../Content/FileReader.h"

namespace SandboxFramework
{
	namespace Graphics {

		class Shader
		{
			friend GraphicsDevice;
		private:
			std::string m_VertexPath, m_FragmentPath;
			GraphicsDevice* m_Graphics;
			GLuint m_Program;
			Collections::Dictionary<std::string, GLint>* locationCache;

		public:
			Shader(GraphicsDevice* graphics, std::string vertexPath, std::string fragmentPath);
			~Shader();

			void Bind() const;
			void Unbind() const;

			GLint getLocation(std::string uniformName) const;
			void setUniformInt(std::string name, int value);
			void setUniformFloat(std::string name, float value);
			void setUniformVector2(std::string name, Math::Vector2 vector);
			void setUniformVector3(std::string name, Math::Vector3 vector);
			void setUniformVector4(std::string name, Math::Vector4 vector);
			void setUniformMatrix(std::string name, Math::Matrix matrix);
		private:
			bool compile(std::string vertexSrc, std::string fragmentSrc);
		};
	}
}