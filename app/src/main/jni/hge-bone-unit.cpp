#include "hge-bone-unit.hpp"
hge::animation::BoneUnit::BoneUnit(BoneUnit * const &father):
	father(father)
{}
void hge::animation::BoneUnit::setData(std::shared_ptr<utility::Stream> &stream, const bool &endianCompatible)
{
	name = utility::readString(stream, endianCompatible);
	head.setData(stream, endianCompatible);
	tail.setData(stream, endianCompatible);
	utility::readBinaryType(stream, (char *)(&index), sizeof(index), endianCompatible);
	utility::readBinaryType(stream, (char *)(&childrenCount), sizeof(childrenCount), endianCompatible);
#ifdef HGE_VERBOSE_TEST_MODE
	HGE_LOG_PRINT("Bone name: %s bone index: %d number of children: %d  head and tail is", name.c_str(), index, childrenCount);
	head.print();
	tail.print();
#endif
	for(ChildrenCountType i; i < childrenCount; i++)
	{
		BoneUnit bone(this);
		bone.setData(stream, endianCompatible);
		children.push_back(bone);
	}
}
void hge::animation::BoneUnit::setDataId(const core::Protocol::Types::IdType &id)
{
	(void) id;
}
hge::core::Protocol::Types::IdType hge::animation::BoneUnit::getDataId()
{
	return 0;
}
