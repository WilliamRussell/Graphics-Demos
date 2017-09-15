#include "FullScreenQuad.h"
#include "ShaderManager.h"
#include "ModelManager.h"
#include "Matrix4x4.h"
#include "Vector3f.h"

FullScreenQuad::FullScreenQuad() : _shaderID(0), _modelID(0)
{
	_camera.SetOrtho(-1.f, +1.f, +1.f, -1.f, -1.f, +1.f);
}

void FullScreenQuad::CleanUp()
{
	//if (_quad)
	//	delete _quad;
}

void FullScreenQuad::Draw(const Engine::Texture **tex, unsigned int numOfTextures) const
{
	Engine::ShaderManager::GetManager()->ApplyShader(_shaderID);	

	_camera.ApplyCameraMatricesToActiveShader(_rotation.Matrix());
	for (int i = 0; i < numOfTextures; i++)
	{
#ifndef USE_BINDLESS_TEXTURES
		tex[i]->ApplyTexture(i);
		Engine::ShaderManager::GetManager()->SetVariable(Engine::ShaderManager::GetManager()->GetTextureLocation(_shaderID, i), i);
#endif

		Engine::ShaderManager::GetManager()->ApplyTextureToShader(_shaderID, tex[i], i);
	}

	Engine::ModelManager::GetManager()->DrawModel(_modelID);
}
