#include "Shader.h"
#include "GL.h"

ShaderProgram::ShaderProgram()
{
	id = glCreateProgram();
}

ShaderProgram::ShaderProgram(Shader* vs, Shader* fs)
{
	if(id == 0)
		id = glCreateProgram();
	AttachShader(vs);
	AttachShader(fs);
	char* buffer;
	if (!Link(&buffer, nullptr))
	{
		printf("SHADER LINK ERROR: %s", buffer);
	}
}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(id);
	uniforms.clear();
	attributes.clear();
}

void ShaderProgram::AttachShader(Shader* shader) 
{
	for (size_t i = 0; i < attachedShaders.size(); ++i)
	{
		if (attachedShaders[i]->GetType() == shader->GetType())
		{
			glDetachShader(id, attachedShaders[i]->GetId());
			delete attachedShaders[i];
			attachedShaders[i] = shader;
			glAttachShader(id, shader->GetId());
			return;
		}
	}

	attachedShaders.push_back(shader);
	glAttachShader(id, shader->GetId());
}

bool ShaderProgram::Link(char** log, size_t* size)
{
	glLinkProgram(id);

	int status;
	glGetProgramiv(id, GL_LINK_STATUS, &status);
	if (status != GL_TRUE)
	{
		if (log != nullptr)
		{
			int infoLogLen;
			glGetProgramiv(id, GL_INFO_LOG_LENGTH, &infoLogLen);
			(*log) = new char[infoLogLen + 1];
			glGetProgramInfoLog(id, infoLogLen, 0, (*log));
			(*log)[infoLogLen] = 0;
			if (size != nullptr) *size = infoLogLen;
		}
		isValid = false;
		return false;
	}

	isValid = true;

	GetUniformsInfo();
	GetAttributesInfo();
	return true;
}

void ShaderProgram::GetUniformsInfo()
{
	if (isValid)
	{
		uniforms.clear();
		int count = 0;
		glGetProgramiv(id, GL_ACTIVE_UNIFORMS, &count);

		for (int i = 0; i < count; ++i)
		{
			char name[255];
			int size;
			unsigned int type;
			glGetActiveUniform(id, i, 255, 0, &size, &type, name);
			auto location = glGetUniformLocation(id, name);
			ShaderUniform uniform = {
				.location = location,
				.name = std::string(name),
				.type = ShaderUniformType(type),
				.size = size
			};

			uniforms.push_back(uniform);
		}
	}
}

void ShaderProgram::GetAttributesInfo()
{
	if (isValid)
	{
		attributes.clear();
		int count = 0;
		glGetProgramiv(id, GL_ACTIVE_ATTRIBUTES, &count);

		for (int i = 0; i < count; ++i)
		{
			char name[255];
			int size;
			unsigned int type;
			glGetActiveAttrib(id, i, 255, 0, &size, &type, name);
			auto location = glGetAttribLocation(id, name);
			ShaderAttribute attribute = {
				.location = location,
				.name = std::string(name),
				.type = ShaderAttributeType(type),
				.size = size
			};

			attributes.push_back(attribute);
		}
	}
}

void ShaderProgram::Bind() const
{
	glUseProgram(id);
}

int ShaderProgram::GetUniformLocation(const char* name) const
{
	for (const auto& uniform : uniforms) {
		if (uniform.name == std::string(name))
		{
			return uniform.location;
		}
	}

	return -1;
}

void ShaderProgram::UniformInt(const char* name, int value) const
{
	auto location = GetUniformLocation(name);
	if (location >= 0)
	{
		glProgramUniform1i(id, location, value);
	}
}

void ShaderProgram::UniformInt64(const char* name, uint64_t value) const
{
	auto location = GetUniformLocation(name);
	if (location >= 0)
	{
		glProgramUniformHandleui64ARB(id, location, value);
	}
}

void ShaderProgram::UniformFloat(const char* name, float value) const
{
	auto location = GetUniformLocation(name);
	if (location >= 0)
	{
		glProgramUniform1f(id, location, value);
	}
}

