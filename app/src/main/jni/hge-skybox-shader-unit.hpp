#ifndef HGESKYBOXSHADERUNIT_HPP
#define HGESKYBOXSHADERUNIT_HPP
#include "hge-shader-unit.hpp"
#include <string>
#define HGESKYBOXSHADERUINTNUMBEROFLEVELS 3
namespace hge
{
	namespace shader
	{
		class SkyBoxShaderUnit : public ShaderUnit
		{
		private:
			GLuint shaderProgram;
			GLuint vertexShaderProgram;
			GLuint geometryShaderProgram;
			GLuint fragmentShaderProgram;
			GLuint modelViewProjectionMatrixUniformLocation;
			GLuint uvMoveUniformLocation;
			GLuint textureSamplerUniformLocation;
			bool hasGeometryShader;
		public:
			SkyBoxShaderUnit(const std::string &fileName, const bool &hasGeometryShader = false);
			virtual ~SkyBoxShaderUnit();
			virtual void setModelMatrix(const math::Matrix4D<> &modelMatrix);
			virtual void setModelViewProjectionMatrix(const math::Matrix4D<> &modelViewProjectionMatrix);
			virtual void setLODNumber(const GLuint& lodNumber);
			virtual void setCloudsSpeed(const float &deltaDistance);
			virtual void use();
			virtual GLuint getModelViewProjectionMatrixUniformLocation();
			virtual GLuint getModelMatrixUniformLoaction();
			virtual GLuint getVertexShaderProgram();
			virtual GLuint getGeometryShaderProgram();
			virtual GLuint getFragmentShaderProgram();
			virtual GLuint getShaderProgram();
		};
	}
}
#endif
