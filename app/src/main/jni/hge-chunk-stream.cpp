#include "hge-chunk-stream.hpp"
hge::utility::ChunkStream::ChunkStream(char * const &chunk, const int &size):
	chunk(chunk),
	size(size),
	offset(0)
{

}
hge::utility::ChunkStream::~ChunkStream()
{
	if(chunk != 0) delete [] chunk;
}

int hge::utility::ChunkStream::read(char * const &buffer, const long int &size)
{
	int endOff = offset + size;
	int readBytes = size;
	if(endOff > this->size)
	{
		endOff = this->size;
		readBytes = this->size - offset;
	}
	for(int i = 0; offset < endOff; offset++, i++)
	{
		buffer[i] = chunk[offset];
	}
	return readBytes;
}
bool hge::utility::ChunkStream::isEnd()
{
	return offset >= size;
}
