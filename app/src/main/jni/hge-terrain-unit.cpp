#include "hge-terrain-unit.hpp"
#include "hge-camera-unit.hpp"
#include "hge-main-window.hpp"
#include <iostream>
#include <thread>
#include <mutex>
#include <functional>
#include <cmath>
#ifdef ANDROID
#include <android/log.h>
#endif
#ifdef _WIN32
#define M_PI 3.1415926535897932384626433832795
#endif
#define NORMALCALCULATIONDEBUGMODE
//#define NORMALCALCULATIONDEBUGMOD2
#define PRINTVECTOR(v) std::cout << " x: " << v.x << " y: " << v.y << " z: " << v.z << std::endl;
#define NORMALCALCULATIONDEBUGPRINT \
if(tmpv.z < 0.0)\
{\
	HGE_LOG_ERROR("Error in normal calculation.");\
	HGE_TERMINATE;\
}
#define CHECKLENGTHZERO \
if(glm::length(tmpv1) == 0.0)\
{\
	HGE_LOG_ERROR("Error normal is zero.");\
	PRINTVECTOR(tmpv2)\
	PRINTVECTOR(tmpv3)\
	HGE_TERMINATE;\
}
#define D1toD2(arr, row, col) arr[(row * width) + col]
//#define HGETERRAINLOADINGDEBUGMODE
hge::render::TerrainUnit::TerrainUnit()
{}
hge::render::TerrainUnit::TerrainUnit(const int16_t *const &heights, const int &aspect,
	const double &verticalDegree, const double &horizontalDegree)
{
	GLfloat *vbo = new GLfloat[aspect * aspect * HGE_TERRAIN_COMPONENT_COUNT];
	calculateNTBs(aspect, verticalDegree, horizontalDegree, vbo, heights);
#ifdef HGE_USE_OPENGL_ES_2
	GLushort *ibo = new GLushort[(aspect - 1) * (aspect - 1) * 6];
	for (int l = 0, iboIndex = 0; l < HGE_TERRAIN_LOD_NUMDER; l++)
	{
		iboIndex = 0;
		for (int i = 0, lStride = 1 << l; i < aspect - lStride; i += lStride)
		{
			for (int j = 0; j < aspect - lStride; j += lStride)
			{
				ibo[iboIndex++] = GLushort((i * aspect) + j);
				ibo[iboIndex++] = GLushort(((i + lStride) * aspect) + j + lStride);
				ibo[iboIndex++] = GLushort(((i + lStride) * aspect) + j);
				ibo[iboIndex++] = GLushort((i * aspect) + j);
				ibo[iboIndex++] = GLushort((i * aspect) + j + lStride);
				ibo[iboIndex++] = GLushort(((i + lStride) * aspect) + j + lStride);
			}
		}
		addIBO(ibo, iboIndex * sizeof(GLushort));
	}
#else
	GLuint *ibo = new GLuint[(aspect - 1) * (aspect - 1) * 6];
	for (int l = 0, iboIndex = 0; l < HGE_TERRAIN_LOD_NUMDER; l++)
	{
		iboIndex = 0;
		for (int i = 0, lStride = 1 << l; i < aspect - lStride; i += lStride)
		{
			for (int j = 0; j < aspect - lStride; j += lStride)
			{
				ibo[iboIndex++] = GLuint((i            * aspect) + j);
				ibo[iboIndex++] = GLuint(((i + lStride) * aspect) + j);
				ibo[iboIndex++] = GLuint(((i + lStride) * aspect) + j + lStride);
				ibo[iboIndex++] = GLuint((i            * aspect) + j);
				ibo[iboIndex++] = GLuint(((i + lStride) * aspect) + j + lStride);
				ibo[iboIndex++] = GLuint((i            * aspect) + j + lStride);
			}
		}
		addIBO(ibo, iboIndex * sizeof(GLuint));
	}
#endif
	setVBO(vbo, aspect * aspect * HGE_TERRAIN_COMPONENT_COUNT * sizeof(GLfloat));
	delete[] ibo;
	delete[] vbo;
}
void hge::render::TerrainUnit::calculateNTBs(const int &aspect, const double &verticalDegree, const double &horizontalDegree, GLfloat *vbo, const int16_t *const &heights)
{
	(void)horizontalDegree;
	const double earthRaidus = 6371000.0;
	const double deltaDegree = 0.004166667;
	/// Vertical delta distance
	const double vDD = (deltaDegree * earthRaidus * M_PI) / 180.0;
	for (int i = 0, vboIndex = 0; i < aspect; i++)
	{
		const double hDD = ((deltaDegree* earthRaidus * M_PI * cos(((verticalDegree - (i * deltaDegree)) * M_PI) / 180.0)) / 180.0);
		for (int j = 0; j < aspect; j++)
		{
			vbo[vboIndex++] = GLfloat((j - (aspect / 2.0f)) * hDD);
			vbo[vboIndex++] = GLfloat(((aspect / 2.0f) - i) * vDD);
			vbo[vboIndex++] = GLfloat(heights[(i * aspect) + j]);
			vboIndex += 9;
		}
	}
	auto getVEC = [&](const int &i, const int &j, const int &ci, const int &cj) -> hge::math::Vector3D < >
	{
		uint64_t tmpInt1 = (((i*aspect) + j)*HGE_TERRAIN_COMPONENT_COUNT);
		uint64_t tmpInt2 = (((ci*aspect) + cj)*HGE_TERRAIN_COMPONENT_COUNT);
		return math::Vector3D<>(vbo[tmpInt1] - vbo[tmpInt2],
			vbo[tmpInt1 + 1] - vbo[tmpInt2 + 1],
			vbo[tmpInt1 + 2] - vbo[tmpInt2 + 2]);
	};
	int i, j, vboIndex;
	for (i = 0, vboIndex = 0; i < aspect; i++)
	{
		for (j = 0; j < aspect; j++)
		{
			math::Vector3D<> nv(0.0f, 0.0f, 0.0f);
			if (i > 0)
			{
				if (j > 0)
				{
					math::Vector3D<> N = getVEC(i - 1, j, i, j);
					math::Vector3D<> W = getVEC(i, j - 1, i, j);
					math::Vector3D<> NW = getVEC(i - 1, j - 1, i, j);
					nv += math::Vector3D<>::normalize(math::Vector3D<>::cross(N, NW));
					nv += math::Vector3D<>::normalize(math::Vector3D<>::cross(NW, W));
				}
				if (j < aspect - 1)
				{
					math::Vector3D<> N = getVEC(i - 1, j, i, j);
					math::Vector3D<> NE = getVEC(i - 1, j + 1, i, j);
					math::Vector3D<> E = getVEC(i, j + 1, i, j);
					nv += math::Vector3D<>::normalize(math::Vector3D<>::cross(NE, N));
					nv += math::Vector3D<>::normalize(math::Vector3D<>::cross(E, NE));
				}
			}
			if (i < aspect - 1)
			{
				if (j > 0)
				{
					math::Vector3D<> S = getVEC(i + 1, j, i, j);
					math::Vector3D<> SW = getVEC(i + 1, j - 1, i, j);
					math::Vector3D<> W = getVEC(i, j - 1, i, j);
					nv += math::Vector3D<>::normalize(math::Vector3D<>::cross(SW, S));
					nv += math::Vector3D<>::normalize(math::Vector3D<>::cross(W, SW));
				}
				if (j < aspect - 1)
				{
					math::Vector3D<> S = getVEC(i + 1, j, i, j);
					math::Vector3D<> E = getVEC(i, j + 1, i, j);
					math::Vector3D<> SE = getVEC(i + 1, j + 1, i, j);
					nv += math::Vector3D<>::normalize(math::Vector3D<>::cross(S, SE));
					nv += math::Vector3D<>::normalize(math::Vector3D<>::cross(SE, E));
				}
			}
			nv = math::Vector3D<>::normalize(nv);
			math::Vector3D<> tv = math::Vector3D<>::normalize(math::Vector3D<>(0.0f, 1.0f, 0.0f) - (nv * (nv.vec[1])));
			math::Vector3D<> btv = math::Vector3D<>::cross(nv, tv);
			vboIndex += 3;
			vbo[vboIndex++] = nv.vec[0];
			vbo[vboIndex++] = nv.vec[1];
			vbo[vboIndex++] = nv.vec[2];
			vbo[vboIndex++] = tv.vec[0];
			vbo[vboIndex++] = tv.vec[1];
			vbo[vboIndex++] = tv.vec[2];
			vbo[vboIndex++] = btv.vec[0];
			vbo[vboIndex++] = btv.vec[1];
			vbo[vboIndex++] = btv.vec[2];
		}
	}
}
hge::render::TerrainUnit::~TerrainUnit()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &vboBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	for (unsigned int i = 0; i < iboBuffers.size(); i++)
	{
		glDeleteBuffers(1, &(iboBuffers[i]));
	}
}
void hge::render::TerrainUnit::draw(const math::Matrix4D<> &vp)
{
	glBindBuffer(GL_ARRAY_BUFFER, vboBuffer);
	shader->use();
	for (unsigned int i = 0; i < textures.size(); i++)
	{
		textures[i]->bind(GL_TEXTURE0 + i);
	}
	shader->setModelViewProjectionMatrix(vp);
	//for (unsigned int i = 0; i < iboBuffers.size(); i++)
	//{
	//	shader->setLODNumber(i);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboBuffers[0]);
#ifdef HGE_USE_OPENGL_ES_2
		glDrawElements(GL_TRIANGLES, iboElements[0], GL_UNSIGNED_SHORT, (void *)(0));
#else
		glDrawElements(GL_TRIANGLES, iboElements[0], GL_UNSIGNED_INT, (void *)(0));
#endif
	//}
}
void hge::render::TerrainUnit::setVBO(const GLfloat * const &vertices, const GLuint &verticesBytes)
{
	glGenBuffers(1, &vboBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vboBuffer);
	glBufferData(GL_ARRAY_BUFFER, verticesBytes, vertices, GL_STATIC_DRAW);
}
#ifdef HGE_USE_OPENGL_ES_2
void hge::render::TerrainUnit::addIBO(const GLushort *const &indices, const GLuint &indicesBytes)
#else
void hge::render::TerrainUnit::addIBO(const GLuint *const &indices, const GLuint &indicesBytes)
#endif
{
	GLuint ibo;
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesBytes, indices, GL_STATIC_DRAW);
#ifdef HGE_USE_OPENGL_ES_2
	iboElements.push_back(indicesBytes / (sizeof(GLushort)));
