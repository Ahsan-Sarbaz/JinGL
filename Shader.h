#pragma once
#include <stdint.h>
#include <vector>
#include <string>

enum class ShaderUniformType : int {
	Float = 0x1406,
	Int = 0x1404,
	Vec2 = 0x8B50,
	Vec3 = 0x8B51,
	Vec4 = 0x8B52,
	Mat2 = 0x8B5A,
	Mat3 = 0x8B5B,
	Mat4 = 0x8B5C,
	Sampler2D = 0x8B5E,
};

enum class ShaderAttributeType : int {
	Float = 0x1406,
	Vec2 = 0x8B50,
	Vec3 = 0x8B51,
	Vec4 = 0x8B52,
	Mat2 = 0x8B5A,
	Mat3 = 0x8B5B,
	Mat4 = 0x8B5C,
	Mat2x3 = 0x8B65,
	Mat2x4 = 0x8B66,
	Mat3x2 = 0x8B67,
	Mat3x4 = 0x8B68,
	Mat4x2 = 0x8B69,
	Mat4x3 = 0x8B6A,
	Int = 0x1404,
	IVec2 = 0x8B53,
	IVec3 = 0x8B54,
	IVec4 = 0x8B55,
	UInt = 0x1405,
	UIVec2 = 0x8DC6,
	UIVec3 = 0x8DC7,
	UIVec4 = 0x8DC8,
	Double = 0x140A,
	DVec2 = 0x8FFC,
	DVec3 = 0x8FFD,
	DVec4 = 0x8FFE,
	DMat2 = 0x8F46,
	DMat3 = 0x8F47,
	DMat4 = 0x8F48,
	DMat2x3 = 0x8F49,
	DMat2x4 = 0x8F4A,
	DMat3x2 = 0x8F4B,
	DMat3x4 = 0x8F4C,
	DMat4x2 = 0x8F4D,
	DMat4x3 = 0x8F4E
};

struct ShaderUniform {
	int location;
	std::string name;
	ShaderUniformType type;
	int size;
};

struct ShaderAttribute {
	int location;
	std::string name;
	ShaderAttributeType type;
	int size;
};

enum class ShaderType {
	Vertex = 0x8B31,
	Fragment = 0x8B30,
};

class Shader 
{
public:

	/**
	* creates a shader
	* @param type type of shader to create i.e Vertex, Fragment
	* @param source source of the shader
	*/
	explicit Shader(ShaderType type, const std::string& source);
	
	/**
	* destroys the underlying OpenGL handle
	*/
	~Shader();

	/**
	* gets the id of underlying OpenGL handle
	* @returns id
	*/
	unsigned int GetId() const { return id; }

	/**
	* gets the type of the shader
	* @returns type
	*/
	ShaderType GetType() const { return type; }

private:
	unsigned int id;
	ShaderType type;
};

class ShaderProgram
{
public:
	
	/**
	* creates a shader program
	*/
	explicit ShaderProgram();
	
	/**
	* creates a shader program and linked with the provided vertex and fragment shaders
	* @param vs vertex shader to attach
	* @param fs fragment shader to attach
	*/
	explicit ShaderProgram(Shader* vs, Shader* fs);
	
	/**
	* destroys the underlying OpenGL handle
	*/
	~ShaderProgram();

	/**
	* links the program with already attached shader. call this after attaching at least one shader
	* @param log pointer to a buffer where the log is stored in (free with delete[] log after use)
	* @param size size is the size in bytes of log stored
	*/
	bool Link(char** log, size_t* size);

	/**
	* binds the program
	*/
	void Bind() const;

	/**
	* attaches shader to the program
	* @param shader shader to attach
	*/
	void AttachShader(Shader* shader);

	/**
	* gets the active uniforms data from the program. it is called when the program is linked by Link
	*/
	void GetUniformsInfo();
	
	/**
	* gets the active attributes data from the program. it is called when the program is linked by Link
	*/
	void GetAttributesInfo();

	/**
	* is the program valid to be bound
	* @return valid
	*/
	bool IsValid() const { return isValid; }

