#include "hge-configure.hpp"
#include "hge-terrain-sun-shader.hpp"
#include "hge-shader-engine.hpp"
#include "hge-main-window.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#ifdef ANDROID
#include <android/log.h>
#endif
#define HGE_u_sea 0
#define HGE_u_sea_str "0"
#define HGE_sure 1
#define HGE_sure_str "1"
#define HGE_grass1 2
#define HGE_grass1_str "2"
#define HGE_grass2 3
#define HGE_grass2_str "3"
#define HGE_soil 4
#define HGE_soil_str "4"
#define HGE_rock 5
#define HGE_rock_str "5"
#define HGE_snow 6
#define HGE_snow_str "6"
#define HGE_ice 7
#define HGE_ice_str "7"
#define HGE_1tab + shaderEndline + shaderTabCharacter +
#define HGE_2tab + shaderEndline + shaderTabCharacter + shaderTabCharacter +
#define HGE_3tab + shaderEndline + shaderTabCharacter + shaderTabCharacter + shaderTabCharacter +
#define HGE_4tab + shaderEndline + shaderTabCharacter + shaderTabCharacter + shaderTabCharacter + shaderTabCharacter +
#define HGE_5tab + shaderEndline + shaderTabCharacter + shaderTabCharacter + shaderTabCharacter + shaderTabCharacter + shaderTabCharacter +
#define HGE_6tab + shaderEndline + shaderTabCharacter + shaderTabCharacter + shaderTabCharacter + shaderTabCharacter + shaderTabCharacter + shaderTabCharacter + s
hge::shader::TerrainSunShader::TerrainSunShader():
	shaderProgram(render::ShaderEngine::createProgram())
{
	std::string pVS =
			shaderLanguageVersion + precisionDefinition + shaderEndline +
			attributeIdentifier + "vec3 " + vertexAttribute + ";" + shaderEndline +
			//All of the normals must be normalized.
			attributeIdentifier + "vec3 " + normalAttribute + ";" + shaderEndline +
			//All of the tangents must be normalized.
			//attributeIdentifier + "vec3 " + tangentAttribute + ";" + shaderEndline +
			//All of the bitangents must be normalized.
			//attributeIdentifier + "vec3 " + bitangentAttribute + ";" + shaderEndline +
#ifndef HGE_GEOMETRY_SHADER_SUPPORT
#define HGE_V_O_z zAttribute
#define HGE_V_O_li lightIntensityVarName
#define HGE_V_O_uv uvVar
#define HGE_V_O_nrm normalVar
//#define HGE_V_O_tng tangentVar
//#define HGE_V_O_btng bitangentVar
			stageOutIdentifier + "float " + zAttribute + ";" + shaderEndline +
			stageOutIdentifier + "float " + lightIntensityVarName + ";" + shaderEndline +
			stageOutIdentifier + "vec2 " + uvVar + ";" + shaderEndline +
			stageOutIdentifier + "vec3 " + normalVar + ";" + shaderEndline +
//			stageOutIdentifier + "vec3 " + tangentVar + ";" + shaderEndline +
//			stageOutIdentifier + "vec3 " + bitangentVar + ";" + shaderEndline +
#else
#define HGE_V_O_z vertexOutName + "." + zAttribute
#define HGE_V_O_li vertexOutName + "." + lightIntensityVarName
#define HGE_V_O_uv vertexOutName + "." + uvVar
#define HGE_V_O_nrm vertexOutName + "." + normalVar
//#define HGE_V_O_tng vertexOutName + "." + tangentVar
//#define HGE_V_O_btng vertexOutName + "." + bitangentVar
#define VSVERTEXDATA \
					"VertexData" + shaderEndline +\
					"{"\
					HGE_1tab "float " + zAttribute + ";"\
					HGE_1tab "float " + lightIntensityVarName + ";"\
					HGE_1tab "vec2 " + uvVar + ";"\
					HGE_1tab "vec3 " + normalVar + ";"+ shaderEndline +\
					"} "
			stageOutIdentifier + VSVERTEXDATA + vertexOutName + ";" + shaderEndline +
#endif
			"uniform mat4 " + modelViewProjectionMatrixUniformName + ";" + shaderEndline +
			"uniform vec3 "  + sunDirectionUniformName + ";" + shaderEndline +
#define HGE_START_SHDR_FUN "void main()" + shaderEndline + "{"
			HGE_START_SHDR_FUN
			HGE_1tab "float nds = dot(" + sunDirectionUniformName + ", -" + normalAttribute + ");"
			HGE_1tab "if(nds < 0.2) " + HGE_V_O_li + " = 0.2;"
			HGE_1tab "else " + HGE_V_O_li + " = nds;"
			//HGE_1tab HGE_V_O_li + " = max(dot(" + sunDirectionUniformName + ", " + normalAttribute + "), 0.3);"
			HGE_1tab HGE_V_O_uv + " = vec2(" + vertexAttribute + ".x + " + vertexAttribute + ".z, " + vertexAttribute + ".y + " + vertexAttribute + ".z);"
			HGE_1tab HGE_V_O_nrm + " = " + normalAttribute + ";"
			HGE_1tab HGE_V_O_z + " = " + vertexAttribute + ".z;"
//			HGE_1tab HGE_V_O_tng + " = " + tangentAttribute + ";"
//			HGE_1tab HGE_V_O_btng + " = " + bitangentAttribute + ";"
			HGE_1tab "gl_Position = " + modelViewProjectionMatrixUniformName + " * vec4(" + vertexAttribute + ", 1.0);" + shaderEndline +
			"}";
#undef HGE_V_O_z
#undef HGE_V_O_li
#undef HGE_V_O_uv
#undef HGE_V_O_nrm
#undef HGE_V_O_tng
#undef HGE_V_O_btng
#ifdef HGE_TEST_MODE
	HGE_LOG_PRINT("vertext shader is: %s", pVS.c_str());
#endif
#ifdef HGE_GEOMETRY_SHADER_SUPPORT
	std::string pGS =
			shaderLanguageVersion +
			"layout (triangles) in;" + shaderEndline +
			"layout (triangle_strip, max_vertices=3) out;" + shaderEndline +
			stageInIdentifier + VSVERTEXDATA + vertexInName + "[];" + shaderEndline +
#define GSVERTEXDATA \
			"GeometryData" + shaderEndline +\
			"{"\
			HGE_1tab "float " + zAttribute + ";"\
			HGE_1tab "float " + lightIntensityVarName + ";"\
			HGE_1tab "vec2 " + uvVar + ";"\
			HGE_1tab "vec3 " + normalVar + ";"+ shaderEndline +\
			"} "
			stageOutIdentifier + GSVERTEXDATA + vertexOutName + ";" + shaderEndline +
			HGE_START_SHDR_FUN
			HGE_1tab "for(int i = 0; i < gl_in.length(); i++)"
			HGE_1tab "{"
				HGE_2tab "gl_Position = gl_in[i].gl_Position;"
				HGE_2tab vertexOutName + "." + uvVar + " = " + vertexInName + "[i]." + uvVar + ";"
				HGE_2tab vertexOutName + "." + normalVar + " = " + vertexInName + "[i]." + normalVar + ";"
				HGE_2tab vertexOutName + "." + zAttribute + " = " + vertexInName + "[i]." + zAttribute + ";"
				HGE_2tab vertexOutName + "." + lightIntensityVarName + " = " + vertexInName + "[i]." + lightIntensityVarName + ";"
//				HGE_2tab vertexOutName + "." + tangentVar + " = " + vertexInName + "[i]." + tangentVar + ";"
//				HGE_2tab vertexOutName + "." + bitangentVar + " = " + vertexInName + "[i]." + bitangentVar + ";"
				HGE_2tab "EmitVertex();"
			HGE_1tab "}"
			HGE_1tab "EndPrimitive();" + shaderEndline +
			"}";

#ifdef HGE_TEST_MODE
	HGE_LOG_PRINT("geometry shader is:%s\n", pGS.c_str());
#endif
#endif
	std::string pFS =
		shaderLanguageVersion + precisionDefinition + shaderEndline +
#ifdef HGE_GEOMETRY_SHADER_SUPPORT
		stageInIdentifier + GSVERTEXDATA + vertexInName + ";" + shaderEndline +
#define HGE_V_I vertexInName + "." +
#define HGE_V_I_z   HGE_V_I zAttribute +
#define HGE_V_I_uv  HGE_V_I uvVar +
#define HGE_V_I_nrm HGE_V_I normalVar +
//#define HGE_V_I_tng HGE_V_I tangentVar +
//#define HGE_V_I_btg HGE_V_I bitangentVar +
#define HGE_V_I_li HGE_V_I lightIntensityVarName +
#else
		stageInIdentifier + "float " + zAttribute + ";" + shaderEndline +
		stageInIdentifier + "float " + lightIntensityVarName + ";" + shaderEndline +
		stageInIdentifier + "vec2 " + uvVar + ";" + shaderEndline +
		stageInIdentifier + "vec3 " + normalVar + ";" + shaderEndline +
//		stageInIdentifier + "vec3 " + tangentVar + ";" + shaderEndline +
//		stageInIdentifier + "vec3 " + bitangentVar + ";" + shaderEndline +
#define HGE_V_I_z zAttribute +
#define HGE_V_I_li lightIntensityVarName +
#define HGE_V_I_uv uvVar +
#define HGE_V_I_nrm normalVar +
#define HGE_V_I_tng tangentVar +
#define HGE_V_I_btg bitangentVar +
#endif
#ifdef HGE_USE_OPENGL_ES_2
		"float limits [7];" + shaderEndline +
#else
		"const float limits [] = " + shaderEndline +
		"{"
		HGE_1tab HGE_TERRAIN_HEIGHT_LIMIT_0 ","
		HGE_1tab HGE_TERRAIN_HEIGHT_LIMIT_1 ","
		HGE_1tab HGE_TERRAIN_HEIGHT_LIMIT_2 ","
		HGE_1tab HGE_TERRAIN_HEIGHT_LIMIT_3 ","
		HGE_1tab HGE_TERRAIN_HEIGHT_LIMIT_4 ","
		HGE_1tab HGE_TERRAIN_HEIGHT_LIMIT_5 ","
		HGE_1tab HGE_TERRAIN_HEIGHT_LIMIT_6 + shaderEndline +
		"};" + shaderEndline +
#endif
		fragColorDefinition + shaderEndline +
		"vec4 tmpColor2 = vec4(1.0);" + shaderEndline +
		"uniform sampler2D " + textureSampler + "[" HGE_TERRAIN_TEXTURE_COUNT_STRING "];" + shaderEndline +
		"uniform vec3 " + sunDirectionUniformName + ";" + shaderEndline +
		HGE_START_SHDR_FUN
#ifdef HGE_USE_OPENGL_ES_2
		HGE_1tab "limits[0] = " HGE_TERRAIN_HEIGHT_LIMIT_0 ";"
		HGE_1tab "limits[1] = " HGE_TERRAIN_HEIGHT_LIMIT_1 ";"
		HGE_1tab "limits[2] = " HGE_TERRAIN_HEIGHT_LIMIT_2 ";"
		HGE_1tab "limits[3] = " HGE_TERRAIN_HEIGHT_LIMIT_3 ";"
		HGE_1tab "limits[4] = " HGE_TERRAIN_HEIGHT_LIMIT_4 ";"
		HGE_1tab "limits[5] = " HGE_TERRAIN_HEIGHT_LIMIT_5 ";"
		HGE_1tab "limits[6] = " HGE_TERRAIN_HEIGHT_LIMIT_6 ";"
#endif
		HGE_1tab "if(" + HGE_V_I_nrm + ".z > " HGE_TERRAIN_SLOP_LIMIT_0 ")"
		HGE_1tab "{"
			HGE_2tab "tmpColor2 = texture2D(" + textureSampler + "[" HGE_rock_str "], " + HGE_V_I_uv ");"
		HGE_1tab "}"
		HGE_1tab "else"
		HGE_1tab "{"
			HGE_2tab "vec4 tmpcolor;"
			HGE_2tab "if(" + HGE_V_I_z " >= " HGE_TERRAIN_HEIGHT_LIMIT_6 " + " HGE_TERRAIN_HEIGHT_FADE_LIMIT ")"
			HGE_2tab "{"
				HGE_3tab "tmpcolor = texture2D(" + textureSampler + "[" HGE_ice_str "], " + HGE_V_I_uv ");"
			HGE_2tab "}"
			HGE_2tab "else"
			HGE_2tab "{"
				HGE_3tab "for(int i = 0; i < " HGE_TERRAIN_TEXTURE_COUNT_STRING " - 1; i++)"
				HGE_3tab "{"
					HGE_4tab "if(" + HGE_V_I_z " < limits[i])"
					HGE_4tab "{"
						HGE_5tab "tmpcolor = texture2D(" + textureSampler + "[i], " + HGE_V_I_uv ");"
						HGE_5tab "break;"
					HGE_4tab "}"
					HGE_4tab "if(" + HGE_V_I_z " < limits[i] + " HGE_TERRAIN_HEIGHT_FADE_LIMIT ")"
					HGE_4tab "{"
						HGE_5tab "float r = (" + HGE_V_I_z " - limits[i]) / " HGE_TERRAIN_HEIGHT_FADE_LIMIT ";"
						HGE_5tab "vec4 c1 = texture2D(" + textureSampler + "[i], " + HGE_V_I_uv ");"
						HGE_5tab "vec4 c2 = texture2D(" + textureSampler + "[i+1], " + HGE_V_I_uv ");"
						HGE_5tab "tmpcolor = mix(c1, c2, r);"
						HGE_5tab "break;"
					HGE_4tab "}"
				HGE_3tab "}"
			HGE_2tab "}"
			HGE_2tab "if(" + HGE_V_I_nrm + ".z > " HGE_TERRAIN_SLOP_LIMIT_0 " + " HGE_TERRAIN_SLOP_FADE_LIMIT ")"
			HGE_2tab "{"
				HGE_3tab "float r = (" + HGE_V_I_nrm + ".z  - " HGE_TERRAIN_SLOP_LIMIT_0 ") / " HGE_TERRAIN_SLOP_FADE_LIMIT ";"
				HGE_3tab "vec4 c = texture2D(" + textureSampler + "[" HGE_rock_str "], " + HGE_V_I_uv ");"
				HGE_3tab "tmpColor2 = mix(c, tmpcolor, r);"
			HGE_2tab "}"
			HGE_2tab "else"
			HGE_2tab "{"
				HGE_3tab "tmpColor2 = tmpcolor;"
			HGE_2tab "}"
		HGE_1tab "}"
		HGE_1tab "if(tmpColor2 == vec4(1.0)) tmpColor2 = texture2D(" + textureSampler + "[" HGE_rock_str "], " + HGE_V_I_uv ");"
		//HGE_1tab fragColor + " = max(" + HGE_V_I_li " + (dot(" + HGE_V_I_tng + "," + HGE_V_I_btg + ") / 100), 0.99) * tmpColor2;" + shaderEndline +
		HGE_1tab fragColor + " = " + HGE_V_I_li " * tmpColor2;" + shaderEndline +
		"}";

#ifdef HGE_TEST_MODE
	HGE_LOG_PRINT("fragment shader is:\n %s", pFS.c_str());
#endif
#undef HGE_V_I_z
#undef HGE_V_I_uv
#undef HGE_V_I_nrm
#undef HGE_V_I_tng
#undef HGE_V_I_btg
#undef HGE_V_I
#undef HGE_START_SHDR_FUN
	vertexShaderProgram = render::ShaderEngine::addShaderToProgram(pVS, GL_VERTEX_SHADER, shaderProgram);
#ifdef HGE_TEST_MODE
	HGE_LOG_PRINT("Vertext shader compiled.");
#endif
#ifdef HGE_GEOMETRY_SHADER_SUPPORT
	geometryShaderProgram = render::ShaderEngine::addShaderToProgram(pGS, GL_GEOMETRY_SHADER, shaderProgram);
#ifdef HGE_TEST_MODE
	HGE_LOG_PRINT("Geometry shader compiled.");
#endif
#endif
	fragmentShaderProgram = render::ShaderEngine::addShaderToProgram(pFS, GL_FRAGMENT_SHADER, shaderProgram);
#ifdef HGE_TEST_MODE
	HGE_LOG_PRINT("Fragment shader compiled.");
#endif
	hge::render::ShaderEngine::run(shaderProgram);
#ifdef HGE_TEST_MODE
	HGE_LOG_PRINT("shader run.");
#endif
	vrtxAttInd = glGetAttribLocation(shaderProgram, vertexAttribute.c_str());
#ifdef HGE_DEBUG_MODE
	if(-1 == vrtxAttInd) ui::MainWindow::printGraphicAPIErrorAndTerminate();
#endif
	nrmAttInd = glGetAttribLocation(shaderProgram, normalAttribute.c_str());
#ifdef HGE_DEBUG_MODE
	if(-1 == nrmAttInd) ui::MainWindow::printGraphicAPIErrorAndTerminate();
#endif
	tngAttInd = glGetAttribLocation(shaderProgram, tangentAttribute.c_str());
#ifdef HGE_DEBUG_MODE
	if(-1 == tngAttInd)ui::MainWindow::printGraphicAPIErrorAndTerminate();
#endif
	btngAttInd = glGetAttribLocation(shaderProgram, bitangentAttribute.c_str());
#ifdef HGE_DEBUG_MODE
	if(-1 == btngAttInd)ui::MainWindow::printGraphicAPIErrorAndTerminate();
#endif
	mvpmul = render::ShaderEngine::getUniformLocation(modelViewProjectionMatrixUniformName, shaderProgram);
#ifdef HGE_DEBUG_MODE
	assert(mvpmul != 0xFFFFFFFF);
#endif
	glUniformMatrix4fv(mvpmul, 1, GL_FALSE, math::Matrix4D<>(1.0f).mat);
	sldul = render::ShaderEngine::getUniformLocation(sunDirectionUniformName, shaderProgram);
#ifdef HGE_DEBUG_MODE
	assert(sldul != 0xFFFFFFFF);
#endif
	glUniform3fv(sldul, 1, math::Vector3D<>(1.0f).vec);
	/// \todo
//	cprtmul = render::ShaderEngine::getUniformLocation(std::string("cprtm"), shaderProgram);
//#ifdef HGE_DEBUG_MODE
//	assert(cprtmul != 0xFFFFFFFF);
//#endif
//	glUniform3fv(cprtmul, 1, math::Vector3D<>(1.0f).vec);
//	lodnul = render::ShaderEngine::getUniformLocation(std::string("lodn"), shaderProgram);
//#ifdef HGE_DEBUG_MODE
//	assert(lodnul != 0xFFFFFFFF);
//#endif
//	glUniform1i(lodnul, 0);
	for(GLuint i = 0; i < HGE_TERRAIN_TEXTURE_COUNT; i++)
	{
		tsl[i] = render::ShaderEngine::getUniformLocation(textureSampler + "[" + std::to_string(i) + "]", shaderProgram);
#ifdef HGE_DEBUG_MODE
		assert(tsl[i] != 0xFFFFFFFF);
#endif
		glUniform1i(tsl[i], i);
	}
}
hge::shader::TerrainSunShader::~TerrainSunShader()
{
	hge::render::ShaderEngine::endObject(vertexShaderProgram);
	hge::render::ShaderEngine::endObject(geometryShaderProgram);
	hge::render::ShaderEngine::endObject(fragmentShaderProgram);
	hge::render::ShaderEngine::endProgram(shaderProgram);
}
void hge::shader::TerrainSunShader::setModelMatrix(const math::Matrix4D<> &modelMatrix)
{
	glUniformMatrix4fv(mmul, 1, GL_FALSE, modelMatrix.mat);
}
void hge::shader::TerrainSunShader::setModelViewProjectionMatrix(const math::Matrix4D<> &modelViewProjectionMatrix)
{
	glUniformMatrix4fv(mvpmul, 1, GL_FALSE, modelViewProjectionMatrix.mat);
}
void hge::shader::TerrainSunShader::setCameraPositionRelativeToModel(const math::Vector3D<>& p)
{
	glUniform3fv(cprtmul, 1, p.vec);
}
void hge::shader::TerrainSunShader::setLODNumber(const GLuint& lodNumber)
{
	//glUniform1i(lodnul, lodNumber);
}
void hge::shader::TerrainSunShader::use()
{
	glUseProgram(shaderProgram);
	glEnableVertexAttribArray(vrtxAttInd);
	glEnableVertexAttribArray(nrmAttInd);
#ifdef HGE_DEBUG_MODE
	if(tngAttInd != -1)
#endif
	glEnableVertexAttribArray(tngAttInd);
#ifdef HGE_DEBUG_MODE
	if(btngAttInd != -1)
#endif
	glEnableVertexAttribArray(btngAttInd);
	glVertexAttribPointer(vrtxAttInd, 3, GL_FLOAT, GL_FALSE, HGE_TERRAIN_COMPONENT_COUNT * sizeof(GLfloat), (void*) 0);
	glVertexAttribPointer(nrmAttInd, 3, GL_FLOAT, GL_FALSE, HGE_TERRAIN_COMPONENT_COUNT * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
#ifdef HGE_DEBUG_MODE
	if(tngAttInd != -1)
#endif
	glVertexAttribPointer(tngAttInd, 3, GL_FLOAT, GL_FALSE, HGE_TERRAIN_COMPONENT_COUNT * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
#ifdef HGE_DEBUG_MODE
	if(tngAttInd != -1)
#endif
	glVertexAttribPointer(btngAttInd, 3, GL_FLOAT, GL_FALSE, HGE_TERRAIN_COMPONENT_COUNT * sizeof(GLfloat), (void*)(9 * sizeof(GLfloat)));
}
GLuint hge::shader::TerrainSunShader::getModelViewProjectionMatrixUniformLocation()
{
	return mvpmul;
}
GLuint hge::shader::TerrainSunShader::getModelMatrixUniformLoaction()
{
	return mmul;
}
GLuint hge::shader::TerrainSunShader::getVertexShaderProgram()
{
	return vertexShaderProgram;
}
GLuint hge::shader::TerrainSunShader::getGeometryShaderProgram()
{
	return geometryShaderProgram;
}
GLuint hge::shader::TerrainSunShader::getFragmentShaderProgram()
{
	return fragmentShaderProgram;
}
GLuint hge::shader::TerrainSunShader::getShaderProgram()
{
	return shaderProgram;
}
GLuint* hge::shader::TerrainSunShader::getTextureSamplerLocations()
{
	return tsl;
}
std::string hge::shader::TerrainSunShader::readShaderFile(const std::string &fileName)
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
	HGE_TERMINATE;
}
