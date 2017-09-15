#include "FrustumPlane.h"


namespace Engine
{
	FrustumPlane::FrustumPlane(float x, float y, float z, float d) : _planeNormal(x, y, z), _distance(d)
	{
	}

	void FrustumPlane::Assign(float x, float y, float z, float d)
	{
		_planeNormal.setX(x);
		_planeNormal.setY(y);
		_planeNormal.setZ(z);
		_distance = d;
	}

	void FrustumPlane::NormalizePlane()
	{
		float mag = _planeNormal.getMagnitude();
		_planeNormal.setX(_planeNormal.getX() / mag);
		_planeNormal.setY(_planeNormal.getY() / mag);
		_planeNormal.setZ(_planeNormal.getZ() / mag);
		_distance = _distance / mag;
	}

	bool FrustumPlane::TestPoint(const Vector3f& point) const
	{
		if (_planeNormal.dotProduct(point) + _distance > 0.f)
			return true;
		return false;
	}
}