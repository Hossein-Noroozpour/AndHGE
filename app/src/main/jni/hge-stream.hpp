#ifndef HGE_STREAM_HPP
#define HGE_STREAM_HPP
#include <string>
#include <memory>
namespace hge
{
	namespace utility
	{
		class Stream
		{
		public:
			virtual int read(char *const &buffer, const long int &size) = 0;
			virtual bool isEnd() = 0;
		};
		void swapObject(char *const &data, const unsigned int &size);
		std::string readString(std::shared_ptr<Stream> &stream, const bool &endianCompatible = true);
		void readBinaryType(std::shared_ptr<Stream> &stream, char *const &data, const int &size, const bool &endianCompatible = true);
	}
}
#endif
