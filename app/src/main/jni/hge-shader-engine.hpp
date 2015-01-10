#ifndef HGESHADERENGINE_HPP
#define HGESHADERENGINE_HPP
#include <string>
#ifdef ANDROID
#include <GLES2/gl2.h>
#else
#include <GL/glew.h>
#include <GL/gl.h>
#endif
#include <memory>
namespace hge
{
	namespace render
	{
		class ShaderEngine
		{
		private:
		public:
			typedef struct
			{
				GLuint point;
				GLuint index;
				GLuint buffer;
				GLuint size;
			} hgeUniformBlock, *hgeUniformBlockPtr;
			static GLuint createProgram();
			static void run(const GLuint &shaderProgram);
			static GLuint addShaderToProgram(
				const std::string &shd,
				const GLenum &shaderType,
				const GLuint &shaderProgram);
			static GLuint getUniformLocation(
				const std::string &uname,
				const GLuint &shaderProgram);
			static void endProgram(const GLuint &shaderProgram);
			static void endObject(const GLuint &shaderObject);
			static std::shared_ptr<hgeUniformBlock> initUniformBlock(
				const std::string &uniformBlockName,
				const GLuint &shaderProgram);
#ifdef GL_ES_VERSION_3_0
			static void setUniformBlockData(
				const GLuint &offset,
				const GLuint &sizeOfData,
				const void * const &data,
				const hgeUniformBlockPtr &uniformBlock);
#endif
			static std::string readIntireFile(const std::string &fileName);
		};
	}
}
#endif
