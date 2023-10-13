#pragma once

class Buffer
{
public:
	/**
	* creates a buffer
	* @param size size of buffer to allocate
	* @param data pointer to cpu side data to upload data pointer can be null for dynamic buffers
	* @param dynamic true if you want to change its content later a combined vertex and element buffer 
	*	should also be marked dynamic since its data is uploaded later
	*/
	explicit Buffer(size_t size, void* data, bool dynamic);

	/**
	* Destroys the buffer and de-allocates all the memory
	* @note since the de-allocation is done by the driver we have to control over it
	*/
	~Buffer();

	/**
	* updates / sets the data of the buffer (if the buffe is dynamic only)
	* @param size size of data to upload
	* @param offset offset into buffer to upload the data to
	* @param data is the pointer to cpu size data to upload (cannot be null)
	*/
	void SubData(size_t size, size_t offset, void* data);

	/**
	* gets the id of underlying OpenGL handle
	* @returns id
	*/
	unsigned int GetID() const { return id; }

private:
	unsigned int id;
};