	/**
	* gets active uniforms of the program
	* @returns uniforms
	*/
	const std::vector<ShaderUniform>& GetUniforms() const { return uniforms; }

	/**
	* gets active attributes of the program
	* @returns attributes
	*/
	const std::vector<ShaderAttribute>& GetAttributes() const { return attributes; }
	
	/**
	* gets attached shaders
	* @returns shaders
	*/
	const std::vector<Shader*>& GetAttachedShader() const { return attachedShaders; }

	/**
	* gets the location of the active uniform by name
	* @param name name of the uniform
	* @returns location
	*/
	int GetUniformLocation(const char* name) const;
	
	/**
	* gets the id of underlying OpenGL handle
	* @returns id
	*/
	unsigned int GetID() const { return id; }

	/**
	* set the int uniforms value
	* @param name name of the uniform
	* @param value value of the uniform
	*/
	void UniformInt(const char* name, int value) const;
	
	/**
	* set the int64 uniforms value
	* @param name name of the uniform
	* @param value value of the uniform
	*/
	void UniformInt64(const char* name, uint64_t value) const;

	/**
	* set the float uniforms value
	* @param name name of the uniform
	* @param value value of the uniform
	*/
	void UniformFloat(const char* name, float value)  const;

	/**
	* set the vec2 uniforms value
	* @param name name of the uniform
	* @param value value of the uniform
	*/
	void UniformVec2(const char* name, float* value) const;

	void UniformUVec2(const char* name, unsigned int* value) const;

	/**
	* set the vec3 uniforms value
	* @param name name of the uniform
	* @param value value of the uniform
	*/
	void UniformVec3(const char* name, float* value) const;

	/**
	* set the vec4 uniforms value
	* @param name name of the uniform
	* @param value value of the uniform
	*/
	void UniformVec4(const char* name, float* value) const;

	/**
	* set the mat2 uniforms value
	* @param name name of the uniform
	* @param value value of the uniform
	*/
	void UniformMat2(const char* name, float* value) const;

	/**
	* set the mat3 uniforms value
	* @param name name of the uniform
	* @param value value of the uniform
	*/
	void UniformMat3(const char* name, float* value) const;

	/**
	* set the mat4 uniforms value
	* @param name name of the uniform
	* @param value value of the uniform
	*/
	void UniformMat4(const char* name, float* value) const;

	/**
	* set the int array uniforms value
	* @param name name of the uniform
	* @param count count of values
	* @param value value of the uniform
	*/
	void UniformIntArray(const char* name, int count, int* value) const;

	/**
	* set the float array uniforms value
	* @param name name of the uniform
	* @param count count of values
	* @param value value of the uniform
	*/
	void UniformFloatArray(const char* name, int count, float* value) const;

	/**
	* set the vec2 array uniforms value
	* @param name name of the uniform
	* @param count count of values
	* @param value value of the uniform
	*/
	void UniformVec2Array(const char* name, int count, float* value) const;

	/**
	* set the vec3 array uniforms value
	* @param name name of the uniform
	* @param count count of values
	* @param value value of the uniform
	*/
	void UniformVec3Array(const char* name, int count, float* value) const;

	/**
	* set the mat2 array uniforms value
	* @param name name of the uniform
	* @param count count of values
	* @param value value of the uniform
	*/
	void UniformMat2Array(const char* name, int count, float* value) const;
	
	/**
	* set the mat3 array uniforms value
	* @param name name of the uniform
	* @param count count of values
	* @param value value of the uniform
	*/
	void UniformMat3Array(const char* name, int count, float* value) const;

	/**
	* set the mat4 array uniforms value
	* @param name name of the uniform
	* @param count count of values
	* @param value value of the uniform
	*/
	void UniformMat4Array(const char* name, int count, float* value) const;

private:
	unsigned int id{ 0 };
	std::vector<ShaderUniform> uniforms;
	std::vector<ShaderAttribute> attributes;
	std::vector<Shader*> attachedShaders;
	bool isValid{ false };
};