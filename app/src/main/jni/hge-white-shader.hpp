#ifndef HGEWHITESHADER_HPP
#define	HGEWHITESHADER_HPP
#include "hge-math.hpp"
#include "hge-shader-unit.hpp"
/*
 * \todo must have a good initializing and removing
 * all program must be removed!!
 */
namespace hge
{
	namespace shader
	{
		class WhiteShader : public ShaderUnit
		{
		private:
			GLuint modelViewProjectionMatrixUniformLocation;
			GLuint shaderProgram;
			GLuint vertexShaderProgram;
			GLuint fragmentShaderProgram;
		public:
			///\note You must initialize OpenGL before call of this function.
			WhiteShader();
			~WhiteShader();
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
		};
	}
}
#endif
