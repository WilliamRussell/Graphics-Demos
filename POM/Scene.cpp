#include "Scene.h"
#include "Context.h"
#include "MaterialManager.h"
#include "ShaderManager.h"
#include "ModelManager.h"
#include "TextureFactory.h"
#include "Text.h"
#include <cmath>
#include "Color.h"

#include <fstream>

Scene* Scene::currentScene = 0;

void WindowResize(int width, int height)
{
	int viewWidth, viewHeight, viewBottom, viewLeft;
	if (width < static_cast<int>(height * Scene::currentScene->_aspectRatio))
	{
		viewHeight = static_cast<int>(width / Scene::currentScene->_aspectRatio);
		viewBottom = static_cast<int>((height / 2.f) - (viewHeight / 2.f));
		viewLeft = 0;
		viewWidth = width;
	}
	else
	{
		viewWidth = static_cast<int>(height * Scene::currentScene->_aspectRatio);
		viewLeft = static_cast<int>(width / 2.f - viewWidth / 2.f);
		viewBottom = 0;
		viewHeight = height;
	}
	Engine::Context::GetCurrentContext()->SetViewport(viewLeft, viewBottom, viewWidth, viewHeight);
	Scene::currentScene->_gBuffer->Resize(viewWidth, viewHeight);
}

void OnMouseMove(double x, double y)
{
	int xChange = x - Scene::currentScene->_mouseX;
	int yChange = y - Scene::currentScene->_mouseY;

	Scene::currentScene->_mouseX = x;
	Scene::currentScene->_mouseY = y;

	if (Engine::Context::GetCurrentContext()->isMouseButtonDown(BUTTON_RIGHT) || Engine::Context::GetCurrentContext()->isMouseButtonDown(BUTTON_LEFT))
	{
		Engine::Vector3f pos = Scene::currentScene->_camera.GetPosition();
		Engine::Vector3f up = Scene::currentScene->_camera.GetUpVector();

		if (Engine::Context::GetCurrentContext()->isMouseButtonDown(BUTTON_RIGHT))
		{
			Scene::currentScene->_yRot -= xChange * 0.01f;
			Scene::currentScene->_xRot -= yChange * 0.01f;
		}
		else if (Engine::Context::GetCurrentContext()->isMouseButtonDown(BUTTON_LEFT))
		{
			Scene::currentScene->_radius += yChange * 0.01f;
			if (Scene::currentScene->_radius < 3.0f)
				Scene::currentScene->_radius = 3.0f;
		}

		up = Engine::Vector3f(0.f, 1.f, 0.f).rotate(Scene::currentScene->_xRot, 1.f, 0.f, 0.f);
		up = up.rotate(Scene::currentScene->_yRot, 0.f, 1.f, 0.f);

		pos = Engine::Vector3f(0.f, 0.f, Scene::currentScene->_radius).rotate(Scene::currentScene->_xRot, 1.f, 0.f, 0.f);
		pos = pos.rotate(Scene::currentScene->_yRot, 0.f, 1.f, 0.f);

		Scene::currentScene->_camera.SetCameraLookAt(pos, Engine::Vector3f(0.0f, 0.0f, 0.0f), up);
	}
}

void OnKeyboard(int button, int state)
{
	switch (button)
	{
	case KEY_ESC:
		Scene::currentScene->_quit = true;
		return;
	case 'A':
		if (state == PRESS)
		{
			if (Scene::currentScene->_light.GetLightMoveState() == MovingLight::LIGHT_MOVE_ANTICLOCKWISE)
				Scene::currentScene->_light.SetLightMoveState(MovingLight::LIGHT_STOPPED);
			else
				Scene::currentScene->_light.SetLightMoveState(MovingLight::LIGHT_MOVE_CLOCKWISE);
		}
		else if (state == RELEASE)
		{
			Scene::currentScene->_light.SetLightMoveState(MovingLight::LIGHT_STOPPED);
		}
		return;
	case 'D':
		if (state == PRESS)
		{
			if (Scene::currentScene->_light.GetLightMoveState() == MovingLight::LIGHT_MOVE_CLOCKWISE)
				Scene::currentScene->_light.SetLightMoveState(MovingLight::LIGHT_STOPPED);
			else
				Scene::currentScene->_light.SetLightMoveState(MovingLight::LIGHT_MOVE_ANTICLOCKWISE);
		}
		else if (state == RELEASE)
		{
			Scene::currentScene->_light.SetLightMoveState(MovingLight::LIGHT_STOPPED);
		}
		return;
	default:
		return;
	}
}

