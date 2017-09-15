#pragma once
#include "Color.h"
#include "Texture.h"

namespace Engine
{
	enum FBOFlags
	{
		NONE = 0,
		DEPTH_BUFFER = 1,
		TEXTURE_DEPTH_BUFFER = 2,
		CUBE_MAP_TEXTURE_DEPTH_BUFFER = 3
	};	

	class FrameBuffer
	{
	public:
		FrameBuffer(unsigned int width, unsigned int height) : _width(width), _height(height), _attachments(0) {}
		virtual ~FrameBuffer() {}

		virtual void Resize(unsigned int width, unsigned int height) = 0;
		virtual void Apply() const = 0;
		virtual void ClearColorBuffer(int bufferIndex, const Engine::Color& color) const = 0;
		virtual void ClearDepthBuffer(float depth) const = 0;
		virtual const Texture*  GetColorAttachmentsAsTexture(unsigned int attachment) const = 0;
		virtual const Texture*  GetDepthAttachmentAsTexture() const = 0;

		virtual int AttachTexture(Texture* texture) = 0;
		virtual void DetachTexture(unsigned int texture) = 0;

		unsigned int GetWidth() const { return _width; }
		unsigned int GetHeight() const { return _height; }
		unsigned int GetNumberOfAttachments() const { return _attachments; }
		virtual void CleanUp() = 0;
	protected:
		unsigned int _width;
		unsigned int _height;
		unsigned int _attachments;
	};
}