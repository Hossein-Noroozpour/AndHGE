#include "hge-animation-data-manager-unit.hpp"
void hge::animation::AnimationDataManagerUnit::setData(std::shared_ptr<utility::Stream> &stream, const bool &endianCompatible)
{
	action.setData(stream, endianCompatible);
}
void hge::animation::AnimationDataManagerUnit::setDataId(const core::Protocol::Types::IdType &id)
{
	(void) id;
}
hge::core::Protocol::Types::IdType hge::animation::AnimationDataManagerUnit::getDataId()
{
	return 0;
}
