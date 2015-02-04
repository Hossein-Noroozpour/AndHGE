#include "hge-armature-unit.hpp"
void hge::animation::ArmatureUnit::setData(std::shared_ptr<utility::Stream> &stream, const bool &endianCompatible)
{
	name = utility::readString(stream, endianCompatible);
	RootBoneCountType rootBonesCount;
	utility::readBinaryType(stream, (char *)(&rootBonesCount), sizeof(RootBoneCountType), endianCompatible);
#ifdef HGE_VERBOSE_TEST_MODE
	HGE_LOG_PRINT("Armature name is: %s  and number of root bones: %d", name.c_str(), rootBonesCount);
#endif
	for(RootBoneCountType i = 0; i < rootBonesCount; i++)
	{
		BoneUnit bone;
		bone.setData(stream, endianCompatible);
		rootBones.push_back(bone);
	}
	animationDataManager.setData(stream, endianCompatible);
	utility::readBinaryType(stream, (char *)(&maxAffectingBone), sizeof(maxAffectingBone), endianCompatible);
#ifdef HGE_VERBOSE_TEST_MODE
	HGE_LOG_PRINT("Max affecting bone on a vertex: %d", maxAffectingBone);
#endif
	skin.setData(stream, endianCompatible);
}
void hge::animation::ArmatureUnit::setDataId(const core::Protocol::Types::IdType &id)
{
	(void) id;
}
hge::core::Protocol::Types::IdType hge::animation::ArmatureUnit::getDataId()
{
	return 0;
}
