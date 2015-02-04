#include "hge-animation-channel-unit.hpp"
void hge::animation::AnimationChannelUnit::setData(std::shared_ptr<utility::Stream> &stream, const bool &endianCompatible)
{
	utility::readBinaryType(stream, (char *)(&channelType), sizeof(channelType), endianCompatible);
	utility::readBinaryType(stream, (char *)(&boneIndex), sizeof(boneIndex), endianCompatible);
	boneName = utility::readString(stream, endianCompatible);
	utility::readBinaryType(stream, (char *)(&keyframesCount), sizeof(keyframesCount), endianCompatible);
#ifdef HGE_VERBOSE_TEST_MODE
	HGE_LOG_PRINT("Channel type: %d, Bone index: %d, Bone name: %s, Keyframes count: %d", channelType, boneIndex, boneName.c_str(), keyframesCount);
#endif
	for(KeyframesCountType i = 0; i < keyframesCount; i++)
	{
		ChannelKeyframe keyframe;
		keyframe.setData(stream, endianCompatible);
		keyframes.push_back(keyframe);
	}

}
void hge::animation::AnimationChannelUnit::setDataId(const core::Protocol::Types::IdType &id)
{
	(void) id;
}
hge::core::Protocol::Types::IdType hge::animation::AnimationChannelUnit::getDataId()
{
	return 0;
}