void ShaderProgram::UniformVec2(const char* name, float* value) const
{
	auto location = GetUniformLocation(name);
	if (location >= 0)
	{
		glProgramUniform2fv(id, location, 1, value);
	}
}

void ShaderProgram::UniformUVec2(const char* name, unsigned int* value) const
{
	auto location = GetUniformLocation(name);
	if (location >= 0)
	{
		glProgramUniform2uiv(id, location, 1, (unsigned int*)value);
	}
}

void ShaderProgram::UniformVec3(const char* name, float* value) const
{
	auto location = GetUniformLocation(name);
	if (location >= 0)
	{
		glProgramUniform3fv(id, location, 1, value);
	}
}

void ShaderProgram::UniformVec4(const char* name, float* value) const
{
	auto location = GetUniformLocation(name);
	if (location >= 0)
	{
		glProgramUniform4fv(id, location, 1, value);
	}
}

void ShaderProgram::UniformMat2(const char* name, float* value) const
{
	auto location = GetUniformLocation(name);
	if (location >= 0)
	{
		glProgramUniformMatrix2fv(id, location, 1, false, value);
	}
}

void ShaderProgram::UniformMat3(const char* name, float* value) const
{
	auto location = GetUniformLocation(name);
	if (location >= 0)
	{
		glProgramUniformMatrix3fv(id, location, 1, false, value);
	}
}

void ShaderProgram::UniformMat4(const char* name, float* value) const
{
	auto location = GetUniformLocation(name);
	if (location >= 0)
	{
		glProgramUniformMatrix4fv(id, location, 1, false, value);
	}
}

void ShaderProgram::UniformIntArray(const char* name, int count, int* value) const
{
	auto location = GetUniformLocation(name);
	if (location >= 0)
	{
		glProgramUniform1iv(id, location, count, value);
	}
}

void ShaderProgram::UniformFloatArray(const char* name, int count, float* value) const
{
	auto location = GetUniformLocation(name);
	if (location >= 0)
	{
		glProgramUniform1fv(id, location, count, value);
	}
}

void ShaderProgram::UniformVec2Array(const char* name, int count, float* value) const
{
	auto location = GetUniformLocation(name);
	if (location >= 0)
	{
		glProgramUniform2fv(id, location, count, value);
	}
}

void ShaderProgram::UniformVec3Array(const char* name, int count, float* value) const
{
	auto location = GetUniformLocation(name);
	if (location >= 0)
	{
		glProgramUniform3fv(id, location, count, value);
	}
}

void ShaderProgram::UniformMat2Array(const char* name, int count, float* value) const
{
	auto location = GetUniformLocation(name);
	if (location >= 0)
	{
		glProgramUniformMatrix2fv(id, location, count, false, value);
	}
}

void ShaderProgram::UniformMat3Array(const char* name, int count, float* value) const
{
	auto location = GetUniformLocation(name);
	if (location >= 0)
	{
		glProgramUniformMatrix3fv(id, location, count, false, value);
	}
}

void ShaderProgram::UniformMat4Array(const char* name, int count, float* value) const
{
	auto location = GetUniformLocation(name);
	if (location >= 0)
	{
		glProgramUniformMatrix4fv(id, location, count, false, value);
	}
}

Shader::Shader(ShaderType type, const std::string& source)
	:type(type)
{
	id = glCreateShader(GLenum(type));

	const char* src = source.c_str();
	glShaderSource(id, 1, &src, 0);
	glCompileShader(id);

	int status;
	glGetShaderiv(id, GL_COMPILE_STATUS, &status);
	if (status != GL_TRUE)
	{
		int infoLogLen;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &infoLogLen);
		auto log = new char[infoLogLen + 1];
		glGetShaderInfoLog(id, infoLogLen, 0, log);
		log[infoLogLen] = 0;
		// TODO : add a proper console for this
		printf("Shader Error : %s\n", log);
		delete[] log;
	}
}

Shader::~Shader()
{
	glDeleteShader(id);
}
