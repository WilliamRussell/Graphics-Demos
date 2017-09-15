#pragma once

#include <Light.h>
#include <Camera.h>

class MovingLight : public Engine::Light
{
public:
	enum LightMoveState
	{
		LIGHT_STOPPED,
		LIGHT_MOVE_CLOCKWISE,
		LIGHT_MOVE_ANTICLOCKWISE
	};

	MovingLight() : _moveLight(LIGHT_STOPPED), _moveTime(0.f) {};
	~MovingLight() {};

	void SetLightMoveState(LightMoveState state) { _moveLight = state; }
	LightMoveState GetLightMoveState() const { return _moveLight; }
	void SetPosition(const Engine::Vector3f& position);

	void Update(float dt);

	const Engine::Light& GetLight() const { return _light; }
	const Engine::Camera& GetCamera() const { return _lightCamera; }

	// light setters & getters	
	void SetAmbient(const Engine::Color& ambient) { _light.SetAmbient(ambient); }
	void SetDiffuse(const Engine::Color& diffuse) { _light.SetDiffuse(diffuse); }
	void SetSpecular(const Engine::Color& specular) { _light.SetSpecular(specular); }

	const Engine::Vector3f& GetPosition() const { return _light.GetPosition(); }
	const Engine::Color& GetAmbient() const { return _light.GetAmbient(); }
	const Engine::Color& GetDiffuse() const { return _light.GetDiffuse(); }
	const Engine::Color& GetSpecular() const { return _light.GetSpecular(); }

	//camera setters & getters
	void SetFrustum(float left, float right, float top, float bottom, float near, float far) { _lightCamera.SetFrustum(left, right, top, bottom, near, far); }
private:
	Engine::Light _light;
	Engine::Camera _lightCamera;

	LightMoveState _moveLight;
	float _moveTime;
};