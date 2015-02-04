#ifndef HGE_ANIMATION_DATA_MANAGER_UNIT_HPP
#define	HGE_ANIMATION_DATA_MANAGER_UNIT_HPP
#include "hge-data-object.hpp"
#include "hge-animation-action-unit.hpp"
namespace hge
{
	namespace animation
	{
		class AnimationDataManagerUnit : core::DataObject
		{
		private:
			AnimationActionUnit action;
		public:
			void setData(std::shared_ptr<utility::Stream> &stream, const bool &endianCompatible = true);
			void setDataId(const core::Protocol::Types::IdType &id);
			core::Protocol::Types::IdType getDataId();
		};
	}
}
#endif
