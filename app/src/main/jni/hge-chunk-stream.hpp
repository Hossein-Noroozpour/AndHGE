#ifndef HGE_CHUNK_STREAM_HPP
#define HGE_CHUNK_STREAM_HPP
#include "hge-stream.hpp"
namespace hge
{
	namespace utility
	{
		class ChunkStream : public Stream
		{
		public:
			ChunkStream(char *const& chunk, const int &size);
			~ChunkStream();
			int read(char * const &buffer, const long int &size);
			bool isEnd();
		private:
			char *chunk;
			int offset;
			int size;
		};
	}
}
#endif
