#include "hge-shader-engine.hpp"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include "hge-configure.hpp"
GLuint
hge::render::ShaderEngine::createProgram()
{
	GLuint shaderProgram = glCreateProgram();
	if (shaderProgram == 0)
	{
		HGE_LOG_ERROR("Error creating shader program.");
		HGE_TERMINATE;
	}
	return shaderProgram;
}
GLuint
hge::render::ShaderEngine::addShaderToProgram(
	const std::string &shd,
	const GLenum &shaderType,
	const GLuint &shaderProgram)
{
	GLuint shaderObj = glCreateShader(shaderType);
	if (shaderObj == 0)
	{
		HGE_LOG_ERROR("Error creating shader type.");
		HGE_TERMINATE;
	}
	const char *chtemp = &(shd[0]);
	const GLint uintemp = (GLint)shd.length();
	glShaderSource(shaderObj, 1, &(chtemp), &(uintemp));
	glCompileShader(shaderObj);
	GLint success;
	glGetShaderiv(shaderObj, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		GLchar infoLog[10000] = {0};
		glGetShaderInfoLog(shaderObj, 10000, NULL, infoLog);
		HGE_LOG_ERROR("Error compiling shader type. Info: %s", infoLog);
		HGE_TERMINATE;
	}
	glAttachShader(shaderProgram, shaderObj);
	return shaderObj;
}
void
hge::render::ShaderEngine::run(
	const GLuint &shaderProgram)
{
	GLint isSuccess = (GLint)0;
	GLchar errorLog[10000] = {0};
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &isSuccess);
	if (isSuccess == 0) {
		glGetProgramInfoLog(shaderProgram, sizeof(errorLog), NULL, errorLog);
		HGE_LOG_ERROR("Error linking shader program: %s", errorLog);
		HGE_TERMINATE;
	}
	glValidateProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_VALIDATE_STATUS, &isSuccess);
	if (!isSuccess) {
		glGetProgramInfoLog(shaderProgram, sizeof(errorLog), NULL, errorLog);
		HGE_LOG_ERROR("Invalid shader program: %s", errorLog);
		HGE_TERMINATE;
	}
	glUseProgram(shaderProgram);
}
GLuint
hge::render::ShaderEngine::getUniformLocation(
	const std::string &uname,
	const GLuint &shaderProgram)
{
	return glGetUniformLocation(shaderProgram, &(uname[0]));
}
void hge::render::ShaderEngine::endProgram(
	const GLuint &shaderProgram)
{
	glDeleteProgram(shaderProgram);
}
void hge::render::ShaderEngine::endObject(
	const GLuint &shaderObject)
{
	glDeleteShader(shaderObject);
}
std::shared_ptr<hge::render::ShaderEngine::hgeUniformBlock>
hge::render::ShaderEngine::initUniformBlock(const std::string &uniformBlockName, const GLuint &shaderProgram)
{
	auto result = std::shared_ptr<hgeUniformBlock>(new hgeUniformBlock);
//	result->index = glGetUniformBlockIndex(shaderProgram, uniformBlockName.c_str());
//	glGenBuffers(1, &(result->buffer));
//	glBindBuffer(GL_UNIFORM_BUFFER, result->buffer);
//	glGetActiveUniformBlockiv(shaderProgram, GL_UNIFORM_BLOCK_DATA_SIZE, uniformBlockName.c_str(), &(result->size));
//	glBindBufferBase(GL_UNIFORM_BUFFER, result->index, result->buffer);

	return result;
}
#ifdef GL_ES_VERSION_3_0
void hge::render::ShaderEngine::setUniformBlockData(
		const GLuint &offset,
		const GLuint &sizeOfData,
		const void * const &data,
		const hgeUniformBlockPtr &uniformBlock)
{
	glBindBuffer(GL_UNIFORM_BUFFER, uniformBlock->buffer);
	glBufferSubData(GL_UNIFORM_BUFFER, offset , sizeOfData, data);
}
#endif
std::string hge::render::ShaderEngine::readIntireFile(const std::string &fileName)
{
	std::string result;
	std::ifstream in(fileName, std::ios::in);
	if(in)
	{
		in.seekg(0, std::ios::end);
		result.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&result[0], result.size());
		in.close();
		return result;
	}
	HGE_LOG_ERROR("Error in reading file: %s", fileName.c_str());
	HGE_TERMINATE;
}
