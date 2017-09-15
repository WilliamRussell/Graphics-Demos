#pragma once
#include "Model.h"
#include "Vector3f.h"
#include "Quaternion.h"
#include <vector>

namespace Engine
{
	class ModelManager
	{
	public:
		~ModelManager(){}
		static ModelManager* GetManager();

		bool CreateModels(const char* filename);
		int AddModel(Model* model);
		bool DeleteModel(int modelID);
		bool DeleteAllModels();

		int GetModelID(const char* modelName) const;
		const Model* GetModel(int modelID) const {return _models[modelID];}

		void DrawModel(int modelID) const;
	private:
		int _numOfModels;
		std::vector<Model*> _models;
		static ModelManager* _pManager;

		ModelManager() : _numOfModels(0) {}
		ModelManager(const ModelManager&);
		ModelManager& operator=(const ModelManager&);
	};
}