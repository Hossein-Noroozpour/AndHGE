#ifndef HGE_ANIMATION_CHANNEL_UNIT_HPP
#define	HGE_ANIMATION_CHANNEL_UNIT_HPP
#include "hge-data-object.hpp"
#include "hge-bone-unit.hpp"
#include "hge-channel-keyframe.hpp"
namespace hge
{
	namespace animation
	{
		class AnimationChannelUnit : public core::DataObject
		{
		private:
			typedef std::uint8_t ChannelType;
			typedef std::uint16_t KeyframesCountType;

			static const ChannelType X_LOCATION = 1;
			static const ChannelType Y_LOCATION = 2;
			static const ChannelType Z_LOCATION = 3;
			static const ChannelType W_QUATERNION_ROTATION = 4;
			static const ChannelType X_QUATERNION_ROTATION = 5;
			static const ChannelType Y_QUATERNION_ROTATION = 6;
			static const ChannelType Z_QUATERNION_ROTATION = 7;
			static const ChannelType X_SCALE = 8;
			static const ChannelType Y_SCALE = 9;
			static const ChannelType Z_SCALE = 10;

			ChannelType channelType;
			BoneUnit::BoneIndexType boneIndex;
			std::string boneName;
			KeyframesCountType keyframesCount;
			std::vector<ChannelKeyframe> keyframes;

		public:
			void setData(std::shared_ptr<utility::Stream> &stream, const bool &endianCompatible = true);
			void setDataId(const core::Protocol::Types::IdType &id);
			core::Protocol::Types::IdType getDataId();
		};
	}
}
#endif
