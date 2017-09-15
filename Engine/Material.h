#pragma once
#include <string>
#include <vector>
#include "OGLTexture.h"
#include "Color.h"

namespace Engine
{
	class Material
	{
	public:
		Material() {}
		Material(int numTextures, int numColorProperties, int numFloatProperties);
		~Material();

		bool LoadTextureFromFile(const char* filename, int texIndex) { return LoadTextureFromFile(filename, _textures[texIndex]); }

		void SetMaterialName(const char* MaterialName) { _materialName = MaterialName; }	
		const char* GetMaterialName() const {return _materialName.data();}

		void SetColorProperty(const Color& colorProperty, int index) { _colorProperties[index] = colorProperty; }
		void SetFloatProperty(float floatProperty, int index) { _floatProperties[index] = floatProperty; }
	
		const Color& GetColorProperty(int colorIndex) const { return _colorProperties[colorIndex]; }
		float GetFloatProperty(int floatIndex) const { return _floatProperties[floatIndex]; }
		const Texture* GetTexture(int texIndex) const { return _textures[texIndex]; }

		int NumberOfTextures() const { return _textures.size(); }
		int NumberOfColorProperties() const { return _colorProperties.size(); }
		int NumberOfFloatProperties() const { return _floatProperties.size(); }

		void BindTextures() const;	
	private:
		bool LoadTextureFromFile(const char* filename, Texture* texture);

		std::string _materialName;		

		std::vector<Texture*> _textures;
		std::vector<Color> _colorProperties;
		std::vector<float> _floatProperties;		
	};
}