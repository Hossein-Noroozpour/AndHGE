#include "hge-skybox-shader-unit.hpp"
#include "hge-shader-engine.hpp"
#include <iostream>
#include <cassert>
hge::shader::SkyBoxShaderUnit::SkyBoxShaderUnit(const std::string &fileName, const bool &hasGeometryShader)
{
	this->hasGeometryShader = hasGeometryShader;

	shaderProgram = render::ShaderEngine::createProgram();

	auto pVS = render::ShaderEngine::readIntireFile(fileName + ".vertexShader");
	vertexShaderProgram = render::ShaderEngine::addShaderToProgram(pVS, GL_VERTEX_SHADER, shaderProgram);
#ifdef ANDROID
#else
	if(hasGeometryShader)
	{
		auto pGS = render::ShaderEngine::readIntireFile(fileName + ".geometryShader");
		geometryShaderProgram = render::ShaderEngine::addShaderToProgram(pGS, GL_GEOMETRY_SHADER, shaderProgram);
	}
#endif
	auto pFS = render::ShaderEngine::readIntireFile(fileName + ".fragmentShader");
	fragmentShaderProgram = render::ShaderEngine::addShaderToProgram(pFS, GL_FRAGMENT_SHADER, shaderProgram);

	render::ShaderEngine::run(shaderProgram);

	modelViewProjectionMatrixUniformLocation =
			render::ShaderEngine::getUniformLocation(std::string("mvpm"), shaderProgram);
	assert(modelViewProjectionMatrixUniformLocation != 0xFFFFFFFF);
	glUniformMatrix4fv(modelViewProjectionMatrixUniformLocation, 1, GL_FALSE, math::Matrix4D<>(1.0f).mat);

	uvMoveUniformLocation =	render::ShaderEngine::getUniformLocation(std::string("uvMove"), shaderProgram);
	assert(uvMoveUniformLocation != 0xFFFFFFFF);
	glUniform1f(uvMoveUniformLocation, 0.0f);

	textureSamplerUniformLocation = render::ShaderEngine::getUniformLocation("ts" , shaderProgram);
	assert(textureSamplerUniformLocation != 0xFFFFFFFF);
	glUniform1i(textureSamplerUniformLocation, 0);
}
hge::shader::SkyBoxShaderUnit::~SkyBoxShaderUnit()
{
	hge::render::ShaderEngine::endObject(vertexShaderProgram);
	if(hasGeometryShader) hge::render::ShaderEngine::endObject(geometryShaderProgram);
	hge::render::ShaderEngine::endObject(fragmentShaderProgram);
	hge::render::ShaderEngine::endProgram(shaderProgram);
}

void hge::shader::SkyBoxShaderUnit::setModelMatrix(const math::Matrix4D<> &modelMatrix)
{
	(void) modelMatrix;
	HGE_LOG_ERROR("This shader does not have model matrix.");
	HGE_TERMINATE;
}

void hge::shader::SkyBoxShaderUnit::setModelViewProjectionMatrix(const math::Matrix4D<> &modelViewProjectionMatrix)
{
	glUniformMatrix4fv(modelViewProjectionMatrixUniformLocation, 1, GL_FALSE, modelViewProjectionMatrix.mat);
}

void hge::shader::SkyBoxShaderUnit::setLODNumber(const GLuint& lodNumber)
{
	(void)lodNumber;
	HGE_LOG_ERROR("This shader does not have LOD system.");
	HGE_TERMINATE;
}

void hge::shader::SkyBoxShaderUnit::setCloudsSpeed(const float &deltaDistance)
{
	glUniform1f(uvMoveUniformLocation, deltaDistance);
}

void hge::shader::SkyBoxShaderUnit::use()
{
	glUseProgram(shaderProgram);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*) 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
}

GLuint hge::shader::SkyBoxShaderUnit::getModelViewProjectionMatrixUniformLocation()
{
	return modelViewProjectionMatrixUniformLocation;
}

GLuint hge::shader::SkyBoxShaderUnit::getModelMatrixUniformLoaction()
{
	HGE_LOG_ERROR("This shader does not have model matrix.");
	HGE_TERMINATE;
	return 0;
}

GLuint hge::shader::SkyBoxShaderUnit::getVertexShaderProgram()
{
	return vertexShaderProgram;
}

GLuint hge::shader::SkyBoxShaderUnit::getGeometryShaderProgram()
{
	if(hasGeometryShader)
	{
		HGE_LOG_ERROR("This shader does not have geometry shader.");
		HGE_TERMINATE;
	}
	return 0;
}

GLuint hge::shader::SkyBoxShaderUnit::getFragmentShaderProgram()
{
	return fragmentShaderProgram;
}

GLuint hge::shader::SkyBoxShaderUnit::getShaderProgram()
{
	return shaderProgram;
}
