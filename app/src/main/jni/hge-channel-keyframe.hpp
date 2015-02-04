#ifndef HGE_CHANNEL_KEYFRAME_HPP
#define HGE_CHANNEL_KEYFRAME_HPP
#include "hge-data-object.hpp"
namespace hge
{
	namespace animation
	{
		class ChannelKeyframe : public core::DataObject
		{
		private:
			typedef float KeyframeElementType;
			KeyframeElementType position [2];
			KeyframeElementType leftHandle [2];
			KeyframeElementType rightHandle [2];
		public:
			void setData(std::shared_ptr<utility::Stream> &stream, const bool &endianCompatible = true);
			void setDataId(const core::Protocol::Types::IdType &id);
			core::Protocol::Types::IdType getDataId();
		};
	}
}
#endif
