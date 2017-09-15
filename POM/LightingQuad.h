#pragma once
#include "FullScreenQuad.h" 
#include "Light.h"

class LightingQuad : public FullScreenQuad
{
public:
	void Draw(const Engine::Texture **tex, unsigned int numOfTextures, const Engine::Light &light, const Engine::Camera &worldCamera, const Engine::Camera &lightCamera) const;
};