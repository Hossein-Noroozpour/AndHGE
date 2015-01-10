#ifndef HGE_PERSPECTIVE_UNIT_HPP_
#define HGE_PERSPECTIVE_UNIT_HPP_
#include "hge-math.hpp"
namespace hge
{
	namespace math
	{
		class PerspectiveUnit
		{
		private:
			Matrix4D<> persM;
		public:
			PerspectiveUnit();
			~PerspectiveUnit();
			const Matrix4D<> &getMatrix();
		};
	}
}
#endif
