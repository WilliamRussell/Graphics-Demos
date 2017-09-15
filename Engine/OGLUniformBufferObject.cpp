#include "OGLUniformBufferObject.h"
#include "OGLShader.h"
#include "MaterialManager.h"
#include <string>
#include <vector>
#include <iostream>

#include "ShaderManager.h"

namespace Engine
{
	OGLUniformBufferObject::OGLUniformBufferObject()
	{
		glGenBuffers(1, &_ubo);
	}

	OGLUniformBufferObject::~OGLUniformBufferObject()
	{
		glDeleteBuffers(1, &_ubo);
	}

	void OGLUniformBufferObject::CreateUniformBuffer()
	{		
		glBindBuffer(GL_UNIFORM_BUFFER, _ubo);		
		
		int numOfMaterials = MaterialManager::GetManager()->GetNumberOfMaterials();

		if (numOfMaterials < 1)
			return;

		int colorVals = MaterialManager::GetManager()->GetMaterial(0)->NumberOfColorProperties();
		int floatVals = MaterialManager::GetManager()->GetMaterial(0)->NumberOfFloatProperties();
		int textureVals = MaterialManager::GetManager()->GetMaterial(0)->NumberOfTextures();

#ifdef USE_BINDLESS_TEXTURES
		int numOfValues = RoundUp(textureVals * 2, 4) + RoundUp(colorVals * 4, 4) + RoundUp(floatVals, 4);		
#else
		int numOfValues = RoundUp(colorVals * 4, 4) + RoundUp(floatVals, 4);
#endif
		int sizeOfMaterialBuffer = numOfValues;
		//int padding = sizeOfMaterialBuffer - numOfValues;

		float *bufferData = new float[numOfMaterials*sizeOfMaterialBuffer];

		int bufferDataIndex = 0;

		for (int i = 0; i < numOfMaterials; i++)
		{
#ifdef USE_BINDLESS_TEXTURES
			for (int j = 0; j < textureVals; j++)
			{				
				GLuint64 handle = glGetTextureHandleARB(static_cast<const OGLTexture*>(MaterialManager::GetManager()->GetMaterial(i)->GetTexture(j))->GetOGLHandle());	
				glMakeTextureHandleResidentARB(handle);

				memcpy(&(bufferData[bufferDataIndex]), &handle, sizeof(GLuint64));
				bufferDataIndex += 2;
			}
			bufferDataIndex = RoundUp(bufferDataIndex, 4);
#endif
			for (int j = 0; j < colorVals; j++)
			{
				bufferData[bufferDataIndex++] = MaterialManager::GetManager()->GetMaterial(i)->GetColorProperty(j).rgba()[0];
				bufferData[bufferDataIndex++] = MaterialManager::GetManager()->GetMaterial(i)->GetColorProperty(j).rgba()[1];
				bufferData[bufferDataIndex++] = MaterialManager::GetManager()->GetMaterial(i)->GetColorProperty(j).rgba()[2];
				bufferData[bufferDataIndex++] = MaterialManager::GetManager()->GetMaterial(i)->GetColorProperty(j).rgba()[3];
			}
			bufferDataIndex = RoundUp(bufferDataIndex, 4);
			for (int j = 0; j < floatVals; j++)
			{
				bufferData[bufferDataIndex++] = MaterialManager::GetManager()->GetMaterial(i)->GetFloatProperty(j);				
			}

			bufferDataIndex = RoundUp(bufferDataIndex, 4);
		}		
		glBufferData(GL_UNIFORM_BUFFER, sizeof(float)*numOfMaterials*sizeOfMaterialBuffer, bufferData, GL_STATIC_DRAW);
		glBindBufferRange(GL_UNIFORM_BUFFER, 0, _ubo, 0, sizeof(float)*numOfMaterials*sizeOfMaterialBuffer);
		
		//glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}

	int OGLUniformBufferObject::RoundUp(int inputVal, int multiple) const
	{
		if (multiple == 0)
		{
			return inputVal;
		}

		int remainder = inputVal % multiple;
		if (remainder == 0)
		{
			return inputVal;
		}

		return inputVal + multiple - remainder;
	}
}