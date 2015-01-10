#ifndef HGETERRAINUNIT_HPP
#define	HGETERRAINUNIT_HPP
#include <string>
#include <vector>
#include "hge-mesh-unit.hpp"
#include "hge-model-unit.hpp"
#include "hge-shader-unit.hpp"
#include "hge-texture-unit.hpp"
#include "hge-data-object.hpp"
#include <memory>
namespace hge
{
	namespace render
	{
		///\note This terrain gets meshes and shaders and in its draw-call uses each meshes and shaders with same index
		/// for rendering and all the textures will be feed to the all the shaders.
		class TerrainUnit : public core::DataObject
		{
		public:
			TerrainUnit();
			TerrainUnit(const int16_t *const &heights, const int &aspect, const double &verticalDegree, const double &horizontalDegree);
			~TerrainUnit();
			void draw(const math::Matrix4D<> &vp);
			void setShader (const std::shared_ptr<shader::ShaderUnit>& s);
			void addTexture(const std::shared_ptr<texture::TextureUnit>& texture);
			///\warning Do not delete this pointer.
			math::ModelUnit* getModelMatrix();
			// serializable part
			void setData(std::shared_ptr<utility::Stream> &stream, const bool &endianCompatible);
			// end of serializable part
			// data object part
			void setDataId(const core::Protocol::Types::IdType &id);
			core::Protocol::Types::IdType getDataId();
			// end of data object
		private:
			GLuint vboBuffer;
			GLuint numberOfIndices;
			std::vector<GLuint> iboBuffers;
			std::vector<GLuint> iboElements;
			math::Matrix4D<> mvp;
			math::ModelUnit modelMatrix;
			std::shared_ptr<shader::ShaderUnit> shader;
			std::vector<std::shared_ptr<texture::TextureUnit> > textures;
			core::Protocol::Types::IdType id;
			void calculateNTBs(const int &aspect, const double &verticalDegree, const double &horizontalDegree, GLfloat* vbo, const int16_t *const &heights);
			///\warning This function does not delete vertices pointer and caller must take care of it.
			void setVBO(const GLfloat *const &vertices, const GLuint &verticesBytes);
			///\warning This function does not delete indices pointer and caller must take care of it.
#ifdef HGE_USE_OPENGL_ES_2
			void addIBO(const GLushort *const &ibo, const GLuint &indicesBytes);
#else
			void addIBO(const GLuint *const &ibo, const GLuint &indicesBytes);
#endif
		};
	}
}
#endif
