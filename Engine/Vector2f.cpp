#include "Vector2f.h"

namespace Engine
{
	#define PI 3.141592f

	void Vector2f::Assign(float x, float y) 
	{
		_xy[0] = x;
		_xy[1] = y;	
	}

	Vector2f::Vector2f() 
	{ 
		Assign(0.0, 0.0);
	}

	Vector2f::Vector2f(float x, float y) 
	{
		Assign(x, y);
	}

	Vector2f::Vector2f(float xy[]) 
	{
		Assign(xy[0], xy[1]);
	}

	const float* Vector2f::xy() const 
	{
		return _xy;
	}	

	Vector2f Vector2f::normalize() const
	{
		float mag = getMagnitude();
		if (mag < 0.001)
			return Vector2f(0.0f,0.0f);
		else
			return Vector2f(_xy[0]/mag, _xy[1]/mag);
	}

	float Vector2f::getMagnitude()const
	{
		float x = _xy[0] * _xy[0];
		float y = _xy[1] * _xy[1];		

		float sq = sqrt(x + y);

		return sq;
		//return float(sqrt((_xy[0] * _xy[0]) + (_xy[1] * _xy[1]) + (_xy[2] * _xy[2])));
	}
}