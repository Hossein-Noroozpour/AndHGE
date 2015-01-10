#include "hge-model-unit.hpp"
hge::math::ModelUnit::ModelUnit():
	localX(math::Vector3D<>(1.0f, 0.0f, 0.0f)),
	localY(math::Vector3D<>(0.0f, 1.0f, 0.0f)),
	localZ(math::Vector3D<>(0.0f, 0.0f, 1.0f)),
	location(math::Vector3D<>(0.0f, 0.0f, 0.0f))
{
}

void hge::math::ModelUnit::translate (const math::Vector3D<> &trn)
{
	location += trn;
	rotateScaleTranslateMatrix = rotateScaleTranslateMatrix * Matrix4D<>::translate(trn);
}

void hge::math::ModelUnit::scale(const float &size)
{
	(void) size;
	/// TODO: It is not neccesary now
	//rotateScaleMatrix.scale(size);
	//rotateScaleTranslateMatrix.translate(location);
}

const hge::math::Matrix4D<> &hge::math::ModelUnit::getConstRotateScaleTranslateMatrix()
{
	return rotateScaleTranslateMatrix;
}

const hge::math::Matrix4D<> &hge::math::ModelUnit::getConstRotateScaleMatrix()
{
	return rotateScaleMatrix;
}

const hge::math::Matrix4D<> &hge::math::ModelUnit::getConstRotateMatrix()
{
	return rotateMatrix;
}
