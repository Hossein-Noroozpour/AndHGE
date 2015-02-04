#include "hge-file-stream.hpp"
#include "hge-configure.hpp"
hge::utility::FileStream::FileStream(const std::string &fileName)
{
	file.open(fileName, std::ios::binary | std::ios::in);
	if(!file.is_open())
	{
		HGE_LOG_ERROR("Can not open specified file.");
		HGE_TERMINATE;
	}
}
int hge::utility::FileStream::read(char *const &buffer, const long int &size)
{
	file.read(buffer, size);
	return file.gcount();
}
bool hge::utility::FileStream::isEnd()
{
	return file.eof();
}
