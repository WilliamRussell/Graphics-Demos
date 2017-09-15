#pragma once
#include "Vector4f.h"
namespace Engine
{
	class Matrix4x4
	{
	public:
		Matrix4x4();
		Matrix4x4(float elements[]);

		void LoadIdentity();
		Matrix4x4 Multiply(const Matrix4x4& rhs) const;
		Vector4f Multiply(const Vector4f& rhs) const;

		Matrix4x4 GetInverse() const;
		Matrix4x4 GetTranspose() const;

		const float* Element() const {return _elements;}

		float& operator[](int i) {return _elements[i];}

		Matrix4x4 operator* (const Matrix4x4 &rhs) const {return Multiply(rhs);}
		Vector4f operator* (const Vector4f &rhs) const {return Multiply(rhs);} 
	private:
		float _elements[16];
	};
}