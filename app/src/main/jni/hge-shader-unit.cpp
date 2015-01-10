#include "hge-shader-unit.hpp"
#ifdef HGE_USE_OPENGL_43
const std::string hge::shader::ShaderUnit::shaderLanguageVersion("#version 430\n");
#elif defined(HGE_USE_OPENGL_42)
const std::string hge::shader::ShaderUnit::shaderLanguageVersion("#version 420\n");
#elif defined(HGE_USE_OPENGL_41)
const std::string hge::shader::ShaderUnit::shaderLanguageVersion("#version 410\n");
#elif defined(HGE_USE_OPENGL_40)
const std::string hge::shader::ShaderUnit::shaderLanguageVersion("#version 400\n");
#elif defined(HGE_USE_OPENGL_33)
const std::string hge::shader::ShaderUnit::shaderLanguageVersion("#version 330\n");
#elif defined(HGE_USE_OPENGL_ES_3)
const std::string hge::shader::ShaderUnit::shaderLanguageVersion("\n"); /// Not yet
#elif defined(HGE_USE_OPENGL_ES_2)
const std::string hge::shader::ShaderUnit::shaderLanguageVersion("\n"); /// Not yet
#endif
#if defined(HGE_USE_OPENGL_ES_2) || defined(HGE_USE_OPENGL_ES_3)
const std::string hge::shader::ShaderUnit::attributeIdentifier("attribute ");
const std::string hge::shader::ShaderUnit::stageInIdentifier("varying ");
const std::string hge::shader::ShaderUnit::stageOutIdentifier("varying ");
const std::string hge::shader::ShaderUnit::precisionDefinition("precision lowp sampler2D; precision lowp float;");
const std::string hge::shader::ShaderUnit::fragColor("gl_FragColor");
const std::string hge::shader::ShaderUnit::fragColorDefinition("");
#else
const std::string hge::shader::ShaderUnit::attributeIdentifier("in ");
const std::string hge::shader::ShaderUnit::stageInIdentifier("in ");
const std::string hge::shader::ShaderUnit::stageOutIdentifier("out ");
const std::string hge::shader::ShaderUnit::precisionDefinition("");
const std::string hge::shader::ShaderUnit::fragColor("fragColor");
const std::string hge::shader::ShaderUnit::fragColorDefinition("out vec4 fragColor;");
#endif
#ifdef HGE_DEBUG_MODE
const std::string hge::shader::ShaderUnit::vsUvOutVarName("outUV");
const std::string hge::shader::ShaderUnit::vsWorldPositionOutVarName("worldPosition");
const std::string hge::shader::ShaderUnit::lightIntensityVarName("lightIntensity");
const std::string hge::shader::ShaderUnit::modelViewProjectionMatrixUniformName("mvpMatrix");
const std::string hge::shader::ShaderUnit::modelMatrixUniformName("modelMatrix");
const std::string hge::shader::ShaderUnit::sunDirectionUniformName("sunD");
const std::string hge::shader::ShaderUnit::shaderEndline("\n");
const std::string hge::shader::ShaderUnit::shaderTabCharacter("    ");
const std::string hge::shader::ShaderUnit::vertexAttribute("vertex");
const std::string hge::shader::ShaderUnit::normalAttribute("normal");
const std::string hge::shader::ShaderUnit::zAttribute("z");
const std::string hge::shader::ShaderUnit::uvAttribute("uv");
const std::string hge::shader::ShaderUnit::tangentAttribute("tangent");
const std::string hge::shader::ShaderUnit::bitangentAttribute("bitangent");
const std::string hge::shader::ShaderUnit::vertexInName("vertexIn");
const std::string hge::shader::ShaderUnit::vertexOutName("vertexOut");
const std::string hge::shader::ShaderUnit::textureSampler("textureSampler");
const std::string hge::shader::ShaderUnit::normalVar("nrm");
const std::string hge::shader::ShaderUnit::tangentVar("tng");
const std::string hge::shader::ShaderUnit::bitangentVar("btng");
const std::string hge::shader::ShaderUnit::uvVar("uvv");
#else
const std::string hge::shader::ShaderUnit::vsUvOutVarName("ouv");
const std::string hge::shader::ShaderUnit::vsWorldPositionOutVarName("wp");
const std::string hge::shader::ShaderUnit::lightIntensityVarName("li");
const std::string hge::shader::ShaderUnit::modelViewProjectionMatrixUniformName("mvp");
const std::string hge::shader::ShaderUnit::modelMatrixUniformName("m");
const std::string hge::shader::ShaderUnit::sunDirectionUniformName("s");
const std::string hge::shader::ShaderUnit::shaderEndline("");
const std::string hge::shader::ShaderUnit::shaderTabCharacter("");
const std::string hge::shader::ShaderUnit::vertexAttribute("v");
const std::string hge::shader::ShaderUnit::normalAttribute("n");
const std::string hge::shader::ShaderUnit::zAttribute("z");
const std::string hge::shader::ShaderUnit::uvAttribute("uv");
const std::string hge::shader::ShaderUnit::tangentAttribute("t");
const std::string hge::shader::ShaderUnit::bitangentAttribute("bt");
const std::string hge::shader::ShaderUnit::vertexInName("vi");
const std::string hge::shader::ShaderUnit::vertexOutName("vo");
const std::string hge::shader::ShaderUnit::textureSampler("ts");
const std::string hge::shader::ShaderUnit::normalVar("nrm");
const std::string hge::shader::ShaderUnit::tangentVar("tng");
const std::string hge::shader::ShaderUnit::bitangentVar("btng");
const std::string hge::shader::ShaderUnit::uvVar("uvv");
#endif
