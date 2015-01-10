#include "hge-perspective-unit.hpp"
hge::math::PerspectiveUnit::PerspectiveUnit():
	persM(Matrix4D<>::perspective(1.5f, 1.0f, 1.0f, 100000000000.0f))
{
}
hge::math::PerspectiveUnit::~PerspectiveUnit()
{
}
const hge::math::Matrix4D<> &hge::math::PerspectiveUnit::getMatrix()
{
	return persM;
}
