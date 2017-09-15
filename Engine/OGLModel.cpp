#include "OGLModel.h"
#include <iostream>

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

namespace Engine
{		
	OGLModel::OGLModel() : _vertexAttribData(0)
	{
		glGenVertexArrays(1, &_vaoID);
		glGenBuffers(1, &_vertexBufferID);
		glGenBuffers(1, &_indicesBufferID);
	}	

	bool OGLModel::LoadWBF(const char* filename)
	{
		if (!Model::LoadWBF(filename))
			return false;

		glBindVertexArray(_vaoID);

		glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * _numOfVertices * 14, _vertexBuffer, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indicesBufferID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * _numOfIndices, _indices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glEnableVertexAttribArray(3);
		glEnableVertexAttribArray(4);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 14, BUFFER_OFFSET(0));
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 14, BUFFER_OFFSET(12));
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 14, BUFFER_OFFSET(24));
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 14, BUFFER_OFFSET(36));
		glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 14, BUFFER_OFFSET(48));

		glBindVertexArray(0);

		return true;

	}

	void OGLModel::Draw() const
	{
		glBindVertexArray(_vaoID);		
		glDrawElements(GL_TRIANGLES, _numOfIndices, GL_UNSIGNED_INT, BUFFER_OFFSET(0));
		glBindVertexArray(0);
	}

	void OGLModel::DrawMesh(int meshIndex) const
	{
		int start = _meshIndicesRange[meshIndex * 2];		
		int count = _meshIndicesRange[meshIndex * 2 + 1];

		glBindVertexArray(_vaoID);		
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, BUFFER_OFFSET(start * sizeof(GL_UNSIGNED_INT)));
		glBindVertexArray(0);
	}
	void OGLModel::CleanUp()
	{	
		if (_vertexAttribData)
			delete[] _vertexAttribData;
		glDeleteBuffers(1, &_vertexBufferID);
		glDeleteBuffers(1, &_indicesBufferID);
	}
}