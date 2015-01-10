#include "hge-unlit-shader.hpp"
#include "hge-shader-engine.hpp"
#include <iostream>
#include <cassert>
#ifdef ANDROID
#include <android/log.h>
#endif
hge::shader::UnlitShader::UnlitShader(const math::Vector3D<> &sunDirection) :
shaderProgram(render::ShaderEngine::createProgram())
{
	std::string pVS =
		shaderLanguageVersion +
		"layout (location=0) in vec3 " + vertexAttribute + ";" + shaderEndline +
		"layout (location=1) in vec2 " + uvAttribute + ";" + shaderEndline +
		"out vec2 " + vsUvOutVarName + ";" + shaderEndline +
		"uniform mat4 " + modelViewProjectionMatrixUniformName + ";" + shaderEndline +
		"void main()" + shaderEndline + "{" + shaderEndline +
		shaderTabCharacter + "gl_Position = " + modelViewProjectionMatrixUniformName + " * vec4(" + vertexAttribute + ", 1.0);" + shaderEndline +
		shaderTabCharacter + vsUvOutVarName + " = " + uvAttribute + ";" + shaderEndline +
		"}" + shaderEndline;
	///////////////////////////////////////////////////////////////////////
	std::string pFS =
		shaderLanguageVersion +
		"in vec2 " + vsUvOutVarName + ";" + shaderEndline +
		"out vec4 fragColor;" + shaderEndline +
		"uniform sampler2D " + textureSampler + ";" + shaderEndline +
		"void main()" + shaderEndline + "{" + shaderEndline +
		shaderTabCharacter + "fragColor = texture2D(" + textureSampler + ", " + vsUvOutVarName + ");" + shaderEndline +
		"}" + shaderEndline;
	///////////////////////////////////////////////////////////////////////
	vertexShaderProgram = render::ShaderEngine::addShaderToProgram(pVS, GL_VERTEX_SHADER, shaderProgram);
	fragmentShaderProgram = render::ShaderEngine::addShaderToProgram(pFS, GL_FRAGMENT_SHADER, shaderProgram);
	hge::render::ShaderEngine::run(shaderProgram);
	modelViewProjectionMatrixUniformLocation = render::ShaderEngine::getUniformLocation(modelViewProjectionMatrixUniformName, shaderProgram);
#ifdef HGE_DEBUG_MODE
	assert(modelViewProjectionMatrixUniformLocation != 0xFFFFFFFF);
#endif
	glUniformMatrix4fv(modelViewProjectionMatrixUniformLocation, 1, GL_FALSE, math::Matrix4D<>(1.0f).mat);
	textureSamplerLocation = render::ShaderEngine::getUniformLocation(textureSampler, shaderProgram);
#ifdef HGE_DEBUG_MODE
	assert(textureSamplerLocation != 0xFFFFFFFF);
#endif
	glUniform1i(textureSamplerLocation, 0);
}
hge::shader::UnlitShader::~UnlitShader()
{
	hge::render::ShaderEngine::endObject(vertexShaderProgram);
	hge::render::ShaderEngine::endObject(fragmentShaderProgram);
	hge::render::ShaderEngine::endProgram(shaderProgram);
}
void hge::shader::UnlitShader::setModelMatrix(const math::Matrix4D<> &modelMatrix)
{
	(void)modelMatrix;
	/// \todo throw exception in future.
}
void hge::shader::UnlitShader::setModelViewProjectionMatrix(const math::Matrix4D<> &modelViewProjectionMatrix)
{
	glUniformMatrix4fv(modelViewProjectionMatrixUniformLocation, 1, GL_FALSE, modelViewProjectionMatrix.mat);
}
void hge::shader::UnlitShader::setLODNumber(const GLuint& lodNumber)
{
	(void)lodNumber;
	HGE_LOG_ERROR("Error this shader does not have LOD system.");
}
void hge::shader::UnlitShader::use()
{
	glUseProgram(shaderProgram);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
}
GLuint hge::shader::UnlitShader::getModelViewProjectionMatrixUniformLocation()
{
	return modelViewProjectionMatrixUniformLocation;
}
GLuint hge::shader::UnlitShader::getModelMatrixUniformLoaction()
{
	return 0;
}
GLuint hge::shader::UnlitShader::getVertexShaderProgram()
{
	return vertexShaderProgram;
}
GLuint hge::shader::UnlitShader::getGeometryShaderProgram()
{
	HGE_LOG_ERROR("Error this shader program does not have geometry shader.");
	return 0;
}
GLuint hge::shader::UnlitShader::getFragmentShaderProgram()
{
	return fragmentShaderProgram;
}
GLuint hge::shader::UnlitShader::getShaderProgram()
{
	return shaderProgram;
}
GLuint hge::shader::UnlitShader::getTextureSamplerLocation()
{
	return textureSamplerLocation;
}
