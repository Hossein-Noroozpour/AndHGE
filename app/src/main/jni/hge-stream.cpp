#include "hge-stream.hpp"
#include "hge-protocol.hpp"
void hge::utility::swapObject(char *const &data, const unsigned int &size)
{
	char tmp;
	for (int j = size / 2, i = j - 1; i >= 0; i--, j++)
	{
		tmp = data[i];
		data[i] = data[j];
		data[j] = tmp;
	}
}
std::string hge::utility::readString(std::shared_ptr<Stream> &stream, const bool &endianCompatible)
{
	core::Protocol::Types::StringLengthType len;
	stream->read((char *)(&len), sizeof(len));
	if(!endianCompatible)
	{
		swapObject((char *)(&len), sizeof(len));
	}
	char *str = new char[len + 1];
	stream->read(str, len);
	str[len] = 0;
	std::string s = std::string(str, len);
	delete [] str;
	return s;
}
void hge::utility::readBinaryType(std::shared_ptr<Stream> &stream, char * const &data, const int &size, const bool &endianCompatible)
{
	stream->read(data, size);
	if(!endianCompatible)
	{
		swapObject(data, size);
	}
}
