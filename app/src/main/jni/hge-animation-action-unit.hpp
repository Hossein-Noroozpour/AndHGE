#ifndef HGE_ANIMATION_ACTION_UNIT_HPP
#define	HGE_ANIMATION_ACTION_UNIT_HPP
#include "hge-data-object.hpp"
#include "hge-animation-channel-unit.hpp"
namespace hge
{
	namespace animation
	{
		class AnimationActionUnit : core::DataObject
		{
		private:
			typedef float KeyframeRangeType;
			typedef std::uint16_t ChannelCountType;

			KeyframeRangeType keyframeRange[2];
			ChannelCountType channelCount;
			std::vector<AnimationChannelUnit> channels;
		public:
			void setData(std::shared_ptr<utility::Stream> &stream, const bool &endianCompatible = true);
			void setDataId(const core::Protocol::Types::IdType &id);
			core::Protocol::Types::IdType getDataId();
		};
	}
}
#endif
