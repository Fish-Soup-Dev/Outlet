#include "engine/Renderer.h"
#include "Gui.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <array>

struct Vertex
{
	glm::vec3 Position;
	glm::vec4 Color;
	glm::vec2 TexCoords;
	float TexID;
};

static Vertex* CreateQuad(Vertex* target, float x, float y, glm::vec4 color, float textureID)
{
	float size = 1.0f;
	x += -0.5f;
	y += -0.5f;

	target->Position = glm::vec3(x, y, 0.0f);
	target->Color = color;
	target->TexCoords = glm::vec2(0.0f, 0.0f);
	target->TexID = textureID;
	target++;

	target->Position = glm::vec3(x + size, y, 0.0f);
	target->Color = color;
	target->TexCoords = glm::vec2(1.0f, 0.0f);
	target->TexID = textureID;
	target++;

	target->Position = glm::vec3(x + size, y + size, 0.0f);
	target->Color = color;
	target->TexCoords = glm::vec2(1.0f, 1.0f);
	target->TexID = textureID;
	target++;

	target->Position = glm::vec3(x, y + size, 0.0f);
	target->Color = color;
	target->TexCoords = glm::vec2(0.0f, 1.0f);
	target->TexID = textureID;
	target++;

	return target;
}

static glm::vec4 ConvertRGB(const uint32_t r, const uint32_t g, const uint32_t b, const uint32_t a)
{
	float R = (float)r / 255.0f;
	float G = (float)g / 255.0f;
	float B = (float)b / 255.0f;
	float A = (float)a / 255.0f;
	return glm::vec4(R, G, B, A);
}

int main()
{
	Renderer* renderer = new Renderer(800, 600, "Program Window", false);
	renderer->Init();

	const size_t MaxQuadCount = 20;
	const size_t MaxVertexCount = MaxQuadCount * 4;
	const size_t MaxIndexCount = MaxQuadCount * 6;

	VertexArray va;
	VertexBuffer vb(nullptr, sizeof(Vertex) * MaxVertexCount);

	VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(4);
	layout.Push<float>(2);
	layout.Push<float>(1);
	va.AddBuffer(vb, layout);

	uint32_t indices[MaxIndexCount];
	uint32_t offeset = 0;
	for (size_t i = 0; i < MaxIndexCount; i += 6)
	{
		indices[i + 0] = 0 + offeset;
		indices[i + 1] = 1 + offeset;
		indices[i + 2] = 2 + offeset;

		indices[i + 3] = 2 + offeset;
		indices[i + 4] = 3 + offeset;
		indices[i + 5] = 0 + offeset;

		offeset += 4;
	}

	IndexBuffer ib(indices, sizeof(indices));

	glm::mat4 proj = glm::perspective(glm::radians(60.0f), (float)renderer->m_WindowWidth / (float)renderer->m_WindowHeight, 0.1f, 100.0f);
	glm::mat4 veiw = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -2));

	Shader shader("res/shaders/basic.glsl");
	shader.Bind();

	glm::mat4 mvp = proj * veiw;

	shader.SetUniformMat4f("u_MVP", mvp);

	va.UnBind();
	ib.UnBind();
	vb.UnBind();
	shader.UnBind();

	while (!glfwWindowShouldClose(renderer->m_Window))
	{
		uint32_t indexCount = 0;

		std::array<Vertex, 20> vertices;
		Vertex* buffer = vertices.data();

		buffer = CreateQuad(buffer,  0.7f, 0.0f, ConvertRGB(97, 231, 88, 255), 0.0f);
		indexCount += 6;

		buffer = CreateQuad(buffer, -0.7f, 0.0f, ConvertRGB(246, 56, 124, 255), 0.0f);
		indexCount += 6;

		vb.Bind();
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());

		renderer->Clear(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));

		renderer->Draw(va, ib, indexCount, shader);
		
		renderer->Render();
	}

	delete renderer;
}