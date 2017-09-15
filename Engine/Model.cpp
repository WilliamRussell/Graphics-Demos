#include "Model.h"
#include "ModelLoader.h"


namespace Engine
{
	Model::Model() : _vertexBuffer(0), _indices(0), _meshIndicesRange(0)
	{}

	Model::~Model()
	{
		if (_vertexBuffer)
			delete[] _vertexBuffer;
		if (_indices)
			delete[] _indices;
		if (_meshIndicesRange)
			delete[] _meshIndicesRange;
	}	

	bool Model::LoadWBF(const char* filename)
	{
		return LoadModel(filename, &_vertexBuffer, &_indices, &_meshIndicesRange, _numOfIndices, _numOfVertices, _numOfMeshes);
	}
}