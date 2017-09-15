#pragma once
#include "Texture.h"
#include <GL/glew.h>

namespace Engine
{
	class OGLTexture : public Texture
	{
	public:
		OGLTexture();
		OGLTexture(const char* filename);
		~OGLTexture();
		void CreateTexture();
		bool LoadTextureFromFile(const char* filename);
		void ApplyTexture(int textureUnit) const;
		void GenerateMipmaps();
		void ApplyTexParameter(TextureParam param, TextureParamValue value);
		void Cleanup();

		void SetTextureType(GLenum type) { _textureType = type; }
		GLenum GetTextureType() const { return _textureType; }
		GLuint GetOGLHandle() const {return _hTexture;}
	private:
		GLuint _hTexture;
		GLenum _textureType;
	};
}
