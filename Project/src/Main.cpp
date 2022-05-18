#include "engine/Renderer.h"
#include "Gui.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <array>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

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

static void loadOBJ(const char* path, std::vector <glm::vec3>& out_vertices, std::vector <uint32_t>& out_indices)
{
	FILE* file = fopen(path, "r");
	if (file == NULL)
	{
		printf("Impossible to open the file !\n");
		return;
	}

	while (1)
	{
		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.

		if (strcmp(lineHeader, "v") == 0)
		{
			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			out_vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vn") == 0)
		{

		}
		else if (strcmp(lineHeader, "f") == 0)
		{
			unsigned int vertexIndex[3];
			int matches = fscanf(file, "%d %d %d\n", &vertexIndex[0], &vertexIndex[1], &vertexIndex[2]);

			out_indices.push_back(vertexIndex[0] - 1);
			out_indices.push_back(vertexIndex[1] - 1);
			out_indices.push_back(vertexIndex[2] - 1);
		}
	}
}

int main()
{
	Renderer* renderer = new Renderer(800, 600, "Program Window", false);
	renderer->Init();

	std::vector <glm::vec3> objVertices;
	std::vector <uint32_t> objIndices;
	loadOBJ("res/objects/plane.obj", objVertices, objIndices);

	VertexArray va;
	VertexBuffer vb(&objVertices[0], objVertices.size() * sizeof(glm::vec3));

	VertexBufferLayout layout;
	layout.Push<float>(3);
	va.AddBuffer(vb, layout);

	IndexBuffer ib(&objIndices[0], objIndices.size() * sizeof(uint32_t));

	glm::mat4 proj = glm::perspective(glm::radians(60.0f), (float)renderer->m_WindowWidth / (float)renderer->m_WindowHeight, 0.1f, 100.0f);
	glm::mat4 veiw = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -3.0f));

	glm::mat4 model = glm::rotate(glm::mat4(1.0f), 0.4f, glm::vec3(1, 0, 0));

	Shader shader("res/shaders/basic.glsl");
	shader.Bind();

	glm::mat4 mvp = proj * veiw * model;

	shader.SetUniformMat4f("u_MVP", mvp);

	va.UnBind();
	ib.UnBind();
	vb.UnBind();
	shader.UnBind();

	float roateAngle = 0.0f;
	float offset = 0.0f;

	while (!glfwWindowShouldClose(renderer->m_Window))
	{
		renderer->Clear(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));

		shader.Bind();
		glm::mat4 model = glm::rotate(glm::mat4(1.0f), 0.4f, glm::vec3(1, 0, 0)) * glm::rotate(glm::mat4(1.0f), roateAngle, glm::vec3(0, 1, 0));
		glm::mat4 mvp = proj * veiw * model;

		shader.SetUniformMat4f("u_MVP", mvp);
		shader.SetUniform1f("u_offset", offset);

		renderer->Draw(va, ib, shader);

		roateAngle += 0.001f;
		offset += 0.03f;
		
		renderer->Render();
	}

	delete renderer;
}