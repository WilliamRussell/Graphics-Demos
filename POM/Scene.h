#pragma once
#include "Camera.h"
#include "Light.h"
#include "LightingQuad.h"
#include "FullScreenQuad.h"
#include "Object.h"
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
	Object _lightSphere;
	Object _box;
	LightingQuad _lightQuad;
	FullScreenQuad _simpleQuad;
	Engine::Camera _camera, _orthoCamera;
	MovingLight _light;	
	Engine::FrameBuffer *_gBuffer;

	static Scene *currentScene;
};


