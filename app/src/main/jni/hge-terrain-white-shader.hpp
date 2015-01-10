#ifndef HGE_TERRAIN_WHITE_SHADER_HPP
#define	HGE_TERRAIN_WHITE_SHADER_HPP
#include "hge-configure.hpp"
#include "hge-math.hpp"
#include "hge-shader-unit.hpp"
#include <string>
namespace hge
{
	namespace shader
	{
		class TerrainWhiteShader : public ShaderUnit
		{
		private:
			GLuint mvpmul;
			GLuint shaderProgram;
			GLuint vertexShaderProgram;
			GLuint fragmentShaderProgram;
		public:
			TerrainWhiteShader();
			~TerrainWhiteShader();
			void setModelMatrix(const math::Matrix4D<> &modelMatrix);
			void setModelViewProjectionMatrix(const math::Matrix4D<> &modelViewProjectionMatrix);
			void setLODNumber(const GLuint& lodNumber);
			void use();
			GLuint getModelViewProjectionMatrixUniformLocation();
			GLuint getModelMatrixUniformLoaction();
			GLuint getVertexShaderProgram();
			GLuint getGeometryShaderProgram();
			GLuint getFragmentShaderProgram();
			GLuint getShaderProgram();
			GLuint getTextureSamplerLocation();
		};
	}
}
#endif
