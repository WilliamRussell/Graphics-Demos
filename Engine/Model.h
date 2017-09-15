#pragma once
#include "Vector3f.h"
#include "Quaternion.h"
#include <string>
#include <vector>

namespace Engine
{
	class Model
	{
	public:
		Model();
		virtual ~Model();	

		virtual bool LoadWBF(const char* filename);

		virtual void Draw() const = 0;
		virtual void DrawMesh(int meshIndex) const = 0;

		void SetModelName(const char* modelName) {_modelName = modelName;}
		const char* GetModelName() const {return _modelName.data();}

		int GetNumberOfMeshes() const { return _numOfMeshes; }

	protected:
		std::string _modelName;

		unsigned int* _indices;
		unsigned int _numOfIndices;
		unsigned int _numOfVertices;

		float *_vertexBuffer;

		unsigned int _numOfMeshes;
		unsigned int *_meshIndicesRange;
	};
}