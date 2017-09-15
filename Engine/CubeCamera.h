#pragma once
#include "ICamera.h"
#include "FrustumPlane.h"

namespace Engine
{
	class CubeCamera : public ICamera
	{
	public:
		CubeCamera() : _projMat(), _viewMat() { _projMat.LoadIdentity(); _viewMat.LoadIdentity(); }
		~CubeCamera() {}

		void SetFrustum(float left, float right, float top, float bottom, float near, float far);		

		void SetCameraView(const Vector3f& cameraPos);		

		Vector3f GetPosition() const { return _cameraPos; }		

		const Matrix4x4& GetProjectionMatrix() const { return _projMat; }
		const Matrix4x4& GetViewMatrix() const { return _viewMat; }

		void SetProjectionMatrix(const Matrix4x4& projMat) { _projMat = projMat; }		

		void ApplyCameraMatricesToActiveShader(const Matrix4x4 &modelMatrix) const;		

		//Matrix4x4 CalculateTransformationToCamera(const Camera& camera) const;
		//Matrix4x4 CalculateTransformationToOmnidirectionalCamera(const CubeCamera& camera) const;

		bool PointFrustumCheck(const Vector3f& point) const;
		bool GridAlignedBoxFrustumCheck(const Vector3f& minBox, const Vector3f& maxBox) const;

	private:
		Vector3f _cameraPos;		

		Matrix4x4 _projMat;
		Matrix4x4 _viewMat;

		//FrustumPlane _frustumPlanes[6];
	};
}