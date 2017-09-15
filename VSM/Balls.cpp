#include "Balls.h"
#include "MaterialManager.h"
#include "ShaderManager.h"
#include "ModelManager.h"
#include "Matrix4x4.h"

Balls::Balls() : _numberOfBalls(16)
{
	_positions = new Engine::Vector3f[16];	
}

Balls::Balls(int width, int height, int depth) : _numberOfBalls(width * height * depth)
{
	_positions = new Engine::Vector3f[_numberOfBalls];
	CalculateBallPositions(width, height, depth);
}

Balls::~Balls()
{
	delete[] _positions;
}

void Balls::CalculateBallPositions(int width, int height, int depth)
{
	for (int i = 0; i < depth; i++)
	{
		for (int j = 0; j < height; j++)
		{
			for (int k = 0; k < width; k++)
			{
				Engine::Vector3f tempPos(_position.getX() + 1.0f * k, _position.getY() + 1.0f * j, _position.getZ() + 1.0f * i);
				_positions[i * depth * height + j * height + k] = tempPos;
			}
		}
	}
}

void Balls::TranslateBallPositions(const Engine::Vector3f& translation)
{
	for (int i = 0; i < _numberOfBalls; i++)
	{
		_positions[i] = _positions[i] + translation;
	}
}

void Balls::SetNumberOfBalls(int width, int height, int depth)
{
	if (width * height * depth != _numberOfBalls)
	{
		_numberOfBalls = width * height * depth;
		delete[] _positions;
		_positions = new Engine::Vector3f[_numberOfBalls];
	}

	CalculateBallPositions(width, height, depth);
}

void Balls::SetPosition(const Engine::Vector3f& position)
{
	Engine::Vector3f translation = _position - position;
	_position = position;

	TranslateBallPositions(translation);
}

void Balls::Draw(const Engine::Camera &camera) const
{
	Engine::ShaderManager::GetManager()->ApplyShader(_shaderID);
	Engine::MaterialManager::GetManager()->ApplyMaterialToActiveShader(_materialID);	

	for (int i = 0; i < _numberOfBalls; i++)
	{
		Engine::Matrix4x4 temp = GenerateObjectMatrix(i);
		camera.ApplyCameraMatricesToActiveShader(temp);
		Engine::ModelManager::GetManager()->DrawModel(_modelID);
	}
}

void Balls::DrawDepth(const Engine::Camera &camera) const
{
	Engine::ShaderManager::GetManager()->ApplyShader(_depthShaderID);

	for (int i = 0; i < _numberOfBalls; i++)
	{
		Engine::Matrix4x4 temp = GenerateObjectMatrix(i);
		camera.ApplyCameraMatricesToActiveShader(temp);
		Engine::ModelManager::GetManager()->DrawModel(_modelID);
	}
}

Engine::Matrix4x4 Balls::GenerateObjectMatrix(int ballIndex) const
{
	Engine::Matrix4x4 tempMat;
	tempMat.LoadIdentity();

	tempMat[12] = _positions[ballIndex].getX();
	tempMat[13] = _positions[ballIndex].getY();
	tempMat[14] = _positions[ballIndex].getZ();

	return _rotation.Matrix().Multiply(tempMat);
}