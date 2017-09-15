#pragma once
#include "Object.h"

class Balls : public Object
{
public:
	Balls();
	Balls(int width, int height, int depth);
	~Balls();

	void SetNumberOfBalls(int width, int height, int depth);
	void SetPosition(const Engine::Vector3f& position);

	void Draw(const Engine::Camera &camera) const;
	void DrawDepth(const Engine::Camera &camera) const;

private:
	void CalculateBallPositions(int width, int height, int depth);
	void TranslateBallPositions(const Engine::Vector3f& translation);

	Engine::Matrix4x4 GenerateObjectMatrix(int ballIndex) const;

	int _numberOfBalls;	
	Engine::Vector3f* _positions;
};