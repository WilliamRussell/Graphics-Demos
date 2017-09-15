#include "OGLText.h"
#include "ShaderManager.h"
#include "OGLTexture.h"
#include <string.h>
#define BUFFER_OFFSET(i) ((char *)NULL + (i))

namespace Engine
{
	Text* Text::_pText = 0;

	Text* Text::GetManager()
	{
		if (!_pText)
			_pText = new OGLText();
		return _pText;
	}

	OGLText::OGLText()
	{
		_positionTransform.LoadIdentity();
		_textureTransform.LoadIdentity();
		InitalizeOGLText();
	}

	OGLText::~OGLText()
	{
		glDeleteBuffers(1, &_vertexBufferID);
		glDeleteBuffers(1, &_indicesBufferID);
	}

	void OGLText::PrintString(const Camera &camera, const Vector3f &position, float scale, const char* string) const
	{
		//apply texture
		_pTexture->ApplyTexture(0);
		//initalize matrices
		_positionTransform[12] = position.getX();
		_positionTransform[13] = position.getY();
		_positionTransform[14] = position.getZ();

		_positionTransform[0] = scale;
		_positionTransform[5] = scale;
		_positionTransform[10] = scale;	

		//initalize shader variables
		int shaderID = ShaderManager::GetManager()->GetActiveShaderID();
		int texMatLoc = ShaderManager::GetManager()->GetVariableLocation(shaderID, "textureMat");
		
		camera.ApplyCameraMatricesToActiveShader(_positionTransform);

		//bind array and index buffers
		glBindVertexArray(_vaoID);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		for (int i = 0; i < static_cast<int>(strlen(string)); i++)
		{
			char character = string[i] - 32;		

			float texX = (static_cast<float>(character % 16)) / 16.f;			
			float texY = (static_cast<float>(character / 16)) / 16.f +0.0625f;

			_textureTransform[6] = texX;
			_textureTransform[7] = texY;

			_positionTransform[12] += scale*2;
			camera.ApplyCameraMatricesToActiveShader(_positionTransform);

			ShaderManager::GetManager()->SetVariable(texMatLoc, _textureTransform);
			
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, BUFFER_OFFSET(0));			
		}
		glDisable(GL_BLEND);

		glBindVertexArray(0);			
	}

	bool OGLText::LoadCharacterSheet(const char* filename)
	{
		if (_pTexture)
			delete _pTexture;
		_pTexture = new OGLTexture(filename);
		return true;
	}

	void OGLText::InitalizeOGLText()
	{		
		glGenVertexArrays(1, &_vaoID);
		glGenBuffers(1, &_vertexBufferID);
		glGenBuffers(1, &_indicesBufferID);		
			
		float vertexArrayData[] = 		
		{
			-1.f, -1.f, 0.1f,	/*vertex*/
			+1.f, -1.f, 0.1f,	/*vertex*/
			+1.f, +1.f, 0.1f,	/*vertex*/
			-1.f, +1.f, 0.1f,	/*vertex*/ 

			0.f, 1.0f,			/*texcoord*/
			0.0625f, 1.0f,			/*texcoord*/
			0.0625f, 1.f-0.06f,			/*texcoord*/
			0.f, 1.f-0.06f			/*texcoord*/
		};
		glBindVertexArray(_vaoID);

		glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferID);	
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 20, vertexArrayData, GL_STATIC_DRAW);
		
		unsigned char indicesArrayData[] = {0,1,2,2,3,0};
		indicesArrayData[0] = 0;
		indicesArrayData[1] = 1;
		indicesArrayData[2] = 2;
		indicesArrayData[3] = 2;
		indicesArrayData[4] = 3;
		indicesArrayData[5] = 0;

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indicesBufferID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned char)*6, indicesArrayData, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(4);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
		glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(48));

		glBindVertexArray(0);
	}
}