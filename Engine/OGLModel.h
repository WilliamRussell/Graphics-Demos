#pragma once
#include "Model.h"
#include <GL/glew.h>
namespace Engine
{
	class OGLModel : public Model
	{
	public:
		OGLModel();
		~OGLModel(){CleanUp();}
		void Draw() const;
		void DrawMesh(int meshIndex) const;
		bool LoadModelFromMemory(
			float scale,
			Vector3f *vertexData, 
			Vector3f *normalData, 
			Vector3f *binormalData, 
			Vector3f *tangentData, 
			Vector3f *texCoords,		
			unsigned int *indexData,
			unsigned int numOfIndices,
			unsigned int numOfVertices,
			int *meshIndicesRange,
			int numOfMeshes);		
		bool LoadWBF(const char* filename);		
		void CleanUp();
	private:		
		GLuint _vaoID;
		GLuint _vertexBufferID;
		GLuint _indicesBufferID;
		GLfloat* _vertexAttribData;
	};
}