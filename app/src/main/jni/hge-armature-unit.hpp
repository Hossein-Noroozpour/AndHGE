#ifndef HGE_ARMATURE_UNIT_HPP
#define	HGE_ARMATURE_UNIT_HPP
#include "hge-data-object.hpp"
#include "hge-bone-unit.hpp"
#include "hge-mesh-unit.hpp"
#include "hge-animation-data-manager-unit.hpp"
namespace hge
{
	namespace animation
	{
		class ArmatureUnit : public core::DataObject
		{
		private:
			typedef std::uint16_t RootBoneCountType;
			typedef std::uint8_t MaxAffectingBoneType;
			MaxAffectingBoneType maxAffectingBone;
			std::string name;
			std::vector<animation::BoneUnit> rootBones;
			AnimationDataManagerUnit animationDataManager;
			render::MeshUnit skin;
		public:
			void setData(std::shared_ptr<utility::Stream> &stream, const bool &endianCompatible = true);
			void setDataId(const core::Protocol::Types::IdType &id);
			core::Protocol::Types::IdType getDataId();
		};
	}
}
#endif
