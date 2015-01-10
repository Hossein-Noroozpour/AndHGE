#ifndef HGESUNSHADER_HPP
#define	HGESUNSHADER_HPP
#include "hge-math.hpp"
#include "hge-shader-unit.hpp"
/*
 * \TODO must have a good initializing and removing
 * all program must be removed!!
 */
namespace hge
{
	namespace shader
	{
		class SunShader : public ShaderUnit
		{
		private:
			GLuint modelViewProjectionMatrixUniformLocation;
			GLuint modelMatrixUniformLocation;
			GLuint shaderProgram;
			GLuint vertexShaderProgram;
			GLuint fragmentShaderProgram;
			GLuint sunLightDirectionUniformLocation;
			GLuint textureSamplerLocation;
			GLint vertexAttInd;
			GLint normalAttInd;
			GLint uvAttInd;
		public:
			///\note You must initialize OpenGL before call of this function.
			SunShader(const math::Vector3D<> &sunDirection = math::Vector3D<>(0.0f, 0.0f, 1.0f));
			~SunShader();
			void setModelMatrix(const math::Matrix4D<> &modelMatrix);
			void setModelViewProjectionMatrix(const math::Matrix4D<> &modelViewProjectionMatrix);
			void setLODNumber(const GLuint& lodNumber);
			void setSunDirection(const math::Vector3D<> &sunDirection = math::Vector3D<>(1.0f));
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
