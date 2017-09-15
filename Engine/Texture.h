#pragma once

namespace Engine
{
	enum AttachmentFormat
	{
		BYTE_R,
		FLOAT_R,
		FLOAT_RG,
		FLOAT_RGBA,
		BYTE_RGBA,
		UIBYTE_R,
		CUBE_FLOAT_R,
		CUBE_FLOAT_RGBA
	};

	enum TextureParam
	{
		FILTER_MODE,		
		WRAP_MODE,
		COMPARE_MODE
	};

	enum TextureParamValue
	{
		FILTER_NEAREST,
		FILTER_LINEAR,
		FILTER_LINEAR_MIPMAP,
		WRAP_CLAMP,
		WRAP_REPEAT,
		COMPARE_LEQUAL,
	};

	class Texture
	{
	public:	
		Texture(){};
		virtual void CreateTexture() = 0;
		virtual bool LoadTextureFromFile(const char* filename) = 0;
		virtual void ApplyTexture(int textureUnit) const = 0;

		virtual void GenerateMipmaps() = 0;
		virtual void ApplyTexParameter(TextureParam param, TextureParamValue value) = 0;
		virtual void Cleanup() = 0;
		virtual ~Texture(){};
	};
}
