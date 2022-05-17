#include "engine/Renderer.h"
#include "Gui.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

int main()
{
	Renderer* renderer = new Renderer(800, 600, "Program Window", false);
	renderer->Init();

	float verteics[] = {
		-0.5f, -0.5f,  0.0f,
		 0.5f, -0.5f,  0.0f,
		 0.5f,  0.5f,  0.0f,
		-0.5f,  0.5f,  0.0f
	};

	unsigned int indices[6] = {
		0, 1, 2,
		2, 3, 0
	};

	VertexArray va;
	VertexBuffer vb(verteics, 12 * sizeof(float));

	VertexBufferLayout layout;
	layout.Push<float>(3);
	va.AddBuffer(vb, layout);

	IndexBuffer ib(indices, 6);

	glm::mat4 proj = glm::perspective(glm::radians(90.0f), (float)renderer->m_WindowWidth / (float)renderer->m_WindowHeight, 0.1f, 100.0f);
	glm::mat4 veiw = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

	Shader shader("res/shaders/basic.glsl");
	shader.Bind();
	shader.SetUniform4f("u_color", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

	glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -1));
	glm::mat4 mvp = proj * veiw * model;

	shader.SetUniformMat4f("u_MVP", mvp);

	va.UnBind();
	ib.UnBind();
	vb.UnBind();
	shader.UnBind();

	while (!glfwWindowShouldClose(renderer->m_Window))
	{
		renderer->Clear(glm::vec4(0.2f, 0.3f, 0.3f, 1.0f));

		renderer->Draw(va, ib, shader);
		
		renderer->Render();
	}

	delete renderer;
}