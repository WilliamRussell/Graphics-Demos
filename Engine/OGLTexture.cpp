#include "OGLTexture.h"
#include "SOIL.h"
#include <fstream>
#include <algorithm>

namespace Engine
{
	OGLTexture::OGLTexture() : _hTexture(0), _textureType(GL_TEXTURE_2D)
	{	
		glGenTextures(1, &_hTexture);	
	}
	OGLTexture::OGLTexture(const char* filename) : _hTexture(0), _textureType(GL_TEXTURE_2D)
	{
		glGenTextures(1, &_hTexture);
		LoadTextureFromFile(filename);
	}

	OGLTexture::~OGLTexture()
	{
		Cleanup();
	}

	void OGLTexture::CreateTexture()
	{
		glGenTextures(1, &_hTexture);
	}

	bool OGLTexture::LoadTextureFromFile(const char *filename)
	{	
		std::ifstream instream(filename);
		if (!instream)
			return false; // file does not exist
		instream.close();

		int width, height, channels;

		unsigned char* imageData = SOIL_load_image(filename, &width, &height, &channels, SOIL_LOAD_AUTO);

		if (imageData && _hTexture)
		{						
			glBindTexture(_textureType, _hTexture);

			int levels = floor(log2(std::max(width, height))) + 1;

			glTexStorage2D(_textureType, levels, GL_RGBA8, width, height);
			if (channels == 3)
				glTexSubImage2D(_textureType, 0, 0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, imageData);
			else if (channels == 4)
				glTexSubImage2D(_textureType, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
			glGenerateMipmap(_textureType);

			// TODO: Query engine for set anisotropy level
			float maximumAnisotropy;
			glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maximumAnisotropy);
			glTexParameteri(_textureType, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(_textureType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameterf(_textureType, GL_TEXTURE_MAX_ANISOTROPY_EXT, maximumAnisotropy);
			glTextureParameteri(_hTexture, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTextureParameteri(_hTexture, GL_TEXTURE_WRAP_T, GL_REPEAT);

			

			delete[] imageData;
			return true;
		}
		return false;	
	}

	void OGLTexture::ApplyTexture(int textureUnit) const
	{
		glActiveTexture(GL_TEXTURE0 + textureUnit);
		glBindTexture(_textureType, _hTexture);
	}

	void OGLTexture::GenerateMipmaps()
	{		
		glGenerateTextureMipmap(_hTexture);
	}

	void OGLTexture::ApplyTexParameter(TextureParam param, TextureParamValue value)
	{
		switch (value)
		{
		case FILTER_NEAREST:			
			glTextureParameteri(_hTexture, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTextureParameteri(_hTexture, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			break;
		case FILTER_LINEAR:
			glTextureParameteri(_hTexture, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTextureParameteri(_hTexture, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			break;
		case FILTER_LINEAR_MIPMAP:
			glTextureParameteri(_hTexture, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTextureParameteri(_hTexture, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			float maximumAnisotropy;
			glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maximumAnisotropy);
			glTextureParameterf(_hTexture, GL_TEXTURE_MAX_ANISOTROPY_EXT, maximumAnisotropy);
			break;			
		case WRAP_CLAMP:
		{
			GLfloat col[] = { 1000.0f, 1000.0f, 1000.0f, 1000.0f };
			glTextureParameterfv(_hTexture, GL_TEXTURE_BORDER_COLOR, col);
			glTextureParameteri(_hTexture, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
			glTextureParameteri(_hTexture, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
			//glTextureParameteri(_hTexture, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			//glTextureParameteri(_hTexture, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);	
			break;
		}
		case WRAP_REPEAT:
			glTextureParameteri(_hTexture, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTextureParameteri(_hTexture, GL_TEXTURE_WRAP_T, GL_REPEAT);
			break;
		case COMPARE_LEQUAL:
			glTextureParameteri(_hTexture, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);
			glTextureParameteri(_hTexture, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
			break;		
		}
	}

	void OGLTexture::Cleanup()
	{
		if (_hTexture)
			glDeleteTextures(1, &_hTexture);
		_hTexture = 0;
	}
}
