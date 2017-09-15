#pragma once
#include "Text.h"
#include <GL/glew.h>

namespace Engine
{
	class OGLText : public Text
	{
	public:		
		~OGLText();
		bool LoadCharacterSheet(const char* filename);
		void PrintString(const Camera &camera, const Vector3f &position, float scale, const char* string) const;
	private:
		OGLText();
		OGLText(const OGLText&){InitalizeOGLText();}
		OGLText& operator= (const OGLText&){}

		void InitalizeOGLText();

		GLuint _vaoID;
		GLuint _vertexBufferID;
		GLuint _indicesBufferID;

		friend class Text;
	};
}