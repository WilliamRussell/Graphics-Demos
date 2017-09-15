#pragma once
#include <cmath>
class Vector3i;

namespace Engine
{
	class Vector3f
	{
	private:
		float _xyz[3];

	public:
		void Assign(float x, float y, float z);

		Vector3f();
		Vector3f(float x, float y, float z);
		Vector3f(float xyz[]);
		//Vector3f(const Vector3i& copy);

		const float* xyz() const;

		void setX(float x){_xyz[0] = x;}
		void setY(float y){_xyz[1] = y;}
		void setZ(float z){_xyz[2] = z;}	

		Vector3f add(const Vector3f &rhs) const {return Vector3f(_xyz[0] + rhs._xyz[0], _xyz[1] + rhs._xyz[1], _xyz[2] + rhs._xyz[2]);}
		Vector3f subtract(const Vector3f &rhs) const {return Vector3f(_xyz[0] - rhs._xyz[0], _xyz[1] - rhs._xyz[1], _xyz[2] - rhs._xyz[2]);}
		Vector3f scaleBy(float value) const {return Vector3f(_xyz[0] * value, _xyz[1] * value, _xyz[2] * value);}
		Vector3f crossProduct(const Vector3f &rhs) const;		

		Vector3f rotate(float rotate, float x, float y, float z) const;

		float dotProduct(const Vector3f &rhs) const { return _xyz[0] * rhs._xyz[0] + _xyz[1] * rhs._xyz[1] + _xyz[2] * rhs._xyz[2]; }

		float getX() const {return _xyz[0];}
		float getY() const {return _xyz[1];}
		float getZ() const {return _xyz[2];}		

		float getMagnitude()const;
		Vector3f Vector3f::normalize() const;

		Vector3f operator+(const Vector3f& rhs) const { return add(rhs); }
		Vector3f operator-(const Vector3f& rhs) const { return subtract(rhs); }		
	};
}