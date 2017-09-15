#pragma once
#include "Texture.h"
#include "Vector3f.h"
#include "Camera.h"
#include "Matrix3x3.h"

namespace Engine
{
	class Text
	{
	public:
		static Text* GetManager();
		virtual ~Text(){}

		virtual bool LoadCharacterSheet(const char* filename) = 0;
		virtual void PrintString(const Camera &camera, const Vector3f &position, float scale, const char* string) const = 0;
		
	protected:
		Text() : _pTexture(0){}

		static Text* _pText;
		Texture *_pTexture;

		mutable Matrix4x4 _positionTransform; 
		mutable Matrix3x3 _textureTransform;
	};
}