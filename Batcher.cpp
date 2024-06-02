#include "Batcher.h"
#include "GL.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


void Batcher::Init()
{
	cpuBuffer = new BatchVertex[maxVerticesPerBatch];
	numVertices = 0;
	numTriangles = 0;

	gpuBuffer = new Buffer(maxVerticesPerBatch * sizeof(BatchVertex), cpuBuffer, true);

	std::string v_shader_source = R"(
		#version 460
		layout(location = 0) in vec4 position;
		layout(location = 1) in vec4 color;
		layout(location = 2) in vec2 uv;
		layout(location = 3) in vec2 texture_index;

		uniform mat4 projection;

		out vec4 v_color;
		out vec2 v_uv;
		flat out uvec2 v_texture_index;

		void main()
		{
			gl_Position = projection * position;
			v_color = color;
			v_uv = uv;
			v_texture_index = uvec2(int(texture_index.y), int(texture_index.x));
		}
	)";

	std::string f_shader_source = R"(
		#version 460
		#extension GL_ARB_bindless_texture : require

		out vec4 frag_color;

		in vec4 v_color;
		in vec2 v_uv;
		flat in uvec2 v_texture_index;
		
		void main()
		{
			if (v_texture_index.x == 0 && v_texture_index.y == 0)
			{
				frag_color = v_color;
			}
			else
			{
				frag_color = texture(sampler2D(v_texture_index), v_uv) * v_color;
			}
		}
	)";

	auto v_shader = new Shader(ShaderType::Vertex, v_shader_source);
	auto f_shader = new Shader(ShaderType::Fragment, f_shader_source);

	shaderProgram = new ShaderProgram(v_shader, f_shader);

	vertexInput = new VertexInput(*shaderProgram);

	vertexInput->SetVertexBuffer(*gpuBuffer, 0, sizeof(BatchVertex), 0);
}

void Batcher::Start()
{
	numTriangles = 0;
	numVertices = 0;
}

void Batcher::Draw()
{
	size_t size = numVertices * sizeof(BatchVertex);
	gpuBuffer->SubData(size, 0, cpuBuffer);
	vertexInput->Bind();
	shaderProgram->Bind();

	glm::mat4 projection = glm::ortho(0.0f, 1920.0f, 1080.0f, 0.0f);
	shaderProgram->UniformMat4("projection", glm::value_ptr(projection));

	glDrawArrays(GL_TRIANGLES, 0, (int)numVertices);
}

void Batcher::End()
{
	Draw();
}

void Batcher::DrawTriangle(
	const glm::vec4& p1, const glm::vec4& p2, const glm::vec4& p3,
	const glm::vec4& c1, const glm::vec4& c2, const glm::vec4& c3,
	const glm::vec2& uv1, const glm::vec2& uv2, const glm::vec2& uv3,
	uint64_t textureHandle
)
{
	if (numVertices >= maxVerticesPerBatch)
	{
		End();
		Start();
	}

	const glm::vec4 positions[3] = { p1, p2, p3 };
	const glm::vec4 colors[3] = { c1, c2, c3 };
	const glm::vec2 uvs[3] = { uv1, uv2, uv3 };
	const auto t = glm::vec2((float)(textureHandle >> 32), (float)(textureHandle & 0xFFFFFFFF));

	for (int i = 0; i < 3; i++)
	{
		cpuBuffer[numVertices].position = positions[i];
		cpuBuffer[numVertices].color = colors[i];
		cpuBuffer[numVertices].uv = uvs[i];
		cpuBuffer[numVertices].texture_handle = t;

		numVertices++;
	}

	numTriangles++;
}

void Batcher::DrawQuadEx(
	const glm::vec4& p1, const glm::vec4& p2, const glm::vec4& p3, const glm::vec4& p4,
	const glm::vec4& c1, const glm::vec4& c2, const glm::vec4& c3, const glm::vec4& c4,
	const glm::vec2& uv1, const glm::vec2& uv2, const glm::vec2& uv3, const glm::vec2& uv4,
	uint64_t textureHandle
)
{
	DrawTriangle(p1, p2, p3, c1, c2, c3, uv1, uv2, uv3, textureHandle);
	DrawTriangle(p1, p3, p4, c1, c3, c4, uv1, uv3, uv4, textureHandle);
}

void Batcher::DrawQuad(const Quad& quad, const glm::vec2& origin)
{
	auto& [pos, size, color, rect, handle] = quad;

	glm::vec2 originPoint = { size.x * origin.x, size.y * origin.y };

	glm::vec4 p1 = { pos.x - originPoint.x, pos.y - originPoint.y, 0.0f, 1.0f };
	glm::vec4 p2 = { pos.x + size.x - originPoint.x, pos.y - originPoint.y, 0.0f, 1.0f };
	glm::vec4 p3 = { pos.x + size.x - originPoint.x, pos.y + size.y - originPoint.y, 0.0f, 1.0f };
	glm::vec4 p4 = { pos.x - originPoint.x, pos.y + size.y - originPoint.y, 0.0f, 1.0f };

	glm::vec2 uv1 = { rect.position.y, rect.position.x };
	glm::vec2 uv2 = { rect.position.y + rect.size.y, rect.position.x };
	glm::vec2 uv3 = { rect.position.y + rect.size.y, rect.position.x + rect.size.x };
	glm::vec2 uv4 = { rect.position.y, rect.position.x + rect.size.x };

	DrawQuadEx(p1, p2, p3, p4, color, color, color, color, uv1, uv2, uv3, uv4, handle);
}

void Batcher::DrawQuad(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color, const glm::vec2& origin)
{
	DrawQuad({ pos, size, color, {}, 0 }, origin);
}
