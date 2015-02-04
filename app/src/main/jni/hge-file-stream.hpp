#ifndef HGE_FILE_STREAM_HPP
#define HGE_FILE_STREAM_HPP
#include "hge-stream.hpp"
#include <fstream>
#include <string>
namespace hge
{
	namespace utility
	{
		class FileStream : public Stream
		{
		private:
			std::ifstream file;
		public:
			FileStream(const std::string &fileName);
			int read(char *const &buffer, const long int &size);
			bool isEnd();
		};
	}
}
#endif
