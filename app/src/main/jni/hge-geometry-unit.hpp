#ifndef HGE_GEOMETRY_UNIT_HPP
#define HGE_GEOMETRY_UNIT_HPP
#include "hge-configure.hpp"
#include "hge-mesh-unit.hpp"
#include "hge-model-unit.hpp"
#include "hge-shader-unit.hpp"
#include "hge-texture-unit.hpp"
#include "hge-math.hpp"
#include "hge-data-object.hpp"
#include "hge-stream.hpp"
#include <string.h>
//#define HGEGEOMETRYDEBUGMVPVALUECHECK
#ifdef HGE_BASIC_QUERY_SUPPORT
#define HGEGEOMETRYNUMBEROFQUERIES 2
#define HGEGEOMETRYOCCLUSIONQUERYINDEX 0
#define HGEGEOMETRYPIXELSPASSED 1
#endif
namespace hge
{
	namespace render
	{
		class GeometryUnit : public core::DataObject
		{
		public:
			GeometryUnit();
			~GeometryUnit();
			void setMesh(const std::shared_ptr<MeshUnit> &m);
#ifdef HGE_BASIC_QUERY_SUPPORT
			void setOcclusionQueryMesh(const std::shared_ptr<MeshUnit> &m);
			void draw();
			void occlusionQuery(const math::Matrix4D<>& vp);
			void occlusionQueryStarter(const math::Matrix4D<>& vp);
			void setOcclusionQueryShader(const std::shared_ptr<shader::ShaderUnit>& shader);
#else
			void draw(const math::Matrix4D<> &vp);
#endif
			void setShader(const std::shared_ptr<shader::ShaderUnit>& shader);
			void setTexture(const std::shared_ptr<texture::TextureUnit>& texture);
			math::ModelUnit* getModelMatrix();
			std::shared_ptr<MeshUnit> getMesh();
			// serializable part
			void setData(std::shared_ptr<utility::Stream> &stream, const bool &endianCompatible = true);
			// end of serializable part
			// data object part
			void setDataId(const core::Protocol::Types::IdType &id);
			core::Protocol::Types::IdType getDataId();
			// end of data object
		private:
			core::Protocol::Types::IdType id;
			math::ModelUnit modelMatrix;
			std::shared_ptr<MeshUnit> mesh;
			std::shared_ptr<shader::ShaderUnit> shader;
			std::shared_ptr<texture::TextureUnit> texture;
#ifdef HGE_BASIC_QUERY_SUPPORT
			GLuint queries[HGEGEOMETRYNUMBEROFQUERIES];
			math::Matrix4D<> mvp;
			std::shared_ptr<MeshUnit> occlusionQueryMesh;
			std::shared_ptr<shader::ShaderUnit> occlusionQueryShader;
#endif
		};
	}
}
#endif
