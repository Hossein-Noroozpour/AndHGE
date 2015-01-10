#ifndef HGETERRAINSUNSHADER_HPP
#define	HGETERRAINSUNSHADER_HPP
#include "hge-configure.hpp"
#include "hge-math.hpp"
#include "hge-shader-unit.hpp"
#include <string>
/*
 * \TODO must have a good initializing and removing
 * all program must be removed!!
 */
namespace hge
{
	namespace shader
	{
		class TerrainSunShader : public ShaderUnit
		{
		private:
			/// Model View Projection Matrix Uniform Location
			GLuint mvpmul;
			/// Model Matrix Uniform Location
			GLuint mmul;
			/// Sun Light Direction Location
			GLuint sldul;
			/// Camera Position Relative To Model
			GLuint cprtmul;
			/// Level Of Detail Number
			GLuint lodnul;
			GLuint shaderProgram;
			GLuint vertexShaderProgram;
			GLuint geometryShaderProgram;
			GLuint fragmentShaderProgram;
			/// texture Sampler Location
			GLuint tsl[HGE_TERRAIN_TEXTURE_COUNT];
			GLint vrtxAttInd;
			GLint nrmAttInd;
			GLint tngAttInd;
			GLint btngAttInd;
		public:
			///\note You must initialize OpenGL before call of this function.
			TerrainSunShader();
			~TerrainSunShader();
			void setModelMatrix(const math::Matrix4D<> &modelMatrix);
			void setModelViewProjectionMatrix(const math::Matrix4D<> &modelViewProjectionMatrix);
			void setLODNumber(const GLuint& lodNumber);
			void setSunLightDirection(const math::Vector3D<> &sunDirection);
			void setCameraPositionRelativeToModel(const math::Vector3D<> &p);
			void use();
			GLuint getModelViewProjectionMatrixUniformLocation();
			GLuint getModelMatrixUniformLoaction();
			GLuint getVertexShaderProgram();
			GLuint getGeometryShaderProgram();
			GLuint getFragmentShaderProgram();
			GLuint getShaderProgram();
			GLuint* getTextureSamplerLocations();
			std::string readShaderFile(const std::string &fileName);
		};
	}
}
#endif
