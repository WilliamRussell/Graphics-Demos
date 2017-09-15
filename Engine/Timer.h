#pragma once
#include <GLFW/glfw3.h>
namespace Engine
{	
	void InitTimer() {glfwSetTime(0.0);}
	double GetTimeElapsed() {return glfwGetTime();}	
}