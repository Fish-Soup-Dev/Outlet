#include "Window.h"
#include "Gui.h"
#include "vec/vec.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"

int main()
{
	Window* window = new Window(800, 600, "Program Window", false);
	window->Init();

	Gui* gui = new Gui(window->m_Window);
	gui->Init();

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

	VertexArray* va = new VertexArray();
	VertexBuffer* vb = new VertexBuffer(verteics, 4 * 2 * sizeof(float));

	VertexBufferLayout layout;
	layout.Push<float>(2);
	va->AddBuffer(*vb, layout);

	IndexBuffer* ib = new IndexBuffer(indices, 6);

	ShaderProgramSource source = ParseShader("res/shaders/basic.glsl");
	unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);
	glUseProgram(shader);

	int location = glGetUniformLocation(shader, "u_color");
	glUniform4f(location, 0.6f, 0.2f, 0.8f, 1.0f);
	
	va->UnBind();
	ib->UnBind();
	vb->UnBind();
	glUseProgram(0);
	

	while (!glfwWindowShouldClose(window->m_Window))
	{
		window->Clear(vec4(0.2f, 0.3f, 0.3f, 1.0f));

		glUseProgram(shader);
		va->Bind();
		ib->Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

		gui->StartFrame();
		gui->Render();
		window->Render();
	}

	delete va;
	delete vb;
	delete ib;

	delete gui;
	delete window;
}