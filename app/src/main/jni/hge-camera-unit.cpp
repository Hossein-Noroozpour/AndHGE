#include "hge-camera-unit.hpp"
namespace hge
{
	namespace math
	{
		CameraUnit::CameraUnit():
			cmrX(Vector3D<>(1.0f, 0.0f, 0.0f)),
			cmrY(Vector3D<>(0.0f, 1.0f, 0.0f)),
			cmrZ(Vector3D<>::cross(cmrX, cmrY)),
			cmrLoc(Vector3D<>(0.0f, 0.0f, 50.0f)),
			viewM(Matrix4D<>::lookAt(Vector3D<>(0.0f, 0.0f, 50.0f), Vector3D<>(0.0f, 0.0f, 0.0f), Vector3D<>(0.0f, 1.0f, 0.0f))),
			rotsclM(viewM * Matrix4D<>::translate(cmrLoc))
		{
		}
		CameraUnit::~CameraUnit()
		{
		}
		void CameraUnit::translate(const Vector3D<> &vec)
		{
			cmrLoc -= vec;
			viewM = Matrix4D<>::translate(-vec) * viewM;
		}
		/// WARNING: Unknown issue maybe exist
		void CameraUnit::move(const Vector3D<> &vec)
		{
			cmrLoc = vec;
			viewM = Matrix4D<>::translate(vec) * viewM;
		}
		void CameraUnit::rotateLocalX(const float &rad)
		{
			Matrix4D<> rot = cmrX.createRotationMatrix(rad);
			cmrY = rot * cmrY;
			cmrZ = rot * cmrZ;
			rotsclM = rot * rotsclM;
			viewM = Matrix4D<>::translate(-cmrLoc) * rotsclM;
		}
		// Not tested
		void CameraUnit::rotateLocalY(const float &rad)
		{
			Matrix4D<> rot = cmrY.createRotationMatrix(-rad);
			cmrX = rot * cmrX;
			cmrZ = rot * cmrZ;
			rotsclM = rot * rotsclM;
			viewM = rotsclM;
			viewM = viewM * Matrix4D<>::translate(-cmrLoc);
		}
		// not tested
		void CameraUnit::rotateLocalZ(const float &rad)
		{
			Matrix4D<> rot = cmrZ.createRotationMatrix(-rad);
			cmrX = rot * cmrX;
			cmrY = rot * cmrY;
			rotsclM = rot * rotsclM;
			viewM = rotsclM;
			viewM = viewM * Matrix4D<>::translate(-cmrLoc);
		}
		// not tested
		void CameraUnit::rotateLocal(const float &rad, const Vector3D<> &vec)
		{
			Matrix4D<> rot = vec.createRotationMatrix(-rad);
			cmrX = rot * cmrX;
			cmrY = rot * cmrY;
			cmrZ = rot * cmrZ;
			rotsclM = rot * rotsclM;
			viewM = rotsclM;
			viewM = viewM * Matrix4D<>::translate(-cmrLoc);
		}
		void CameraUnit::rotateGlobalX(const float &rad)
		{
			Matrix4D<> rot = Vector3D<>(1.0f, 0.0f, 0.0f).createRotationMatrix(-rad);
			cmrX = rot * cmrX;
			cmrY = rot * cmrY;
			cmrZ = rot * cmrZ;
			rotsclM = rot * rotsclM;
			viewM = rotsclM;
			viewM = viewM * Matrix4D<>::translate(-cmrLoc);
		}
		void CameraUnit::rotateGlobalY(const float &rad)
		{
			Matrix4D<> rot = Vector3D<>(0.0f, 1.0f, 0.0f).createRotationMatrix(-rad);
			cmrX = rot * cmrX;
			cmrY = rot * cmrY;
			cmrZ = rot * cmrZ;
			rotsclM = rot * rotsclM;
			viewM = rotsclM;
			viewM = viewM * Matrix4D<>::translate(-cmrLoc);
		}
		void CameraUnit::rotateGlobalZ(const float &rad)
		{
			Matrix4D<> rot = Vector3D<>(0.0f, 0.0f, 1.0f).createRotationMatrix(rad);
			cmrX = rot * cmrX;
			cmrY = rot * cmrY;
			cmrZ = rot * cmrZ;
			rotsclM =  rot * rotsclM;
			viewM = Matrix4D<>::translate(-cmrLoc) * rotsclM;
		}
		void CameraUnit::rotateTotal(const float &rad, const Vector3D<> &vec)
		{
			Matrix4D<> rot = vec.createRotationMatrix(-rad);
			cmrX    = rot * cmrX;
			cmrY    = rot * cmrY;
			cmrZ    = rot * cmrZ;
			cmrLoc  = rot * cmrLoc;
			rotsclM = rot * rotsclM;
			viewM   = rot * viewM;
		}
		void CameraUnit::scaleX(const float &x)
		{
			for(unsigned int i = 0; i < 3; i++)
			{
				rotsclM.mat[i] *= x;
				viewM.mat[i]   *= x;
			}
		}
		void CameraUnit::scaleY(const float &y)
		{
			for(unsigned int i = 4; i < 7; i++)
			{
				rotsclM.mat[i] *= y;
				viewM.mat[i]   *= y;
			}
		}
		void CameraUnit::scaleZ(const float &z)
		{
			for(unsigned int i = 8; i < 11; i++)
			{
				rotsclM.mat[i] *= z;
				viewM.mat[i]   *= z;
			}
		}
		void CameraUnit::scale(const float &x, const float &y, const float &z)
		{
			for(unsigned int i = 0; i < 3; i++)
			{
				rotsclM.mat[i] *= x;
				viewM.mat[i]   *= x;
			}
			for(unsigned int i = 4; i < 7; i++)
			{
				rotsclM.mat[i] *= y;
				viewM.mat[i]   *= y;
			}
			for(unsigned int i = 8; i < 11; i++)
			{
				rotsclM.mat[i] *= z;
				viewM.mat[i]   *= z;
			}
		}
		const Matrix4D<> &CameraUnit::getMatrix()
		{
			return viewM;
		}
		const Matrix4D<> &CameraUnit::getRotateScaleMatrix()
		{
			return rotsclM;
		}
		const Vector3D<> CameraUnit::getLocation()
		{
			return cmrLoc;
		}
		void CameraUnit::moveForward(const float &spd)
		{
			Vector3D<> vec = cmrZ * -spd;
			cmrLoc -= vec;
			viewM = Matrix4D<>::translate(vec) * viewM;
		}
		void CameraUnit::moveSideward(const float& spd)
		{
			Vector3D<> vec = cmrX * -spd;
			cmrLoc -= vec;
			viewM = Matrix4D<>::translate(vec) * viewM;
		}
	}
}
