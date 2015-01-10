#ifndef HGE_SHADER_UNIT_HPP_
#define HGE_SHADER_UNIT_HPP_
#include "hge-configure.hpp"
#ifdef ANDROID
#ifdef HGE_USE_OPENGL_ES_3
#include <GLES3/gl3.h>
#elif defined(HGE_USE_OPENGL_ES_2)
#include <GLES2/gl2.h>
#endif
#else
#include <GL/glew.h>
#include <GL/gl.h>
#endif
#include "hge-math.hpp"
#include <string>
namespace hge
{
	namespace shader
	{
		class ShaderUnit
		{
		protected:
			static const std::string shaderLanguageVersion;
			static const std::string vsUvOutVarName;
			static const std::string vsWorldPositionOutVarName;
			static const std::string lightIntensityVarName;
			static const std::string modelViewProjectionMatrixUniformName;
			static const std::string modelMatrixUniformName;
			static const std::string sunDirectionUniformName;
			static const std::string vertexAttribute;
			static const std::string normalAttribute;
			static const std::string zAttribute;
			static const std::string uvAttribute;
			static const std::string tangentAttribute;
			static const std::string bitangentAttribute;
			static const std::string vertexInName;
			static const std::string vertexOutName;
			static const std::string shaderEndline;
			static const std::string shaderTabCharacter;
			static const std::string textureSampler;
			static const std::string attributeIdentifier;
			static const std::string stageInIdentifier;
			static const std::string stageOutIdentifier;
			static const std::string precisionDefinition;
			static const std::string fragColor;
			static const std::string fragColorDefinition;
			static const std::string normalVar;
			static const std::string tangentVar;
			static const std::string bitangentVar;
			static const std::string uvVar;
		public:
			virtual void setModelMatrix(const math::Matrix4D<> &modelMatrix) = 0;
			virtual void setModelViewProjectionMatrix(const math::Matrix4D<> &modelViewProjectionMatrix) = 0;
			virtual void setLODNumber(const GLuint& lodNumber) = 0;
			virtual void use() = 0;
			virtual GLuint getModelViewProjectionMatrixUniformLocation() = 0;
			virtual GLuint getModelMatrixUniformLoaction() = 0;
			virtual GLuint getVertexShaderProgram() = 0;
			virtual GLuint getGeometryShaderProgram() = 0;
			virtual GLuint getFragmentShaderProgram() = 0;
			virtual GLuint getShaderProgram() = 0;
		};
	}
}
#endif
