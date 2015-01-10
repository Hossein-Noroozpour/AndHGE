#include "hge-white-shader.hpp"
#include <iostream>
#include <cassert>
#include "hge-shader-engine.hpp"
hge::shader::WhiteShader::WhiteShader():
	shaderProgram(render::ShaderEngine::createProgram())
{
	std::string pVS =
			shaderLanguageVersion + precisionDefinition + shaderEndline +
			attributeIdentifier + "vec3 " + vertexAttribute + ";" + shaderEndline +
			"uniform mat4 " + modelViewProjectionMatrixUniformName + ";" + shaderEndline +
			"void main()" + shaderEndline +
			"{" + shaderEndline +
			shaderTabCharacter + "gl_Position = " + modelViewProjectionMatrixUniformName + " * vec4(" + vertexAttribute + ", 1.0);" + shaderEndline +
			"}" + shaderEndline;
#ifdef HGE_VERBOSE_TEST_MODE
	HGE_LOG_PRINT("Vertex shader is: \n%s", pVS.c_str());
#endif
	///////////////////////////////////////////////////////////////////////
#if defined(HGE_USE_OPENGL_ES_2) || defined(HGE_USE_OPENGL_ES_3)
	std::string fragColor("gl_FragColor");
#else
	std::string fragColor("fragColor");
#endif
	std::string pFS =
			shaderLanguageVersion + precisionDefinition + shaderEndline +
#if defined(HGE_USE_OPENGL_ES_2) || defined(HGE_USE_OPENGL_ES_3)

#else
		stageOutIdentifier + "vec4 " + fragColor + ";" + shaderEndline +
#endif
		"void main()" + shaderEndline +
		"{" + shaderEndline +
			shaderTabCharacter + fragColor + " =  vec4(1.0);" + shaderEndline +
		"}" + shaderEndline;
#ifdef HGE_VERBOSE_TEST_MODE
	HGE_LOG_PRINT("Fragment shader is: \n%s", pFS.c_str());
#endif
	///////////////////////////////////////////////////////////////////////
	vertexShaderProgram = render::ShaderEngine::addShaderToProgram(pVS, GL_VERTEX_SHADER, shaderProgram);
#ifdef HGE_VERBOSE_TEST_MODE
	HGE_LOG_PRINT("Vertex shader compiled successfully.");
#endif
	fragmentShaderProgram = render::ShaderEngine::addShaderToProgram(pFS, GL_FRAGMENT_SHADER, shaderProgram);
#ifdef HGE_VERBOSE_TEST_MODE
	HGE_LOG_PRINT("Fragment shader compiled successfully.");
#endif
	hge::render::ShaderEngine::run(shaderProgram);
#ifdef HGE_VERBOSE_TEST_MODE
	HGE_LOG_PRINT("Shader program run successfully.");
#endif
	modelViewProjectionMatrixUniformLocation = render::ShaderEngine::getUniformLocation(modelViewProjectionMatrixUniformName, shaderProgram);
#ifdef HGE_DEBUG_MODE
	assert(modelViewProjectionMatrixUniformLocation != 0xFFFFFFFF);
#endif
	math::Matrix4D<GLfloat> modelViewProjectionMatrix(1.0f);
	glUniformMatrix4fv(modelViewProjectionMatrixUniformLocation, 1, GL_FALSE, modelViewProjectionMatrix.mat);
}
hge::shader::WhiteShader::~WhiteShader()
{
	hge::render::ShaderEngine::endObject(vertexShaderProgram);
	hge::render::ShaderEngine::endObject(fragmentShaderProgram);
	hge::render::ShaderEngine::endProgram(shaderProgram);
}
void hge::shader::WhiteShader::setModelMatrix(const math::Matrix4D<> &modelMatrix)
{
	(void) modelMatrix;
	HGE_LOG_ERROR("Error this shader does not have model matrix.");
	//HGE_TERMINATE;
}
void hge::shader::WhiteShader::setModelViewProjectionMatrix(const math::Matrix4D<> &modelViewProjectionMatrix)
{
	glUniformMatrix4fv(modelViewProjectionMatrixUniformLocation, 1, GL_FALSE, modelViewProjectionMatrix.mat);
}
void hge::shader::WhiteShader::setLODNumber(const GLuint& lodNumber)
{
	(void) lodNumber;
	HGE_LOG_ERROR("Error this shader does not have LOD system.");
	//HGE_TERMINATE;
}
void hge::shader::WhiteShader::use()
{
	glUseProgram(shaderProgram);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
}
GLuint hge::shader::WhiteShader::getModelViewProjectionMatrixUniformLocation()
{
	return modelViewProjectionMatrixUniformLocation;
}
GLuint hge::shader::WhiteShader::getModelMatrixUniformLoaction()
{
	HGE_LOG_ERROR("Error this shader does not have model matrix.");
	//HGE_TERMINATE;
	return 0;
}
GLuint hge::shader::WhiteShader::getVertexShaderProgram()
{
	return vertexShaderProgram;
}
GLuint hge::shader::WhiteShader::getGeometryShaderProgram()
{
	HGE_LOG_ERROR("Error this shader program does not have geometry shader.");
	//HGE_TERMINATE;
	return 0;
}
GLuint hge::shader::WhiteShader::getFragmentShaderProgram()
{
	return fragmentShaderProgram;
}
GLuint hge::shader::WhiteShader::getShaderProgram()
{
	return shaderProgram;
}
