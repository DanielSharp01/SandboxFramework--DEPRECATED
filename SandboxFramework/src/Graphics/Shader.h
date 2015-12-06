#pragma once

#include "GraphicsDevice.h"
#include "../Math/Vector2.h"
#include "../Math/Vector3.h"
#include "../Math/Vector4.h"
#include "../Math/Matrix.h"

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

			bool compile(std::string vertexSrc, std::string fragmentSrc);
			void Use();

			GLint getLocation(std::string uniformName);
			void setUniformInt(std::string name, int value);
			void setUniformFloat(std::string name, float value);
			void setUniformVector2(std::string name, Math::Vector2 vector);
			void setUniformVector3(std::string name, Math::Vector3 vector);
			void setUniformVector4(std::string name, Math::Vector4 vector);
			void setUniformMatrix(std::string name, Math::Matrix matrix);
		};
	}
}