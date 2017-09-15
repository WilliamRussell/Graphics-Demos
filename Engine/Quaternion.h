#pragma once
#include "Vector3f.h"
#include "Matrix4x4.h"
#include <cmath>

namespace Engine
{
	class Quaternion
	{
	public:
		Quaternion(void) {Assign(0.f,0.f,0.f,0.f);}
		Quaternion(float x, float y, float z, float w);
		Quaternion(const Vector3f& axis, float angle);
		~Quaternion(void) {}

		void Assign(float x, float y, float z, float w)
		{
			_xyzw[0] = x;
			_xyzw[1] = y;
			_xyzw[2] = z;
			_xyzw[3] = w;
		}

		void setX(float x){_xyzw[0] = x;}
		void setY(float y){_xyzw[1] = y;}
		void setZ(float z){_xyzw[2] = z;}
		void setW(float w){_xyzw[3] = w;}

		float getX() const {return _xyzw[0];}
		float getY() const {return _xyzw[1];}
		float getZ() const {return _xyzw[2];}
		float getW() const {return _xyzw[3];}

		void axisAngle(Vector3f& axis, float& angle) const;  // convert to an axis and an angle(in radians)

		Matrix4x4 Matrix() const;

		void identity()
		{		
			_xyzw[0] = 0;
			_xyzw[1] = 0;
			_xyzw[2] = 0;
			_xyzw[3] = 1;
		}

		Quaternion add(const Quaternion& rhs);
		Quaternion subtract(const Quaternion& rhs);
		Quaternion scaleBy(float scale);
		Quaternion multiply(const Quaternion& rhs);
		float length() const;		
		void normalize();

	private:
		float _xyzw[4];
	};
}