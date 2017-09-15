#pragma once
#include "Matrix4x4.h"

namespace Engine
{
	class ICamera
	{
	public:
		ICamera() {}
		virtual ~ICamera() {}

		virtual Vector3f GetPosition() const = 0;

		virtual const Matrix4x4& GetProjectionMatrix() const = 0;
		virtual const Matrix4x4& GetViewMatrix() const = 0;

		virtual void ApplyCameraMatricesToActiveShader(const Matrix4x4 &modelMatrix) const = 0;		

		virtual bool PointFrustumCheck(const Vector3f& point) const = 0;
		virtual bool GridAlignedBoxFrustumCheck(const Vector3f& minBox, const Vector3f& maxBox) const = 0;
	};
}