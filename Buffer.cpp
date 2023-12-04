#include "Buffer.h"
#include "GL.h"

Buffer::Buffer(size_t size, void* data, bool dynamic)
	:Buffer(size, data, dynamic, false, false)
{ }

Buffer::Buffer(size_t size, void* data, bool dynamic, bool cpu_write, bool cpu_read)
{
	glCreateBuffers(1, &id);
	int flags = 0;
	if (dynamic) flags |= GL_DYNAMIC_STORAGE_BIT;
	if (cpu_write) flags |= GL_MAP_WRITE_BIT;
	if (cpu_read) flags |= GL_MAP_READ_BIT;
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

void* Buffer::MapRead()
{
	return glMapNamedBuffer(id, GL_READ_ONLY);
}

void* Buffer::MapWrite()
{
	return glMapNamedBuffer(id, GL_WRITE_ONLY);
}

void* Buffer::MapReadWrite()
{
	return glMapNamedBuffer(id, GL_READ_WRITE);
}

void Buffer::Unmap()
{
	glUnmapNamedBuffer(id);
}

void Buffer::BindAsSSBO(int index)
{
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, index, id);
}
