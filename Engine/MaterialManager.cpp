#include "MaterialManager.h"
#include "ShaderManager.h"
#include "Parser.h"
#include <fstream>
#include <map>
#include <iostream>

namespace Engine
{
	MaterialManager* MaterialManager::_pManager = 0;


	//	GetManager	
	//	Returns the instance of MaterialManager
	MaterialManager* MaterialManager::GetManager()
	{
		if (!_pManager)	
			_pManager = new MaterialManager();	
		return _pManager;
	}

	//
	//dtor
	MaterialManager::~MaterialManager()
	{
		DeleteAllMaterials();
	}

	//	CreateMaterials
	//	Create materials from text file
	bool MaterialManager::CreateMaterials(const char *filename)
	{
		std::ifstream filein(filename);

		// check file opened correctly
		if (!filein)
			return false;

		std::map<std::string, std::pair<std::string, int> > matProperties;
		int numFloatProperties = 0;
		int numColorProperties = 0;
		int numTextures = 0;
		std::string word;		
		while(filein >> word)
		{
			if (word.compare("materialProperties") == 0)
			{
				filein >> word;
				if (word.compare("{") == 0)
				{
					while ((filein >> word) && (word.compare("}") != 0))
					{						
						std::string name = word;
						filein >> word;
						if (word.compare("color") == 0)
						{
							matProperties[name] = std::pair<std::string, int>("color", numColorProperties);
							numColorProperties += 1;							
						}
						else if (word.compare("float") == 0)
						{
							matProperties[name] = std::pair<std::string, int>("float", numFloatProperties);
							numFloatProperties += 1;							
						}
						else if (word.compare("texture") == 0)
						{
							matProperties[name] = std::pair<std::string, int>("texture", numTextures);
							numTextures += 1;							
						}
						else
						{
							std::cout << "Error: \"" << word << "\" is not a valid type for material property \"" << name << "\"." << std::endl;							
						}
					}
				}
			}

			if (word.compare("material") == 0)
			{
				// read the next 
				filein >> word;
				if (word.compare("{") == 0)
				{
					Material* newMaterial = new Material(numTextures, numColorProperties, numFloatProperties);
					while ((filein >> word) && (word.compare("}") != 0))
					{
						if (word.compare("name") == 0)
						{
							std::string materialName;
							filein >> materialName;
							newMaterial->SetMaterialName(materialName.data());
							continue;
						}

						if (matProperties.find(word) == matProperties.end())
						{
							std::cout << "Error: material property \"" << word << "\" is not defined." << std::endl;
						}
						else
						{
							std::pair<std::string, int> materialInfo = matProperties[word];
							if (materialInfo.first.compare("float") == 0)
							{
								std::string value;
								filein >> value;
								newMaterial->SetFloatProperty(ParseFloat(value), materialInfo.second);
								continue;
							}
							if (materialInfo.first.compare("color") == 0)
							{
								std::string value;
								filein >> value;
								newMaterial->SetColorProperty(ParseColor(value), materialInfo.second);
								continue;
							}
							if (materialInfo.first.compare("texture") == 0)
							{
								std::string value;
								filein >> value;
								if (!newMaterial->LoadTextureFromFile(value.c_str(), materialInfo.second))
									std::cout << "Failed to load texture: " << value.c_str() << std::endl;
								continue;
							}
						}											
					}
					_materials.push_back(newMaterial);
					_numOfMaterials++;
				}
			}
		}
		filein.close();
	
		_ubo.CreateUniformBuffer();
		if (_numOfMaterials)
			return true;
		return false;
	}

	int MaterialManager::GetMaterialID(const char* materialName) const
	{
		for (int i = 0; i < _numOfMaterials; i++)
		{			
			if (!strcmp(_materials[i]->GetMaterialName(), materialName))
			{
				return i;
			}		
		}
		return -1;
	}

	//	DeleteMaterial
	//	Delete a material corresponding to the materil ID
	bool MaterialManager::DeleteMaterial(int materialID)
	{
		delete _materials[materialID];
		_materials[materialID] = 0;
		return true;
	}

	//	DeleteAllMaterials
	//	Delete every material managed by material manager
	bool MaterialManager::DeleteAllMaterials()
	{
		for (unsigned int i = 0; i < _materials.size(); i++)
		{
			if (_materials[i])
			{
				delete _materials[i];
				_materials[i] = 0;
			}
		}
		_materials.clear();
		_numOfMaterials = 0;
		return true;
	}

	// GetMaterial
	// Return pointer to the requested material
	const Material* MaterialManager::GetMaterial(int materialID)
	{
		if (_materials[materialID] && materialID <= _numOfMaterials)
		{
			return _materials[materialID];			 
		}
		return _materials[0];
	}

	// ApplyMaterialToActiveShader
	// Apply the material properties to the current shader
	bool MaterialManager::ApplyMaterialToActiveShader(int materialID) const
	{
		if (_materials[materialID] && materialID <= _numOfMaterials)
		{
			_materials[materialID]->BindTextures();

			int shaderID = ShaderManager::GetManager()->GetActiveShaderID();
			int matIDLoc = ShaderManager::GetManager()->GetMaterialIDLocation(shaderID);
			ShaderManager::GetManager()->SetVariable(matIDLoc, static_cast<unsigned int>(materialID));

#ifndef USE_BINDLESS_TEXTURES
			for (int i = 0; i < _materials[materialID]->NumberOfTextures(); i++)
			{
				int textureLoc = ShaderManager::GetManager()->GetTextureLocation(shaderID, i);
				ShaderManager::GetManager()->SetVariable(textureLoc, i);
			}
#endif
			return true;
		}
		return false;
	}
}


