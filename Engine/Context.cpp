#include "Context.h"

namespace Engine
{
	Context* Context::_pCurrentContext = 0;

	Context* Context::GetCurrentContext()
	{
		if (!_pCurrentContext)	
			_pCurrentContext = new Context();
		return _pCurrentContext;
	}

	void Context::SetViewport(int left, int bottom, int width, int height)
	{
		glViewport(left, bottom, width, height);	
		_viewLeft = left;
		_viewBottom = bottom;
		_viewWidth = width;
		_viewHeight = height;
	}
	
	bool Context::CreateWindow(const char* windowTitle, int width, int height, int colorBits, int depthBits, int stencilBits)
	{
		if (width <= 0 || height <= 0)
			return false;
		int singleColorBit = colorBits / 4;

		if (!glfwInit())
			return false;

		glfwWindowHint(GLFW_RED_BITS, singleColorBit);
		glfwWindowHint(GLFW_GREEN_BITS, singleColorBit);
		glfwWindowHint(GLFW_BLUE_BITS, singleColorBit);
		glfwWindowHint(GLFW_ALPHA_BITS, singleColorBit);
		glfwWindowHint(GLFW_DEPTH_BITS, depthBits);
		glfwWindowHint(GLFW_STENCIL_BITS, stencilBits);
		//glfwWindowHint(GLFW_DECORATED, 0);

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);

		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
		//const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

		//glfwWindowHint(GLFW_RED_BITS, mode->redBits);
		//glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
		//glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
		//glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

		_pWindow = glfwCreateWindow(width, height, windowTitle, NULL, NULL);
		//_pWindow = glfwCreateWindow(mode->width, mode->height, "WILL IS AWESOME!", glfwGetPrimaryMonitor(), NULL);
		if (!_pWindow)
		{
			glfwTerminate();
			return false;
		}
		glfwMakeContextCurrent(_pWindow);			

		GLenum err = glewInit();		
		
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);		
		glfwSetFramebufferSizeCallback(_pWindow, windowResize);
		glfwSetCursorPosCallback(_pWindow, onMouseMove);
		glfwSetMouseButtonCallback(_pWindow, onMouseButton);
		glfwSetKeyCallback(_pWindow, onKeyboard);
		glfwSetInputMode(_pWindow, GLFW_STICKY_KEYS, 1);		

		
		glEnable(GL_CULL_FACE);		
		glEnable(GL_DEPTH_TEST);
		glCullFace(GL_BACK);
		glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		
		_windowWidth = width;
		_windowHeight = height;
		//_windowWidth = mode->width;
		//_windowHeight = mode->height;

		_fullscreen = false;

		_viewLeft = 0;
		_viewBottom = 0;
		_viewWidth = _windowWidth;
		_viewHeight = _windowHeight;		
		return true;
	}

	void Context::SwitchFullscreen()
	{
		if (_fullscreen == false)
		{
			_oldWindowHeight = _windowHeight;
			_oldWindowWidth = _windowWidth;

			const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
			glfwSetWindowSize(_pWindow, mode->width, mode->height);

			_fullscreen = true;
		}
		else
		{
			_windowHeight = _oldWindowHeight;
			_windowWidth = _oldWindowWidth;

			glfwSetWindowSize(_pWindow, _windowWidth, _windowHeight);

			_fullscreen = false;
		}
	}


	void Context::ApplyDefaultFrameBuffer() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		GLenum buff = GL_BACK_LEFT;
		glDrawBuffers(1, &buff);
		glViewport(_viewLeft, _viewBottom, _viewWidth, _viewHeight);
	}

	void Context::ClearBuffers(const Color& clearColor) const
	{
		glClearColor(clearColor.rgba()[0], clearColor.rgba()[1], clearColor.rgba()[2], clearColor.rgba()[3]);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void windowResize(GLFWwindow* window, int width, int height)
	{
		Context::GetCurrentContext()->_windowWidth = width;
		Context::GetCurrentContext()->_windowHeight = height;

		if (Context::GetCurrentContext()->_userWindowResize)		
			Context::GetCurrentContext()->_userWindowResize(width, height);		
	}

	void onMouseMove(GLFWwindow* window, double x, double y)
	{
		if (Context::GetCurrentContext()->_userOnMouseMove)
			Context::GetCurrentContext()->_userOnMouseMove(x, y);
	}

	void onMouseButton(GLFWwindow* window, int button, int action, int mods)
	{
		if (Context::GetCurrentContext()->_userOnMouseButton)
			Context::GetCurrentContext()->_userOnMouseButton(button, action);
	}


	void onKeyboard(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (Context::GetCurrentContext()->_userOnKeyboard)
			Context::GetCurrentContext()->_userOnKeyboard(key, action);
	}

	bool Context::isWindowOpen() const
	{
		//return glfwGetWindowParam(GLFW_OPENED);
		return (!glfwWindowShouldClose(_pWindow));
	}

	bool Context::isMouseButtonDown(int button) const
	{		
		//return glfwGetMouseButton(button);
		//return false;

		if (glfwGetMouseButton(_pWindow, button) == GLFW_PRESS)
			return true;
		return false;
	}

	bool Context::isKeyDown(int key) const
	{
		//return glfwGetKey(key);
		return false;
	}

	void Context::CullFrontFace() const
	{
		glCullFace(GL_FRONT);
	}

	void Context::CullBackFace() const
	{
		glCullFace(GL_BACK);
	}
	
	void Context::WriteToColorBuffer(bool enable)
	{
		glColorMask(enable, enable, enable, enable);
	}

	void Context::WriteToDepthBuffer(bool enable)
	{
		glDepthMask(enable);
	}

	void Context::EnableAlphaBlening(bool enable)
	{
		if (enable)
			glEnable(GL_BLEND);
		else
			glDisable(GL_BLEND);
	}
}

