#include "hge-animation-action-unit.hpp"
void hge::animation::AnimationActionUnit::setData(std::shared_ptr<utility::Stream> &stream, const bool &endianCompatible)
{
	utility::readBinaryType(stream, (char *)(&keyframeRange[0]), sizeof(keyframeRange[0]), endianCompatible);
	utility::readBinaryType(stream, (char *)(&keyframeRange[1]), sizeof(keyframeRange[1]), endianCompatible);
	utility::readBinaryType(stream, (char *)(&channelCount), sizeof(channelCount), endianCompatible);
#ifdef HGE_VERBOSE_TEST_MODE
	HGE_LOG_PRINT("Keyframes range : (%f, %f) number of channels: %d", keyframeRange[0], keyframeRange[1], channelCount);
#endif
	for(ChannelCountType i = 0; i < channelCount; i++)
	{
		AnimationChannelUnit channel;
		channel.setData(stream, endianCompatible);
		channels.push_back(channel);
	}
}
void hge::animation::AnimationActionUnit::setDataId(const core::Protocol::Types::IdType &id)
{
	(void) id;
}
hge::core::Protocol::Types::IdType hge::animation::AnimationActionUnit::getDataId()
{
	return 0;
}
