#include "Camera.h"
#include "ShaderManager.h"
#include "Matrix3x3.h"

#define PI 3.141592

namespace Engine
{
	void Camera::SetFrustum(float left, float right, float top, float bottom, float near, float far)
	{
		_projMat.LoadIdentity();
		_projMat[ 0] = (2 * near) / (right - left);
		_projMat[ 5] = (2 * near) / (top - bottom);
		_projMat[ 8] = (right + left) / (right - left);
		_projMat[ 9] = (top + bottom) / (top - bottom);
		_projMat[10] = -(far + near) / (far - near);
		_projMat[11] = -1.f;
		_projMat[14] = -(2 * far * near) / (far - near);
		_projMat[15] = 0;

		CalculateFrustumPlanes();
	}

	void Camera::SetOrtho(float left, float right, float top, float bottom, float near, float far)
	{
		_projMat.LoadIdentity();
		_projMat[ 0] = +2 / (right-left);
		_projMat[ 5] = +2 / (top-bottom);
		_projMat[10] = -2 / (far-near);
		_projMat[12] = (right+left)/(right-left);
		_projMat[13] = (top+bottom)/(top-bottom);
		_projMat[14] = (far+near)/(far-near);

		CalculateFrustumPlanes();
	}

	void Camera::SetCameraLookAt(const Vector3f& cameraPos, const Vector3f& cameraLookAtVector, const Vector3f& cameraUpVector)
	{		
		Vector3f cameraLookVector(cameraLookAtVector.subtract(cameraPos));
		float mag = cameraLookVector.getMagnitude();
		cameraLookVector = cameraLookVector.scaleBy(1.f/mag);

		SetCameraView(cameraPos, cameraLookVector, cameraUpVector);
	}
	
	void Camera::SetCameraView(const Vector3f& cameraPos, const Vector3f& cameraLookVector, const Vector3f& cameraUpVector)
	{
		_cameraPos = cameraPos;
		_cameraLookVec = cameraLookVector;
		_cameraUpVec = cameraUpVector;		

		Matrix4x4 tempMat;	

		Vector3f s = cameraLookVector.crossProduct(cameraUpVector);
		Vector3f u = s.crossProduct(cameraLookVector);
		
		tempMat[0] = s.getX();
		tempMat[1] = u.getX();
		tempMat[2] = -cameraLookVector.getX();

		tempMat[4] = s.getY();
		tempMat[5] = u.getY();
		tempMat[6] = -cameraLookVector.getY();

		tempMat[8] = s.getZ();
		tempMat[9] = u.getZ();
		tempMat[10] = -cameraLookVector.getZ();

		tempMat[15] = 1.f;		

		_viewMat = tempMat;
		tempMat.LoadIdentity();
		
		tempMat[12] = -cameraPos.getX();
		tempMat[13] = -cameraPos.getY();
		tempMat[14] = -cameraPos.getZ();		

		_viewMat = _viewMat.Multiply(tempMat);

		CalculateFrustumPlanes();
	}

	void Camera::ApplyCameraMatricesToActiveShader(const Matrix4x4 &modelMatrix) const
	{
		int shaderID = ShaderManager::GetManager()->GetActiveShaderID();

		Matrix4x4 tempRot;
		tempRot[0] = 1.f; tempRot[4] = 0.f; tempRot[8] = 0.f; tempRot[12] = 0.f;
		tempRot[1] = 0.f; tempRot[5] = 0.f; tempRot[9] = -1.f; tempRot[13] = 0.f;
		tempRot[2] = 0.f; tempRot[6] = 1.f; tempRot[10] = 0.f; tempRot[14] = 0.f;
		tempRot[3] = 0.f; tempRot[7] = 0.f; tempRot[11] = 0.f; tempRot[15] = 1.f;

		Matrix4x4 temp = _viewMat * modelMatrix;
		Matrix3x3 normalMatrix;
		normalMatrix[0] = temp[0];
		normalMatrix[1] = temp[1];
		normalMatrix[2] = temp[2];
		normalMatrix[3] = temp[4];
		normalMatrix[4] = temp[5];
		normalMatrix[5] = temp[6];
		normalMatrix[6] = temp[8];
		normalMatrix[7] = temp[9];
		normalMatrix[8] = temp[10];

		int modViewMatLoc = ShaderManager::GetManager()->GetModelViewMatrixLocation(shaderID);
		int normalMatLoc = ShaderManager::GetManager()->GetNormalMatrixLocation(shaderID);
		int projMatLoc = ShaderManager::GetManager()->GetProjectionMatrixLocation(shaderID);

		ShaderManager::GetManager()->SetVariable(modViewMatLoc, temp);
		ShaderManager::GetManager()->SetVariable(projMatLoc, GetProjectionMatrix());
		ShaderManager::GetManager()->SetVariable(normalMatLoc, normalMatrix);
	}

