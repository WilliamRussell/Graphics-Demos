#include "Matrix4x4.h"
#include <algorithm>

namespace Engine
{
	Matrix4x4::Matrix4x4()
	{
		std::memset(_elements, 0, 16 * sizeof(float)); 
	}

	Matrix4x4::Matrix4x4(float elements[])
	{		
		std::memcpy(_elements, elements, 16 * sizeof(float));
	}

	void Matrix4x4::LoadIdentity()
	{
		std::memset(_elements, 0, 16 * sizeof(float));
		_elements[0] = _elements[5] = _elements[10] = _elements[15] = 1.f;
	}

	Matrix4x4 Matrix4x4::Multiply(const Matrix4x4& rhs) const
	{
		float newMatrix[] = 
		{
			(_elements[ 0] * rhs._elements[ 0] + _elements[ 4] * rhs._elements[ 1] + _elements[ 8] * rhs._elements[ 2] + _elements[12] * rhs._elements[ 3]),
			(_elements[ 1] * rhs._elements[ 0] + _elements[ 5] * rhs._elements[ 1] + _elements[ 9] * rhs._elements[ 2] + _elements[13] * rhs._elements[ 3]),
			(_elements[ 2] * rhs._elements[ 0] + _elements[ 6] * rhs._elements[ 1] + _elements[10] * rhs._elements[ 2] + _elements[14] * rhs._elements[ 3]),
			(_elements[ 3] * rhs._elements[ 0] + _elements[ 7] * rhs._elements[ 1] + _elements[11] * rhs._elements[ 2] + _elements[15] * rhs._elements[ 3]),
			(_elements[ 0] * rhs._elements[ 4] + _elements[ 4] * rhs._elements[ 5] + _elements[ 8] * rhs._elements[ 6] + _elements[12] * rhs._elements[ 7]),
			(_elements[ 1] * rhs._elements[ 4] + _elements[ 5] * rhs._elements[ 5] + _elements[ 9] * rhs._elements[ 6] + _elements[13] * rhs._elements[ 7]),
			(_elements[ 2] * rhs._elements[ 4] + _elements[ 6] * rhs._elements[ 5] + _elements[10] * rhs._elements[ 6] + _elements[14] * rhs._elements[ 7]),
			(_elements[ 3] * rhs._elements[ 4] + _elements[ 7] * rhs._elements[ 5] + _elements[11] * rhs._elements[ 6] + _elements[15] * rhs._elements[ 7]),
			(_elements[ 0] * rhs._elements[ 8] + _elements[ 4] * rhs._elements[ 9] + _elements[ 8] * rhs._elements[10] + _elements[12] * rhs._elements[11]),
			(_elements[ 1] * rhs._elements[ 8] + _elements[ 5] * rhs._elements[ 9] + _elements[ 9] * rhs._elements[10] + _elements[13] * rhs._elements[11]),
			(_elements[ 2] * rhs._elements[ 8] + _elements[ 6] * rhs._elements[ 9] + _elements[10] * rhs._elements[10] + _elements[14] * rhs._elements[11]),
			(_elements[ 3] * rhs._elements[ 8] + _elements[ 7] * rhs._elements[ 9] + _elements[11] * rhs._elements[10] + _elements[15] * rhs._elements[11]),
			(_elements[ 0] * rhs._elements[12] + _elements[ 4] * rhs._elements[13] + _elements[ 8] * rhs._elements[14] + _elements[12] * rhs._elements[15]),
			(_elements[ 1] * rhs._elements[12] + _elements[ 5] * rhs._elements[13] + _elements[ 9] * rhs._elements[14] + _elements[13] * rhs._elements[15]),
			(_elements[ 2] * rhs._elements[12] + _elements[ 6] * rhs._elements[13] + _elements[10] * rhs._elements[14] + _elements[14] * rhs._elements[15]),
			(_elements[ 3] * rhs._elements[12] + _elements[ 7] * rhs._elements[13] + _elements[11] * rhs._elements[14] + _elements[15] * rhs._elements[15])
		};
		return Matrix4x4(newMatrix);
	}

	Vector4f Matrix4x4::Multiply(const Vector4f& rhs) const
	{
		return Vector4f(
			_elements[ 0] * rhs.getX() + _elements[ 4] * rhs.getY() + _elements[ 8] * rhs.getZ() +_elements[12] * rhs.getW(),
			_elements[ 1] * rhs.getX() + _elements[ 5] * rhs.getY() + _elements[ 9] * rhs.getZ() +_elements[13] * rhs.getW(),
			_elements[ 2] * rhs.getX() + _elements[ 6] * rhs.getY() + _elements[10] * rhs.getZ() +_elements[14] * rhs.getW(),
			_elements[ 3] * rhs.getX() + _elements[ 7] * rhs.getY() + _elements[11] * rhs.getZ() +_elements[15] * rhs.getW());
	}

	Matrix4x4 Matrix4x4::GetTranspose() const
	{
		float newMatrix[] = 
		{
			_elements[0], _elements[4], _elements[8], _elements[12],
			_elements[1], _elements[5], _elements[9], _elements[13],
			_elements[2], _elements[6], _elements[10], _elements[14],
			_elements[3], _elements[7], _elements[11], _elements[15]
		};
		return Matrix4x4(newMatrix);
	}

	Matrix4x4 Matrix4x4::GetInverse() const
	{
		float newMatrix[] =
		{
			_elements[0], _elements[4], _elements[ 8], 0.0f,
			_elements[1], _elements[5], _elements[ 9], 0.0f,
			_elements[2], _elements[6], _elements[10], 0.0f,
			_elements[0] * -_elements[12] + _elements[1] * -_elements[13] + _elements[2] * -_elements[14],
			_elements[4] * -_elements[12] + _elements[5] * -_elements[13] + _elements[6] * -_elements[14],
			_elements[8] * -_elements[12] + _elements[9] * -_elements[13] + _elements[10] * -_elements[14],
			1.0f
		};
		return Matrix4x4(newMatrix);
	}

}