#pragma once
#include <string>
#include "Color.h"
#include "Vector3f.h"
#include "Vector4f.h"

Engine::Color ParseColor(const std::string &inString);
Engine::Vector3f ParseVector2f(const std::string &inString); //TODO: Update function to return Vector2f
Engine::Vector3f ParseVector3f(const std::string &inString);
Engine::Vector4f ParseVector4f(const std::string &inString);
int ParseInt(const std::string &inString);
float ParseFloat(const std::string &instring);