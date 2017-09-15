#include "Material.h"
#include "Context.h"

namespace Engine
{
	Material::~Material()
	{
		for (int i = 0; i < _textures.size(); i++)
			delete _textures[i];
	}

	Material::Material(int numTextures, int numColorProperties, int numFloatProperties)
	{
		for (int i = 0; i < numTextures; i++)
		{
			_textures.push_back(new OGLTexture);
		}
		for (int i = 0; i < numColorProperties; i++)
		{
			_colorProperties.push_back(Color::white());
		}
		for (int i = 0; i < numFloatProperties; i++)
		{
			_floatProperties.push_back(float(0.f));
		}
	}


	bool Material::LoadTextureFromFile(const char* filename, Texture* texture)
	{		
		if (texture->LoadTextureFromFile(filename))
			return true;					
		return false;
	}

	void Material::BindTextures() const
	{
		for (int i = 0; i < _textures.size(); i++)
			_textures[i]->ApplyTexture(i);
	}
}