#pragma once
#include <cmath>
namespace Engine
{
	class Vector2f
	{
	private:
		float _xy[2];

	public:
		void Assign(float x, float y);

		Vector2f();

		Vector2f(float x, float y);

		Vector2f(float xy[]);

		const float* xy() const;

		void setX(float x){_xy[0] = x;}
		void setY(float y){_xy[1] = y;}		

		Vector2f add(const Vector2f &rhs) const {return Vector2f(_xy[0] + rhs._xy[0], _xy[1] + rhs._xy[1]);}
		Vector2f subtract(const Vector2f &rhs) const {return Vector2f(_xy[0] - rhs._xy[0], _xy[1] - rhs._xy[1]);}
		Vector2f scaleBy(float value) const {return Vector2f(_xy[0] * value, _xy[1] * value);}		

		Vector2f rotate(float rotate, float x, float y) const;

		float getX() const {return _xy[0];}
		float getY() const {return _xy[1];}				

		float getMagnitude()const;
		Vector2f Vector2f::normalize() const;

		Vector2f operator+(const Vector2f& rhs) const { return add(rhs); }
		Vector2f operator-(const Vector2f& rhs) const { return subtract(rhs); }
	};
}