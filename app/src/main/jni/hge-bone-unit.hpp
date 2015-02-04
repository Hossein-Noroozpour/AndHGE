#ifndef HGE_BONE_UNIT_HPP
#define HGE_BONE_UNIT_HPP
#include "hge-math.hpp"
#include "hge-data-object.hpp"
#include <string>
#include <vector>
namespace hge
{
	namespace animation
	{
		class BoneUnit : public core::DataObject
		{
		public:
			typedef std::uint16_t BoneIndexType;
		private:
			typedef std::uint8_t ChildrenCountType;
			std::string name;
			math::Vector3D<> head, tail;
			std::vector<BoneUnit> children;
			BoneIndexType index;
			ChildrenCountType childrenCount;
			BoneUnit *father;
		public:
			BoneUnit(BoneUnit *const &father = nullptr);
			void setData(std::shared_ptr<utility::Stream> &stream, const bool &endianCompatible = true);
			void setDataId(const core::Protocol::Types::IdType &id);
			core::Protocol::Types::IdType getDataId();
		};
	}

}
#endif
