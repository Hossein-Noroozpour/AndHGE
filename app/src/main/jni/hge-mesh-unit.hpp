#ifndef HGE_MESH_UNIT_HPP_
#define HGE_MESH_UNIT_HPP_
#include "hge-configure.hpp"
#include "hge-serializable.hpp"
#ifdef ANDROID
#ifdef HGE_USE_OPENGL_ES_2
#include <GLES2/gl2.h>
#elif defined(HGE_USE_OPENGL_ES_3)
#include <GLES2/gl3.h>
#endif
#else
#include <GL/glew.h>
#include <GL/gl.h>
#endif
namespace hge
{
	namespace render
	{
		class MeshUnit : public core::Serializable
		{
		public:
			///\warning Do not use this ever, this function is only for
			/// internal use.
			MeshUnit();
			///\warning If you do not use this function properly
			/// it will cause core dump!
			MeshUnit(
					const GLfloat* const& vertices,
					const GLuint* const& indices,
					const GLuint& verticesByteSize,
					const GLuint& verticesNumber,
					const GLuint& indicesByteSize);
			~MeshUnit();
			void bindVBO();
			void bindIBO();
			void bindTotal();
			void draw();
			GLuint getVBO();
			GLuint getIBO();
			void setData(std::shared_ptr<utility::Stream> &stream, const bool &endianCompatible = true);
		private:
			GLuint vbo, ibo, vboSize, vboElementsNumber, iboSize, numberOfIndices;
		};
	}
}
#endif
