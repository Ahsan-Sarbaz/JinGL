#pragma once
#include "Shader.h"
#include "VertexInput.h"

#include <glm/glm.hpp>

#pragma pack(push, 1)
struct Rect
{
	glm::vec2 position;
	glm::vec2 size;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct Quad
{
	glm::vec2 position;
	glm::vec2 size;
	glm::vec4 color;
	Rect uv;
	uint64_t texture_handle;
};
#pragma pack(pop)

#pragma pack(push, 1)
struct BatchVertex
{
	glm::vec4 position;
	glm::vec4 color;
	glm::vec2 uv;
	glm::vec2 texture_handle;
};
#pragma pack(pop)

static constexpr glm::vec2 OriginTopLeft = { 0.0f, 0.0f };
static constexpr glm::vec2 OriginTopRight = { 1.0f, 0.0f };
static constexpr glm::vec2 OriginBottomLeft = { 0.0f, 1.0f };
static constexpr glm::vec2 OriginBottomRight = { 1.0f, 1.0f };
static constexpr glm::vec2 OriginCenter = { 0.5f, 0.5f };

class Batcher
{
public:
	Batcher()
		: cpuBuffer(0), gpuBuffer(0), vertexInput(0), shaderProgram(0)
	{

	}

	~Batcher()
	{
		delete cpuBuffer;
		delete gpuBuffer;
		delete vertexInput;
		delete shaderProgram;
	}

	void Init();
	void Start();
	void Draw();
	void End();

	void DrawTriangle(
		const glm::vec4& p1, const glm::vec4& p2, const glm::vec4& p3,
		const glm::vec4& c1, const glm::vec4& c2, const glm::vec4& c3,
		const glm::vec2& uv1, const glm::vec2& uv2, const glm::vec2& uv3,
		uint64_t textureHandle
	);

	void DrawQuadEx(
		const glm::vec4& p1, const glm::vec4& p2, const glm::vec4& p3, const glm::vec4& p4,
		const glm::vec4& c1, const glm::vec4& c2, const glm::vec4& c3, const glm::vec4& c4,
		const glm::vec2& uv1, const glm::vec2& uv2, const glm::vec2& uv3, const glm::vec2& uv4,
		uint64_t textureHandle
	);

	void DrawQuad(const Quad& quad, const glm::vec2& origin = OriginTopLeft);
	void DrawQuad(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color, const glm::vec2& origin = OriginTopLeft);


private:
	size_t numTriangles = 0;
	size_t numVertices = 0;
	const size_t maxTriangles = 100000;
	const size_t maxVerticesPerBatch = maxTriangles * 3;
	BatchVertex* cpuBuffer;
	Buffer* gpuBuffer;
	VertexInput* vertexInput;
	ShaderProgram* shaderProgram;
};
