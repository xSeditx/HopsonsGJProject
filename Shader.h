#pragma once
#include <iostream>
#include <glew.h>
#include <fstream>
#include <sstream>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

using namespace std;

struct ShaderProgram {
	string VertexSource;
	string FragmentSource;
};

static  ShaderProgram  ParseShader(const string & filepath)
{
	stringstream ss[2];

	ifstream stream(filepath);
	string line;
	enum class ShaderType {
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};
	ShaderType Type = ShaderType::NONE;
	while (getline(stream, line)) {
		if (line.find("#shader") != string::npos) {
			if (line.find("vertex") != string::npos) {//VERTEX
				Type = ShaderType::VERTEX;
			}
			if (line.find("fragment") != string::npos) {//FRAGMENT
				Type = ShaderType::FRAGMENT;
			}
		}
		else {
			
				ss[(int)Type] << line << '\n';
			
		}
	}
	return { ss[0].str() , ss[1].str() };
}


static unsigned int CompileShader(unsigned int type, const string & source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);


	//Error Display
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		int p;
		string str;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char*massage = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, massage);
		glGetShaderiv(id, GL_SHADER_TYPE, &p);
		cout << endl;
		cout << "Failed Shader To Compile :" << p << "|" << endl;
		cout << massage << endl;
	}
	//Return id of shader 
	return id;
}

static unsigned int CreateShader(const std::string& vertex, const std::string& fragment) {

	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertex);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragment);
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);
	glDeleteShader(vs);
	glDeleteShader(fs);
	return program;

}

class Shader
{
private:
	unsigned int m_RendererID;
public:
	Shader(string filepath);
	~Shader();
	void Bind() const;
	void Unbind() const;
	void Uniform4f(string  name, float v0, float v1, float v2, float v3);
	void Uniform1i(string  name, int v0);
	void UniformMat4f(string name, glm::mat4 mat);

};

