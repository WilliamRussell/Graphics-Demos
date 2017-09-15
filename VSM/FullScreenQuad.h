#pragma once
#include "Camera.h"
#include "Texture.h"
#include "OGLModel.h"

class FullScreenQuad
{
public:
	FullScreenQuad();
	virtual ~FullScreenQuad(){ CleanUp(); }

	virtual void SetShaderID(int shaderID) { _shaderID = shaderID; }
	virtual int GetShaderID() const { return _shaderID; }

	virtual void SetModelID(int modelID) { _modelID = modelID; }
	virtual int GetModelID() const { return _modelID; }

	virtual void Draw(const Engine::Texture **tex, unsigned int numOfTextures) const;

	virtual const Engine::Quaternion& GetRotation() const { return _rotation; }
	virtual void SetRotation(const Engine::Quaternion& rotation) { _rotation = rotation; }

	virtual void CleanUp();
protected:
	int _shaderID, _modelID;
	Engine::Camera _camera;
	Engine::Quaternion _rotation;
};