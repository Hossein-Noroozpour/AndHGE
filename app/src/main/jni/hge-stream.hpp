#ifndef HGE_STREAM_HPP
#define HGE_STREAM_HPP
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
	}
}
#endif
