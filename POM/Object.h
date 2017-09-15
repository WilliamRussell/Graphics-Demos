#pragma once
#include "Vector3f.h"
#include "Quaternion.h"
#include "OGLModel.h"
#include "Camera.h"

class Object
{
public:
	Object() : _materialID(0), _shaderID(0), _depthShaderID(0), _modelID(0) {}
	virtual ~Object() {CleanUp();}

	const Engine::Vector3f& GetPosition() const {return _position;}
	const Engine::Quaternion& GetRotation() const {return _rotation;}

	virtual void SetPosition(const Engine::Vector3f& position) {_position = position;}
	virtual void SetRotation(const Engine::Quaternion& rotation) {_rotation = rotation;}

	virtual void SetMaterialID(int matID) {_materialID = matID;}
	virtual void SetShaderID(int shaderID) {_shaderID = shaderID;}
	virtual void SetDepthShaderID(int depthShaderID) {_depthShaderID = depthShaderID;}
	virtual void SetModelID(int modelID) {_modelID = modelID;}

	virtual int GetMaterialID() const {return _materialID;}
	virtual int GetShaderID() const {return _shaderID;}
	virtual int GetModelID() const {return _modelID;}

	virtual void CleanUp() {}

	virtual void Draw(const Engine::Camera &camera) const;
	virtual void DrawDepth(const Engine::Camera &camera) const;
protected:
	Engine::Matrix4x4 GenerateObjectMatrix() const;

	int _materialID;
	int _modelID;
	int _shaderID, _depthShaderID;
	Engine::Vector3f _position;
	Engine::Quaternion _rotation;
};