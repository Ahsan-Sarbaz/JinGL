#include "Framebuffer.h"
#include "GL.h"

Framebuffer::Framebuffer(int width, int height)
	:id(0), width(width), height(height), depthStencilAttachment(nullptr)
{
}

Framebuffer::~Framebuffer()
{
	glDeleteFramebuffers(1, &id);
	for (auto &[texture, _ ]: attachments)
		delete texture;
	attachments.clear();

	delete depthStencilAttachment;
}

void Framebuffer::AddAttachment(Format format, bool draw)
{
	attachments.push_back({ new Texture2D(width, height, format), draw });
}

void Framebuffer::AddDepthStencil()
{
	if (depthStencilAttachment)
		delete depthStencilAttachment;

	depthStencilAttachment = new Texture2D(width, height, Format::D24S8);
}

void Framebuffer::Resize(int width, int height)
{
	bool actualResize = id > 0;

	this->width = width;
	this->height = height;

	if (actualResize)
	{
	
		std::vector<std::tuple<Format, bool>> attachmentFormats;

		auto colorAttachmentsCount = attachments.size();

		for (int i = 0; i < (int)attachments.size(); i++)
		{
			auto &[texture, draw] = attachments[i];

			attachmentFormats.push_back({ texture->GetFormat(), draw });
			delete texture;
		}

		attachments.clear();
		for (int i = 0; i < (int)colorAttachmentsCount; i++)
		{
			auto& [format, draw] = attachmentFormats[i];

			AddAttachment(format, draw);
		}
	}
	else
	{
		glCreateFramebuffers(1, &id);
	}

	std::vector<GLenum> drawAttachments;

	for (int i = 0; i < (int)attachments.size(); i++)
	{
		auto& [texture, draw] = attachments[i];
		glNamedFramebufferTexture(id, GL_COLOR_ATTACHMENT0 + i, texture->GetID(), 0);
		if (draw) drawAttachments.push_back(GL_COLOR_ATTACHMENT0 + i);
	}

	if (!drawAttachments.empty())
	{
		glNamedFramebufferDrawBuffers(id, (GLsizei)drawAttachments.size(), drawAttachments.data());
	}

	if (depthStencilAttachment != nullptr)
	{
		if(actualResize)
			AddDepthStencil();
		glNamedFramebufferTexture(id, GL_DEPTH_STENCIL_ATTACHMENT, depthStencilAttachment->GetID(), 0);
	}

	if (glCheckNamedFramebufferStatus(id, GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		printf("Framebuffer is not complete!\n");
}

void Framebuffer::Bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, id);
	glViewport(0, 0, width, height);
}

void Framebuffer::ClearColorAttachments(float color[4])
{
	for (int i = 0; i < (int)attachments.size(); i++)
		glClearNamedFramebufferfv(id, GL_COLOR, i, color);
}

void Framebuffer::ClearDepthStencilAttachment(float depth, int stencil)
{
	glClearNamedFramebufferfi(id, GL_DEPTH_STENCIL, 0, depth, stencil);
}

void Framebuffer::ClearAttachments()
{
	float color[4] = { 0, 0, 0, 1 };
	ClearAttachments(color, 1.0f, 1);
}

void Framebuffer::ClearAttachments(float color[4], float depth, int stencil)
{
	ClearColorAttachments(color);
	ClearDepthStencilAttachment(depth, stencil);
}

void Framebuffer::BindColorAttachments()
{
	for (int i = 0; i < (int)attachments.size(); i++)
	{
		auto& [texture, _] = attachments[i];
		texture->Bind(i);
	}
}
