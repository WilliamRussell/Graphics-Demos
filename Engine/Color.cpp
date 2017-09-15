#include "Color.h"

namespace Engine
{

	void Color::Assign(float r, float g, float b, float a) 
	{
		_rgba[0] = r;
		_rgba[1] = g;
		_rgba[2] = b;
		_rgba[3] = a;
	}

	Color::Color() 
	{ 
		Assign(0.0, 0.0, 0.0, 0.0);
	}

	Color::Color(float r, float g, float b, float a) 
	{
		Assign(r, g, b, a);
	}

	Color::Color(float rgba[]) 
	{
		Assign(rgba[0], rgba[1], rgba[2], rgba[3]);
	}
}

