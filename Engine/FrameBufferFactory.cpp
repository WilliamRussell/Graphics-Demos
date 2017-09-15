#include "FrameBufferFactory.h"
#include "Context.h"

namespace Engine
{
	FrameBuffer* FrameBufferFactory::CreateFrameBuffer(unsigned int width, unsigned int height, unsigned int flags, unsigned int colorAttachments, AttachmentFormat *formats)
	{		
		
		OGLFrameBuffer* returnBuffer = new OGLFrameBuffer(width, height);

		if (flags == TEXTURE_DEPTH_BUFFER)
			returnBuffer->AddTextureDepthBuffer();
		else if (flags == DEPTH_BUFFER)
			returnBuffer->AddDepthBuffer();
		else if (flags == CUBE_MAP_TEXTURE_DEPTH_BUFFER)
			returnBuffer->AddCubeMapTextureDepthBuffer();

		for (int i = 0; i < colorAttachments; i++)
			returnBuffer->AddRenderBuffer(formats[i]);
		if (!colorAttachments)
		{
			glDrawBuffer(GL_NONE);
			glReadBuffer(GL_NONE);
		}

		bool complete = returnBuffer->CheckFBOCompleteness();

		Context::GetCurrentContext()->ApplyDefaultFrameBuffer();

		if (complete)
			return static_cast<FrameBuffer*>(returnBuffer);
		else
			delete returnBuffer;
		return 0;
	}
}