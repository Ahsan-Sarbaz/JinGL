#include "Shader.h"
#include "GL.h"

ShaderProgram::ShaderProgram()
{
	id = glCreateProgram();
}

ShaderProgram::ShaderProgram(const Shader& vs, const Shader& fs)
{
	if(id == 0)
		id = glCreateProgram();
	AttachShader(vs);
	AttachShader(fs);
	Link();
}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(id);
	uniforms.clear();
	attributes.clear();
}

void ShaderProgram::AttachShader(const Shader& shader) 
{
	glAttachShader(id, shader.GetId());
}

bool ShaderProgram::Link()
{
	glLinkProgram(id);

	int status;
	glGetProgramiv(id, GL_LINK_STATUS, &status);
	if (status != GL_TRUE)
	{
		int infoLogLen;
		glGetProgramiv(id, GL_INFO_LOG_LENGTH, &infoLogLen);
		auto log = new char[infoLogLen + 1];
		glGetProgramInfoLog(id, infoLogLen, 0, log);
		log[infoLogLen] = 0;
		// TODO : add a proper console for this
		printf("Program Error : %s\n", log);
		delete[] log;
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

Shader::Shader(ShaderType type, const std::string& source)
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
