#ifndef HGE_MODEL_UNIT_HPP_
#define HGE_MODEL_UNIT_HPP_
#include "hge-math.hpp"
namespace hge
{
	namespace math
	{
		class ModelUnit
		{
		private:
			Vector3D<> localX;//object local directionX
			Vector3D<> localY;//object local directionY
			Vector3D<> localZ;//object local directionZ
			Vector3D<> location;//object location
			Matrix4D<> rotateScaleTranslateMatrix;//rotation scale translate matrix
			Matrix4D<> rotateScaleMatrix;//rotation scale matrix
			Matrix4D<> rotateMatrix;	//rotation matrix
		public:
			ModelUnit();
			void translate(const Vector3D<> &trn);
			void scale(const float &size);
			const Matrix4D<> &getConstRotateScaleTranslateMatrix();
			const Matrix4D<> &getConstRotateScaleMatrix();
			const Matrix4D<> &getConstRotateMatrix();
		};
	}
}
#endif
