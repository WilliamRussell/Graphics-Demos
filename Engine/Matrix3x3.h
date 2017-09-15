#pragma once
#include "Vector3f.h"
namespace Engine
{
	class Matrix3x3
	{
	public:
		Matrix3x3();
		Matrix3x3(float elements[]);

		void LoadIdentity();
		Matrix3x3 Multiply(const Matrix3x3& rhs) const;
		Vector3f Multiply(const Vector3f& rhs) const;

		Matrix3x3 GetInverse() const;
		Matrix3x3 GetTranspose() const;

		const float* Element() const {return _elements;}

		float& operator[](int i) {return _elements[i];}

		Matrix3x3 operator* (const Matrix3x3 &rhs) const {return Multiply(rhs);}
		Vector3f operator* (const Vector3f &rhs) const {return Multiply(rhs);} 
	private:
		float _elements[9];
	};
}