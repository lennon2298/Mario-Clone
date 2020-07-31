#pragma once

#include <glad/glad.h>
#include <unordered_map>
#include <string>
#include <sstream>
#include <fstream>
#include <stb_image.h>

#include "Shader.h"
#include "Texture.h"

class ResourceManager
{
private:
	static std::unordered_map<std::string, Shader> m_ShaderMap;
	static std::unordered_map<std::string, Texture> m_TextureMap;

public:
	static Shader LoadShader(const std::string& vertexFile, const std::string& fragmentFile, std::string name);
	static Shader GetShader(std::string name);

	static Texture LoadTexture(const std::string& texFile, bool aplha, std::string name);
	static Texture GetTexture(std::string name);

	static void Clear();

private:
	static Shader ParseShader(const std::string& vertexFile, const std::string& fragmentFile);

	static Texture ParseTexture(const std::string& texFile, bool aplha);
};