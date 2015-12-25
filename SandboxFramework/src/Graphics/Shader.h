#pragma once

#include "GraphicsDevice.h"
#include "../Math/structs.h"
#include "../Collections/Dictionary.h"

namespace Sand
{
	namespace Graphics {

		class Shader
		{
			friend GraphicsDevice;
		protected:
			std::string m_VertexSrc, m_FragmentSrc;
			GraphicsDevice* m_Graphics;
			GLuint m_Program;
			Collections::Dictionary<std::string, GLint>* m_LocationCache;

		public:
			Shader(GraphicsDevice* graphics, std::string vertexSrc, std::string fragmentSrc);
			~Shader();

			static Shader* Load(Game* game, std::string vertPath, std::string fragPath);

			void Bind() const;
			void Unbind() const;

			void SetUniformInt(std::string name, int value);
			void SetUniformIntV(std::string name, int* value, unsigned int count);
			void SetUniformDefaultIntV(std::string name, unsigned int count);
			void SetUniformFloat(std::string name, float value);
			void SetUniformVector2(std::string name, Math::Vector2 vector);
			void SetUniformVector3(std::string name, Math::Vector3 vector);
			void SetUniformVector4(std::string name, Math::Vector4 vector);
			void SetUniformColor(std::string name, Color color);
			void SetUniformMatrix(std::string name, Math::Matrix matrix);
		private:
			GLint getLocation(std::string uniformName) const;
			bool compile(std::string vertexSrc, std::string fragmentSrc);
		};
	}
}