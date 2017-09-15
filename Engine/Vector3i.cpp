#include "Vector3i.h"

namespace Engine
{
#define PI 3.141592f

	void Vector3i::Assign(int x, int y, int z)
	{
		_xyz[0] = x;
		_xyz[1] = y;
		_xyz[2] = z;
	}

	Vector3i::Vector3i()
	{
		Assign(0.0, 0.0, 0.0);
	}

	Vector3i::Vector3i(int x, int y, int z)
	{
		Assign(x, y, z);
	}

	Vector3i::Vector3i(int xyz[])
	{
		Assign(xyz[0], xyz[1], xyz[2]);
	}

	const int* Vector3i::xyz() const
	{
		return _xyz;
	}

	Vector3f Vector3i::normalize() const
	{
		float mag = getMagnitude();
		if (mag < 0.001)
			return Vector3f(0.0f, 0.0f, 0.0f);
		else
			return Vector3f(static_cast<float>(_xyz[0]) / mag, static_cast<float>(_xyz[1]) / mag, static_cast<float>(_xyz[2]) / mag);
	}

	float Vector3i::getMagnitude()const
	{
		int x = _xyz[0] * _xyz[0];
		int y = _xyz[1] * _xyz[1];
		int z = _xyz[2] * _xyz[2];

		int sq = sqrt(static_cast<float>(x)+static_cast<float>(y)+static_cast<float>(z));

		return sq;
		//return int(sqrt((_xyz[0] * _xyz[0]) + (_xyz[1] * _xyz[1]) + (_xyz[2] * _xyz[2])));
	}
}