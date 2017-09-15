#include <Engine.h>
#include "Scene.h"
#include <Timer.h>


int main()
{
	Scene* _scene = new Scene();
	if (_scene->Init())
	{
		Engine::InitTimer();
		double timeElapsed = Engine::GetTimeElapsed();
		double lastTime = 0;
		float dt = static_cast<float>(timeElapsed);
		while (_scene->LoopOnce(dt))
		{
			lastTime = timeElapsed;
			timeElapsed = Engine::GetTimeElapsed();
			dt = static_cast<float>(timeElapsed - lastTime);
		}
	}
	delete _scene;
	return 0;
}