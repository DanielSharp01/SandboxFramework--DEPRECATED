#pragma once

#include "../Collections/Dictionary.h"
#include "GraphicsDevice.h"
#include "VBOLocation.h"

namespace Sand {
	namespace Graphics {
		class VBO;

		class VAO
		{
			friend GraphicsDevice;
		private:
			GraphicsDevice* m_Graphics;
			GLuint m_ID;

			//NOTE: FOR DEBUGGING PUPROSES
			Collections::Dictionary<VBO*, Collections::ArrayList<VBOLocation>*>* m_VBOLocations;
		public:
			VAO(GraphicsDevice* graphics);
			~VAO();

			void BindVBOToLocation(VBO* vbo, GLint location, GLint componentCount, GLenum componentType = GL_FLOAT, GLint stride = 0, const GLvoid* offset = (const GLvoid*)0);

			void Bind() const;
			void Unbind() const;
		};
	}
}