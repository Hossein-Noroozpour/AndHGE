#ifndef HGEDATAOBJECT_HPP
#define HGEDATAOBJECT_HPP
#include "hge-serializable.hpp"
namespace hge
{
	namespace core
	{
		class DataObject : public Serializable
		{
		public:
			virtual void setDataId(const Protocol::Types::IdType &id) = 0;
			virtual Protocol::Types::IdType getDataId() = 0;
		};
	}
}
#endif
