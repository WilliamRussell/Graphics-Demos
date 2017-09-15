#include "Vector2i.h"

namespace Engine
{
#define PI 3.141592f

	void Vector2i::Assign(int x, int y)
	{
		_xy[0] = x;
		_xy[1] = y;
	}

	Vector2i::Vector2i()
	{
		Assign(0, 0);
	}

	Vector2i::Vector2i(int x, int y)
	{
		Assign(x, y);
	}

	Vector2i::Vector2i(int xy[])
	{
		Assign(xy[0], xy[1]);
	}

	const int* Vector2i::xy() const
	{
		return _xy;
	}

	Vector2f Vector2i::normalize() const
	{
		float mag = getMagnitude();
		if (mag < 0.001)
			return Vector2f(0.0f, 0.0f);
		else
			return Vector2f(static_cast<float>(_xy[0]) / mag, static_cast<float>(_xy[1]) / mag);
	}

	float Vector2i::getMagnitude()const
	{
		int x = _xy[0] * _xy[0];
		int y = _xy[1] * _xy[1];

		float sq = sqrt(static_cast<float>(x) + static_cast<float>(y));

		return sq;
		//return float(sqrt((_xy[0] * _xy[0]) + (_xy[1] * _xy[1]) + (_xy[2] * _xy[2])));
	}
}