#include "MovingLight.h"

void MovingLight::SetPosition(const Engine::Vector3f& position)
{
	_light.SetPosition(position);

	Engine::Vector3f up(0.f, 1.f, 0.f);

	up = up.crossProduct(_light.GetPosition());
	up = _light.GetPosition().crossProduct(up).normalize();

	_lightCamera.SetCameraLookAt(_light.GetPosition(), Engine::Vector3f(0.f, 0.f, 0.f), up);
}

void MovingLight::Update(float dt)
{
	if (_moveLight == LIGHT_MOVE_CLOCKWISE)
	{
		_moveTime += dt;
	}
	else if (_moveLight == LIGHT_MOVE_ANTICLOCKWISE)
	{
		_moveTime -= dt;
	}
	else
	{
		return;
	}

	_light.SetPosition(Engine::Vector3f(-6.f * sin(_moveTime), 6.0f, 6.f * cos(_moveTime)));	

	Engine::Vector3f up(0.f, 1.f, 0.f);

	up = up.crossProduct(_light.GetPosition());
	up = _light.GetPosition().crossProduct(up).normalize();

	_lightCamera.SetCameraLookAt(_light.GetPosition(), Engine::Vector3f(0.f, 0.f, 0.f), up);
}