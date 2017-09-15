#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Matrix4x4.h"
#include "Input.h"
#include "Color.h"

namespace Engine
{
	class Context
	{

		friend void windowResize(GLFWwindow* window, int width, int height);
		friend void onMouseMove(GLFWwindow* window, double x, double y);
		friend void onMouseButton(GLFWwindow* window, int button, int action, int mods);
		friend void onKeyboard(GLFWwindow* window, int key, int scancode, int action, int mods);

	public:			
		bool CreateWindow(const char* windowTitle, int width, int height, int colorBits, int depthBits, int stencilBits);
		void SwitchFullscreen();
		void CloseWindow() { glfwTerminate(); }

		int GetWindowWidth() const { return _windowWidth; }
		int GetWindowHeight() const { return _windowHeight; }

		void SwapBuffers() { glfwSwapBuffers(_pWindow); glfwPollEvents(); }
		void ClearBuffers(const Color& clearColor = Color::black()) const;

		void ApplyDefaultFrameBuffer() const;

		void RegisterWindowResizeCallback(void (*userWindowResize)(int width, int height)) {_userWindowResize = userWindowResize;}
		void RegisterOnMouseMoveCallback(void (*userOnMouseMove)(double x, double y)) {_userOnMouseMove = userOnMouseMove;}
		void RegisterOnMouseButtonCallback(void (*userOnMouseButton)(int button, int action)) {_userOnMouseButton = userOnMouseButton;}
		void RegisterOnKeyboardCallback(void (*userOnKeyboard)(int button, int state)) {_userOnKeyboard = userOnKeyboard;}

		void EnableFullscreen();
		void DisableFullscreen();
		
		bool isKeyDown(int key) const;
		bool isMouseButtonDown(int button) const;
		bool isWindowOpen() const;

		void CullFrontFace() const;
		void CullBackFace() const;

		void WriteToColorBuffer(bool enable);
		void WriteToDepthBuffer(bool enable);

		void EnableAlphaBlening(bool enable);

		void SetViewport(int left, int bottom, int width, int height);

		static Context* GetCurrentContext();
	private:
		Context() : _pWindow(0), _userWindowResize(0), _userOnMouseMove(0), _userOnKeyboard(0), _userOnMouseButton(0) {}
		~Context(){}

		static Context* _pCurrentContext;

		GLFWwindow* _pWindow;
		void (*_userWindowResize)(int width, int height);
		void (*_userOnMouseMove)(double x, double y);
		void (*_userOnKeyboard)(int button, int state);
		void (*_userOnMouseButton)(int button, int action);
		// Window dimension variables
		int _windowWidth;
		int _windowHeight;
		bool _fullscreen;
		int _oldWindowHeight;
		int _oldWindowWidth;
		// Viewport dimension variables
		int _viewLeft, _viewBottom, _viewWidth, _viewHeight;		
	};
}
