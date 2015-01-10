#include "hge-configure.hpp"
#include "hge-terrain-white-shader.hpp"
#include "hge-shader-engine.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#ifdef ANDROID
#include <android/log.h>
#endif
#define HGE_1tab + shaderEndline + shaderTabCharacter +
hge::shader::TerrainWhiteShader::TerrainWhiteShader():
	shaderProgram(render::ShaderEngine::createProgram())
{
	std::string pVS =
			shaderLanguageVersion +
			"layout (location=0) in vec3 " + vertexAttribute + ";" + shaderEndline +
			"uniform mat4 " + modelViewProjectionMatrixUniformName + ";" + shaderEndline +
#define HGE_START_SHDR_FUN "void main()" + shaderEndline + "{"
			HGE_START_SHDR_FUN
			HGE_1tab "gl_Position = " + modelViewProjectionMatrixUniformName + " * vec4(" + vertexAttribute + ", 1.0);" + shaderEndline +
			"}";
#ifdef HGE_TEST_MODE
	HGE_LOG_PRINT("vertext shader is:\n%s", pVS.c_str());
#endif
	std::string pFS =
			shaderLanguageVersion +
			"out vec4 fragColor;" + shaderEndline +
			HGE_START_SHDR_FUN
			HGE_1tab "fragColor = vec4(0.5);" + shaderEndline +
			"}";

#ifdef HGE_TEST_MODE
	HGE_LOG_PRINT("fragment shader is:\n%s", pFS.c_str());
#endif
#undef HGE_START_SHDR_FUN
	vertexShaderProgram = render::ShaderEngine::addShaderToProgram(pVS, GL_VERTEX_SHADER, shaderProgram);
#ifdef HGE_TEST_MODE
	HGE_LOG_PRINT("Vertext shader compiled.");
#endif
	fragmentShaderProgram = render::ShaderEngine::addShaderToProgram(pFS, GL_FRAGMENT_SHADER, shaderProgram);
#ifdef HGE_TEST_MODE
	HGE_LOG_PRINT("Fragment shader compiled.");
#endif
	hge::render::ShaderEngine::run(shaderProgram);
	mvpmul = render::ShaderEngine::getUniformLocation(modelViewProjectionMatrixUniformName, shaderProgram);
#ifdef HGE_DEBUG_MODE
	assert(mvpmul != 0xFFFFFFFF);
#endif
	glUniformMatrix4fv(mvpmul, 1, GL_FALSE, math::Matrix4D<>(1.0f).mat);
}
hge::shader::TerrainWhiteShader::~TerrainWhiteShader()
{
	hge::render::ShaderEngine::endObject(vertexShaderProgram);
	hge::render::ShaderEngine::endObject(fragmentShaderProgram);
	hge::render::ShaderEngine::endProgram(shaderProgram);
}
void hge::shader::TerrainWhiteShader::setModelMatrix(const math::Matrix4D<> &modelMatrix)
{
}
void hge::shader::TerrainWhiteShader::setModelViewProjectionMatrix(const math::Matrix4D<> &modelViewProjectionMatrix)
{
	glUniformMatrix4fv(mvpmul, 1, GL_FALSE, modelViewProjectionMatrix.mat);
}
void hge::shader::TerrainWhiteShader::setLODNumber(const GLuint& lodNumber)
{
}
void hge::shader::TerrainWhiteShader::use()
{
	glUseProgram(shaderProgram);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, HGE_TERRAIN_COMPONENT_COUNT * sizeof(GLfloat), (void*) 0);
}
GLuint hge::shader::TerrainWhiteShader::getModelViewProjectionMatrixUniformLocation()
{
	return mvpmul;
}
GLuint hge::shader::TerrainWhiteShader::getModelMatrixUniformLoaction()
{
	return 0;
}
GLuint hge::shader::TerrainWhiteShader::getVertexShaderProgram()
{
	return vertexShaderProgram;
}
GLuint hge::shader::TerrainWhiteShader::getGeometryShaderProgram()
{
	return 0;
}
GLuint hge::shader::TerrainWhiteShader::getFragmentShaderProgram()
{
	return fragmentShaderProgram;
}
GLuint hge::shader::TerrainWhiteShader::getShaderProgram()
{
	return shaderProgram;
}
GLuint hge::shader::TerrainWhiteShader::getTextureSamplerLocation()
{
	return 0;
}
