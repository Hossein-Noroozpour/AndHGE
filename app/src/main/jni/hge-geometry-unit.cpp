#include "hge-geometry-unit.hpp"
#include "hge-main-window.hpp"
#include <string>
#include <cstring>
#ifdef ANDROID
#include <android/log.h>
#else
#include <iostream>
#endif
hge::render::GeometryUnit::GeometryUnit()
#ifdef HGE_BASIC_QUERY_SUPPORT
	:mvp(math::Matrix4D<>(1.0f))
#endif
{
#ifdef HGE_BASIC_QUERY_SUPPORT
	glGenQueries(HGEGEOMETRYNUMBEROFQUERIES, queries);
#endif
}
hge::render::GeometryUnit::~GeometryUnit()
{
#ifdef HGE_BASIC_QUERY_SUPPORT
	glDeleteQueries(HGEGEOMETRYNUMBEROFQUERIES, queries);
#endif
}
void hge::render::GeometryUnit::setMesh(const std::shared_ptr<hge::render::MeshUnit>& m)
{
	mesh = m;
}
#ifdef HGE_BASIC_QUERY_SUPPORT
void hge::render::GeometryUnit::draw()
{
#else
void hge::render::GeometryUnit::draw(const math::Matrix4D<> &vp)
{
#endif
#ifdef HGE_BASIC_QUERY_SUPPORT
#ifdef HGE_CONDITIONAL_RENDERING_SUPPORT
	//glBeginConditionalRender(queries[HGEGEOMETRYOCCLUSIONQUERYINDEX], GL_QUERY_WAIT);
#else
	GLuint query_result = 0;
	glGetQueryObjectuiv(queries[HGEGEOMETRYOCCLUSIONQUERYINDEX], GL_QUERY_RESULT, &query_result);
	if(query_result == 0)
	{
		return;
	}
#endif
#endif
	mesh->bindVBO();
	shader->use();
	texture->bind(GL_TEXTURE0);
	shader->setModelMatrix(modelMatrix.getConstRotateMatrix());
#ifndef HGE_BASIC_QUERY_SUPPORT
	auto mvp = modelMatrix.getConstRotateScaleTranslateMatrix() * vp;
#endif
	shader->setModelViewProjectionMatrix(mvp);
	mesh->bindIBO();
	mesh->draw();
#ifdef HGE_BASIC_QUERY_SUPPORT
#ifdef HGE_CONDITIONAL_RENDERING_SUPPORT
	//glEndConditionalRender();
#endif
#endif
}
#ifdef HGE_BASIC_QUERY_SUPPORT
void hge::render::GeometryUnit::occlusionQuery(const math::Matrix4D<> &vp)
{
	mvp = modelMatrix.getConstRotateScaleTranslateMatrix() * vp;
	glBeginQuery(GL_ANY_SAMPLES_PASSED, queries[HGEGEOMETRYOCCLUSIONQUERYINDEX]);
	occlusionQueryShader->setModelViewProjectionMatrix(mvp);
	occlusionQueryMesh->bindTotal();
	occlusionQueryMesh->draw();
	glEndQuery(GL_ANY_SAMPLES_PASSED);
}
void hge::render::GeometryUnit::occlusionQueryStarter(const math::Matrix4D<> &vp)
{
	mvp = modelMatrix.getConstRotateScaleTranslateMatrix() * vp;
	glBeginQuery(GL_ANY_SAMPLES_PASSED, queries[HGEGEOMETRYOCCLUSIONQUERYINDEX]);
	occlusionQueryMesh->bindTotal();
	occlusionQueryShader->use();
	occlusionQueryShader->setModelViewProjectionMatrix(mvp);
	occlusionQueryMesh->draw();
	glEndQuery(GL_ANY_SAMPLES_PASSED);
}
#endif
void hge::render::GeometryUnit::setShader(const std::shared_ptr<shader::ShaderUnit>& sh)
{
	shader = sh;
}
#ifdef HGE_BASIC_QUERY_SUPPORT
void hge::render::GeometryUnit::setOcclusionQueryShader(const std::shared_ptr<shader::ShaderUnit>& sh)
{
	occlusionQueryShader = sh;
}
#endif
void hge::render::GeometryUnit::setTexture(const std::shared_ptr<texture::TextureUnit>& texture)
{
	this->texture = texture;
}
hge::math::ModelUnit* hge::render::GeometryUnit::getModelMatrix()
{
	return &modelMatrix;
}
std::shared_ptr<hge::render::MeshUnit> hge::render::GeometryUnit::getMesh()
{
	return mesh;
}
#ifdef HGE_BASIC_QUERY_SUPPORT
void hge::render::GeometryUnit::setOcclusionQueryMesh(const std::shared_ptr<MeshUnit> &m)
{
	occlusionQueryMesh = m;
}
#endif
void hge::render::GeometryUnit::setData(std::shared_ptr<utility::Stream> &stream, const bool &endianCompatible)
{
#define HGE_READ_BTYPE(t) stream->read((char *)(&t), sizeof(t));if(!endianCompatible){swapObject((char *)(&t), sizeof(t));}
#ifdef HGE_TEST_MODE
#define HGE_TEST_FORMAT if(stream->isEnd()){HGE_LOG_ERROR("Format error!");}
#else
#define HGE_TEST_FORMAT ;
#endif
#define HGE_READ_STRING(s)\
	{\
		core::Protocol::Types::StringLengthType len;\
		HGE_READ_BTYPE(len);\
		char *str = new char[len + 1];\
		stream->read(str, len);\
		str[len] = 0;\
		s = std::string(str, len);\
		delete [] str;\
	}
	/// ID
//	std::string idStr;
//	HGE_READ_STRING(idStr);
//#ifdef HGE_TEST_MODE
//	HGE_LOG_PRINT("ID string is: (%s) size is: (%d)", idStr.c_str(), idStr.length());
//#endif
//	HGE_TEST_FORMAT;
	/// Name
	std::string nameStr;
	HGE_READ_STRING(nameStr);
#ifdef HGE_TEST_MODE
	HGE_LOG_PRINT("Name string is: (%s) size is: (%d)", nameStr.c_str(), nameStr.length());
#endif
	HGE_TEST_FORMAT;
	/// ID
//	HGE_READ_BTYPE(id);
//#ifdef HGE_TEST_MODE
//	HGE_LOG_PRINT("ID number is: %d", id);
//#endif
	/// Mesh
	mesh = std::shared_ptr<MeshUnit>(new MeshUnit());
	mesh->setData(stream, endianCompatible);
	HGE_TEST_FORMAT;
//	math::Matrix4D<> meshMatrix;
//	meshMatrix.setData(stream, endianCompatible);
//	HGE_TEST_FORMAT;
	// Occlusion mesh
	core::Protocol::Types::HgeBoolean hasOcc;
	HGE_READ_BTYPE(hasOcc);
	if (core::Protocol::Values::HgeTrue == hasOcc)
	{
#ifdef HGE_VERBOSE_TEST_MODE
		HGE_LOG_PRINT("Has occlusion query mesh.");
#endif
#ifndef HGE_BASIC_QUERY_SUPPORT
		std::shared_ptr<MeshUnit> occlusionQueryMesh;
#endif
		occlusionQueryMesh = std::shared_ptr<MeshUnit>(new MeshUnit());
		occlusionQueryMesh->setData(stream, endianCompatible);
//		HGE_TEST_FORMAT;
//		math::Matrix4D<> occlusionQueryMeshMatrix;
//		occlusionQueryMeshMatrix.setData(stream, endianCompatible);
//		HGE_TEST_FORMAT;
	}
}
void hge::render::GeometryUnit::setDataId(const core::Protocol::Types::IdType &id)
{
	this->id = id;
}
hge::core::Protocol::Types::IdType hge::render::GeometryUnit::getDataId()
{
	return id;
}
