#include "LightingQuad.h"
#include "ShaderManager.h"
#include "ModelManager.h"
#include "Matrix4x4.h"


void LightingQuad::Draw(const Engine::Texture **tex, unsigned int numOfTextures, const Engine::Light &light, const Engine::Camera &worldCamera, const Engine::Camera &lightCamera) const
{
	Engine::ShaderManager::GetManager()->ApplyShader(_shaderID);

	Engine::Matrix4x4 temp;
	temp.LoadIdentity();

	_camera.ApplyCameraMatricesToActiveShader(temp);
	for (int i = 0; i < numOfTextures; i++)
	{
		tex[i]->ApplyTexture(i);
		Engine::ShaderManager::GetManager()->SetVariable(Engine::ShaderManager::GetManager()->GetTextureLocation(_shaderID, i), i);
	}

	light.PassLightToShader(_shaderID, worldCamera.GetViewMatrix());

	int variableLoc = Engine::ShaderManager::GetManager()->GetVariableLocation(_shaderID, "transformMat");
	Engine::ShaderManager::GetManager()->SetVariable(variableLoc, worldCamera.CalculateTransformationToCamera(lightCamera));

	Engine::ModelManager::GetManager()->DrawModel(_modelID);
}