	Matrix4x4 Camera::CalculateTransformationToCamera(const Camera& camera) const
	{
		Matrix4x4 invert = _viewMat.GetInverse();
		return camera.GetProjectionMatrix() * camera.GetViewMatrix() * invert;
	}

	Matrix4x4 Camera::CalculateTransformationToOmnidirectionalCamera(const ICamera& camera) const
	{		
		return camera.GetViewMatrix() * _viewMat.GetInverse();
	}

	void Camera::CalculateFrustumPlanes()
	{
		Matrix4x4 clipMat = _projMat.Multiply(_viewMat);		
		
		_frustumPlanes[0].Assign(clipMat[3] - clipMat[0], clipMat[7] - clipMat[4], clipMat[11] - clipMat[ 8], clipMat[15] - clipMat[12]);
		_frustumPlanes[1].Assign(clipMat[3] + clipMat[0], clipMat[7] + clipMat[4], clipMat[11] + clipMat[ 8], clipMat[15] + clipMat[12]);
		_frustumPlanes[2].Assign(clipMat[3] + clipMat[1], clipMat[7] + clipMat[5], clipMat[11] + clipMat[ 9], clipMat[15] + clipMat[13]);
		_frustumPlanes[3].Assign(clipMat[3] - clipMat[1], clipMat[7] - clipMat[5], clipMat[11] - clipMat[ 9], clipMat[15] - clipMat[13]);
		_frustumPlanes[4].Assign(clipMat[3] - clipMat[2], clipMat[7] - clipMat[6], clipMat[11] - clipMat[10], clipMat[15] - clipMat[14]);
		_frustumPlanes[5].Assign(clipMat[3] + clipMat[2], clipMat[7] + clipMat[6], clipMat[11] + clipMat[10], clipMat[15] + clipMat[14]);

		_frustumPlanes[0].NormalizePlane();
		_frustumPlanes[1].NormalizePlane();
		_frustumPlanes[2].NormalizePlane();
		_frustumPlanes[3].NormalizePlane();
		_frustumPlanes[4].NormalizePlane();
		_frustumPlanes[5].NormalizePlane();
	}

	bool Camera::PointFrustumCheck(const Vector3f& point) const
	{
		for (int i = 0; i < 6; i++)
		{
			if (!_frustumPlanes[i].TestPoint(point))
				return false;
		}
		return true;
	}

	bool Camera::GridAlignedBoxFrustumCheck(const Vector3f& minBox, const Vector3f& maxBox) const
	{
		float x1 = minBox.getX();
		float y1 = minBox.getY();
		float z1 = minBox.getZ();

		float x2 = maxBox.getX();
		float y2 = maxBox.getY();
		float z2 = maxBox.getZ();

		for (int i = 0; i < 6; i++)
		{
			if (_frustumPlanes[i].TestPoint(Engine::Vector3f(x1, y1, z1))) continue;
			if (_frustumPlanes[i].TestPoint(Engine::Vector3f(x2, y1, z1))) continue;
			if (_frustumPlanes[i].TestPoint(Engine::Vector3f(x1, y2, z1))) continue;
			if (_frustumPlanes[i].TestPoint(Engine::Vector3f(x2, y2, z1))) continue;
			if (_frustumPlanes[i].TestPoint(Engine::Vector3f(x1, y1, z2))) continue;
			if (_frustumPlanes[i].TestPoint(Engine::Vector3f(x2, y1, z2))) continue;
			if (_frustumPlanes[i].TestPoint(Engine::Vector3f(x1, y2, z2))) continue;
			if (_frustumPlanes[i].TestPoint(Engine::Vector3f(x2, y2, z2))) continue;

			return false;
		}
		return true;
	}
}