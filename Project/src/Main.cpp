#include "engine/Renderer.h"
#include "Gui.h"
#include "vec/vec.h"

int main()
{
	Renderer* renderer = new Renderer(800, 600, "Program Window", false);
	renderer->Init();

	//Gui* gui = new Gui(renderer->m_Window);
	//gui->Init();

	float verteics[16] = {
		-0.5f, -0.5f,      0.0f, 0.0f,
		 0.5f, -0.5f,      1.0f, 0.0f,
		 0.5f,  0.5f,      1.0f, 1.0f,
		-0.5f,  0.5f,      0.0f, 1.0f
	};

	unsigned int indices[6] = {
		0, 1, 2,
		2, 3, 0
	};

	VertexArray va;
	VertexBuffer vb(verteics, 4 * 4 * sizeof(float));

	VertexBufferLayout layout;
	layout.Push<float>(2);
	layout.Push<float>(2);
	va.AddBuffer(vb, layout);

	IndexBuffer ib(indices, 6);

	Shader shader("res/shaders/basic.glsl");
	shader.Bind();

	Texture texture("res/textures/bird.png");
	texture.Bind();
	shader.SetUniform1i("u_texture", 0);

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