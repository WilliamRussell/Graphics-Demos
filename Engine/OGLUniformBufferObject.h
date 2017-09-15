#pragma once
#include "OGLShader.h"

namespace Engine
{
	class OGLUniformBufferObject
	{
	public:
		OGLUniformBufferObject();
		~OGLUniformBufferObject();
		void CreateUniformBuffer();
	private:
		int RoundUp(int inputVal, int multiple) const;
		GLuint _ubo;
	};
}