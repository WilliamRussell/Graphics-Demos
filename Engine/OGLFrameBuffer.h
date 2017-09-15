#pragma once 
#include "FrameBuffer.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "OGLTexture.h"
#include <vector>

class Texture;

namespace Engine
{
	class OGLFrameBuffer : public FrameBuffer
	{
	public:	

		void Resize(unsigned int width, unsigned int height);
		void Apply() const;
		void CleanUp();

		void ClearColorBuffer(int bufferIndex, const Engine::Color& color) const;
		void ClearDepthBuffer(float depth) const;

		const Texture* GetColorAttachmentsAsTexture(unsigned int attachment) const;
		const Texture* GetDepthAttachmentAsTexture() const;

		int AttachTexture(Texture* texture);
		void DetachTexture(unsigned int texture);

	private:
		OGLFrameBuffer(unsigned int width, unsigned int height);
		~OGLFrameBuffer() {CleanUp();}

		OGLFrameBuffer(const OGLFrameBuffer*);
		OGLFrameBuffer& operator=(const OGLFrameBuffer&);

		void AddRenderBuffer(AttachmentFormat format);
		void AddDepthBuffer();
		void AddTextureDepthBuffer();
		void AddCubeMapTextureDepthBuffer();

		bool CheckFBOCompleteness() const;

		GLuint _hFBO, _hDepth;
		mutable OGLTexture* _hDepthTex;
		std::vector<OGLTexture*> _hRender;
		std::vector<AttachmentFormat> _format;

		friend class FrameBufferFactory; // this class can only be instantiated from a FrameBufferFactory
	};
}