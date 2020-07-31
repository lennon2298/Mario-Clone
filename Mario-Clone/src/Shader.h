#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include <glm/glm.hpp>
#include <glm/mat4x4.hpp>

class Shader {
private:
	unsigned int m_ID;
	std::unordered_map<std::string, int> m_UniformLocationCache;

public:
	Shader() 
		:m_ID(0)
	{};
	~Shader();

	void Compile(const std::string& vertexFile, const std::string& fragmentFile);

	Shader &Bind();
	void Unbind() const;
	void DeleteShader();

	void GetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void GetUniform3f(const std::string& name, glm::vec3 vecValue);
	void GetUniform3f(const std::string& name, float v0, float v1, float v2);
	void GetUniform1i(const std::string& name, int value);
	void GetUniform1f(const std::string& name, float value);
	void GetUniformMat4f(const std::string& name, glm::mat4& matValue);

private:
	unsigned int CompileShader(const std::string& shader, unsigned int type);
	int GetUniformLoc(const std::string& name);
	void checkCompileErrors(unsigned int object, std::string type);
};
