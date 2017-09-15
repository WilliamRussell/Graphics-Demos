#pragma once
#include <cmath>
#include "Vector2f.h"
namespace Engine
{
	class Vector2i
	{
	private:
		int _xy[2];

	public:
		void Assign(int x, int y);

		Vector2i();

		Vector2i(int x, int y);

		Vector2i(int xy[]);

		const int* xy() const;

		void setX(int x){ _xy[0] = x; }
		void setY(int y){ _xy[1] = y; }

		Vector2i add(const Vector2i &rhs) const { return Vector2i(_xy[0] + rhs._xy[0], _xy[1] + rhs._xy[1]); }
		Vector2i subtract(const Vector2i &rhs) const { return Vector2i(_xy[0] - rhs._xy[0], _xy[1] - rhs._xy[1]); }
		Vector2i scaleBy(int value) const { return Vector2i(_xy[0] * value, _xy[1] * value); }		

		int getX() const { return _xy[0]; }
		int getY() const { return _xy[1]; }

		float getMagnitude()const;
		Vector2f Vector2i::normalize() const;
	};
}