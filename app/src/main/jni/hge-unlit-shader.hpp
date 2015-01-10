#ifndef HGE_UNLIT_SHADER_HPP
#define	HGE_UNLIT_SHADER_HPP
#include "hge-math.hpp"
#include "hge-shader-unit.hpp"
namespace hge
{
	namespace shader
	{
		class UnlitShader : public ShaderUnit
		{
		private:
			GLuint modelViewProjectionMatrixUniformLocation;
			GLuint shaderProgram;
			GLuint vertexShaderProgram;
			GLuint fragmentShaderProgram;
			GLuint textureSamplerLocation;
		public:
			///\note You must initialize OpenGL before call of this function.
			UnlitShader(const math::Vector3D<> &sunDirection = math::Vector3D<>(0.0f, 0.0f, 1.0f));
			~UnlitShader();
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
