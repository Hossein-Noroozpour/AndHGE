#ifndef HGETEXTUREUNIT_HPP
#define	HGETEXTUREUNIT_HPP
#ifdef ANDROID
#ifdef HGE_USE_OPENGL_ES_3
#inlude <GLES/gl3.h>
#else
#include <GLES2/gl2.h>
#endif
#else
#include <GL/glew.h>
#include <GL/gl.h>
#endif
#include "hge-stream.hpp"
#include <memory>
#include <string>
#define HGE_TEXTURE_PRINT_INFO
namespace hge
{
	namespace texture
	{
		class TextureUnit
		{
		public:
			enum exceptions
			{
				FailedToOpenFile,
				FailedToRead,
				UnrecognizedFormat,
				InitializationError,
				InformationError,
				ParsingError
			};
			TextureUnit(std::shared_ptr<utility::Stream> &source);
			TextureUnit(const std::string &fileAddress);
			bool validate(std::shared_ptr<utility::Stream> &source);
			void bind(const GLenum &TextureUnit);
		private:
			void constructor(std::shared_ptr<utility::Stream> &source);
			GLenum textureTarget;
			GLuint textureObject;
		};
	}
}
#endif
