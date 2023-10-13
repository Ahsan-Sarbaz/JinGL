#pragma once
#include "Buffer.h"
#include "Shader.h"

class VertexInput
{
public:
	/**
	* creates a vertex input (Vertex Array Object)
	*/
	explicit VertexInput();

	/**
	* creates a vertex input based on the active attributes of the shader program
	* @param shader the shader to get the attributes information from
	*/
	explicit VertexInput(const ShaderProgram& shader);
	
	/**
	* destroys the underlying OpenGL handle
	*/
	~VertexInput();

	/**
	* increments the binding index so all the subsequent Add* call use the next binding point in the VAO
	*/
	void NextBinding();
	
	/**
	* adds a byte input attribute
	*/
	void AddByte();
	
	/**
	* adds a short input attribute
	*/
	void AddShort();
	
	/**
	* adds a int input attribute
	*/
	void AddInt();
	
	/**
	* adds a float input attribute
	*/
	void AddFloat();

	/**
	* adds a double input attribute
	*/
	void AddDouble();

	/**
	* adds a vec2 input attribute
	*/
	void AddVec2();

	/**
	* adds a vec3 input attribute
	*/
	void AddVec3();
	
	/**
	* adds a vec4 input attribute
	*/
	void AddVec4();

	/**
	* adds an input attribute of size and type
	* @param size of the input attribute (element count not size in bytes)
	* @param type of the input attribute
	*/
	void AddAttribute(int size, int type);

	/**
	* sets the vertex buffer to be used in the vertex stream for the shaders
	* @param buffer buffer to use
	* @param binding binding point of the buffer
	* @param stride stride of the buffer (in bytes)
	* @param offset offset into the buffer to use as a start address usually 0
	*/
	void SetVertexBuffer(const Buffer& buffer, int binding, int stride, int offset);

	/**
	* sets the index to be used
	* @param buffer buffer to use
	*/
	void SetIndexBuffer(const Buffer& buffer);

	/**
	* binds the vertex input to used in subsequent draw calls
	*/
	void Bind();
	
	/**
	* gets the id of underlying OpenGL handle
	* @returns id
	*/
	unsigned int GetID() { return id; }

private:
	unsigned int id;
	unsigned int offset;
	unsigned int binding;
	unsigned int index;
};