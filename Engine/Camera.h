#pragma once
#include "ICamera.h"
#include "FrustumPlane.h"


namespace Engine
{
	class Camera : public ICamera
	{
	public:
		Camera() : _projMat(), _viewMat() {_projMat.LoadIdentity(); _viewMat.LoadIdentity();}
		~Camera() {}

		void SetFrustum(float left, float right, float top, float bottom, float near, float far);
		void SetOrtho(float left, float right, float top, float bottom, float near, float far);
		
		void SetCameraView(const Vector3f& cameraPos, const Vector3f& cameraLookVector, const Vector3f& cameraUpVector);
		void SetCameraLookAt(const Vector3f& cameraPos, const Vector3f& cameraLookAtVector, const Vector3f& cameraUpVector);

		Vector3f GetPosition() const {return _cameraPos;}
		Vector3f GetLookVector() const {return _cameraLookVec;}
		Vector3f GetUpVector() const {return _cameraUpVec;}

		const Matrix4x4& GetProjectionMatrix() const {return _projMat;}
		const Matrix4x4& GetViewMatrix() const {return _viewMat;}

		void SetProjectionMatrix(const Matrix4x4& projMat) {_projMat = projMat;}
		void SetViewMatrix(const Matrix4x4& viewMat) {_viewMat = viewMat;}

		void ApplyCameraMatricesToActiveShader(const Matrix4x4 &modelMatrix) const;		

		Matrix4x4 CalculateTransformationToCamera(const Camera& camera) const;
		Matrix4x4 CalculateTransformationToOmnidirectionalCamera(const ICamera& camera) const;

		bool PointFrustumCheck(const Vector3f& point) const;
		bool GridAlignedBoxFrustumCheck(const Vector3f& minBox, const Vector3f& maxBox) const;
		
	private:
		void CalculateFrustumPlanes();

		Vector3f _cameraPos;
		Vector3f _cameraLookVec;
		Vector3f _cameraUpVec;

		Matrix4x4 _projMat;
		Matrix4x4 _viewMat;

		FrustumPlane _frustumPlanes[6];
	};
}