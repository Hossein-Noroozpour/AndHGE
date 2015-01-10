#include "hge-configure.hpp"
#include "hge-terrain-unlit-shader.hpp"
#include "hge-shader-engine.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#ifdef ANDROID
#include <android/log.h>
#endif
#define HGE_1tab + shaderEndline + shaderTabCharacter +
#define HGE_2tab + shaderEndline + shaderTabCharacter + shaderTabCharacter +
#define HGE_3tab + shaderEndline + shaderTabCharacter + shaderTabCharacter + shaderTabCharacter +
#define HGE_4tab + shaderEndline + shaderTabCharacter + shaderTabCharacter + shaderTabCharacter + shaderTabCharacter +
#define HGE_5tab + shaderEndline + shaderTabCharacter + shaderTabCharacter + shaderTabCharacter + shaderTabCharacter + shaderTabCharacter +
#define HGE_6tab + shaderEndline + shaderTabCharacter + shaderTabCharacter + shaderTabCharacter + shaderTabCharacter + shaderTabCharacter + shaderTabCharacter + s
hge::shader::TerrainUnlitShader::TerrainUnlitShader():
	shaderProgram(render::ShaderEngine::createProgram())
{
	std::string pVS =
			shaderLanguageVersion +
			"layout (location=0) in vec3 " + vertexAttribute + ";" + shaderEndline +
			//All of the normals must be normalized.
			"layout (location=1) in vec3 " + normalAttribute + ";" + shaderEndline +
			//All of the tangents must be normalized.
			"layout (location=2) in vec3 " + tangentAttribute + ";" + shaderEndline +
			//All of the bitangents must be normalized.
			"layout (location=3) in vec3 " + bitangentAttribute + ";" + shaderEndline +
#define VSVERTEXDATA \
			"VertexData" + shaderEndline + \
			"{" \
			HGE_1tab "vec2 " + uvAttribute + ";" + shaderEndline + \
			"} "
			"out " VSVERTEXDATA  + vertexOutName + ";" + shaderEndline +
			"uniform mat4 " + modelViewProjectionMatrixUniformName + ";" + shaderEndline +
#define HGE_START_SHDR_FUN "void main()" + shaderEndline + "{"
			HGE_START_SHDR_FUN
			//HGE_1tab vertexOutName + "." + lightIntensityVarName + " = float(max(float(dot(" + sunDirectionUniformName + ", " + normalAttribute + ")), 0.1));" + shaderEndline +
			HGE_1tab "gl_Position = " + modelViewProjectionMatrixUniformName + " * vec4(" + vertexAttribute + ", 1.0);"
			HGE_1tab vertexOutName + "." + uvAttribute + " = vec2(" + vertexAttribute + ".x + " + vertexAttribute + ".z, " +
			vertexAttribute + ".y + " + vertexAttribute + ".z);" + shaderEndline +
			"}";
#ifdef HGE_TEST_MODE
	HGE_LOG_PRINT("vertext shader is:\n%s", pVS.c_str());
#endif
	std::string pFS =
			shaderLanguageVersion +
			"in " VSVERTEXDATA + vertexInName + ";" + shaderEndline +
#define HGE_V_I vertexInName + "." +
#define HGE_V_I_uv  HGE_V_I uvAttribute +
			"out vec4 fragColor;" + shaderEndline +
			"uniform sampler2D " + textureSampler + ";" + shaderEndline +
			HGE_START_SHDR_FUN
			HGE_1tab "fragColor = texture2D(" + textureSampler + ", " + HGE_V_I_uv ");" + shaderEndline +
			"}";

#ifdef HGE_TEST_MODE
	HGE_LOG_PRINT("fragment shader is:\n%s", pFS.c_str());
#endif
#undef HGE_V_I_uv
#undef HGE_V_I
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
	tsl = render::ShaderEngine::getUniformLocation(textureSampler, shaderProgram);
#ifdef HGE_DEBUG_MODE
	assert(tsl != 0xFFFFFFFF);
#endif
	glUniform1i(tsl, 0);
}
hge::shader::TerrainUnlitShader::~TerrainUnlitShader()
{
	hge::render::ShaderEngine::endObject(vertexShaderProgram);
	hge::render::ShaderEngine::endObject(fragmentShaderProgram);
	hge::render::ShaderEngine::endProgram(shaderProgram);
}
void hge::shader::TerrainUnlitShader::setModelMatrix(const math::Matrix4D<> &modelMatrix)
{
}
void hge::shader::TerrainUnlitShader::setModelViewProjectionMatrix(const math::Matrix4D<> &modelViewProjectionMatrix)
{
	glUniformMatrix4fv(mvpmul, 1, GL_FALSE, modelViewProjectionMatrix.mat);
}
void hge::shader::TerrainUnlitShader::setLODNumber(const GLuint& lodNumber)
{
}
void hge::shader::TerrainUnlitShader::use()
{
	glUseProgram(shaderProgram);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, HGE_TERRAIN_COMPONENT_COUNT * sizeof(GLfloat), (void*) 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, HGE_TERRAIN_COMPONENT_COUNT * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, HGE_TERRAIN_COMPONENT_COUNT * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, HGE_TERRAIN_COMPONENT_COUNT * sizeof(GLfloat), (void*)(9 * sizeof(GLfloat)));
}
GLuint hge::shader::TerrainUnlitShader::getModelViewProjectionMatrixUniformLocation()
{
	return mvpmul;
}
GLuint hge::shader::TerrainUnlitShader::getModelMatrixUniformLoaction()
{
	return 0;
}
GLuint hge::shader::TerrainUnlitShader::getVertexShaderProgram()
{
	return vertexShaderProgram;
}
GLuint hge::shader::TerrainUnlitShader::getGeometryShaderProgram()
{
	return 0;
}
GLuint hge::shader::TerrainUnlitShader::getFragmentShaderProgram()
{
	return fragmentShaderProgram;
}
GLuint hge::shader::TerrainUnlitShader::getShaderProgram()
{
	return shaderProgram;
}
GLuint hge::shader::TerrainUnlitShader::getTextureSamplerLocation()
{
	return tsl;
}
