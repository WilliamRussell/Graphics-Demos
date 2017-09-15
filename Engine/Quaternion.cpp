#include "Quaternion.h"

namespace Engine
{
	Quaternion::Quaternion(float x, float y, float z, float w)
	{
		this->Assign(x, y, z, w);
	}

	Quaternion::Quaternion(const Vector3f &axis, float angle)
	{
		const float a = angle * 0.5f;
		const float s = (float)sin(a);
		const float c = (float)cos(a);
	
		_xyzw[0] = axis.getX() * s;
		_xyzw[1] = axis.getY() * s;
		_xyzw[2] = axis.getZ() * s;
		_xyzw[3] = c;
	}

	void Quaternion::axisAngle(Vector3f& axis, float& angle) const // convert to an axis and an angle(in radians)
	{
		const float squareLength = _xyzw[0]*_xyzw[0] + _xyzw[1]*_xyzw[1] + _xyzw[2]*_xyzw[2];			
		if (squareLength > 0.0001f)
		{
			angle = 2.0f * (float) acos(_xyzw[3]);
			const float inverseLength = 1.0f / (float) pow(squareLength, 0.5f);
			axis.setX(_xyzw[0] * inverseLength);
			axis.setY(_xyzw[1] * inverseLength);
			axis.setZ(_xyzw[2] * inverseLength);
		}
		else
		{
			angle = 0.0f;
			axis.setX(1.0f);
			axis.setY(0.0f);
			axis.setZ(0.0f);
		}
	}

	Matrix4x4 Quaternion::Matrix() const
	{
		float fTx  = 2.0f*_xyzw[0];
		float fTy  = 2.0f*_xyzw[1];
		float fTz  = 2.0f*_xyzw[2];
		float fTwx = fTx*_xyzw[3];
		float fTwy = fTy*_xyzw[3];
		float fTwz = fTz*_xyzw[3];
		float fTxx = fTx*_xyzw[0];
		float fTxy = fTy*_xyzw[0];
		float fTxz = fTz*_xyzw[0];
		float fTyy = fTy*_xyzw[1];
		float fTyz = fTz*_xyzw[1];
		float fTzz = fTz*_xyzw[2];

		float elements[] = {
			1.0f-(fTyy+fTzz), fTxy-fTwz,        fTxz+fTwy,        0.0f,
			fTxy+fTwz,        1.0f-(fTxx+fTzz), fTyz-fTwx,        0.0f,
			fTxz-fTwy,        fTyz+fTwx,        1.0f-(fTxx+fTyy), 0.0f,
			0.0f,             0.0f,             0.0f,             1.0f};

		return Matrix4x4(elements);		
	}

	Quaternion Quaternion::add(const Quaternion& rhs)
	{
		return Quaternion(_xyzw[0]+rhs._xyzw[0], _xyzw[1]+rhs._xyzw[1], _xyzw[2]+rhs._xyzw[2], _xyzw[3]+rhs._xyzw[3]);
	}

	Quaternion Quaternion::subtract(const Quaternion& rhs)
	{
		return Quaternion(_xyzw[0]-rhs._xyzw[0], _xyzw[1]-rhs._xyzw[1], _xyzw[2]-rhs._xyzw[2], _xyzw[3]-rhs._xyzw[3]);
	}

	Quaternion Quaternion::scaleBy(float scale)
	{
		return Quaternion(_xyzw[0]*scale, _xyzw[1]*scale, _xyzw[2]*scale, _xyzw[3]*scale);
	}

	Quaternion Quaternion::multiply(const Quaternion& rhs)
	{
		return Quaternion(_xyzw[3]*rhs._xyzw[0] + _xyzw[0]*rhs._xyzw[3] + _xyzw[1]*rhs._xyzw[2] - _xyzw[2]*rhs._xyzw[1],
							_xyzw[3]*rhs._xyzw[1] - _xyzw[0]*rhs._xyzw[2] + _xyzw[1]*rhs._xyzw[3] + _xyzw[2]*rhs._xyzw[0],
							_xyzw[3]*rhs._xyzw[2] + _xyzw[0]*rhs._xyzw[1] - _xyzw[1]*rhs._xyzw[0] + _xyzw[2]*rhs._xyzw[3],
							_xyzw[3]*rhs._xyzw[3] - _xyzw[0]*rhs._xyzw[0] - _xyzw[1]*rhs._xyzw[1] - _xyzw[2]*rhs._xyzw[2]);
	}

	float Quaternion::length() const
	{
		return sqrt(_xyzw[0]*_xyzw[0] + _xyzw[1]*_xyzw[1] + _xyzw[2]*_xyzw[2] + _xyzw[3]*_xyzw[3]);
	}

	void Quaternion::normalize()
	{
		const float length = this->length();

		if (length == 0)
		{
			_xyzw[0] = 0;
			_xyzw[1] = 0;
			_xyzw[2] = 0;
			_xyzw[3] = 1;
		}
		else
		{
			float inv = 1.0f / length;
			_xyzw[0] = _xyzw[0] * inv;
			_xyzw[1] = _xyzw[1] * inv;
			_xyzw[2] = _xyzw[2] * inv;
			_xyzw[3] = _xyzw[3] * inv;
		}
	}
}