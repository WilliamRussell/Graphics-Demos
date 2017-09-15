#pragma once
#include "Vector3f.h"
#include <cmath>
namespace Engine
{
	class Vector4f
	{
	private:
		float _xyzw[4];

	public:
		void Assign(float x, float y, float z, float w);

		Vector4f();

		Vector4f(const Vector3f& rhs);

		Vector4f(float x, float y, float z, float w);

		Vector4f(float xyzw[]);

		const float* xyzw() const;

		void setX(float x){_xyzw[0] = x;};
		void setY(float y){_xyzw[1] = y;};
		void setZ(float z){_xyzw[2] = z;};
		void setW(float w){_xyzw[3] = w;};

		Vector4f add(const Vector4f &rhs){return Vector4f(_xyzw[0] + rhs._xyzw[0], _xyzw[1] + rhs._xyzw[1], _xyzw[2] + rhs._xyzw[2], _xyzw[3] + rhs._xyzw[3]);};
		Vector4f subtract(const Vector4f &rhs){return Vector4f(_xyzw[0] - rhs._xyzw[0], _xyzw[1] - rhs._xyzw[1], _xyzw[2] - rhs._xyzw[2], _xyzw[3] - rhs._xyzw[3]);};
		Vector4f scaleBy(float value){return Vector4f(_xyzw[0] * value, _xyzw[1] * value, _xyzw[2] * value, _xyzw[3] * value);};		

		float getX() const {return _xyzw[0];};
		float getY() const {return _xyzw[1];};
		float getZ() const {return _xyzw[2];};
		float getW() const {return _xyzw[3];};

		float getMagnitude()const {return float(sqrt((_xyzw[0] * _xyzw[0]) + (_xyzw[1] * _xyzw[1]) + (_xyzw[2] * _xyzw[2])));};
	};
}