bool Scene::Init()
{
	_timeElapsed = 0.f;
	_fpsAverage = 0;
	_fpsTotal = 0.f;
	_tickCount = 0.f;
	_aspectRatio = 1.78f; //16:9


	if (Engine::Context::GetCurrentContext()->CreateWindow("Parallax Occlusion Mapping", 800, 600, 32, 0, 0))
	{		
		// Set static current scene pointer to this class. This allows the user event callback functions to access this object specifically
		currentScene = this;
		_mouseX = 0;
		_mouseY = 0;
		_quit = false;
		_radius = 3.0f;
		_yRot = 0.f;
		_xRot = 0.f;

		// Set an initial viewport, this is also set later on window resize
		Engine::Context::GetCurrentContext()->SetViewport(0, 75, 800, 449);

		// Initialize managers and create all materials, shaders and models
		if (!Engine::MaterialManager::GetManager()->CreateMaterials("materials\\materials.txt"))
			return false;
		if (!Engine::ShaderManager::GetManager()->CreateShaders("shaders\\shaders.txt"))
			return false;
		if (!Engine::ModelManager::GetManager()->CreateModels("models\\models.txt"))
			return false;
		if (!Engine::Text::GetManager()->LoadCharacterSheet("materials\\aafonts.png"))
			return false;

		//Initialize box object
		_box.SetModelID(Engine::ModelManager::GetManager()->GetModelID("cube"));
		_box.SetMaterialID(Engine::MaterialManager::GetManager()->GetMaterialID("CubeMat"));
		_box.SetShaderID(Engine::ShaderManager::GetManager()->GetShaderID("gBufferShader"));
		_box.SetPosition(Engine::Vector3f(0.0f, 0.0f, 0.0f));
		//_box.SetDepthShaderID(Engine::ShaderManager::GetManager()->GetShaderID("depthShader"));

		//Initialize light sphere object
		_lightSphere.SetModelID(Engine::ModelManager::GetManager()->GetModelID("sphere"));
		_lightSphere.SetMaterialID(Engine::MaterialManager::GetManager()->GetMaterialID("LightMat"));
		_lightSphere.SetShaderID(Engine::ShaderManager::GetManager()->GetShaderID("gBufferShader"));
		_lightSphere.SetPosition(Engine::Vector3f(0.0f, 0.0f, 0.0f));
		//_lightSphere.SetDepthShaderID(Engine::ShaderManager::GetManager()->GetShaderID("depthShader"));

		//Initialize quad objects
		_lightQuad.SetShaderID(Engine::ShaderManager::GetManager()->GetShaderID("lightingShader"));
		_lightQuad.SetModelID(Engine::ModelManager::GetManager()->GetModelID("fullScreenQuad"));	

		_simpleQuad.SetShaderID(Engine::ShaderManager::GetManager()->GetShaderID("basic"));
		_simpleQuad.SetModelID(Engine::ModelManager::GetManager()->GetModelID("fullScreenQuad"));

		//Initialize camera
		_camera.SetCameraView(Engine::Vector3f(0.f, 0.f, _radius), Engine::Vector3f(0.f, 0.f, -1.f), Engine::Vector3f(0.f, 1.f, 0.f));
		_camera.SetFrustum(-0.5f*_aspectRatio, 0.5f*_aspectRatio, 0.5f, -0.5f, 0.5f, 30.f);
		_light.SetFrustum(-1.5f, 1.5f, 1.5f, -1.5f, 3.0f, 30.f);
		_orthoCamera.SetOrtho(-1.f*_aspectRatio, +1.f*_aspectRatio, +1.f, -1.f, -1.f, +1.f);
		_orthoCamera.SetCameraView(Engine::Vector3f(0.f, 0.f, 0.f), Engine::Vector3f(0.f, 0.f, -1.f), Engine::Vector3f(0.f, 1.f, 0.f));

		// Create FBOs
		Engine::AttachmentFormat formats[] = { Engine::BYTE_RGBA, Engine::FLOAT_RGBA, Engine::FLOAT_RGBA, Engine::UIBYTE_R, Engine::FLOAT_RGBA, Engine::FLOAT_RG };
		_gBuffer = Engine::FrameBufferFactory::CreateFrameBuffer(800, 449, Engine::DEPTH_BUFFER, 4, formats);	

		//Set up light
		_light.SetAmbient(Engine::Color(0.1f, 0.1f, 0.1f, 1.0f));
		_light.SetDiffuse(Engine::Color::white());
		_light.SetSpecular(Engine::Color::white());
		_light.SetPosition(Engine::Vector3f(-0.f, 6.f, 6.f));

		// Register callbacks for resize, mouse move, and key press events
		Engine::Context::GetCurrentContext()->RegisterWindowResizeCallback(WindowResize);
		Engine::Context::GetCurrentContext()->RegisterOnMouseMoveCallback(OnMouseMove);
		Engine::Context::GetCurrentContext()->RegisterOnKeyboardCallback(OnKeyboard);

		_textShader = Engine::ShaderManager::GetManager()->GetShaderID("textShader");

		return true;
	}
	return false;
}

