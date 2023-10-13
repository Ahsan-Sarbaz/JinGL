#include "Buffer.h"
#include "GL.h"

Buffer::Buffer(size_t size, void* data, bool dynamic)
{
	glCreateBuffers(1, &id);
	int flags = 0;
	if (dynamic) flags |= GL_DYNAMIC_STORAGE_BIT;
	glNamedBufferStorage(id, size, data, flags);
}

Buffer::~Buffer()
{
	glDeleteBuffers(1, &id);
}

void Buffer::SubData(size_t size, size_t offset, void* data)
{
	glNamedBufferSubData(id, offset, size, data);
}
