#include "Shader.h"
#include <iostream>





Shader::Shader(string  filepath)
{
	ShaderProgram src = ParseShader(filepath);
	m_RendererID = CreateShader(src.VertexSource, src.FragmentSource);
	glUseProgram(m_RendererID);
}

Shader::~Shader()
{
	glDeleteProgram(m_RendererID);
}

void Shader::Bind() const
{
	glUseProgram(m_RendererID);
}

void Shader::Unbind() const
{
	glUseProgram(0);
}

void Shader::Uniform4f(string  name, float v0, float v1, float v2, float v3)
{
	glUseProgram(m_RendererID);
	unsigned int Loc = glGetUniformLocation(m_RendererID, name.c_str());
	glUniform4f(Loc, v0, v1, v2, v3);
}

void Shader::Uniform1i(string name, int v0)
{
	glUseProgram(m_RendererID);
	unsigned int Loc = glGetUniformLocation(m_RendererID, name.c_str());
	glUniform1i(Loc, v0);
}

void Shader::UniformMat4f(string name, glm::mat4 mat)
{
	glUseProgram(m_RendererID);
	unsigned int Loc = glGetUniformLocation(m_RendererID, name.c_str());
	glUniformMatrix4fv(Loc,1 , GL_FALSE , &mat[0][0]);
	
}

