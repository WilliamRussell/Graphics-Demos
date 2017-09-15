#pragma once
#include <fstream>
#include "Vector3f.h"

namespace Engine
{
	bool LoadModel(const char* filename, 
				   float **vertexData, 
				   unsigned int **indexData, 
				   unsigned int **meshRangeData, 
				   unsigned int &numOfIndices,
				   unsigned int &numOfVertices,
				   unsigned int &numOfMeshes);	
}