bool Scene::LoopOnce(float dt)
{	
	_timeElapsed += dt;

	_light.Update(dt);
	_lightSphere.SetPosition(_light.GetPosition());	

	//Apply the frame buffer and clear it's contents
	_gBuffer->Apply();
	Engine::Context::GetCurrentContext()->ClearBuffers();		

	//draw the solid objects to the framebuffer		
	_box.Draw(_camera);	
	_lightSphere.Draw(_camera);


	//apply the default frame buffer
	Engine::Context::GetCurrentContext()->ApplyDefaultFrameBuffer();
	Engine::Context::GetCurrentContext()->ClearBuffers();
	

	//Draw a full screen quad with all the textures generated as inputs 
	const Engine::Texture *textures[4];
	textures[0] = _gBuffer->GetColorAttachmentsAsTexture(0);
	textures[1] = _gBuffer->GetColorAttachmentsAsTexture(1);
	textures[2] = _gBuffer->GetColorAttachmentsAsTexture(2);
	textures[3] = _gBuffer->GetColorAttachmentsAsTexture(3);
		

	_lightQuad.Draw(textures, 4, _light.GetLight(), _camera, _light.GetCamera());	

	// debugging, render a buffer to screen
	//apply the default framebuffer (rendering to the screen)	
	//textures[0] = _gBuffer->GetColorAttachmentsAsTexture(3);
	//_simpleQuad.Draw(textures, 1);

	//calculate fps

	if (_fpsTotal > 2.0f)
	{
		_fpsAverage = (int)(1 / (_fpsTotal / _tickCount));
		_tickCount = 0;
		_fpsTotal = 0.0f;
	}
	else
	{
		_fpsTotal += dt;
		_tickCount++;
	}
	char fpsstring[32];
	sprintf_s(fpsstring, "FPS: %i", _fpsAverage);

	// write text to screen
	Engine::ShaderManager::GetManager()->ApplyShader(_textShader);
	Engine::Text::GetManager()->PrintString(_orthoCamera, Engine::Vector3f(-0.9f, 0.80f, 0.5f), 0.04f, "Parallax Occlusion Mapping");
	Engine::Text::GetManager()->PrintString(_orthoCamera, Engine::Vector3f(-0.9f, 0.50f, 0.5f), 0.02f, fpsstring);
	Engine::Text::GetManager()->PrintString(_orthoCamera, Engine::Vector3f(-0.9f, -0.9f, 0.5f), 0.02f, "William Russell");

	Engine::Text::GetManager()->PrintString(_orthoCamera, Engine::Vector3f(-0.9f, 0.70f, 0.5f), 0.02f, "Hold down right mouse button to rotate camera.");
	Engine::Text::GetManager()->PrintString(_orthoCamera, Engine::Vector3f(-0.9f, 0.65f, 0.5f), 0.02f, "Hold down left mouse button to move camera closer/further away.");
	Engine::Text::GetManager()->PrintString(_orthoCamera, Engine::Vector3f(-0.9f, 0.60f, 0.5f), 0.02f, "Use \'A\' and \'D\' to rotate the light source around the scene.");

	//swap front and back buffers
	Engine::Context::GetCurrentContext()->SwapBuffers();

	if (_quit || !Engine::Context::GetCurrentContext()->isWindowOpen())
	{
		Engine::Context::GetCurrentContext()->CloseWindow();
		return false;
	}
	else
	{
		return true;
	}
}
