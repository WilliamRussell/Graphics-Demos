#include "ModelManager.h"
#include "OGLModel.h"
#include "ImportFlags.h"
#include <fstream>
#include "Parser.h"

namespace Engine
{
	ModelManager* ModelManager::_pManager = 0;

	ModelManager* ModelManager::GetManager()
	{
		if (!_pManager)
			_pManager = new ModelManager();
		return _pManager;
	}

	int ModelManager::AddModel(Model* model)
	{
		_models.push_back(model);
		_numOfModels++;
		return _numOfModels - 1;
	}

	bool ModelManager::CreateModels(const char* filename)
	{
		std::ifstream filein(filename);

		// check file opened correctly
		if (!filein)
			return false;

		std::string word;		
		while(filein >> word)
		{
			if (word.compare("model") == 0)
			{
				// read the next 
				filein >> word;
				if (word.compare("{") == 0)
				{
					std::string modelName, modelFile;
					unsigned int importFlags = 0;
					float scale = 1.f;
					
					while((word.compare("}") != 0) && (filein >> word))
					{
						if (word.compare("name") == 0)
						{											
							filein >> modelName;
							continue;
						}
						if (word.compare("file") == 0)
						{							
							filein >> modelFile;
							continue;
						}
						if (word.compare("scale") == 0)
						{
							std::string stringScale;
							filein >> stringScale;
							scale = ParseFloat(stringScale);
						}
						if (word.compare("FLAG_FLIP_UV") == 0)
						{
							//importFlags |= IMPORT_FLAG_FLIP_UV;
						}
					}	
					Model* newModel = new OGLModel();
					newModel->SetModelName(modelName.data());

					if (!newModel->LoadWBF(modelFile.c_str()))
					{
						delete newModel;
						continue;
					}
					
					_models.push_back(newModel);
					_numOfModels++;
					continue;										
				}
			}
		}
		filein.close();
		if (_numOfModels)
			return true;
		return false;
	}

	int ModelManager::GetModelID(const char* modelName) const
	{
		for (int i = 0; i < _numOfModels; i++)
		{			
			if (!strcmp(_models[i]->GetModelName(), modelName))
			{
				return i;
			}		
		}
		return 0;
	}

	bool ModelManager::DeleteModel(int modelID)
	{
		if (_models[modelID])
			delete _models[modelID];
		_models[modelID] = 0;
		return true;
	}

	void ModelManager::DrawModel(int modelID) const
	{
		_models[modelID]->Draw();
	}
}