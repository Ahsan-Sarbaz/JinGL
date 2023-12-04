#pragma once
#include <vector>
#include "Texture2D.h"

class Framebuffer
{
public:

	/**
	* creates the framebuffer (this actually does nothing the framebuffer is actually created at the first call to Resize)
	* @param width width of the framebuffer
	* @param height height of the framebuffer
	*/
	Framebuffer(int width, int height);

	/**
	* destroys the framebuffer and all the associated attachments
	*/
	~Framebuffer();

	/**
	* adds an attachment to the framebuffer
	* @param format pixel format the attachment is going to use 
	*	(do not use Depth/Stencil Format here to create depth/stencil attachment use AddDepthStencil instead)
	* @param draw do you want to draw to this attachment from fragment shader
	*/
	void AddAttachment(Format format, bool draw);

	/**
	* add a depth stencil attachment to the framebuffer there is only one this attachment at any time if you add
	* again it will delete the last one
	*/
	void AddDepthStencil();

	/**
	* resizes the framebuffer if the its called the first time it will actually create the framebuffer
	* on next calls with re-create all the attachments with the new size
	* @param width width of the framebuffer
	* @param height height of the framebuffer
	*/
	void Resize(int width, int height);

	/**
	* binds the framebuffer and sets the viewport to its size
	*/
	void Bind();

	/**
	* gets the id of underlying OpenGL handle
	* @returns id
	*/
	unsigned int GetID() const { return id; }
	
	/**
	* gets width of the framebuffer
	* @returns width
	*/
	int GetWidth() const { return width; }

	/**
	* gets height of the framebuffer
	* @returns height
	*/
	int GetHeight() const { return height; }

	/**
	* gets handles to attachments of the framebuffer
	* @returns attachments
	*/
	const std::vector<std::tuple<Texture2D*, bool>>& GetColorAttachments() const { return attachments; }

	/**
	* gets the attachments of the framebuffer
	* @returns attachments
	*/
	const Texture2D* GetDepthStencilAttachment() const { return depthStencilAttachment; }

	/**
	* clears all the attachments to default values
	*/
	void ClearAttachments();
	
	/**
	* clears the color attachments
	* @param color color value to clear the attachment
	*/
	void ClearColorAttachments(float color[4]);
	
	/**
	* clears the depth attachment
	* @param depth depth value to clear with
	* @param stencil stencil value to clear with
	*/
	void ClearDepthStencilAttachment(float depth, int stencil);
	
	/**
	* clears all the attachments and depth attachment
	* @param color color value to clear the attachment
	* @param depth depth value to clear with
	* @param stencil stencil value to clear with
	*/
	void ClearAttachments(float color[4], float depth, int stencil);

	/**
	* binds all the color attachments to texture units for use in shaders
	* the unit texture is attached to is based on its index
	*/
	void BindColorAttachments();

private:
	unsigned int id;
	int width, height;
	std::vector<std::tuple<Texture2D*, bool>> attachments;
	Texture2D* depthStencilAttachment;
};