#include "hge-sun-shader.hpp"
#include "hge-shader-engine.hpp"
#include "hge-main-window.hpp"
#include <iostream>
#include <cassert>
hge::shader::SunShader::SunShader(const math::Vector3D<> &sunDirection):
	shaderProgram(render::ShaderEngine::createProgram())
{
	std::string pVS =
			shaderLanguageVersion + precisionDefinition + shaderEndline +
			attributeIdentifier + "vec3 " + vertexAttribute + ";" + shaderEndline +
			attributeIdentifier + "vec3 " + normalAttribute + ";" + shaderEndline +
			attributeIdentifier + "vec2 " + uvAttribute + ";" + shaderEndline +
			stageOutIdentifier + "vec2 " + vsUvOutVarName + ";" + shaderEndline +
			stageOutIdentifier + "float " + lightIntensityVarName + ";" + shaderEndline +
			"uniform mat4 " + modelViewProjectionMatrixUniformName + ";" + shaderEndline +
			"uniform mat4 " + modelMatrixUniformName + ";" + shaderEndline +
			"uniform vec3 " + sunDirectionUniformName + ";" + shaderEndline +
			"void main()" + shaderEndline +
			"{" + shaderEndline +
			shaderTabCharacter + lightIntensityVarName + " = float(max(float(dot(" + sunDirectionUniformName + ", vec3(" +
				modelMatrixUniformName + " * vec4(" + normalAttribute + ", 1.0)))), 0.1));" + shaderEndline +
			shaderTabCharacter + "gl_Position = " + modelViewProjectionMatrixUniformName + " * vec4(" + vertexAttribute +
				", 1.0);" + shaderEndline +
			shaderTabCharacter + vsUvOutVarName + " = " + uvAttribute + ";" + shaderEndline +
			"}" + shaderEndline;
#ifdef HGE_VERBOSE_TEST_MODE
	HGE_LOG_PRINT("Vertex shader is: \n%s", pVS.c_str());
#endif
	///////////////////////////////////////////////////////////////////////
	std::string pFS =
			shaderLanguageVersion + precisionDefinition + shaderEndline +
			stageInIdentifier + "vec2 " + vsUvOutVarName + ";" + shaderEndline +
#if !defined(HGE_USE_OPENGL_ES_2) && !defined(HGE_USE_OPENGL_ES_3)
			stageOutIdentifier + "vec4 gl_FragColor;\n" +
#endif
			stageInIdentifier + "float " + lightIntensityVarName + ";" + shaderEndline +
			"uniform sampler2D " + textureSampler + ";" + shaderEndline +
			"void main()" + shaderEndline +
			"{" + shaderEndline +
			shaderTabCharacter + "if(" + lightIntensityVarName + " > 1.0) gl_FragColor = texture2D(" +
				textureSampler + ", " + vsUvOutVarName + ");" + shaderEndline +
			shaderTabCharacter + "else if(" + lightIntensityVarName + " > 0.3) gl_FragColor = texture2D(" +
				textureSampler + ", " + vsUvOutVarName + ") * " + lightIntensityVarName + ";" + shaderEndline +
			shaderTabCharacter + "else gl_FragColor = texture2D(" + textureSampler + ", " + vsUvOutVarName + ") * 0.3;" + shaderEndline +
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
	vertexAttInd = glGetAttribLocation(shaderProgram, vertexAttribute.c_str());
#ifdef HGE_DEBUG_MODE
	if(-1 == vertexAttInd) ui::MainWindow::printGraphicAPIErrorAndTerminate();
#endif
	normalAttInd = glGetAttribLocation(shaderProgram, normalAttribute.c_str());
#ifdef HGE_DEBUG_MODE
	if(-1 == normalAttInd) ui::MainWindow::printGraphicAPIErrorAndTerminate();
#endif
	uvAttInd = glGetAttribLocation(shaderProgram, uvAttribute.c_str());
#ifdef HGE_DEBUG_MODE
	if(-1 == uvAttInd) ui::MainWindow::printGraphicAPIErrorAndTerminate();
#endif
	modelMatrixUniformLocation = render::ShaderEngine::getUniformLocation(modelMatrixUniformName, shaderProgram);
#ifdef HGE_DEBUG_MODE
	assert(modelMatrixUniformLocation != 0xFFFFFFFF);
#endif
	glUniformMatrix4fv(modelMatrixUniformLocation, 1, GL_FALSE, math::Matrix4D<>(1.0f).mat);
	//HGE_LOG_PRINT("Program is %d", modelMatrixUniformLocation);
	//hge::ui::MainWindow::printGraphicAPIErrorAndTerminate();
	//HGE_IMMIDIATE_PRINT
	modelViewProjectionMatrixUniformLocation = render::ShaderEngine::getUniformLocation(modelViewProjectionMatrixUniformName, shaderProgram);
#ifdef HGE_DEBUG_MODE
	assert(modelViewProjectionMatrixUniformLocation != 0xFFFFFFFF);
#endif
	glUniformMatrix4fv(modelViewProjectionMatrixUniformLocation, 1, GL_FALSE, math::Matrix4D<>(1.0f).mat);
	sunLightDirectionUniformLocation = render::ShaderEngine::getUniformLocation(sunDirectionUniformName, shaderProgram);
#ifdef HGE_DEBUG_MODE
	assert(sunLightDirectionUniformLocation != 0xFFFFFFFF);
#endif
	glUniform3fv(sunLightDirectionUniformLocation, 1, sunDirection.vec);
	textureSamplerLocation = render::ShaderEngine::getUniformLocation(textureSampler, shaderProgram);
#ifdef HGE_DEBUG_MODE
	assert(textureSamplerLocation != 0xFFFFFFFF);
#endif
	glUniform1i(textureSamplerLocation, 0);
}
hge::shader::SunShader::~SunShader()
{
	hge::render::ShaderEngine::endObject(vertexShaderProgram);
	hge::render::ShaderEngine::endObject(fragmentShaderProgram);
	hge::render::ShaderEngine::endProgram(shaderProgram);
}
void hge::shader::SunShader::setModelMatrix(const math::Matrix4D<> &modelMatrix)
{
	glUniformMatrix4fv(modelMatrixUniformLocation, 1, GL_FALSE, modelMatrix.mat);
}
void hge::shader::SunShader::setModelViewProjectionMatrix(const math::Matrix4D<> &modelViewProjectionMatrix)
{
	glUniformMatrix4fv(modelViewProjectionMatrixUniformLocation, 1, GL_FALSE, modelViewProjectionMatrix.mat);
}
void hge::shader::SunShader::setLODNumber(const GLuint& lodNumber)
{
	(void) lodNumber;
	HGE_LOG_ERROR("Error this shader does not have LOD system.");
	HGE_TERMINATE;
}
void hge::shader::SunShader::setSunDirection(const math::Vector3D<> &sunDirection)
{
	glUniform3fv(sunLightDirectionUniformLocation, 1, sunDirection.vec);
}
void hge::shader::SunShader::use()
{
	glUseProgram(shaderProgram);
#if defined(HGE_USE_OPENGL_ES_2) || defined(HGE_USE_OPENGL_ES_3)
	glEnableVertexAttribArray(vertexAttInd);
	glEnableVertexAttribArray(normalAttInd);
	glEnableVertexAttribArray(uvAttInd);
	glVertexAttribPointer(vertexAttInd, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*) 0);
	glVertexAttribPointer(normalAttInd, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glVertexAttribPointer(uvAttInd, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
#else
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*) 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
#endif
}
GLuint hge::shader::SunShader::getModelViewProjectionMatrixUniformLocation()
{
	return modelViewProjectionMatrixUniformLocation;
}
GLuint hge::shader::SunShader::getModelMatrixUniformLoaction()
{
	return modelMatrixUniformLocation;
}
GLuint hge::shader::SunShader::getVertexShaderProgram()
{
	return vertexShaderProgram;
}
GLuint hge::shader::SunShader::getGeometryShaderProgram()
{
	HGE_LOG_ERROR("Error this shader program does not have geometry shader.");
	HGE_TERMINATE;
}
GLuint hge::shader::SunShader::getFragmentShaderProgram()
{
	return fragmentShaderProgram;
}
GLuint hge::shader::SunShader::getShaderProgram()
{
	return shaderProgram;
}
GLuint hge::shader::SunShader::getTextureSamplerLocation()
{
	return textureSamplerLocation;
}
