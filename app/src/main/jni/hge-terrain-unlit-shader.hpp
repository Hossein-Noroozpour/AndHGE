#ifndef HGE_TERRAIN_UNLIT_SHADER_HPP
#define	HGE_TERRAIN_UNLIT_SHADER_HPP
#include "hge-configure.hpp"
#include "hge-math.hpp"
#include "hge-shader-unit.hpp"
#include <string>
namespace hge
{
	namespace shader
	{
		class TerrainUnlitShader : public ShaderUnit
		{
		private:
			/// Model View Projection Matrix Uniform Location
			GLuint mvpmul;
			GLuint shaderProgram;
			GLuint vertexShaderProgram;
			GLuint fragmentShaderProgram;
			/// texture Sampler Location
			GLuint tsl;
		public:
			///\note You must initialize OpenGL before call of this function.
			TerrainUnlitShader();
			~TerrainUnlitShader();
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
