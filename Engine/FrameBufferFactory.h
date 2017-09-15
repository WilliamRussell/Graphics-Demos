#pragma once
#include "OGLFrameBuffer.h"

namespace Engine
{
	class FrameBufferFactory
	{
	public:
		static FrameBuffer* CreateFrameBuffer(unsigned int width, unsigned int height, unsigned int flags, unsigned int colorAttachments, AttachmentFormat *formats);
	};
}