#else
	iboElements.push_back(indicesBytes / (sizeof(GLuint)));
#endif
	iboBuffers.push_back(ibo);
}
void hge::render::TerrainUnit::setShader(const std::shared_ptr<shader::ShaderUnit>& s)
{
	shader = s;
}
void hge::render::TerrainUnit::addTexture(const std::shared_ptr<texture::TextureUnit>& texture)
{
	textures.push_back(texture);
}
hge::math::ModelUnit *hge::render::TerrainUnit::getModelMatrix()
{
	return &modelMatrix;
}
void hge::render::TerrainUnit::setData(std::shared_ptr<utility::Stream> &stream, const bool &endianCompatible)
{
#define HGE_READ_BTYPE(t) stream->read((char*)(&t),sizeof(t));if(!endianCompatible){swapObject((char *)(&t),sizeof(t));}
#define HGE_TEST_FORMAT if(stream->isEnd()){HGE_LOG_ERROR("Format error!");}
	core::Protocol::Types::TerrainAspectType aspect;
	HGE_READ_BTYPE(aspect);
#ifdef HGE_TEST_MODE
	HGE_LOG_PRINT("Aspect is: %d", aspect);
#endif
#ifdef HGE_INTENSIVE_DEBUG_MODE
	if (powf(2.f, floorf(log2f(aspect))) != float(aspect))
	{
		HGE_LOG_ERROR("Error: Terrain aspect is not a power of 2 number.");
		HGE_TERMINATE;
	}
	HGE_TEST_FORMAT;
#endif
	HGE_READ_BTYPE(id);
#ifdef HGE_INTENSIVE_DEBUG_MODE
	if (id < 8)
	{
		HGE_LOG_PRINT("Error: Terrain ID is less than 8 this means its exporter part doesn't work very well.");
	}
	HGE_TEST_FORMAT;
#endif
	core::Protocol::Types::TerrainVboComponentsCountType vbo_com_cnt;
	HGE_READ_BTYPE(vbo_com_cnt);
#ifdef HGE_DEBUG_MODE
	if (HGE_TERRAIN_COMPONENT_COUNT != vbo_com_cnt)
	{
		/// \todo Add support for different VBO component count.
		HGE_LOG_ERROR("Error: Terrain VBO component is not equal to imported terrain.");
		HGE_TERMINATE;
	}
	HGE_TEST_FORMAT;
#endif
	core::Protocol::Types::VertexElementType *vbo_data = new core::Protocol::Types::VertexElementType[vbo_com_cnt * aspect * aspect];
	stream->read((char *)(vbo_data), aspect * aspect * vbo_com_cnt * sizeof(core::Protocol::Types::VertexElementType));
	/*for (int i = 0; i < aspect * aspect * vbo_com_cnt;)
	{
		for (int j = 0; j < vbo_com_cnt; j++) std::cout << vbo_data[i++] << " ";
		std::cout << std::endl;
	}*/
	if (!endianCompatible)
	{
		for (int i = 0; i < aspect * aspect * vbo_com_cnt; i++)
		{
			swapObject((char *)(&(vbo_data[i])), sizeof(core::Protocol::Types::VertexElementType));
		}
	}
#ifdef HGE_USE_OPENGL_ES_2
	GLushort *ibo = new GLushort[(aspect - 1) * (aspect - 1) * 6];
	for (int l = 0, iboIndex = 0; l < HGE_TERRAIN_LOD_NUMDER; l++)
	{
		iboIndex = 0;
		for (int i = 0, lStride = 1 << l; i < aspect - lStride; i += lStride)
		{
			for (int j = 0; j < aspect - lStride; j += lStride)
			{
				ibo[iboIndex++] = GLushort((i * aspect) + j);
				ibo[iboIndex++] = GLushort(((i + lStride) * aspect) + j + lStride);
				ibo[iboIndex++] = GLushort(((i + lStride) * aspect) + j);
				ibo[iboIndex++] = GLushort((i * aspect) + j);
				ibo[iboIndex++] = GLushort((i * aspect) + j + lStride);
				ibo[iboIndex++] = GLushort(((i + lStride) * aspect) + j + lStride);
			}
		}
		addIBO(ibo, iboIndex * sizeof(GLushort));
	}
#else
	GLuint *ibo = new GLuint[(aspect - 1) * (aspect - 1) * 6];
	for (int l = 0, iboIndex = 0; l < HGE_TERRAIN_LOD_NUMDER; l++)
	{
		iboIndex = 0;
		for (int i = 0, lStride = 1 << l; i < aspect - lStride; i += lStride)
		{
			for (int j = 0; j < aspect - lStride; j += lStride)
			{
				ibo[iboIndex++] = GLuint((i * aspect) + j);
				ibo[iboIndex++] = GLuint(((i + lStride) * aspect) + j + lStride);
				ibo[iboIndex++] = GLuint(((i + lStride) * aspect) + j);
				ibo[iboIndex++] = GLuint((i * aspect) + j);
				ibo[iboIndex++] = GLuint((i * aspect) + j + lStride);
				ibo[iboIndex++] = GLuint(((i + lStride) * aspect) + j + lStride);
			}
		}
		addIBO(ibo, iboIndex * sizeof(GLuint));
	}
#endif
	setVBO(vbo_data, aspect * aspect * HGE_TERRAIN_COMPONENT_COUNT * sizeof(core::Protocol::Types::VertexElementType));
	delete[] ibo;
	delete[] vbo_data;
}
void hge::render::TerrainUnit::setDataId(const core::Protocol::Types::IdType &id)
{
	this->id = id;
}
hge::core::Protocol::Types::IdType hge::render::TerrainUnit::getDataId()
{
	return id;
}
