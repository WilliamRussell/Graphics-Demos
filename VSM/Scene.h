#pragma once
#include "Camera.h"
#include "Light.h"
#include "LightingQuad.h"
#include "FullScreenQuad.h"
#include "Balls.h"
#include "FrameBufferFactory.h"
#include "MovingLight.h"

class Scene
{
	friend void WindowResize(int width, int height);
	friend void OnMouseMove(double x, double y);
	friend void OnKeyboard(int button, int state);

public:
	bool Init();
	bool LoopOnce(float dt);
private:
	bool _quit;
	int _mouseX;
	int _mouseY;

	float _radius;
	float _yRot;
	float _xRot;

	float _aspectRatio;

	int _fpsAverage;
	float _fpsTotal;
	int _tickCount;

	float _timeElapsed;
	int _textShader;
	Balls _balls;
	Object _lightSphere;
	Object _floor;
	LightingQuad _lightQuad;
	FullScreenQuad _simpleQuad, _blurQuad;
	Engine::Camera _camera, _orthoCamera;
	MovingLight _light;
	Engine::Texture *_varianceShadowMap;
	Engine::FrameBuffer *_gBuffer, *_varianceShadowBuffer, *_blurBuffer;

	static Scene *currentScene;
};


