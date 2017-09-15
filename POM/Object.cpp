#include "Object.h"
#include "MaterialManager.h"
#include "ShaderManager.h"
#include "ModelManager.h"
#include "Matrix4x4.h"

void Object::Draw(const Engine::Camera &camera) const
{
	Engine::ShaderManager::GetManager()->ApplyShader(_shaderID);
	Engine::MaterialManager::GetManager()->ApplyMaterialToActiveShader(_materialID);

	Engine::Matrix4x4 temp = GenerateObjectMatrix();
	
	camera.ApplyCameraMatricesToActiveShader(temp);

	Engine::ModelManager::GetManager()->DrawModel(_modelID);
}

void Object::DrawDepth(const Engine::Camera &camera) const
{
	Engine::ShaderManager::GetManager()->ApplyShader(_depthShaderID);
	Engine::Matrix4x4 temp = GenerateObjectMatrix();
	camera.ApplyCameraMatricesToActiveShader(temp);
	Engine::ModelManager::GetManager()->DrawModel(_modelID);
}

Engine::Matrix4x4 Object::GenerateObjectMatrix() const
{
	Engine::Matrix4x4 tempMat;
	tempMat.LoadIdentity();

	tempMat[12] = _position.getX();
	tempMat[13] = _position.getY();
	tempMat[14] = _position.getZ();

	return tempMat.Multiply(_rotation.Matrix());
}