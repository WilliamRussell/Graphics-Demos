#include "OGLFrameBuffer.h"
#include "TextureFactory.h"
#include <vector>

namespace Engine
{

	OGLFrameBuffer::OGLFrameBuffer(unsigned int width, unsigned int height) : FrameBuffer(width, height), _hFBO(-1), _hDepth(-1), _hDepthTex(0)
	{		
		glGenFramebuffers(1, &_hFBO);
	}

	void OGLFrameBuffer::CleanUp()
	{
		glDeleteFramebuffers(1, &_hFBO);

		if (_hDepth != -1)
			glDeleteRenderbuffers(1, &_hDepth);

		if (_hDepthTex)
		{
			delete _hDepthTex;
			_hDepth = 0;
		}

		for (int i = 0; i < _hRender.size(); i++)
			delete _hRender[i];
	}

	void OGLFrameBuffer::Apply() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, _hFBO);

		GLenum buffs[] = {	GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, 
							GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3, 
							GL_COLOR_ATTACHMENT4, GL_COLOR_ATTACHMENT5,
							GL_COLOR_ATTACHMENT6, GL_COLOR_ATTACHMENT7};

		
		glDrawBuffers(_attachments, buffs);
		glViewport(0, 0, _width, _height);
	}

	void OGLFrameBuffer::ClearColorBuffer(int bufferIndex, const Engine::Color& color) const
	{
		glClearBufferfv(GL_COLOR, bufferIndex, color.rgba());
	}

	void OGLFrameBuffer::ClearDepthBuffer(float depth) const
	{
		glClearBufferfv(GL_DEPTH, 0, &depth);
	}

	const Texture* OGLFrameBuffer::GetColorAttachmentsAsTexture(unsigned int attachment) const
	{
		if (attachment < _hRender.size())
			return _hRender[attachment];
		return 0;
	}

	const Texture* OGLFrameBuffer::GetDepthAttachmentAsTexture() const
	{
		/*if (!_hDepth)
		{
			if( _hDepthTex)		
				return _hDepthTex;
			return 0;
		}*/

		if( _hDepthTex)		
			return _hDepthTex;
		return 0;


		//if (!_hDepthTex)		
		//	_hDepthTex = new OGLTexture();

		//_hDepthTex->ApplyTexture(0);
		//glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 0, 0, _width, _height, 0);

		
				
	}

	void OGLFrameBuffer::Resize(unsigned int width, unsigned int height)
	{
		_width = width;
		_height = height;

		if (_hDepth != -1)
		{
			glBindRenderbuffer(GL_RENDERBUFFER, _hDepth);
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, _width, _height);
		}		
		else if (_hDepthTex)
		{
			_hDepthTex->ApplyTexture(0);
			glTexImage2D(_hDepthTex->GetTextureType(), 0, GL_DEPTH_COMPONENT24, _width, _height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, 0);
		}

		for (int i = 0; i < _hRender.size(); i++)
		{
			//_hRender[i]->ApplyTexture(0);
			
			_hRender[i]->Cleanup();
			_hRender[i]->CreateTexture();
			_hRender[i]->ApplyTexture(0);			
			
			switch (_format[i])
			{
			case BYTE_R:
				glTexStorage2D(_hRender[i]->GetTextureType(), 1, GL_R8, _width, _height);
				break;
			case FLOAT_RG:
				glTexStorage2D(_hRender[i]->GetTextureType(), 1, GL_RG32F, _width, _height);
				break;
			case FLOAT_RGBA:
				glTexStorage2D(_hRender[i]->GetTextureType(), 1, GL_RGBA32F, _width, _height);
				break;
			case BYTE_RGBA:				
				glTexStorage2D(_hRender[i]->GetTextureType(), 1, GL_RGBA8, _width, _height);
				break;
			case UIBYTE_R:				
				glTexStorage2D(_hRender[i]->GetTextureType(), 1, GL_R8UI, _width, _height);
				break;
			case CUBE_FLOAT_R:				
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_R32F, _width, _height, 0, GL_RED, GL_FLOAT, 0);
				glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_R32F, _width, _height, 0, GL_RED, GL_FLOAT, 0);
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_R32F, _width, _height, 0, GL_RED, GL_FLOAT, 0);
				glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_R32F, _width, _height, 0, GL_RED, GL_FLOAT, 0);
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_R32F, _width, _height, 0, GL_RED, GL_FLOAT, 0);
				glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_R32F, _width, _height, 0, GL_RED, GL_FLOAT, 0);

				glTexParameteri(_hRender[i]->GetTextureType(), GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
				break;
			case CUBE_FLOAT_RGBA:				
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGBA32F, _width, _height, 0, GL_RGBA, GL_FLOAT, 0);
				glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGBA32F, _width, _height, 0, GL_RGBA, GL_FLOAT, 0);
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGBA32F, _width, _height, 0, GL_RGBA, GL_FLOAT, 0);
				glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGBA32F, _width, _height, 0, GL_RGBA, GL_FLOAT, 0);
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGBA32F, _width, _height, 0, GL_RGBA, GL_FLOAT, 0);
				glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGBA32F, _width, _height, 0, GL_RGBA, GL_FLOAT, 0);

				glTexParameteri(_hRender[i]->GetTextureType(), GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
				break;
			}
			glTexParameterf(_hRender[i]->GetTextureType(), GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameterf(_hRender[i]->GetTextureType(), GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(_hRender[i]->GetTextureType(), GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(_hRender[i]->GetTextureType(), GL_TEXTURE_MIN_FILTER, GL_NEAREST);

			glBindFramebuffer(GL_FRAMEBUFFER, _hFBO);
			glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, _hRender[i]->GetOGLHandle(), 0);
		}
	}

	void OGLFrameBuffer::AddDepthBuffer()
	{
		if (_hDepthTex)
		{
			delete _hDepthTex;
			_hDepthTex = 0;
		}
		if (_hDepth != -1)
			glDeleteRenderbuffers(1, &_hDepth);
		glGenRenderbuffers(1, &_hDepth);

		glBindFramebuffer(GL_FRAMEBUFFER, _hFBO);
		glBindRenderbuffer(GL_RENDERBUFFER, _hDepth);

		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, _width, _height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _hDepth);	
	}

	void OGLFrameBuffer::AddTextureDepthBuffer()
	{
		if (_hDepth != -1)
		{
			glDeleteRenderbuffers(1, &_hDepth);
			_hDepth = -1;
		}
		if (_hDepthTex)
			delete _hDepthTex;

		OGLTexture *tempTexture = new OGLTexture();
		tempTexture->ApplyTexture(0);
		tempTexture->SetTextureType(GL_TEXTURE_2D);
		
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F,  _width, _height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);

		GLfloat col[] = {1.0f, 1.0f, 1.0f, 1.0f};
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, col);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);

		//glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE, GL_INTENSITY); 
		
		glBindFramebuffer(GL_FRAMEBUFFER, _hFBO);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, tempTexture->GetOGLHandle(), 0);		

		_hDepthTex = tempTexture;
	}

	void OGLFrameBuffer::AddCubeMapTextureDepthBuffer()
	{
		if (_hDepth != -1)
		{
			glDeleteRenderbuffers(1, &_hDepth);
			_hDepth = -1;
		}
		if (_hDepthTex)
			delete _hDepthTex;

		OGLTexture *tempTexture = new OGLTexture();
		tempTexture->SetTextureType(GL_TEXTURE_CUBE_MAP);
		tempTexture->ApplyTexture(0);
	

		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_DEPTH_COMPONENT24, _width, _height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, 0);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_DEPTH_COMPONENT24, _width, _height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, 0);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_DEPTH_COMPONENT24, _width, _height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, 0);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_DEPTH_COMPONENT24, _width, _height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, 0);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_DEPTH_COMPONENT24, _width, _height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, 0);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_DEPTH_COMPONENT24, _width, _height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, 0);		

		GLfloat col[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		glTexParameterfv(tempTexture->GetTextureType(), GL_TEXTURE_BORDER_COLOR, col);
		glTexParameteri(tempTexture->GetTextureType(), GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(tempTexture->GetTextureType(), GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		glTexParameteri(tempTexture->GetTextureType(), GL_TEXTURE_WRAP_R, GL_CLAMP_TO_BORDER);
		glTexParameteri(tempTexture->GetTextureType(), GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(tempTexture->GetTextureType(), GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		//glTexParameteri(tempTexture->GetTextureType(), GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);
		//glTexParameteri(tempTexture->GetTextureType(), GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
		//glTexParameteri(tempTexture->GetTextureType(), GL_TEXTURE_COMPARE_FUNC, GL_EQUAL);

		glBindFramebuffer(GL_FRAMEBUFFER, _hFBO);
		glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, tempTexture->GetOGLHandle(), 0);		

		_hDepthTex = tempTexture;
	}

	void OGLFrameBuffer::AddRenderBuffer(AttachmentFormat format)
	{
		OGLTexture *tempTexture = new OGLTexture();	
		
		switch (format)
		{
		case BYTE_R:
			tempTexture->SetTextureType(GL_TEXTURE_2D);
			tempTexture->ApplyTexture(0);
			glTexStorage2D(GL_TEXTURE_2D, 1, GL_R8, _width, _height);
			break;
		case FLOAT_R:
			tempTexture->SetTextureType(GL_TEXTURE_2D);
			tempTexture->ApplyTexture(0);
			glTexStorage2D(GL_TEXTURE_2D, 1, GL_R32F, _width, _height);
			break;
		case FLOAT_RG:
			tempTexture->SetTextureType(GL_TEXTURE_2D);
			tempTexture->ApplyTexture(0);
			glTexStorage2D(GL_TEXTURE_2D, 1, GL_RG32F, _width, _height);
			break;
		case FLOAT_RGBA:
			tempTexture->SetTextureType(GL_TEXTURE_2D);
			tempTexture->ApplyTexture(0);
			glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA32F, _width, _height);
			break;
		case BYTE_RGBA:
			tempTexture->SetTextureType(GL_TEXTURE_2D);
			tempTexture->ApplyTexture(0);
			glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, _width, _height);
			break;
		case UIBYTE_R:
			tempTexture->SetTextureType(GL_TEXTURE_2D);
			tempTexture->ApplyTexture(0);
			glTexStorage2D(GL_TEXTURE_2D, 1, GL_R8UI, _width, _height);
			break;
		case CUBE_FLOAT_R:
			tempTexture->SetTextureType(GL_TEXTURE_CUBE_MAP);
			tempTexture->ApplyTexture(0);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_R32F, _width, _height, 0, GL_RED, GL_FLOAT, 0);			
			glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_R32F, _width, _height, 0, GL_RED, GL_FLOAT, 0);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_R32F, _width, _height, 0, GL_RED, GL_FLOAT, 0);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_R32F, _width, _height, 0, GL_RED, GL_FLOAT, 0);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_R32F, _width, _height, 0, GL_RED, GL_FLOAT, 0);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_R32F, _width, _height, 0, GL_RED, GL_FLOAT, 0);
			glTexParameteri(tempTexture->GetTextureType(), GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);			
			break;
		case CUBE_FLOAT_RGBA:
			tempTexture->SetTextureType(GL_TEXTURE_CUBE_MAP);
			tempTexture->ApplyTexture(0);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGBA32F, _width, _height, 0, GL_RGBA, GL_FLOAT, 0);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGBA32F, _width, _height, 0, GL_RGBA, GL_FLOAT, 0);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGBA32F, _width, _height, 0, GL_RGBA, GL_FLOAT, 0);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGBA32F, _width, _height, 0, GL_RGBA, GL_FLOAT, 0);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGBA32F, _width, _height, 0, GL_RGBA, GL_FLOAT, 0);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGBA32F, _width, _height, 0, GL_RGBA, GL_FLOAT, 0);			
			glTexParameteri(tempTexture->GetTextureType(), GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
			break;
		}
		
		glTexParameteri(tempTexture->GetTextureType(), GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(tempTexture->GetTextureType(), GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(tempTexture->GetTextureType(), GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(tempTexture->GetTextureType(), GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		
		glBindFramebuffer(GL_FRAMEBUFFER, _hFBO);		
		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + _attachments, tempTexture->GetOGLHandle(), 0);			
		_format.push_back(format);
		_hRender.push_back(tempTexture);
		_attachments++;		
	}

	bool OGLFrameBuffer::CheckFBOCompleteness() const
	{
		return (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE) ?  true : false;
	}

	int OGLFrameBuffer::AttachTexture(Texture* texture)
	{
		OGLTexture* tempTex = static_cast<OGLTexture*> (texture);

		int attachmentPoint = _attachments;
		glBindFramebuffer(GL_FRAMEBUFFER, _hFBO);
		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + attachmentPoint, tempTex->GetOGLHandle(), 0);
		_attachments++;

		return attachmentPoint;
	}

	void OGLFrameBuffer::DetachTexture(unsigned int texture)
	{

	}
}