#include "hge-channel-keyframe.hpp"
#include "hge-configure.hpp"
void hge::animation::ChannelKeyframe::setData(std::shared_ptr<utility::Stream> &stream, const bool &endianCompatible)
{
	stream->read((char *)(position), sizeof(position));
	stream->read((char *)(leftHandle), sizeof(leftHandle));
	stream->read((char *)(rightHandle), sizeof(rightHandle));
	if(!endianCompatible)
	{
		swapObject((char *)(&(position[0])), sizeof(position[0]));
		swapObject((char *)(&(position[1])), sizeof(position[1]));
		swapObject((char *)(&(leftHandle[0])), sizeof(leftHandle[0]));
		swapObject((char *)(&(leftHandle[1])), sizeof(leftHandle[1]));
		swapObject((char *)(&(rightHandle[0])), sizeof(rightHandle[0]));
		swapObject((char *)(&(rightHandle[1])), sizeof(rightHandle[1]));
	}
#ifdef HGE_VERBOSE_TEST_MODE
	HGE_LOG_PRINT("Left handle(%f, %f) Position(%f, %f) Right handle(%f, %f)",
				  leftHandle[0], leftHandle[1], position[0], position[1], rightHandle[0], rightHandle[1]);
#endif
}
void hge::animation::ChannelKeyframe::setDataId(const core::Protocol::Types::IdType &id)
{
	(void)id;
}
hge::core::Protocol::Types::IdType hge::animation::ChannelKeyframe::getDataId()
{
	return hge::core::Protocol::Types::IdType(0);
}
