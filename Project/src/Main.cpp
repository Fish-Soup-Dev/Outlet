#include "engine/Renderer.h"
#include "Gui.h"
#include "vec/vec.h"

int main()
{
	Renderer* renderer = new Renderer(800, 600, "Program Window", false);
	renderer->Init();

	//Gui* gui = new Gui(renderer->m_Window);
	//gui->Init();

	float verteics[8] = {
		-0.5f, -0.5f,
		 0.5f, -0.5f,
		 0.5f,  0.5f,
		-0.5f,  0.5f
	};

	unsigned int indices[6] = {
		0, 1, 2,
		2, 3, 0
	};

	VertexArray va;
	VertexBuffer vb(verteics, 4 * 2 * sizeof(float));

	VertexBufferLayout layout;
	layout.Push<float>(2);
	va.AddBuffer(vb, layout);

	IndexBuffer ib(indices, 6);

	Shader shader("res/shaders/basic.glsl");
	shader.Bind();
	shader.SetUniform4f("u_color", vec4(0.6f, 0.2f, 0.8f, 1.0f));

	va.UnBind();
	ib.UnBind();
	vb.UnBind();
	shader.UnBind();

	while (!glfwWindowShouldClose(renderer->m_Window))
	{
		renderer->Clear(vec4(0.2f, 0.3f, 0.3f, 1.0f));

		renderer->Draw(va, ib, shader);

		//gui->StartFrame();
		//gui->Render();
		renderer->Render();
	}

	//delete gui;
	delete renderer;
}