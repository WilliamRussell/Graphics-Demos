#include "ModelLoader.h"
#include <string>
#include <iostream>
#include <iomanip>
#include "Parser.h"

//#include <assimp/Importer.hpp>
//#include <assimp/scene.h>
//#include <assimp/postprocess.h>

namespace Engine
{
	bool LoadModel(const char* filename,
		float **vertexData,
		unsigned int **indexData,
		unsigned int **meshRangeData,
		unsigned int &numOfIndices,
		unsigned int &numOfVertices,
		unsigned int &numOfMeshes)
	{
		FILE *file = NULL;
		fopen_s(&file, filename, "rb");
		if (!file)
			return false;

		// check file header
		char header[4];
		fread_s(header, sizeof(header), sizeof(char), 4, file);
		if (strcmp(header, "WBF") != 0)
		{
			fclose(file);
			return false;
		}

		// get buffer sizes
		unsigned int vertexBufferSize, indicesBufferSize, meshRangeBufferSize = 0;
		fread_s(&vertexBufferSize, sizeof(vertexBufferSize), sizeof(vertexBufferSize), 1, file);
		fread_s(&indicesBufferSize, sizeof(indicesBufferSize), sizeof(indicesBufferSize), 1, file);
		fread_s(&meshRangeBufferSize, sizeof(meshRangeBufferSize), sizeof(meshRangeBufferSize), 1, file);

		// read vertex buffer
		float* vertexBuffer = new float[vertexBufferSize];
		fread_s(vertexBuffer, sizeof(float) * vertexBufferSize, sizeof(float), vertexBufferSize, file);

		// read indices buffer
		unsigned int* indicesBuffer = new unsigned int[indicesBufferSize];
		fread(indicesBuffer, sizeof(unsigned int), indicesBufferSize, file);

		// read meshRange buffer
		unsigned int* meshRangeBuffer = new unsigned int[meshRangeBufferSize];
		fread_s(meshRangeBuffer, sizeof(unsigned int) * meshRangeBufferSize, sizeof(unsigned int), meshRangeBufferSize, file);

		*vertexData = vertexBuffer;
		*indexData = indicesBuffer;
		*meshRangeData = meshRangeBuffer;

		numOfIndices = indicesBufferSize;
		numOfVertices = vertexBufferSize / 14;
		numOfMeshes = meshRangeBufferSize / 2;

		fclose(file);
		return true;
	}
}