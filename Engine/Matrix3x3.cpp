#include "Matrix3x3.h"
#include <algorithm>

namespace Engine
{
	Matrix3x3::Matrix3x3()
	{
		std::memset(_elements, 0.f, 9 * sizeof(float)); 
	}

	Matrix3x3::Matrix3x3(float elements[])
	{		
		std::memcpy(_elements, elements, 9 * sizeof(float));
	}

	void Matrix3x3::LoadIdentity()
	{
		std::memset(_elements, 0.f, 9 * sizeof(float));
		_elements[0] = _elements[4] = _elements[8] = 1.f;
	}

	Matrix3x3 Matrix3x3::Multiply(const Matrix3x3& rhs) const
	{
		float newMatrix[] = 
		{
			(_elements[0] * rhs._elements[0] + _elements[3] * rhs._elements[1] + _elements[6] * rhs._elements[2]),
			(_elements[1] * rhs._elements[0] + _elements[4] * rhs._elements[1] + _elements[7] * rhs._elements[2]),
			(_elements[2] * rhs._elements[0] + _elements[5] * rhs._elements[1] + _elements[8] * rhs._elements[2]),
			(_elements[0] * rhs._elements[3] + _elements[3] * rhs._elements[4] + _elements[6] * rhs._elements[5]),
			(_elements[1] * rhs._elements[3] + _elements[4] * rhs._elements[4] + _elements[7] * rhs._elements[5]),
			(_elements[2] * rhs._elements[3] + _elements[5] * rhs._elements[4] + _elements[8] * rhs._elements[5]),
			(_elements[0] * rhs._elements[6] + _elements[3] * rhs._elements[7] + _elements[6] * rhs._elements[8]),
			(_elements[1] * rhs._elements[6] + _elements[4] * rhs._elements[7] + _elements[7] * rhs._elements[8]),
			(_elements[2] * rhs._elements[6] + _elements[5] * rhs._elements[7] + _elements[8] * rhs._elements[8])
		};
		return Matrix3x3(newMatrix);
	}

	Vector3f Matrix3x3::Multiply(const Vector3f& rhs) const
	{
		return Vector3f(
			_elements[0] * rhs.getX() + _elements[3] * rhs.getY() + _elements[6] * rhs.getZ(),
			_elements[1] * rhs.getX() + _elements[4] * rhs.getY() + _elements[7] * rhs.getZ(),
			_elements[2] * rhs.getX() + _elements[5] * rhs.getY() + _elements[8] * rhs.getZ());
	}
}