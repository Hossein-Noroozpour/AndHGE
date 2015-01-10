#ifndef HGE_CORE_SERIALIZABLE_HPP
#define HGE_CORE_SERIALIZABLE_HPP
#include "hge-protocol.hpp"
#include "hge-stream.hpp"
#include <memory>
namespace hge
{
	namespace core
	{
		class Serializable
		{
		public:
			enum exceptions
			{
				IncompatibleDataSize
			};
			virtual void setData(std::shared_ptr<utility::Stream> &stream, const bool &endianCompatible = true) = 0;
			static void swapObject(char *const &data, const unsigned int &size);
		private:
		};
	}
}
#endif
