#pragma once
#include <cmath>
#include "Vector3f.h"
namespace Engine
{
	class Vector3i
	{
	private:
		int _xyz[3];

	public:
		void Assign(int x, int y, int z);

		Vector3i();

		Vector3i(int x, int y, int z);

		Vector3i(int xyz[]);

		const int* xyz() const;

		void setX(int x){ _xyz[0] = x; }
		void setY(int y){ _xyz[1] = y; }
		void setZ(int z){ _xyz[2] = z; }

		Vector3i add(const Vector3i &rhs) const { return Vector3i(_xyz[0] + rhs._xyz[0], _xyz[1] + rhs._xyz[1], _xyz[2] + rhs._xyz[2]); }
		Vector3i subtract(const Vector3i &rhs) const { return Vector3i(_xyz[0] - rhs._xyz[0], _xyz[1] - rhs._xyz[1], _xyz[2] - rhs._xyz[2]); }
		Vector3i scaleBy(int value) const { return Vector3i(_xyz[0] * value, _xyz[1] * value, _xyz[2] * value); }	
		

		int getX() const { return _xyz[0]; }
		int getY() const { return _xyz[1]; }
		int getZ() const { return _xyz[2]; }

		float getMagnitude()const;
		Vector3f Vector3i::normalize() const;
	};
}