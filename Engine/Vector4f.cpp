//
//Vector4f.cpp
//Cube v1.2
//By William Russell, w.russell@live.co.uk
//
#include "Vector4f.h"

namespace Engine
{
	#define PI 3.141592f

	void Vector4f::Assign(float x, float y, float z, float w) 
	{
		_xyzw[0] = x;
		_xyzw[1] = y;
		_xyzw[2] = z;
		_xyzw[3] = w;
	}

	Vector4f::Vector4f() 
	{ 
		Assign(0.0, 0.0, 0.0, 1.0);
	}

	Vector4f::Vector4f(float x, float y, float z, float w) 
	{
		Assign(x, y, z, w);
	}

	Vector4f::Vector4f(float xyzw[]) 
	{
		Assign(xyzw[0], xyzw[1], xyzw[2], xyzw[3]);
	}

	Vector4f::Vector4f(const Vector3f& rhs)
	{
		Assign(rhs.getX(), rhs.getY(), rhs.getZ(), 1.0);
	}

	const float* Vector4f::xyzw() const 
	{
		return _xyzw;
	}
}