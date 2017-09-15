#include "OGLTexture.h"

namespace Engine
{
	class TextureFactory
	{
	public:
		static Texture* CreateTexture(){return new OGLTexture();}
		static Texture* CreateTexture(int width, int height, int levels, AttachmentFormat format)
		{
			OGLTexture* tempTexture = new OGLTexture();
			switch (format)
			{
			case BYTE_R:
				tempTexture->SetTextureType(GL_TEXTURE_2D);
				tempTexture->ApplyTexture(0);
				glTexStorage2D(GL_TEXTURE_2D, levels, GL_R8, width, height);
				break;
			case FLOAT_R:
				tempTexture->SetTextureType(GL_TEXTURE_2D);
				tempTexture->ApplyTexture(0);
				glTexStorage2D(GL_TEXTURE_2D, levels, GL_R32F, width, height);
				break;
			case FLOAT_RG:
				tempTexture->SetTextureType(GL_TEXTURE_2D);
				tempTexture->ApplyTexture(0);
				glTexStorage2D(GL_TEXTURE_2D, levels, GL_RG32F, width, height);
				break;
			case FLOAT_RGBA:
				tempTexture->SetTextureType(GL_TEXTURE_2D);
				tempTexture->ApplyTexture(0);
				glTexStorage2D(GL_TEXTURE_2D, levels, GL_RGBA32F, width, height);
				break;
			case BYTE_RGBA:
				tempTexture->SetTextureType(GL_TEXTURE_2D);
				tempTexture->ApplyTexture(0);
				glTexStorage2D(GL_TEXTURE_2D, levels, GL_RGBA8, width, height);
				break;
			case UIBYTE_R:
				tempTexture->SetTextureType(GL_TEXTURE_2D);
				tempTexture->ApplyTexture(0);
				glTexStorage2D(GL_TEXTURE_2D, levels, GL_R8UI, width, height);
				break;
			}

			return tempTexture;
		}
		static Texture* CreateTexture(const char* filename){return new OGLTexture(filename);}
	};
}
