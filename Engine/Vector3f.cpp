#include "Vector3f.h"
#include "Vector3i.h"

namespace Engine
{
	#define PI 3.141592f

	void Vector3f::Assign(float x, float y, float z) 
	{
		_xyz[0] = x;
		_xyz[1] = y;
		_xyz[2] = z;		
	}

	Vector3f::Vector3f() 
	{ 
		Assign(0.0, 0.0, 0.0);
	}

	Vector3f::Vector3f(float x, float y, float z) 
	{
		Assign(x, y, z);
	}

	Vector3f::Vector3f(float xyz[]) 
	{
		Assign(xyz[0], xyz[1], xyz[2]);
	}

	//Vector3f::Vector3f(const Vector3i& copy)
	//{
	//	Assign(static_cast<float>(copy.getX()), static_cast<float>(copy.getY()), static_cast<float>(copy.getZ()));
	//}

	const float* Vector3f::xyz() const 
	{
		return _xyz;
	}

	Vector3f Vector3f::crossProduct(const Vector3f& rhs) const
	{
		return Vector3f(this->getY() * rhs.getZ() - this->getZ() * rhs.getY(),
						this->getZ() * rhs.getX() - this->getX() * rhs.getZ(),
						this->getX() * rhs.getY() - this->getY() * rhs.getX());
	}
	

	Vector3f Vector3f::rotate(float rotate, float x, float y, float z) const
	{
		return Vector3f(_xyz[0]*(x*x+(1-x*x)*cos(rotate))+_xyz[1]*(x*y*(1-cos(rotate))-z*sin(rotate))+_xyz[2]*(x*z*(1-cos(rotate))+y*sin(rotate)),
						_xyz[0]*(x*y*(1-cos(rotate))+z*sin(rotate))+_xyz[1]*(y*y+(1-y*y)*cos(rotate))+_xyz[2]*(y*z*(1-cos(rotate))-x*sin(rotate)),
						_xyz[0]*(x*z*(1-cos(rotate))-y*sin(rotate))+_xyz[1]*(y*z*(1-cos(rotate))+x*sin(rotate))+_xyz[2]*(z*z+(1-z*z)*cos(rotate)));
	}	

	Vector3f Vector3f::normalize() const
	{
		float mag = getMagnitude();
		if (mag < 0.001)
			return Vector3f(0.0f,0.0f,0.0f);
		else
			return Vector3f(_xyz[0]/mag, _xyz[1]/mag, _xyz[2]/mag);
	}

	float Vector3f::getMagnitude()const
	{
		float x = _xyz[0] * _xyz[0];
		float y = _xyz[1] * _xyz[1];
		float z = _xyz[2] * _xyz[2];

		float sq = sqrt(x + y + z);

		return sq;
		//return float(sqrt((_xyz[0] * _xyz[0]) + (_xyz[1] * _xyz[1]) + (_xyz[2] * _xyz[2])));
	}
}