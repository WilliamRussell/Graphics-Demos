#pragma once 
#include "Vector3f.h"

namespace Engine
{
	class FrustumPlane
	{
	public:
		FrustumPlane() : _planeNormal(), _distance(0.f){}
		FrustumPlane(float x, float y, float z, float d);
		~FrustumPlane() {}
		void Assign(float x, float y, float z, float d);
		void NormalizePlane();
		bool TestPoint(const Vector3f& point) const;
	private:
		Vector3f _planeNormal;
		float _distance;
	};
}