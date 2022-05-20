#include "Shader.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include <GL/glew.h>

Shader::Shader(const std::string& filepathVertex, const std::string& filepathFragment) : m_FilePathVertex(filepathVertex), m_FilePathFragment(filepathFragment), m_RendererID(0)
{
	ShaderProgramSource source = ParseShader(filepathVertex, filepathFragment);
	m_RendererID = CreateShader(source.VertexSource, source.FragmentSource);
}

Shader::~Shader()
{
	glDeleteProgram(m_RendererID);
}

ShaderProgramSource Shader::ParseShader(const std::string& filepathVertex, const std::string& filepathFragment)
{
	std::ifstream streamVertex(filepathVertex);
	std::ifstream streamFragment(filepathFragment);

	std::string line;
	std::stringstream ss[2];

	while (getline(streamVertex, line))
	{
		ss[0] << line << '\n';
	}

	while (getline(streamFragment, line))
	{
		ss[1] << line << '\n';
	}

	return { ss[0].str(), ss[1].str() };
}

uint32_t Shader::CompileShader(uint32_t type, const std::string& source)
{
	uint32_t id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)_malloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "[ERROR] Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader" << std::endl;
		glDeleteShader(id);
		return 0;
	}

	return id;
}

uint32_t Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	uint32_t program = glCreateProgram();
	uint32_t vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	uint32_t fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

void Shader::Bind() const
{
	glUseProgram(m_RendererID);
}

void Shader::UnBind() const
{
	glUseProgram(0);
}

void Shader::SetUniform1i(const std::string& name, int v)
{
	glUniform1i(GetUniformLocation(name), v);
}

void Shader::SetUniform1f(const std::string& name, float v)
{
	glUniform1f(GetUniformLocation(name), v);
}

void Shader::SetUniform4f(const std::string& name, glm::vec4 v)
{
	glUniform4f(GetUniformLocation(name), v.x, v.y, v.z, v.w);
}

void Shader::SetUniformMat4f(const std::string& name, glm::mat4 matrix)
{
	glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
}

int Shader::GetUniformLocation(const std::string& name) const
{
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
		return m_UniformLocationCache[name];

	int location = glGetUniformLocation(m_RendererID, name.c_str());
	if (location == -1)
		std::cout << "[WARNING] unifrom " << name << " dose not exist" << std::endl;

	m_UniformLocationCache[name] = location;
	return location;
}
