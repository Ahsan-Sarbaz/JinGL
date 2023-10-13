#include "VertexInput.h"
#include "GL.h"

VertexInput::VertexInput()
	:offset(0), binding(0), index(0)
{
	glCreateVertexArrays(1, &id);
	offset = 0;
	binding = 0;
	index = 0;
}

VertexInput::VertexInput(const ShaderProgram& shader)
	:offset(0), binding(0), index(0)
{
	glCreateVertexArrays(1, &id);

	for (const auto& attribute : shader.GetAttributes())
	{
		switch (attribute.type)
		{
			case ShaderAttributeType::Float:	AddAttribute(1, GL_FLOAT); break;
			case ShaderAttributeType::Vec2:		AddAttribute(2, GL_FLOAT); break;
			case ShaderAttributeType::Vec3:		AddAttribute(3, GL_FLOAT); break;
			case ShaderAttributeType::Vec4:		AddAttribute(4, GL_FLOAT); break;
			case ShaderAttributeType::Mat2:		AddAttribute(2 * 2, GL_FLOAT); break;
			case ShaderAttributeType::Mat3:		AddAttribute(3 * 3, GL_FLOAT); break;
			case ShaderAttributeType::Mat4:		AddAttribute(4 * 4, GL_FLOAT); break;
			case ShaderAttributeType::Mat2x3:	AddAttribute(2 * 3, GL_FLOAT); break;
			case ShaderAttributeType::Mat2x4:	AddAttribute(2 * 4, GL_FLOAT); break;
			case ShaderAttributeType::Mat3x2:	AddAttribute(3 * 2, GL_FLOAT); break;
			case ShaderAttributeType::Mat3x4:	AddAttribute(3 * 4, GL_FLOAT); break;
			case ShaderAttributeType::Mat4x2:	AddAttribute(4 * 2, GL_FLOAT); break;
			case ShaderAttributeType::Mat4x3:	AddAttribute(4 * 3, GL_FLOAT); break;
			case ShaderAttributeType::Int:		AddAttribute(1, GL_INT); break;
			case ShaderAttributeType::IVec2:	AddAttribute(2, GL_INT); break;
			case ShaderAttributeType::IVec3:	AddAttribute(3, GL_INT); break;
			case ShaderAttributeType::IVec4:	AddAttribute(4, GL_INT); break;
			case ShaderAttributeType::UInt:		AddAttribute(1, GL_UNSIGNED_INT); break;
			case ShaderAttributeType::UIVec2:	AddAttribute(2, GL_UNSIGNED_INT);break;
			case ShaderAttributeType::UIVec3:	AddAttribute(3, GL_UNSIGNED_INT);break;
			case ShaderAttributeType::UIVec4:	AddAttribute(4, GL_UNSIGNED_INT);break;
			case ShaderAttributeType::Double:	AddAttribute(1, GL_DOUBLE); break;
			case ShaderAttributeType::DVec2:	AddAttribute(2, GL_DOUBLE); break;
			case ShaderAttributeType::DVec3:	AddAttribute(3, GL_DOUBLE); break;
			case ShaderAttributeType::DVec4:	AddAttribute(4, GL_DOUBLE); break;
			case ShaderAttributeType::DMat2:	AddAttribute(2 * 2, GL_DOUBLE); break;
			case ShaderAttributeType::DMat3:	AddAttribute(3 * 3, GL_DOUBLE); break;
			case ShaderAttributeType::DMat4:	AddAttribute(4 * 4, GL_DOUBLE); break;
			case ShaderAttributeType::DMat2x3:	AddAttribute(2 * 3, GL_DOUBLE); break;
			case ShaderAttributeType::DMat2x4:	AddAttribute(2 * 4, GL_DOUBLE); break;
			case ShaderAttributeType::DMat3x2:	AddAttribute(3 * 2, GL_DOUBLE); break;
			case ShaderAttributeType::DMat3x4:	AddAttribute(3 * 4, GL_DOUBLE); break;
			case ShaderAttributeType::DMat4x2:	AddAttribute(4 * 2, GL_DOUBLE); break;
			case ShaderAttributeType::DMat4x3:	AddAttribute(4 * 3, GL_DOUBLE); break;
		}
	}
}

VertexInput::~VertexInput()
{
	glDeleteVertexArrays(1, &id);
}

void VertexInput::NextBinding()
{
	offset = 0;
	index = 0;
	binding++;
}

void VertexInput::AddByte()
{
	AddAttribute(1, GL_BYTE);
}

void VertexInput::AddShort()
{
	AddAttribute(1, GL_SHORT);
}

void VertexInput::AddInt()
{
	AddAttribute(1, GL_INT);
}

void VertexInput::AddFloat()
{
	AddAttribute(1, GL_FLOAT);
}

void VertexInput::AddDouble()
{
	AddAttribute(1, GL_DOUBLE);
}

void VertexInput::AddVec2()
{
	AddAttribute(2, GL_FLOAT);
}

void VertexInput::AddVec3()
{
	AddAttribute(3, GL_FLOAT);
}

void VertexInput::AddVec4()
{
	AddAttribute(4, GL_FLOAT);
}

void VertexInput::AddAttribute(int size, int type)
{
	glVertexArrayAttribBinding(id, index, binding);
	if (type == GL_DOUBLE)
	{
		glVertexArrayAttribLFormat(id, index, size, type, offset);
	}
	else
	{
		glVertexArrayAttribFormat(id, index, size, type, false, offset);
	}

	glEnableVertexArrayAttrib(id, index);

	int element_size = 0;
	switch (type)
	{
	case GL_BYTE: element_size = sizeof(GLbyte); break;
	case GL_SHORT: element_size = sizeof(GLshort); break;
	case GL_FIXED: element_size = sizeof(GLfixed); break;
	case GL_FLOAT: element_size = sizeof(GLfloat); break;
	case GL_HALF_FLOAT: element_size = sizeof(GLhalf); break;
	case GL_DOUBLE: element_size = sizeof(GLdouble); break;
	case GL_INT: element_size = sizeof(GLint); break;
	case GL_UNSIGNED_BYTE: element_size = sizeof(GLubyte); break;
	case GL_UNSIGNED_SHORT: element_size = sizeof(GLushort); break;
	case GL_UNSIGNED_INT: element_size = sizeof(GLuint); break;
	case GL_INT_2_10_10_10_REV: element_size = sizeof(GLuint); break;
	case GL_UNSIGNED_INT_10F_11F_11F_REV: element_size = sizeof(GLuint); break;
	}

	offset += size * element_size;
	index++;

}

void VertexInput::SetVertexBuffer(const Buffer& buffer, int binding, int stride, int offset)
{
	glVertexArrayVertexBuffer(id, binding, buffer.GetID(), offset, stride);
}

void VertexInput::SetIndexBuffer(const Buffer& buffer)
{
	glVertexArrayElementBuffer(id, buffer.GetID());
}

void VertexInput::Bind()
{
	glBindVertexArray(id);
}