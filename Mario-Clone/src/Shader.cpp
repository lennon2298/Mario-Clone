#include "Shader.h"
#include <glad/glad.h>

#include "ErrorHandling.h"

Shader::~Shader() {

}

void Shader::DeleteShader()
{
	GLCall(glDeleteProgram(m_ID));
}

void Shader::Compile(const std::string& vertexFile, const std::string& fragmentFile)
{
	m_ID = glCreateProgram();
	unsigned int vs = CompileShader(vertexFile, GL_VERTEX_SHADER);
	unsigned int fs = CompileShader(fragmentFile, GL_FRAGMENT_SHADER);

	checkCompileErrors(vs, "VERTEX");
	checkCompileErrors(fs, "FRAGMENT");

	GLCall(glAttachShader(m_ID, vs));
	GLCall(glAttachShader(m_ID, fs));
	GLCall(glLinkProgram(m_ID));

	GLCall(glValidateProgram(m_ID));

	checkCompileErrors(m_ID, "PROGRAM");

	GLCall(glDeleteShader(vs));
	GLCall(glDeleteShader(fs));

}

Shader &Shader::Bind()
{
	GLCall(glUseProgram(m_ID));
	return *this;
}

void Shader::Unbind() const
{
	GLCall(glUseProgram(0));
}

void Shader::GetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	GLCall(glUniform4f(GetUniformLoc(name), v0, v1, v2, v3));
}

void Shader::GetUniform3f(const std::string& name, glm::vec3 vecValue)
{
	GLCall(glUniform3f(GetUniformLoc(name), vecValue.x, vecValue.y, vecValue.z));
}

void Shader::GetUniform3f(const std::string& name, float v0, float v1, float v2)
{
	GLCall(glUniform3f(GetUniformLoc(name), v0, v1, v2));
}

void Shader::GetUniform1i(const std::string& name, int value)
{
	GLCall(glUniform1i(GetUniformLoc(name), value));
}

void Shader::GetUniform1f(const std::string& name, float value)
{
	GLCall(glUniform1f(GetUniformLoc(name), value));
}

void Shader::GetUniformMat4f(const std::string& name, glm::mat4& matValue)
{
	GLCall(glUniformMatrix4fv(GetUniformLoc(name), 1, GL_FALSE, &matValue[0][0]));
}


unsigned int Shader::CompileShader(const std::string& shader, unsigned int type)
{
	unsigned int id = glCreateShader(type);
	const char* src = shader.c_str();

	GLCall(glShaderSource(id, 1, &src, nullptr));
	GLCall(glCompileShader(id));

	return id;
}

int Shader::GetUniformLoc(const std::string& name)
{
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end()) {
		return m_UniformLocationCache[name];
	}
	GLCall(int location = glGetUniformLocation(m_ID, name.c_str()));
	m_UniformLocationCache[name] = location;
	return location;
}

void Shader::checkCompileErrors(unsigned int object, std::string type)
{
	int success;
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(object, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(object, 1024, NULL, infoLog);
			std::cout << "| ERROR::SHADER: Compile-time error: Type: " << type << "\n"
				<< infoLog << "\n -- --------------------------------------------------- -- "
				<< std::endl;
		}
		else {
			std::cout << type << " SHADER COMPILED SUCCESSFULLY" << std::endl;
		}
	}
	else
	{
		glGetProgramiv(object, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(object, 1024, NULL, infoLog);
			std::cout << "| ERROR::Shader: Link-time error: Type: " << type << std::endl;
			std::cout << infoLog << "\n -- --------------------------------------------------- -- "
				<< std::endl;
		}
		else
		{
			std::cout << "Shader Linked Successfully" << std::endl;
		}
	}
}
