#include "CubeCamera.h"
#include "ShaderManager.h"
#include "Matrix3x3.h"
#include "Camera.h"

#include <iostream>


namespace Engine
{
	void CubeCamera::SetFrustum(float left, float right, float top, float bottom, float near, float far)
	{
		_projMat.LoadIdentity();
		_projMat[0] = (2 * near) / (right - left);
		_projMat[5] = (2 * near) / (top - bottom);
		_projMat[8] = (right + left) / (right - left);
		_projMat[9] = (top + bottom) / (top - bottom);
		_projMat[10] = -(far + near) / (far - near);
		_projMat[11] = -1.f;
		_projMat[14] = -(2 * far * near) / (far - near);
		_projMat[15] = 0;		
	}


	void CubeCamera::SetCameraView(const Vector3f& cameraPos)
	{
		_cameraPos = cameraPos;	

		Matrix4x4 tempMat;

		tempMat.LoadIdentity();

		tempMat[12] = cameraPos.getX();
		tempMat[13] = cameraPos.getY();
		tempMat[14] = cameraPos.getZ();

		_viewMat = tempMat;		
	}

	void CubeCamera::ApplyCameraMatricesToActiveShader(const Matrix4x4 &modelMatrix) const
	{
		int shaderID = ShaderManager::GetManager()->GetActiveShaderID();

		Camera xPos, xNeg, zPos, zNeg, yPos, yNeg;
		xPos.SetCameraView(_cameraPos, Vector3f(+1.0f, +0.0f, +0.0f), Vector3f(0.0f, -1.0f, 0.0f));
		xNeg.SetCameraView(_cameraPos, Vector3f(-1.0f, +0.0f, +0.0f), Vector3f(0.0f, -1.0f, 0.0f));
		yPos.SetCameraView(_cameraPos, Vector3f(+0.0f, +1.0f, +0.0f), Vector3f(0.0f, 0.0f, 1.0f));
		yNeg.SetCameraView(_cameraPos, Vector3f(+0.0f, -1.0f, +0.0f), Vector3f(0.0f, 0.0f, -1.0f));
		zPos.SetCameraView(_cameraPos, Vector3f(+0.0f, +0.0f, +1.0f), Vector3f(0.0f, -1.0f, 0.0f));
		zNeg.SetCameraView(_cameraPos, Vector3f(+0.0f, +0.0f, -1.0f), Vector3f(0.0f, -1.0f, 0.0f));		

		int modViewMatLoc = ShaderManager::GetManager()->GetModelViewMatrixLocation(shaderID);
		int projMatLoc = ShaderManager::GetManager()->GetProjectionMatrixLocation(shaderID);

		ShaderManager::GetManager()->SetVariable(modViewMatLoc + 0, xPos.GetViewMatrix() * modelMatrix);
		ShaderManager::GetManager()->SetVariable(modViewMatLoc + 1, xNeg.GetViewMatrix() * modelMatrix);
		ShaderManager::GetManager()->SetVariable(modViewMatLoc + 2, yPos.GetViewMatrix() * modelMatrix);
		ShaderManager::GetManager()->SetVariable(modViewMatLoc + 3, yNeg.GetViewMatrix() * modelMatrix);
		ShaderManager::GetManager()->SetVariable(modViewMatLoc + 4, zPos.GetViewMatrix() * modelMatrix);
		ShaderManager::GetManager()->SetVariable(modViewMatLoc + 5, zNeg.GetViewMatrix() * modelMatrix);

		ShaderManager::GetManager()->SetVariable(projMatLoc, GetProjectionMatrix());
	}


	bool CubeCamera::PointFrustumCheck(const Vector3f& point) const
	{	
		return true;
	}

	bool CubeCamera::GridAlignedBoxFrustumCheck(const Vector3f& minBox, const Vector3f& maxBox) const
	{
		return true;
	}
}